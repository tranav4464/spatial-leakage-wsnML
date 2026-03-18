"""
Fair ALE Comparison: 2-Feature Baselines vs ALE Rule
=====================================================
The ALE rule uses only 2 features (SNR_dB and Local_Density), but all other
models in the main pipeline use 8 features. This script creates a fair
apples-to-apples comparison by training CART and LinReg on the SAME 2 features,
alongside the full 8-feature models for reference.

Output: data/processed/fair_ale_comparison.json
"""

import numpy as np
import csv
import os
import json
from sklearn.model_selection import GroupKFold
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
os.makedirs(PROCESSED_DIR, exist_ok=True)

# Fixed RNG for reproducibility (same seed as main pipeline)
RNG = np.random.default_rng(42)

# ============================================================
# Feature definitions
# ============================================================
features_cols = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]
target_col = 'PRR'  # Packet Reception Rate (formerly Detection_Accuracy)

# The 2 features used by the ALE rule
SNR_IDX = features_cols.index('SNR_dB')          # index 5
DENS_IDX = features_cols.index('Local_Density')   # index 2
TWO_FEAT_INDICES = [SNR_IDX, DENS_IDX]

# ============================================================
# Step 1: Load dataset (identical to train_and_extract.py)
# ============================================================
print("=" * 60)
print("STEP 1: Loading dataset...")
print("=" * 60)

X_data = []
y_data = []
groups_data = []

with open(DATASET_PATH) as f:
    reader = csv.DictReader(f)
    for row in reader:
        if float(row['Residual_Energy_J']) > 0:
            X_data.append([float(row[c]) for c in features_cols])
            y_val = row.get(target_col) or row.get('Detection_Accuracy')
            y_data.append(float(y_val))
            groups_data.append(int(row['Config_ID']))

X = np.array(X_data)
y = np.array(y_data)
groups = np.array(groups_data)

# Downsample to 150k (same seed, same method as main pipeline)
if len(X) > 150000:
    idx = RNG.choice(len(X), 150000, replace=False)
    X = X[idx]
    y = y[idx]
    groups = groups[idx]

# Create the 2-feature subset
X_2feat = X[:, TWO_FEAT_INDICES]

print(f"  Loaded {len(y):,} active rows")
print(f"  Full features shape: {X.shape}")
print(f"  2-feature subset shape: {X_2feat.shape}")
print(f"  2 features used: SNR_dB (idx {SNR_IDX}), Local_Density (idx {DENS_IDX})")
print(f"  Unique configurations: {len(np.unique(groups))}")

# ============================================================
# ALE helpers (replicated from train_and_extract.py)
# ============================================================


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
    snr_idx = features_cols.index('SNR_dB')
    dens_idx = features_cols.index('Local_Density')

    # Compute ALE on a seeded subset of training data
    subset_size = min(10000, len(X_train))
    ale_idx = RNG.choice(len(X_train), subset_size, replace=False)
    X_ale = X_train[ale_idx]

    # Compute ALE for all features, extract rules from SNR + Density
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
    #    (ALE extraction uses ale_idx subset; calibration uses the remainder
    #     to avoid overfitting the calibration to the same data)
    def engineer_features(X_data):
        X_eng = np.zeros((len(X_data), 2))
        for i, row in enumerate(X_data):
            snr = row[snr_idx]
            density = row[dens_idx]

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
        # Fallback: if too few calibration samples, use all training data
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
    }


# ============================================================
# Step 2: 5-Fold GroupKFold CV — Fair Comparison
# ============================================================
print("\n" + "=" * 60)
print("STEP 2: 5-Fold GroupKFold Cross-Validation (Fair Comparison)...")
print("=" * 60)

gkf = GroupKFold(n_splits=5)

xgb_params = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1
}

# Metrics storage
metrics = {
    # --- 2-feature models ---
    'cart_d6_2feat': {'r2': [], 'rmse': []},
    'cart_d4_2feat': {'r2': [], 'rmse': []},
    'linreg_2feat':  {'r2': [], 'rmse': []},
    'ale_rule':      {'r2': [], 'rmse': []},
    # --- 8-feature models (reference) ---
    'cart_d6_8feat': {'r2': [], 'rmse': []},
    'linreg_8feat':  {'r2': [], 'rmse': []},
}

for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups)):
    print(f"\n  --> Fold {fold + 1}/5")
    X_train, X_test = X[train_idx], X[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]

    # 2-feature subsets
    X_train_2 = X_train[:, TWO_FEAT_INDICES]
    X_test_2 = X_test[:, TWO_FEAT_INDICES]

    # ----------------------------------------------------------
    # 2-FEATURE MODELS
    # ----------------------------------------------------------

    # CART depth 6, 2 features
    cart_d6_2 = DecisionTreeRegressor(max_depth=6, random_state=42)
    cart_d6_2.fit(X_train_2, y_train)
    y_pred = cart_d6_2.predict(X_test_2)
    metrics['cart_d6_2feat']['r2'].append(r2_score(y_test, y_pred))
    metrics['cart_d6_2feat']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred)))
    print(f"      CART d=6 (2-feat): R² = {metrics['cart_d6_2feat']['r2'][-1]:.4f}")

    # CART depth 4, 2 features
    cart_d4_2 = DecisionTreeRegressor(max_depth=4, random_state=42)
    cart_d4_2.fit(X_train_2, y_train)
    y_pred = cart_d4_2.predict(X_test_2)
    metrics['cart_d4_2feat']['r2'].append(r2_score(y_test, y_pred))
    metrics['cart_d4_2feat']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred)))
    print(f"      CART d=4 (2-feat): R² = {metrics['cart_d4_2feat']['r2'][-1]:.4f}")

    # Linear Regression, 2 features
    lr_2 = LinearRegression()
    lr_2.fit(X_train_2, y_train)
    y_pred = lr_2.predict(X_test_2)
    metrics['linreg_2feat']['r2'].append(r2_score(y_test, y_pred))
    metrics['linreg_2feat']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred)))
    print(f"      LinReg   (2-feat): R² = {metrics['linreg_2feat']['r2'][-1]:.4f}")

    # ALE Rule (train XGBoost teacher on full 8 features, then distill)
    teacher = xgb.XGBRegressor(**xgb_params)
    teacher.fit(X_train, y_train)

    rule_info = extract_ale_rule(teacher, X_train, y_train, features_cols)
    X_test_eng = rule_info['engineer_fn'](X_test)
    y_pred_rule = (rule_info['coefs'][0] * X_test_eng[:, 0] +
                   rule_info['coefs'][1] * X_test_eng[:, 1] +
                   rule_info['intercept'])
    y_pred_rule = np.clip(y_pred_rule, 0.0, 1.0)
    metrics['ale_rule']['r2'].append(r2_score(y_test, y_pred_rule))
    metrics['ale_rule']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred_rule)))
    print(f"      ALE Rule (2-feat): R² = {metrics['ale_rule']['r2'][-1]:.4f}")

    # ----------------------------------------------------------
    # 8-FEATURE MODELS (reference)
    # ----------------------------------------------------------

    # CART depth 6, 8 features
    cart_d6_8 = DecisionTreeRegressor(max_depth=6, random_state=42)
    cart_d6_8.fit(X_train, y_train)
    y_pred = cart_d6_8.predict(X_test)
    metrics['cart_d6_8feat']['r2'].append(r2_score(y_test, y_pred))
    metrics['cart_d6_8feat']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred)))
    print(f"      CART d=6 (8-feat): R² = {metrics['cart_d6_8feat']['r2'][-1]:.4f}")

    # Linear Regression, 8 features
    lr_8 = LinearRegression()
    lr_8.fit(X_train, y_train)
    y_pred = lr_8.predict(X_test)
    metrics['linreg_8feat']['r2'].append(r2_score(y_test, y_pred))
    metrics['linreg_8feat']['rmse'].append(np.sqrt(mean_squared_error(y_test, y_pred)))
    print(f"      LinReg   (8-feat): R² = {metrics['linreg_8feat']['r2'][-1]:.4f}")

# ============================================================
# Step 3: Summary Table
# ============================================================
print("\n" + "=" * 60)
print("STEP 3: Summary — Fair ALE Comparison")
print("=" * 60)

print("\n  {:28s} {:>12s} {:>12s}".format("Model", "R² Mean±Std", "RMSE Mean±Std"))
print("  " + "-" * 54)

display_order = [
    ('cart_d6_2feat', 'CART d=6 (2-feat)'),
    ('cart_d4_2feat', 'CART d=4 (2-feat)'),
    ('linreg_2feat',  'LinReg (2-feat)'),
    ('ale_rule',      'ALE Rule (2-feat)'),
    ('cart_d6_8feat', 'CART d=6 (8-feat)'),
    ('linreg_8feat',  'LinReg (8-feat)'),
]

for key, label in display_order:
    r2_m = np.mean(metrics[key]['r2'])
    r2_s = np.std(metrics[key]['r2'])
    rmse_m = np.mean(metrics[key]['rmse'])
    rmse_s = np.std(metrics[key]['rmse'])
    print(f"  {label:28s} {r2_m:.4f}±{r2_s:.4f}  {rmse_m:.4f}±{rmse_s:.4f}")

# ============================================================
# Step 4: Save results JSON
# ============================================================
print("\n" + "=" * 60)
print("STEP 4: Saving results...")
print("=" * 60)


def build_entry(key):
    return {
        'r2_mean': round(float(np.mean(metrics[key]['r2'])), 4),
        'r2_std': round(float(np.std(metrics[key]['r2'])), 4),
        'rmse_mean': round(float(np.mean(metrics[key]['rmse'])), 4),
        'rmse_std': round(float(np.std(metrics[key]['rmse'])), 4),
        'per_fold_r2': [round(float(v), 4) for v in metrics[key]['r2']],
        'per_fold_rmse': [round(float(v), 4) for v in metrics[key]['rmse']],
    }


output = {
    'description': (
        'Fair comparison: 2-feature baselines (SNR_dB + Local_Density) vs ALE rule, '
        'plus 8-feature reference models. All evaluated with 5-Fold GroupKFold CV.'
    ),
    'two_features_used': ['SNR_dB', 'Local_Density'],
    'cv_protocol': 'GroupKFold(n_splits=5) grouped by Config_ID',
    'n_samples': int(len(y)),
    'two_feature_models': {
        'cart_d6_2feat': build_entry('cart_d6_2feat'),
        'cart_d4_2feat': build_entry('cart_d4_2feat'),
        'linreg_2feat': build_entry('linreg_2feat'),
        'ale_rule': build_entry('ale_rule'),
    },
    'eight_feature_models': {
        'cart_d6_8feat': build_entry('cart_d6_8feat'),
        'linreg_8feat': build_entry('linreg_8feat'),
    },
}

out_path = os.path.join(PROCESSED_DIR, 'fair_ale_comparison.json')
with open(out_path, 'w') as f:
    json.dump(output, f, indent=2)

print(f"  Saved to: {out_path}")
print("\nDone.")
