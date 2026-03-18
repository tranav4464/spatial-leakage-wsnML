#!/usr/bin/env python3
"""
Lille IoT-LAB experiment: Uses pre-compiled firmware from Grenoble.
Connects to Lille frontend, copies ELF from Grenoble home dir (shared NFS),
submits experiment, captures serial data, and parses to CSV.
"""
import paramiko
import time
import os
import sys
import csv
import json
import subprocess

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
RAW_DIR = os.path.join(ROOT_DIR, 'data', 'raw')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')

USER = 'varshney'
PASSWORD = sys.argv[1] if len(sys.argv) > 1 else 'Computer@123'
SITE = 'lille.iot-lab.info'

N_NODES = 50
DURATION_MIN = 15
SERIAL_COLLECT_S = 600
CHANNEL = 11

# Firmware path (compiled on Grenoble, shared via NFS home dir)
ELF_PATH = '~/lqe_broadcast/bin/iotlab-m3/lqe_broadcast.elf'

os.makedirs(RAW_DIR, exist_ok=True)
os.makedirs(PROCESSED_DIR, exist_ok=True)


def ssh_exec(client, cmd, timeout=120):
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


def parse_serial_to_csv(serial_log_path, csv_path):
    """Parse serial_aggregator output to radio CSV."""
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
            rx_node = parts[1]

            try:
                ts = float(ts_str)
            except ValueError:
                continue

            if parts[2] == 'TX' and len(parts) >= 4:
                tx_payload = parts[3]
                if tx_payload.startswith('LQE:'):
                    tx_parts = tx_payload.split(':')
                    if len(tx_parts) >= 2:
                        addr_to_node[tx_parts[1]] = rx_node

            elif parts[2].startswith('RX') and len(parts) >= 6:
                payload = parts[3] if len(parts) > 3 else parts[2]
                if payload.startswith('RX;'):
                    payload = payload[3:]
                if not payload.startswith('LQE:'):
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

                src_node = addr_to_node.get(src_addr, f'addr-{src_addr}')
                records.append([round(ts, 6), src_node, rx_node, rssi, lqi, seq, CHANNEL])

    with open(csv_path, 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(['timestamp', 'src_node', 'dst_node', 'rssi', 'lqi', 'seq_num', 'channel'])
        w.writerows(records)

    print(f"  Parsed {len(records):,} records")
    print(f"  Unique TX nodes: {len(set(r[1] for r in records))}")
    print(f"  Unique RX nodes: {len(set(r[2] for r in records))}")
    return len(records)


print("=" * 60)
print("  LILLE IoT-LAB EXPERIMENT")
print("=" * 60)

# Connect to Lille
print(f"\n  Connecting to {USER}@{SITE}...")
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(SITE, username=USER, password=PASSWORD)
print("  Connected.")

# Check firmware exists (should be in NFS home dir from Grenoble compilation)
print("\n  Checking firmware...")
out, err = ssh_exec(client, f"ls -la {ELF_PATH}")
if 'No such file' in err or 'No such file' in out:
    print("  ERROR: Firmware ELF not found on server.")
    print("  Run the Grenoble experiment first to compile firmware.")
    client.close()
    sys.exit(1)
print("  Firmware found.")

# Stop old experiments
print("\n  Stopping old experiments...")
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

# Submit experiment
print(f"\n  Submitting {N_NODES}-node experiment at Lille ({DURATION_MIN} min)...")
submit_cmd = (
    f"iotlab-experiment submit -n lqe_lille -d {DURATION_MIN * 60} "
    f"-l {N_NODES},archi=m3:at86rf231+site=lille,"
    f"{ELF_PATH}"
)
out, err = ssh_exec(client, submit_cmd)

try:
    exp_data = json.loads(out.strip())
    exp_id = exp_data['id']
    print(f"  Experiment ID: {exp_id}")
except (json.JSONDecodeError, KeyError):
    print("  Failed to submit experiment!")
    print("  Output:", out[:300])
    print("  Error:", err[:300])
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

# Wait for stabilization + reset
print("\n  Waiting 15s for stabilization...")
time.sleep(15)
ssh_exec(client, f"iotlab-node -i {exp_id} --reset")
time.sleep(5)

# Capture serial data
remote_log = f"/senslab/users/{USER}/lqe_experiment/serial_lille_{exp_id}.log"
ssh_exec(client, "mkdir -p ~/lqe_experiment")

print(f"\n  Running serial_aggregator for {SERIAL_COLLECT_S}s...")
serial_cmd = (
    f"timeout {SERIAL_COLLECT_S + 30} serial_aggregator -i {exp_id} "
    f"> {remote_log} 2>&1"
)
stdin, stdout, stderr = client.exec_command(serial_cmd, timeout=SERIAL_COLLECT_S + 60)
exit_status = stdout.channel.recv_exit_status()
print(f"  serial_aggregator exit code: {exit_status}")

# Check file
out, _ = ssh_exec(client, f"wc -l {remote_log}")
out2, _ = ssh_exec(client, f"grep -c '^.*RX;LQE' {remote_log} || echo '0'")
rx_count = int(out2.strip()) if out2.strip().isdigit() else 0
print(f"  RX lines: {rx_count}")

# Download
local_log = os.path.join(RAW_DIR, 'iotlab_serial_lille.log')
print(f"\n  Downloading serial log...")
sftp = client.open_sftp()
sftp.get(remote_log, local_log)
print(f"  Downloaded: {os.path.getsize(local_log)} bytes")

# Stop experiment
ssh_exec(client, f"iotlab-experiment stop -i {exp_id}")
sftp.close()
client.close()
print("  SSH connection closed.")

# Parse to CSV
print("\n  Parsing serial log to CSV...")
csv_path = os.path.join(RAW_DIR, 'iotlab_radio_lille.csv')
n_records = parse_serial_to_csv(local_log, csv_path)

if n_records < 100:
    print(f"  WARNING: Only {n_records} records.")

# Process
print("\n  Processing Lille dataset...")
try:
    result = subprocess.run(
        [sys.executable, os.path.join(ROOT_DIR, 'src', 'data', 'process_testbed.py'),
         '--site', 'lille'],
        capture_output=True, text=True, timeout=120, cwd=ROOT_DIR
    )
    print(result.stdout[-1500:] if result.stdout else "  No stdout")
    if result.returncode != 0:
        print(f"  STDERR: {result.stderr[-500:]}")
except Exception as e:
    print(f"  Error: {e}")

# Check output
lille_csv = os.path.join(PROCESSED_DIR, 'testbed_dataset_lille.csv')
if os.path.exists(lille_csv):
    with open(lille_csv) as f:
        n_lines = sum(1 for _ in f) - 1
    print(f"\n  testbed_dataset_lille.csv: {n_lines} records")
else:
    print("\n  testbed_dataset_lille.csv NOT FOUND")

print("\n" + "=" * 60)
print("  LILLE EXPERIMENT COMPLETE")
print("  Next steps:")
print("    python src/modeling/testbed_validation.py --site lille")
print("    python src/modeling/cross_site_validation.py")
print("=" * 60)
