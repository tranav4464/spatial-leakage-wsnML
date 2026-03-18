"""
Cross-Site Validation
======================
Trains on one FIT IoT-LAB site, tests on the other.
The ultimate test of spatial generalization: if models learn site-specific
RF fingerprints, cross-site R² will be even worse than within-site LOGO.

Requires:
  - data/processed/testbed_dataset.csv (Grenoble)
  - data/processed/testbed_dataset_lille.csv (Lille)

Output: data/processed/cross_site_results.json
"""
import os
import json
import csv
import numpy as np
from sklearn.metrics import r2_score, mean_squared_error
from sklearn.model_selection import LeaveOneGroupOut
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')

GRENOBLE_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')
LILLE_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset_lille.csv')

FEATURE_COLS = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def load_site_data(path, site_name):
    """Load a site's dataset, return X, y, groups."""
    X_data, y_data, groups_data = [], [], []
    with open(path) as f:
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

    n_good = (y > 0.9).sum()
    n_trans = ((y >= 0.1) & (y <= 0.9)).sum()
    print(f"  {site_name}: {len(y):,} samples, {len(unique_groups)} dst_nodes, "
          f"Good={100*n_good/len(y):.1f}%, Trans={100*n_trans/len(y):.1f}%")

    return X, y, groups_int, unique_groups


def eval_predictions(y_true, y_pred):
    """Compute metrics."""
    y_pred_c = np.clip(y_pred, 0, 1)
    r2 = float(r2_score(y_true, y_pred_c))
    rmse = float(np.sqrt(mean_squared_error(y_true, y_pred_c)))
    mae = float(np.mean(np.abs(y_true - y_pred_c)))

    good_mask = y_true > 0.9
    trans_mask = (y_true >= 0.1) & (y_true <= 0.9)

    result = {
        'r2': round(r2, 4),
        'rmse': round(rmse, 4),
        'mae': round(mae, 4),
        'n_samples': int(len(y_true)),
    }

    if good_mask.sum() > 0:
        result['mae_good'] = round(float(np.mean(np.abs(y_true[good_mask] - y_pred_c[good_mask]))), 4)
    if trans_mask.sum() > 10:
        result['trans_r2'] = round(float(r2_score(y_true[trans_mask], y_pred_c[trans_mask])), 4)
        result['mae_trans'] = round(float(np.mean(np.abs(y_true[trans_mask] - y_pred_c[trans_mask]))), 4)
        result['trans_n'] = int(trans_mask.sum())

    return result


def run_logo_on_site(X, y, groups, site_name):
    """Run LOGO CV on a single site (for within-site comparison).

    Reports mean-of-fold R² (consistent with testbed_validation.py)
    and aggregate R² on pooled predictions for comparison.
    """
    logo = LeaveOneGroupOut()
    n_folds = len(np.unique(groups))

    models = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
        'linreg': lambda: LinearRegression(),
    }

    all_preds = {name: np.zeros(len(y)) for name in models}
    per_fold_r2 = {name: [] for name in models}

    for fold, (train_idx, test_idx) in enumerate(logo.split(X, y, groups)):
        for name, model_fn in models.items():
            model = model_fn()
            model.fit(X[train_idx], y[train_idx])
            preds = model.predict(X[test_idx])
            all_preds[name][test_idx] = preds
            fold_r2 = float(r2_score(y[test_idx], np.clip(preds, 0, 1)))
            per_fold_r2[name].append(fold_r2)

    results = {}
    for name in models:
        agg = eval_predictions(y, all_preds[name])
        fold_r2_arr = np.array(per_fold_r2[name])
        agg['r2_mean_of_folds'] = round(float(np.mean(fold_r2_arr)), 4)
        agg['r2_std_of_folds'] = round(float(np.std(fold_r2_arr)), 4)
        agg['r2_aggregate'] = agg.pop('r2')
        agg['r2'] = agg['r2_mean_of_folds']
        results[name] = agg

    print(f"\n  {site_name} LOGO ({n_folds} folds):")
    for name, r in results.items():
        print(f"    {name:10s}: R²(mean-of-fold)={r['r2']:.4f}  "
              f"R²(aggregate)={r['r2_aggregate']:.4f}  "
              f"Trans-R²={r.get('trans_r2', 'N/A')}")

    return results


def run_cross_site(X_train, y_train, X_test, y_test, direction):
    """Train on one site, test on the other."""
    models = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
        'linreg': lambda: LinearRegression(),
    }

    results = {}
    print(f"\n  {direction}:")
    for name, model_fn in models.items():
        model = model_fn()
        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)
        results[name] = eval_predictions(y_test, y_pred)
        print(f"    {name:10s}: R²={results[name]['r2']:.4f}  "
              f"Trans-R²={results[name].get('trans_r2', 'N/A')}")

    return results


def main():
    print("=" * 60)
    print("CROSS-SITE VALIDATION")
    print("=" * 60)

    if not os.path.exists(GRENOBLE_PATH):
        print(f"ERROR: {GRENOBLE_PATH} not found.")
        return
    if not os.path.exists(LILLE_PATH):
        print(f"ERROR: {LILLE_PATH} not found.")
        print("Run the Lille experiment first:")
        print("  python scripts/run_full_experiment.py --site lille")
        print("  python src/data/process_testbed.py --site lille")
        return

    print("\nLoading datasets...")
    X_g, y_g, groups_g, _ = load_site_data(GRENOBLE_PATH, "Grenoble")
    X_l, y_l, groups_l, _ = load_site_data(LILLE_PATH, "Lille")

    all_results = {}

    # Within-site LOGO for comparison
    print("\n" + "=" * 60)
    print("WITHIN-SITE LOGO CV")
    print("=" * 60)
    all_results['grenoble_logo'] = run_logo_on_site(X_g, y_g, groups_g, "Grenoble")
    all_results['lille_logo'] = run_logo_on_site(X_l, y_l, groups_l, "Lille")

    # Cross-site
    print("\n" + "=" * 60)
    print("CROSS-SITE TRAIN/TEST")
    print("=" * 60)
    all_results['train_grenoble_test_lille'] = run_cross_site(
        X_g, y_g, X_l, y_l, "Train Grenoble -> Test Lille")
    all_results['train_lille_test_grenoble'] = run_cross_site(
        X_l, y_l, X_g, y_g, "Train Lille -> Test Grenoble")

    # Save
    output = {
        'description': (
            'Cross-site validation: within-site LOGO and cross-site train/test '
            'between Grenoble and Lille FIT IoT-LAB sites.'
        ),
        'features': FEATURE_COLS,
        'target': TARGET_COL,
        'grenoble_n_samples': int(len(y_g)),
        'lille_n_samples': int(len(y_l)),
    }
    output.update(all_results)

    out_path = os.path.join(PROCESSED_DIR, 'cross_site_results.json')
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nSaved: {out_path}")


if __name__ == '__main__':
    main()
