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
    float var5;
    if (input[4] >= -95.0) {
        if (input[5] >= -2.4050002) {
            if (input[0] >= -7.5) {
                var5 = -0.029445915;
            } else {
                if (input[0] >= -12.5) {
                    var5 = -0.028465157;
                } else {
                    if (input[7] >= 1.4827476) {
                        var5 = -0.027241578;
                    } else {
                        var5 = -0.0056007016;
                    }
                }
            }
        } else {
            var5 = -0.029591748;
        }
    } else {
        if (input[0] >= -20.0) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var5 = -0.029460276;
                } else {
                    var5 = -0.028680904;
                }
            } else {
                if (input[6] >= 3.5) {
                    if (input[7] >= 4.4928284) {
                        if (input[1] >= 50.415) {
                            var5 = -0.02601488;
                        } else {
                            var5 = -0.027414829;
                        }
                    } else {
                        if (input[1] >= 52.295) {
                            var5 = -0.0010549099;
                        } else {
                            var5 = -0.016221441;
                        }
                    }
                } else {
                    var5 = -0.027926117;
                }
            }
        } else {
            if (input[1] >= 41.105) {
                if (input[1] >= 53.795) {
                    if (input[1] >= 53.855) {
                        if (input[1] >= 61.015) {
                            var5 = -0.010949032;
                        } else {
                            var5 = -0.019239333;
                        }
                    } else {
                        if (input[1] >= 53.825) {
                            var5 = 0.010181618;
                        } else {
                            var5 = -0.0054706563;
                        }
                    }
                } else {
                    if (input[7] >= 1.479478) {
                        if (input[1] >= 49.440002) {
                            var5 = -0.02169765;
                        } else {
                            var5 = -0.023604883;
                        }
                    } else {
                        var5 = -0.0052369977;
                    }
                }
            } else {
                if (input[1] >= 34.965) {
                    if (input[7] >= 1.5144329) {
                        if (input[1] >= 34.975) {
                            var5 = -0.025489679;
                        } else {
                            var5 = -0.012972078;
                        }
                    } else {
                        if (input[7] >= 1.5121645) {
                            var5 = -0.0042366027;
                        } else {
                            var5 = -0.017407376;
                        }
                    }
                } else {
                    if (input[7] >= 1.5149424) {
                        var5 = -0.0269918;
                    } else {
                        if (input[7] >= 1.5140414) {
                            var5 = -0.002090086;
                        } else {
                            var5 = -0.020062625;
                        }
                    }
                }
            }
        }
    }
    float var6;
    if (input[4] >= -95.0) {
        if (input[5] >= -2.205) {
            if (input[0] >= -7.5) {
                var6 = -0.026499962;
            } else {
                if (input[0] >= -12.5) {
                    var6 = -0.02558121;
                } else {
                    if (input[7] >= 1.4827476) {
                        var6 = -0.024597056;
                    } else {
                        var6 = -0.005320667;
                    }
                }
            }
        } else {
            var6 = -0.02663192;
        }
    } else {
        if (input[0] >= -20.0) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var6 = -0.026506975;
                } else {
                    var6 = -0.025832579;
                }
            } else {
                if (input[1] >= 0.985) {
                    var6 = -0.024717068;
                } else {
                    if (input[5] >= 45.47) {
                        var6 = -0.013098854;
                    } else {
                        var6 = 0.0022594302;
                    }
                }
            }
        } else {
            if (input[1] >= 41.075) {
                if (input[1] >= 49.440002) {
                    if (input[1] >= 60.705) {
                        if (input[7] >= 9.746229) {
                            var6 = -0.0004130736;
                        } else {
                            var6 = -0.012941546;
                        }
                    } else {
                        if (input[7] >= 1.482605) {
                            var6 = -0.018568108;
                        } else {
                            var6 = 0.00020343215;
                        }
                    }
                } else {
                    if (input[7] >= 1.4980915) {
                        if (input[7] >= 9.6561165) {
                            var6 = -0.022502964;
                        } else {
                            var6 = -0.020962764;
                        }
                    } else {
                        if (input[7] >= 1.490464) {
                            var6 = -0.001164025;
                        } else {
                            var6 = -0.010634005;
                        }
                    }
                }
            } else {
                if (input[1] >= 35.010002) {
                    if (input[7] >= 1.5172485) {
                        if (input[1] >= 35.045) {
                            var6 = -0.023147488;
                        } else {
                            var6 = -0.013870415;
                        }
                    } else {
                        var6 = -0.01567922;
                    }
                } else {
                    if (input[7] >= 1.5149424) {
                        if (input[5] >= 36.705) {
                            var6 = -0.013170603;
                        } else {
                            var6 = -0.024391461;
                        }
                    } else {
                        if (input[7] >= 1.5140414) {
                            var6 = -0.0019855814;
                        } else {
                            var6 = -0.017026797;
                        }
                    }
                }
            }
        }
    }
    float var7;
    if (input[2] >= 36.5) {
        if (input[2] >= 47.5) {
            if (input[2] >= 75.5) {
                var7 = -0.024041003;
            } else {
                var7 = -0.0238608;
            }
        } else {
            if (input[5] >= -0.695) {
                if (input[0] >= -12.5) {
                    var7 = -0.023641549;
                } else {
                    if (input[3] >= -94.015) {
                        var7 = -0.016822567;
                    } else {
                        if (input[0] >= -20.0) {
                            var7 = -0.022732463;
                        } else {
                            var7 = -0.020756556;
                        }
                    }
                }
            } else {
                var7 = -0.023943484;
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[5] >= -1.945) {
                if (input[0] >= -7.5) {
                    var7 = -0.023403356;
                } else {
                    if (input[0] >= -12.5) {
                        if (input[5] >= 16.130001) {
                            var7 = -0.011521392;
                        } else {
                            var7 = -0.018238602;
                        }
                    } else {
                        if (input[2] >= 24.5) {
                            var7 = -0.012720423;
                        } else {
                            var7 = 0.0012227923;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    var7 = -0.023999253;
                } else {
                    var7 = -0.024477905;
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var7 = -0.023537371;
                } else {
                    if (input[2] >= 22.5) {
                        if (input[3] >= -95.354996) {
                            var7 = -0.01932661;
                        } else {
                            var7 = -0.022291396;
                        }
                    } else {
                        if (input[2] >= 5.5) {
                            var7 = -0.019220054;
                        } else {
                            var7 = -0.0046375305;
                        }
                    }
                }
            } else {
                if (input[2] >= 25.5) {
                    if (input[0] >= -20.0) {
                        if (input[3] >= -97.604996) {
                            var7 = -0.013306391;
                        } else {
                            var7 = -0.020311965;
                        }
                    } else {
                        if (input[2] >= 29.5) {
                            var7 = -0.01666168;
                        } else {
                            var7 = -0.01160708;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[2] >= 16.5) {
                            var7 = -0.015017504;
                        } else {
                            var7 = -0.01036204;
                        }
                    } else {
                        if (input[2] >= 17.5) {
                            var7 = -0.0075685917;
                        } else {
                            var7 = 0.0030282326;
                        }
                    }
                }
            }
        }
    }
    float var8;
    if (input[2] >= 37.5) {
        if (input[2] >= 45.5) {
            if (input[2] >= 72.5) {
                if (input[4] >= -95.0) {
                    var8 = -0.02154402;
                } else {
                    var8 = -0.021787863;
                }
            } else {
                if (input[1] >= 21.835) {
                    var8 = -0.021504093;
                } else {
                    var8 = -0.021140998;
                }
            }
        } else {
            if (input[1] >= 26.545) {
                if (input[4] >= -95.0) {
                    var8 = -0.021551657;
                } else {
                    if (input[3] >= -99.994995) {
                        var8 = -0.021508543;
                    } else {
                        if (input[1] >= 44.09) {
                            var8 = -0.021051973;
                        } else {
                            var8 = -0.019621892;
                        }
                    }
                }
            } else {
                if (input[5] >= -1.5799999) {
                    if (input[3] >= -91.64) {
                        if (input[1] >= 12.605) {
                            var8 = -0.019843314;
                        } else {
                            var8 = -0.017612152;
                        }
                    } else {
                        if (input[1] >= 9.74) {
                            var8 = -0.016014045;
                        } else {
                            var8 = 0.000055085122;
                        }
                    }
                } else {
                    var8 = -0.021733055;
                }
            }
        }
    } else {
        if (input[5] >= -0.235) {
            if (input[3] >= -99.975006) {
                if (input[1] >= 16.255001) {
                    if (input[1] >= 40.989998) {
                        if (input[2] >= 26.5) {
                            var8 = -0.021670198;
                        } else {
                            var8 = -0.020524196;
                        }
                    } else {
                        if (input[3] >= -92.69) {
                            var8 = -0.020325713;
                        } else {
                            var8 = -0.017936604;
                        }
                    }
                } else {
                    if (input[3] >= -81.46) {
                        if (input[1] >= 9.17) {
                            var8 = -0.019687794;
                        } else {
                            var8 = -0.016545607;
                        }
                    } else {
                        if (input[1] >= 11.055) {
                            var8 = -0.014799172;
                        } else {
                            var8 = -0.010213654;
                        }
                    }
                }
            } else {
                if (input[2] >= 26.5) {
                    if (input[1] >= 38.725) {
                        if (input[2] >= 30.5) {
                            var8 = -0.020572815;
                        } else {
                            var8 = -0.01904323;
                        }
                    } else {
                        if (input[1] >= 28.48) {
                            var8 = -0.014502688;
                        } else {
                            var8 = -0.012165774;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        if (input[1] >= 54.59) {
                            var8 = -0.016625052;
                        } else {
                            var8 = -0.012085218;
                        }
                    } else {
                        if (input[2] >= 7.5) {
                            var8 = -0.0049442854;
                        } else {
                            var8 = 0.0063918526;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.9650002) {
                if (input[1] >= 17.955) {
                    var8 = -0.020930225;
                } else {
                    if (input[2] >= 22.0) {
                        var8 = -0.017789092;
                    } else {
                        var8 = -0.0041645104;
                    }
                }
            } else {
                var8 = -0.021707876;
            }
        }
    }
    float var9;
    if (input[2] >= 34.5) {
        if (input[2] >= 43.5) {
            if (input[2] >= 78.5) {
                if (input[4] >= -95.0) {
                    var9 = -0.019398673;
                } else {
                    var9 = -0.019644227;
                }
            } else {
                if (input[1] >= 15.045) {
                    var9 = -0.019348266;
                } else {
                    if (input[2] >= 58.5) {
                        var9 = -0.0189864;
                    } else {
                        var9 = -0.017474016;
                    }
                }
            }
        } else {
            if (input[1] >= 28.47) {
                if (input[4] >= -95.0) {
                    var9 = -0.019401921;
                } else {
                    if (input[3] >= -99.994995) {
                        var9 = -0.019399917;
                    } else {
                        if (input[1] >= 39.745) {
                            var9 = -0.01855608;
                        } else {
                            var9 = -0.016745804;
                        }
                    }
                }
            } else {
                if (input[5] >= -2.0749998) {
                    if (input[3] >= -85.979996) {
                        if (input[1] >= 12.684999) {
                            var9 = -0.018384011;
                        } else {
                            var9 = -0.016344994;
                        }
                    } else {
                        if (input[1] >= 15.969999) {
                            var9 = -0.015508157;
                        } else {
                            var9 = -0.012855803;
                        }
                    }
                } else {
                    var9 = -0.019578213;
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 11.809999) {
                if (input[5] >= -2.565) {
                    if (input[1] >= 25.33) {
                        var9 = -0.018970473;
                    } else {
                        if (input[3] >= -85.42) {
                            var9 = -0.01830032;
                        } else {
                            var9 = -0.015906427;
                        }
                    }
                } else {
                    var9 = -0.01954808;
                }
            } else {
                if (input[5] >= -2.9650002) {
                    if (input[3] >= -83.895004) {
                        if (input[3] >= -74.58) {
                            var9 = -0.01673392;
                        } else {
                            var9 = -0.013421533;
                        }
                    } else {
                        if (input[3] >= -88.354996) {
                            var9 = -0.004838289;
                        } else {
                            var9 = -0.013103398;
                        }
                    }
                } else {
                    var9 = -0.01998326;
                }
            }
        } else {
            if (input[3] >= -99.975006) {
                if (input[1] >= 17.99) {
                    if (input[1] >= 41.105003) {
                        if (input[2] >= 26.5) {
                            var9 = -0.019516518;
                        } else {
                            var9 = -0.018308355;
                        }
                    } else {
                        if (input[3] >= -92.69) {
                            var9 = -0.018421965;
                        } else {
                            var9 = -0.016094904;
                        }
                    }
                } else {
                    if (input[3] >= -88.54) {
                        if (input[1] >= 10.755) {
                            var9 = -0.016787749;
                        } else {
                            var9 = -0.0126765445;
                        }
                    } else {
                        if (input[2] >= 27.5) {
                            var9 = -0.00869891;
                        } else {
                            var9 = -0.001591659;
                        }
                    }
                }
            } else {
                if (input[2] >= 22.5) {
                    if (input[1] >= 41.6) {
                        if (input[2] >= 25.5) {
                            var9 = -0.01797593;
                        } else {
                            var9 = -0.015214431;
                        }
                    } else {
                        if (input[1] >= 27.935001) {
                            var9 = -0.012655496;
                        } else {
                            var9 = -0.009738418;
                        }
                    }
                } else {
                    if (input[2] >= 7.5) {
                        if (input[2] >= 16.5) {
                            var9 = -0.011585586;
                        } else {
                            var9 = -0.0088288;
                        }
                    } else {
                        if (input[1] >= 57.805) {
                            var9 = -0.006757883;
                        } else {
                            var9 = 0.010007534;
                        }
                    }
                }
            }
        }
    }
    return NAN + (var0 + var1 + var2 + var3 + var4 + var5 + var6 + var7 + var8 + var9);
}

volatile float result;
int main(void) {
    float input[8] = {-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f};
    result = score(input);
    return 0;
}
