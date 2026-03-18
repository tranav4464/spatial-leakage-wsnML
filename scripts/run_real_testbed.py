#!/usr/bin/env python3
"""
FIT IoT-LAB Serial-Based Experiment Runner
==========================================
Collects real hardware testbed data using serial_aggregator.
"""
import os
import sys
import time
import json
import re
import csv
import paramiko
import argparse
import getpass
import subprocess

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
RAW_DIR = os.path.join(ROOT_DIR, 'data', 'raw')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')

def banner(text):
    print(f"\n{'='*60}\n  {text}\n{'='*60}")

def ssh_exec(client, cmd, timeout=30):
    stdin, stdout, stderr = client.exec_command(cmd, timeout=timeout)
    out = stdout.read().decode('utf-8', errors='ignore')
    err = stderr.read().decode('utf-8', errors='ignore')
    rc = stdout.channel.recv_exit_status()
    return out, err, rc

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--user', default='varshney')
    parser.add_argument('--password', default=None)
    parser.add_argument('--nodes', type=int, default=50)
    parser.add_argument('--duration', type=int, default=15)
    args = parser.parse_args()

    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    
    password = args.password or getpass.getpass(f'IoT-LAB password for {args.user}: ')
    print(f"Connecting to grenoble.iot-lab.info as {args.user}...")
    client.connect('grenoble.iot-lab.info', username=args.user, password=password)
    
    banner("Stopping Old Experiments")
    out, err, rc = ssh_exec(client, 'iotlab-experiment get -l --state Running')
    running = []
    if rc == 0:
        try:
            data = json.loads(out)
            running = data.get('items', [])
        except (json.JSONDecodeError, KeyError, TypeError):
            pass
    for exp in running:
        exp_id = exp.get('id')
        print(f"Stopping {exp_id}...")
        ssh_exec(client, f'iotlab-experiment stop -i {exp_id}')

    banner("Submitting New Experiment")
    firmware = "~/lqe_broadcast/bin/iotlab-m3/lqe_broadcast.elf"
    duration_s = args.duration * 60
    cmd = f'iotlab-experiment submit -n lqe_serial -d {duration_s} -l {args.nodes},archi=m3:at86rf231+site=grenoble,{firmware}'
    out, err, rc = ssh_exec(client, cmd)
    
    try:
        resp = json.loads(out)
        exp_id = resp['id']
    except (json.JSONDecodeError, KeyError):
        match = re.search(r'"id"\s*:\s*(\d+)', out)
        exp_id = int(match.group(1)) if match else None
        
    if not exp_id:
        print("Failed to submit:", err, out)
        return 1
        
    print(f"Experiment ID: {exp_id}")
    
    print("Waiting for experiment to start...")
    for _ in range(60):
        out, _, _ = ssh_exec(client, f'iotlab-experiment get -i {exp_id} -s')
        if '"Running"' in out:
            print("Experiment is RUNNING!")
            break
        time.sleep(10)
    else:
        print("Experiment failed to start.")
        return 1

    banner("Collecting Data via Node Logs")
    # Wait for nodes to boot and transmit for 60 seconds
    time.sleep(60)
    
    remote_csv = "/senslab/users/varshney/iotlab_radio.csv"
    
    parse_script = """
import os
import csv
import time

log_dir = "/senslab/users/varshney/.iot-lab/last/log/"
csv_path = "/senslab/users/varshney/iotlab_radio.csv"
records = []

if not os.path.exists(log_dir):
    print("No log dir")
else:
    for fname in os.listdir(log_dir):
        if not fname.endswith('.log'): continue
        rx_node = fname.replace('_', '-').replace('.log', '')
        with open(os.path.join(log_dir, fname), 'r', errors='ignore') as f:
            for line in f:
                parts = line.strip().split(';')
                if 'RX;' in line and 'LQE:' in line:
                    try:
                        idx = parts.index('RX') if 'RX' in parts else -1
                        if idx == -1:
                            for i, p in enumerate(parts):
                                if 'RX' in p: idx = i; break
                        if idx != -1 and len(parts) >= idx + 4:
                            payload = parts[idx+1]
                            rssi = int(parts[idx+2])
                            lqi = int(parts[idx+3])
                            
                            p_parts = payload.split(':')
                            if len(p_parts) == 3:
                                src_addr_hex = p_parts[1]
                                seq_num = int(p_parts[2])
                                tx_node = f"0x{src_addr_hex}"
                                records.append([time.time(), tx_node, rx_node, rssi, lqi, seq_num, 11])
                    except (ValueError, IndexError, TypeError):
                        pass

with open(csv_path, 'w') as f:
    w = csv.writer(f)
    w.writerow(['timestamp', 'src_node', 'dst_node', 'rssi', 'lqi', 'seq_num', 'channel'])
    w.writerows(records)

print(f"Parsed {len(records)} records remotely.")
"""
    ssh_exec(client, f"cat << 'EOF' > /senslab/users/varshney/parse_logs.py\n{parse_script}\nEOF")
    out, err, rc = ssh_exec(client, "python3 /senslab/users/varshney/parse_logs.py")
    print(out)
    
    sftp = client.open_sftp()
    csv_path = os.path.join(RAW_DIR, "iotlab_radio.csv")
    try:
        sftp.get(remote_csv, csv_path)
        print(f"Downloaded CSV to {csv_path}")
    except Exception as e:
        print(f"Failed to download CSV: {e}")

    
    # We also need coordinates for these nodes. Fetching...
    fetch_script = os.path.join(ROOT_DIR, 'src', 'data', 'fetch_testbed.py')
    subprocess.run([sys.executable, fetch_script], cwd=ROOT_DIR)
    
    print("\nDONE. Run `python src/data/process_testbed.py` and then validation.")
    return 0

if __name__ == '__main__':
    sys.exit(main())