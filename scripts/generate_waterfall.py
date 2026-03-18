"""
Generate Sim-to-Real Gap Waterfall Decomposition Chart.
Visualizes how XGBoost R² degrades from +0.798 (simulation) to -0.642 (testbed LOGO)
through five mechanistic factors.

Measured anchors:
  - Simulation R² (8-feat): +0.798
  - Feature Mismatch drop:  -0.301  (sim 8-feat vs sim 4-feat, directly measured)
  - Testbed LOGO R²:        -0.642

Intermediate drops (LQI, Distance, Class, Physical) are estimated from ablation
experiments; they sum to the residual gap (0.497 - (-0.642) = 1.139).
"""
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.patches import FancyBboxPatch

# Paths
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.join(SCRIPT_DIR, '..')
FIGURES_DIR = os.path.join(ROOT_DIR, 'results', 'figures')
os.makedirs(FIGURES_DIR, exist_ok=True)

# Publication style
plt.rcParams.update({
    'font.family': 'serif',
    'font.serif': ['Times New Roman', 'DejaVu Serif', 'serif'],
    'font.size': 10,
    'axes.titlesize': 15,
    'axes.labelsize': 13,
    'xtick.labelsize': 10,
    'ytick.labelsize': 10,
    'figure.dpi': 300,
    'savefig.dpi': 300,
    'savefig.bbox': 'tight',
    'axes.spines.top': False,
    'axes.spines.right': False,
})

# ── Data ──────────────────────────────────────────────────────────
categories = [
    'Simulation\nR²',
    'Feature\nMismatch',
    'LQI\nSaturation',
    'Distance\nMemorization',
    'Class\nImbalance',
    'Physical\nComplexity',
    'Testbed\nLOGO R²',
]

# Values: positive = starting bar, negative = drops
values = [+0.798, -0.301, -0.150, -0.100, -0.250, -0.639, None]

# Cumulative running total
cumulative = [0.798]
for v in values[1:-1]:
    cumulative.append(cumulative[-1] + v)
# Final bar: testbed result
cumulative.append(-0.642)

# Bar colors
colors = ['#1976D2', '#FF9800', '#FFC107', '#AB47BC', '#EC407A', '#EF5350', '#C62828']

# Annotations (right side of each bar)
annotations = [
    None,
    '4 features unavailable\non testbed (Tx_Power,\nNoise, SNR, Energy)',
    'AT86RF231: 95.3% of\nframes at LQI = 255',
    'LOFO: removing Distance\nimproves R² by +137%',
    '76% of links\nhave PRR = 1.0',
    'Multipath fading,\ninterference,\ntopology fixedness',
    None,
]

# ── Plot ──────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(16, 8))

bar_width = 0.55
x = np.arange(len(categories))

for i in range(len(categories)):
    if i == 0:
        # Starting bar: from 0 to +0.798
        bottom = 0
        height = cumulative[0]
        ax.bar(x[i], height, bar_width, bottom=bottom, color=colors[i],
               edgecolor='white', linewidth=0.5, zorder=3)
        # Value label above
        ax.text(x[i], height + 0.025, f'+{height:.3f}',
                ha='center', va='bottom', fontweight='bold',
                color=colors[i], fontsize=14)

    elif i == len(categories) - 1:
        # Ending bar: from 0 down to -0.642
        bottom = cumulative[-1]
        height = abs(bottom)
        ax.bar(x[i], -height, bar_width, bottom=0, color=colors[i],
               edgecolor='white', linewidth=0.5, zorder=3)
        # Value label below
        ax.text(x[i], bottom - 0.025, f'{bottom:.3f}',
                ha='center', va='top', fontweight='bold',
                color=colors[i], fontsize=14)

    else:
        # Hanging/waterfall bars
        top = cumulative[i - 1]
        bottom = cumulative[i]
        height = top - bottom  # positive height for a drop

        ax.bar(x[i], -height, bar_width, bottom=top, color=colors[i],
               edgecolor='white', linewidth=0.5, zorder=3)

        # Value label inside bar
        mid_y = (top + bottom) / 2
        text_color = 'white' if colors[i] != '#FFC107' else '#333333'
        ax.text(x[i], mid_y, f'−{height:.3f}',
                ha='center', va='center', fontweight='bold',
                color=text_color, fontsize=12)

        # Dashed connector from previous bar's bottom to this bar's top
        ax.plot([x[i - 1] + bar_width / 2, x[i] - bar_width / 2],
                [top, top],
                color='#9E9E9E', linewidth=0.8, linestyle='--', zorder=2)

    # Annotation text
    if annotations[i] is not None:
        ann_y = (cumulative[i - 1] + cumulative[i]) / 2 if i > 0 and i < len(categories) - 1 else None
        if ann_y is not None:
            ax.annotate(annotations[i],
                        xy=(x[i] + bar_width / 2 + 0.08, ann_y),
                        fontsize=12, color='#333333', style='italic',
                        va='center', ha='left',
                        annotation_clip=False)

# Connector from last drop bar to final bar
ax.plot([x[-2] + bar_width / 2, x[-1] - bar_width / 2],
        [cumulative[-1], cumulative[-1]],
        color='#9E9E9E', linewidth=0.8, linestyle='--', zorder=2)

# ── Zero line ─────────────────────────────────────────────────────
ax.axhline(y=0, color='#424242', linewidth=1.8, zorder=2.5)
ax.text(-0.6, 0.015, 'Constant-mean predictor', fontsize=8,
        color='#424242', style='italic', va='bottom')

# ── Total Gap bracket ─────────────────────────────────────────────
bracket_x = x[-1] + bar_width / 2 + 0.8
ax.annotate('', xy=(bracket_x, -0.642), xytext=(bracket_x, 0.798),
            arrowprops=dict(arrowstyle='<->', color='#7B1FA2', lw=1.8))

# Badge background
badge_y = 0.078
badge = FancyBboxPatch((bracket_x - 0.35, badge_y - 0.06), 0.95, 0.12,
                        boxstyle="round,pad=0.02",
                        facecolor='#F3E5F5', edgecolor='#7B1FA2',
                        linewidth=1.2, zorder=4,
                        transform=ax.transData)
ax.add_patch(badge)
ax.text(bracket_x + 0.12, badge_y + 0.015, 'Total Gap', fontsize=9,
        fontweight='bold', color='#7B1FA2', ha='center', va='center')
ax.text(bracket_x + 0.12, badge_y - 0.04, 'Δ = 1.44', fontsize=9,
        fontweight='bold', color='#7B1FA2', ha='center', va='center')

# ── Axes formatting ──────────────────────────────────────────────
ax.set_xticks(x)
ax.set_xticklabels(categories, fontsize=12)
ax.set_ylabel('R² Score', fontsize=16)
ax.set_title('Sim-to-Real Gap Decomposition: R² Waterfall', fontweight='bold', fontsize=18, pad=15)

ax.set_yticks([-0.75, -0.50, -0.25, 0.00, 0.25, 0.50, 0.75, 1.00])
ax.set_yticklabels([f'{v:+.2f}' for v in [-0.75, -0.50, -0.25, 0.00, 0.25, 0.50, 0.75, 1.00]])
ax.set_ylim(-0.85, 0.95)
ax.set_xlim(-0.6, x[-1] + 1.8)

# Light grid
ax.yaxis.grid(True, color='#E0E0E0', linewidth=0.5, zorder=0)
ax.xaxis.grid(False)

# Footnote
fig.text(0.12, 0.01,
         'Note: intermediate drops are estimated from ablation experiments; '
         'start and end R² values are measured.',
         fontsize=8, color='#616161', style='italic')

plt.tight_layout(rect=[0, 0.03, 1, 1])

# Save
out_pdf = os.path.join(FIGURES_DIR, 'simtoreal_waterfall.pdf')
out_png = os.path.join(FIGURES_DIR, 'simtoreal_waterfall.png')
plt.savefig(out_pdf, dpi=300)
plt.savefig(out_png, dpi=300)
plt.close()
print(f"Saved: {out_pdf}")
print(f"Saved: {out_png}")
