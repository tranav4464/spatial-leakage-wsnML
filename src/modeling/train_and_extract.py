"""
WSN XGBoost Training + Empirical ALE Distillation Pipeline
=========================================================
1. Loads the WSN dataset (with hidden spatial mechanics).
2. Performs 5-Fold GroupKFold Cross-Validation for XGBoost, CART, LinReg,
   and the ALE-distilled rule (all models use the same CV protocol).
3. Computes ALE for the proxy features.
4. Extracts empirical thresholds and a discrete Lookup Table (LUT).
5. Reports mean +/- std for all metrics with statistical significance tests.
"""

import numpy as np
import csv
import os
import json
from sklearn.model_selection import GroupKFold
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from scipy.stats import wilcoxon
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
os.makedirs(PROCESSED_DIR, exist_ok=True)

# Fixed RNG for reproducibility
RNG = np.random.default_rng(42)

# ============================================================
# Step 1: Load dataset
# ============================================================
print("=" * 60)
print("STEP 1: Loading dataset...")
print("=" * 60)

features_cols = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]
target_col = 'PRR'  # Packet Reception Rate (formerly Detection_Accuracy)

X_data = []
y_data = []
groups_data = []

with open(DATASET_PATH) as f:
    reader = csv.DictReader(f)
    for row in reader:
        if float(row['Residual_Energy_J']) > 0:
            X_data.append([float(row[c]) for c in features_cols])
            # Support both old ('Detection_Accuracy') and new ('PRR') column names
            y_val = row.get(target_col) or row.get('Detection_Accuracy')
            y_data.append(float(y_val))
            groups_data.append(int(row['Config_ID']))

X = np.array(X_data)
y = np.array(y_data)
groups = np.array(groups_data)

# Downsample to 150k for faster CV — using seeded RNG
if len(X) > 150000:
    idx = RNG.choice(len(X), 150000, replace=False)
    X = X[idx]
    y = y[idx]
    groups = groups[idx]

print(f"  Loaded and sampled {len(y):,} active rows, {len(features_cols)} features")
print(f"  Unique configurations: {len(np.unique(groups))}")

# ============================================================
# Step 2: 5-Fold GroupKFold Cross Validation
# ============================================================
print("\n" + "=" * 60)
print("STEP 2: 5-Fold GroupKFold Cross-Validation...")
print("=" * 60)

gkf = GroupKFold(n_splits=5)

xgb_params = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1
}

metrics = {
    'xgb': {'r2': [], 'rmse': []},
    'lr': {'r2': [], 'rmse': []},
    'cart': {'r2': [], 'rmse': []},
    'ale_rule': {'r2': [], 'rmse': []},
}


def compute_ale(model, X, feature_idx, n_bins=40):
    """Compute Accumulated Local Effects for a single feature."""
    feature_values = X[:, feature_idx]
    percentiles = np.linspace(0, 100, n_bins + 1)
    bin_edges = np.unique(np.percentile(feature_values, percentiles))
    if len(bin_edges) < 3:
        return np.array([feature_values[0]]), np.array([0.0])

    ale_values = []
    bin_centers = []
    for i in range(len(bin_edges) - 1):
        lo, hi = bin_edges[i], bin_edges[i + 1]
        mask = (feature_values >= lo) & (feature_values <= hi)
        if mask.sum() == 0:
            continue
        X_bin = X[mask].copy()

        X_upper, X_lower = X_bin.copy(), X_bin.copy()
        X_upper[:, feature_idx] = hi
        X_lower[:, feature_idx] = lo

        local_effect = np.mean(model.predict(X_upper) - model.predict(X_lower))
        ale_values.append(local_effect)
        bin_centers.append((lo + hi) / 2)

    ale_accumulated = np.cumsum(ale_values)
    ale_accumulated -= np.mean(ale_accumulated)
    return np.array(bin_centers), ale_accumulated


def extract_ale_rule(model, X_train, y_train, features_cols):
    """Extract ALE-based rule from a trained model on training data only."""
    SNR_IDX = features_cols.index('SNR_dB')
    DENS_IDX = features_cols.index('Local_Density')

    # Compute ALE on a seeded subset of training data
    subset_size = min(10000, len(X_train))
    ale_idx = RNG.choice(len(X_train), subset_size, replace=False)
    X_ale = X_train[ale_idx]

    # Compute ALE for all features (for analysis), but extract rules from SNR + Density
    ale_all = {}
    for idx, name in enumerate(features_cols):
        centers, ale_vals = compute_ale(model, X_ale, idx, n_bins=40)
        ale_all[name] = {'centers': centers.tolist(), 'ale': ale_vals.tolist()}

    # 1. SNR thresholds: find steepest gradient
    snr_c = np.array(ale_all['SNR_dB']['centers'])
    snr_a = np.array(ale_all['SNR_dB']['ale'])

    if len(snr_c) > 1:
        gradients = np.diff(snr_a) / np.maximum(np.diff(snr_c), 1e-10)
        max_grad_idx = np.argmax(gradients)
        snr_transition_center = snr_c[max_grad_idx]
        snr_low = float(snr_transition_center - 3.0)
        snr_high = float(snr_transition_center + 3.0)
    else:
        snr_low, snr_high = 0.0, 10.0

    # 2. Density LUT
    dens_c = np.array(ale_all['Local_Density']['centers'])
    dens_a = np.array(ale_all['Local_Density']['ale'])
    lut_indices = np.linspace(0, len(dens_c) - 1, 5, dtype=int)
    lut_points = []
    for i in lut_indices:
        lut_points.append({
            'density': round(float(dens_c[i]), 1),
            'ale_effect': round(float(dens_a[i]), 4)
        })

    # 3. Engineer features and fit calibration on held-out split
    def engineer_features(X_data):
        X_eng = np.zeros((len(X_data), 2))
        for i, row in enumerate(X_data):
            snr = row[SNR_IDX]
            density = row[DENS_IDX]

            if snr < snr_low:
                base = 0.0
            elif snr > snr_high:
                base = 1.0
            else:
                base = (snr - snr_low) / (snr_high - snr_low)
            X_eng[i, 0] = base

            effect = 0.0
            if density <= lut_points[0]['density']:
                effect = lut_points[0]['ale_effect']
            elif density >= lut_points[-1]['density']:
                effect = lut_points[-1]['ale_effect']
            else:
                for j in range(len(lut_points) - 1):
                    d1 = lut_points[j]['density']
                    d2 = lut_points[j + 1]['density']
                    if d1 <= density <= d2:
                        e1 = lut_points[j]['ale_effect']
                        e2 = lut_points[j + 1]['ale_effect']
                        denom = d2 - d1
                        if denom < 1e-10:
                            effect = e1
                        else:
                            effect = e1 + ((density - d1) / denom) * (e2 - e1)
                        break
            X_eng[i, 1] = effect
        return X_eng

    # Use samples NOT in ALE subset for calibration (prevents overfitting)
    cal_mask = np.ones(len(X_train), dtype=bool)
    cal_mask[ale_idx] = False
    if cal_mask.sum() < 100:
        cal_mask = np.ones(len(X_train), dtype=bool)
    print(f"  ALE calibration: {len(ale_idx)} ALE samples, "
          f"{cal_mask.sum()} calibration samples"
          + (" (FALLBACK: using all training data)" if cal_mask.all() else ""))
    X_cal_eng = engineer_features(X_train[cal_mask])
    calibration_model = LinearRegression()
    calibration_model.fit(X_cal_eng, y_train[cal_mask])

    return {
        'snr_low': snr_low,
        'snr_high': snr_high,
        'lut_points': lut_points,
        'coefs': calibration_model.coef_.tolist(),
        'intercept': float(calibration_model.intercept_),
        'engineer_fn': engineer_features,
        'ale_all': ale_all,
    }


# Train the final model on full data (for ALE computation and export)
print("  Training final model on full sample...")
final_model = xgb.XGBRegressor(**xgb_params)
final_model.fit(X, y)

# Cross-validation loop: all models evaluated with the same protocol
for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups)):
    print(f"  --> Running Fold {fold + 1}/5...")
    X_train, X_test = X[train_idx], X[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]

    # XGBoost
    model_xgb = xgb.XGBRegressor(**xgb_params)
    model_xgb.fit(X_train, y_train)
    y_pred_xgb = model_xgb.predict(X_test)
    metrics['xgb']['r2'].append(r2_score(y_test, y_pred_xgb))
    metrics['xgb']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred_xgb)))

    # Linear Regression
    model_lr = LinearRegression()
    model_lr.fit(X_train, y_train)
    y_pred_lr = model_lr.predict(X_test)
    metrics['lr']['r2'].append(r2_score(y_test, y_pred_lr))
    metrics['lr']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred_lr)))

    # CART (Depth 4)
    model_cart = DecisionTreeRegressor(max_depth=4, random_state=42)
    model_cart.fit(X_train, y_train)
    y_pred_cart = model_cart.predict(X_test)
    metrics['cart']['r2'].append(r2_score(y_test, y_pred_cart))
    metrics['cart']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred_cart)))

    # ALE Distilled Rule (extracted and evaluated per fold)
    rule_info = extract_ale_rule(model_xgb, X_train, y_train, features_cols)
    X_test_eng = rule_info['engineer_fn'](X_test)
    y_pred_rule = (rule_info['coefs'][0] * X_test_eng[:, 0] +
                   rule_info['coefs'][1] * X_test_eng[:, 1] +
                   rule_info['intercept'])
    y_pred_rule = np.clip(y_pred_rule, 0.0, 1.0)
    metrics['ale_rule']['r2'].append(r2_score(y_test, y_pred_rule))
    metrics['ale_rule']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred_rule)))

# Report results with confidence intervals
print("\n  5-Fold GroupKFold CV Results (Mean +/- Std):")
for name, label in [('xgb', 'XGBoost'), ('cart', 'CART (DT d=4)'),
                     ('lr', 'LinReg'), ('ale_rule', 'ALE Rule')]:
    r2_mean = np.mean(metrics[name]['r2'])
    r2_std = np.std(metrics[name]['r2'])
    rmse_mean = np.mean(metrics[name]['rmse'])
    rmse_std = np.std(metrics[name]['rmse'])
    print(f"    {label:15s}: R² = {r2_mean:.4f} +/- {r2_std:.4f}  |  "
          f"RMSE = {rmse_mean:.4f} +/- {rmse_std:.4f}")

# Statistical significance tests (Wilcoxon signed-rank)
print("\n  Statistical Significance (Wilcoxon signed-rank p-values):")
pairs = [('xgb', 'cart'), ('xgb', 'ale_rule'), ('cart', 'ale_rule'),
         ('ale_rule', 'lr')]
for m1, m2 in pairs:
    r2_1 = metrics[m1]['r2']
    r2_2 = metrics[m2]['r2']
    try:
        stat, pval = wilcoxon(r2_1, r2_2)
        sig = "***" if pval < 0.001 else "**" if pval < 0.01 else "*" if pval < 0.05 else "ns"
        print(f"    {m1} vs {m2}: p = {pval:.4f} {sig}")
    except ValueError:
        print(f"    {m1} vs {m2}: insufficient variation for test")

# ============================================================
# Step 3: Compute ALE on full dataset using final model
# ============================================================
print("\n" + "=" * 60)
print("STEP 3: Computing ALE Plots (final model, full data)...")
print("=" * 60)

ale_results = {}
X_ale_subset = X[RNG.choice(X.shape[0], min(10000, len(X)), replace=False)]

for idx, name in enumerate(features_cols):
    centers, ale_vals = compute_ale(final_model, X_ale_subset, idx, n_bins=40)
    ale_results[name] = {'centers': centers.tolist(), 'ale': ale_vals.tolist()}

ale_path = os.path.join(PROCESSED_DIR, 'ale_results.json')
with open(ale_path, 'w') as f:
    json.dump(ale_results, f, indent=2)

# ============================================================
# Step 4: Extract final rule (for deployment) and save metadata
# ============================================================
print("\n" + "=" * 60)
print("STEP 4: Extracting Final ALE Rule for Deployment...")
print("=" * 60)

final_rule = extract_ale_rule(final_model, X, y, features_cols)

print(f"  SNR Zone: {final_rule['snr_low']:.2f}dB to {final_rule['snr_high']:.2f}dB")
print(f"  Density LUT: {final_rule['lut_points']}")
print(f"  Coefficients: base={final_rule['coefs'][0]:.4f}, "
      f"density={final_rule['coefs'][1]:.4f}, intercept={final_rule['intercept']:.4f}")

# ============================================================
# Step 5: Save Metadata
# ============================================================
threshold_data = {
    'snr_low': round(final_rule['snr_low'], 2),
    'snr_high': round(final_rule['snr_high'], 2),
    'density_lut': final_rule['lut_points'],
    'rule_coefs': {
        'base_weight': final_rule['coefs'][0],
        'density_weight': final_rule['coefs'][1],
        'intercept': final_rule['intercept'],
    },
    'model_metrics': {
        'xgboost_r2_mean': round(np.mean(metrics['xgb']['r2']), 4),
        'xgboost_r2_std': round(np.std(metrics['xgb']['r2']), 4),
        'xgboost_rmse_mean': round(np.mean(metrics['xgb']['rmse']), 4),
        'cart_r2_mean': round(np.mean(metrics['cart']['r2']), 4),
        'cart_r2_std': round(np.std(metrics['cart']['r2']), 4),
        'cart_rmse_mean': round(np.mean(metrics['cart']['rmse']), 4),
        'linear_r2_mean': round(np.mean(metrics['lr']['r2']), 4),
        'linear_r2_std': round(np.std(metrics['lr']['r2']), 4),
        'linear_rmse_mean': round(np.mean(metrics['lr']['rmse']), 4),
        'rule_r2_mean': round(np.mean(metrics['ale_rule']['r2']), 4),
        'rule_r2_std': round(np.std(metrics['ale_rule']['r2']), 4),
        'rule_rmse_mean': round(np.mean(metrics['ale_rule']['rmse']), 4),
        'per_fold_r2': {
            'xgboost': [round(v, 4) for v in metrics['xgb']['r2']],
            'cart': [round(v, 4) for v in metrics['cart']['r2']],
            'linear': [round(v, 4) for v in metrics['lr']['r2']],
            'ale_rule': [round(v, 4) for v in metrics['ale_rule']['r2']],
        },
    },
    'feature_importances': {
        name: round(float(imp), 4)
        for name, imp in zip(features_cols, final_model.feature_importances_)
    },
}

with open(os.path.join(PROCESSED_DIR, 'extracted_thresholds.json'), 'w') as f:
    json.dump(threshold_data, f, indent=2)

final_model.save_model(os.path.join(PROCESSED_DIR, 'xgboost_model.json'))
print("\nPipeline complete.")
