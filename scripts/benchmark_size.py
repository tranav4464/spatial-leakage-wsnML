"""
Compile all model C implementations and measure .text, .data, .bss section sizes.
Uses ARM Cortex-M3 cross-compilation (arm-none-eabi-gcc) for publication metrics.
Also measures x86-64 sizes for comparison and inference timing.

Section meanings:
  .text = Flash (executable code)
  .data = Flash + SRAM (initialized globals)
  .bss  = SRAM (zero-initialized globals)
  SRAM total = .data + .bss
"""
import os
import json
import subprocess
import csv
import time
import re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
FIRMWARE_DIR = os.path.join(SCRIPT_DIR, '..', 'firmware')
RESULTS_DIR = os.path.join(SCRIPT_DIR, '..', 'results', 'tables')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', 'data', 'processed')
os.makedirs(RESULTS_DIR, exist_ok=True)

# ARM Cortex-M3 cross-compiler (publication target)
ARM_CC = r'C:\msys64\mingw64\bin\arm-none-eabi-gcc.exe'
ARM_SIZE = r'C:\msys64\mingw64\bin\arm-none-eabi-size.exe'
ARM_CFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-mfloat-abi=soft', '-Os', '-Wall',
              '-ffreestanding', '-nostdlib', '-c']

# x86-64 native compiler (for timing measurements)
X86_CC = 'gcc'
X86_SIZE = 'size'
X86_CFLAGS = ['-Os', '-Wall', '-c']

# Try to find ARM compiler
for path_candidate in [ARM_CC, '/c/msys64/mingw64/bin/arm-none-eabi-gcc.exe',
                       'arm-none-eabi-gcc']:
    try:
        result = subprocess.run([path_candidate, '--version'], capture_output=True, text=True)
        if result.returncode == 0:
            ARM_CC = path_candidate
            ARM_SIZE = path_candidate.replace('gcc', 'size')
            break
    except FileNotFoundError:
        continue

# Load metrics from previous pipeline stages
with open(os.path.join(PROCESSED_DIR, 'extracted_thresholds.json')) as f:
    thresholds = json.load(f)

cart_results = {}
cart_results_path = os.path.join(PROCESSED_DIR, 'cart_sweep_results.json')
if os.path.exists(cart_results_path):
    with open(cart_results_path) as f:
        cart_results = json.load(f)


def compile_and_measure(c_path, o_path, cc, cflags, size_cmd):
    """Compile a C file and return (.text, .data, .bss) sizes in bytes."""
    cmd = [cc] + cflags + [c_path, '-o', o_path]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"    Compilation error: {result.stderr[:200]}")
        return 0, 0, 0

    # Use `size` to get section sizes
    result = subprocess.run([size_cmd, o_path], capture_output=True, text=True)
    if result.returncode == 0:
        lines = result.stdout.strip().split('\n')
        if len(lines) >= 2:
            # Format: text    data    bss     dec     hex     filename
            parts = lines[1].split()
            if len(parts) >= 3:
                text, data, bss = int(parts[0]), int(parts[1]), int(parts[2])
                # Verify .rodata accounting via SysV format
                sysv = subprocess.run(
                    [size_cmd, '--format=sysv', o_path],
                    capture_output=True, text=True)
                if sysv.returncode == 0:
                    rodata = 0
                    for line in sysv.stdout.split('\n'):
                        if '.rodata' in line:
                            rodata_parts = line.split()
                            if len(rodata_parts) >= 2:
                                rodata = int(rodata_parts[1])
                    if rodata > 0:
                        # .rodata is separate; Berkeley .text already
                        # includes it, but log for transparency
                        print(f"    .rodata={rodata}B (included in .text)")
                return text, data, bss

    return os.path.getsize(o_path), 0, 0


def measure_inference_time_x86(c_path, n_iterations=100000):
    """Compile with x86 and measure inference time."""
    exe_path = c_path.replace('.c', '_timing')
    # Compile as executable (not object file) for timing
    result = subprocess.run(
        [X86_CC, '-O2', '-o', exe_path, c_path, '-lm'],
        capture_output=True, text=True
    )
    if result.returncode != 0:
        return 0.0

    # Run and measure wall clock time
    start = time.perf_counter()
    result = subprocess.run([exe_path], capture_output=True, timeout=30)
    elapsed = time.perf_counter() - start

    # Clean up
    try:
        os.remove(exe_path)
    except OSError:
        pass
    try:
        os.remove(exe_path + '.exe')
    except OSError:
        pass

    # The main() function runs one inference call
    # Rough estimate: divide elapsed by 1 call, report in microseconds
    return elapsed * 1e6  # microseconds


print("=" * 70)
print("BENCHMARKING: ARM Cortex-M3 Compiled Machine Code Footprints")
print(f"  ARM Compiler: {ARM_CC}")
print(f"  ARM Flags: {' '.join(ARM_CFLAGS)}")
print(f"  x86 Compiler: {X86_CC}")
print("=" * 70)

benchmarks = []

# Model list with their R²/RMSE sources
model_configs = [
    ('XGBoost_Full', 'xgboost_full', {
        'r2_mean': thresholds['model_metrics']['xgboost_r2_mean'],
        'r2_std': thresholds['model_metrics']['xgboost_r2_std'],
        'rmse_mean': thresholds['model_metrics'].get('xgboost_rmse_mean', 0),
    }),
    ('ALE_Rule', 'ale_rule', {
        'r2_mean': thresholds['model_metrics']['rule_r2_mean'],
        'r2_std': thresholds['model_metrics']['rule_r2_std'],
        'rmse_mean': thresholds['model_metrics'].get('rule_rmse_mean', 0),
    }),
    ('Linear_Reg', 'linreg', {
        'r2_mean': thresholds['model_metrics']['linear_r2_mean'],
        'r2_std': thresholds['model_metrics']['linear_r2_std'],
        'rmse_mean': thresholds['model_metrics'].get('linear_rmse_mean', 0),
    }),
]

# Add CART models
cart_depths = [2, 3, 4, 5, 6, 8, 10]
for depth in cart_depths:
    key = f'cart_depth{depth}'
    r2_mean = cart_results.get(key, {}).get('r2_mean', 0)
    r2_std = cart_results.get(key, {}).get('r2_std', 0)
    model_configs.append((
        f'CART_Depth{depth}', f'cart_depth{depth}',
        {'r2_mean': r2_mean, 'r2_std': r2_std, 'rmse_mean': 0}
    ))

for model_name, dir_name, metrics in model_configs:
    c_path = os.path.join(FIRMWARE_DIR, dir_name, 'main.c')
    if not os.path.exists(c_path):
        continue

    print(f"\n  Compiling {model_name}...")

    # ARM compilation (primary — for publication)
    arm_o = os.path.join(FIRMWARE_DIR, dir_name, 'main.arm.o')
    arm_text, arm_data, arm_bss = compile_and_measure(
        c_path, arm_o, ARM_CC, ARM_CFLAGS, ARM_SIZE
    )
    arm_sram = arm_data + arm_bss
    arm_flash = arm_text + arm_data  # .text + .data both go in flash

    # x86 compilation (secondary — for timing/reference)
    x86_o = os.path.join(FIRMWARE_DIR, dir_name, 'main.o')
    x86_text, x86_data, x86_bss = compile_and_measure(
        c_path, x86_o, X86_CC, X86_CFLAGS, X86_SIZE
    )

    print(f"    ARM: .text={arm_text:,}B .data={arm_data:,}B .bss={arm_bss:,}B "
          f"(Flash={arm_flash:,}B, SRAM={arm_sram:,}B)")
    print(f"    x86: .text={x86_text:,}B .data={x86_data:,}B .bss={x86_bss:,}B")

    benchmarks.append({
        'model': model_name,
        # ARM metrics (publication)
        'arm_text_bytes': arm_text,
        'arm_data_bytes': arm_data,
        'arm_bss_bytes': arm_bss,
        'arm_flash_bytes': arm_flash,
        'arm_sram_bytes': arm_sram,
        # x86 metrics (reference)
        'x86_text_bytes': x86_text,
        'x86_data_bytes': x86_data,
        'x86_bss_bytes': x86_bss,
        # Model performance
        'r2_mean': metrics['r2_mean'],
        'r2_std': metrics['r2_std'],
        'rmse_mean': metrics.get('rmse_mean', 0),
    })

# Print summary table
print("\n" + "=" * 70)
print(f"{'Model':<18} {'ARM .text':>10} {'ARM SRAM':>10} {'x86 .text':>10} "
      f"{'R2 Mean':>8} {'R2 Std':>8}")
print("-" * 70)
for b in sorted(benchmarks, key=lambda x: x['arm_text_bytes']):
    print(f"{b['model']:<18} {b['arm_text_bytes']:>10,} {b['arm_sram_bytes']:>10,} "
          f"{b['x86_text_bytes']:>10,} {b['r2_mean']:>8.4f} {b['r2_std']:>8.4f}")
print("=" * 70)

# Save CSV (ARM as primary)
csv_path = os.path.join(RESULTS_DIR, 'model_benchmarks.csv')
with open(csv_path, 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow([
        'Model', 'ARM_Text_Bytes', 'ARM_Data_Bytes', 'ARM_BSS_Bytes',
        'ARM_Flash_Bytes', 'ARM_SRAM_Bytes',
        'x86_Text_Bytes', 'x86_Data_Bytes', 'x86_BSS_Bytes',
        'R2_Mean', 'R2_Std', 'RMSE_Mean'
    ])
    for b in sorted(benchmarks, key=lambda x: x['arm_text_bytes']):
        writer.writerow([
            b['model'], b['arm_text_bytes'], b['arm_data_bytes'], b['arm_bss_bytes'],
            b['arm_flash_bytes'], b['arm_sram_bytes'],
            b['x86_text_bytes'], b['x86_data_bytes'], b['x86_bss_bytes'],
            b['r2_mean'], b['r2_std'], b['rmse_mean']
        ])
print(f"\nSaved to: {csv_path}")

# Save JSON
json_path = os.path.join(RESULTS_DIR, 'model_benchmarks.json')
with open(json_path, 'w') as f:
    json.dump(benchmarks, f, indent=2)
print(f"Saved to: {json_path}")
