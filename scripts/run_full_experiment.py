#!/usr/bin/env python3
"""
Full IoT-LAB experiment: 50 nodes, 15 min, serial-based data collection.
Uploads firmware, compiles, runs experiment, captures serial data,
parses to CSV, and runs local processing pipeline.
"""
import paramiko
import time
import os
import sys
import csv
import re
import json
import subprocess
import argparse
import getpass

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
FIRMWARE_DIR = os.path.join(ROOT_DIR, 'firmware', 'testbed_broadcast')
RAW_DIR = os.path.join(ROOT_DIR, 'data', 'raw')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')

# Parse arguments
_parser = argparse.ArgumentParser(description='Full IoT-LAB experiment pipeline')
_parser.add_argument('--site', default='grenoble', help='IoT-LAB site (grenoble, lille, etc.)')
_parser.add_argument('--user', default='varshney', help='IoT-LAB username')
_parser.add_argument('--password', default=None, help='IoT-LAB password')
_parser.add_argument('--nodes', type=int, default=50, help='Number of nodes')
_parser.add_argument('--duration', type=int, default=15, help='Experiment duration (minutes)')
_args = _parser.parse_args()

SITE_NAME = _args.site
SITE = f'{SITE_NAME}.iot-lab.info'
USER = _args.user
PASSWORD = _args.password or getpass.getpass(f'IoT-LAB password for {USER}: ')

N_NODES = _args.nodes
DURATION_MIN = _args.duration
SERIAL_COLLECT_S = 600  # 10 minutes of serial capture
CHANNEL = 11

# Site-specific file suffixes
_site_suffix = f'_{SITE_NAME}' if SITE_NAME != 'grenoble' else ''

def ssh_exec(client, cmd, timeout=120):
    """Execute command and return stdout, stderr."""
    print(f"    $ {cmd[:150]}")
    stdin, stdout, stderr = client.exec_command(cmd, timeout=timeout)
    out = stdout.read().decode('utf-8', errors='replace')
    err = stderr.read().decode('utf-8', errors='replace')
    lines = out.strip().split('\n') if out.strip() else []
    for line in lines[:15]:
        print(f"  {line}")
    if len(lines) > 15:
        print(f"  ... ({len(lines) - 15} more lines)")
    return out, err

def parse_serial_to_csv(serial_log_path, csv_path, nodes_json_path):
    """Parse serial_aggregator output to radio CSV.

    Serial format: timestamp;node_id;RX;LQE:SRC_ADDR:SEQ;RSSI;LQI
    """
    # Build addr -> node mapping from the serial log TX lines
    addr_to_node = {}
    records = []

    print(f"  Parsing {serial_log_path}...")

    with open(serial_log_path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or 'Aggregator' in line:
                continue

            parts = line.split(';')
            if len(parts) < 3:
                continue

            ts_str = parts[0]
            rx_node = parts[1]  # e.g., "m3-100"

            try:
                ts = float(ts_str)
            except ValueError:
                continue

            # TX line: timestamp;node;TX;LQE:ADDR:SEQ
            if parts[2] == 'TX' and len(parts) >= 4:
                tx_payload = parts[3]
                if tx_payload.startswith('LQE:'):
                    tx_parts = tx_payload.split(':')
                    if len(tx_parts) >= 2:
                        addr = tx_parts[1]
                        addr_to_node[addr] = rx_node

            # RX line: timestamp;node;RX;LQE:SRC_ADDR:SEQ;RSSI;LQI
            elif parts[2].startswith('RX') and len(parts) >= 6:
                payload = parts[3] if len(parts) > 3 else parts[2]
                # Handle case where RX and payload might be in same field
                if payload.startswith('RX;'):
                    payload = payload[3:]

                if not payload.startswith('LQE:'):
                    # Try field index 2 which might be "RX;LQE:..."
                    if parts[2].startswith('RX;LQE:'):
                        payload = parts[2][3:]
                    else:
                        continue

                lqe_parts = payload.split(':')
                if len(lqe_parts) < 3:
                    continue

                src_addr = lqe_parts[1]
                try:
                    seq = int(lqe_parts[2])
                except ValueError:
                    continue

                try:
                    rssi = int(parts[-2])
                    lqi = int(parts[-1])
                except (ValueError, IndexError):
                    continue

                # Map src_addr to node name
                src_node = addr_to_node.get(src_addr, f'addr-{src_addr}')

                records.append([
                    round(ts, 6), src_node, rx_node,
                    rssi, lqi, seq, CHANNEL
                ])

    # If we couldn't map some addresses, try to infer from the address
    # IoT-LAB M3 nodes use their node number as part of the short address
    unmapped = set()
    for r in records:
        if r[1].startswith('addr-'):
            unmapped.add(r[1])

    if unmapped:
        print(f"  Warning: {len(unmapped)} unmapped addresses: {list(unmapped)[:5]}")

    # Write CSV
    with open(csv_path, 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(['timestamp', 'src_node', 'dst_node', 'rssi', 'lqi', 'seq_num', 'channel'])
        w.writerows(records)

    print(f"  Parsed {len(records)} records")
    print(f"  Unique TX nodes: {len(set(r[1] for r in records))}")
    print(f"  Unique RX nodes: {len(set(r[2] for r in records))}")
    if records:
        rssis = [r[3] for r in records]
        print(f"  RSSI range: [{min(rssis)}, {max(rssis)}]")

    return len(records)


print("=" * 60)
print("  FULL IoT-LAB EXPERIMENT PIPELINE")
print("=" * 60)

os.makedirs(RAW_DIR, exist_ok=True)
os.makedirs(PROCESSED_DIR, exist_ok=True)

# Connect
print(f"\n  Connecting to {USER}@{SITE}...")
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(SITE, username=USER, password=PASSWORD)
sftp = client.open_sftp()
print("  Connected.")

# Step 1: Upload and compile firmware
print("\n" + "=" * 60)
print("  Step 1: Upload & Compile Firmware")
print("=" * 60)

ssh_exec(client, "mkdir -p ~/riot_broadcast")
sftp.put(os.path.join(FIRMWARE_DIR, 'main.c'), f'/senslab/users/{USER}/riot_broadcast/main.c')
sftp.put(os.path.join(FIRMWARE_DIR, 'Makefile'), f'/senslab/users/{USER}/riot_broadcast/Makefile')

compile_cmd = """
export PATH=/opt/gcc-arm-none-eabi-9-2020-q2-update/bin/:$PATH
source /opt/riot.iot-lab/riot-env.sh 2>/dev/null || true
cd ~/riot_broadcast
make clean all 2>&1
BUILD_RC=$?
echo "BUILD_EXIT_CODE=${BUILD_RC}"
"""
out, err = ssh_exec(client, compile_cmd, timeout=300)

if 'BUILD_EXIT_CODE=0' not in out:
    print("  COMPILATION FAILED!")
    print("  Error:", err[:500])
    client.close()
    sys.exit(1)

ssh_exec(client, """
export PATH=/opt/gcc-arm-none-eabi-9-2020-q2-update/bin/:$PATH
arm-none-eabi-size ~/riot_broadcast/bin/iotlab-m3/lqe_broadcast.elf
""")
ssh_exec(client, """
mkdir -p ~/lqe_broadcast/bin/iotlab-m3/
cp ~/riot_broadcast/bin/iotlab-m3/lqe_broadcast.elf ~/lqe_broadcast/bin/iotlab-m3/lqe_broadcast.elf
""")
print("  Firmware compiled successfully!")

# Step 2: Stop old experiments
print("\n" + "=" * 60)
print("  Step 2: Stop Running Experiments")
print("=" * 60)

out, _ = ssh_exec(client, "iotlab-experiment get -l --state Running 2>/dev/null || echo 'none'")
try:
    data = json.loads(out.strip())
    if 'items' in data:
        for item in data['items']:
            exp_id = item.get('id')
            if exp_id:
                print(f"  Stopping experiment {exp_id}...")
                ssh_exec(client, f"iotlab-experiment stop -i {exp_id}")
                time.sleep(2)
except (json.JSONDecodeError, KeyError):
    pass

# Step 3: Submit full experiment
print("\n" + "=" * 60)
print(f"  Step 3: Submit {N_NODES}-Node Experiment ({DURATION_MIN} min)")
print("=" * 60)

submit_cmd = (
    f"iotlab-experiment submit -n lqe_full -d {DURATION_MIN * 60} "
    f"-l {N_NODES},archi=m3:at86rf231+site={SITE_NAME},"
    f"~/lqe_broadcast/bin/iotlab-m3/lqe_broadcast.elf"
)
out, err = ssh_exec(client, submit_cmd)

try:
    exp_data = json.loads(out.strip())
    exp_id = exp_data['id']
    print(f"  Experiment ID: {exp_id}")
except (json.JSONDecodeError, KeyError):
    print("  Failed to submit experiment!")
    print("  Output:", out[:300])
    client.close()
    sys.exit(1)

# Wait for Running
print("  Waiting for experiment to start...")
for i in range(60):
    time.sleep(5)
    out, _ = ssh_exec(client, f"iotlab-experiment get -i {exp_id} -s 2>/dev/null")
    if '"Running"' in out:
        print("  Experiment is RUNNING!")
        break
    if '"Error"' in out or '"Terminated"' in out:
        print("  Experiment failed!")
        client.close()
        sys.exit(1)
else:
    print("  Timeout!")
    client.close()
    sys.exit(1)

# Get node list
out, _ = ssh_exec(client, f"iotlab-experiment get -i {exp_id} -n")
try:
    nodes_data = json.loads(out.strip())
    nodes = [item['network_address'].split('.')[0] for item in nodes_data['items']]
    print(f"  Total nodes: {len(nodes)}")
    print(f"  Sample: {nodes[:5]}...")
except (json.JSONDecodeError, KeyError):
    nodes = []
    print("  Could not parse node list")

# Step 4: Wait for stabilization then capture serial
print("\n" + "=" * 60)
print(f"  Step 4: Capture Serial Data ({SERIAL_COLLECT_S}s)")
print("=" * 60)

print("  Waiting 15s for nodes to stabilize...")
time.sleep(15)

# Reset all nodes
ssh_exec(client, f"iotlab-node -i {exp_id} --reset")
time.sleep(5)

# Capture serial data to remote file
remote_log = f"/senslab/users/{USER}/lqe_experiment/serial_{exp_id}.log"
ssh_exec(client, "mkdir -p ~/lqe_experiment")

print(f"  Running serial_aggregator for {SERIAL_COLLECT_S}s...")
print("  This will take ~10 minutes...")

serial_cmd = (
    f"timeout {SERIAL_COLLECT_S + 30} serial_aggregator -i {exp_id} "
    f"> {remote_log} 2>&1"
)
stdin, stdout, stderr = client.exec_command(serial_cmd, timeout=SERIAL_COLLECT_S + 60)

# Wait for completion
exit_status = stdout.channel.recv_exit_status()
print(f"  serial_aggregator exit code: {exit_status}")

# Check file size
out, _ = ssh_exec(client, f"wc -l {remote_log}")
out2, _ = ssh_exec(client, f"ls -lh {remote_log}")

# Show sample
out3, _ = ssh_exec(client, f"head -5 {remote_log}")
out4, _ = ssh_exec(client, f"tail -5 {remote_log}")

# Count RX and TX lines
out5, _ = ssh_exec(client, f"grep -c '^.*RX;LQE' {remote_log} || echo '0'")
rx_count = int(out5.strip()) if out5.strip().isdigit() else 0
out6, _ = ssh_exec(client, f"grep -c '^.*TX;LQE' {remote_log} || echo '0'")
tx_count = int(out6.strip()) if out6.strip().isdigit() else 0

print(f"\n  RX lines: {rx_count}")
print(f"  TX lines: {tx_count}")

if rx_count < 100:
    print("  WARNING: Very few RX lines!")

# Step 5: Download serial log
print("\n" + "=" * 60)
print("  Step 5: Download Data")
print("=" * 60)

local_log = os.path.join(RAW_DIR, f'iotlab_serial{_site_suffix}.log')
print(f"  Downloading serial log to {local_log}...")
sftp.get(remote_log, local_log)
print(f"  Downloaded: {os.path.getsize(local_log)} bytes")

# Step 6: Stop experiment
print(f"\n  Stopping experiment {exp_id}...")
ssh_exec(client, f"iotlab-experiment stop -i {exp_id}")

sftp.close()
client.close()
print("  SSH connection closed.")

# Step 7: Parse serial log to CSV
print("\n" + "=" * 60)
print("  Step 6: Parse Serial Log to CSV")
print("=" * 60)

csv_path = os.path.join(RAW_DIR, f'iotlab_radio{_site_suffix}.csv')
nodes_json = os.path.join(RAW_DIR, f'iotlab_nodes{_site_suffix}.json')
n_records = parse_serial_to_csv(local_log, csv_path, nodes_json)

if n_records < 100:
    print(f"  WARNING: Only {n_records} records. May be insufficient.")

# Step 8: Run processing pipeline
print("\n" + "=" * 60)
print("  Step 7: Process Testbed Data")
print("=" * 60)

_process_cmd = [sys.executable, os.path.join(SCRIPT_DIR, '..', 'src', 'data', 'process_testbed.py')]
if SITE_NAME != 'grenoble':
    _process_cmd += ['--site', SITE_NAME]
try:
    result = subprocess.run(
        _process_cmd,
        capture_output=True, text=True, timeout=120,
        cwd=ROOT_DIR
    )
    print(result.stdout[-1000:] if result.stdout else "  No stdout")
    if result.returncode != 0:
        print(f"  STDERR: {result.stderr[-500:]}")
except Exception as e:
    print(f"  Error: {e}")

# Check output
testbed_csv = os.path.join(PROCESSED_DIR, f'testbed_dataset{_site_suffix}.csv')
if os.path.exists(testbed_csv):
    with open(testbed_csv, 'r') as f:
        n_lines = sum(1 for _ in f) - 1  # subtract header
    print(f"  testbed_dataset.csv: {n_lines} records")
else:
    print("  testbed_dataset.csv NOT FOUND")

# Step 9: Run ML validation
print("\n" + "=" * 60)
print("  Step 8: ML Validation")
print("=" * 60)

try:
    result = subprocess.run(
        [sys.executable, os.path.join(SCRIPT_DIR, '..', 'src', 'modeling', 'testbed_validation.py')],
        capture_output=True, text=True, timeout=300,
        cwd=ROOT_DIR
    )
    print(result.stdout[-2000:] if result.stdout else "  No stdout")
    if result.returncode != 0:
        print(f"  STDERR: {result.stderr[-500:]}")
except Exception as e:
    print(f"  Error: {e}")

# Check results
results_json = os.path.join(PROCESSED_DIR, 'testbed_results.json')
if os.path.exists(results_json):
    with open(results_json, 'r') as f:
        results = json.load(f)
    print("\n  ML Results:")
    if 'models' in results:
        for name, metrics in results['models'].items():
            r2 = metrics.get('r2', metrics.get('R2', 'N/A'))
            print(f"    {name}: R2={r2}")
else:
    print("  testbed_results.json NOT FOUND")

print("\n" + "=" * 60)
print("  EXPERIMENT COMPLETE")
print("=" * 60)
