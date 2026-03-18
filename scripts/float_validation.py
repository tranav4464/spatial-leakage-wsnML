"""
Float32 vs Float64 Prediction Validation
==========================================
Validates the manuscript claim that float32 vs float64 produces
delta R^2 < 0.001 on the testbed XGBoost model.

Output: data/processed/float_validation.json
"""
import os
import json
import csv
import numpy as np
from sklearn.model_selection import GroupKFold
from sklearn.metrics import r2_score
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
DATASET_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')

FEATURE_COLS = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def main():
    print("=" * 60)
    print("FLOAT32 vs FLOAT64 PREDICTION VALIDATION")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found.")
        return

    # Load data
    X_data, y_data, groups_data = [], [], []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            X_data.append([float(row[c]) for c in FEATURE_COLS])
            y_data.append(float(row[TARGET_COL]))
            groups_data.append(row[GROUP_COL])

    X = np.array(X_data, dtype=np.float64)
    y = np.array(y_data, dtype=np.float64)
    groups = np.array(groups_data)
    unique_groups = np.unique(groups)
    group_map = {g: i for i, g in enumerate(unique_groups)}
    groups_int = np.array([group_map[g] for g in groups])

    print(f"Loaded {len(y):,} samples")

    gkf = GroupKFold(n_splits=5)
    results_64, results_32 = [], []
    max_abs_diff = 0.0

    for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups_int)):
        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        # Train at float64
        model = xgb.XGBRegressor(**XGB_PARAMS)
        model.fit(X_train, y_train)

        # Predict at float64
        pred_64 = np.clip(model.predict(X_test), 0, 1)
        r2_64 = r2_score(y_test, pred_64)

        # Predict at float32 (cast features to float32)
        X_test_32 = X_test.astype(np.float32)
        pred_32 = np.clip(model.predict(X_test_32), 0, 1)
        r2_32 = r2_score(y_test, pred_32)

        delta = abs(r2_64 - r2_32)
        max_abs_diff = max(max_abs_diff, delta)

        results_64.append(r2_64)
        results_32.append(r2_32)
        print(f"  Fold {fold + 1}: R^2_64={r2_64:.6f}, R^2_32={r2_32:.6f}, "
              f"delta={delta:.6f}")

    mean_64 = np.mean(results_64)
    mean_32 = np.mean(results_32)
    mean_delta = abs(mean_64 - mean_32)

    print(f"\n  Mean R^2 (float64): {mean_64:.6f}")
    print(f"  Mean R^2 (float32): {mean_32:.6f}")
    print(f"  Mean delta:         {mean_delta:.6f}")
    print(f"  Max per-fold delta: {max_abs_diff:.6f}")
    print(f"  Claim 'delta < 0.001': {'CONFIRMED' if mean_delta < 0.001 else 'VIOLATED'}")

    out = {
        'float64_r2_mean': round(mean_64, 6),
        'float32_r2_mean': round(mean_32, 6),
        'delta_r2_mean': round(mean_delta, 6),
        'max_fold_delta': round(max_abs_diff, 6),
        'claim_confirmed': bool(mean_delta < 0.001),
        'per_fold_64': [round(v, 6) for v in results_64],
        'per_fold_32': [round(v, 6) for v in results_32],
    }

    out_path = os.path.join(PROCESSED_DIR, 'float_validation.json')
    with open(out_path, 'w') as f:
        json.dump(out, f, indent=2)
    print(f"\nSaved: {out_path}")


if __name__ == '__main__':
    main()
