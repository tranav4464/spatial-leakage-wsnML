"""
WSN Dataset Generator — High-Fidelity Physical Simulation with Hidden States
Grounded in IEEE 802.15.4 Physical and MAC-Layer Models
=============================================================
This script generates a realistic Wireless Sensor Network dataset.
Crucially, it introduces hidden spatial variables to make the dataset
non-trivial for simple analytical curve-fitting:
1.  **Spatial Obstacles**: A central "wall" causes non-linear path loss.
2.  **Hidden Terminals**: Asymmetric collisions based on spatial geometry.
3.  **Feature Masking**: Node coordinates (X, Y) are NOT saved in the dataset.
    The ML model must infer the RF environment through proxy features.

PHY Model: O-QPSK BER with IEEE 802.15.4 DSSS processing gain (spreading factor=8).
    The effective Eb/N0 = SNR * 8 due to 2 Mcps chip rate / 250 kbps data rate.
    Ref: Zuniga & Krishnamachari, "Analyzing the transitional region in
         low power wireless links," IEEE SECON 2004.
MAC Model: p-persistent CSMA approximation with IEEE 802.15.4 defaults
    (macMinBE=3, macMaxBE=5, macMaxCSMABackoffs=4).
"""

import numpy as np
import csv
import os
import itertools
from scipy.special import erfc

# ============================================================
# SIMULATION PARAMETERS
# ============================================================
AREA_SIZE = 100.0
NODE_COUNTS = [100, 200, 300]
TX_POWERS_DBM = [-25, -15, -10, -5, 0]
NOISE_FLOORS_DBM = [-100, -90, -80]
INITIAL_ENERGIES_J = [2.0, 5.0, 10.0]
SIM_DURATION_S = 300.0
TIME_WINDOW_S = 10.0
PACKETS_PER_WINDOW = 30
RANDOM_SEED = 42
NUM_DEPLOYMENTS = 5  # Independent spatial placements per configuration

# RF Physics (IEEE 802.15.4 at 2.4 GHz)
FREQ_HZ = 2.4e9
WAVELENGTH = 3e8 / FREQ_HZ
D0 = 1.0
PATH_LOSS_EXP = 3.0
SHADOWING_STD = 4.0
FRAME_LENGTH_BITS = 127 * 8
OBSTACLE_PENALTY_DB = 8.0

# Hardware Limits (CC2420 Transceiver)
RX_SENSITIVITY_DBM = -95.0
RSSI_MAX_DBM = -10.0
RSSI_MIN_DBM = -100.0

# Energy Model (CC2420)
SUPPLY_VOLTAGE = 3.0
RX_CURRENT_A = 18.8e-3
IDLE_CURRENT_A = 0.426e-3
TX_CURRENT_MAP = {
    -25: 8.5e-3, -15: 9.9e-3, -10: 11.2e-3, -5: 14.0e-3, 0: 17.4e-3,
}
TX_DURATION_S = 0.004256
RX_DURATION_S = 0.004256

# Advanced Physics Thresholds
VOLTAGE_DROOP_THRESHOLD_J = 1.0
INTERFERENCE_RANGE_M = 30.0

# IEEE 802.15.4 MAC Parameters (unslotted CSMA/CA defaults)
MAC_MIN_BE = 3
MAC_MAX_BE = 5
MAC_MAX_CSMA_BACKOFFS = 4


def place_nodes(n_nodes, rng):
    sink = np.array([[AREA_SIZE / 2, AREA_SIZE / 2]])
    nodes = rng.uniform(5, AREA_SIZE - 5, size=(n_nodes, 2))
    return nodes, sink


def compute_distances(nodes, sink):
    return np.sqrt(np.sum((nodes - sink[0]) ** 2, axis=1))


def compute_carrier_sense_range(tx_power_dbm):
    """Compute the maximum distance at which a node's transmission can be sensed,
    based on the path loss model and receiver sensitivity."""
    pl_d0 = 20 * np.log10(4 * np.pi * D0 / WAVELENGTH)
    # max_path_loss = tx_power - rx_sensitivity (ignoring shadowing for CS range)
    max_pl = tx_power_dbm - RX_SENSITIVITY_DBM
    # Solve: max_pl = pl_d0 + 10*n*log10(d/d0) for d
    exponent = (max_pl - pl_d0) / (10 * PATH_LOSS_EXP)
    return D0 * (10 ** exponent)


def compute_local_density_and_hidden(nodes, sink, active_mask, interference_range,
                                     tx_power_dbm):
    """
    Computes standard density and hidden-terminal contention.
    Hidden terminal: A node that can reach the sink but cannot hear
    the current transmitting node. Carrier-sense range is derived from
    the path loss model and receiver sensitivity.
    """
    n_nodes = len(nodes)
    density = np.zeros(n_nodes)
    hidden_terminals = np.zeros(n_nodes)

    cs_range = compute_carrier_sense_range(tx_power_dbm)
    dist_to_sink = compute_distances(nodes, sink)
    can_reach_sink = dist_to_sink < cs_range

    for i in range(n_nodes):
        if not active_mask[i]:
            continue
        dist_to_others = np.sqrt(np.sum((nodes - nodes[i]) ** 2, axis=1))

        # Standard density: Active nodes within interference range
        in_range = (dist_to_others < interference_range) & active_mask
        in_range[i] = False
        density[i] = np.sum(in_range)

        # Hidden terminals: Active nodes that CAN reach the sink but CANNOT hear node 'i'
        hidden = (~in_range) & active_mask & can_reach_sink
        hidden[i] = False
        hidden_terminals[i] = np.sum(hidden)

    return density, hidden_terminals


def _segments_intersect(p1, p2, p3, p4):
    """Check if line segment p1-p2 intersects segment p3-p4 using cross products."""
    def cross(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

    d1 = cross(p3, p4, p1)
    d2 = cross(p3, p4, p2)
    d3 = cross(p1, p2, p3)
    d4 = cross(p1, p2, p4)

    if ((d1 > 0 and d2 < 0) or (d1 < 0 and d2 > 0)) and \
       ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)):
        return True

    # Collinear cases (treat as non-intersecting for simplicity)
    return False


def check_obstacle_intersection(node, sink):
    """
    Checks if the line-of-sight from node to sink crosses a virtual wall.
    The wall is a line segment from (40, 20) to (40, 80).
    Uses proper line-segment intersection test.
    """
    wall_start = (40.0, 20.0)
    wall_end = (40.0, 80.0)

    node_pt = (float(node[0]), float(node[1]))
    sink_pt = (float(sink[0][0]), float(sink[0][1]))

    return _segments_intersect(node_pt, sink_pt, wall_start, wall_end)


def path_loss_db(nodes, sink, distances, rng):
    d_safe = np.maximum(distances, 0.1)
    pl_d0 = 20 * np.log10(4 * np.pi * D0 / WAVELENGTH)
    pl = pl_d0 + 10 * PATH_LOSS_EXP * np.log10(d_safe / D0)

    # Add obstacle penalty (the hidden variable)
    for i in range(len(nodes)):
        if check_obstacle_intersection(nodes[i], sink):
            pl[i] += OBSTACLE_PENALTY_DB

    shadowing = rng.normal(0, SHADOWING_STD, size=len(distances))
    return pl + shadowing


def ieee802154_ber(snr_db):
    """
    IEEE 802.15.4 O-QPSK BER with DSSS processing gain.

    O-QPSK has the same BER as BPSK: BER = 0.5 * erfc(sqrt(Eb/N0)).
    For 802.15.4 at 2.4 GHz, DSSS spreading provides a processing gain of 8
    (chip rate 2 Mcps / data rate 250 kbps), so Eb/N0 = SNR * 8.

    This produces the correct transitional region around -10 to 0 dB SNR,
    consistent with Zuniga & Krishnamachari (IEEE SECON 2004).
    """
    snr_linear = 10 ** (snr_db / 10.0)
    snr_linear = np.maximum(snr_linear, 1e-10)

    # DSSS processing gain: spreading factor = chip_rate / data_rate = 2e6 / 250e3 = 8
    spreading_gain = 8.0
    eb_n0 = snr_linear * spreading_gain

    ber = 0.5 * erfc(np.sqrt(eb_n0))
    return np.clip(ber, 0.0, 0.5)


def csma_collision_probability(n_contenders):
    """
    p-persistent CSMA/CA collision probability for IEEE 802.15.4 (unslotted).
    Uses the average backoff window size across backoff stages.

    With macMinBE=3 (W=8) as initial window, collision probability
    for a single transmission attempt among n contenders:
        p_coll = 1 - (1 - 1/W)^(n-1)

    We average over backoff stages for a more realistic estimate.
    """
    n_contenders = np.asarray(n_contenders, dtype=float)
    n_safe = np.maximum(n_contenders, 1.0)

    # Average backoff window across stages (macMinBE=3 to macMaxBE=5)
    avg_window = np.mean([2 ** be for be in range(MAC_MIN_BE, MAC_MAX_BE + 1)])
    tau = 1.0 / avg_window  # Transmission probability per slot

    p_coll = 1.0 - (1.0 - tau) ** (n_safe - 1.0)
    return np.clip(p_coll, 0.0, 1.0)


def detection_accuracy_calc(snr_db, local_density, hidden_terminals, n_packets, rng):
    # PHY layer: IEEE 802.15.4 O-QPSK BER (Zuniga-Krishnamachari)
    ber = ieee802154_ber(snr_db)
    per = 1.0 - (1.0 - ber) ** FRAME_LENGTH_BITS
    p_success_phy = np.clip(1.0 - per, 0, 1)

    # MAC layer: p-persistent CSMA collision model
    p_collision_standard = csma_collision_probability(local_density)
    p_collision_hidden = csma_collision_probability(hidden_terminals)

    p_success_total = p_success_phy * (1.0 - p_collision_standard) * (1.0 - p_collision_hidden)

    packets_received = np.array([
        rng.binomial(n_packets, max(0, min(1, p))) for p in p_success_total
    ])
    accuracy = packets_received / n_packets
    return packets_received, accuracy


def run_simulation():
    rng = np.random.default_rng(RANDOM_SEED)
    print("=" * 60)
    print("Running IEEE 802.15.4 WSN Simulation (Hidden States)...")
    print("PHY: O-QPSK/DSSS BER (Zuniga-Krishnamachari)")
    print("MAC: p-persistent CSMA/CA (macMinBE=3, macMaxBE=5)")
    print(f"Deployments per config: {NUM_DEPLOYMENTS}")
    print("=" * 60)

    n_time_windows = int(SIM_DURATION_S / TIME_WINDOW_S)
    timestamps = [(i + 1) * TIME_WINDOW_S for i in range(n_time_windows)]

    output_path = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                               '..', '..', 'data', 'raw', 'wsn_dataset.csv')
    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    # Config_ID enables GroupKFold during training (prevents temporal leakage)
    # X and Y coordinates are INTENTIONALLY left out.
    headers = [
        'Config_ID', 'Node_ID', 'Timestamp_s', 'Num_Nodes',
        'Transmission_Power_dBm', 'Distance_to_Sink_m',
        'Local_Density', 'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
        'Initial_Energy_J', 'Residual_Energy_J',
        'Packets_Sent', 'Packets_Received', 'PRR'
    ]

    row_count = 0
    config_id = 0

    with open(output_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(headers)

        for n_nodes, tx_power, noise_floor, init_energy in itertools.product(
            NODE_COUNTS, TX_POWERS_DBM, NOISE_FLOORS_DBM, INITIAL_ENERGIES_J
        ):
            for deploy_idx in range(NUM_DEPLOYMENTS):
                nodes, sink = place_nodes(n_nodes, rng)
                distances = compute_distances(nodes, sink)

                cumulative_energy_used = np.zeros(n_nodes)
                residual_energy = np.full(n_nodes, init_energy)

                for t_idx, timestamp in enumerate(timestamps):
                    active_mask = residual_energy > 0

                    local_density, hidden_terminals = compute_local_density_and_hidden(
                        nodes, sink, active_mask, INTERFERENCE_RANGE_M, tx_power
                    )

                    actual_tx_power = np.full(n_nodes, float(tx_power))
                    droop_mask = (residual_energy < VOLTAGE_DROOP_THRESHOLD_J) & active_mask
                    actual_tx_power[droop_mask] -= 5.0 * (1.0 - residual_energy[droop_mask])

                    pl_db = path_loss_db(nodes, sink, distances, rng)
                    rssi = np.clip(actual_tx_power - pl_db, RSSI_MIN_DBM, RSSI_MAX_DBM)
                    snr = rssi - noise_floor

                    pkts_received = np.zeros(n_nodes)
                    accuracy = np.zeros(n_nodes)

                    if np.any(active_mask):
                        p_rx, acc = detection_accuracy_calc(
                            snr[active_mask], local_density[active_mask],
                            hidden_terminals[active_mask], PACKETS_PER_WINDOW, rng
                        )
                        pkts_received[active_mask] = p_rx
                        accuracy[active_mask] = acc

                    window_energy = np.zeros(n_nodes)
                    for i in range(n_nodes):
                        if not active_mask[i]:
                            continue
                        closest_base = min(TX_CURRENT_MAP.keys(),
                                           key=lambda k: abs(k - actual_tx_power[i]))
                        tx_current = TX_CURRENT_MAP[closest_base]

                        e_tx = SUPPLY_VOLTAGE * tx_current * TX_DURATION_S * PACKETS_PER_WINDOW
                        e_rx = SUPPLY_VOLTAGE * RX_CURRENT_A * RX_DURATION_S * pkts_received[i]
                        active_time = (PACKETS_PER_WINDOW * TX_DURATION_S +
                                       pkts_received[i] * RX_DURATION_S)
                        e_idle = SUPPLY_VOLTAGE * IDLE_CURRENT_A * max(
                            TIME_WINDOW_S - active_time, 0)

                        window_energy[i] = e_tx + e_rx + e_idle

                    cumulative_energy_used += window_energy
                    residual_energy = np.maximum(init_energy - cumulative_energy_used, 0)

                    for i in range(n_nodes):
                        packets_sent = PACKETS_PER_WINDOW if active_mask[i] else 0
                        writer.writerow([
                            config_id, i, round(timestamp, 1), n_nodes,
                            round(actual_tx_power[i], 2), round(distances[i], 2),
                            int(local_density[i]), round(rssi[i], 2), noise_floor,
                            round(snr[i], 2), init_energy, round(residual_energy[i], 6),
                            packets_sent, int(pkts_received[i]), round(accuracy[i], 4)
                        ])
                        row_count += 1

                config_id += 1

    print(f"Done! Generated {row_count:,} rows across {config_id} configurations.")
    print(f"Dataset saved to: {output_path}")


if __name__ == '__main__':
    run_simulation()
