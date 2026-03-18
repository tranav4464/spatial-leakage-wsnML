"""
Generate publication-quality figures from current data files.
All values are read from JSON — nothing is hardcoded.
Publication formatting: serif font, 300 DPI, proper sizing.

Figures generated:
  1. Feature Importance
  2. Model Performance Comparison (R2 with error bars)
  3. Pareto Frontier (ARM .text vs R2)
  4. Spatial Leakage Comparison (Naive KFold vs GroupKFold)
  5. Testbed Pareto Frontier
  6. Reweighting Comparison
  7. Grouping Comparison
  8. Temporal vs Static Comparison
  9. Multi-Site Leakage Comparison
"""
import os
import json
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Publication style
sns.set_theme(style="whitegrid", context="paper", font_scale=1.2)
plt.rcParams['font.family'] = 'serif'
plt.rcParams['axes.titlesize'] = 14
plt.rcParams['axes.labelsize'] = 12
plt.rcParams['figure.dpi'] = 300

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
PROCESSED_DIR = os.path.join(ROOT_DIR, 'data', 'processed')
FIGURES_DIR = os.path.join(ROOT_DIR, 'results', 'figures')
TABLES_DIR = os.path.join(ROOT_DIR, 'results', 'tables')
os.makedirs(FIGURES_DIR, exist_ok=True)

# Load data
with open(os.path.join(PROCESSED_DIR, 'extracted_thresholds.json')) as f:
    thresholds = json.load(f)

# ============================================================
# 1. Feature Importance Plot
# ============================================================
print("Generating Feature Importance plot...")
importances = thresholds['feature_importances']
feat_df = pd.DataFrame({
    'Feature': list(importances.keys()),
    'Importance': list(importances.values())
}).sort_values('Importance', ascending=False)

# Clean feature names: replace underscores with spaces
feat_df['Feature'] = feat_df['Feature'].str.replace('_', ' ')

plt.figure(figsize=(10, 6))
sns.barplot(data=feat_df, x='Importance', y='Feature', palette='viridis')
plt.title("XGBoost Global Feature Importance (Split-Based)")
plt.tight_layout()
plt.savefig(os.path.join(FIGURES_DIR, 'feature_importance.pdf'), dpi=300)
plt.savefig(os.path.join(FIGURES_DIR, 'feature_importance.png'), dpi=300)
plt.close()
print(f"  Saved: feature_importance.pdf/png")

# ============================================================
# 3. Model Performance Comparison (R2 with error bars)
# ============================================================
print("Generating Performance Comparison plot...")
m = thresholds['model_metrics']

perf_df = pd.DataFrame({
    'Model': ['XGBoost', 'CART (d=4)', 'Linear Reg.'],
    'R2 Mean': [m['xgboost_r2_mean'], m['cart_r2_mean'],
                m['linear_r2_mean']],
    'R2 Std': [m['xgboost_r2_std'], m['cart_r2_std'],
               m['linear_r2_std']],
})

plt.figure(figsize=(8, 5))
ax = plt.gca()
colors = sns.color_palette('Set2', len(perf_df))
bars = ax.bar(perf_df['Model'], perf_df['R2 Mean'], yerr=perf_df['R2 Std'],
              capsize=5, color=colors, edgecolor='black', linewidth=0.5)

for bar, mean, std in zip(bars, perf_df['R2 Mean'], perf_df['R2 Std']):
    ax.text(bar.get_x() + bar.get_width() / 2., bar.get_height() + std + 0.02,
            f'{mean:.4f}', ha='center', va='bottom', fontsize=10)

plt.title("Model Comparison: Predictive Accuracy ($R^2$, 5-Fold GroupKFold CV)")
plt.ylabel("$R^2$ Score")
plt.ylim(0, 1.1)
plt.tight_layout()
plt.savefig(os.path.join(FIGURES_DIR, 'performance_comparison.pdf'), dpi=300)
plt.savefig(os.path.join(FIGURES_DIR, 'performance_comparison.png'), dpi=300)
plt.close()
print(f"  Saved: performance_comparison.pdf/png")

# ============================================================
# 4. Pareto Frontier (using ARM .text sizes if available)
# ============================================================
bench_path = os.path.join(TABLES_DIR, 'model_benchmarks.json')
if os.path.exists(bench_path):
    print("Generating Pareto Frontier plot...")
    with open(bench_path) as f:
        benchmarks = json.load(f)

    fig, ax = plt.subplots(figsize=(10, 6))

    # Use ARM .text if available, else fall back to x86
    size_key = 'arm_text_bytes' if 'arm_text_bytes' in benchmarks[0] else 'text_size'
    arch_label = "ARM Cortex-M3" if size_key == 'arm_text_bytes' else "x86-64"

    # Define manual offsets for specific models to prevent overlap
    label_offsets = {
        'XGBoost_Full': (-30, 10),
        'ALE_Rule': (5, -15),
        'Linear_Reg': (-25, 10),
        'CART_Depth2': (-35, -12),
        'CART_Depth3': (5, -15),
        'CART_Depth4': (5, 5),
        'CART_Depth5': (5, -15),
        'CART_Depth6': (5, 5),
        'CART_Depth8': (5, -15),
        'CART_Depth10': (5, 5)
    }

    for b in benchmarks:
        text_size = b.get(size_key, b.get('text_size', 0))
        if text_size == 0:
            continue
        color = 'blue' if 'XGBoost' in b['model'] else \
                '#0072B2' if 'CART' in b['model'] else 'orange'
        marker = 'D' if 'XGBoost' in b['model'] else \
                 'o' if 'CART' in b['model'] else '^'
        ax.scatter(text_size, b['r2_mean'], color=color, marker=marker,
                   s=100, zorder=5, edgecolors='black', linewidth=0.5)
        
        offset = label_offsets.get(b['model'], (5, 5))
        ax.annotate(b['model'], (text_size, b['r2_mean']),
                    textcoords="offset points", xytext=offset, fontsize=8)

    ax.set_xscale('log')
    ax.set_xlabel(f"Compiled .text Size (bytes, log scale) [{arch_label}]")
    ax.set_ylabel("$R^2$ Score (5-Fold GroupKFold CV)")
    ax.set_title(f"Accuracy-Footprint Pareto Frontier ({arch_label})")
    ax.grid(True, alpha=0.3)

    # MCU reference lines (flash budgets) — horizontal labels above plot
    ymin, ymax = ax.get_ylim()
    label_y = ymax + (ymax - ymin) * 0.02
    for size_bytes, label in [(8192, 'ATtiny85\n8 KB'),
                               (16384, 'MSP430\n16 KB'),
                               (32768, 'ATmega328P\n32 KB')]:
        ax.axvline(size_bytes, color='gray', linestyle=':', alpha=0.5)
        ax.text(size_bytes, label_y, label, rotation=0,
                va='bottom', ha='center', fontsize=7, color='gray')
    ax.set_ylim(ymin, ymax + (ymax - ymin) * 0.12)

    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'pareto_frontier.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'pareto_frontier.png'), dpi=300)
    plt.close()
    print(f"  Saved: pareto_frontier.pdf/png")

# ============================================================
# 5. Spatial Leakage Comparison (Figure 3 from briefing)
# ============================================================
leakage_path = os.path.join(PROCESSED_DIR, 'spatial_leakage_results.json')
if os.path.exists(leakage_path):
    print("Generating Spatial Leakage Comparison plot...")
    with open(leakage_path) as f:
        leakage = json.load(f)

    naive = leakage.get('naive_kfold', {})
    grouped = leakage.get('groupkfold', {})

    models = []
    for key in naive:
        label = key.upper() if key == 'xgboost' else key.replace('_', ' ').title()
        models.append(key)

    fig, ax = plt.subplots(figsize=(10, 6))

    x = np.arange(len(models))
    width = 0.35

    naive_means = [naive[m]['r2_mean'] for m in models]
    naive_stds = [naive[m]['r2_std'] for m in models]
    group_means = [grouped[m]['r2_mean'] for m in models]
    group_stds = [grouped[m]['r2_std'] for m in models]

    labels = [m.upper() if m == 'xgboost' else m.replace('_', ' ').title()
              for m in models]

    bars1 = ax.bar(x - width/2, naive_means, width, yerr=naive_stds,
                   label='Naive KFold (spatial leakage)', color='#e74c3c',
                   capsize=5, edgecolor='black', linewidth=0.5, alpha=0.85)
    bars2 = ax.bar(x + width/2, group_means, width, yerr=group_stds,
                   label='GroupKFold (leakage prevented)', color='#2ecc71',
                   capsize=5, edgecolor='black', linewidth=0.5, alpha=0.85)

    # Add delta annotations
    for i, (nm, gm) in enumerate(zip(naive_means, group_means)):
        delta = nm - gm
        if delta > 0:
            ax.annotate(f'$\\Delta$={delta:.3f}', xy=(i, max(nm, gm) + 0.03),
                        ha='center', fontsize=9, color='#CC79A7', fontweight='bold')

    ax.set_xlabel('Model')
    ax.set_ylabel('$R^2$ Score')
    ax.set_title('Impact of Spatial Leakage: Naive KFold vs. Geographic GroupKFold')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()
    ax.set_ylim(0, 1.15)
    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'spatial_leakage_comparison.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'spatial_leakage_comparison.png'), dpi=300)
    plt.close()
    print(f"  Saved: spatial_leakage_comparison.pdf/png")
else:
    print("  SKIPPED: spatial_leakage_results.json not found")


# ============================================================
# 7. Testbed Pareto Frontier (Simulation vs Physical)
# ============================================================
testbed_path = os.path.join(PROCESSED_DIR, 'testbed_results.json')
if os.path.exists(testbed_path) and os.path.exists(bench_path):
    print("Generating Testbed Pareto Frontier plot...")
    with open(testbed_path) as f:
        testbed = json.load(f)

    # Load simulation benchmarks for overlay
    with open(bench_path) as f:
        sim_benchmarks = json.load(f)

    fig, ax = plt.subplots(figsize=(10, 6))

    # Plot simulation Pareto frontier (dashed, background)
    sim_sizes = []
    sim_r2s = []
    for b in sim_benchmarks:
        text_size = b.get('arm_text_bytes', 0)
        if text_size > 0 and 'CART' in b['model']:
            sim_sizes.append(text_size)
            sim_r2s.append(b['r2_mean'])

    if sim_sizes:
        sorted_pairs = sorted(zip(sim_sizes, sim_r2s))
        ax.plot([p[0] for p in sorted_pairs], [p[1] for p in sorted_pairs],
                '--', color='gray', alpha=0.5, linewidth=1.5, label='Simulation CART frontier')

    # Plot simulation models (faded)
    for b in sim_benchmarks:
        text_size = b.get('arm_text_bytes', 0)
        if text_size == 0:
            continue
        color = 'blue' if 'XGBoost' in b['model'] else \
                '#0072B2' if 'CART' in b['model'] else 'orange'
        ax.scatter(text_size, b['r2_mean'], color=color, marker='o',
                   s=60, alpha=0.3, edgecolors='gray', linewidth=0.5)

    # Plot testbed models (solid, foreground)
    testbed_sizes = testbed.get('arm_sizes', [])
    testbed_models = testbed.get('models', {})

    # CART depths from testbed — alternate label offsets to avoid overlap
    tb_cart_sizes = []
    tb_cart_r2s = []
    label_offsets = [(8, 8), (-8, -12), (8, 8), (-8, -12), (8, 8),
                     (-8, -12), (8, 8), (-8, -12), (8, 8)]
    for idx_sr, sr in enumerate(testbed_sizes):
        if sr['arm_text_bytes'] > 0:
            ax.scatter(sr['arm_text_bytes'], sr['r2_mean'], color='#D55E00',
                       marker='s', s=120, zorder=5, edgecolors='black', linewidth=1)
            ofs = label_offsets[idx_sr % len(label_offsets)]
            ax.annotate(sr['model'].replace('_Testbed', ''),
                        (sr['arm_text_bytes'], sr['r2_mean']),
                        textcoords="offset points", xytext=ofs, fontsize=7,
                        fontweight='bold')
            tb_cart_sizes.append(sr['arm_text_bytes'])
            tb_cart_r2s.append(sr['r2_mean'])

    if tb_cart_sizes:
        sorted_pairs = sorted(zip(tb_cart_sizes, tb_cart_r2s))
        ax.plot([p[0] for p in sorted_pairs], [p[1] for p in sorted_pairs],
                '-', color='#D55E00', alpha=0.7, linewidth=2,
                label='Testbed CART frontier')

    # Plot testbed LinReg (use simulation-equivalent size)
    lr_sim_size = next((b['arm_text_bytes'] for b in sim_benchmarks
                        if 'Linear' in b['model']), 292)

    if 'linreg' in testbed_models:
        ax.scatter(lr_sim_size, testbed_models['linreg']['r2_mean'],
                   color='darkorange', marker='X', s=120, zorder=5,
                   edgecolors='black', linewidth=1)
        ax.annotate('LinReg (Testbed)', (lr_sim_size,
                    testbed_models['linreg']['r2_mean']),
                    textcoords="offset points", xytext=(5, -10), fontsize=7,
                    fontweight='bold', color='darkorange')

    ax.set_xscale('log')
    ax.set_xlabel("Compiled .text Size (bytes, log scale) [ARM Cortex-M3]")
    ax.set_ylabel("$R^2$ Score (GroupKFold CV)")
    ax.set_title("Testbed vs. Simulation Pareto Frontier")
    ax.legend(fontsize=9)
    ax.grid(True, alpha=0.3)

    # MCU reference lines — horizontal labels above plot
    ymin, ymax = ax.get_ylim()
    label_y = ymax + (ymax - ymin) * 0.02
    for size_bytes, label in [(8192, 'ATtiny85\n8 KB'),
                               (16384, 'MSP430\n16 KB'),
                               (32768, 'ATmega328P\n32 KB')]:
        ax.axvline(size_bytes, color='gray', linestyle=':', alpha=0.5)
        ax.text(size_bytes, label_y, label, rotation=0,
                va='bottom', ha='center', fontsize=7, color='gray')
    ax.set_ylim(ymin, ymax + (ymax - ymin) * 0.12)
    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'testbed_pareto_frontier.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'testbed_pareto_frontier.png'), dpi=300)
    plt.close()
    print(f"  Saved: testbed_pareto_frontier.pdf/png")
else:
    print("  SKIPPED: testbed_results.json not found (run testbed_validation.py)")

# ============================================================
# 8. Reweighting Comparison (Trans-R² across experiments)
# ============================================================
print("\n--- Figure 8: Reweighting Comparison ---")
reweight_path = os.path.join(PROCESSED_DIR, 'reweighting_results.json')
if os.path.exists(reweight_path):
    with open(reweight_path) as f:
        rw_data = json.load(f)

    experiments = ['baseline', 'inverse_weight', 'trans_only_train', 'oversampling']
    exp_labels = ['Baseline\n(unweighted)', 'Inverse\nFrequency', 'Trans-Only\nTraining', 'Oversampling']
    models = ['xgboost', 'cart_d3', 'linreg']
    model_labels = ['XGBoost', 'CART d3', 'LinReg']
    colors = ['#2196F3', '#4CAF50', '#FF9800']

    fig, ax = plt.subplots(figsize=(8, 5))
    x = np.arange(len(experiments))
    width = 0.25

    for i, (model, mlabel, color) in enumerate(zip(models, model_labels, colors)):
        trans_r2s = []
        for exp in experiments:
            val = rw_data.get(exp, {}).get(model, {}).get('trans_r2_mean', float('nan'))
            trans_r2s.append(val)
        ax.bar(x + i * width, trans_r2s, width, label=mlabel, color=color, alpha=0.85)

    ax.set_xlabel('Experiment')
    ax.set_ylabel('Trans-$R^2$ (transitional region)')
    ax.set_title('Effect of Class Reweighting on Transitional-Region Performance')
    ax.set_xticks(x + width)
    ax.set_xticklabels(exp_labels, fontsize=9)
    ax.legend()
    ax.axhline(y=0, color='black', linestyle='-', linewidth=0.8)
    ax.grid(True, alpha=0.3, axis='y')
    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'reweighting_comparison.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'reweighting_comparison.png'), dpi=300)
    plt.close()
    print(f"  Saved: reweighting_comparison.pdf/png")
else:
    print("  SKIPPED: reweighting_results.json not found")

# ============================================================
# 9. Grouping Comparison (R² across grouping strategies)
# ============================================================
print("\n--- Figure 9: Grouping Comparison ---")
grouping_path = os.path.join(PROCESSED_DIR, 'grouping_comparison.json')
if os.path.exists(grouping_path):
    with open(grouping_path) as f:
        gc_data = json.load(f)

    groupings = gc_data.get('groupings', {})
    group_names = list(groupings.keys())
    group_labels = ['dst_node\nLOGO', 'src_node\nLOGO', 'link_id\nGKF-10']
    models = ['xgboost', 'cart_d3']
    model_labels = ['XGBoost', 'CART d3']
    colors = ['#2196F3', '#4CAF50']

    fig, ax = plt.subplots(figsize=(8, 5))
    x = np.arange(len(group_names))
    width = 0.3

    for i, (model, mlabel, color) in enumerate(zip(models, model_labels, colors)):
        r2s = []
        stds = []
        for gname in group_names:
            gdata = groupings[gname]
            r2s.append(gdata.get(model, {}).get('r2_mean', float('nan')))
            stds.append(min(gdata.get(model, {}).get('r2_std', 0), 2.0))  # cap error bars
        ax.bar(x + i * width, r2s, width, yerr=stds, label=mlabel,
               color=color, alpha=0.85, capsize=3)

    ax.set_xlabel('Grouping Strategy')
    ax.set_ylabel('$R^2$ Score (mean ± std)')
    ax.set_title('Spatial Leakage Robustness\nAcross Grouping Strategies')
    ax.set_xticks(x + width / 2)
    ax.set_xticklabels(group_labels[:len(group_names)], fontsize=9)
    ax.legend()
    ax.axhline(y=0, color='black', linestyle='-', linewidth=0.8)
    ax.grid(True, alpha=0.3, axis='y')
    ax.set_ylim(-3, 1)  # sensible range instead of letting error bars dominate
    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'grouping_comparison.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'grouping_comparison.png'), dpi=300)
    plt.close()
    print(f"  Saved: grouping_comparison.pdf/png")
else:
    print("  SKIPPED: grouping_comparison.json not found")

# ============================================================
# 10. Temporal vs Static Comparison (Figure 10)
# ============================================================
print("\n--- Figure 10: Temporal vs Static Comparison ---")
temporal_path = os.path.join(PROCESSED_DIR, 'temporal_baseline_results.json')
if os.path.exists(temporal_path):
    with open(temporal_path) as f:
        temporal_data = json.load(f)

    models_data = temporal_data['models']
    # Build comparison data — include MLP if available
    has_mlp = 'mlp_static' in models_data and 'mlp_temporal' in models_data
    if has_mlp:
        labels = ['XGBoost', 'CART d3', 'LinReg', 'MLP', 'EWMA']
        static_r2 = [
            models_data['xgboost_static']['r2_mean'],
            models_data['cart_d3_static']['r2_mean'],
            models_data['linreg_static']['r2_mean'],
            models_data['mlp_static']['r2_mean'],
            None,
        ]
        temporal_r2 = [
            models_data['xgboost_temporal']['r2_mean'],
            models_data['cart_d3_temporal']['r2_mean'],
            models_data['linreg_temporal']['r2_mean'],
            models_data['mlp_temporal']['r2_mean'],
            models_data['ewma_baseline']['r2_mean'],
        ]
    else:
        labels = ['XGBoost', 'CART d3', 'LinReg', 'EWMA']
        static_r2 = [
            models_data['xgboost_static']['r2_mean'],
            models_data['cart_d3_static']['r2_mean'],
            models_data['linreg_static']['r2_mean'],
            None,
        ]
        temporal_r2 = [
            models_data['xgboost_temporal']['r2_mean'],
            models_data['cart_d3_temporal']['r2_mean'],
            models_data['linreg_temporal']['r2_mean'],
            models_data['ewma_baseline']['r2_mean'],
        ]

    x = np.arange(len(labels))
    width = 0.35

    fig, ax = plt.subplots(figsize=(8, 5))
    # Static bars — only for models that have a static version (not EWMA)
    static_vals = [v for v in static_r2 if v is not None]
    n_static = len(static_vals)
    x_ml = x[:n_static]
    bars1 = ax.bar(x_ml - width/2, static_vals, width, label='Static (4 features)',
                   color='#d62728', alpha=0.8)
    bars2 = ax.bar(x + width/2, temporal_r2, width, label='Temporal (7 features / EWMA)',
                   color='#2ca02c', alpha=0.8)

    ax.set_ylabel('$R^2$ (LOGO CV)')
    ax.set_title('Static vs Temporal Models Under LOGO Evaluation')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.axhline(y=0, color='black', linestyle='-', linewidth=0.5)
    ax.legend()
    all_vals = static_vals + temporal_r2
    ax.set_ylim(min(all_vals) - 0.2, max(all_vals) + 0.1)

    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'temporal_comparison.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'temporal_comparison.png'), dpi=300)
    plt.close()
    print(f"  Saved: temporal_comparison.pdf/png")
else:
    print("  SKIPPED: temporal_baseline_results.json not found")

# ============================================================
# 11. Multi-Site Leakage Comparison (Grenoble vs Lille)
# ============================================================
print("\n--- Figure 11: Multi-Site Leakage Comparison ---")
testbed_grenoble_path = os.path.join(PROCESSED_DIR, 'testbed_results.json')
testbed_lille_path = os.path.join(PROCESSED_DIR, 'testbed_results_lille.json')
cross_site_path = os.path.join(PROCESSED_DIR, 'cross_site_results.json')

if os.path.exists(testbed_grenoble_path) and os.path.exists(testbed_lille_path):
    with open(testbed_grenoble_path) as f:
        grenoble_data = json.load(f)
    with open(testbed_lille_path) as f:
        lille_data = json.load(f)

    fig, axes = plt.subplots(1, 2, figsize=(14, 5))

    # Panel (a): LOGO R2 comparison
    models_to_plot = ['xgboost', 'cart_d3', 'linreg']
    model_labels = ['XGBoost', 'CART d3', 'LinReg']
    x = np.arange(len(models_to_plot))
    width = 0.35

    g_r2 = [grenoble_data['models'][m]['r2_mean'] for m in models_to_plot]
    l_r2 = [lille_data['models'][m]['r2_mean'] for m in models_to_plot]

    axes[0].bar(x - width/2, g_r2, width, label='Grenoble (49 nodes)',
                color='#2196F3', alpha=0.85, edgecolor='black', linewidth=0.5)
    axes[0].bar(x + width/2, l_r2, width, label='Lille (46 nodes)',
                color='#FF9800', alpha=0.85, edgecolor='black', linewidth=0.5)

    axes[0].set_ylabel('$R^2$ (LOGO CV)')
    axes[0].set_title('(a) Within-Site LOGO Performance')
    axes[0].set_xticks(x)
    axes[0].set_xticklabels(model_labels)
    axes[0].legend(fontsize=9)
    axes[0].axhline(y=0, color='black', linestyle='-', linewidth=0.5)

    # Panel (b): Cross-site train/test
    if os.path.exists(cross_site_path):
        with open(cross_site_path) as f:
            cross_data = json.load(f)

        cross_models = ['xgboost', 'cart_d3', 'linreg']
        cross_labels = ['XGBoost', 'CART d3', 'LinReg']
        x2 = np.arange(len(cross_models))

        g_logo = [cross_data['grenoble_logo'][m]['r2'] for m in cross_models]
        l_logo = [cross_data['lille_logo'][m]['r2'] for m in cross_models]
        g_to_l = [cross_data['train_grenoble_test_lille'][m]['r2'] for m in cross_models]
        l_to_g = [cross_data['train_lille_test_grenoble'][m]['r2'] for m in cross_models]

        width2 = 0.2
        axes[1].bar(x2 - 1.5*width2, g_logo, width2, label='Grenoble LOGO',
                    color='#2196F3', alpha=0.85, edgecolor='black', linewidth=0.5)
        axes[1].bar(x2 - 0.5*width2, l_logo, width2, label='Lille LOGO',
                    color='#FF9800', alpha=0.85, edgecolor='black', linewidth=0.5)
        axes[1].bar(x2 + 0.5*width2, g_to_l, width2, label='Grenoble->Lille',
                    color='#e74c3c', alpha=0.85, edgecolor='black', linewidth=0.5)
        axes[1].bar(x2 + 1.5*width2, l_to_g, width2, label='Lille->Grenoble',
                    color='#9C27B0', alpha=0.85, edgecolor='black', linewidth=0.5)

        axes[1].set_ylabel('$R^2$')
        axes[1].set_title('(b) Cross-Site Generalization')
        axes[1].set_xticks(x2)
        axes[1].set_xticklabels(cross_labels)
        axes[1].legend(fontsize=8, loc='lower right')
        axes[1].axhline(y=0, color='black', linestyle='-', linewidth=0.5)

    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'multi_site_comparison.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'multi_site_comparison.png'), dpi=300)
    plt.close()
    print(f"  Saved: multi_site_comparison.pdf/png")
else:
    print("  SKIPPED: testbed results for both sites not found")

# ============================================================
# 10. DISTANCE MEMORIZATION (LOFO)
# ============================================================
lofo_path = os.path.join(PROCESSED_DIR, 'testbed_lofo.json')
if os.path.exists(lofo_path):
    print("\n[10] Generating distance memorization plot...")
    with open(lofo_path) as f:
        lofo = json.load(f)

    fig, ax = plt.subplots(figsize=(8, 4))

    # Extract LOFO results for XGBoost — actual structure: lofo['xgboost']['features_dropped']
    xgb_data = lofo.get('xgboost', {})
    features_data = xgb_data.get('features_dropped', {})
    baseline_r2 = xgb_data.get('baseline_r2_mean', 0)

    if features_data:
        feat_names = list(features_data.keys())
        r2_without = [features_data[f].get('r2_mean', 0) for f in feat_names]

        # Color: green if removal improves R² (delta_r2 < 0), blue otherwise
        colors = ['#4CAF50' if features_data[f].get('delta_r2', 0) < 0 else '#1976D2'
                  for f in feat_names]

        bars = ax.bar(range(len(feat_names)), r2_without, color=colors,
                      edgecolor='black', linewidth=0.5, alpha=0.85)
        ax.axhline(y=baseline_r2, color='black', linestyle='--', linewidth=1.0,
                   label=f'Baseline $R^2$ = {baseline_r2:.3f}')

        # Annotate Distance bar
        for i, f in enumerate(feat_names):
            if 'Distance' in f.lower() or 'dist' in f.lower():
                delta = features_data[f].get('delta_r2', 0)
                if delta < 0:  # Removal improves R²
                    ax.annotate(f'Removal improves\n$R^2$ by {-delta:.3f}',
                                xy=(i, r2_without[i]),
                                xytext=(i + 1.2, r2_without[i] - 0.05),
                                fontsize=9, ha='center',
                                arrowprops=dict(arrowstyle='->', color='#d32f2f', lw=1.5),
                                color='#d32f2f', fontweight='bold')

        # Add value labels on bars
        for i, v in enumerate(r2_without):
            # Use a white bounding box to prevent the baseline from crossing through the text
            bbox_props = dict(boxstyle="round,pad=0.15", fc="white", ec="none", alpha=0.85)
            ax.text(i, v + 0.003, f'{v:.3f}', ha='center', va='bottom', fontsize=9, 
                    fontweight='bold', zorder=10, bbox=bbox_props)

        ax.set_xticks(range(len(feat_names)))
        ax.set_xticklabels([f.replace('_', '\n') for f in feat_names], fontsize=9)
        ax.set_ylabel('$R^2$ without feature (LOGO)')
        ax.set_title('Leave-One-Feature-Out: XGBoost (Testbed, LOGO CV)')
        ax.legend(fontsize=9)
        ax.grid(True, alpha=0.3, axis='y')

    plt.tight_layout()
    plt.savefig(os.path.join(FIGURES_DIR, 'distance_memorization.pdf'), dpi=300)
    plt.savefig(os.path.join(FIGURES_DIR, 'distance_memorization.png'), dpi=300)
    plt.close()
    print(f"  Saved: distance_memorization.pdf/png")
else:
    print("  SKIPPED: testbed_lofo.json not found")


# ============================================================
# 11. DISTANCE INTERACTION (Leakage Isolation)
# ============================================================
dist_int_path = os.path.join(PROCESSED_DIR, 'distance_interaction.json')
if os.path.exists(dist_int_path):
    print("\n[11] Generating distance interaction plot...")
    with open(dist_int_path) as f:
        dist_int = json.load(f)

    model_results = dist_int.get('results', {})
    if model_results:
        fig, axes = plt.subplots(1, len(model_results), figsize=(5 * len(model_results), 4), squeeze=False)

        for idx, (model_name, r) in enumerate(model_results.items()):
            ax = axes[0][idx]

            categories = ['With\nDistance', 'Without\nDistance']
            naive_vals = [r['naive_full'], r['naive_nodist']]
            logo_vals = [r['logo_full'], r['logo_nodist']]

            x = np.arange(len(categories))
            w = 0.35

            bars1 = ax.bar(x - w/2, naive_vals, w, label='Naive KFold',
                          color='#FF7043', edgecolor='black', linewidth=0.5, alpha=0.85)
            bars2 = ax.bar(x + w/2, logo_vals, w, label='LOGO',
                          color='#42A5F5', edgecolor='black', linewidth=0.5, alpha=0.85)

            # Annotate leakage delta
            max_val = -float('inf')
            min_val = float('inf')
            for i in range(2):
                delta = naive_vals[i] - logo_vals[i]
                mid_y = max(naive_vals[i], logo_vals[i]) + 0.15
                max_val = max(max_val, mid_y)
                min_val = min(min_val, min(naive_vals[i], logo_vals[i]))
                ax.annotate(f'$\\Delta$ = {delta:.2f}',
                           xy=(x[i], mid_y), fontsize=9, ha='center',
                           fontweight='bold',
                           color='#d32f2f' if delta > 0.5 else '#388E3C')

            ax.axhline(y=0, color='black', linestyle='-', linewidth=0.5)
            ax.set_ylabel('$R^2$')
            ax.set_title(model_name.upper())
            ax.set_xticks(x)
            ax.set_xticklabels(categories)
            ax.legend(fontsize=8, loc='lower left')
            
            # Add padding to prevent overflow
            ax.set_ylim(min_val - 0.2, max_val + 0.25)

        plt.suptitle('Distance Feature Interaction with Spatial Leakage',
                     fontsize=12, fontweight='bold')
        plt.tight_layout()
        plt.savefig(os.path.join(FIGURES_DIR, 'distance_interaction.pdf'), dpi=300)
        plt.savefig(os.path.join(FIGURES_DIR, 'distance_interaction.png'), dpi=300)
        plt.close()
        print(f"  Saved: distance_interaction.pdf/png")
else:
    print("  SKIPPED: distance_interaction.json not found")


# ============================================================
# 12. LQI SATURATION ANALYSIS
# ============================================================
raw_radio_path = os.path.join(ROOT_DIR, 'data', 'raw', 'iotlab_radio.csv')
if os.path.exists(raw_radio_path):
    print("\n[12] Generating LQI saturation plot...")
    import pandas as pd

    # Load raw radio data (may be large, sample if needed)
    try:
        df_raw = pd.read_csv(raw_radio_path, nrows=700000)
    except Exception:
        df_raw = pd.read_csv(raw_radio_path)

    # Normalize column names
    col_map = {}
    for c in df_raw.columns:
        cl = c.strip().lower()
        if 'lqi' in cl or 'link_quality' in cl:
            col_map['lqi'] = c
        elif 'rssi' in cl or 'signal' in cl:
            col_map['rssi'] = c

    if 'lqi' in col_map and 'rssi' in col_map:
        lqi = df_raw[col_map['lqi']].dropna().values
        rssi = df_raw[col_map['rssi']].dropna().values

        fig, axes = plt.subplots(1, 2, figsize=(10, 4))

        # Panel (a): LQI histogram
        ax = axes[0]
        counts, bins, patches = ax.hist(lqi, bins=50, color='#42A5F5',
                                         edgecolor='black', linewidth=0.3, alpha=0.85)
        # Highlight the 255 bar
        for p, b in zip(patches, bins):
            if b >= 254:
                p.set_facecolor('#d32f2f')
        sat_pct = (lqi == 255).mean() * 100
        ax.annotate(f'{sat_pct:.1f}% at LQI=255',
                   xy=(255, counts[-1] if len(counts) > 0 else 0),
                   xytext=(220, counts.max() * 0.8),
                   fontsize=10, fontweight='bold', color='#d32f2f',
                   arrowprops=dict(arrowstyle='->', color='#d32f2f'))
        ax.set_xlabel('LQI value')
        ax.set_ylabel('Packet count')
        ax.set_title('(a) LQI Distribution (AT86RF231)')

        # Panel (b): LQI vs RSSI
        ax = axes[1]
        # Use the minimum of the two arrays
        n_common = min(len(lqi), len(rssi))
        lqi_c = lqi[:n_common]
        rssi_c = rssi[:n_common]

        # Bin by RSSI
        rssi_bins = np.arange(-95, -20, 5)
        bin_indices = np.digitize(rssi_c, rssi_bins)

        bin_centers = []
        lqi_means = []
        lqi_stds = []
        sat_pcts_per_bin = []

        for i in range(1, len(rssi_bins)):
            mask = bin_indices == i
            if mask.sum() > 10:
                bin_centers.append((rssi_bins[i-1] + rssi_bins[i]) / 2)
                lqi_means.append(np.mean(lqi_c[mask]))
                lqi_stds.append(np.std(lqi_c[mask]))
                sat_pcts_per_bin.append((lqi_c[mask] == 255).mean() * 100)

        ax.errorbar(bin_centers, lqi_means, yerr=lqi_stds, fmt='o-',
                   color='#1976D2', capsize=3, markersize=4, linewidth=1.5)
        ax.axhline(y=255, color='#d32f2f', linestyle='--', linewidth=0.8,
                  label='Saturation (255)')
        ax.axvline(x=-80, color='gray', linestyle=':', linewidth=0.8,
                  label='RSSI = -80 dBm')
        ax.set_xlabel('RSSI (dBm)')
        ax.set_ylabel('Mean LQI')
        ax.set_title('(b) LQI vs RSSI (per 5 dB bin)')
        ax.legend(fontsize=8)

        plt.tight_layout()
        plt.savefig(os.path.join(FIGURES_DIR, 'lqi_saturation.pdf'), dpi=300)
        plt.savefig(os.path.join(FIGURES_DIR, 'lqi_saturation.png'), dpi=300)
        plt.close()
        print(f"  Saved: lqi_saturation.pdf/png")
    else:
        print(f"  SKIPPED: Could not find LQI/RSSI columns in {raw_radio_path}")
else:
    print("  SKIPPED: raw radio data not found")


print("\nVisualization generation complete.")
