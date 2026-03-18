/*
 * ALE-Extracted Rule -- WSN Detection Accuracy Predictor
 * Empirical data-driven rule (no analytical equations)
 *
 * Performance: R2 = 0.1437 +/- 0.0148
 *   vs XGBoost R2 = 0.7978 +/- 0.0422
 */

float predict_accuracy(float snr_db, float local_density) {
    float base_feature = 0.0f;

    /* 1. Extract SNR Feature */
    if (snr_db <= -4.75f) {
        base_feature = 0.0f;
    } else if (snr_db >= 1.25f) {
        base_feature = 1.0f;
    } else {
        base_feature = (snr_db - -4.75f) / (1.25f - -4.75f);
    }

    /* 2. Extract Density Feature from LUT (Linear Interpolation) */
    float effect_feature = 0.0f;
    if (local_density <= 10.5f) {
        effect_feature = 0.0379f;
    } else if (local_density >= 121.5f) {
        effect_feature = -0.0078f;
    } else if (local_density <= 37.0f) {
        effect_feature = 0.0379f + (local_density - 10.5f) / (37.0f - 10.5f) * (0.0023f - 0.0379f);
    } else if (local_density <= 57.5f) {
        effect_feature = 0.0023f + (local_density - 37.0f) / (57.5f - 37.0f) * (-0.004f - 0.0023f);
    } else if (local_density <= 76.5f) {
        effect_feature = -0.004f + (local_density - 57.5f) / (76.5f - 57.5f) * (-0.0066f - -0.004f);
    } else {
        effect_feature = -0.0066f + (local_density - 76.5f) / (121.5f - 76.5f) * (-0.0078f - -0.0066f);
    }

    /* 3. Apply Linear Calibration Weights */
    float prediction = (0.020618732780908082f * base_feature) +
                       (1.1957444862761497f * effect_feature) +
                       -0.00044025651344063894f;

    if (prediction < 0.0f) prediction = 0.0f;
    if (prediction > 1.0f) prediction = 1.0f;

    return prediction;
}

/* Minimal main for size measurement */
volatile float result;
int main(void) {
    result = predict_accuracy(8.0f, 15.0f);
    return 0;
}
