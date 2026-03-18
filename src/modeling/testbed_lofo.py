"""
Testbed Leave-One-Feature-Out (LOFO) Analysis
===============================================
Mirrors the simulation LOFO (Figure 2) but on the physical testbed dataset.
For each of the 4 testbed features, trains XGBoost and CART d3 with 3 features
(dropping one) and reports the R^2 change vs the full-feature baseline.

Key hypothesis: LQI removal causes near-zero R^2 drop (confirming saturation).

Output: data/processed/testbed_lofo.json
"""
import os
import json
import csv
import numpy as np
from sklearn.model_selection import GroupKFold
from sklearn.metrics import r2_score
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
DATASET_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')

FEATURE_COLS = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def load_testbed_data():
    """Load testbed CSV and return X, y, groups."""
    X_data, y_data, groups_data = [], [], []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            X_data.append([float(row[c]) for c in FEATURE_COLS])
            y_data.append(float(row[TARGET_COL]))
            groups_data.append(row[GROUP_COL])
    X = np.array(X_data)
    y = np.array(y_data)
    groups = np.array(groups_data)
    unique_groups = np.unique(groups)
    group_map = {g: i for i, g in enumerate(unique_groups)}
    groups_int = np.array([group_map[g] for g in groups])
    return X, y, groups_int


def cv_r2(X, y, groups, model_fn, n_splits=5):
    """Run GroupKFold CV and return per-fold R^2 list."""
    gkf = GroupKFold(n_splits=n_splits)
    r2s = []
    for train_idx, test_idx in gkf.split(X, y, groups):
        model = model_fn()
        model.fit(X[train_idx], y[train_idx])
        y_pred = np.clip(model.predict(X[test_idx]), 0, 1)
        r2s.append(r2_score(y[test_idx], y_pred))
    return r2s


def main():
    print("=" * 60)
    print("TESTBED LOFO (Leave-One-Feature-Out) ANALYSIS")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found. Run process_testbed.py first.")
        return

    X, y, groups = load_testbed_data()
    print(f"Loaded {len(y):,} samples, {X.shape[1]} features")

    models = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
    }

    results = {}

    for model_name, model_fn in models.items():
        print(f"\n--- {model_name} ---")

        # Baseline: all features
        baseline_r2s = cv_r2(X, y, groups, model_fn)
        baseline_mean = np.mean(baseline_r2s)
        print(f"  Baseline (all 4 features): R^2 = {baseline_mean:.4f}")

        model_results = {
            'baseline_r2_mean': round(baseline_mean, 4),
            'baseline_r2_std': round(float(np.std(baseline_r2s)), 4),
            'baseline_per_fold': [round(v, 4) for v in baseline_r2s],
            'features_dropped': {},
        }

        # LOFO: drop each feature
        for feat_idx, feat_name in enumerate(FEATURE_COLS):
            keep_idx = [i for i in range(len(FEATURE_COLS)) if i != feat_idx]
            X_reduced = X[:, keep_idx]
            lofo_r2s = cv_r2(X_reduced, y, groups, model_fn)
            lofo_mean = np.mean(lofo_r2s)
            delta = baseline_mean - lofo_mean

            model_results['features_dropped'][feat_name] = {
                'r2_mean': round(lofo_mean, 4),
                'r2_std': round(float(np.std(lofo_r2s)), 4),
                'delta_r2': round(delta, 4),
                'pct_drop': round(delta / max(abs(baseline_mean), 1e-10) * 100, 1),
                'per_fold': [round(v, 4) for v in lofo_r2s],
            }
            print(f"  Drop {feat_name:15s}: R^2 = {lofo_mean:.4f} "
                  f"(delta = {delta:+.4f}, {delta / max(abs(baseline_mean), 1e-10) * 100:+.1f}%)")

        results[model_name] = model_results

    # Save
    out_path = os.path.join(PROCESSED_DIR, 'testbed_lofo.json')
    with open(out_path, 'w') as f:
        json.dump(results, f, indent=2)
    print(f"\nSaved: {out_path}")


if __name__ == '__main__':
    main()
