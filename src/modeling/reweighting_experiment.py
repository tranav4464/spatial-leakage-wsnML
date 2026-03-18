"""
Reweighting Experiment: Class Imbalance Analysis
=================================================
Tests whether the negative Trans-R² under LOGO CV is caused by the 76%
PRR=1.0 class imbalance rather than fundamental feature insufficiency.

Three experiments on the existing testbed_dataset.csv:
  A. Inverse-frequency sample weights by PRR zone
  B. Transitional-only training subset
  C. Oversampling transitional region to match Good count

Uses Leave-One-Group-Out CV (49 folds by dst_node), matching testbed_validation.py.

Output: data/processed/reweighting_results.json
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
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
DATASET_PATH = os.path.join(PROCESSED_DIR, 'testbed_dataset.csv')
os.makedirs(PROCESSED_DIR, exist_ok=True)

FEATURE_COLS = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'

RNG = np.random.default_rng(42)

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def load_testbed_data():
    """Load testbed CSV and return X, y, groups, src_nodes."""
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


def compute_zone_weights(y_train):
    """Compute inverse-frequency weights by PRR zone."""
    weights = np.ones(len(y_train))
    good_mask = y_train > 0.9
    trans_mask = (y_train >= 0.1) & (y_train <= 0.9)
    bad_mask = y_train < 0.1

    n_good = max(good_mask.sum(), 1)
    n_trans = max(trans_mask.sum(), 1)
    n_bad = max(bad_mask.sum(), 1)
    total = len(y_train)

    # Inverse frequency: rare classes get higher weight
    n_classes = sum([n_good > 0, n_trans > 0, n_bad > 0])
    weights[good_mask] = total / (n_classes * n_good)
    weights[trans_mask] = total / (n_classes * n_trans)
    weights[bad_mask] = total / (n_classes * n_bad)
    return weights


def eval_fold(y_test, y_pred):
    """Compute full + transitional metrics for a single fold."""
    y_pred_clipped = np.clip(y_pred, 0, 1)
    r2 = r2_score(y_test, y_pred_clipped)
    rmse = float(np.sqrt(mean_squared_error(y_test, y_pred_clipped)))
    mae = float(np.mean(np.abs(y_test - y_pred_clipped)))

    trans_mask = (y_test >= 0.1) & (y_test <= 0.9)
    if trans_mask.sum() > 10:
        t_r2 = r2_score(y_test[trans_mask], y_pred_clipped[trans_mask])
        t_rmse = float(np.sqrt(mean_squared_error(
            y_test[trans_mask], y_pred_clipped[trans_mask])))
        t_mae = float(np.mean(np.abs(
            y_test[trans_mask] - y_pred_clipped[trans_mask])))
    else:
        t_r2 = float('nan')
        t_rmse = float('nan')
        t_mae = float('nan')

    return {
        'r2': r2, 'rmse': rmse, 'mae': mae,
        'trans_r2': t_r2, 'trans_rmse': t_rmse, 'trans_mae': t_mae,
        'trans_n': int(trans_mask.sum()),
    }


def run_experiment(X, y, groups, experiment_name, train_modifier_fn):
    """Run a single experiment across all models with LOGO CV."""
    print(f"\n{'='*60}")
    print(f"Experiment: {experiment_name}")
    print(f"{'='*60}")

    logo = LeaveOneGroupOut()
    n_folds = len(np.unique(groups))

    model_defs = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
        'linreg': lambda: LinearRegression(),
    }

    # Metric accumulators
    metric_keys = ['r2', 'rmse', 'mae', 'trans_r2', 'trans_rmse', 'trans_mae', 'trans_n']
    metrics = {name: {k: [] for k in metric_keys} for name in model_defs}

    for fold, (train_idx, test_idx) in enumerate(logo.split(X, y, groups)):
        if fold % 10 == 0:
            print(f"  Fold {fold+1}/{n_folds}...")

        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        # Apply experiment-specific training modification
        X_train_mod, y_train_mod, sample_weight = train_modifier_fn(
            X_train, y_train)

        for model_name, model_fn in model_defs.items():
            model = model_fn()

            # Train with modification
            if sample_weight is not None and X_train_mod is X_train:
                # Weighted training (Experiment A)
                model.fit(X_train_mod, y_train_mod, sample_weight=sample_weight)
            else:
                # Modified data (Experiments B, C) or baseline
                model.fit(X_train_mod, y_train_mod)

            y_pred = model.predict(X_test)
            fold_metrics = eval_fold(y_test, y_pred)

            for k in metric_keys:
                metrics[model_name][k].append(fold_metrics[k])

    # Summarize
    results = {}
    for model_name in model_defs:
        m = metrics[model_name]
        r2_vals = m['r2']
        trans_r2_vals = [v for v in m['trans_r2'] if not np.isnan(v)]
        trans_mae_vals = [v for v in m['trans_mae'] if not np.isnan(v)]

        entry = {
            'r2_mean': round(float(np.mean(r2_vals)), 4),
            'r2_std': round(float(np.std(r2_vals)), 4),
            'rmse_mean': round(float(np.mean(m['rmse'])), 4),
            'mae_mean': round(float(np.mean(m['mae'])), 4),
            'per_fold_r2': [round(float(v), 4) for v in r2_vals],
        }
        if trans_r2_vals:
            entry['trans_r2_mean'] = round(float(np.mean(trans_r2_vals)), 4)
            entry['trans_r2_std'] = round(float(np.std(trans_r2_vals)), 4)
            entry['trans_rmse_mean'] = round(float(np.mean(
                [v for v in m['trans_rmse'] if not np.isnan(v)])), 4)
            entry['trans_mae_mean'] = round(float(np.mean(trans_mae_vals)), 4)
            entry['per_fold_trans_r2'] = [
                round(float(v), 4) if not np.isnan(v) else None
                for v in m['trans_r2']]
            entry['trans_n_mean'] = int(np.mean(m['trans_n']))

        results[model_name] = entry
        print(f"  {model_name:10s}: R²={entry['r2_mean']:.4f}±{entry['r2_std']:.4f}"
              f"  Trans-R²={entry.get('trans_r2_mean', float('nan')):.4f}")

    return results, metrics


def main():
    print("=" * 60)
    print("REWEIGHTING EXPERIMENT: CLASS IMBALANCE ANALYSIS")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found.")
        return

    X, y, groups = load_testbed_data()
    print(f"Loaded {len(y):,} samples, {X.shape[1]} features")

    # Dataset imbalance summary
    n_good = (y > 0.9).sum()
    n_trans = ((y >= 0.1) & (y <= 0.9)).sum()
    n_bad = (y < 0.1).sum()
    print(f"Zone distribution: Good={n_good} ({100*n_good/len(y):.1f}%), "
          f"Trans={n_trans} ({100*n_trans/len(y):.1f}%), "
          f"Bad={n_bad} ({100*n_bad/len(y):.1f}%)")

    all_results = {}

    # --- Baseline: no modification ---
    def baseline_modifier(X_train, y_train):
        return X_train, y_train, None

    baseline_results, baseline_metrics = run_experiment(
        X, y, groups, "Baseline (unweighted)", baseline_modifier)
    all_results['baseline'] = baseline_results

    # --- Experiment A: Inverse-frequency sample weights ---
    def inverse_weight_modifier(X_train, y_train):
        weights = compute_zone_weights(y_train)
        return X_train, y_train, weights

    exp_a_results, exp_a_metrics = run_experiment(
        X, y, groups, "A: Inverse-frequency weights", inverse_weight_modifier)
    all_results['inverse_weight'] = exp_a_results

    # --- Experiment B: Transitional-only training ---
    def trans_only_modifier(X_train, y_train):
        trans_mask = (y_train >= 0.1) & (y_train <= 0.9)
        if trans_mask.sum() < 10:
            return X_train, y_train, None  # fallback if too few
        return X_train[trans_mask], y_train[trans_mask], None

    exp_b_results, exp_b_metrics = run_experiment(
        X, y, groups, "B: Transitional-only training", trans_only_modifier)
    all_results['trans_only_train'] = exp_b_results

    # --- Experiment C: Oversampling transitional region ---
    def oversampling_modifier(X_train, y_train):
        good_mask = y_train > 0.9
        trans_mask = (y_train >= 0.1) & (y_train <= 0.9)
        n_good = good_mask.sum()
        n_trans = max(trans_mask.sum(), 1)

        if n_trans < 5:
            return X_train, y_train, None

        # Duplicate transitional samples to match Good count
        trans_indices = np.where(trans_mask)[0]
        n_repeats = max(1, n_good // n_trans)
        extra_indices = np.tile(trans_indices, n_repeats - 1)

        all_indices = np.concatenate([np.arange(len(y_train)), extra_indices])
        RNG_local = np.random.default_rng(42)
        RNG_local.shuffle(all_indices)

        return X_train[all_indices], y_train[all_indices], None

    exp_c_results, exp_c_metrics = run_experiment(
        X, y, groups, "C: Oversampling transitional", oversampling_modifier)
    all_results['oversampling'] = exp_c_results

    # --- Wilcoxon tests: each experiment vs baseline ---
    print("\n" + "=" * 60)
    print("Wilcoxon Signed-Rank Tests vs Baseline")
    print("=" * 60)

    wilcoxon_results = {}
    experiments = [
        ('inverse_weight', exp_a_metrics),
        ('trans_only_train', exp_b_metrics),
        ('oversampling', exp_c_metrics),
    ]

    for exp_name, exp_metrics in experiments:
        wilcoxon_results[exp_name] = {}
        for model_name in ['xgboost', 'cart_d3', 'linreg']:
            base_r2 = np.array(baseline_metrics[model_name]['trans_r2'])
            exp_r2 = np.array(exp_metrics[model_name]['trans_r2'])

            # Filter out NaN folds
            valid = ~(np.isnan(base_r2) | np.isnan(exp_r2))
            if valid.sum() < 5:
                wilcoxon_results[exp_name][model_name] = {
                    'error': 'Too few valid folds', 'significant': False,
                }
                continue

            base_valid = base_r2[valid]
            exp_valid = exp_r2[valid]
            diff = float(np.mean(exp_valid) - np.mean(base_valid))

            try:
                stat, pval = wilcoxon(exp_valid, base_valid)
                # Bonferroni: 9 comparisons (3 experiments x 3 models)
                pval_corrected = min(pval * 9, 1.0)
                pooled_std = np.sqrt(
                    (np.std(base_valid)**2 + np.std(exp_valid)**2) / 2)
                cohens_d = diff / pooled_std if pooled_std > 1e-10 else 0.0

                result = {
                    'delta_trans_r2': round(diff, 4),
                    'p_value': round(float(pval), 6),
                    'p_bonferroni': round(float(pval_corrected), 6),
                    'cohens_d': round(float(cohens_d), 2),
                    'significant': bool(pval_corrected < 0.05),
                    'n_valid_folds': int(valid.sum()),
                }
            except ValueError as e:
                result = {'error': str(e), 'significant': False}

            wilcoxon_results[exp_name][model_name] = result
            sig = 'SIG' if result.get('significant') else 'ns'
            print(f"  {exp_name} / {model_name}: "
                  f"delta_trans_R²={diff:+.4f} p={result.get('p_bonferroni', 'N/A')} "
                  f"{sig}")

    all_results['wilcoxon_vs_baseline'] = wilcoxon_results

    # --- Save ---
    output = {
        'description': (
            'Reweighting experiments testing whether negative Trans-R² is caused '
            'by 76% PRR=1.0 class imbalance. Three experiments: (A) inverse-frequency '
            'sample weights, (B) transitional-only training, (C) oversampling. '
            'LOGO CV (49 folds by dst_node).'
        ),
        'features': FEATURE_COLS,
        'target': TARGET_COL,
        'cv_protocol': 'LeaveOneGroupOut (49 folds) grouped by dst_node',
        'n_samples': int(len(y)),
        'zone_distribution': {
            'good_pct': round(100 * n_good / len(y), 1),
            'transitional_pct': round(100 * n_trans / len(y), 1),
            'bad_pct': round(100 * n_bad / len(y), 1),
        },
    }
    output.update(all_results)

    out_path = os.path.join(PROCESSED_DIR, 'reweighting_results.json')
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nSaved: {out_path}")

    # --- Interpretation ---
    print("\n" + "=" * 60)
    print("INTERPRETATION")
    print("=" * 60)
    for model_name in ['xgboost', 'cart_d3']:
        base_tr2 = all_results['baseline'][model_name].get('trans_r2_mean', float('nan'))
        weighted_tr2 = all_results['inverse_weight'][model_name].get('trans_r2_mean', float('nan'))
        print(f"\n  {model_name}:")
        print(f"    Baseline Trans-R²:  {base_tr2:.4f}")
        print(f"    Weighted Trans-R²:  {weighted_tr2:.4f}")
        if not np.isnan(weighted_tr2):
            if weighted_tr2 > -0.5:
                print(f"    --> IMBALANCE IS THE PROBLEM (weighted Trans-R² > -0.5)")
            elif weighted_tr2 < -1.0:
                print(f"    --> FEATURES TRULY INSUFFICIENT (weighted Trans-R² < -1.0)")
            else:
                print(f"    --> PARTIAL IMPROVEMENT (weighted Trans-R² between -1.0 and -0.5)")


if __name__ == '__main__':
    main()
