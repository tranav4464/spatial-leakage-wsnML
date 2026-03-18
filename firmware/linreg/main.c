/*
 * Linear Regression -- WSN Detection Accuracy Predictor
 * Auto-generated from sklearn LinearRegression
 * y = intercept + sum(coef_i * x_i)
 */

float predict_linreg(float *input) {
    float prediction =
    -0.0248062091f
    + (-0.0012074682f * input[0])  /* Transmission_Power_dBm */
    + (-0.0003803051f * input[1])  /* Distance_to_Sink_m */
    + (-0.0005061298f * input[2])  /* Local_Density */
    + (-0.0000834654f * input[3])  /* Signal_Strength_RSSI_dBm */
    + (-0.0006236958f * input[4])  /* Noise_Level_dBm */
    + (0.0005402304f * input[5])  /* SNR_dB */
    + (0.0051422457f * input[6])  /* Initial_Energy_J */
    + (-0.0050439615f * input[7])  /* Residual_Energy_J */;

    if (prediction < 0.0f) prediction = 0.0f;
    if (prediction > 1.0f) prediction = 1.0f;
    return prediction;
}

/* Minimal main for size measurement */
volatile float result;
int main(void) {
    float input[8] = {-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f};
    result = predict_linreg(input);
    return 0;
}
