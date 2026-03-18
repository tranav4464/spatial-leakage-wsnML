"""
Physical Testbed Validation Pipeline
======================================
Validates the simulation's architectural claim on FIT IoT-LAB physical data:
  CART Depth 4-6 > Linear Regression

Uses Leave-One-Group-Out CV (49 folds, one per dst_node) to prevent spatial
leakage and provide adequate statistical power for Wilcoxon signed-rank tests.
  - Model suite: XGBoost, CART (depths 2-10), LinReg
  - Traditional baselines: RSSI-binned (ETX-like), WMEWMA-like
  - ARM Cortex-M3 compiled size measurement

Input:  data/processed/testbed_dataset.csv
Output: data/processed/testbed_results.json
        firmware/testbed_cart_depth{N}/main.c (C code for testbed models)
"""
import os
import json
import csv
import subprocess
import numpy as np
from scipy.stats import wilcoxon
from sklearn.model_selection import GroupKFold, LeaveOneGroupOut
from sklearn.metrics import mean_squared_error, r2_score, f1_score
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
DATASET_PATH = os.path.join(ROOT_DIR, 'data', 'processed', 'testbed_dataset.csv')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
FIRMWARE_DIR = os.path.join(ROOT_DIR, 'firmware')
RESULTS_DIR = os.path.join(ROOT_DIR, 'results', 'tables')
os.makedirs(PROCESSED_DIR, exist_ok=True)
os.makedirs(RESULTS_DIR, exist_ok=True)

# Feature definitions for testbed (4 features vs simulation's 8)
FEATURE_COLS = ['Distance_m', 'RSSI_mean', 'LQI_mean', 'Local_Density']
FEATURE_NAMES_C = ['distance', 'rssi', 'lqi', 'density']
TARGET_COL = 'PRR'
GROUP_COL = 'dst_node'  # Group by receiver for spatial leakage prevention

RNG = np.random.default_rng(42)

CART_DEPTHS = [2, 3, 4, 5, 6, 8, 10]

XGB_PARAMS = {
    'n_estimators': 150, 'max_depth': 6, 'learning_rate': 0.1,
    'subsample': 0.8, 'colsample_bytree': 0.8, 'random_state': 42, 'n_jobs': -1,
}

# ARM cross-compiler (same as benchmark_size.py)
ARM_CC = r'C:\msys64\mingw64\bin\arm-none-eabi-gcc.exe'
ARM_SIZE = r'C:\msys64\mingw64\bin\arm-none-eabi-size.exe'
ARM_CFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-mfloat-abi=soft', '-Os', '-Wall',
              '-ffreestanding', '-nostdlib', '-c']

for path_candidate in [ARM_CC, '/c/msys64/mingw64/bin/arm-none-eabi-gcc.exe',
                        'arm-none-eabi-gcc']:
    try:
        result = subprocess.run([path_candidate, '--version'],
                                capture_output=True, text=True)
        if result.returncode == 0:
            ARM_CC = path_candidate
            ARM_SIZE = path_candidate.replace('gcc', 'size')
            break
    except FileNotFoundError:
        continue


# ============================================================
# Traditional LQE baselines (Reviewer W5: ETX/WMEWMA comparison)
# ============================================================

class RSSIBinnedEstimator:
    """ETX-like baseline: bin RSSI, predict training-set mean PRR per bin.

    This approximates how ETX works operationally — estimating link quality
    from historical delivery statistics binned by signal strength.
    """
    def __init__(self, n_bins=20, rssi_col_idx=1):
        self.n_bins = n_bins
        self.rssi_idx = rssi_col_idx
        self.bin_edges = None
        self.bin_means = None
        self.global_mean = 0.5

    def fit(self, X, y):
        rssi = X[:, self.rssi_idx]
        self.global_mean = float(np.mean(y))
        self.bin_edges = np.percentile(rssi, np.linspace(0, 100, self.n_bins + 1))
        self.bin_edges[0] -= 1
        self.bin_edges[-1] += 1
        self.bin_means = np.full(self.n_bins, self.global_mean)
        for i in range(self.n_bins):
            mask = (rssi >= self.bin_edges[i]) & (rssi < self.bin_edges[i + 1])
            if mask.sum() > 0:
                self.bin_means[i] = float(np.mean(y[mask]))
        return self

    def predict(self, X):
        rssi = X[:, self.rssi_idx]
        preds = np.full(len(rssi), self.global_mean)
        for i in range(self.n_bins):
            mask = (rssi >= self.bin_edges[i]) & (rssi < self.bin_edges[i + 1])
            preds[mask] = self.bin_means[i]
        return preds


class WMEWMAEstimator:
    """WMEWMA-like baseline: RSSI + LQI combined binned estimator.

    Approximates the Window Mean with EWMA approach by using
    both RSSI and LQI to create a 2D binned PRR lookup. In steady-state,
    WMEWMA converges to the conditional mean E[PRR | RSSI, LQI], which
    is what this 2D histogram estimator computes.
    """
    def __init__(self, n_bins_rssi=10, n_bins_lqi=5, rssi_idx=1, lqi_idx=2):
        self.n_rssi = n_bins_rssi
        self.n_lqi = n_bins_lqi
        self.rssi_idx = rssi_idx
        self.lqi_idx = lqi_idx
        self.rssi_edges = None
        self.lqi_edges = None
        self.grid_means = None
        self.global_mean = 0.5

    def fit(self, X, y):
        rssi = X[:, self.rssi_idx]
        lqi = X[:, self.lqi_idx]
        self.global_mean = float(np.mean(y))
        self.rssi_edges = np.percentile(rssi, np.linspace(0, 100, self.n_rssi + 1))
        self.rssi_edges[0] -= 1
        self.rssi_edges[-1] += 1
        self.lqi_edges = np.percentile(lqi, np.linspace(0, 100, self.n_lqi + 1))
        self.lqi_edges[0] -= 1
        self.lqi_edges[-1] += 1
        self.grid_means = np.full((self.n_rssi, self.n_lqi), self.global_mean)
        for i in range(self.n_rssi):
            r_mask = (rssi >= self.rssi_edges[i]) & (rssi < self.rssi_edges[i + 1])
            for j in range(self.n_lqi):
                l_mask = (lqi >= self.lqi_edges[j]) & (lqi < self.lqi_edges[j + 1])
                mask = r_mask & l_mask
                if mask.sum() > 0:
                    self.grid_means[i, j] = float(np.mean(y[mask]))
        return self

    def predict(self, X):
        rssi = X[:, self.rssi_idx]
        lqi = X[:, self.lqi_idx]
        preds = np.full(len(rssi), self.global_mean)
        for i in range(self.n_rssi):
            r_mask = (rssi >= self.rssi_edges[i]) & (rssi < self.rssi_edges[i + 1])
            for j in range(self.n_lqi):
                l_mask = (lqi >= self.lqi_edges[j]) & (lqi < self.lqi_edges[j + 1])
                mask = r_mask & l_mask
                if mask.any():
                    preds[mask] = self.grid_means[i, j]
        return preds


# ============================================================
# C code generation (adapted for 4-feature testbed models)
# ============================================================

def tree_to_c(tree, indent=4):
    """Recursively convert a sklearn decision tree to C if/else code."""
    tree_ = tree.tree_
    lines = []

    def recurse(node, depth):
        prefix = " " * (indent * depth)
        if tree_.feature[node] >= 0:
            threshold = tree_.threshold[node]
            lines.append(f"{prefix}if (input[{tree_.feature[node]}] <= "
                         f"{threshold:.6f}f) {{")
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
    """Generate C file for a testbed CART model."""
    c_body = tree_to_c(tree_model)
    n_features = len(FEATURE_COLS)
    sample_vals = "5.0f, -82.0f, 200.0f, 10.0f"  # distance, rssi, lqi, density

    return f"""/*
 * CART Decision Tree -- Depth {depth} (Testbed Validation)
 * Auto-generated from sklearn DecisionTreeRegressor
 * Features: {', '.join(FEATURE_NAMES_C)}
 * Target: PRR (Packet Reception Rate) prediction
 */

float predict_cart(float *input) {{
{c_body}
}}

/* Minimal main for size measurement */
volatile float result;
int main(void) {{
    float input[{n_features}] = {{{sample_vals}}};
    result = predict_cart(input);
    return 0;
}}
"""


def compile_and_measure(c_path, o_path):
    """Compile C file to ARM and measure .text size."""
    cmd = [ARM_CC] + ARM_CFLAGS + [c_path, '-o', o_path]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"    Compilation error: {result.stderr[:200]}")
        return 0

    result = subprocess.run([ARM_SIZE, o_path], capture_output=True, text=True)
    if result.returncode == 0:
        lines = result.stdout.strip().split('\n')
        if len(lines) >= 2:
            parts = lines[1].split()
            if len(parts) >= 1:
                return int(parts[0])  # .text size
    return 0


def classify_link_zone(prr):
    """Classify PRR into link zones for F1 computation.

    Thresholds (Zuniga & Krishnamachari 2004):
      Good:          PRR > 0.9
      Transitional:  0.1 <= PRR <= 0.9
      Bad:           PRR < 0.1
    """
    if prr > 0.9:
        return 'Good'
    elif prr >= 0.1:
        return 'Transitional'
    else:
        return 'Bad'


# ============================================================
# Main Pipeline
# ============================================================

def main():
    print("=" * 60)
    print("PHYSICAL TESTBED VALIDATION PIPELINE")
    print("=" * 60)

    # ---- Step 1: Load testbed dataset ----
    print("\nStep 1: Loading testbed dataset...")
    if not os.path.exists(DATASET_PATH):
        print(f"  ERROR: {DATASET_PATH} not found.")
        print(f"  Run process_testbed.py first.")
        return

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

    # Encode string group labels to integers for GroupKFold
    unique_groups = np.unique(groups)
    group_map = {g: i for i, g in enumerate(unique_groups)}
    groups_int = np.array([group_map[g] for g in groups])

    print(f"  Loaded {len(y):,} records, {len(FEATURE_COLS)} features")
    print(f"  Unique RX nodes (groups): {len(unique_groups)}")
    print(f"  PRR range: [{y.min():.3f}, {y.max():.3f}], mean={y.mean():.3f}")

    # Use Leave-One-Group-Out CV (49 folds — one per dst_node)
    # This provides adequate statistical power for Wilcoxon tests
    # (n=49 vs n=5 with GroupKFold), addressing the key limitation.
    n_splits = len(unique_groups)

    # ---- Step 2: Cross-Validation ----
    print(f"\nStep 2: Leave-One-Group-Out CV ({n_splits} folds, one per dst_node)...")
    logo = LeaveOneGroupOut()

    # Metric accumulators: full dataset + transitional region only (W11, Priority 3d/5a)
    metric_keys = ['r2', 'rmse', 'mae', 'f1_weighted', 'trans_rmse', 'trans_r2', 'trans_n',
                    'mae_good', 'mae_trans', 'mae_bad']

    metrics = {
        'xgboost': {k: [] for k in metric_keys},
        'linreg': {k: [] for k in metric_keys},
        'rssi_binned': {k: [] for k in metric_keys},
        'wmewma': {k: [] for k in metric_keys},
        'mean_baseline': {k: [] for k in metric_keys},
    }
    for d in CART_DEPTHS:
        metrics[f'cart_d{d}'] = {k: [] for k in metric_keys}

    for fold, (train_idx, test_idx) in enumerate(logo.split(X, y, groups_int)):
        held_out_group = unique_groups[groups_int[test_idx[0]]]
        print(f"\n  --> Fold {fold + 1}/{n_splits} (held-out node: {held_out_group})")
        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        # True link zones for F1
        zones_true = [classify_link_zone(p) for p in y_test]
        zone_labels = ['Bad', 'Transitional', 'Good']

        # Transitional region mask (PRR in [0.1, 0.9]) for this fold
        trans_mask = (y_test >= 0.1) & (y_test <= 0.9)

        def eval_model(name, y_pred):
            y_pred_clipped = np.clip(y_pred, 0, 1)
            r2 = r2_score(y_test, y_pred_clipped)
            rmse = np.sqrt(mean_squared_error(y_test, y_pred_clipped))
            mae = np.mean(np.abs(y_test - y_pred_clipped))
            zones_pred = [classify_link_zone(p) for p in y_pred_clipped]
            f1 = f1_score(zones_true, zones_pred, labels=zone_labels,
                          average='weighted', zero_division=0)
            metrics[name]['r2'].append(r2)
            metrics[name]['rmse'].append(rmse)
            metrics[name]['mae'].append(mae)
            metrics[name]['f1_weighted'].append(f1)

            # Transitional-region-only metrics (Reviewer W11, Priority 5a)
            if trans_mask.sum() > 10:
                t_r2 = r2_score(y_test[trans_mask], y_pred_clipped[trans_mask])
                t_rmse = np.sqrt(mean_squared_error(
                    y_test[trans_mask], y_pred_clipped[trans_mask]))
                metrics[name]['trans_r2'].append(t_r2)
                metrics[name]['trans_rmse'].append(t_rmse)
            else:
                metrics[name]['trans_r2'].append(float('nan'))
                metrics[name]['trans_rmse'].append(float('nan'))
            metrics[name]['trans_n'].append(int(trans_mask.sum()))

            # Stratified MAE by PRR zone (reviewer: R² inappropriate for bimodal data)
            good_mask_test = y_test > 0.9
            bad_mask_test = y_test < 0.1
            for zone_name, zone_mask in [('good', good_mask_test),
                                          ('trans', trans_mask),
                                          ('bad', bad_mask_test)]:
                if zone_mask.sum() > 0:
                    metrics[name][f'mae_{zone_name}'].append(
                        float(np.mean(np.abs(y_test[zone_mask] - y_pred_clipped[zone_mask]))))
                else:
                    metrics[name][f'mae_{zone_name}'].append(float('nan'))

            print(f"      {name:15s}: R²={r2:.4f}  RMSE={rmse:.4f}  F1w={f1:.4f}")

        # XGBoost
        model_xgb = xgb.XGBRegressor(**XGB_PARAMS)
        model_xgb.fit(X_train, y_train)
        eval_model('xgboost', model_xgb.predict(X_test))

        # CART at multiple depths
        for depth in CART_DEPTHS:
            tree = DecisionTreeRegressor(max_depth=depth, random_state=42)
            tree.fit(X_train, y_train)
            eval_model(f'cart_d{depth}', tree.predict(X_test))

        # Linear Regression
        lr = LinearRegression()
        lr.fit(X_train, y_train)
        eval_model('linreg', lr.predict(X_test))

        # --- Traditional LQE Baselines (Reviewer W5) ---

        # RSSI-binned estimator (ETX-like): bin RSSI, predict mean PRR per bin
        rssi_est = RSSIBinnedEstimator(n_bins=20, rssi_col_idx=1)
        rssi_est.fit(X_train, y_train)
        eval_model('rssi_binned', rssi_est.predict(X_test))

        # WMEWMA-like: 2D RSSI x LQI binned estimator
        wmewma_est = WMEWMAEstimator(rssi_idx=1, lqi_idx=2)
        wmewma_est.fit(X_train, y_train)
        eval_model('wmewma', wmewma_est.predict(X_test))

        # Mean baseline (constant predictor = training mean PRR)
        mean_pred = np.full(len(y_test), np.mean(y_train))
        eval_model('mean_baseline', mean_pred)

    # ---- Step 3: Summary ----
    print("\n" + "=" * 60)
    print("Step 3: Results Summary")
    print("=" * 60)

    print(f"\n  {'Model':<18} {'R² Mean±Std':>14} {'RMSE':>10} {'F1w':>10}"
          f" {'Trans_RMSE':>11} {'Trans_R²':>10}")
    print("  " + "-" * 76)

    # Order: XGBoost, CART depths, LinReg, traditional baselines
    display_order = ['xgboost']
    display_order += [f'cart_d{d}' for d in CART_DEPTHS]
    display_order += ['linreg', 'rssi_binned', 'wmewma', 'mean_baseline']

    for name in display_order:
        m = metrics[name]
        r2_m, r2_s = np.mean(m['r2']), np.std(m['r2'])
        rmse_m = np.mean(m['rmse'])
        f1_m = np.mean(m['f1_weighted'])
        trans_rmse_vals = [v for v in m['trans_rmse'] if not np.isnan(v)]
        trans_r2_vals = [v for v in m['trans_r2'] if not np.isnan(v)]
        t_rmse = np.mean(trans_rmse_vals) if trans_rmse_vals else float('nan')
        t_r2 = np.mean(trans_r2_vals) if trans_r2_vals else float('nan')
        print(f"  {name:<18} {r2_m:.4f}±{r2_s:.4f}  {rmse_m:>10.4f}  {f1_m:>10.4f}"
              f"  {t_rmse:>10.4f}  {t_r2:>10.4f}")

    # ---- Step 4: Generate C code and measure sizes ----
    print("\n" + "=" * 60)
    print("Step 4: C Code Generation + ARM Compilation")
    print("=" * 60)

    # Train final models on all data for C code export
    size_results = []

    for depth in CART_DEPTHS:
        tree = DecisionTreeRegressor(max_depth=depth, random_state=42)
        tree.fit(X, y)

        dir_name = f'testbed_cart_depth{depth}'
        cart_dir = os.path.join(FIRMWARE_DIR, dir_name)
        os.makedirs(cart_dir, exist_ok=True)

        c_code = generate_cart_c(depth, tree)
        c_path = os.path.join(cart_dir, 'main.c')
        with open(c_path, 'w') as f:
            f.write(c_code)

        # Compile and measure
        o_path = os.path.join(cart_dir, 'main.arm.o')
        text_size = compile_and_measure(c_path, o_path)

        m = metrics[f'cart_d{depth}']
        size_results.append({
            'model': f'CART_Depth{depth}_Testbed',
            'arm_text_bytes': text_size,
            'r2_mean': round(float(np.mean(m['r2'])), 4),
            'r2_std': round(float(np.std(m['r2'])), 4),
        })
        print(f"  CART d={depth}: .text={text_size:,}B, "
              f"R²={np.mean(m['r2']):.4f}")

    # ---- Step 5: Spatial leakage check ----
    print("\n" + "=" * 60)
    print("Step 5: Spatial Leakage Check (Naive KFold vs GroupKFold)")
    print("=" * 60)

    from sklearn.model_selection import KFold
    naive_kf = KFold(n_splits=5, shuffle=True, random_state=42)
    leakage_check = {}

    for name, ModelClass, params in [
        ('xgboost', xgb.XGBRegressor, XGB_PARAMS),
        ('cart_d6', DecisionTreeRegressor, {'max_depth': 6, 'random_state': 42}),
        ('linreg', LinearRegression, {}),
    ]:
        naive_r2 = []
        for train_idx, test_idx in naive_kf.split(X, y):
            model = ModelClass(**params)
            model.fit(X[train_idx], y[train_idx])
            y_pred = np.clip(model.predict(X[test_idx]), 0, 1)
            naive_r2.append(r2_score(y[test_idx], y_pred))

        grouped_r2 = metrics[name]['r2']
        delta = np.mean(naive_r2) - np.mean(grouped_r2)
        leakage_check[name] = {
            'naive_r2_mean': round(float(np.mean(naive_r2)), 4),
            'grouped_r2_mean': round(float(np.mean(grouped_r2)), 4),
            'inflation_delta': round(float(delta), 4),
        }
        print(f"  {name:12s}: Naive={np.mean(naive_r2):.4f}  "
              f"Grouped={np.mean(grouped_r2):.4f}  "
              f"Delta={delta:+.4f}")

    # ---- Step 5b: Statistical Significance Tests (Priority 3c) ----
    print("\n" + "=" * 60)
    print("Step 5b: Wilcoxon Signed-Rank Tests (Bonferroni corrected)")
    print("=" * 60)

    stat_pairs = [
        ('cart_d2', 'cart_d3'), ('cart_d3', 'linreg'),
        ('cart_d3', 'rssi_binned'),
        ('cart_d3', 'wmewma'), ('xgboost', 'cart_d3'),
        ('rssi_binned', 'wmewma'), ('linreg', 'rssi_binned'),
        ('cart_d3', 'mean_baseline'),
    ]
    n_comparisons = len(stat_pairs)
    wilcoxon_results = {}

    for m1, m2 in stat_pairs:
        r2_1 = np.array(metrics[m1]['r2'])
        r2_2 = np.array(metrics[m2]['r2'])
        try:
            stat, pval = wilcoxon(r2_1, r2_2)
            pval_corrected = min(pval * n_comparisons, 1.0)  # Bonferroni
            diff = np.mean(r2_1) - np.mean(r2_2)
            # Cohen's d effect size
            pooled_std = np.sqrt((np.std(r2_1)**2 + np.std(r2_2)**2) / 2)
            cohens_d = diff / pooled_std if pooled_std > 1e-10 else float('inf')
            sig = ("***" if pval_corrected < 0.001 else
                   "**" if pval_corrected < 0.01 else
                   "*" if pval_corrected < 0.05 else "ns")
            print(f"  {m1} vs {m2}: "
                  f"delta={diff:+.4f}  p={pval:.4f} (corrected={pval_corrected:.4f}) "
                  f"d={cohens_d:.2f} {sig}")
            wilcoxon_results[f'{m1}_vs_{m2}'] = {
                'delta_r2': round(float(diff), 4),
                'p_value': round(float(pval), 4),
                'p_bonferroni': round(float(pval_corrected), 4),
                'cohens_d': round(float(cohens_d), 2),
                'significant': sig != 'ns',
            }
        except ValueError as e:
            print(f"  {m1} vs {m2}: {e}")
            wilcoxon_results[f'{m1}_vs_{m2}'] = {
                'error': str(e), 'significant': False,
            }

    print(f"\n  Note: {n_comparisons} comparisons, Bonferroni alpha = "
          f"{0.05/n_comparisons:.4f}")
    print(f"  Minimum achievable p with {n_splits} folds: "
          f"{1/2**n_splits:.4f}")

    # ---- Step 6: Save results ----
    print("\n" + "=" * 60)
    print("Step 6: Saving Results")
    print("=" * 60)

    def build_entry(name):
        m = metrics[name]
        trans_rmse_vals = [v for v in m['trans_rmse'] if not np.isnan(v)]
        trans_r2_vals = [v for v in m['trans_r2'] if not np.isnan(v)]
        entry = {
            'r2_mean': round(float(np.mean(m['r2'])), 4),
            'r2_std': round(float(np.std(m['r2'])), 4),
            'rmse_mean': round(float(np.mean(m['rmse'])), 4),
            'rmse_std': round(float(np.std(m['rmse'])), 4),
            'mae_mean': round(float(np.mean(m['mae'])), 4),
            'f1_weighted_mean': round(float(np.mean(m['f1_weighted'])), 4),
            'per_fold_r2': [round(float(v), 4) for v in m['r2']],
        }
        if trans_rmse_vals:
            entry['trans_rmse_mean'] = round(float(np.mean(trans_rmse_vals)), 4)
            entry['trans_r2_mean'] = round(float(np.mean(trans_r2_vals)), 4)
            entry['trans_n_mean'] = int(np.mean(m['trans_n']))
        # Stratified MAE by PRR zone
        for zone in ['good', 'trans', 'bad']:
            vals = [v for v in m[f'mae_{zone}'] if not np.isnan(v)]
            if vals:
                entry[f'mae_{zone}_mean'] = round(float(np.mean(vals)), 4)
        return entry

    # Transitional region summary
    trans_total = sum(1 for yi in y if 0.1 <= yi <= 0.9)
    trans_pct = 100.0 * trans_total / len(y)

    output = {
        'description': (
            'Physical testbed validation on FIT IoT-LAB data. '
            '4 features: [Distance_m, RSSI_mean, LQI_mean, Local_Density] -> PRR. '
            'Local_Density reconstructed via Euclidean spatial reconstruction '
            '(R_int = 2*R_tx, active node filter). '
            'Includes traditional LQE baselines (RSSI-binned/ETX-like, WMEWMA-like) '
            'and transitional-region-only metrics.'
        ),
        'features': FEATURE_COLS,
        'target': TARGET_COL,
        'cv_protocol': f'LeaveOneGroupOut ({n_splits} folds) grouped by {GROUP_COL}',
        'n_samples': int(len(y)),
        'n_groups': int(len(unique_groups)),
        'transitional_region': {
            'definition': 'PRR in [0.1, 0.9]',
            'n_samples': trans_total,
            'pct_of_total': round(trans_pct, 1),
        },
        'models': {name: build_entry(name) for name in display_order},
        'arm_sizes': size_results,
        'spatial_leakage_check': leakage_check,
        'wilcoxon_tests': wilcoxon_results,
    }

    site = os.environ.get('TESTBED_SITE', '')
    results_name = f'testbed_results_{site}.json' if site else 'testbed_results.json'
    out_path = os.path.join(PROCESSED_DIR, results_name)
    with open(out_path, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"  Saved: {out_path}")

    # ---- Step 7: Architectural claim verification ----
    print("\n" + "=" * 60)
    print("Step 7: Architectural Claim Verification")
    print("=" * 60)

    cart_d6_r2 = np.mean(metrics['cart_d6']['r2'])
    lr_r2 = np.mean(metrics['linreg']['r2'])
    xgb_r2 = np.mean(metrics['xgboost']['r2'])

    print(f"\n  XGBoost (teacher):  R² = {xgb_r2:.4f}")
    print(f"  CART Depth 6:       R² = {cart_d6_r2:.4f}")
    print(f"  Linear Regression:  R² = {lr_r2:.4f}")

    claim = cart_d6_r2 > lr_r2
    print(f"\n  CART d6 > LinReg:    {'CONFIRMED' if claim else 'FAILED'} "
          f"({cart_d6_r2:.4f} vs {lr_r2:.4f})")

    # Find Pareto elbow
    best_pareto = None
    for sr in size_results:
        depth = int(sr['model'].split('Depth')[1].split('_')[0])
        if sr['arm_text_bytes'] > 0 and sr['arm_text_bytes'] < 10000:
            ratio = sr['r2_mean'] / np.log10(max(sr['arm_text_bytes'], 1))
            if best_pareto is None or ratio > best_pareto[1]:
                best_pareto = (depth, ratio, sr['r2_mean'], sr['arm_text_bytes'])

    if best_pareto:
        print(f"\n  Pareto-optimal CART depth: {best_pareto[0]} "
              f"(R²={best_pareto[2]:.4f}, {best_pareto[3]:,} bytes)")
        if 4 <= best_pareto[0] <= 6:
            print("  Elbow at Depth 4-6: CONFIRMED (matches simulation)")
        else:
            print(f"  Elbow shifted to Depth {best_pareto[0]} "
                  f"(simulation had Depth 6)")

    print("\n" + "=" * 60)
    print("TESTBED VALIDATION COMPLETE")
    print("=" * 60)


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description='Testbed validation pipeline')
    parser.add_argument('--site', default=None,
                        help='IoT-LAB site name (e.g., lille). Uses site-specific dataset and output paths.')
    args = parser.parse_args()
    if args.site and args.site != 'grenoble':
        DATASET_PATH = os.path.join(PROCESSED_DIR, f'testbed_dataset_{args.site}.csv')
        # Also set a global for site-specific output naming
        os.environ['TESTBED_SITE'] = args.site
    main()
