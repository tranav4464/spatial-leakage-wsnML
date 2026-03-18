"""
Grouping Comparison: Spatial Leakage Robustness
================================================
Tests whether the negative R² finding under LOGO CV is robust across
different spatial grouping strategies:

  1. LOGO by dst_node (baseline — 49 folds, one per receiver)
  2. LOGO by src_node (49 folds, one per transmitter)
  3. GroupKFold by link_id (10 folds, grouped by src-dst pair, 1005 links)

Models: XGBoost and CART d3.

Output: data/processed/grouping_comparison.json
"""
import os
import json
import csv
import numpy as np
from sklearn.model_selection import LeaveOneGroupOut, GroupKFold
from sklearn.metrics import r2_score, mean_squared_error
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
DATASET_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')
os.makedirs(PROCESSED_DIR, exist_ok=True)

FEATURE_COLS = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
TARGET_COL = 'PRR'

RNG = np.random.default_rng(42)

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def load_testbed_data():
    """Load testbed CSV and return X, y, dst_nodes, src_nodes, link_ids."""
    X_data, y_data = [], []
    dst_nodes, src_nodes, link_ids = [], [], []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            X_data.append([float(row[c]) for c in FEATURE_COLS])
            y_data.append(float(row[TARGET_COL]))
            dst_nodes.append(row['dst_node'])
            src_nodes.append(row['src_node'])
            link_ids.append(row['src_node'] + '_' + row['dst_node'])
    return (np.array(X_data), np.array(y_data),
            np.array(dst_nodes), np.array(src_nodes), np.array(link_ids))


def encode_groups(groups):
    """Encode string group labels to integers."""
    unique = np.unique(groups)
    mapping = {g: i for i, g in enumerate(unique)}
    return np.array([mapping[g] for g in groups]), len(unique)


def run_cv(X, y, groups_int, cv_obj, cv_name, n_groups):
    """Run CV for XGBoost and CART d3, return results dict."""
    print(f"\n  --- {cv_name} ({n_groups} groups) ---")

    model_defs = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
    }

    metric_keys = ['r2', 'rmse', 'mae', 'trans_r2', 'trans_rmse', 'trans_n']
    metrics = {name: {k: [] for k in metric_keys} for name in model_defs}

    folds = list(cv_obj.split(X, y, groups_int))
    n_folds = len(folds)

    for fold_idx, (train_idx, test_idx) in enumerate(folds):
        if fold_idx % 10 == 0:
            print(f"    Fold {fold_idx+1}/{n_folds}...")

        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        trans_mask = (y_test >= 0.1) & (y_test <= 0.9)

        for model_name, model_fn in model_defs.items():
            model = model_fn()
            model.fit(X_train, y_train)
            y_pred = np.clip(model.predict(X_test), 0, 1)

            metrics[model_name]['r2'].append(r2_score(y_test, y_pred))
            metrics[model_name]['rmse'].append(
                float(np.sqrt(mean_squared_error(y_test, y_pred))))
            metrics[model_name]['mae'].append(
                float(np.mean(np.abs(y_test - y_pred))))

            if trans_mask.sum() > 10:
                metrics[model_name]['trans_r2'].append(
                    r2_score(y_test[trans_mask], y_pred[trans_mask]))
                metrics[model_name]['trans_rmse'].append(
                    float(np.sqrt(mean_squared_error(
                        y_test[trans_mask], y_pred[trans_mask]))))
            else:
                metrics[model_name]['trans_r2'].append(float('nan'))
                metrics[model_name]['trans_rmse'].append(float('nan'))
            metrics[model_name]['trans_n'].append(int(trans_mask.sum()))

    # Summarize
    results = {'n_folds': n_folds, 'n_groups': n_groups}
    for model_name in model_defs:
        m = metrics[model_name]
        trans_r2_valid = [v for v in m['trans_r2'] if not np.isnan(v)]
        entry = {
            'r2_mean': round(float(np.mean(m['r2'])), 4),
            'r2_std': round(float(np.std(m['r2'])), 4),
            'rmse_mean': round(float(np.mean(m['rmse'])), 4),
            'mae_mean': round(float(np.mean(m['mae'])), 4),
            'per_fold_r2': [round(float(v), 4) for v in m['r2']],
        }
        if trans_r2_valid:
            entry['trans_r2_mean'] = round(float(np.mean(trans_r2_valid)), 4)
            entry['trans_r2_std'] = round(float(np.std(trans_r2_valid)), 4)
            entry['trans_n_mean'] = int(np.mean(m['trans_n']))
        results[model_name] = entry

        print(f"    {model_name:10s}: R²={entry['r2_mean']:.4f}±{entry['r2_std']:.4f}"
              f"  Trans-R²={entry.get('trans_r2_mean', float('nan')):.4f}")

    return results


def main():
    print("=" * 60)
    print("GROUPING COMPARISON: SPATIAL LEAKAGE ROBUSTNESS")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found.")
        return

    X, y, dst_nodes, src_nodes, link_ids = load_testbed_data()
    print(f"Loaded {len(y):,} samples, {X.shape[1]} features")

    dst_int, n_dst = encode_groups(dst_nodes)
    src_int, n_src = encode_groups(src_nodes)
    link_int, n_links = encode_groups(link_ids)

    print(f"Unique dst_nodes: {n_dst}, src_nodes: {n_src}, links: {n_links}")

    groupings = {}

    # 1. LOGO by dst_node (baseline)
    groupings['dst_node_logo'] = run_cv(
        X, y, dst_int, LeaveOneGroupOut(),
        "LOGO by dst_node (baseline)", n_dst)

    # 2. LOGO by src_node
    groupings['src_node_logo'] = run_cv(
        X, y, src_int, LeaveOneGroupOut(),
        "LOGO by src_node", n_src)

    # 3. GroupKFold by link_id (10 folds)
    groupings['link_id_gkf10'] = run_cv(
        X, y, link_int, GroupKFold(n_splits=10),
        "GroupKFold by link_id (10 folds)", n_links)

    # --- Save ---
    output = {
        'description': (
            'Grouping comparison: tests spatial leakage robustness across '
            'dst_node LOGO (49 folds), src_node LOGO (49 folds), and '
            'link_id GroupKFold (10 folds, 1005 links). '
            'Models: XGBoost and CART d3.'
        ),
        'features': FEATURE_COLS,
        'target': TARGET_COL,
        'n_samples': int(len(y)),
        'groupings': groupings,
    }

    out_path = os.path.join(PROCESSED_DIR, 'grouping_comparison.json')
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nSaved: {out_path}")

    # --- Summary table ---
    print("\n" + "=" * 60)
    print("SUMMARY")
    print("=" * 60)
    print(f"\n  {'Grouping':<20} {'Folds':>6} {'XGB R²':>10} {'CART d3 R²':>12}")
    print("  " + "-" * 50)
    for gname, gdata in groupings.items():
        xgb_r2 = gdata['xgboost']['r2_mean']
        cart_r2 = gdata['cart_d3']['r2_mean']
        n_folds = gdata['n_folds']
        print(f"  {gname:<20} {n_folds:>6} {xgb_r2:>10.4f} {cart_r2:>12.4f}")


if __name__ == '__main__':
    main()
