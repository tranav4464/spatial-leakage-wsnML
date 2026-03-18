/*
 * CART Decision Tree -- Depth 3
 * Auto-generated from sklearn DecisionTreeRegressor
 * Target: PRR (Packet Reception Rate) prediction
 */

float predict_cart(float *input) {
    if (input[4] <= -95.000000f) {
        if (input[2] <= 32.500000f) {
            if (input[0] <= -12.500000f) {
                return 0.184865f;
            } else {
                return 0.021988f;
            }
        } else {
            if (input[0] <= -20.000000f) {
                return 0.030991f;
            } else {
                return 0.005020f;
            }
        }
    } else {
        if (input[1] <= 12.295000f) {
            if (input[2] <= 45.500000f) {
                return 0.057295f;
            } else {
                return 0.003340f;
            }
        } else {
            if (input[5] <= -2.575000f) {
                return 0.000013f;
            } else {
                return 0.003977f;
            }
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
