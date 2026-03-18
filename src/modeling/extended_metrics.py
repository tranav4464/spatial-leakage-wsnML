"""
Extended Evaluation Metrics for WSN ML Models
==============================================
Computes RMSE, MAE, R², and link-zone F1-score (Good/Transitional/Bad)
for all models using the same 5-Fold GroupKFold protocol as
train_and_extract.py.

Saves results to data/processed/extended_metrics.json.
"""

import numpy as np
import csv
import os
import json

from sklearn.model_selection import GroupKFold
from sklearn.metrics import (
    r2_score,
    mean_squared_error,
    mean_absolute_error,
    f1_score,
    classification_report,
)
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
# Feature / target configuration
# ============================================================
features_cols = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]
target_col = 'PRR'  # Packet Reception Rate (formerly Detection_Accuracy)


# ============================================================
# Link-zone classification helper
# ============================================================
def classify_link_zone(prr_values):
    """Classify PRR values into link-quality zones.

    - Good:          PRR > 0.9
    - Transitional:  0.1 <= PRR <= 0.9
    - Bad:           PRR < 0.1

    Parameters
    ----------
    prr_values : array-like
        Packet Reception Rate values (0-1 range).

    Returns
    -------
    labels : np.ndarray of str
        Zone labels for each value.
    """
    prr = np.asarray(prr_values, dtype=float)
    labels = np.empty(prr.shape, dtype=object)
    labels[prr > 0.9] = 'Good'
    labels[prr < 0.1] = 'Bad'
    labels[(prr >= 0.1) & (prr <= 0.9)] = 'Transitional'
    return labels


# ============================================================
# Step 1: Load dataset (identical to train_and_extract.py)
# ============================================================
print("=" * 60)
print("Loading dataset...")
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

# Downsample to 150k (same seed as main pipeline)
if len(X) > 150000:
    idx = RNG.choice(len(X), 150000, replace=False)
    X = X[idx]
    y = y[idx]
    groups = groups[idx]

print(f"  Loaded {len(y):,} active rows, {len(features_cols)} features")
print(f"  Unique configurations: {len(np.unique(groups))}")

# ============================================================
# Step 2: Define models
# ============================================================
ZONE_LABELS = ['Good', 'Transitional', 'Bad']

model_defs = {
    'xgboost': lambda: xgb.XGBRegressor(
        n_estimators=150, max_depth=6, learning_rate=0.1,
        subsample=0.8, colsample_bytree=0.8,
        random_state=42, n_jobs=-1,
    ),
    'cart_depth4': lambda: DecisionTreeRegressor(max_depth=4, random_state=42),
    'cart_depth6': lambda: DecisionTreeRegressor(max_depth=6, random_state=42),
    'linear_regression': lambda: LinearRegression(),
}

# Per-fold accumulators (includes transitional-region metrics per Priority 3d)
fold_metrics = {
    name: {
        'r2': [], 'rmse': [], 'mae': [],
        'f1_macro': [], 'f1_weighted': [],
        'f1_per_class': {z: [] for z in ZONE_LABELS},
        'trans_rmse': [], 'trans_r2': [], 'trans_n': [],
    }
    for name in model_defs
}

# ============================================================
# Step 3: 5-Fold GroupKFold Cross-Validation
# ============================================================
print("\n" + "=" * 60)
print("5-Fold GroupKFold Cross-Validation with extended metrics...")
print("=" * 60)

gkf = GroupKFold(n_splits=5)

for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups)):
    print(f"\n  --> Fold {fold + 1}/5")
    X_train, X_test = X[train_idx], X[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]

    # True link-zone labels for this fold's test set
    y_test_zones = classify_link_zone(y_test)

    # Transitional region mask for this fold
    trans_mask = (y_test >= 0.1) & (y_test <= 0.9)

    for model_name, make_model in model_defs.items():
        model = make_model()
        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)

        # Regression metrics
        r2 = r2_score(y_test, y_pred)
        rmse = np.sqrt(mean_squared_error(y_test, y_pred))
        mae = mean_absolute_error(y_test, y_pred)

        fold_metrics[model_name]['r2'].append(r2)
        fold_metrics[model_name]['rmse'].append(rmse)
        fold_metrics[model_name]['mae'].append(mae)

        # Transitional-region-only metrics (Priority 3d)
        if trans_mask.sum() > 10:
            t_r2 = r2_score(y_test[trans_mask], y_pred[trans_mask])
            t_rmse = np.sqrt(mean_squared_error(y_test[trans_mask], y_pred[trans_mask]))
            fold_metrics[model_name]['trans_r2'].append(t_r2)
            fold_metrics[model_name]['trans_rmse'].append(t_rmse)
        else:
            fold_metrics[model_name]['trans_r2'].append(float('nan'))
            fold_metrics[model_name]['trans_rmse'].append(float('nan'))
        fold_metrics[model_name]['trans_n'].append(int(trans_mask.sum()))

        # Link-zone classification metrics
        y_pred_zones = classify_link_zone(y_pred)

        macro_f1 = f1_score(
            y_test_zones, y_pred_zones,
            labels=ZONE_LABELS, average='macro', zero_division=0,
        )
        weighted_f1 = f1_score(
            y_test_zones, y_pred_zones,
            labels=ZONE_LABELS, average='weighted', zero_division=0,
        )
        fold_metrics[model_name]['f1_macro'].append(macro_f1)
        fold_metrics[model_name]['f1_weighted'].append(weighted_f1)

        # Per-class F1
        per_class_f1 = f1_score(
            y_test_zones, y_pred_zones,
            labels=ZONE_LABELS, average=None, zero_division=0,
        )
        for i, zone in enumerate(ZONE_LABELS):
            fold_metrics[model_name]['f1_per_class'][zone].append(per_class_f1[i])

        print(f"    {model_name:20s}  R²={r2:.4f}  RMSE={rmse:.4f}  "
              f"MAE={mae:.4f}  F1_macro={macro_f1:.4f}  F1_wt={weighted_f1:.4f}")

    # Print detailed classification report for best model (XGBoost) on last fold
    if fold == 4:
        print("\n  Classification report (XGBoost, fold 5):")
        xgb_model = model_defs['xgboost']()
        xgb_model.fit(X_train, y_train)
        y_pred_xgb = xgb_model.predict(X_test)
        xgb_zones_pred = classify_link_zone(y_pred_xgb)
        report = classification_report(
            y_test_zones, xgb_zones_pred,
            labels=ZONE_LABELS, zero_division=0,
        )
        print(report)

# ============================================================
# Step 4: Aggregate and save results
# ============================================================
print("\n" + "=" * 60)
print("Aggregated Results (Mean +/- Std across 5 folds)")
print("=" * 60)

results = {}

for model_name in model_defs:
    fm = fold_metrics[model_name]

    trans_rmse_vals = [v for v in fm['trans_rmse'] if not np.isnan(v)]
    trans_r2_vals = [v for v in fm['trans_r2'] if not np.isnan(v)]

    entry = {
        'r2_mean':         round(float(np.mean(fm['r2'])), 4),
        'r2_std':          round(float(np.std(fm['r2'])), 4),
        'rmse_mean':       round(float(np.mean(fm['rmse'])), 4),
        'rmse_std':        round(float(np.std(fm['rmse'])), 4),
        'mae_mean':        round(float(np.mean(fm['mae'])), 4),
        'mae_std':         round(float(np.std(fm['mae'])), 4),
        'f1_macro_mean':   round(float(np.mean(fm['f1_macro'])), 4),
        'f1_macro_std':    round(float(np.std(fm['f1_macro'])), 4),
        'f1_weighted_mean': round(float(np.mean(fm['f1_weighted'])), 4),
        'f1_weighted_std': round(float(np.std(fm['f1_weighted'])), 4),
        'f1_per_class': {
            zone: round(float(np.mean(fm['f1_per_class'][zone])), 4)
            for zone in ZONE_LABELS
        },
    }
    if trans_rmse_vals:
        entry['trans_rmse_mean'] = round(float(np.mean(trans_rmse_vals)), 4)
        entry['trans_r2_mean'] = round(float(np.mean(trans_r2_vals)), 4)
        entry['trans_n_mean'] = int(np.mean(fm['trans_n']))

    results[model_name] = entry

    print(f"\n  {model_name}:")
    print(f"    R²          = {entry['r2_mean']:.4f} +/- {entry['r2_std']:.4f}")
    print(f"    RMSE        = {entry['rmse_mean']:.4f} +/- {entry['rmse_std']:.4f}")
    print(f"    MAE         = {entry['mae_mean']:.4f} +/- {entry['mae_std']:.4f}")
    print(f"    F1 (macro)  = {entry['f1_macro_mean']:.4f} +/- {entry['f1_macro_std']:.4f}")
    print(f"    F1 (weight) = {entry['f1_weighted_mean']:.4f} +/- {entry['f1_weighted_std']:.4f}")
    print(f"    F1 per-class: Good={entry['f1_per_class']['Good']:.4f}  "
          f"Trans={entry['f1_per_class']['Transitional']:.4f}  "
          f"Bad={entry['f1_per_class']['Bad']:.4f}")

# Save to JSON
output_path = os.path.join(PROCESSED_DIR, 'extended_metrics.json')
with open(output_path, 'w') as f:
    json.dump(results, f, indent=2)

print(f"\nResults saved to {output_path}")
print("Done.")
