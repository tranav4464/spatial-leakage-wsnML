/*
 * CART Decision Tree -- Depth 5
 * Auto-generated from sklearn DecisionTreeRegressor
 * Target: PRR (Packet Reception Rate) prediction
 */

float predict_cart(float *input) {
    if (input[4] <= -95.000000f) {
        if (input[2] <= 32.500000f) {
            if (input[0] <= -12.500000f) {
                if (input[0] <= -20.000000f) {
                    if (input[2] <= 22.500000f) {
                        return 0.333287f;
                    } else {
                        return 0.180550f;
                    }
                } else {
                    if (input[2] <= 20.500000f) {
                        return 0.167453f;
                    } else {
                        return 0.105146f;
                    }
                }
            } else {
                if (input[0] <= -7.500000f) {
                    if (input[1] <= 49.529999f) {
                        return 0.064000f;
                    } else {
                        return 0.025046f;
                    }
                } else {
                    if (input[0] <= -2.500000f) {
                        return 0.009000f;
                    } else {
                        return 0.003093f;
                    }
                }
            }
        } else {
            if (input[0] <= -20.000000f) {
                if (input[2] <= 45.500000f) {
                    if (input[1] <= 31.795000f) {
                        return 0.140494f;
                    } else {
                        return 0.073326f;
                    }
                } else {
                    if (input[2] <= 62.500000f) {
                        return 0.034356f;
                    } else {
                        return 0.010509f;
                    }
                }
            } else {
                if (input[2] <= 40.500000f) {
                    if (input[1] <= 32.924999f) {
                        return 0.054414f;
                    } else {
                        return 0.006985f;
                    }
                } else {
                    if (input[0] <= -12.500000f) {
                        return 0.008294f;
                    } else {
                        return 0.000726f;
                    }
                }
            }
        }
    } else {
        if (input[1] <= 12.295000f) {
            if (input[2] <= 45.500000f) {
                if (input[0] <= -7.500000f) {
                    if (input[5] <= -2.160000f) {
                        return 0.004660f;
                    } else {
                        return 0.138735f;
                    }
                } else {
                    if (input[0] <= -2.500000f) {
                        return 0.014332f;
                    } else {
                        return 0.003312f;
                    }
                }
            } else {
                if (input[0] <= -7.500000f) {
                    if (input[2] <= 83.500000f) {
                        return 0.010896f;
                    } else {
                        return 0.002001f;
                    }
                } else {
                    return 0.000000f;
                }
            }
        } else {
            if (input[5] <= -2.575000f) {
                if (input[5] <= -3.185000f) {
                    if (input[3] <= -83.715000f) {
                        return 0.000001f;
                    } else {
                        return 0.000231f;
                    }
                } else {
                    if (input[2] <= 37.500000f) {
                        return 0.002840f;
                    } else {
                        return 0.000143f;
                    }
                }
            } else {
                if (input[2] <= 40.500000f) {
                    if (input[0] <= -7.500000f) {
                        return 0.073387f;
                    } else {
                        return 0.005774f;
                    }
                } else {
                    if (input[0] <= -12.500000f) {
                        return 0.007769f;
                    } else {
                        return 0.000374f;
                    }
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
