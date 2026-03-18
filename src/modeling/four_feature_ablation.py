"""
Four-Feature Simulation Ablation
==================================
Runs simulation models with only 4 features matching the testbed:
  Distance, RSSI, Local_Density, + synthetic LQI proxy from SNR.

This creates a fair apples-to-apples comparison with testbed results,
addressing the criticism that the 8-feature sim vs. 4-feature testbed
comparison inflates the apparent sim-to-real gap.

Output: data/processed/four_feature_ablation.json
"""
import os
import json
import csv
import numpy as np
from scipy.special import erfc
from sklearn.model_selection import GroupKFold, KFold
from sklearn.metrics import r2_score, mean_squared_error
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
DATASET_PATH = os.path.join(ROOT_DIR, 'data', 'raw', 'wsn_dataset.csv')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
os.makedirs(PROCESSED_DIR, exist_ok=True)

RNG = np.random.default_rng(42)

# Full 8-feature set (for comparison)
FULL_FEATURES = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]

# 4 testbed-matched features (Distance, RSSI, Density, + synthetic LQI)
MATCHED_FEATURES = ['Distance_to_Sink_m', 'Signal_Strength_RSSI_dBm', 'Local_Density']
# LQI proxy is computed from SNR_dB

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}


def compute_lqi_proxy(snr_db):
    """Compute synthetic AT86RF231-like LQI from SNR.

    Uses the IEEE 802.15.4 O-QPSK BER model to compute expected
    frame success rate, then maps to [0, 255] LQI range.
    Saturates at 255 for SNR > 5 dB to mimic AT86RF231 behavior.
    """
    snr_linear = 10.0 ** (snr_db / 10.0)
    snr_linear = np.maximum(snr_linear, 1e-10)
    ber = 0.5 * erfc(np.sqrt(8.0 * snr_linear))
    frame_success = (1.0 - ber) ** (127 * 8)  # 127-byte frame
    lqi = 255.0 * frame_success
    # Saturate at 255 for high SNR (mimics AT86RF231 correlation-based LQI)
    lqi = np.clip(lqi, 0, 255)
    # Force saturation for SNR > 5 dB
    lqi[snr_db > 5.0] = 255.0
    return lqi


def load_data():
    """Load simulation dataset with both full and 4-feature subsets."""
    print("Loading simulation data...")
    X_full, X_matched, y_data, groups_data = [], [], [], []
    snr_values = []

    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if float(row['Residual_Energy_J']) > 0:
                X_full.append([float(row[c]) for c in FULL_FEATURES])
                X_matched.append([float(row[c]) for c in MATCHED_FEATURES])
                snr_values.append(float(row['SNR_dB']))
                y_data.append(float(row.get('PRR') or row.get('Detection_Accuracy')))
                groups_data.append(int(row['Config_ID']))

    X_full = np.array(X_full)
    X_matched = np.array(X_matched)
    snr_arr = np.array(snr_values)
    y = np.array(y_data)
    groups = np.array(groups_data)

    # Add synthetic LQI as 4th feature
    lqi_proxy = compute_lqi_proxy(snr_arr)
    X_4feat = np.column_stack([X_matched, lqi_proxy])

    # Downsample if needed
    if len(X_full) > 150000:
        idx = RNG.choice(len(X_full), 150000, replace=False)
        X_full, X_4feat, y, groups = X_full[idx], X_4feat[idx], y[idx], groups[idx]

    print(f"  Loaded {len(y):,} samples, {len(np.unique(groups))} configs")
    print(f"  LQI proxy: {(lqi_proxy[idx] if len(X_full) == 150000 else lqi_proxy) .mean():.1f} mean, "
          f"{((lqi_proxy[idx] if len(X_full) == 150000 else lqi_proxy) == 255).mean()*100:.1f}% saturated")

    return X_full, X_4feat, y, groups


def run_cv(X, y, groups, label):
    """Run GroupKFold(5) and return per-model R² results."""
    gkf = GroupKFold(n_splits=5)

    models = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d6': lambda: DecisionTreeRegressor(max_depth=6, random_state=42),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
        'linreg': lambda: LinearRegression(),
    }

    results = {}
    for name, model_fn in models.items():
        fold_r2 = []
        fold_rmse = []
        for train_idx, test_idx in gkf.split(X, y, groups):
            model = model_fn()
            model.fit(X[train_idx], y[train_idx])
            pred = np.clip(model.predict(X[test_idx]), 0, 1)
            fold_r2.append(float(r2_score(y[test_idx], pred)))
            fold_rmse.append(float(np.sqrt(mean_squared_error(y[test_idx], pred))))

        results[name] = {
            'r2_mean': round(float(np.mean(fold_r2)), 4),
            'r2_std': round(float(np.std(fold_r2)), 4),
            'rmse_mean': round(float(np.mean(fold_rmse)), 4),
            'per_fold_r2': [round(v, 4) for v in fold_r2],
        }
        print(f"    {name:10s}: R²={results[name]['r2_mean']:.4f} ± {results[name]['r2_std']:.4f}")

    return results


def run_naive_cv(X, y, label):
    """Run naive KFold(5, shuffle=True) and return per-model R² results."""
    kf = KFold(n_splits=5, shuffle=True, random_state=42)

    models = {
        'xgboost': lambda: xgb.XGBRegressor(**XGB_PARAMS),
        'cart_d6': lambda: DecisionTreeRegressor(max_depth=6, random_state=42),
        'cart_d3': lambda: DecisionTreeRegressor(max_depth=3, random_state=42),
        'linreg': lambda: LinearRegression(),
    }

    results = {}
    for name, model_fn in models.items():
        fold_r2 = []
        fold_rmse = []
        for train_idx, test_idx in kf.split(X, y):
            model = model_fn()
            model.fit(X[train_idx], y[train_idx])
            pred = np.clip(model.predict(X[test_idx]), 0, 1)
            fold_r2.append(float(r2_score(y[test_idx], pred)))
            fold_rmse.append(float(np.sqrt(mean_squared_error(y[test_idx], pred))))

        results[name] = {
            'r2_mean': round(float(np.mean(fold_r2)), 4),
            'r2_std': round(float(np.std(fold_r2)), 4),
            'rmse_mean': round(float(np.mean(fold_rmse)), 4),
            'per_fold_r2': [round(v, 4) for v in fold_r2],
        }
        print(f"    {name:10s}: R²={results[name]['r2_mean']:.4f} ± {results[name]['r2_std']:.4f}")

    return results


def main():
    print("=" * 60)
    print("FOUR-FEATURE SIMULATION ABLATION")
    print("=" * 60)

    if not os.path.exists(DATASET_PATH):
        print(f"ERROR: {DATASET_PATH} not found.")
        return

    X_full, X_4feat, y, groups = load_data()

    print(f"\n--- 8-feature simulation (GroupKFold) ---")
    results_8feat = run_cv(X_full, y, groups, "8-feature")

    print(f"\n--- 4-feature simulation (GroupKFold) ---")
    results_4feat = run_cv(X_4feat, y, groups, "4-feature")

    print(f"\n--- 8-feature simulation (naive KFold) ---")
    results_8feat_naive = run_naive_cv(X_full, y, "8-feature-naive")

    print(f"\n--- 4-feature simulation (naive KFold) ---")
    results_4feat_naive = run_naive_cv(X_4feat, y, "4-feature-naive")

    # Compute leakage delta for both feature sets
    print("\n" + "=" * 60)
    print("SPATIAL LEAKAGE ISOLATION: Naive vs GroupKFold")
    print("=" * 60)
    print(f"  {'Model':10s}  {'8f Naive':>8s}  {'8f Group':>8s}  {'D_8f':>6s}  {'4f Naive':>8s}  {'4f Group':>8s}  {'D_4f':>6s}")
    for name in results_8feat:
        n8 = results_8feat_naive[name]['r2_mean']
        g8 = results_8feat[name]['r2_mean']
        d8 = n8 - g8
        n4 = results_4feat_naive[name]['r2_mean']
        g4 = results_4feat[name]['r2_mean']
        d4 = n4 - g4
        print(f"  {name:10s}  {n8:+8.4f}  {g8:+8.4f}  {d8:+6.3f}  {n4:+8.4f}  {g4:+8.4f}  {d4:+6.3f}")

    # Compute gap reduction
    print("\n" + "=" * 60)
    print("COMPARISON: Fair sim-to-real gap")
    print("=" * 60)
    print(f"  {'Model':10s}  {'Sim 8-feat':>10s}  {'Sim 4-feat':>10s}  {'Drop':>8s}")
    for name in results_8feat:
        r2_8 = results_8feat[name]['r2_mean']
        r2_4 = results_4feat[name]['r2_mean']
        drop = r2_8 - r2_4
        print(f"  {name:10s}  {r2_8:+10.4f}  {r2_4:+10.4f}  {drop:+8.4f}")

    # Save
    output = {
        'description': (
            'Four-feature simulation ablation: comparison of 8-feature '
            '(original) vs 4-feature (testbed-matched: Distance, RSSI, '
            'Density, synthetic LQI proxy) simulation R² under both '
            'GroupKFold(5) and naive KFold(5, shuffle=True). The naive vs '
            'grouped delta isolates spatial leakage independent of feature '
            'starvation.'
        ),
        'full_features': FULL_FEATURES,
        'matched_features': MATCHED_FEATURES + ['LQI_proxy'],
        'n_samples': int(len(y)),
        'results_8feat': results_8feat,
        'results_4feat': results_4feat,
        'results_8feat_naive': results_8feat_naive,
        'results_4feat_naive': results_4feat_naive,
    }

    out_path = os.path.join(PROCESSED_DIR, 'four_feature_ablation.json')
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"\nSaved: {out_path}")


if __name__ == '__main__':
    main()
