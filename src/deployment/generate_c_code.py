"""
Generate C code for embedded deployment comparison:
1. Full XGBoost model -> C (via m2cgen)
2. ALE-extracted rule -> C (hand-written)
"""
import os
import json

import re
import m2cgen as m2c
import xgboost as xgb

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
FIRMWARE_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'firmware')

# Load the trained model
model = xgb.XGBRegressor()
model.load_model(os.path.join(PROCESSED_DIR, 'xgboost_model.json'))

# Load thresholds
with open(os.path.join(PROCESSED_DIR, 'extracted_thresholds.json')) as f:
    thresholds = json.load(f)

# ============================================================
# 1. Generate XGBoost full model C code
# ============================================================
print("Generating XGBoost C code via m2cgen...")
xgb_c_code = m2c.export_to_c(model)
# Fix 'nan' conflicts with GCC math.h (robust regex replacement)
xgb_c_code = re.sub(r'\bnan\b', 'NAN', xgb_c_code)
# Convert double to float for fair comparison with CART/LinReg on ARM Cortex-M
# (ARM Cortex-M3 has single-precision FPU only; double is software-emulated)
xgb_c_code = xgb_c_code.replace('double ', 'float ')
xgb_c_code = xgb_c_code.replace('double\n', 'float\n')

xgb_full = f"""/*
 * XGBoost Full Model -- Auto-generated via m2cgen
 * 150 trees, max_depth=6
 * Target: PRR (PRR) prediction
 * Features: Tx_Power, Distance, Local_Density, RSSI, Noise, SNR, Init_Energy, Residual_Energy
 * NOTE: Converted to single-precision float for ARM Cortex-M3 compatibility.
 */
#include <math.h>

{xgb_c_code}

/* Entry point -- predict PRR */
float predict_xgboost(float tx_power, float distance, float density, float rssi,
                      float noise, float snr, float init_energy,
                      float residual_energy) {{
    float input[8] = {{tx_power, distance, density, rssi, noise, snr,
                       init_energy, residual_energy}};
    return score(input);
}}

/* Minimal main for size measurement */
volatile float result;
int main(void) {{
    result = predict_xgboost(-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f);
    return 0;
}}
"""

os.makedirs(os.path.join(FIRMWARE_DIR, 'xgboost_full'), exist_ok=True)
xgb_path = os.path.join(FIRMWARE_DIR, 'xgboost_full', 'main.c')
with open(xgb_path, 'w') as f:
    f.write(xgb_full)
print(f"  Written: {xgb_path}")
print(f"  C source size: {os.path.getsize(xgb_path):,} bytes")

# ============================================================
# 2. Generate ALE rule C code
# ============================================================
print("\nGenerating ALE rule C code...")

snr_low = thresholds['snr_low']
snr_high = thresholds['snr_high']
coefs = thresholds['rule_coefs']
lut = thresholds['density_lut']

ale_rule = f"""/*
 * ALE-Extracted Rule -- WSN Detection Accuracy Predictor
 * Empirical data-driven rule (no analytical equations)
 *
 * Performance: R2 = {thresholds['model_metrics']['rule_r2_mean']:.4f} +/- {thresholds['model_metrics']['rule_r2_std']:.4f}
 *   vs XGBoost R2 = {thresholds['model_metrics']['xgboost_r2_mean']:.4f} +/- {thresholds['model_metrics']['xgboost_r2_std']:.4f}
 */

float predict_accuracy(float snr_db, float local_density) {{
    float base_feature = 0.0f;

    /* 1. Extract SNR Feature */
    if (snr_db <= {snr_low}f) {{
        base_feature = 0.0f;
    }} else if (snr_db >= {snr_high}f) {{
        base_feature = 1.0f;
    }} else {{
        base_feature = (snr_db - {snr_low}f) / ({snr_high}f - {snr_low}f);
    }}

    /* 2. Extract Density Feature from LUT (Linear Interpolation) */
    float effect_feature = 0.0f;
    if (local_density <= {lut[0]['density']}f) {{
        effect_feature = {lut[0]['ale_effect']}f;
    }} else if (local_density >= {lut[4]['density']}f) {{
        effect_feature = {lut[4]['ale_effect']}f;
    }} else if (local_density <= {lut[1]['density']}f) {{
        effect_feature = {lut[0]['ale_effect']}f + (local_density - {lut[0]['density']}f) / ({lut[1]['density']}f - {lut[0]['density']}f) * ({lut[1]['ale_effect']}f - {lut[0]['ale_effect']}f);
    }} else if (local_density <= {lut[2]['density']}f) {{
        effect_feature = {lut[1]['ale_effect']}f + (local_density - {lut[1]['density']}f) / ({lut[2]['density']}f - {lut[1]['density']}f) * ({lut[2]['ale_effect']}f - {lut[1]['ale_effect']}f);
    }} else if (local_density <= {lut[3]['density']}f) {{
        effect_feature = {lut[2]['ale_effect']}f + (local_density - {lut[2]['density']}f) / ({lut[3]['density']}f - {lut[2]['density']}f) * ({lut[3]['ale_effect']}f - {lut[2]['ale_effect']}f);
    }} else {{
        effect_feature = {lut[3]['ale_effect']}f + (local_density - {lut[3]['density']}f) / ({lut[4]['density']}f - {lut[3]['density']}f) * ({lut[4]['ale_effect']}f - {lut[3]['ale_effect']}f);
    }}

    /* 3. Apply Linear Calibration Weights */
    float prediction = ({coefs['base_weight']}f * base_feature) +
                       ({coefs['density_weight']}f * effect_feature) +
                       {coefs['intercept']}f;

    if (prediction < 0.0f) prediction = 0.0f;
    if (prediction > 1.0f) prediction = 1.0f;

    return prediction;
}}

/* Minimal main for size measurement */
volatile float result;
int main(void) {{
    result = predict_accuracy(8.0f, 15.0f);
    return 0;
}}
"""

os.makedirs(os.path.join(FIRMWARE_DIR, 'ale_rule'), exist_ok=True)
ale_path = os.path.join(FIRMWARE_DIR, 'ale_rule', 'main.c')
with open(ale_path, 'w') as f:
    f.write(ale_rule)
print(f"  Written: {ale_path}")
print(f"  C source size: {os.path.getsize(ale_path):,} bytes")

print("\nBoth C files generated. Ready for compilation.")
