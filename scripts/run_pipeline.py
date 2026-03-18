"""
Master Pipeline Orchestration
Runs all steps in dependency order and verifies data-figure consistency.
"""
import subprocess
import sys
import os
import json
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')


def run_step(name, script_path):
    """Run a Python script and report timing."""
    print(f"\n{'='*60}")
    print(f"  STEP: {name}")
    print(f"  Script: {script_path}")
    print(f"{'='*60}\n")

    start = time.time()
    result = subprocess.run(
        [sys.executable, script_path],
        cwd=ROOT_DIR,
    )
    elapsed = time.time() - start

    if result.returncode != 0:
        print(f"\n  FAILED: {name} (exit code {result.returncode})")
        sys.exit(1)
    else:
        print(f"\n  DONE: {name} ({elapsed:.1f}s)")


def verify_consistency():
    """Check that all data files referenced by plots exist and are non-empty."""
    print(f"\n{'='*60}")
    print("  VERIFICATION: Data-Figure Consistency")
    print(f"{'='*60}")

    processed = os.path.join(ROOT_DIR, 'data', 'processed')
    required_files = [
        'ale_results.json',
        'extracted_thresholds.json',
        'xgboost_model.json',
        'spatial_leakage_results.json',
        'fair_ale_comparison.json',
        'extended_metrics.json',
    ]

    all_ok = True
    for fname in required_files:
        path = os.path.join(processed, fname)
        if not os.path.exists(path):
            print(f"  MISSING: {fname}")
            all_ok = False
        else:
            size = os.path.getsize(path)
            print(f"  OK: {fname} ({size:,} bytes)")
            if size == 0:
                print(f"  WARNING: {fname} is empty!")
                all_ok = False

    # Verify thresholds JSON has expected keys
    thresh_path = os.path.join(processed, 'extracted_thresholds.json')
    if os.path.exists(thresh_path):
        with open(thresh_path) as f:
            data = json.load(f)
        required_keys = ['snr_low', 'snr_high', 'density_lut', 'rule_coefs',
                         'model_metrics', 'feature_importances']
        for key in required_keys:
            if key not in data:
                print(f"  MISSING KEY in thresholds: {key}")
                all_ok = False

        # Verify metrics have std fields (indicating proper CV)
        metrics = data.get('model_metrics', {})
        for model in ['xgboost', 'cart', 'linear', 'rule']:
            mean_key = f'{model}_r2_mean'
            std_key = f'{model}_r2_std'
            if mean_key not in metrics:
                print(f"  MISSING: model_metrics.{mean_key}")
                all_ok = False
            if std_key not in metrics:
                print(f"  MISSING: model_metrics.{std_key}")
                all_ok = False

    # Optional testbed validation check
    testbed_path = os.path.join(processed, 'testbed_results.json')
    if os.path.exists(testbed_path):
        size = os.path.getsize(testbed_path)
        print(f"  OK: testbed_results.json ({size:,} bytes)")
        with open(testbed_path) as f:
            tb = json.load(f)
        if 'models' not in tb or 'arm_sizes' not in tb:
            print(f"  WARNING: testbed_results.json missing expected keys")
            all_ok = False

    if all_ok:
        print("\n  All consistency checks PASSED.")
    else:
        print("\n  Some consistency checks FAILED.")

    return all_ok


def main():
    print("=" * 60)
    print("  WSN RESEARCH PIPELINE — FULL EXECUTION")
    print("=" * 60)

    steps = [
        ("1. Generate Dataset (IEEE 802.15.4 Simulation)",
         os.path.join(ROOT_DIR, 'src', 'simulation', 'wsn_simulation.py')),

        ("2. Train XGBoost + ALE Distillation (GroupKFold CV)",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'train_and_extract.py')),

        ("3. CART Depth Sweep + C Code Generation",
         os.path.join(ROOT_DIR, 'src', 'deployment', 'generate_cart_c_code.py')),

        ("4. Linear Regression C Code Generation",
         os.path.join(ROOT_DIR, 'src', 'deployment', 'generate_linreg_c_code.py')),

        ("5. XGBoost + ALE C Code Generation",
         os.path.join(ROOT_DIR, 'src', 'deployment', 'generate_c_code.py')),

        ("6. Knowledge Distillation Experiments",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'knowledge_distillation.py')),

        ("7. Pruned XGBoost Pareto Sweep",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'pareto_frontier.py')),

        ("8. Ablation Studies",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'ablation_studies.py')),

        ("9. Spatial Leakage Comparison (Naive KFold vs GroupKFold)",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'spatial_leakage_comparison.py')),

        ("10. Fair ALE Comparison (2-Feature Baselines)",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'fair_ale_comparison.py')),

        ("11. Extended Metrics (RMSE, MAE, F1-Score)",
         os.path.join(ROOT_DIR, 'src', 'modeling', 'extended_metrics.py')),

        ("12. Benchmark Compiled Sizes (ARM + x86)",
         os.path.join(ROOT_DIR, 'scripts', 'benchmark_size.py')),

        ("13. Generate Publication Figures",
         os.path.join(ROOT_DIR, 'scripts', 'generate_plots.py')),
    ]

    # Optional testbed validation steps (run only if testbed data exists)
    testbed_dataset = os.path.join(ROOT_DIR, 'data', 'processed', 'testbed_dataset.csv')
    if os.path.exists(testbed_dataset):
        steps.append(
            ("14. Testbed Validation (FIT IoT-LAB)",
             os.path.join(ROOT_DIR, 'src', 'modeling', 'testbed_validation.py')))
        # Re-run figure generation to include testbed Pareto frontier
        steps.append(
            ("15. Regenerate Figures (with Testbed Pareto)",
             os.path.join(ROOT_DIR, 'scripts', 'generate_plots.py')))
    else:
        print(f"\n  NOTE: Testbed dataset not found at {testbed_dataset}")
        print(f"  Skipping testbed validation steps.")
        print(f"  To enable: run src/data/fetch_testbed.py + process_testbed.py")

    for name, path in steps:
        run_step(name, path)

    verify_consistency()

    print(f"\n{'='*60}")
    print("  PIPELINE COMPLETE")
    print(f"{'='*60}")


if __name__ == '__main__':
    main()
