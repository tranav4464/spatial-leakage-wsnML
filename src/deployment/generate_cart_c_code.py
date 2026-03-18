"""
Export sklearn DecisionTreeRegressor to C if/else chains.
Generates C code for CART trees at multiple depths for Pareto frontier analysis.
"""
import os
import json
import numpy as np
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import GroupKFold
from sklearn.metrics import r2_score
import csv

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
FIRMWARE_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'firmware')
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')

FEATURE_COLS = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]
FEATURE_NAMES_C = [
    'tx_power', 'distance', 'density', 'rssi',
    'noise', 'snr', 'init_energy', 'residual_energy',
]

CART_DEPTHS = [2, 3, 4, 5, 6, 8, 10]
RNG = np.random.default_rng(42)


def tree_to_c(tree, feature_names, indent=4):
    """Recursively convert a sklearn decision tree to C if/else code."""
    tree_ = tree.tree_
    feature_name = [
        feature_names[i] if i >= 0 else "undefined"
        for i in tree_.feature
    ]

    lines = []

    def recurse(node, depth):
        prefix = " " * (indent * depth)
        if tree_.feature[node] >= 0:
            name = feature_name[node]
            threshold = tree_.threshold[node]
            lines.append(f"{prefix}if (input[{tree_.feature[node]}] <= {threshold:.6f}f) {{")
            recurse(tree_.children_left[node], depth + 1)
            lines.append(f"{prefix}}} else {{")
            recurse(tree_.children_right[node], depth + 1)
            lines.append(f"{prefix}}}")
        else:
            value = tree_.value[node][0][0]
            lines.append(f"{prefix}return {value:.6f}f;")

    recurse(0, 1)
    return "\n".join(lines)


def generate_cart_c(depth, tree_model):
    """Generate a complete C file for a CART model at a given depth."""
    c_body = tree_to_c(tree_model, FEATURE_NAMES_C)

    return f"""/*
 * CART Decision Tree -- Depth {depth}
 * Auto-generated from sklearn DecisionTreeRegressor
 * Target: PRR (Packet Reception Rate) prediction
 */

float predict_cart(float *input) {{
{c_body}
}}

/* Minimal main for size measurement */
volatile float result;
int main(void) {{
    float input[8] = {{-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f}};
    result = predict_cart(input);
    return 0;
}}
"""


def main():
    print("=" * 60)
    print("CART C Code Generation + Cross-Validated Evaluation")
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

    print(f"  Dataset: {len(y):,} rows")

    results = {}
    gkf = GroupKFold(n_splits=5)

    for depth in CART_DEPTHS:
        print(f"\n  Depth {depth}:")
        r2_scores = []
        for fold, (train_idx, test_idx) in enumerate(gkf.split(X, y, groups)):
            tree = DecisionTreeRegressor(max_depth=depth, random_state=42)
            tree.fit(X[train_idx], y[train_idx])
            y_pred = tree.predict(X[test_idx])
            r2_scores.append(r2_score(y[test_idx], y_pred))

        r2_mean = np.mean(r2_scores)
        r2_std = np.std(r2_scores)
        print(f"    R2 = {r2_mean:.4f} +/- {r2_std:.4f}")

        # Train on full data for C code generation
        final_tree = DecisionTreeRegressor(max_depth=depth, random_state=42)
        final_tree.fit(X, y)

        cart_dir = os.path.join(FIRMWARE_DIR, f'cart_depth{depth}')
        os.makedirs(cart_dir, exist_ok=True)
        c_code = generate_cart_c(depth, final_tree)
        c_path = os.path.join(cart_dir, 'main.c')
        with open(c_path, 'w') as f:
            f.write(c_code)
        print(f"    Written: {c_path} ({os.path.getsize(c_path):,} bytes)")

        results[f'cart_depth{depth}'] = {
            'r2_mean': round(r2_mean, 4),
            'r2_std': round(r2_std, 4),
            'per_fold_r2': [round(v, 4) for v in r2_scores],
        }

    # Save results
    out_path = os.path.join(PROCESSED_DIR, 'cart_sweep_results.json')
    with open(out_path, 'w') as f:
        json.dump(results, f, indent=2)
    print(f"\n  Results saved to: {out_path}")


if __name__ == '__main__':
    main()
