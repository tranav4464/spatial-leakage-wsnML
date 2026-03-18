"""
True Knowledge Distillation: Train student models on teacher soft labels.
Compares direct training (on ground truth y) vs KD training (on teacher predictions).

KD formulation:
    y_soft = alpha * y_true + (1 - alpha) * y_teacher
    Student is trained to predict y_soft.

Evaluated with 5-Fold GroupKFold CV.
"""
import numpy as np
import csv
import os
import json
from sklearn.model_selection import GroupKFold
from sklearn.metrics import r2_score
from sklearn.tree import DecisionTreeRegressor
from sklearn.linear_model import LinearRegression
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
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1
}

CART_DEPTHS = [2, 3, 4, 5, 6, 8]
ALPHAS = [0.0, 0.25, 0.5, 0.75, 1.0]  # 0=pure teacher labels, 1=pure ground truth


def main():
    print("=" * 60)
    print("KNOWLEDGE DISTILLATION: Soft Label Training")
    print("=" * 60)

    # Load data
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

    print(f"  Dataset: {len(y):,} rows\n")

    gkf = GroupKFold(n_splits=5)
    results = {}

    for depth in CART_DEPTHS:
        for alpha in ALPHAS:
            key = f"CART_d{depth}_alpha{alpha}"
            r2_scores = []

            for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups)):
                X_tr, X_te = X[train_idx], X[test_idx]
                y_tr, y_te = y[train_idx], y[test_idx]

                # Out-of-fold teacher predictions to avoid data leakage
                # (teacher predicting on its own training data gives trivially
                # accurate soft labels that collapse KD to standard training)
                y_teacher_oof = np.zeros_like(y_tr)
                inner_gkf = GroupKFold(n_splits=3)
                for i_tr, i_val in inner_gkf.split(X_tr, y_tr, groups[train_idx]):
                    teacher = xgb.XGBRegressor(**XGB_PARAMS)
                    teacher.fit(X_tr[i_tr], y_tr[i_tr])
                    y_teacher_oof[i_val] = teacher.predict(X_tr[i_val])

                # Soft labels using held-out teacher predictions
                y_soft = alpha * y_tr + (1 - alpha) * y_teacher_oof

                # Train student on soft labels
                student = DecisionTreeRegressor(max_depth=depth, random_state=42)
                student.fit(X_tr, y_soft)

                # Evaluate on ground truth
                y_pred = student.predict(X_te)
                r2_scores.append(r2_score(y_te, y_pred))

            r2_mean = np.mean(r2_scores)
            r2_std = np.std(r2_scores)
            results[key] = {
                'depth': depth,
                'alpha': alpha,
                'r2_mean': round(r2_mean, 4),
                'r2_std': round(r2_std, 4),
                'per_fold_r2': [round(v, 4) for v in r2_scores],
            }
            label = "ground truth" if alpha == 1.0 else \
                    "teacher only" if alpha == 0.0 else f"alpha={alpha}"
            print(f"  CART d={depth}, {label:15s}: R2 = {r2_mean:.4f} +/- {r2_std:.4f}")

        print()  # Blank line between depths

    # Save results
    out_path = os.path.join(PROCESSED_DIR, 'kd_results.json')
    with open(out_path, 'w') as f:
        json.dump(results, f, indent=2)
    print(f"\nResults saved to: {out_path}")

    # Summary: find best alpha per depth
    print("\n  Best alpha per depth:")
    for depth in CART_DEPTHS:
        best = max(
            [(a, results[f"CART_d{depth}_alpha{a}"]['r2_mean']) for a in ALPHAS],
            key=lambda x: x[1]
        )
        print(f"    Depth {depth}: alpha={best[0]}, R2={best[1]:.4f}")


if __name__ == '__main__':
    main()
