#!/usr/bin/env python3
"""Upload fixed firmware, compile, deploy to 5 test nodes, check serial output."""
import paramiko
import time
import os
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
FIRMWARE_DIR = os.path.join(ROOT_DIR, 'firmware', 'testbed_broadcast')

USER = 'varshney'
PASSWORD = sys.argv[1] if len(sys.argv) > 1 else 'Computer@123'
SITE = 'grenoble.iot-lab.info'

def ssh_exec(client, cmd, timeout=120):
    """Execute command and return stdout, stderr."""
    print(f"    $ {cmd[:120]}")
    stdin, stdout, stderr = client.exec_command(cmd, timeout=timeout)
    out = stdout.read().decode('utf-8', errors='replace')
    err = stderr.read().decode('utf-8', errors='replace')
    if out.strip():
        # Show first 30 lines
        lines = out.strip().split('\n')
        for line in lines[:30]:
            print(f"  {line}")
        if len(lines) > 30:
            print(f"  ... ({len(lines) - 30} more lines)")
    return out, err

print("=" * 60)
print("  FIRMWARE TEST PIPELINE")
print("=" * 60)

# Connect
print(f"\n  Connecting to {USER}@{SITE}...")
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(SITE, username=USER, password=PASSWORD)
sftp = client.open_sftp()
print("  Connected.")

# Step 1: Upload firmware source files via SFTP
print("\n" + "=" * 60)
print("  Step 1: Upload Firmware via SFTP")
print("=" * 60)

ssh_exec(client, "mkdir -p ~/riot_broadcast")

# Upload main.c
local_main_c = os.path.join(FIRMWARE_DIR, 'main.c')
print(f"  Uploading {local_main_c}...")
sftp.put(local_main_c, '/senslab/users/varshney/riot_broadcast/main.c')

# Upload Makefile
local_makefile = os.path.join(FIRMWARE_DIR, 'Makefile')
print(f"  Uploading {local_makefile}...")
sftp.put(local_makefile, '/senslab/users/varshney/riot_broadcast/Makefile')

# Verify uploaded files
out, _ = ssh_exec(client, "cat ~/riot_broadcast/main.c | head -5")
out, _ = ssh_exec(client, "cat ~/riot_broadcast/Makefile")

# Step 2: Compile
print("\n" + "=" * 60)
print("  Step 2: Compile Firmware")
print("=" * 60)

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
    print("\n  COMPILATION FAILED!")
    print("  STDERR:", err[:500])
    # Show more output for debugging
    compile_cmd2 = """
export PATH=/opt/gcc-arm-none-eabi-9-2020-q2-update/bin/:$PATH
source /opt/riot.iot-lab/riot-env.sh 2>/dev/null || true
cd ~/riot_broadcast
make clean all 2>&1 | grep -i error | head -20
"""
    out2, _ = ssh_exec(client, compile_cmd2, timeout=300)
    client.close()
    sys.exit(1)

# Check binary size
out, _ = ssh_exec(client, """
export PATH=/opt/gcc-arm-none-eabi-9-2020-q2-update/bin/:$PATH
arm-none-eabi-size ~/riot_broadcast/bin/iotlab-m3/lqe_broadcast.elf
""")

# Copy to expected location
ssh_exec(client, """
mkdir -p ~/lqe_broadcast/bin/iotlab-m3/
cp ~/riot_broadcast/bin/iotlab-m3/lqe_broadcast.elf ~/lqe_broadcast/bin/iotlab-m3/lqe_broadcast.elf
""")

print("  Firmware compiled successfully!")

# Step 3: Stop old experiments
print("\n" + "=" * 60)
print("  Step 3: Stop Running Experiments")
print("=" * 60)

out, _ = ssh_exec(client, "iotlab-experiment get -l --state Running 2>/dev/null || echo 'none'")
# Try to extract running experiment IDs
import json as json_mod
try:
    data = json_mod.loads(out.strip())
    if 'items' in data:
        for item in data['items']:
            exp_id = item.get('id')
            if exp_id:
                print(f"  Stopping experiment {exp_id}...")
                ssh_exec(client, f"iotlab-experiment stop -i {exp_id}")
except:
    print("  No running experiments found.")

# Step 4: Submit small test experiment
print("\n" + "=" * 60)
print("  Step 4: Submit 5-Node Test Experiment")
print("=" * 60)

submit_cmd = (
    "iotlab-experiment submit -n lqe_test -d 300 "
    "-l 5,archi=m3:at86rf231+site=grenoble,"
    "~/lqe_broadcast/bin/iotlab-m3/lqe_broadcast.elf"
)
out, err = ssh_exec(client, submit_cmd)

try:
    exp_data = json_mod.loads(out.strip())
    exp_id = exp_data['id']
    print(f"  Experiment ID: {exp_id}")
except:
    print("  Failed to parse experiment ID!")
    print("  Output:", out[:200])
    print("  Error:", err[:200])
    client.close()
    sys.exit(1)

# Wait for Running state
print("  Waiting for experiment to start...")
for i in range(30):
    time.sleep(5)
    out, _ = ssh_exec(client, f"iotlab-experiment get -i {exp_id} -s 2>/dev/null")
    if '"Running"' in out:
        print("  Experiment is RUNNING!")
        break
    if '"Error"' in out or '"Terminated"' in out:
        print("  Experiment failed to start!")
        client.close()
        sys.exit(1)
else:
    print("  Timeout waiting for experiment!")
    client.close()
    sys.exit(1)

# Get node list
out, _ = ssh_exec(client, f"iotlab-experiment get -i {exp_id} -n")
try:
    nodes_data = json_mod.loads(out.strip())
    nodes = [item['network_address'].split('.')[0] for item in nodes_data['items']]
    print(f"  Nodes: {nodes}")
except:
    print("  Could not parse node list")

# Step 5: Wait for boot and capture serial output
print("\n" + "=" * 60)
print("  Step 5: Capture Serial Output (30 seconds)")
print("=" * 60)

print("  Waiting 10s for nodes to boot...")
time.sleep(10)

# Reset all nodes first
ssh_exec(client, f"iotlab-node -i {exp_id} --reset")
time.sleep(3)

# Capture serial output
print("  Running serial_aggregator for 30s...")
serial_cmd = f"timeout 35 serial_aggregator -i {exp_id} 2>&1 | head -200"
out, err = ssh_exec(client, serial_cmd, timeout=60)

serial_lines = out.strip().split('\n')
print(f"\n  Serial output: {len(serial_lines)} lines")

# Count meaningful lines
lqe_lines = [l for l in serial_lines if 'LQE' in l]
rx_lines = [l for l in serial_lines if 'RX;' in l]
tx_lines = [l for l in serial_lines if 'TX;' in l]
fault_lines = [l for l in serial_lines if 'FAULT' in l or 'panic' in l]

print(f"  LQE lines: {len(lqe_lines)}")
print(f"  RX lines: {len(rx_lines)}")
print(f"  TX lines: {len(tx_lines)}")
print(f"  FAULT/panic lines: {len(fault_lines)}")

if fault_lines:
    print("\n  WARNING: HARD FAULT detected!")
    for line in fault_lines[:5]:
        print(f"    {line}")

if len(lqe_lines) == 0 and len(serial_lines) < 5:
    print("\n  No meaningful serial output. Trying direct node access...")
    # Try connecting to individual nodes
    if nodes:
        node = nodes[0]
        print(f"  Trying nc {node} 20000 for 10s...")
        out2, _ = ssh_exec(client, f"timeout 10 nc {node} 20000 2>&1 || echo 'nc failed'", timeout=20)
        print(f"  NC output: {out2[:500]}")

# Step 6: Summary
print("\n" + "=" * 60)
print("  RESULT")
print("=" * 60)

if len(lqe_lines) > 0 and len(fault_lines) == 0:
    print("  SUCCESS: Firmware is working! Serial output detected.")
    print(f"  Ready to run full experiment with {len(lqe_lines)} LQE lines in 30s.")
else:
    print("  ISSUE: No LQE data or firmware crash detected.")
    print("  Serial output sample:")
    for line in serial_lines[:20]:
        print(f"    {line}")

# Stop the test experiment
print(f"\n  Stopping test experiment {exp_id}...")
ssh_exec(client, f"iotlab-experiment stop -i {exp_id}")

sftp.close()
client.close()
print("\n  Done.")
