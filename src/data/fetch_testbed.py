"""
FIT IoT-LAB Testbed Data Acquisition
=====================================
Downloads node coordinates from the FIT IoT-LAB REST API and converts
sniffer PCAP data from IoT-LAB experiments into the CSV format expected
by process_testbed.py.

Usage:
  1. Run this script to download Grenoble M3 node coordinates.
  2. Place your sniffer PCAP at data/raw/iotlab_sniffer.pcap
     OR place a pre-converted CSV at data/raw/iotlab_radio.csv
  3. Run process_testbed.py to compute link-level features.

Supports two input formats:
  A) PCAP from IoT-LAB sniffer mode (ZEPv2 encapsulated 802.15.4 frames)
  B) Pre-converted CSV with columns: timestamp,src_node,dst_node,rssi,lqi,seq_num,channel
"""
import os
import json
import csv
import sys
import struct
import argparse

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
RAW_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw')
os.makedirs(RAW_DIR, exist_ok=True)

# Default site
SITE = 'grenoble'

NODES_OUTPUT = os.path.join(RAW_DIR, 'iotlab_nodes.json')
PCAP_INPUT = os.path.join(RAW_DIR, 'iotlab_sniffer.pcap')
RADIO_OUTPUT = os.path.join(RAW_DIR, 'iotlab_radio.csv')


def get_api_urls(site):
    """Return IoT-LAB REST API endpoints for the given site."""
    return [
        f"https://www.iot-lab.info/api/nodes?site={site}&archi=m3",
        f"https://www.iot-lab.info/api/sites/{site}/nodes",
        f"https://www.iot-lab.info/rest/nodes?site={site}",
    ]


# Default URLs for backward compatibility
IOTLAB_API_URLS = get_api_urls(SITE)

# IoT-LAB M3 node 802.15.4 short address mapping
# Short addresses are typically assigned as node_id (e.g., m3-2 -> 0x0002)
# This can also be extracted from the experiment metadata


def fetch_node_coordinates(site=None):
    """Download node coordinates from FIT IoT-LAB REST API."""
    site = site or SITE
    api_urls = get_api_urls(site)

    print("=" * 60)
    print(f"STEP 1: Fetching FIT IoT-LAB {site.title()} Node Coordinates")
    print("=" * 60)

    import urllib.request
    raw_list = None
    for api_url in api_urls:
        try:
            print(f"  Trying: {api_url}")
            req = urllib.request.Request(api_url)
            req.add_header('Accept', 'application/json')
            with urllib.request.urlopen(req, timeout=30) as resp:
                data = json.loads(resp.read().decode())
            raw_list = data.get('items', data) if isinstance(data, dict) else data
            print(f"  Success: received {len(raw_list)} entries")
            break
        except Exception as e:
            print(f"    Failed: {e}")

    if raw_list is None:
        print("  All API endpoints failed.")
        print(f"  Place node coordinates JSON at: {NODES_OUTPUT}")
        return False

    nodes = {}
    for entry in raw_list:
        addr = entry.get('network_address', '')
        node_id = addr.split('.')[0] if '.' in addr else addr

        if not node_id.startswith('m3'):
            continue

        try:
            x = float(entry.get('x', 0))
            y = float(entry.get('y', 0))
            z = float(entry.get('z', 0))
        except (ValueError, TypeError):
            continue

        if x == 0 and y == 0 and z == 0:
            continue

        nodes[node_id] = {'x': x, 'y': y, 'z': z}

    print(f"  Found {len(nodes)} M3 nodes with valid 3D coordinates")

    output_path = NODES_OUTPUT
    if site and site != 'grenoble':
        output_path = os.path.join(RAW_DIR, f'iotlab_nodes_{site}.json')

    with open(output_path, 'w') as f:
        json.dump(nodes, f, indent=2)
    print(f"  Saved to: {output_path}")

    return True


# ============================================================
# PCAP / ZEPv2 Parser
# ============================================================

def parse_pcap_global_header(f):
    """Read PCAP global header, return (byte_order, link_type)."""
    magic = f.read(4)
    if len(magic) < 4:
        return None, None

    magic_val = struct.unpack('<I', magic)[0]
    if magic_val == 0xa1b2c3d4:
        endian = '<'
    elif magic_val == 0xd4c3b2a1:
        endian = '>'
    else:
        print(f"  ERROR: Not a valid PCAP file (magic: {magic.hex()})")
        return None, None

    ver_major, ver_minor, tz, sigfigs, snaplen, link_type = struct.unpack(
        endian + 'HHiIII', f.read(20))

    # Link type 230 = IEEE 802.15.4 (no FCS)
    # Link type 195 = IEEE 802.15.4 (with FCS)
    # Link type 148 = ZEP (used by IoT-LAB sniffer)
    print(f"  PCAP version: {ver_major}.{ver_minor}, link type: {link_type}")
    return endian, link_type


def parse_zepv2_header(data):
    """
    Parse ZEPv2 header from sniffer data.
    ZEPv2 format (32 bytes):
      bytes 0-1:   "EX" (protocol ID)
      byte 2:      version (2)
      byte 3:      type (1=data, 2=ack)
      bytes 4-7:   Channel ID (uint32 BE)
      bytes 8-9:   Device ID (uint16 BE)
      byte 10:     LQI/CRC mode flag
      byte 11:     LQI value
      bytes 12-19: NTP timestamp (8 bytes)
      bytes 20-23: Sequence number (uint32 BE)
      bytes 24-31: Reserved (10 bytes in some versions)
      byte 32:     IEEE 802.15.4 frame length

    Returns dict with parsed fields or None on failure.
    """
    if len(data) < 32:
        return None

    # Check "EX" magic
    if data[0:2] != b'EX':
        return None

    version = data[2]
    if version != 2:
        return None

    pkt_type = data[3]
    channel = struct.unpack('>I', data[4:8])[0]
    device_id = struct.unpack('>H', data[8:10])[0]
    lqi_mode = data[10]
    lqi_val = data[11]

    # NTP timestamp (seconds since 1900-01-01)
    ntp_sec = struct.unpack('>I', data[12:16])[0]
    ntp_frac = struct.unpack('>I', data[16:20])[0]
    # Convert NTP to Unix timestamp (NTP epoch is 1900, Unix is 1970)
    NTP_DELTA = 2208988800
    unix_ts = ntp_sec - NTP_DELTA + ntp_frac / (2**32)

    seq_num = struct.unpack('>I', data[20:24])[0]

    # Reserved bytes may contain RSSI in some implementations
    # IoT-LAB stores RSSI as signed int8 in reserved[0] (byte 24)
    rssi = struct.unpack('b', data[24:25])[0] if len(data) > 24 else 0

    # Frame length at byte 31 (for standard 32-byte ZEPv2 header)
    frame_len = data[31] if len(data) > 31 else 0

    return {
        'version': version,
        'type': pkt_type,
        'channel': channel,
        'device_id': device_id,
        'lqi': lqi_val,
        'timestamp': unix_ts,
        'seq_num': seq_num,
        'rssi': rssi,
        'frame_len': frame_len,
    }


def parse_802154_addresses(frame_data):
    """
    Parse IEEE 802.15.4 MAC header to extract src and dst short addresses.
    Returns (src_addr, dst_addr) as integers, or (None, None) on failure.
    """
    if len(frame_data) < 9:
        return None, None

    # Frame Control Field (2 bytes, little-endian)
    fcf = struct.unpack('<H', frame_data[0:2])[0]

    frame_type = fcf & 0x07
    # Only parse data frames (type 1) and command frames (type 3)
    if frame_type not in (1, 3):
        return None, None

    dst_addr_mode = (fcf >> 10) & 0x03
    src_addr_mode = (fcf >> 14) & 0x03

    # Sequence number at byte 2
    # seq = frame_data[2]

    offset = 3  # After FCF + seq

    dst_addr = None
    src_addr = None

    # Destination PAN + address
    if dst_addr_mode == 2:  # Short address
        if len(frame_data) < offset + 4:
            return None, None
        # dst_pan = struct.unpack('<H', frame_data[offset:offset+2])[0]
        offset += 2
        dst_addr = struct.unpack('<H', frame_data[offset:offset+2])[0]
        offset += 2
    elif dst_addr_mode == 3:  # Extended address
        offset += 2 + 8  # PAN + 8-byte address
        # Skip for now — IoT-LAB M3 typically uses short addresses

    # Source PAN + address (PAN may be compressed)
    pan_id_compression = (fcf >> 6) & 0x01
    if src_addr_mode == 2:  # Short address
        if not pan_id_compression:
            offset += 2  # Source PAN
        if len(frame_data) < offset + 2:
            return dst_addr, None
        src_addr = struct.unpack('<H', frame_data[offset:offset+2])[0]
    elif src_addr_mode == 3:  # Extended address
        if not pan_id_compression:
            offset += 2
        # Skip extended

    return src_addr, dst_addr


def short_addr_to_node_id(addr):
    """
    Map 802.15.4 short address to IoT-LAB node ID.
    Common convention: m3-N uses short address N (or N+1).
    Returns "m3-N" string.
    """
    if addr is None or addr == 0xFFFF:  # Broadcast
        return None
    return f"m3-{addr}"


def parse_pcap_to_csv(pcap_path, csv_path):
    """
    Parse IoT-LAB sniffer PCAP (ZEPv2 encapsulated) to CSV.

    Each PCAP record contains:
      - ZEPv2 header (32 bytes): timestamp, channel, LQI, seq_num, device_id, RSSI
      - IEEE 802.15.4 frame: src/dst short addresses
    """
    print(f"\n  Parsing PCAP: {pcap_path}")

    records = []
    errors = 0

    with open(pcap_path, 'rb') as f:
        endian, link_type = parse_pcap_global_header(f)
        if endian is None:
            return False

        pkt_count = 0
        while True:
            # Read PCAP record header (16 bytes)
            rec_hdr = f.read(16)
            if len(rec_hdr) < 16:
                break

            ts_sec, ts_usec, incl_len, orig_len = struct.unpack(
                endian + 'IIII', rec_hdr)

            # Read packet data
            pkt_data = f.read(incl_len)
            if len(pkt_data) < incl_len:
                break

            pkt_count += 1

            # For ZEP link type (148) or UDP-encapsulated ZEP
            zep_offset = 0

            if link_type == 148:
                # Direct ZEP encapsulation
                zep_offset = 0
            elif link_type == 1:
                # Ethernet -> IP -> UDP -> ZEP
                # Skip Ethernet (14) + IP (20) + UDP (8) = 42 bytes minimum
                if len(pkt_data) < 42:
                    errors += 1
                    continue
                zep_offset = 42
            else:
                # Try to find "EX" magic in the packet
                ex_pos = pkt_data.find(b'EX')
                if ex_pos >= 0:
                    zep_offset = ex_pos
                else:
                    errors += 1
                    continue

            zep_data = pkt_data[zep_offset:]
            zep = parse_zepv2_header(zep_data)
            if zep is None:
                errors += 1
                continue

            # Extract 802.15.4 frame (after 32-byte ZEP header)
            frame_start = zep_offset + 32
            if frame_start >= len(pkt_data):
                errors += 1
                continue

            frame_data = pkt_data[frame_start:]
            src_addr, dst_addr = parse_802154_addresses(frame_data)

            src_node = short_addr_to_node_id(src_addr)
            dst_node = short_addr_to_node_id(dst_addr)

            if src_node is None:
                # Use ZEP device_id as fallback for source
                src_node = f"m3-{zep['device_id']}"

            # Use PCAP timestamp if ZEP NTP timestamp is zero
            timestamp = zep['timestamp']
            if timestamp <= 0:
                timestamp = ts_sec + ts_usec / 1e6

            # Use ZEP RSSI; if zero, try to extract from 802.15.4 frame metadata
            rssi = zep['rssi']

            records.append([
                round(timestamp, 6),
                src_node,
                dst_node if dst_node else 'broadcast',
                rssi,
                zep['lqi'],
                zep['seq_num'],
                zep['channel'],
            ])

    print(f"  Total PCAP packets: {pkt_count:,}")
    print(f"  Successfully parsed: {len(records):,}")
    if errors > 0:
        print(f"  Parse errors/skipped: {errors:,}")

    if not records:
        print("  ERROR: No records extracted from PCAP.")
        return False

    # Filter out broadcast packets (no useful dst)
    unicast = [r for r in records if r[2] != 'broadcast']
    broadcast = len(records) - len(unicast)
    if broadcast > 0:
        print(f"  Broadcast packets (excluded): {broadcast:,}")
        print(f"  Unicast packets (kept): {len(unicast):,}")

    # If all packets are broadcast, keep them — the sniffer node IS the receiver
    output_records = unicast if unicast else records

    # Save CSV
    with open(csv_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['timestamp', 'src_node', 'dst_node', 'rssi', 'lqi',
                          'seq_num', 'channel'])
        writer.writerows(output_records)

    print(f"  Saved {len(output_records):,} records to: {csv_path}")

    # Summary
    src_nodes = set(r[1] for r in output_records)
    dst_nodes = set(r[2] for r in output_records)
    rssis = [r[3] for r in output_records]
    lqis = [r[4] for r in output_records]

    print(f"\n  Summary:")
    print(f"    Unique TX nodes: {len(src_nodes)}")
    print(f"    Unique RX nodes: {len(dst_nodes)}")
    print(f"    RSSI range: [{min(rssis)}, {max(rssis)}] dBm")
    print(f"    LQI range:  [{min(lqis)}, {max(lqis)}]")

    return True


def parse_tshark_csv(tshark_csv_path, output_csv_path):
    """
    Alternative parser: if user pre-converts PCAP with tshark.

    Command to generate input:
      tshark -r experiment.pcap -T fields \
        -e frame.time_epoch -e wpan.src16 -e wpan.dst16 \
        -e zep.lqi -e zep.channel_id -e frame.number \
        -E header=y -E separator=, > tshark_output.csv

    This function maps tshark output to the pipeline's expected format.
    """
    print(f"\n  Parsing tshark CSV: {tshark_csv_path}")

    records = []
    with open(tshark_csv_path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            try:
                ts = float(row.get('frame.time_epoch', 0))
                src = row.get('wpan.src16', '')
                dst = row.get('wpan.dst16', '')

                # Convert hex addresses to node IDs
                if src.startswith('0x'):
                    src = f"m3-{int(src, 16)}"
                if dst.startswith('0x'):
                    dst = f"m3-{int(dst, 16)}"

                lqi = int(row.get('zep.lqi', 0))
                channel = int(row.get('zep.channel_id', 11))
                seq = int(row.get('frame.number', 0))

                # tshark may not directly expose RSSI from ZEP reserved field
                # Use LQI as proxy or extract separately
                rssi = int(row.get('zep.rssi', 0))

                records.append([
                    round(ts, 6), src, dst, rssi, lqi, seq, channel
                ])
            except (ValueError, KeyError):
                continue

    with open(output_csv_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['timestamp', 'src_node', 'dst_node', 'rssi', 'lqi',
                          'seq_num', 'channel'])
        writer.writerows(records)

    print(f"  Converted {len(records):,} records to: {output_csv_path}")
    return len(records) > 0


def validate_radio_data():
    """Check if radio monitoring data exists and has the expected format."""
    print("\n" + "=" * 60)
    print("STEP 2: Checking for Radio Data")
    print("=" * 60)

    # Priority 1: PCAP file from sniffer mode
    if os.path.exists(PCAP_INPUT):
        print(f"  Found PCAP: {PCAP_INPUT}")
        fsize = os.path.getsize(PCAP_INPUT)
        print(f"  File size: {fsize:,} bytes")
        return parse_pcap_to_csv(PCAP_INPUT, RADIO_OUTPUT)

    # Priority 2: tshark pre-converted CSV
    tshark_path = os.path.join(RAW_DIR, 'tshark_output.csv')
    if os.path.exists(tshark_path):
        print(f"  Found tshark CSV: {tshark_path}")
        return parse_tshark_csv(tshark_path, RADIO_OUTPUT)

    # Priority 3: Already-converted CSV
    if os.path.exists(RADIO_OUTPUT):
        print(f"  Found existing CSV: {RADIO_OUTPUT}")
        with open(RADIO_OUTPUT) as f:
            reader = csv.reader(f)
            header = next(reader)
            n_rows = sum(1 for _ in reader)
        print(f"  Columns: {header}")
        print(f"  Records: {n_rows:,}")
        return n_rows > 0

    # Nothing found
    print("  No radio data found. Expected one of:")
    print(f"    1. {PCAP_INPUT}  (sniffer PCAP from IoT-LAB)")
    print(f"    2. {os.path.join(RAW_DIR, 'tshark_output.csv')}  (tshark CSV)")
    print(f"    3. {RADIO_OUTPUT}  (pre-converted CSV)")
    print(f"\n  IoT-LAB sniffer data retrieval:")
    print(f"    ssh <login>@grenoble.iot-lab.info")
    print(f"    sniffer_aggregator -r -d <exp_id> -o experiment.pcap")
    print(f"    scp experiment.pcap to {PCAP_INPUT}")
    print(f"\n  Alternative (tshark conversion on the server):")
    print(f"    tshark -r experiment.pcap -T fields \\")
    print(f"      -e frame.time_epoch -e wpan.src16 -e wpan.dst16 \\")
    print(f"      -e zep.lqi -e zep.channel_id -e frame.number \\")
    print(f"      -E header=y -E separator=, > tshark_output.csv")
    return False


def main(site=None):
    coords_ok = fetch_node_coordinates(site=site)
    radio_ok = validate_radio_data()

    print("\n" + "=" * 60)
    print("STATUS SUMMARY")
    print("=" * 60)
    print(f"  Node coordinates: {'OK' if coords_ok else 'MISSING'}")
    print(f"  Radio data:       {'OK' if radio_ok else 'MISSING'}")

    if coords_ok and radio_ok:
        print("\n  Ready to run: python src/data/process_testbed.py")
    else:
        if not radio_ok:
            print(f"\n  Waiting for experiment data.")
            print(f"  Place sniffer PCAP at: {PCAP_INPUT}")
            print(f"  Or pre-converted CSV at: {RADIO_OUTPUT}")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Fetch IoT-LAB testbed data')
    parser.add_argument('--site', default='grenoble',
                        help='IoT-LAB site name (e.g., grenoble, lille)')
    args = parser.parse_args()
    SITE = args.site
    if args.site != 'grenoble':
        NODES_OUTPUT = os.path.join(RAW_DIR, f'iotlab_nodes_{args.site}.json')
    main(site=args.site)
