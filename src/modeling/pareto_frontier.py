"""
Pareto Frontier Analysis: Sweep model variants and collect (R2, compiled_size) pairs.
Trains pruned XGBoost ensembles at various tree counts and generates C code for each.
"""
import os
import json
import csv
import subprocess
import numpy as np
from sklearn.model_selection import GroupKFold
from sklearn.metrics import r2_score
import xgboost as xgb
import re
import m2cgen as m2c

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
FIRMWARE_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'firmware')
os.makedirs(PROCESSED_DIR, exist_ok=True)

RNG = np.random.default_rng(42)

FEATURE_COLS = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]

# Note: XGBoost with learning_rate=0.1 requires ~50+ trees to converge from
# default base_score=0.5. Ensembles with <50 trees produce severely biased
# predictions clustered near 0.5, yielding negative R² on bimodal targets.
# We include them for completeness but mark as "unconverged" in results.
N_ESTIMATORS_SWEEP = [5, 10, 25, 50, 75, 100, 150]


def find_arm_gcc():
    """Find the ARM cross-compiler."""
    for candidate in [r'C:\msys64\mingw64\bin\arm-none-eabi-gcc.exe',
                      '/c/msys64/mingw64/bin/arm-none-eabi-gcc.exe',
                      'arm-none-eabi-gcc']:
        try:
            result = subprocess.run([candidate, '--version'],
                                    capture_output=True, text=True)
            if result.returncode == 0:
                return candidate
        except FileNotFoundError:
            continue
    return 'gcc'  # fallback to native


ARM_CC = find_arm_gcc()
ARM_SIZE = ARM_CC.replace('gcc', 'size')
ARM_CFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-mfloat-abi=soft', '-Os', '-Wall',
              '-ffreestanding', '-nostdlib', '-c']


def compile_and_measure(c_path, o_path):
    """Compile for ARM Cortex-M3 and return .text section size."""
    if 'arm-none-eabi' in ARM_CC:
        cmd = [ARM_CC] + ARM_CFLAGS + [c_path, '-o', o_path]
        size_cmd = ARM_SIZE
    else:
        cmd = ['gcc', '-Os', '-Wall', '-c', c_path, '-o', o_path]
        size_cmd = 'size'

    subprocess.run(cmd, check=True)
    result = subprocess.run([size_cmd, o_path], capture_output=True, text=True)
    if result.returncode == 0:
        lines = result.stdout.strip().split('\n')
        if len(lines) >= 2:
            parts = lines[1].split()
            if parts:
                return int(parts[0])
    return os.path.getsize(o_path)


def main():
    print("=" * 60)
    print("PARETO FRONTIER: Pruned XGBoost Sweep")
    print("=" * 60)

    X_data, y_data, groups_data = [], [], []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if float(row['Residual_Energy_J']) > 0:
                X_data.append([float(row[c]) for c in FEATURE_COLS])
                y_data.append(float(row.get('PRR') or row.get('Detection_Accuracy')))
                groups_data.append(int(row['Config_ID']))

    X = np.array(X_data)
    y = np.array(y_data)
    groups = np.array(groups_data)

    if len(X) > 150000:
        idx = RNG.choice(len(X), 150000, replace=False)
        X, y, groups = X[idx], y[idx], groups[idx]

    print(f"  Dataset: {len(y):,} rows\n")

    gkf = GroupKFold(n_splits=5)
    results = {}

    for n_est in N_ESTIMATORS_SWEEP:
        print(f"  XGBoost n_estimators={n_est}:")
        params = {
            'n_estimators': n_est, 'max_depth': 6, 'learning_rate': 0.1,
            'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42,
            'n_jobs': -1
        }

        r2_scores = []
        for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups)):
            model = xgb.XGBRegressor(**params)
            model.fit(X[train_idx], y[train_idx])
            y_pred = model.predict(X[test_idx])
            r2_scores.append(r2_score(y[test_idx], y_pred))

        r2_mean = np.mean(r2_scores)
        r2_std = np.std(r2_scores)
        print(f"    R2 = {r2_mean:.4f} +/- {r2_std:.4f}")

        # Generate C code for size measurement
        final_model = xgb.XGBRegressor(**params)
        final_model.fit(X, y)

        c_code = m2c.export_to_c(final_model)
        c_code = re.sub(r'\bnan\b', 'NAN', c_code)
        # Convert double to float for ARM Cortex-M3 compatibility
        c_code = c_code.replace('double ', 'float ')
        c_code = c_code.replace('double\n', 'float\n')

        c_full = f"""#include <math.h>
{c_code}
volatile float result;
int main(void) {{
    float input[8] = {{-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f}};
    result = score(input);
    return 0;
}}
"""
        model_dir = os.path.join(FIRMWARE_DIR, f'xgb_n{n_est}')
        os.makedirs(model_dir, exist_ok=True)
        c_path = os.path.join(model_dir, 'main.c')
        o_path = os.path.join(model_dir, 'main.o')
        with open(c_path, 'w') as f:
            f.write(c_full)

        try:
            text_size = compile_and_measure(c_path, o_path)
            print(f"    .text = {text_size:,} bytes")
        except Exception as e:
            print(f"    Compilation failed: {e}")
            text_size = 0

        converged = bool(r2_mean > 0.0)
        results[f'xgb_n{n_est}'] = {
            'n_estimators': n_est,
            'r2_mean': round(r2_mean, 4),
            'r2_std': round(r2_std, 4),
            'text_size': text_size,
            'per_fold_r2': [round(v, 4) for v in r2_scores],
            'converged': converged,
        }
        if not converged:
            print(f"    WARNING: Unconverged (R2<0). XGBoost with learning_rate=0.1 "
                  f"needs more trees to escape base_score bias.")

    out_path = os.path.join(PROCESSED_DIR, 'pareto_xgb_sweep.json')
    with open(out_path, 'w') as f:
        json.dump(results, f, indent=2)
    print(f"\n  Results saved to: {out_path}")


if __name__ == '__main__':
    main()
