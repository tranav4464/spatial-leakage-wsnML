"""
Export sklearn LinearRegression to C code.
Trivial dot product: y = b0 + b1*x1 + ... + b8*x8
"""
import os
import json
import csv
import numpy as np
from sklearn.linear_model import LinearRegression

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROCESSED_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'processed')
FIRMWARE_DIR = os.path.join(SCRIPT_DIR, '..', '..', 'firmware')
DATASET_PATH = os.path.join(SCRIPT_DIR, '..', '..', 'data', 'raw', 'wsn_dataset.csv')

FEATURE_COLS = [
    'Transmission_Power_dBm', 'Distance_to_Sink_m', 'Local_Density',
    'Signal_Strength_RSSI_dBm', 'Noise_Level_dBm', 'SNR_dB',
    'Initial_Energy_J', 'Residual_Energy_J',
]


def main():
    print("Generating Linear Regression C code...")

    X_data, y_data = [], []
    with open(DATASET_PATH) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if float(row['Residual_Energy_J']) > 0:
                X_data.append([float(row[c]) for c in FEATURE_COLS])
                y_data.append(float(row.get('PRR') or row.get('Detection_Accuracy')))

    X = np.array(X_data)
    y = np.array(y_data)

    model = LinearRegression()
    model.fit(X, y)

    coefs = model.coef_
    intercept = model.intercept_

    terms = [f"    {intercept:.10f}f"]
    for i, (name, c) in enumerate(zip(FEATURE_COLS, coefs)):
        terms.append(f"    + ({c:.10f}f * input[{i}])  /* {name} */")

    c_code = f"""/*
 * Linear Regression -- WSN Detection Accuracy Predictor
 * Auto-generated from sklearn LinearRegression
 * y = intercept + sum(coef_i * x_i)
 */

float predict_linreg(float *input) {{
    float prediction =
{chr(10).join(terms)};

    if (prediction < 0.0f) prediction = 0.0f;
    if (prediction > 1.0f) prediction = 1.0f;
    return prediction;
}}

/* Minimal main for size measurement */
volatile float result;
int main(void) {{
    float input[8] = {{-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f}};
    result = predict_linreg(input);
    return 0;
}}
"""

    linreg_dir = os.path.join(FIRMWARE_DIR, 'linreg')
    os.makedirs(linreg_dir, exist_ok=True)
    c_path = os.path.join(linreg_dir, 'main.c')
    with open(c_path, 'w') as f:
        f.write(c_code)
    print(f"  Written: {c_path} ({os.path.getsize(c_path):,} bytes)")


if __name__ == '__main__':
    main()
