/*
 * CART Decision Tree -- Depth 4
 * Auto-generated from sklearn DecisionTreeRegressor
 * Target: PRR (Packet Reception Rate) prediction
 */

float predict_cart(float *input) {
    if (input[4] <= -95.000000f) {
        if (input[2] <= 32.500000f) {
            if (input[0] <= -12.500000f) {
                if (input[0] <= -20.000000f) {
                    return 0.242732f;
                } else {
                    return 0.124897f;
                }
            } else {
                if (input[0] <= -7.500000f) {
                    return 0.052861f;
                } else {
                    return 0.006108f;
                }
            }
        } else {
            if (input[0] <= -20.000000f) {
                if (input[2] <= 45.500000f) {
                    return 0.085876f;
                } else {
                    return 0.018638f;
                }
            } else {
                if (input[2] <= 40.500000f) {
                    return 0.021889f;
                } else {
                    return 0.002671f;
                }
            }
        }
    } else {
        if (input[1] <= 12.295000f) {
            if (input[2] <= 45.500000f) {
                if (input[0] <= -7.500000f) {
                    return 0.085999f;
                } else {
                    return 0.009053f;
                }
            } else {
                if (input[0] <= -7.500000f) {
                    return 0.005562f;
                } else {
                    return 0.000000f;
                }
            }
        } else {
            if (input[5] <= -2.575000f) {
                if (input[5] <= -3.185000f) {
                    return 0.000002f;
                } else {
                    return 0.000727f;
                }
            } else {
                if (input[2] <= 40.500000f) {
                    return 0.016148f;
                } else {
                    return 0.000754f;
                }
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
