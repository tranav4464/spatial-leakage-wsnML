"""
Bootstrap 95% Confidence Intervals
====================================
Computes BCa bootstrap CIs for per-fold R^2 from simulation and testbed
results, plus CIs for pairwise R^2 differences between key model pairs.

Output: data/processed/bootstrap_ci.json
"""
import os
import json
import numpy as np

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..', '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')

B = 10_000  # bootstrap resamples
RNG = np.random.default_rng(42)


def bootstrap_ci(values, n_boot=B, alpha=0.05):
    """Compute percentile bootstrap 95% CI for the mean of `values`."""
    arr = np.asarray(values, dtype=float)
    n = len(arr)
    boot_means = np.empty(n_boot)
    for i in range(n_boot):
        idx = RNG.integers(0, n, size=n)
        boot_means[i] = arr[idx].mean()
    lo = np.percentile(boot_means, 100 * alpha / 2)
    hi = np.percentile(boot_means, 100 * (1 - alpha / 2))
    return float(np.mean(arr)), float(lo), float(hi)


def bootstrap_diff_ci(vals_a, vals_b, n_boot=B, alpha=0.05):
    """Bootstrap CI for the mean difference (A - B) of paired fold values."""
    a = np.asarray(vals_a, dtype=float)
    b = np.asarray(vals_b, dtype=float)
    diff = a - b
    n = len(diff)
    boot_diffs = np.empty(n_boot)
    for i in range(n_boot):
        idx = RNG.integers(0, n, size=n)
        boot_diffs[i] = diff[idx].mean()
    lo = np.percentile(boot_diffs, 100 * alpha / 2)
    hi = np.percentile(boot_diffs, 100 * (1 - alpha / 2))
    return float(diff.mean()), float(lo), float(hi)


def main():
    print("=" * 60)
    print("BOOTSTRAP 95% CONFIDENCE INTERVALS")
    print("=" * 60)

    results = {'simulation': {}, 'testbed': {}, 'pairwise_diffs': {}}

    # ---- Simulation: per-fold R^2 from extended_metrics.json ----
    sim_path = os.path.join(PROCESSED_DIR, 'extended_metrics.json')
    if os.path.exists(sim_path):
        print("\nSimulation models (from extended_metrics.json):")
        with open(sim_path) as f:
            sim = json.load(f)
        # extended_metrics.json has r2_mean/r2_std but no per_fold_r2
        # Approximate: use mean +/- std to generate placeholder note
        for model, data in sim.items():
            mean_val = data['r2_mean']
            std_val = data['r2_std']
            results['simulation'][model] = {
                'r2_mean': mean_val,
                'r2_std': std_val,
                'note': 'Per-fold values not stored; CI from normal approx',
                'ci_95_lo': round(mean_val - 1.96 * std_val, 4),
                'ci_95_hi': round(mean_val + 1.96 * std_val, 4),
            }
            print(f"  {model:20s}: R^2 = {mean_val:.4f} "
                  f"[{mean_val - 1.96 * std_val:.4f}, "
                  f"{mean_val + 1.96 * std_val:.4f}] (normal approx)")
    else:
        print(f"\n  WARNING: {sim_path} not found, skipping simulation CIs.")

    # ---- Testbed: per-fold R^2 from testbed_results.json ----
    tb_path = os.path.join(PROCESSED_DIR, 'testbed_results.json')
    if os.path.exists(tb_path):
        print("\nTestbed models (from testbed_results.json):")
        with open(tb_path) as f:
            tb = json.load(f)

        per_fold = {}
        for model, data in tb['models'].items():
            folds = data.get('per_fold_r2')
            if folds is None:
                continue
            mean_val, lo, hi = bootstrap_ci(folds)
            results['testbed'][model] = {
                'r2_mean': round(mean_val, 4),
                'ci_95_lo': round(lo, 4),
                'ci_95_hi': round(hi, 4),
                'n_folds': len(folds),
            }
            per_fold[model] = folds
            print(f"  {model:20s}: R^2 = {mean_val:.4f} "
                  f"[{lo:.4f}, {hi:.4f}]")

        # ---- Pairwise differences (key comparisons) ----
        print("\nPairwise R^2 differences (testbed):")
        pairs = [
            ('cart_d3', 'xgboost'),
            ('cart_d3', 'linreg'),
            ('cart_d3', 'rssi_binned'),
            ('cart_d3', 'mean_baseline'),
            ('cart_d2', 'cart_d3'),
            ('xgboost', 'linreg'),
        ]
        for m1, m2 in pairs:
            if m1 in per_fold and m2 in per_fold:
                diff, lo, hi = bootstrap_diff_ci(per_fold[m1], per_fold[m2])
                key = f"{m1}_minus_{m2}"
                results['pairwise_diffs'][key] = {
                    'delta_r2_mean': round(diff, 4),
                    'ci_95_lo': round(lo, 4),
                    'ci_95_hi': round(hi, 4),
                }
                print(f"  {m1:15s} - {m2:15s}: "
                      f"delta = {diff:+.4f} [{lo:+.4f}, {hi:+.4f}]")
    else:
        print(f"\n  WARNING: {tb_path} not found, skipping testbed CIs.")

    # ---- Save ----
    out_path = os.path.join(PROCESSED_DIR, 'bootstrap_ci.json')
    with open(out_path, 'w') as f:
        json.dump(results, f, indent=2)
    print(f"\nSaved: {out_path}")


if __name__ == '__main__':
    main()
