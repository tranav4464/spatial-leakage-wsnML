"""
Distance Memorization Interaction Experiment
==============================================
Tests whether Distance is the primary spatial leakage vector by running
a 2x2 experiment: {with Distance, without Distance} x {naive KFold, LOGO}.

If Distance enables spatial memorization, then:
  - Naive KFold with Distance should inflate R² substantially
  - LOGO with Distance should penalize (negative R²)
  - The leakage delta (naive - LOGO) should collapse when Distance is removed

Output: data/processed/distance_interaction.json
"""
import os
import json
import csv
import numpy as np
from sklearn.model_selection import KFold, LeaveOneGroupOut
from sklearn.metrics import r2_score
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
DATASET_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')

FULL_FEATURES = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
NO_DISTANCE = ['RSSI_mean', 'LQI_mean', 'Local_Density']
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def load_data():
    """Load testbed dataset."""
    rows = []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            rows.append(row)

    X_full = np.array([[float(r[c]) for c in FULL_FEATURES] for r in rows])
    X_nodist = np.array([[float(r[c]) for c in NO_DISTANCE] for r in rows])
    y = np.array([float(r[TARGET_COL]) for r in rows])

    unique_groups = sorted(set(r[GROUP_COL] for r in rows))
    group_map = {g: i for i, g in enumerate(unique_groups)}
    groups = np.array([group_map[r[GROUP_COL]] for r in rows])

    print(f"Loaded {len(y):,} samples, {len(unique_groups)} groups")
    return X_full, X_nodist, y, groups


def run_naive_kfold(X, y, model_fn, n_splits=5, seed=42):
    """Run naive KFold (shuffled, no grouping)."""
    kf = KFold(n_splits=n_splits, shuffle=True, random_state=seed)
    fold_r2 = []
    for train_idx, test_idx in kf.split(X):
        model = model_fn()
        model.fit(X[train_idx], y[train_idx])
        pred = np.clip(model.predict(X[test_idx]), 0, 1)
        fold_r2.append(float(r2_score(y[test_idx], pred)))
    return fold_r2


def run_logo(X, y, groups, model_fn):
    """Run Leave-One-Group-Out CV."""
    logo = LeaveOneGroupOut()
    fold_r2 = []
    for train_idx, test_idx in logo.split(X, y, groups):
        model = model_fn()
        model.fit(X[train_idx], y[train_idx])
        pred = np.clip(model.predict(X[test_idx]), 0, 1)
        fold_r2.append(float(r2_score(y[test_idx], pred)))
    return fold_r2


def main():
    print("=" * 60)
    print("DISTANCE MEMORIZATION INTERACTION EXPERIMENT")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found.")
        return

    X_full, X_nodist, y, groups = load_data()

    model_defs = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d6': lambda: DecisionTreeRegressor(max_depth=6, random_state=42),
    }

    results = {}

    for model_name, model_fn in model_defs.items():
        print(f"\n--- {model_name} ---")

        # 2x2: {with_distance, no_distance} x {naive, LOGO}
        print("  Naive KFold + full features...")
        naive_full = run_naive_kfold(X_full, y, model_fn)
        print("  Naive KFold + no Distance...")
        naive_nodist = run_naive_kfold(X_nodist, y, model_fn)
        print("  LOGO + full features...")
        logo_full = run_logo(X_full, y, groups, model_fn)
        print("  LOGO + no Distance...")
        logo_nodist = run_logo(X_nodist, y, groups, model_fn)

        naive_full_mean = float(np.mean(naive_full))
        naive_nodist_mean = float(np.mean(naive_nodist))
        logo_full_mean = float(np.mean(logo_full))
        logo_nodist_mean = float(np.mean(logo_nodist))

        leakage_with_dist = naive_full_mean - logo_full_mean
        leakage_no_dist = naive_nodist_mean - logo_nodist_mean

        results[model_name] = {
            'naive_full': round(naive_full_mean, 4),
            'naive_nodist': round(naive_nodist_mean, 4),
            'logo_full': round(logo_full_mean, 4),
            'logo_nodist': round(logo_nodist_mean, 4),
            'leakage_with_distance': round(leakage_with_dist, 4),
            'leakage_without_distance': round(leakage_no_dist, 4),
            'leakage_reduction': round(leakage_with_dist - leakage_no_dist, 4),
        }

        print(f"  With Distance:    naive={naive_full_mean:+.4f}  LOGO={logo_full_mean:+.4f}  leakage={leakage_with_dist:+.4f}")
        print(f"  Without Distance: naive={naive_nodist_mean:+.4f}  LOGO={logo_nodist_mean:+.4f}  leakage={leakage_no_dist:+.4f}")
        print(f"  --> Leakage reduction when Distance removed: {leakage_with_dist - leakage_no_dist:+.4f}")

    # Save
    output = {
        'description': (
            'Distance memorization interaction: 2x2 experiment testing '
            '{with Distance, no Distance} x {naive KFold, LOGO}. '
            'If Distance is the leakage vector, leakage delta should '
            'collapse when Distance is removed.'
        ),
        'full_features': FULL_FEATURES,
        'no_distance_features': NO_DISTANCE,
        'results': results,
    }

    out_path = os.path.join(PROCESSED_DIR, 'distance_interaction.json')
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nSaved: {out_path}")


if __name__ == '__main__':
    main()
