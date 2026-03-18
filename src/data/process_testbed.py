"""
FIT IoT-LAB Testbed Feature Engineering
========================================
Processes raw radio monitoring traces into a link-level dataset with
engineered features matching the simulation feature space.

Input:
  - data/raw/iotlab_nodes.json   (node 3D coordinates from fetch_testbed.py)
  - data/raw/iotlab_radio.csv    (packet-level radio monitoring logs)

Output:
  - data/processed/testbed_dataset.csv

Features computed:
  1. Distance_m          — Euclidean 3D distance between TX and RX nodes
  2. RSSI_mean           — Mean RSSI per link per time window
  3. LQI_mean            — Mean LQI per link per time window
  4. Local_Density        — Active nodes within interference radius (R_int)
  5. PRR (target)        — Packet Reception Rate per link per window

Local_Density reconstruction:
  Matches simulation definition exactly:
    density[i] = count of nodes j where distance(i,j) < R_int AND node j is active
  where R_int = 2 * R_tx (standard IEEE 802.15.4 Protocol Interference Model)
  and "active" = node logged at least one packet in that time window.
"""
import os
import sys
import json
import csv
import argparse
import numpy as np
from scipy.spatial.distance import cdist

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
RAW_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
os.makedirs(PROCESSED_DIR, exist_ok=True)

# Default paths (Grenoble); overridden by --site argument
NODES_PATH = os.path.join(RAW_DIR, 'iotlab_nodes.json')
RADIO_PATH = os.path.join(RAW_DIR, 'iotlab_radio.csv')
OUTPUT_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')

# Time window for aggregation (seconds) — matches simulation's 10s windows
TIME_WINDOW_S = 10.0

# Number of packets expected per window per link (for PRR normalization)
# Set to 0 for auto-detection from sequence numbers
EXPECTED_PACKETS_PER_WINDOW = 7  # Hardcoded from experiment 433617 auto-detection (was 0=auto)


def load_node_coordinates():
    """Load node 3D coordinates from JSON."""
    with open(NODES_PATH) as f:
        nodes = json.load(f)
    print(f"  Loaded {len(nodes)} node coordinates")
    return nodes


def parse_radio_column(header):
    """Map flexible column names to standardized names."""
    mapping = {}
    header_lower = [h.strip().lower() for h in header]

    # Map common column name variants
    col_patterns = {
        'timestamp': ['timestamp', 'time', 'ts', 'epoch'],
        'src_node': ['src_node', 'src', 'source', 'tx_node', 'transmitter', 'src_addr'],
        'dst_node': ['dst_node', 'dst', 'dest', 'destination', 'rx_node', 'receiver', 'dst_addr'],
        'rssi': ['rssi', 'signal_strength', 'rx_power', 'received_power'],
        'lqi': ['lqi', 'link_quality', 'quality'],
        'seq_num': ['seq_num', 'seq', 'sequence', 'seqno', 'pkt_id', 'packet_id'],
        'channel': ['channel', 'ch', 'freq'],
    }

    for std_name, variants in col_patterns.items():
        for i, h in enumerate(header_lower):
            if h in variants or any(v in h for v in variants):
                mapping[std_name] = i
                break

    return mapping


def normalize_node_id(raw_id):
    """Normalize node IDs to match coordinate keys (e.g., 'm3-1')."""
    raw_id = str(raw_id).strip()
    # Already in correct format
    if raw_id.startswith('m3-'):
        return raw_id.split('.')[0]  # Strip domain suffix
    # Numeric ID
    try:
        num = int(raw_id)
        return f'm3-{num}'
    except ValueError:
        return raw_id


def load_radio_logs(col_map):
    """Load and parse radio monitoring CSV."""
    records = []
    with open(RADIO_PATH) as f:
        reader = csv.reader(f)
        next(reader)  # skip header
        for row in reader:
            try:
                ts = float(row[col_map['timestamp']]) if 'timestamp' in col_map else 0.0
                src = normalize_node_id(row[col_map['src_node']])
                dst = normalize_node_id(row[col_map['dst_node']])
                rssi = float(row[col_map['rssi']])
                lqi = float(row[col_map['lqi']]) if 'lqi' in col_map else 0.0
                seq = int(row[col_map['seq_num']]) if 'seq_num' in col_map else 0
                records.append({
                    'timestamp': ts,
                    'src': src,
                    'dst': dst,
                    'rssi': rssi,
                    'lqi': lqi,
                    'seq_num': seq,
                })
            except (ValueError, IndexError):
                continue

    print(f"  Loaded {len(records):,} valid packet records")
    return records


def compute_distance_matrix(nodes):
    """Compute NxN Euclidean distance matrix from node coordinates."""
    node_ids = sorted(nodes.keys())
    coords = np.array([[nodes[n]['x'], nodes[n]['y'], nodes[n]['z']]
                        for n in node_ids])
    dist_matrix = cdist(coords, coords, metric='euclidean')
    return node_ids, coords, dist_matrix


def determine_r_tx(records, nodes):
    """
    Determine empirical transmission range by analyzing PRR vs distance.
    R_tx = distance at which PRR drops below 10%.
    """
    # Compute per-link PRR and distance
    link_stats = {}
    for rec in records:
        if rec['src'] not in nodes or rec['dst'] not in nodes:
            continue
        link = (rec['src'], rec['dst'])
        if link not in link_stats:
            link_stats[link] = {'count': 0}
        link_stats[link]['count'] += 1

    if not link_stats:
        return 15.0  # Default fallback

    # Get distances
    distances = []
    prrs = []
    max_count = max(s['count'] for s in link_stats.values())

    for (src, dst), stats in link_stats.items():
        src_c = np.array([nodes[src]['x'], nodes[src]['y'], nodes[src]['z']])
        dst_c = np.array([nodes[dst]['x'], nodes[dst]['y'], nodes[dst]['z']])
        dist = np.linalg.norm(src_c - dst_c)
        prr = stats['count'] / max_count  # Normalized reception rate
        distances.append(dist)
        prrs.append(prr)

    distances = np.array(distances)
    prrs = np.array(prrs)

    # Find R_tx: distance where PRR drops below 10%
    # Bin distances and compute mean PRR per bin
    if len(distances) < 10:
        return 15.0

    sorted_idx = np.argsort(distances)
    n_bins = min(20, len(distances) // 5)
    if n_bins < 3:
        return np.median(distances)

    bin_edges = np.linspace(distances.min(), distances.max(), n_bins + 1)
    r_tx = bin_edges[-1]  # Default to max distance

    for i in range(len(bin_edges) - 1):
        mask = (distances >= bin_edges[i]) & (distances < bin_edges[i + 1])
        if mask.sum() > 0:
            bin_prr = prrs[mask].mean()
            if bin_prr < 0.10:
                r_tx = bin_edges[i]
                break

    print(f"  Empirical R_tx = {r_tx:.1f} m (PRR < 10% threshold)")
    return r_tx


def compute_local_density(node_ids, dist_matrix, active_set, r_int):
    """
    Compute Local_Density for each node: count of active neighbors within R_int.
    Matches simulation definition: (dist_to_others < interference_range) & active_mask

    Args:
        node_ids: ordered list of node IDs
        dist_matrix: NxN Euclidean distance matrix
        active_set: set of node IDs that are active in this window
        r_int: interference radius (= 2 * R_tx)

    Returns:
        dict mapping node_id -> density count
    """
    id_to_idx = {nid: i for i, nid in enumerate(node_ids)}
    density = {}

    for nid in node_ids:
        if nid not in active_set:
            density[nid] = 0
            continue

        i = id_to_idx[nid]
        count = 0
        for other_nid in active_set:
            if other_nid == nid:
                continue
            j = id_to_idx.get(other_nid)
            if j is not None and dist_matrix[i, j] < r_int:
                count += 1
        density[nid] = count

    return density


def aggregate_link_features(records, nodes, node_ids, dist_matrix, r_int):
    """
    Aggregate packet-level records into link-level features per time window.

    Returns list of dicts with:
        src, dst, window_start, Distance_m, RSSI_mean, LQI_mean,
        Local_Density, PRR, n_packets_received
    """
    # Determine time window boundaries
    timestamps = [r['timestamp'] for r in records]
    t_min, t_max = min(timestamps), max(timestamps)
    n_windows = max(1, int(np.ceil((t_max - t_min) / TIME_WINDOW_S)))

    print(f"  Time span: {t_max - t_min:.1f}s across {n_windows} windows")

    # Group records by time window
    window_records = [[] for _ in range(n_windows)]
    for rec in records:
        w_idx = min(int((rec['timestamp'] - t_min) / TIME_WINDOW_S), n_windows - 1)
        window_records[w_idx].append(rec)

    # Determine expected packets per window for PRR
    # Use the median of max observed packets per link per window as the denominator
    expected_pkts = EXPECTED_PACKETS_PER_WINDOW
    if expected_pkts == 0:
        link_counts = {}
        for w_recs in window_records:
            window_links = {}
            for rec in w_recs:
                link = (rec['src'], rec['dst'])
                window_links[link] = window_links.get(link, 0) + 1
            for link, count in window_links.items():
                link_counts[link] = max(link_counts.get(link, 0), count)
        if link_counts:
            expected_pkts = int(np.median(list(link_counts.values())))
        else:
            expected_pkts = 10
        print(f"  Auto-detected expected packets/window: {expected_pkts}")

    # Precompute node distances for link pairs
    id_to_idx = {nid: i for i, nid in enumerate(node_ids)}

    # Aggregate per window
    dataset = []
    for w_idx, w_recs in enumerate(window_records):
        if not w_recs:
            continue

        # Find active nodes in this window (nodes that sent or received packets)
        active_set = set()
        for rec in w_recs:
            active_set.add(rec['src'])
            active_set.add(rec['dst'])
        active_set = active_set & set(node_ids)  # Only nodes with coordinates

        # Compute density for this window
        density = compute_local_density(node_ids, dist_matrix, active_set, r_int)

        # Aggregate per link
        link_data = {}
        for rec in w_recs:
            if rec['src'] not in id_to_idx or rec['dst'] not in id_to_idx:
                continue
            link = (rec['src'], rec['dst'])
            if link not in link_data:
                link_data[link] = {'rssi': [], 'lqi': [], 'count': 0}
            link_data[link]['rssi'].append(rec['rssi'])
            link_data[link]['lqi'].append(rec['lqi'])
            link_data[link]['count'] += 1

        for (src, dst), data in link_data.items():
            # Skip links with too few packets to avoid noise records
            if data['count'] < 3:
                continue
            i_src = id_to_idx[src]
            i_dst = id_to_idx[dst]
            distance = dist_matrix[i_src, i_dst]
            prr = min(1.0, data['count'] / expected_pkts)

            dataset.append({
                'src_node': src,
                'dst_node': dst,
                'window_idx': w_idx,
                'Distance_m': round(distance, 4),
                'RSSI_mean': round(np.mean(data['rssi']), 2),
                'LQI_mean': round(np.mean(data['lqi']), 2),
                'Local_Density': density.get(dst, 0),  # Density at receiver
                'PRR': round(prr, 6),
                'n_packets': data['count'],
            })

    return dataset


def save_dataset(dataset):
    """Save processed dataset to CSV."""
    fieldnames = ['src_node', 'dst_node', 'window_idx', 'Distance_m',
                  'RSSI_mean', 'LQI_mean', 'Local_Density', 'PRR', 'n_packets']

    with open(OUTPUT_PATH, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(dataset)

    print(f"  Saved {len(dataset):,} link records to: {OUTPUT_PATH}")


def print_dataset_summary(dataset):
    """Print summary statistics for quality verification."""
    if not dataset:
        print("  WARNING: Empty dataset!")
        return

    prrs = [d['PRR'] for d in dataset]
    dists = [d['Distance_m'] for d in dataset]
    rssis = [d['RSSI_mean'] for d in dataset]
    densities = [d['Local_Density'] for d in dataset]

    print(f"\n  Dataset Summary:")
    print(f"    Records:     {len(dataset):,}")
    print(f"    Unique links: {len(set((d['src_node'], d['dst_node']) for d in dataset)):,}")
    print(f"    Unique RX nodes: {len(set(d['dst_node'] for d in dataset))}")
    print(f"    Windows:     {max(d['window_idx'] for d in dataset) + 1}")

    print(f"\n  Feature Ranges:")
    print(f"    Distance_m:    [{min(dists):.1f}, {max(dists):.1f}]  "
          f"mean={np.mean(dists):.1f}")
    print(f"    RSSI_mean:     [{min(rssis):.1f}, {max(rssis):.1f}]  "
          f"mean={np.mean(rssis):.1f}")
    print(f"    Local_Density: [{min(densities)}, {max(densities)}]  "
          f"mean={np.mean(densities):.1f}")
    print(f"    PRR:           [{min(prrs):.3f}, {max(prrs):.3f}]  "
          f"mean={np.mean(prrs):.3f}")

    # Check for meaningful transitional region
    transitional = [p for p in prrs if 0.1 <= p <= 0.9]
    pct = 100 * len(transitional) / len(prrs)
    print(f"\n  Transitional Region (0.1 <= PRR <= 0.9): "
          f"{len(transitional):,} records ({pct:.1f}%)")
    if pct < 5:
        print("  WARNING: Very few transitional links. Model discrimination may be weak.")


def main():
    print("=" * 60)
    print("FIT IoT-LAB Testbed Feature Engineering")
    print("=" * 60)

    # Step 1: Load coordinates
    print("\nStep 1: Loading node coordinates...")
    if not os.path.exists(NODES_PATH):
        print(f"  ERROR: {NODES_PATH} not found. Run fetch_testbed.py first.")
        return
    nodes = load_node_coordinates()

    # Step 2: Load radio logs
    print("\nStep 2: Loading radio monitoring data...")
    if not os.path.exists(RADIO_PATH):
        print(f"  ERROR: {RADIO_PATH} not found.")
        print(f"  Place your radio monitoring CSV there and re-run.")
        return

    with open(RADIO_PATH) as f:
        header = next(csv.reader(f))
    col_map = parse_radio_column(header)
    print(f"  Column mapping: {col_map}")

    records = load_radio_logs(col_map)
    if not records:
        print("  ERROR: No valid records parsed.")
        return

    # Step 3: Compute distance matrix
    print("\nStep 3: Computing distance matrix...")
    node_ids, coords, dist_matrix = compute_distance_matrix(nodes)
    print(f"  {len(node_ids)} nodes, distance range: "
          f"[{dist_matrix[dist_matrix > 0].min():.2f}, {dist_matrix.max():.2f}] m")

    # Step 4: Determine R_tx and R_int
    print("\nStep 4: Determining interference radius...")
    r_tx = determine_r_tx(records, nodes)
    r_int = 2.0 * r_tx
    print(f"  R_int = 2 * R_tx = {r_int:.1f} m")

    # Compare with simulation's 30m
    if abs(r_int - 30.0) > 10.0:
        print(f"  NOTE: R_int ({r_int:.1f}m) differs from simulation (30.0m).")
        print(f"  Using empirical R_int for testbed. Document this in the paper.")

    # Step 5: Aggregate features
    print("\nStep 5: Aggregating link-level features...")
    dataset = aggregate_link_features(records, nodes, node_ids, dist_matrix, r_int)

    # Step 6: Save and summarize
    print("\nStep 6: Saving dataset...")
    save_dataset(dataset)
    print_dataset_summary(dataset)

    print("\n" + "=" * 60)
    print("DONE. Next: python src/modeling/testbed_validation.py")
    print("=" * 60)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process testbed data')
    parser.add_argument('--site', default=None,
                        help='IoT-LAB site name (e.g., lille). Uses site-specific file paths.')
    args = parser.parse_args()

    if args.site and args.site != 'grenoble':
        NODES_PATH = os.path.join(RAW_DIR, f'iotlab_nodes_{args.site}.json')
        RADIO_PATH = os.path.join(RAW_DIR, f'iotlab_radio_{args.site}.csv')
        OUTPUT_PATH = os.path.join(PROCESSED_DIR, f'testbed_dataset_{args.site}.csv')

    main()
