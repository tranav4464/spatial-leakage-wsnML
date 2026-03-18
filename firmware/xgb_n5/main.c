#include <math.h>
float score(float * input) {
    float var0;
    if (input[4] >= -95.0) {
        if (input[5] >= -2.065) {
            if (input[0] >= -7.5) {
                var0 = -0.049863346;
            } else {
                var0 = -0.047652077;
            }
        } else {
            var0 = -0.049993545;
        }
    } else {
        if (input[0] >= -20.0) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var0 = -0.04985581;
                } else {
                    var0 = -0.048651118;
                }
            } else {
                if (input[7] >= 1.5018605) {
                    var0 = -0.04673898;
                } else {
                    var0 = -0.036110833;
                }
            }
        } else {
            if (input[7] >= 1.515097) {
                if (input[3] >= -99.805) {
                    var0 = -0.046334732;
                } else {
                    if (input[7] >= 1.9744315) {
                        if (input[7] >= 1.9826026) {
                            var0 = -0.042683806;
                        } else {
                            var0 = -0.013940001;
                        }
                    } else {
                        if (input[3] >= -99.845) {
                            var0 = -0.011665001;
                        } else {
                            var0 = -0.043902155;
                        }
                    }
                }
            } else {
                if (input[7] >= 1.4781106) {
                    if (input[7] >= 1.5149795) {
                        var0 = 0.0016649992;
                    } else {
                        var0 = -0.032431044;
                    }
                } else {
                    if (input[7] >= 1.475567) {
                        if (input[7] >= 1.4773641) {
                            var0 = -0.005;
                        } else {
                            var0 = 0.015000001;
                        }
                    } else {
                        if (input[7] >= 1.4526961) {
                            var0 = -0.015757274;
                        } else {
                            var0 = -0.004443334;
                        }
                    }
                }
            }
        }
    }
    float var1;
    if (input[2] >= 36.5) {
        if (input[2] >= 44.5) {
            if (input[0] >= -20.0) {
                var1 = -0.044950757;
            } else {
                if (input[5] >= -1.805) {
                    if (input[2] >= 62.5) {
                        var1 = -0.04452893;
                    } else {
                        var1 = -0.042086303;
                    }
                } else {
                    var1 = -0.044995904;
                }
            }
        } else {
            if (input[5] >= -0.695) {
                if (input[0] >= -12.5) {
                    if (input[1] >= 26.965) {
                        var1 = -0.044903245;
                    } else {
                        if (input[0] >= -7.5) {
                            var1 = -0.04414275;
                        } else {
                            var1 = -0.037304934;
                        }
                    }
                } else {
                    if (input[1] >= 32.635002) {
                        if (input[0] >= -20.0) {
                            var1 = -0.04342598;
                        } else {
                            var1 = -0.03890459;
                        }
                    } else {
                        var1 = -0.034408115;
                    }
                }
            } else {
                var1 = -0.04496912;
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 12.995) {
                if (input[5] >= -1.885) {
                    if (input[0] >= -7.5) {
                        var1 = -0.044311456;
                    } else {
                        if (input[0] >= -12.5) {
                            var1 = -0.038673546;
                        } else {
                            var1 = -0.03122471;
                        }
                    }
                } else {
                    var1 = -0.044983022;
                }
            } else {
                if (input[0] >= -7.5) {
                    var1 = -0.04404367;
                } else {
                    if (input[5] >= -1.5550001) {
                        if (input[2] >= 25.5) {
                            var1 = -0.030126551;
                        } else {
                            var1 = -0.013132728;
                        }
                    } else {
                        var1 = -0.043781552;
                    }
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var1 = -0.044443663;
                } else {
                    if (input[1] >= 42.635002) {
                        if (input[2] >= 22.5) {
                            var1 = -0.044167213;
                        } else {
                            var1 = -0.039101455;
                        }
                    } else {
                        if (input[1] >= 14.17) {
                            var1 = -0.03870727;
                        } else {
                            var1 = -0.033399012;
                        }
                    }
                }
            } else {
                if (input[2] >= 22.5) {
                    if (input[1] >= 41.61) {
                        if (input[0] >= -20.0) {
                            var1 = -0.04133082;
                        } else {
                            var1 = -0.03281446;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var1 = -0.03196996;
                        } else {
                            var1 = -0.0271264;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[2] >= 14.5) {
                            var1 = -0.030799422;
                        } else {
                            var1 = -0.023719031;
                        }
                    } else {
                        if (input[2] >= 13.5) {
                            var1 = -0.014756605;
                        } else {
                            var1 = 0.0014546276;
                        }
                    }
                }
            }
        }
    }
    float var2;
    if (input[2] >= 35.5) {
        if (input[2] >= 45.5) {
            var2 = -0.040393103;
        } else {
            if (input[1] >= 26.16) {
                if (input[0] >= -20.0) {
                    var2 = -0.040340435;
                } else {
                    var2 = -0.03859962;
                }
            } else {
                if (input[0] >= -7.5) {
                    var2 = -0.03975012;
                } else {
                    if (input[3] >= -82.93) {
                        var2 = -0.031168884;
                    } else {
                        var2 = -0.036406413;
                    }
                }
            }
        }
    } else {
        if (input[0] >= -12.5) {
            if (input[0] >= -7.5) {
                var2 = -0.040230688;
            } else {
                if (input[3] >= -82.545) {
                    var2 = -0.029764926;
                } else {
                    if (input[3] >= -91.675) {
                        var2 = -0.03619523;
                    } else {
                        var2 = -0.03916623;
                    }
                }
            }
        } else {
            if (input[2] >= 20.5) {
                if (input[3] >= -90.515) {
                    if (input[3] >= -82.765) {
                        if (input[2] >= 27.5) {
                            var2 = -0.02478387;
                        } else {
                            var2 = -0.016308103;
                        }
                    } else {
                        if (input[2] >= 24.5) {
                            var2 = -0.03074258;
                        } else {
                            var2 = -0.0062736417;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[1] >= 43.684998) {
                            var2 = -0.0394758;
                        } else {
                            var2 = -0.036795873;
                        }
                    } else {
                        if (input[7] >= 1.5235455) {
                            var2 = -0.035613082;
                        } else {
                            var2 = -0.02517218;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[3] >= -88.905) {
                        if (input[3] >= -84.035) {
                            var2 = -0.003625761;
                        } else {
                            var2 = -0.00029576125;
                        }
                    } else {
                        if (input[7] >= 1.504657) {
                            var2 = -0.03531467;
                        } else {
                            var2 = -0.023730792;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        if (input[7] >= 1.518888) {
                            var2 = -0.030919937;
                        } else {
                            var2 = -0.010885011;
                        }
                    } else {
                        if (input[1] >= 59.3) {
                            var2 = -0.02905399;
                        } else {
                            var2 = -0.009453799;
                        }
                    }
                }
            }
        }
    }
    float var3;
    if (input[4] >= -95.0) {
        if (input[1] >= 12.335) {
            var3 = -0.036469948;
        } else {
            if (input[2] >= 46.0) {
                var3 = -0.03623344;
            } else {
                if (input[0] >= -7.5) {
                    var3 = -0.03552347;
                } else {
                    if (input[3] >= -88.134995) {
                        if (input[4] >= -85.0) {
                            var3 = -0.029389402;
                        } else {
                            var3 = -0.024429325;
                        }
                    } else {
                        if (input[2] >= 24.5) {
                            var3 = -0.035420768;
                        } else {
                            var3 = -0.007654279;
                        }
                    }
                }
            }
        }
    } else {
        if (input[2] >= 32.5) {
            if (input[2] >= 42.5) {
                if (input[0] >= -20.0) {
                    var3 = -0.036346357;
                } else {
                    if (input[2] >= 56.5) {
                        if (input[2] >= 69.5) {
                            var3 = -0.03640682;
                        } else {
                            var3 = -0.0349958;
                        }
                    } else {
                        var3 = -0.03329217;
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[1] >= 30.65) {
                        var3 = -0.036376093;
                    } else {
                        if (input[0] >= -7.5) {
                            var3 = -0.035606414;
                        } else {
                            var3 = -0.03003185;
                        }
                    }
                } else {
                    if (input[1] >= 35.06) {
                        if (input[0] >= -20.0) {
                            var3 = -0.034845423;
                        } else {
                            var3 = -0.030491045;
                        }
                    } else {
                        if (input[1] >= 20.529999) {
                            var3 = -0.02732945;
                        } else {
                            var3 = -0.02506322;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var3 = -0.035933148;
                } else {
                    if (input[1] >= 46.38) {
                        if (input[2] >= 19.5) {
                            var3 = -0.035817664;
                        } else {
                            var3 = -0.031318273;
                        }
                    } else {
                        if (input[1] >= 6.975) {
                            var3 = -0.030844662;
                        } else {
                            var3 = -0.018949773;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[2] >= 17.5) {
                        if (input[1] >= 48.120003) {
                            var3 = -0.03256397;
                        } else {
                            var3 = -0.024846885;
                        }
                    } else {
                        if (input[2] >= 7.5) {
                            var3 = -0.02051838;
                        } else {
                            var3 = -0.0062041837;
                        }
                    }
                } else {
                    if (input[2] >= 18.5) {
                        if (input[2] >= 24.5) {
                            var3 = -0.022024525;
                        } else {
                            var3 = -0.014354906;
                        }
                    } else {
                        if (input[2] >= 10.5) {
                            var3 = -0.004956789;
                        } else {
                            var3 = 0.012601191;
                        }
                    }
                }
            }
        }
    }
    float var4;
    if (input[2] >= 35.5) {
        if (input[2] >= 42.5) {
            if (input[0] >= -12.5) {
                var4 = -0.03281815;
            } else {
                if (input[5] >= -1.975) {
                    if (input[2] >= 67.5) {
                        var4 = -0.032701723;
                    } else {
                        if (input[0] >= -20.0) {
                            var4 = -0.031874593;
                        } else {
                            var4 = -0.03060073;
                        }
                    }
                } else {
                    var4 = -0.032819256;
                }
            }
        } else {
            if (input[5] >= -0.695) {
                if (input[0] >= -12.5) {
                    if (input[1] >= 27.724998) {
                        var4 = -0.032729622;
                    } else {
                        if (input[0] >= -7.5) {
                            var4 = -0.032137893;
                        } else {
                            var4 = -0.02685371;
                        }
                    }
                } else {
                    if (input[1] >= 32.57) {
                        if (input[0] >= -20.0) {
                            var4 = -0.03149035;
                        } else {
                            var4 = -0.027464835;
                        }
                    } else {
                        var4 = -0.023983326;
                    }
                }
            } else {
                var4 = -0.0328526;
            }
        }
    } else {
        if (input[5] >= -0.195) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var4 = -0.032333225;
                } else {
                    if (input[1] >= 43.72) {
                        if (input[2] >= 21.5) {
                            var4 = -0.032305725;
                        } else {
                            var4 = -0.027798822;
                        }
                    } else {
                        if (input[3] >= -73.41) {
                            var4 = -0.019571366;
                        } else {
                            var4 = -0.027579492;
                        }
                    }
                }
            } else {
                if (input[2] >= 22.5) {
                    if (input[1] >= 43.79) {
                        if (input[0] >= -20.0) {
                            var4 = -0.030396018;
                        } else {
                            var4 = -0.024023686;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var4 = -0.022734074;
                        } else {
                            var4 = -0.018144172;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[2] >= 14.5) {
                            var4 = -0.02151146;
                        } else {
                            var4 = -0.015676348;
                        }
                    } else {
                        if (input[2] >= 12.5) {
                            var4 = -0.008976088;
                        } else {
                            var4 = 0.004869618;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.2150002) {
                if (input[0] >= -7.5) {
                    var4 = -0.03238749;
                } else {
                    if (input[1] >= 5.12) {
                        if (input[5] >= -0.22) {
                            var4 = -0.0053854617;
                        } else {
                            var4 = -0.02648047;
                        }
                    } else {
                        var4 = 0.0020706342;
                    }
                }
            } else {
                var4 = -0.033042822;
            }
        }
    }
    return NAN + (var0 + var1 + var2 + var3 + var4);
}

volatile float result;
int main(void) {
    float input[8] = {-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f};
    result = score(input);
    return 0;
}
