/*
 * CART Decision Tree -- Depth 2
 * Auto-generated from sklearn DecisionTreeRegressor
 * Target: PRR (Packet Reception Rate) prediction
 */

float predict_cart(float *input) {
    if (input[4] <= -95.000000f) {
        if (input[2] <= 32.500000f) {
            return 0.087424f;
        } else {
            return 0.010226f;
        }
    } else {
        if (input[1] <= 12.295000f) {
            return 0.011955f;
        } else {
            return 0.000645f;
        }
    }
}

/* Minimal main for size measurement */
volatile float result;
int main(void) {
    float input[8] = {-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f};
    result = predict_cart(input);
    return 0;
}
