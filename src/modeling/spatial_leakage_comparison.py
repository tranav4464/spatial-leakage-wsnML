"""
Spatial Leakage Comparison: Naive KFold vs GroupKFold
=====================================================
Demonstrates the R-squared inflation caused by spatial leakage when using
standard KFold cross-validation on spatially correlated WSN data.

Compares:
  - Naive KFold(n_splits=5, shuffle=True, random_state=42)
      Rows from the same Config_ID can appear in both train and test,
      so the model memorises configuration-specific patterns.
  - GroupKFold(n_splits=5) grouped by Config_ID
      Entire configurations are held out, preventing spatial leakage.

Models evaluated: XGBoost, CART (depth 4), CART (depth 6), Linear Regression.
"""

import numpy as np
import csv
import os
import json

from sklearn.model_selection import KFold, GroupKFold
from sklearn.metrics import r2_score
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

# ============================================================
# Paths
# ============================================================
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
os.makedirs(PROCESSED_DIR, exist_ok=True)

# Fixed RNG for reproducibility (same seed as train_and_extract.py)
RNG = np.random.default_rng(42)

# ============================================================
# Step 1: Load dataset (same protocol as train_and_extract.py)
# ============================================================
print("=" * 65)
print("SPATIAL LEAKAGE COMPARISON")
print("=" * 65)
print("\nStep 1: Loading dataset...")

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
            y_val = row.get(target_col) or row.get('Detection_Accuracy')
            y_data.append(float(y_val))
            groups_data.append(int(row['Config_ID']))

X = np.array(X_data)
y = np.array(y_data)
groups = np.array(groups_data)

# Downsample to 150k with the same seeded RNG
if len(X) > 150000:
    idx = RNG.choice(len(X), 150000, replace=False)
    X = X[idx]
    y = y[idx]
    groups = groups[idx]

print(f"  Loaded {len(y):,} active rows, {len(features_cols)} features")
print(f"  Unique configurations (groups): {len(np.unique(groups))}")

# ============================================================
# Step 2: Define models (same hyper-parameters as train_and_extract.py)
# ============================================================
model_defs = {
    'xgboost': lambda: xgb.XGBRegressor(
        n_estimators=150, max_depth=6, learning_rate=0.1,
        subsample=0.8, colsample_bytree=0.8,
        random_state=42, n_jobs=-1,
    ),
    'cart_d4': lambda: DecisionTreeRegressor(max_depth=4, random_state=42),
    'cart_d6': lambda: DecisionTreeRegressor(max_depth=6, random_state=42),
    'linreg': lambda: LinearRegression(),
}

# ============================================================
# Step 3: Cross-validation under both schemes
# ============================================================
naive_kf = KFold(n_splits=5, shuffle=True, random_state=42)
group_kf = GroupKFold(n_splits=5)

cv_schemes = {
    'naive_kfold': naive_kf,
    'groupkfold': group_kf,
}

results = {scheme: {mname: [] for mname in model_defs} for scheme in cv_schemes}

for scheme_name, splitter in cv_schemes.items():
    label = "Naive KFold (leakage present)" if scheme_name == 'naive_kfold' \
            else "GroupKFold (leakage prevented)"
    print(f"\nStep 3: Running {label}...")
    print("-" * 65)

    # GroupKFold needs the groups argument; KFold ignores it
    if scheme_name == 'groupkfold':
        splits = list(splitter.split(X, y, groups))
    else:
        splits = list(splitter.split(X, y))

    for fold_idx, (train_idx, test_idx) in enumerate(splits):
        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        for mname, make_model in model_defs.items():
            model = make_model()
            model.fit(X_train, y_train)
            y_pred = model.predict(X_test)
            r2 = r2_score(y_test, y_pred)
            results[scheme_name][mname].append(r2)

        fold_summary = ", ".join(
            f"{mname}={results[scheme_name][mname][-1]:.4f}"
            for mname in model_defs
        )
        print(f"  Fold {fold_idx + 1}/5  R2: {fold_summary}")

# ============================================================
# Step 4: Summarise and compute inflation
# ============================================================
print("\n" + "=" * 65)
print("RESULTS SUMMARY")
print("=" * 65)

output = {
    'naive_kfold': {},
    'groupkfold': {},
    'inflation': {},
}

for scheme_name in cv_schemes:
    label = "Naive KFold" if scheme_name == 'naive_kfold' else "GroupKFold"
    print(f"\n  {label}:")
    for mname in model_defs:
        scores = results[scheme_name][mname]
        r2_mean = float(np.mean(scores))
        r2_std = float(np.std(scores))
        output[scheme_name][mname] = {
            'r2_mean': round(r2_mean, 6),
            'r2_std': round(r2_std, 6),
            'per_fold_r2': [round(v, 6) for v in scores],
        }
        print(f"    {mname:10s}:  R2 = {r2_mean:.4f} +/- {r2_std:.4f}")

print(f"\n  R2 Inflation (Naive - GroupKFold):")
for mname in model_defs:
    naive_mean = output['naive_kfold'][mname]['r2_mean']
    group_mean = output['groupkfold'][mname]['r2_mean']
    delta = round(naive_mean - group_mean, 6)
    output['inflation'][mname] = {'delta_r2': delta}
    direction = "+" if delta >= 0 else ""
    print(f"    {mname:10s}:  {direction}{delta:.4f}")

# ============================================================
# Step 5: Save JSON
# ============================================================
out_path = os.path.join(PROCESSED_DIR, 'spatial_leakage_results.json')
with open(out_path, 'w') as f:
    json.dump(output, f, indent=2)

print(f"\nResults saved to {out_path}")
print("Done.")
