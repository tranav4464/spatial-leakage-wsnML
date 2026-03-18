"""
Temporal Baselines Experiment
==============================
Tests whether adding temporal features (lagged PRR, RSSI delta, EWMA)
improves model performance under LOGO CV.

Compares static models (original 4 features) against temporal models
(4 original + 3 temporal features) and a pure EWMA baseline.

Uses Leave-One-Group-Out CV (grouped by dst_node), matching testbed_validation.py.

Output: data/processed/temporal_baseline_results.json
"""
import os
import json
import csv
import numpy as np
from scipy.stats import wilcoxon
from sklearn.model_selection import LeaveOneGroupOut
from sklearn.metrics import r2_score, mean_squared_error
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.neural_network import MLPRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
DATASET_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')
os.makedirs(PROCESSED_DIR, exist_ok=True)

STATIC_FEATURES = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
TEMPORAL_FEATURES = ['PRR_lag1', 'RSSI_lag1', 'RSSI_delta']
ALL_FEATURES = STATIC_FEATURES + TEMPORAL_FEATURES
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'

EWMA_ALPHA = 0.5

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def load_and_enrich_dataset():
    """Load testbed CSV and add temporal features per link."""
    print("Loading dataset and computing temporal features...")

    # Load raw records
    rows = []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            rows.append(row)

    print(f"  Loaded {len(rows):,} records")

    # Sort by (src_node, dst_node, window_idx) for temporal ordering
    rows.sort(key=lambda r: (r['src_node'], r['dst_node'], int(r['window_idx'])))

    # Compute temporal features per link
    enriched = []
    prev = {}  # (src, dst) -> previous row's values
    ewma = {}  # (src, dst) -> running EWMA of PRR

    for row in rows:
        link = (row['src_node'], row['dst_node'])
        prr = float(row[TARGET_COL])
        rssi = float(row['RSSI_mean'])
        w_idx = int(row['window_idx'])

        if link in prev:
            prev_prr, prev_rssi, prev_w_idx = prev[link]
            # Only use lag if windows are consecutive or close
            if w_idx - prev_w_idx <= 2:
                row['PRR_lag1'] = prev_prr
                row['RSSI_lag1'] = prev_rssi
                row['RSSI_delta'] = rssi - prev_rssi
            else:
                row['PRR_lag1'] = None
                row['RSSI_lag1'] = None
                row['RSSI_delta'] = None

            # EWMA always updates regardless of gap
            if link in ewma:
                ewma[link] = EWMA_ALPHA * prev_prr + (1 - EWMA_ALPHA) * ewma[link]
            else:
                ewma[link] = prev_prr
            row['PRR_ewma'] = ewma[link]
        else:
            row['PRR_lag1'] = None
            row['RSSI_lag1'] = None
            row['RSSI_delta'] = None
            row['PRR_ewma'] = None

        prev[link] = (prr, rssi, w_idx)
        enriched.append(row)

    # Filter out records with missing temporal features
    valid = [r for r in enriched if r['PRR_lag1'] is not None and r['PRR_ewma'] is not None]
    dropped = len(enriched) - len(valid)
    print(f"  Valid records with temporal features: {len(valid):,} (dropped {dropped:,} first-window records)")

    # Build arrays
    X_static = np.array([[float(r[c]) for c in STATIC_FEATURES] for r in valid])
    X_temporal = np.array([[float(r[c]) for c in ALL_FEATURES] for r in valid])
    X_ewma = np.array([[float(r['PRR_ewma'])] for r in valid])
    y = np.array([float(r[TARGET_COL]) for r in valid])

    # Groups
    unique_groups = sorted(set(r[GROUP_COL] for r in valid))
    group_map = {g: i for i, g in enumerate(unique_groups)}
    groups = np.array([group_map[r[GROUP_COL]] for r in valid])

    print(f"  Groups: {len(unique_groups)}, Features: static={X_static.shape[1]}, temporal={X_temporal.shape[1]}")

    return X_static, X_temporal, X_ewma, y, groups, len(unique_groups)


def eval_fold(y_test, y_pred):
    """Compute full + transitional metrics for a single fold."""
    y_pred_clipped = np.clip(y_pred, 0, 1)
    r2 = r2_score(y_test, y_pred_clipped)
    rmse = float(np.sqrt(mean_squared_error(y_test, y_pred_clipped)))
    mae = float(np.mean(np.abs(y_test - y_pred_clipped)))

    # Stratified MAE
    good_mask = y_test > 0.9
    trans_mask = (y_test >= 0.1) & (y_test <= 0.9)

    mae_good = float(np.mean(np.abs(y_test[good_mask] - y_pred_clipped[good_mask]))) if good_mask.sum() > 0 else float('nan')
    mae_trans = float(np.mean(np.abs(y_test[trans_mask] - y_pred_clipped[trans_mask]))) if trans_mask.sum() > 0 else float('nan')

    if trans_mask.sum() > 10:
        t_r2 = r2_score(y_test[trans_mask], y_pred_clipped[trans_mask])
    else:
        t_r2 = float('nan')

    return {
        'r2': r2, 'rmse': rmse, 'mae': mae,
        'mae_good': mae_good, 'mae_trans': mae_trans,
        'trans_r2': t_r2,
        'trans_n': int(trans_mask.sum()),
    }


def run_models(X_dict, y, groups, n_groups):
    """Run all model configurations under LOGO CV."""
    logo = LeaveOneGroupOut()
    metric_keys = ['r2', 'rmse', 'mae', 'mae_good', 'mae_trans', 'trans_r2', 'trans_n']

    # Define all model+feature combinations
    configs = {
        # Static models (baseline)
        'xgboost_static': ('static', lambda: xgb.XGBRegressor(**XGB_PARAMS)),
        'cart_d3_static': ('static', lambda: DecisionTreeRegressor(max_depth=3, random_state=42)),
        'linreg_static': ('static', lambda: LinearRegression()),
        # Temporal models (with lag features)
        'xgboost_temporal': ('temporal', lambda: xgb.XGBRegressor(**XGB_PARAMS)),
        'cart_d3_temporal': ('temporal', lambda: DecisionTreeRegressor(max_depth=3, random_state=42)),
        'linreg_temporal': ('temporal', lambda: LinearRegression()),
        # MLP neural baseline (static + temporal)
        'mlp_static': ('static', lambda: MLPRegressor(
            hidden_layer_sizes=(64, 32), activation='relu', solver='adam',
            max_iter=500, random_state=42, early_stopping=True,
            validation_fraction=0.1)),
        'mlp_temporal': ('temporal', lambda: MLPRegressor(
            hidden_layer_sizes=(64, 32), activation='relu', solver='adam',
            max_iter=500, random_state=42, early_stopping=True,
            validation_fraction=0.1)),
    }

    metrics = {name: {k: [] for k in metric_keys} for name in configs}
    # EWMA baseline tracked separately
    metrics['ewma_baseline'] = {k: [] for k in metric_keys}

    print(f"\nRunning LOGO CV ({n_groups} folds)...")
    for fold, (train_idx, test_idx) in enumerate(logo.split(X_dict['static'], y, groups)):
        if fold % 10 == 0:
            print(f"  Fold {fold + 1}/{n_groups}...")

        y_train, y_test = y[train_idx], y[test_idx]

        # EWMA baseline: predict using PRR_ewma directly (no ML)
        y_pred_ewma = X_dict['ewma'][test_idx].ravel()
        fold_ewma = eval_fold(y_test, y_pred_ewma)
        for k in metric_keys:
            metrics['ewma_baseline'][k].append(fold_ewma[k])

        # ML models
        for config_name, (feat_key, model_fn) in configs.items():
            X = X_dict[feat_key]
            X_train, X_test = X[train_idx], X[test_idx]

            model = model_fn()
            model.fit(X_train, y_train)
            y_pred = model.predict(X_test)

            fold_metrics = eval_fold(y_test, y_pred)
            for k in metric_keys:
                metrics[config_name][k].append(fold_metrics[k])

    return metrics


def summarize(metrics):
    """Compute summary statistics from per-fold metrics."""
    results = {}
    for name, m in metrics.items():
        r2_vals = m['r2']
        trans_r2_vals = [v for v in m['trans_r2'] if not np.isnan(v)]
        mae_good_vals = [v for v in m['mae_good'] if not np.isnan(v)]
        mae_trans_vals = [v for v in m['mae_trans'] if not np.isnan(v)]

        entry = {
            'r2_mean': round(float(np.mean(r2_vals)), 4),
            'r2_std': round(float(np.std(r2_vals)), 4),
            'rmse_mean': round(float(np.mean(m['rmse'])), 4),
            'mae_mean': round(float(np.mean(m['mae'])), 4),
            'per_fold_r2': [round(float(v), 4) for v in r2_vals],
        }
        if mae_good_vals:
            entry['mae_good_mean'] = round(float(np.mean(mae_good_vals)), 4)
        if mae_trans_vals:
            entry['mae_trans_mean'] = round(float(np.mean(mae_trans_vals)), 4)
        if trans_r2_vals:
            entry['trans_r2_mean'] = round(float(np.mean(trans_r2_vals)), 4)
            entry['trans_r2_std'] = round(float(np.std(trans_r2_vals)), 4)
            entry['per_fold_trans_r2'] = [
                round(float(v), 4) if not np.isnan(v) else None
                for v in m['trans_r2']]

        results[name] = entry
        print(f"  {name:25s}: R²={entry['r2_mean']:.4f}±{entry['r2_std']:.4f}"
              f"  Trans-R²={entry.get('trans_r2_mean', float('nan')):.4f}"
              f"  MAE_G={entry.get('mae_good_mean', float('nan')):.4f}"
              f"  MAE_T={entry.get('mae_trans_mean', float('nan')):.4f}")

    return results


def wilcoxon_tests(metrics, results):
    """Wilcoxon tests: temporal vs static for each model."""
    print("\n" + "=" * 60)
    print("Wilcoxon Signed-Rank Tests: Temporal vs Static")
    print("=" * 60)

    pairs = [
        ('xgboost_temporal', 'xgboost_static'),
        ('cart_d3_temporal', 'cart_d3_static'),
        ('linreg_temporal', 'linreg_static'),
        ('mlp_temporal', 'mlp_static'),
        ('ewma_baseline', 'xgboost_static'),
        ('ewma_baseline', 'mlp_temporal'),
    ]

    wilcoxon_results = {}
    for temporal_name, static_name in pairs:
        key = f"{temporal_name}_vs_{static_name}"
        t_r2 = np.array(metrics[temporal_name]['r2'])
        s_r2 = np.array(metrics[static_name]['r2'])

        diff = float(np.mean(t_r2) - np.mean(s_r2))
        try:
            stat, pval = wilcoxon(t_r2, s_r2)
            pval_corrected = min(pval * len(pairs), 1.0)  # Bonferroni
            wilcoxon_results[key] = {
                'delta_r2': round(diff, 4),
                'p_value': round(float(pval), 6),
                'p_bonferroni': round(float(pval_corrected), 6),
                'significant': bool(pval_corrected < 0.05),
            }
        except ValueError as e:
            wilcoxon_results[key] = {'error': str(e), 'significant': False}

        sig = 'SIG' if wilcoxon_results[key].get('significant') else 'ns'
        print(f"  {key}: delta_R²={diff:+.4f} p={wilcoxon_results[key].get('p_bonferroni', 'N/A')} {sig}")

    return wilcoxon_results


def main():
    print("=" * 60)
    print("TEMPORAL BASELINES EXPERIMENT")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found.")
        return

    X_static, X_temporal, X_ewma, y, groups, n_groups = load_and_enrich_dataset()

    # Zone distribution
    n_good = (y > 0.9).sum()
    n_trans = ((y >= 0.1) & (y <= 0.9)).sum()
    n_bad = (y < 0.1).sum()
    print(f"Zone distribution: Good={n_good} ({100*n_good/len(y):.1f}%), "
          f"Trans={n_trans} ({100*n_trans/len(y):.1f}%), "
          f"Bad={n_bad} ({100*n_bad/len(y):.1f}%)")

    X_dict = {'static': X_static, 'temporal': X_temporal, 'ewma': X_ewma}

    metrics = run_models(X_dict, y, groups, n_groups)

    print("\n" + "=" * 60)
    print("RESULTS")
    print("=" * 60)
    results = summarize(metrics)

    wilcoxon_results = wilcoxon_tests(metrics, results)

    # Save
    output = {
        'description': (
            'Temporal baselines experiment comparing static (4 features) vs '
            'temporal (4 + PRR_lag1, RSSI_lag1, RSSI_delta) models and a pure '
            'EWMA baseline under LOGO CV grouped by dst_node.'
        ),
        'static_features': STATIC_FEATURES,
        'temporal_features': TEMPORAL_FEATURES,
        'ewma_alpha': EWMA_ALPHA,
        'target': TARGET_COL,
        'cv_protocol': f'LeaveOneGroupOut ({n_groups} folds) grouped by dst_node',
        'n_samples': int(len(y)),
        'zone_distribution': {
            'good_pct': round(100 * n_good / len(y), 1),
            'transitional_pct': round(100 * n_trans / len(y), 1),
            'bad_pct': round(100 * n_bad / len(y), 1),
        },
        'models': results,
        'wilcoxon_temporal_vs_static': wilcoxon_results,
    }

    out_path = os.path.join(PROCESSED_DIR, 'temporal_baseline_results.json')
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nSaved: {out_path}")

    # Interpretation
    print("\n" + "=" * 60)
    print("INTERPRETATION")
    print("=" * 60)
    for model in ['xgboost', 'cart_d3']:
        static_r2 = results[f'{model}_static']['r2_mean']
        temporal_r2 = results[f'{model}_temporal']['r2_mean']
        delta = temporal_r2 - static_r2
        print(f"\n  {model}:")
        print(f"    Static R²:   {static_r2:.4f}")
        print(f"    Temporal R²: {temporal_r2:.4f}")
        print(f"    Delta:       {delta:+.4f}")
        if temporal_r2 > 0:
            print(f"    --> TEMPORAL FEATURES RESCUE PREDICTION")
        elif delta > 0.5:
            print(f"    --> TEMPORAL FEATURES HELP SUBSTANTIALLY")
        elif delta > 0.1:
            print(f"    --> TEMPORAL FEATURES HELP MODERATELY")
        else:
            print(f"    --> TEMPORAL FEATURES DO NOT HELP (static failure confirmed)")

    ewma_r2 = results['ewma_baseline']['r2_mean']
    print(f"\n  EWMA baseline R²: {ewma_r2:.4f}")
    if ewma_r2 > 0:
        print(f"    --> PURE TEMPORAL PREDICTOR BEATS ML MODELS")
    else:
        print(f"    --> EVEN TEMPORAL PREDICTION FAILS UNDER LOGO")

    # ---- EWMA alpha sensitivity sweep ----
    print("\n" + "=" * 60)
    print("EWMA ALPHA SENSITIVITY SWEEP")
    print("=" * 60)

    alpha_sweep = ewma_alpha_sweep(y, groups, n_groups)
    output['ewma_alpha_sweep'] = alpha_sweep

    # Re-save with alpha sweep
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nRe-saved with alpha sweep: {out_path}")


def ewma_alpha_sweep(y, groups, n_groups):
    """Sweep EWMA alpha and report R² under LOGO CV for each."""
    logo = LeaveOneGroupOut()
    alphas = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]

    # We need to recompute EWMA for each alpha on the raw data
    rows = []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            rows.append(row)
    rows.sort(key=lambda r: (r['src_node'], r['dst_node'], int(r['window_idx'])))

    sweep_results = {}
    for alpha in alphas:
        # Recompute EWMA predictions for this alpha
        prev = {}
        ewma_state = {}
        records = []
        for row in rows:
            link = (row['src_node'], row['dst_node'])
            prr = float(row[TARGET_COL])
            if link in prev:
                prev_prr = prev[link]
                if link in ewma_state:
                    ewma_state[link] = alpha * prev_prr + (1 - alpha) * ewma_state[link]
                else:
                    ewma_state[link] = prev_prr
                records.append({
                    'prr': prr,
                    'ewma_pred': ewma_state[link],
                    'dst_node': row[GROUP_COL],
                })
            prev[link] = prr

        y_arr = np.array([r['prr'] for r in records])
        pred_arr = np.array([r['ewma_pred'] for r in records])
        unique_groups = sorted(set(r['dst_node'] for r in records))
        group_map = {g: i for i, g in enumerate(unique_groups)}
        g_arr = np.array([group_map[r['dst_node']] for r in records])

        fold_r2 = []
        for train_idx, test_idx in logo.split(pred_arr, y_arr, g_arr):
            r2 = r2_score(y_arr[test_idx], np.clip(pred_arr[test_idx], 0, 1))
            fold_r2.append(float(r2))

        r2_mean = round(float(np.mean(fold_r2)), 4)
        r2_std = round(float(np.std(fold_r2)), 4)
        sweep_results[str(alpha)] = {
            'r2_mean': r2_mean,
            'r2_std': r2_std,
        }
        print(f"  alpha={alpha:.1f}: R²={r2_mean:.4f} ± {r2_std:.4f}")

    return sweep_results


if __name__ == '__main__':
    main()
