"""
Ablation Studies for Q1 Publication:
1. Leave-one-feature-out analysis
2. Feature correlation matrix
3. Residual analysis
4. Sensitivity analysis (learning curves, cross-seed variance)
"""
import numpy as np
import csv
import os
import json
from sklearn.model_selection import GroupKFold
from sklearn.metrics import r2_score, mean_squared_error
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
os.makedirs(PROCESSED_DIR, exist_ok=True)

RNG = np.random.default_rng(42)

FEATURE_COLS = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'n_jobs': -1
}


def load_data():
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
    return X, y, groups


def leave_one_feature_out(X, y, groups):
    """Train XGBoost with each feature removed; report R2 drop."""
    print("\n  Leave-One-Feature-Out Analysis:")
    gkf = GroupKFold(n_splits=5)

    # Baseline: all features
    baseline_r2 = []
    for train_idx, test_idx in gkf.split(X, y, groups):
        model = xgb.XGBRegressor(**XGB_PARAMS, random_state=42)
        model.fit(X[train_idx], y[train_idx])
        baseline_r2.append(r2_score(y[test_idx], model.predict(X[test_idx])))
    baseline = np.mean(baseline_r2)
    print(f"    Baseline (all features): R2 = {baseline:.4f}")

    results = {'baseline_r2': round(baseline, 4), 'features': {}}
    for idx, name in enumerate(FEATURE_COLS):
        mask = [j for j in range(len(FEATURE_COLS)) if j != idx]
        X_reduced = X[:, mask]
        fold_r2 = []
        for train_idx, test_idx in gkf.split(X_reduced, y, groups):
            model = xgb.XGBRegressor(**XGB_PARAMS, random_state=42)
            model.fit(X_reduced[train_idx], y[train_idx])
            fold_r2.append(r2_score(y[test_idx], model.predict(X_reduced[test_idx])))
        r2_mean = np.mean(fold_r2)
        r2_drop = baseline - r2_mean
        results['features'][name] = {
            'r2_without': round(r2_mean, 4),
            'r2_drop': round(r2_drop, 4),
        }
        print(f"    Without {name:30s}: R2 = {r2_mean:.4f} (drop = {r2_drop:+.4f})")

    return results


def feature_correlation(X):
    """Compute Pearson correlation matrix."""
    print("\n  Feature Correlation Matrix:")
    corr = np.corrcoef(X.T)
    results = {}
    for i, name_i in enumerate(FEATURE_COLS):
        for j, name_j in enumerate(FEATURE_COLS):
            if i < j and abs(corr[i, j]) > 0.5:
                print(f"    {name_i} <-> {name_j}: r = {corr[i, j]:.3f}")
                results[f"{name_i}__vs__{name_j}"] = round(float(corr[i, j]), 4)
    return {
        'matrix': [[round(float(v), 4) for v in row] for row in corr],
        'features': FEATURE_COLS,
        'high_correlations': results,
    }


def learning_curves(X, y, groups):
    """Train on increasing fractions of data; report R2."""
    print("\n  Learning Curves:")
    fractions = [0.1, 0.25, 0.5, 0.75, 1.0]
    gkf = GroupKFold(n_splits=5)

    results = {}
    for frac in fractions:
        fold_r2 = []
        for train_idx, test_idx in gkf.split(X, y, groups):
            n_train = int(len(train_idx) * frac)
            sub_idx = train_idx[:n_train]
            model = xgb.XGBRegressor(**XGB_PARAMS, random_state=42)
            model.fit(X[sub_idx], y[sub_idx])
            fold_r2.append(r2_score(y[test_idx], model.predict(X[test_idx])))
        r2_mean = np.mean(fold_r2)
        r2_std = np.std(fold_r2)
        results[str(frac)] = {
            'r2_mean': round(r2_mean, 4),
            'r2_std': round(r2_std, 4),
        }
        print(f"    {frac*100:5.0f}% data: R2 = {r2_mean:.4f} +/- {r2_std:.4f}")

    return results


def cross_seed_variance(X, y, groups):
    """Run the full pipeline with different random seeds."""
    print("\n  Cross-Seed Variance:")
    seeds = [42, 123, 456, 789, 2024]
    gkf = GroupKFold(n_splits=5)

    seed_r2 = []
    for seed in seeds:
        params = {**XGB_PARAMS, 'random_state': seed}
        fold_r2 = []
        for train_idx, test_idx in gkf.split(X, y, groups):
            model = xgb.XGBRegressor(**params)
            model.fit(X[train_idx], y[train_idx])
            fold_r2.append(r2_score(y[test_idx], model.predict(X[test_idx])))
        seed_r2.append(np.mean(fold_r2))
        print(f"    Seed {seed}: R2 = {np.mean(fold_r2):.4f}")

    results = {
        'seeds': seeds,
        'r2_per_seed': [round(v, 4) for v in seed_r2],
        'r2_mean': round(np.mean(seed_r2), 4),
        'r2_std': round(np.std(seed_r2), 4),
    }
    print(f"    Overall: R2 = {np.mean(seed_r2):.4f} +/- {np.std(seed_r2):.4f}")
    return results


def residual_analysis(X, y, groups):
    """Compute residuals for XGBoost model and summarize error patterns."""
    print("\n  Residual Analysis:")
    gkf = GroupKFold(n_splits=5)

    all_y_true = []
    all_y_pred = []
    all_features = []

    for train_idx, test_idx in gkf.split(X, y, groups):
        model = xgb.XGBRegressor(**XGB_PARAMS, random_state=42)
        model.fit(X[train_idx], y[train_idx])
        y_pred = model.predict(X[test_idx])
        all_y_true.extend(y[test_idx])
        all_y_pred.extend(y_pred)
        all_features.extend(X[test_idx])

    y_true = np.array(all_y_true)
    y_pred = np.array(all_y_pred)
    X_test = np.array(all_features)
    residuals = y_true - y_pred

    # Error by feature quartiles
    results = {
        'overall_mae': round(float(np.mean(np.abs(residuals))), 4),
        'overall_rmse': round(float(np.sqrt(np.mean(residuals ** 2))), 4),
        'residual_mean': round(float(np.mean(residuals)), 4),
        'residual_std': round(float(np.std(residuals)), 4),
        'by_feature_quartile': {},
    }

    for idx, name in enumerate(FEATURE_COLS):
        feat = X_test[:, idx]
        quartiles = np.percentile(feat, [25, 50, 75])
        q_labels = ['Q1', 'Q2', 'Q3', 'Q4']
        q_bounds = [(-np.inf, quartiles[0]), (quartiles[0], quartiles[1]),
                     (quartiles[1], quartiles[2]), (quartiles[2], np.inf)]
        feature_errors = {}
        for label, (lo, hi) in zip(q_labels, q_bounds):
            mask = (feat >= lo) & (feat < hi)
            if mask.sum() > 0:
                mae = float(np.mean(np.abs(residuals[mask])))
                feature_errors[label] = round(mae, 4)
        results['by_feature_quartile'][name] = feature_errors

    # Print worst quartiles
    for name, qerrors in results['by_feature_quartile'].items():
        vals = list(qerrors.values())
        if vals:
            worst_q = max(qerrors, key=qerrors.get)
            print(f"    {name:30s}: worst quartile = {worst_q} (MAE = {qerrors[worst_q]:.4f})")

    # Save predictions for plotting
    results['y_true'] = [round(float(v), 4) for v in y_true[:5000]]
    results['y_pred'] = [round(float(v), 4) for v in y_pred[:5000]]

    return results


def main():
    print("=" * 60)
    print("ABLATION STUDIES")
    print("=" * 60)

    X, y, groups = load_data()
    print(f"  Dataset: {len(y):,} rows\n")

    all_results = {}

    all_results['lofo'] = leave_one_feature_out(X, y, groups)
    all_results['correlation'] = feature_correlation(X)
    all_results['learning_curves'] = learning_curves(X, y, groups)
    all_results['cross_seed'] = cross_seed_variance(X, y, groups)
    all_results['residuals'] = residual_analysis(X, y, groups)

    out_path = os.path.join(PROCESSED_DIR, 'ablation_results.json')
    with open(out_path, 'w') as f:
        json.dump(all_results, f, indent=2)
    print(f"\n  All results saved to: {out_path}")


if __name__ == '__main__':
    main()
