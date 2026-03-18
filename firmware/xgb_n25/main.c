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
    float var10;
    if (input[2] >= 32.5) {
        if (input[2] >= 40.5) {
            if (input[2] >= 64.5) {
                var10 = -0.017497314;
            } else {
                if (input[0] >= -12.5) {
                    var10 = -0.017462058;
                } else {
                    if (input[5] >= -2.4050002) {
                        if (input[1] >= 40.175) {
                            var10 = -0.017173812;
                        } else {
                            var10 = -0.015894165;
                        }
                    } else {
                        var10 = -0.017456174;
                    }
                }
            }
        } else {
            if (input[5] >= -1.665) {
                if (input[0] >= -12.5) {
                    if (input[1] >= 33.675) {
                        var10 = -0.017644813;
                    } else {
                        if (input[0] >= -7.5) {
                            var10 = -0.017253203;
                        } else {
                            var10 = -0.013287318;
                        }
                    }
                } else {
                    if (input[1] >= 30.880001) {
                        if (input[0] >= -20.0) {
                            var10 = -0.017079746;
                        } else {
                            var10 = -0.01417804;
                        }
                    } else {
                        if (input[1] >= 10.684999) {
                            var10 = -0.011158022;
                        } else {
                            var10 = -0.009117576;
                        }
                    }
                }
            } else {
                var10 = -0.017495137;
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 11.745) {
                if (input[5] >= -2.815) {
                    if (input[0] >= -7.5) {
                        var10 = -0.017172433;
                    } else {
                        if (input[1] >= 16.55) {
                            var10 = -0.013982934;
                        } else {
                            var10 = -0.006299796;
                        }
                    }
                } else {
                    if (input[0] >= -12.5) {
                        var10 = -0.01741955;
                    } else {
                        var10 = -0.01782451;
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    var10 = -0.017148657;
                } else {
                    if (input[5] >= -1.255) {
                        if (input[2] >= 24.5) {
                            var10 = -0.008829719;
                        } else {
                            var10 = 0.0038684744;
                        }
                    } else {
                        if (input[2] >= 22.0) {
                            var10 = -0.017269991;
                        } else {
                            var10 = -0.0033011145;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[3] >= -99.785) {
                        var10 = -0.017281868;
                    } else {
                        var10 = -0.01836745;
                    }
                } else {
                    if (input[1] >= 48.620003) {
                        if (input[2] >= 17.5) {
                            var10 = -0.018105237;
                        } else {
                            var10 = -0.015630139;
                        }
                    } else {
                        if (input[3] >= -99.92) {
                            var10 = -0.0133712245;
                        } else {
                            var10 = -0.015070123;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[1] >= 53.225) {
                        if (input[2] >= 14.5) {
                            var10 = -0.017116975;
                        } else {
                            var10 = -0.005142867;
                        }
                    } else {
                        if (input[1] >= 23.130001) {
                            var10 = -0.011019129;
                        } else {
                            var10 = -0.005660914;
                        }
                    }
                } else {
                    if (input[2] >= 18.5) {
                        if (input[2] >= 28.5) {
                            var10 = -0.010485771;
                        } else {
                            var10 = -0.005235569;
                        }
                    } else {
                        if (input[2] >= 12.5) {
                            var10 = 0.001968222;
                        } else {
                            var10 = 0.010627949;
                        }
                    }
                }
            }
        }
    }
    float var11;
    if (input[2] >= 32.5) {
        if (input[2] >= 40.5) {
            if (input[2] >= 55.5) {
                var11 = -0.01572928;
            } else {
                if (input[1] >= 8.860001) {
                    if (input[0] >= -20.0) {
                        if (input[1] >= 21.8) {
                            var11 = -0.015693434;
                        } else {
                            var11 = -0.014652568;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var11 = -0.01573859;
                        } else {
                            var11 = -0.0141245965;
                        }
                    }
                } else {
                    if (input[3] >= -75.99) {
                        if (input[0] >= -20.0) {
                            var11 = -0.014444937;
                        } else {
                            var11 = -0.0032752715;
                        }
                    } else {
                        if (input[3] >= -77.815) {
                            var11 = -0.00039761962;
                        } else {
                            var11 = -0.008452504;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -1.6) {
                if (input[0] >= -12.5) {
                    if (input[1] >= 27.5) {
                        var11 = -0.015815815;
                    } else {
                        if (input[0] >= -7.5) {
                            var11 = -0.015485214;
                        } else {
                            var11 = -0.011786208;
                        }
                    }
                } else {
                    if (input[1] >= 39.08) {
                        if (input[0] >= -20.0) {
                            var11 = -0.015658438;
                        } else {
                            var11 = -0.013010976;
                        }
                    } else {
                        if (input[1] >= 27.045) {
                            var11 = -0.011625892;
                        } else {
                            var11 = -0.009474813;
                        }
                    }
                }
            } else {
                var11 = -0.015745763;
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[5] >= -2.205) {
                if (input[0] >= -7.5) {
                    var11 = -0.015452521;
                } else {
                    if (input[0] >= -12.5) {
                        if (input[1] >= 27.630001) {
                            var11 = -0.0139324535;
                        } else {
                            var11 = -0.010310626;
                        }
                    } else {
                        if (input[2] >= 23.0) {
                            var11 = -0.0060328664;
                        } else {
                            var11 = 0.004787305;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    var11 = -0.015674148;
                } else {
                    if (input[3] >= -82.815) {
                        var11 = -0.0067364373;
                    } else {
                        var11 = -0.016045017;
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        if (input[3] >= -99.97) {
                            var11 = -0.015583604;
                        } else {
                            var11 = -0.016536612;
                        }
                    } else {
                        if (input[1] >= 50.29) {
                            var11 = -0.015851874;
                        } else {
                            var11 = -0.012951768;
                        }
                    }
                } else {
                    if (input[1] >= 54.135002) {
                        if (input[2] >= 15.5) {
                            var11 = -0.01598817;
                        } else {
                            var11 = -0.0066575953;
                        }
                    } else {
                        if (input[2] >= 27.5) {
                            var11 = -0.011858776;
                        } else {
                            var11 = -0.008427844;
                        }
                    }
                }
            } else {
                if (input[2] >= 22.5) {
                    if (input[1] >= 43.82) {
                        if (input[1] >= 56.88) {
                            var11 = -0.013760787;
                        } else {
                            var11 = -0.009857675;
                        }
                    } else {
                        if (input[1] >= 43.245003) {
                            var11 = 0.0012585054;
                        } else {
                            var11 = -0.0059856973;
                        }
                    }
                } else {
                    if (input[2] >= 14.5) {
                        if (input[2] >= 18.5) {
                            var11 = -0.0024866082;
                        } else {
                            var11 = 0.001247782;
                        }
                    } else {
                        if (input[2] >= 9.5) {
                            var11 = 0.0057751504;
                        } else {
                            var11 = 0.012043029;
                        }
                    }
                }
            }
        }
    }
    float var12;
    if (input[2] >= 31.5) {
        if (input[2] >= 39.5) {
            if (input[2] >= 53.5) {
                var12 = -0.014150915;
            } else {
                if (input[5] >= -0.005) {
                    if (input[0] >= -20.0) {
                        if (input[0] >= -12.5) {
                            var12 = -0.014146409;
                        } else {
                            var12 = -0.013455673;
                        }
                    } else {
                        if (input[3] >= -89.815) {
                            var12 = -0.0069389143;
                        } else {
                            var12 = -0.012459768;
                        }
                    }
                } else {
                    var12 = -0.0141375065;
                }
            }
        } else {
            if (input[5] >= -1.665) {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        var12 = -0.014135954;
                    } else {
                        if (input[3] >= -89.185) {
                            var12 = -0.009893023;
                        } else {
                            var12 = -0.01387954;
                        }
                    }
                } else {
                    if (input[3] >= -98.46) {
                        if (input[0] >= -20.0) {
                            var12 = -0.008995811;
                        } else {
                            var12 = -0.0067844973;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var12 = -0.013326793;
                        } else {
                            var12 = -0.010744289;
                        }
                    }
                }
            } else {
                var12 = -0.014179835;
            }
        }
    } else {
        if (input[5] >= -0.195) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[3] >= -99.785) {
                        if (input[0] >= -2.5) {
                            var12 = -0.0142072365;
                        } else {
                            var12 = -0.013541545;
                        }
                    } else {
                        var12 = -0.014865726;
                    }
                } else {
                    if (input[3] >= -99.715) {
                        if (input[3] >= -86.95) {
                            var12 = -0.008214826;
                        } else {
                            var12 = -0.0113406265;
                        }
                    } else {
                        if (input[2] >= 22.5) {
                            var12 = -0.01393327;
                        } else {
                            var12 = -0.012488601;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[3] >= -99.634995) {
                        if (input[3] >= -89.315) {
                            var12 = -0.0030908433;
                        } else {
                            var12 = -0.006855901;
                        }
                    } else {
                        if (input[2] >= 19.5) {
                            var12 = -0.0106469765;
                        } else {
                            var12 = -0.006864236;
                        }
                    }
                } else {
                    if (input[2] >= 22.5) {
                        if (input[2] >= 28.5) {
                            var12 = -0.008136327;
                        } else {
                            var12 = -0.005166925;
                        }
                    } else {
                        if (input[2] >= 14.5) {
                            var12 = -0.00089577615;
                        } else {
                            var12 = 0.0068101096;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.9850001) {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        var12 = -0.013971204;
                    } else {
                        if (input[3] >= -80.625) {
                            var12 = -0.002362533;
                        } else {
                            var12 = -0.011993586;
                        }
                    }
                } else {
                    if (input[5] >= -1.39) {
                        if (input[2] >= 25.0) {
                            var12 = -0.005151232;
                        } else {
                            var12 = 0.006150739;
                        }
                    } else {
                        if (input[3] >= -81.985) {
                            var12 = -0.0028126703;
                        } else {
                            var12 = -0.009946023;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    var12 = -0.014172548;
                } else {
                    var12 = -0.014575012;
                }
            }
        }
    }
    float var13;
    if (input[2] >= 31.5) {
        if (input[2] >= 40.5) {
            if (input[2] >= 79.5) {
                if (input[4] >= -95.0) {
                    var13 = -0.012723783;
                } else {
                    if (input[0] >= -12.5) {
                        var13 = -0.01275675;
                    } else {
                        var13 = -0.013229126;
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    var13 = -0.012730983;
                } else {
                    if (input[3] >= -90.715) {
                        if (input[2] >= 47.0) {
                            var13 = -0.0116807325;
                        } else {
                            var13 = -0.007665942;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var13 = -0.012713489;
                        } else {
                            var13 = -0.01239689;
                        }
                    }
                }
            }
        } else {
            if (input[4] >= -95.0) {
                if (input[3] >= -89.625) {
                    if (input[0] >= -7.5) {
                        var13 = -0.012619642;
                    } else {
                        if (input[3] >= -79.494995) {
                            var13 = -0.0071827136;
                        } else {
                            var13 = -0.01061564;
                        }
                    }
                } else {
                    var13 = -0.012741496;
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[0] >= -7.5) {
                        var13 = -0.012751976;
                    } else {
                        if (input[3] >= -93.345) {
                            var13 = -0.009227112;
                        } else {
                            var13 = -0.012211527;
                        }
                    }
                } else {
                    if (input[3] >= -99.024994) {
                        if (input[3] >= -91.635) {
                            var13 = -0.009795814;
                        } else {
                            var13 = -0.0038640287;
                        }
                    } else {
                        if (input[7] >= 1.5218229) {
                            var13 = -0.009752261;
                        } else {
                            var13 = -0.013093888;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[3] >= -91.935) {
                if (input[0] >= -7.5) {
                    var13 = -0.012566172;
                } else {
                    if (input[4] >= -85.0) {
                        if (input[3] >= -81.985) {
                            var13 = -0.0072751245;
                        } else {
                            var13 = -0.013015288;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var13 = -0.009204375;
                        } else {
                            var13 = -0.0038192407;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    var13 = -0.012749875;
                } else {
                    var13 = -0.013113703;
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[3] >= -99.880005) {
                        if (input[0] >= -2.5) {
                            var13 = -0.012871847;
                        } else {
                            var13 = -0.012273206;
                        }
                    } else {
                        var13 = -0.013400263;
                    }
                } else {
                    if (input[3] >= -99.380005) {
                        if (input[2] >= 18.5) {
                            var13 = -0.010245471;
                        } else {
                            var13 = -0.00822704;
                        }
                    } else {
                        if (input[2] >= 22.5) {
                            var13 = -0.012523894;
                        } else {
                            var13 = -0.0110171465;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[3] >= -99.630005) {
                        if (input[3] >= -82.18) {
                            var13 = -0.0008660898;
                        } else {
                            var13 = -0.0060796253;
                        }
                    } else {
                        if (input[2] >= 20.5) {
                            var13 = -0.009862158;
                        } else {
                            var13 = -0.0068663443;
                        }
                    }
                } else {
                    if (input[2] >= 17.5) {
                        if (input[2] >= 25.5) {
                            var13 = -0.006751794;
                        } else {
                            var13 = -0.0029420813;
                        }
                    } else {
                        if (input[2] >= 10.5) {
                            var13 = 0.0019070253;
                        } else {
                            var13 = 0.010751882;
                        }
                    }
                }
            }
        }
    }
    float var14;
    if (input[2] >= 31.5) {
        if (input[2] >= 42.5) {
            if (input[2] >= 71.5) {
                if (input[5] >= -2.0949998) {
                    if (input[0] >= -7.5) {
                        var14 = -0.011436266;
                    } else {
                        if (input[1] >= 15.965) {
                            var14 = -0.011830612;
                        } else {
                            var14 = -0.0115259895;
                        }
                    }
                } else {
                    var14 = -0.011411441;
                }
            } else {
                if (input[1] >= 24.865002) {
                    if (input[0] >= -20.0) {
                        var14 = -0.011470973;
                    } else {
                        if (input[5] >= -2.105) {
                            var14 = -0.010933899;
                        } else {
                            var14 = -0.011447365;
                        }
                    }
                } else {
                    if (input[0] >= -7.5) {
                        var14 = -0.011498581;
                    } else {
                        if (input[5] >= -0.005) {
                            var14 = -0.010321229;
                        } else {
                            var14 = -0.011435377;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 31.855) {
                if (input[0] >= -20.0) {
                    var14 = -0.011480923;
                } else {
                    if (input[5] >= -5.0) {
                        if (input[1] >= 49.145) {
                            var14 = -0.0109486515;
                        } else {
                            var14 = -0.008615963;
                        }
                    } else {
                        var14 = -0.011628905;
                    }
                }
            } else {
                if (input[5] >= -0.255) {
                    if (input[0] >= -7.5) {
                        if (input[0] >= -2.5) {
                            var14 = -0.011690374;
                        } else {
                            var14 = -0.010967622;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var14 = -0.008486289;
                        } else {
                            var14 = -0.00660368;
                        }
                    }
                } else {
                    if (input[5] >= -3.1550002) {
                        if (input[0] >= -7.5) {
                            var14 = -0.011301979;
                        } else {
                            var14 = -0.0097927665;
                        }
                    } else {
                        var14 = -0.011665808;
                    }
                }
            }
        }
    } else {
        if (input[5] >= -0.195) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[5] >= 0.015) {
                        if (input[0] >= -2.5) {
                            var14 = -0.01151547;
                        } else {
                            var14 = -0.011006527;
                        }
                    } else {
                        var14 = -0.012111459;
                    }
                } else {
                    if (input[1] >= 50.29) {
                        if (input[2] >= 17.5) {
                            var14 = -0.012570478;
                        } else {
                            var14 = -0.01043359;
                        }
                    } else {
                        if (input[1] >= 28.0) {
                            var14 = -0.009726386;
                        } else {
                            var14 = -0.008196934;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[1] >= 51.519997) {
                        if (input[2] >= 15.5) {
                            var14 = -0.01203512;
                        } else {
                            var14 = -0.0040683914;
                        }
                    } else {
                        if (input[1] >= 23.71) {
                            var14 = -0.0067927213;
                        } else {
                            var14 = -0.0025593638;
                        }
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[1] >= 50.760002) {
                            var14 = -0.008637217;
                        } else {
                            var14 = -0.0039503607;
                        }
                    } else {
                        if (input[2] >= 14.5) {
                            var14 = -0.00024933156;
                        } else {
                            var14 = 0.0042907535;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 5.12) {
                if (input[0] >= -20.0) {
                    if (input[1] >= 5.785) {
                        var14 = -0.01145425;
                    } else {
                        var14 = -0.0019428246;
                    }
                } else {
                    if (input[5] >= -3.21) {
                        var14 = -0.0051728054;
                    } else {
                        if (input[2] >= 20.5) {
                            var14 = -0.011640407;
                        } else {
                            var14 = -0.012147931;
                        }
                    }
                }
            } else {
                if (input[5] >= -1.3000001) {
                    var14 = 0.006034163;
                } else {
                    var14 = -0.008040288;
                }
            }
        }
    }
    float var15;
    if (input[4] >= -95.0) {
        if (input[5] >= -3.0149999) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    var15 = -0.010296709;
                } else {
                    if (input[7] >= 1.4807119) {
                        if (input[3] >= -75.365005) {
                            var15 = -0.009319848;
                        } else {
                            var15 = -0.009995534;
                        }
                    } else {
                        if (input[3] >= -77.59) {
                            var15 = 0.0019451507;
                        } else {
                            var15 = -0.0060430006;
                        }
                    }
                }
            } else {
                if (input[5] >= -0.45999998) {
                    if (input[3] >= -90.445) {
                        var15 = -0.009128015;
                    } else {
                        if (input[6] >= 7.5) {
                            var15 = -0.008362238;
                        } else {
                            var15 = 0.006101485;
                        }
                    }
                } else {
                    var15 = -0.009741731;
                }
            }
        } else {
            var15 = -0.010315711;
        }
    } else {
        if (input[0] >= -20.0) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[3] >= -99.985) {
                        var15 = -0.010297753;
                    } else {
                        var15 = -0.010545014;
                    }
                } else {
                    if (input[3] >= -86.505005) {
                        if (input[7] >= 1.484583) {
                            var15 = -0.009539864;
                        } else {
                            var15 = -0.00089536014;
                        }
                    } else {
                        if (input[7] >= 1.4771925) {
                            var15 = -0.01016229;
                        } else {
                            var15 = -0.0019456865;
                        }
                    }
                }
            } else {
                if (input[7] >= 4.887712) {
                    if (input[7] >= 4.895916) {
                        if (input[3] >= -83.354996) {
                            var15 = -0.008027537;
                        } else {
                            var15 = -0.009366555;
                        }
                    } else {
                        if (input[7] >= 4.8942738) {
                            var15 = -0.0033639488;
                        } else {
                            var15 = 0.0028393045;
                        }
                    }
                } else {
                    if (input[7] >= 1.504657) {
                        if (input[3] >= -89.479996) {
                            var15 = -0.009091464;
                        } else {
                            var15 = -0.00990718;
                        }
                    } else {
                        if (input[7] >= 1.504546) {
                            var15 = 0.004378654;
                        } else {
                            var15 = -0.007724495;
                        }
                    }
                }
            }
        } else {
            if (input[3] >= -90.945) {
                if (input[7] >= 1.507398) {
                    var15 = -0.010019065;
                } else {
                    var15 = -0.0025498488;
                }
            } else {
                if (input[7] >= 1.9744315) {
                    if (input[7] >= 1.9820161) {
                        if (input[7] >= 4.519557) {
                            var15 = -0.00852115;
                        } else {
                            var15 = -0.0069437786;
                        }
                    } else {
                        if (input[7] >= 1.9814296) {
                            var15 = 0.0033510595;
                        } else {
                            var15 = 0.009561259;
                        }
                    }
                } else {
                    if (input[7] >= 1.4781106) {
                        if (input[7] >= 1.886271) {
                            var15 = -0.009474125;
                        } else {
                            var15 = -0.008805961;
                        }
                    } else {
                        if (input[7] >= 1.476975) {
                            var15 = 0.007278841;
                        } else {
                            var15 = -0.0068264934;
                        }
                    }
                }
            }
        }
    }
    float var16;
    if (input[2] >= 37.5) {
        if (input[2] >= 54.5) {
            if (input[4] >= -95.0) {
                var16 = -0.009263965;
            } else {
                if (input[5] >= 0.445) {
                    if (input[2] >= 83.5) {
                        if (input[0] >= -7.5) {
                            var16 = -0.009229892;
                        } else {
                            var16 = -0.0095868595;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var16 = -0.009284037;
                        } else {
                            var16 = -0.008711933;
                        }
                    }
                } else {
                    if (input[2] >= 70.5) {
                        if (input[0] >= -12.5) {
                            var16 = -0.009402355;
                        } else {
                            var16 = -0.009855795;
                        }
                    } else {
                        if (input[1] >= 35.675) {
                            var16 = -0.009726352;
                        } else {
                            var16 = -0.008785993;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 21.765) {
                if (input[0] >= -20.0) {
                    if (input[1] >= 34.655) {
                        var16 = -0.009292453;
                    } else {
                        if (input[0] >= -12.5) {
                            var16 = -0.009215286;
                        } else {
                            var16 = -0.00870943;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        var16 = -0.009317394;
                    } else {
                        if (input[1] >= 43.605) {
                            var16 = -0.0088331625;
                        } else {
                            var16 = -0.007281814;
                        }
                    }
                }
            } else {
                if (input[5] >= -1.59) {
                    if (input[0] >= -7.5) {
                        var16 = -0.009200914;
                    } else {
                        if (input[1] >= 21.14) {
                            var16 = -0.0033823748;
                        } else {
                            var16 = -0.006320556;
                        }
                    }
                } else {
                    var16 = -0.009481539;
                }
            }
        }
    } else {
        if (input[5] >= -0.215) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[5] >= 0.04) {
                        if (input[0] >= -2.5) {
                            var16 = -0.009375394;
                        } else {
                            var16 = -0.008903265;
                        }
                    } else {
                        var16 = -0.009721906;
                    }
                } else {
                    if (input[1] >= 36.525) {
                        if (input[2] >= 20.5) {
                            var16 = -0.009431961;
                        } else {
                            var16 = -0.0072097457;
                        }
                    } else {
                        if (input[1] >= 14.17) {
                            var16 = -0.0071726576;
                        } else {
                            var16 = -0.004958352;
                        }
                    }
                }
            } else {
                if (input[2] >= 24.5) {
                    if (input[1] >= 36.48) {
                        if (input[0] >= -20.0) {
                            var16 = -0.009136845;
                        } else {
                            var16 = -0.006820803;
                        }
                    } else {
                        if (input[2] >= 30.5) {
                            var16 = -0.0048586726;
                        } else {
                            var16 = -0.0028078875;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[1] >= 54.48) {
                            var16 = -0.008634175;
                        } else {
                            var16 = -0.00378594;
                        }
                    } else {
                        if (input[2] >= 17.5) {
                            var16 = -0.0012824918;
                        } else {
                            var16 = 0.0035168845;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -3.185) {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        var16 = -0.00917174;
                    } else {
                        if (input[5] >= -1.685) {
                            var16 = -0.007295628;
                        } else {
                            var16 = -0.008839576;
                        }
                    }
                } else {
                    if (input[5] >= -1.48) {
                        if (input[1] >= 15.995) {
                            var16 = -0.0065209754;
                        } else {
                            var16 = -0.0014907763;
                        }
                    } else {
                        if (input[2] >= 22.0) {
                            var16 = -0.0073680575;
                        } else {
                            var16 = -0.0001392141;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    var16 = -0.009243872;
                } else {
                    if (input[2] >= 20.5) {
                        var16 = -0.009421962;
                    } else {
                        var16 = -0.009766675;
                    }
                }
            }
        }
    }
    float var17;
    if (input[2] >= 30.5) {
        if (input[2] >= 47.5) {
            if (input[2] >= 78.5) {
                if (input[5] >= -2.275) {
                    if (input[3] >= -99.955) {
                        var17 = -0.008452008;
                    } else {
                        var17 = -0.008832853;
                    }
                } else {
                    var17 = -0.008307168;
                }
            } else {
                if (input[1] >= 32.535) {
                    if (input[5] >= -0.015) {
                        if (input[2] >= 53.5) {
                            var17 = -0.008566148;
                        } else {
                            var17 = -0.008293237;
                        }
                    } else {
                        var17 = -0.008332748;
                    }
                } else {
                    if (input[5] >= -0.005) {
                        if (input[5] >= 0.015) {
                            var17 = -0.008174953;
                        } else {
                            var17 = -0.0077585126;
                        }
                    } else {
                        var17 = -0.008337425;
                    }
                }
            }
        } else {
            if (input[1] >= 31.845001) {
                if (input[1] >= 39.085) {
                    if (input[1] >= 49.145) {
                        if (input[5] >= -1.855) {
                            var17 = -0.008574554;
                        } else {
                            var17 = -0.008343965;
                        }
                    } else {
                        if (input[5] >= -0.015) {
                            var17 = -0.008139897;
                        } else {
                            var17 = -0.008347623;
                        }
                    }
                } else {
                    if (input[5] >= -0.005) {
                        if (input[3] >= -99.615005) {
                            var17 = -0.008243723;
                        } else {
                            var17 = -0.006724193;
                        }
                    } else {
                        var17 = -0.008349347;
                    }
                }
            } else {
                if (input[5] >= -1.585) {
                    if (input[3] >= -91.545) {
                        if (input[1] >= 16.884998) {
                            var17 = -0.0077903033;
                        } else {
                            var17 = -0.0066677253;
                        }
                    } else {
                        if (input[1] >= 10.684999) {
                            var17 = -0.0056644506;
                        } else {
                            var17 = 0.000031409872;
                        }
                    }
                } else {
                    var17 = -0.008476605;
                }
            }
        }
    } else {
        if (input[5] >= -0.005) {
            if (input[3] >= -99.975006) {
                if (input[1] >= 11.115) {
                    if (input[3] >= -95.935) {
                        if (input[1] >= 33.745003) {
                            var17 = -0.008130019;
                        } else {
                            var17 = -0.0073490217;
                        }
                    } else {
                        if (input[1] >= 42.42) {
                            var17 = -0.0077163638;
                        } else {
                            var17 = -0.005926242;
                        }
                    }
                } else {
                    if (input[3] >= -78.145004) {
                        if (input[1] >= 4.54) {
                            var17 = -0.007093794;
                        } else {
                            var17 = -0.0026876542;
                        }
                    } else {
                        if (input[7] >= 9.787459) {
                            var17 = 0.003404624;
                        } else {
                            var17 = -0.00085781823;
                        }
                    }
                }
            } else {
                if (input[2] >= 18.5) {
                    if (input[1] >= 47.5) {
                        if (input[1] >= 58.129997) {
                            var17 = -0.008967835;
                        } else {
                            var17 = -0.007353314;
                        }
                    } else {
                        if (input[1] >= 19.945) {
                            var17 = -0.0045262636;
                        } else {
                            var17 = 0.0009433785;
                        }
                    }
                } else {
                    if (input[2] >= 7.5) {
                        if (input[7] >= 4.6038156) {
                            var17 = -0.0025631157;
                        } else {
                            var17 = -0.0045472775;
                        }
                    } else {
                        if (input[6] >= 3.5) {
                            var17 = 0.0077601047;
                        } else {
                            var17 = -0.0013277493;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 5.12) {
                if (input[5] >= -3.0749998) {
                    if (input[1] >= 12.389999) {
                        if (input[1] >= 26.735) {
                            var17 = -0.008198435;
                        } else {
                            var17 = -0.00715222;
                        }
                    } else {
                        if (input[2] >= 28.5) {
                            var17 = -0.0068759928;
                        } else {
                            var17 = -0.0022163573;
                        }
                    }
                } else {
                    var17 = -0.008438348;
                }
            } else {
                if (input[3] >= -91.3) {
                    var17 = 0.0055019185;
                } else {
                    var17 = -0.0043153237;
                }
            }
        }
    }
    float var18;
    if (input[2] >= 30.5) {
        if (input[2] >= 45.5) {
            if (input[2] >= 81.5) {
                if (input[5] >= -2.2649999) {
                    if (input[5] >= 0.71500003) {
                        var18 = -0.007600348;
                    } else {
                        if (input[4] >= -95.0) {
                            var18 = -0.0076578553;
                        } else {
                            var18 = -0.007977554;
                        }
                    }
                } else {
                    var18 = -0.0074760593;
                }
            } else {
                if (input[1] >= 16.535) {
                    if (input[1] >= 36.075) {
                        if (input[4] >= -95.0) {
                            var18 = -0.0074994215;
                        } else {
                            var18 = -0.0076772766;
                        }
                    } else {
                        if (input[2] >= 60.5) {
                            var18 = -0.0075104;
                        } else {
                            var18 = -0.007379727;
                        }
                    }
                } else {
                    if (input[4] >= -85.0) {
                        var18 = -0.00750113;
                    } else {
                        if (input[5] >= 12.385) {
                            var18 = -0.0073453956;
                        } else {
                            var18 = -0.006908662;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 25.105) {
                if (input[1] >= 39.035) {
                    if (input[1] >= 49.095) {
                        if (input[4] >= -95.0) {
                            var18 = -0.0075158733;
                        } else {
                            var18 = -0.0077526295;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var18 = -0.007521961;
                        } else {
                            var18 = -0.00730531;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        var18 = -0.007495479;
                    } else {
                        if (input[5] >= 0.005) {
                            var18 = -0.007244491;
                        } else {
                            var18 = -0.0055967714;
                        }
                    }
                }
            } else {
                if (input[5] >= -1.6) {
                    if (input[5] >= 5.91) {
                        if (input[1] >= 0.985) {
                            var18 = -0.006432613;
                        } else {
                            var18 = -0.000754888;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var18 = -0.0056393067;
                        } else {
                            var18 = -0.004032852;
                        }
                    }
                } else {
                    if (input[5] >= -3.105) {
                        if (input[7] >= 9.949337) {
                            var18 = -0.0010811724;
                        } else {
                            var18 = -0.0070776343;
                        }
                    } else {
                        var18 = -0.00775109;
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 10.96) {
                if (input[5] >= -1.675) {
                    if (input[1] >= 25.675) {
                        var18 = -0.00722989;
                    } else {
                        if (input[5] >= -1.615) {
                            var18 = -0.006392476;
                        } else {
                            var18 = 0.002740763;
                        }
                    }
                } else {
                    var18 = -0.0075874166;
                }
            } else {
                if (input[2] >= 23.0) {
                    if (input[5] >= -2.775) {
                        if (input[5] >= 13.69) {
                            var18 = -0.006929127;
                        } else {
                            var18 = -0.0031992067;
                        }
                    } else {
                        var18 = -0.007910956;
                    }
                } else {
                    var18 = 0.0059472458;
                }
            }
        } else {
            if (input[5] >= 0.024999999) {
                if (input[1] >= 15.530001) {
                    if (input[1] >= 48.285) {
                        if (input[2] >= 17.5) {
                            var18 = -0.007847293;
                        } else {
                            var18 = -0.0070262174;
                        }
                    } else {
                        if (input[5] >= 3.5149999) {
                            var18 = -0.0069109797;
                        } else {
                            var18 = -0.005829926;
                        }
                    }
                } else {
                    if (input[5] >= 4.6850004) {
                        if (input[7] >= 1.7485454) {
                            var18 = -0.004605495;
                        } else {
                            var18 = -0.0007595541;
                        }
                    } else {
                        if (input[5] >= 1.1700001) {
                            var18 = 0.005968595;
                        } else {
                            var18 = -0.003049486;
                        }
                    }
                }
            } else {
                if (input[1] >= 51.515) {
                    if (input[2] >= 15.5) {
                        if (input[1] >= 58.125) {
                            var18 = -0.00878781;
                        } else {
                            var18 = -0.0066308375;
                        }
                    } else {
                        if (input[2] >= 9.5) {
                            var18 = -0.0032760464;
                        } else {
                            var18 = 0.0012883508;
                        }
                    }
                } else {
                    if (input[2] >= 22.5) {
                        if (input[1] >= 36.655) {
                            var18 = -0.0056207436;
                        } else {
                            var18 = -0.003290259;
                        }
                    } else {
                        if (input[7] >= 9.42682) {
                            var18 = -0.0019901195;
                        } else {
                            var18 = -0.0034772032;
                        }
                    }
                }
            }
        }
    }
    float var19;
    if (input[2] >= 38.5) {
        if (input[2] >= 62.5) {
            if (input[4] >= -95.0) {
                var19 = -0.006757925;
            } else {
                if (input[5] >= 0.605) {
                    if (input[2] >= 83.5) {
                        var19 = -0.0068460368;
                    } else {
                        if (input[1] >= 20.535) {
                            var19 = -0.0067967637;
                        } else {
                            var19 = -0.00644841;
                        }
                    }
                } else {
                    if (input[1] >= 36.145) {
                        var19 = -0.0072368705;
                    } else {
                        if (input[2] >= 75.5) {
                            var19 = -0.0071565225;
                        } else {
                            var19 = -0.0066537447;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 8.219999) {
                if (input[1] >= 28.375) {
                    if (input[1] >= 43.114998) {
                        if (input[4] >= -95.0) {
                            var19 = -0.0067540356;
                        } else {
                            var19 = -0.0068798545;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var19 = -0.006760511;
                        } else {
                            var19 = -0.006541528;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[5] >= -1.555) {
                            var19 = -0.0065035233;
                        } else {
                            var19 = -0.006799403;
                        }
                    } else {
                        if (input[5] >= 5.09) {
                            var19 = -0.006485309;
                        } else {
                            var19 = -0.005554656;
                        }
                    }
                }
            } else {
                if (input[5] >= 22.86) {
                    if (input[1] >= 0.90999997) {
                        var19 = -0.0060859593;
                    } else {
                        var19 = -0.0008629695;
                    }
                } else {
                    if (input[5] >= 22.765) {
                        var19 = 0.0067504146;
                    } else {
                        if (input[1] >= 7.24) {
                            var19 = -0.0057575125;
                        } else {
                            var19 = -0.003864246;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -0.605) {
            if (input[5] >= 0.005) {
                if (input[1] >= 21.224998) {
                    if (input[1] >= 39.235) {
                        if (input[2] >= 24.5) {
                            var19 = -0.006989166;
                        } else {
                            var19 = -0.0063305437;
                        }
                    } else {
                        if (input[5] >= 8.059999) {
                            var19 = -0.0065113935;
                        } else {
                            var19 = -0.0058344244;
                        }
                    }
                } else {
                    if (input[5] >= 12.23) {
                        if (input[1] >= 1.805) {
                            var19 = -0.0059074084;
                        } else {
                            var19 = -0.0018185464;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var19 = -0.0051226933;
                        } else {
                            var19 = -0.0028809889;
                        }
                    }
                }
            } else {
                if (input[2] >= 27.5) {
                    if (input[1] >= 34.989998) {
                        if (input[1] >= 49.065002) {
                            var19 = -0.0069664777;
                        } else {
                            var19 = -0.006192909;
                        }
                    } else {
                        if (input[7] >= 4.484642) {
                            var19 = -0.0032402053;
                        } else {
                            var19 = -0.005214084;
                        }
                    }
                } else {
                    if (input[1] >= 51.515) {
                        if (input[2] >= 17.5) {
                            var19 = -0.006944254;
                        } else {
                            var19 = -0.002904091;
                        }
                    } else {
                        if (input[7] >= 1.5077465) {
                            var19 = -0.0030642257;
                        } else {
                            var19 = -0.006563245;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -3.0749998) {
                if (input[1] >= 22.415) {
                    if (input[7] >= 1.4211965) {
                        var19 = -0.006607762;
                    } else {
                        var19 = -0.0019336896;
                    }
                } else {
                    if (input[7] >= 1.6672931) {
                        if (input[2] >= 24.5) {
                            var19 = -0.00603502;
                        } else {
                            var19 = 0.0005882507;
                        }
                    } else {
                        if (input[7] >= 1.6574825) {
                            var19 = 0.0040239794;
                        } else {
                            var19 = -0.004224746;
                        }
                    }
                }
            } else {
                if (input[1] >= 13.095) {
                    if (input[2] >= 20.5) {
                        var19 = -0.0067861625;
                    } else {
                        var19 = -0.0069103814;
                    }
                } else {
                    var19 = -0.0073744454;
                }
            }
        }
    }
    float var20;
    if (input[2] >= 31.5) {
        if (input[2] >= 48.5) {
            if (input[5] >= -2.165) {
                if (input[2] >= 67.5) {
                    if (input[3] >= -99.965) {
                        if (input[2] >= 92.5) {
                            var20 = -0.0061992425;
                        } else {
                            var20 = -0.0060735606;
                        }
                    } else {
                        if (input[1] >= 9.275) {
                            var20 = -0.006408937;
                        } else {
                            var20 = -0.0033261292;
                        }
                    }
                } else {
                    if (input[1] >= 35.675) {
                        if (input[3] >= -98.55) {
                            var20 = -0.006121892;
                        } else {
                            var20 = -0.0062914714;
                        }
                    } else {
                        if (input[3] >= -99.990005) {
                            var20 = -0.0059523447;
                        } else {
                            var20 = -0.005532618;
                        }
                    }
                }
            } else {
                var20 = -0.006069054;
            }
        } else {
            if (input[1] >= 17.474998) {
                if (input[4] >= -95.0) {
                    var20 = -0.0060857604;
                } else {
                    if (input[1] >= 35.125) {
                        if (input[1] >= 49.095) {
                            var20 = -0.0062562875;
                        } else {
                            var20 = -0.0058117476;
                        }
                    } else {
                        if (input[3] >= -91.54) {
                            var20 = -0.0060388595;
                        } else {
                            var20 = -0.004499092;
                        }
                    }
                }
            } else {
                if (input[5] >= -1.6949999) {
                    if (input[3] >= -74.16) {
                        if (input[1] >= 3.88) {
                            var20 = -0.006513302;
                        } else {
                            var20 = -0.004643476;
                        }
                    } else {
                        if (input[3] >= -89.385) {
                            var20 = -0.0044433004;
                        } else {
                            var20 = -0.0026726977;
                        }
                    }
                } else {
                    var20 = -0.006311367;
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 11.965) {
                if (input[5] >= -2.7849998) {
                    if (input[1] >= 25.695) {
                        if (input[3] >= -72.785) {
                            var20 = -0.0016923333;
                        } else {
                            var20 = -0.0059925965;
                        }
                    } else {
                        if (input[3] >= -87.93) {
                            var20 = -0.0056027346;
                        } else {
                            var20 = -0.0040569673;
                        }
                    }
                } else {
                    if (input[3] >= -99.985) {
                        var20 = -0.0060493406;
                    } else {
                        if (input[2] >= 20.5) {
                            var20 = -0.0061318534;
                        } else {
                            var20 = -0.0063020247;
                        }
                    }
                }
            } else {
                if (input[2] >= 22.5) {
                    if (input[5] >= -3.2150002) {
                        if (input[3] >= -85.83) {
                            var20 = -0.004807851;
                        } else {
                            var20 = 0.0011218599;
                        }
                    } else {
                        var20 = -0.0066746795;
                    }
                } else {
                    if (input[3] >= -89.770004) {
                        var20 = 0.005885405;
                    } else {
                        var20 = -0.0003482111;
                    }
                }
            }
        } else {
            if (input[3] >= -99.774994) {
                if (input[1] >= 14.299999) {
                    if (input[1] >= 48.625) {
                        if (input[2] >= 17.5) {
                            var20 = -0.006398351;
                        } else {
                            var20 = -0.005752091;
                        }
                    } else {
                        if (input[3] >= -94.815) {
                            var20 = -0.0057105264;
                        } else {
                            var20 = -0.004816086;
                        }
                    }
                } else {
                    if (input[3] >= -93.17) {
                        if (input[1] >= 1.585) {
                            var20 = -0.0034346674;
                        } else {
                            var20 = 0.0058567277;
                        }
                    } else {
                        if (input[1] >= 13.254999) {
                            var20 = -0.0032219768;
                        } else {
                            var20 = 0.0076857144;
                        }
                    }
                }
            } else {
                if (input[2] >= 20.5) {
                    if (input[1] >= 45.225) {
                        if (input[2] >= 27.5) {
                            var20 = -0.006405479;
                        } else {
                            var20 = -0.00545294;
                        }
                    } else {
                        if (input[1] >= 45.03) {
                            var20 = 0.0031708644;
                        } else {
                            var20 = -0.0032965739;
                        }
                    }
                } else {
                    if (input[1] >= 54.434998) {
                        if (input[2] >= 12.5) {
                            var20 = -0.0063241795;
                        } else {
                            var20 = -0.00062162115;
                        }
                    } else {
                        if (input[7] >= 4.6032677) {
                            var20 = -0.0014967264;
                        } else {
                            var20 = -0.0029638845;
                        }
                    }
                }
            }
        }
    }
    float var21;
    if (input[0] >= -20.0) {
        if (input[0] >= -12.5) {
            if (input[3] >= -99.915) {
                if (input[0] >= -7.5) {
                    if (input[1] >= 11.575) {
                        if (input[5] >= -2.225) {
                            var21 = -0.0055026417;
                        } else {
                            var21 = -0.005440662;
                        }
                    } else {
                        var21 = -0.00563283;
                    }
                } else {
                    if (input[5] >= 13.455) {
                        if (input[7] >= 1.647896) {
                            var21 = -0.004801942;
                        } else {
                            var21 = -0.005590861;
                        }
                    } else {
                        if (input[1] >= 3.96) {
                            var21 = -0.005412008;
                        } else {
                            var21 = -0.0006695971;
                        }
                    }
                }
            } else {
                if (input[5] >= -4.96) {
                    if (input[1] >= 50.215) {
                        var21 = -0.0061234045;
                    } else {
                        if (input[0] >= -7.5) {
                            var21 = -0.0058224546;
                        } else {
                            var21 = -0.00563638;
                        }
                    }
                } else {
                    var21 = -0.005449438;
                }
            }
        } else {
            if (input[5] >= 0.285) {
                if (input[1] >= 18.535) {
                    if (input[5] >= 7.94) {
                        if (input[7] >= 1.505028) {
                            var21 = -0.005812589;
                        } else {
                            var21 = 0.0014414362;
                        }
                    } else {
                        if (input[5] >= 7.895) {
                            var21 = 0.0014442648;
                        } else {
                            var21 = -0.0049383775;
                        }
                    }
                } else {
                    if (input[3] >= -99.635) {
                        if (input[7] >= 1.9057624) {
                            var21 = -0.004421721;
                        } else {
                            var21 = -0.0049654157;
                        }
                    } else {
                        if (input[1] >= 17.01) {
                            var21 = -0.0029702114;
                        } else {
                            var21 = 0.00622364;
                        }
                    }
                }
            } else {
                if (input[5] >= -2.815) {
                    if (input[1] >= 59.775) {
                        if (input[7] >= 9.922875) {
                            var21 = -0.0009939903;
                        } else {
                            var21 = -0.007929507;
                        }
                    } else {
                        if (input[6] >= 3.5) {
                            var21 = -0.0050461115;
                        } else {
                            var21 = -0.005519315;
                        }
                    }
                } else {
                    var21 = -0.0054938593;
                }
            }
        }
    } else {
        if (input[5] >= -2.06) {
            if (input[1] >= 40.5) {
                if (input[1] >= 40.525) {
                    if (input[1] >= 51.254997) {
                        if (input[1] >= 51.394997) {
                            var21 = -0.0030828544;
                        } else {
                            var21 = 0.0013263398;
                        }
                    } else {
                        if (input[1] >= 50.735) {
                            var21 = -0.0054075196;
                        } else {
                            var21 = -0.0038874347;
                        }
                    }
                } else {
                    var21 = 0.0090481555;
                }
            } else {
                if (input[1] >= 30.34) {
                    if (input[6] >= 7.5) {
                        if (input[7] >= 9.47299) {
                            var21 = -0.0041707624;
                        } else {
                            var21 = 0.0026624484;
                        }
                    } else {
                        if (input[7] >= 4.9517956) {
                            var21 = -0.0060152668;
                        } else {
                            var21 = -0.004559537;
                        }
                    }
                } else {
                    if (input[7] >= 9.859335) {
                        if (input[7] >= 9.86774) {
                            var21 = -0.004451081;
                        } else {
                            var21 = 0.0025022079;
                        }
                    } else {
                        if (input[7] >= 1.4821789) {
                            var21 = -0.0048944983;
                        } else {
                            var21 = -0.0107994415;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 47.455) {
                var21 = -0.0056639174;
            } else {
                var21 = -0.005515644;
            }
        }
    }
    float var22;
    if (input[2] >= 30.5) {
        if (input[2] >= 47.5) {
            if (input[5] >= -2.3449998) {
                if (input[0] >= -7.5) {
                    if (input[2] >= 78.5) {
                        var22 = -0.0048748106;
                    } else {
                        var22 = -0.0049628885;
                    }
                } else {
                    if (input[2] >= 79.5) {
                        if (input[0] >= -12.5) {
                            var22 = -0.0051313858;
                        } else {
                            var22 = -0.005368497;
                        }
                    } else {
                        if (input[1] >= 32.545) {
                            var22 = -0.0052152467;
                        } else {
                            var22 = -0.004549809;
                        }
                    }
                }
            } else {
                var22 = -0.004915136;
            }
        } else {
            if (input[1] >= 27.724998) {
                if (input[0] >= -20.0) {
                    if (input[5] >= -1.145) {
                        if (input[1] >= 33.82) {
                            var22 = -0.0051061907;
                        } else {
                            var22 = -0.0045396704;
                        }
                    } else {
                        var22 = -0.004900493;
                    }
                } else {
                    if (input[5] >= -5.0) {
                        if (input[1] >= 48.715) {
                            var22 = -0.004890544;
                        } else {
                            var22 = -0.0031425587;
                        }
                    } else {
                        var22 = -0.0050498154;
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    if (input[1] >= 10.575001) {
                        if (input[0] >= -2.5) {
                            var22 = -0.005259803;
                        } else {
                            var22 = -0.0046986197;
                        }
                    } else {
                        if (input[7] >= 9.813343) {
                            var22 = -0.004386353;
                        } else {
                            var22 = -0.005837726;
                        }
                    }
                } else {
                    if (input[5] >= -1.485) {
                        if (input[0] >= -12.5) {
                            var22 = -0.0029849317;
                        } else {
                            var22 = -0.0015527918;
                        }
                    } else {
                        if (input[5] >= -3.105) {
                            var22 = -0.0042139217;
                        } else {
                            var22 = -0.005167411;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -0.005) {
            if (input[0] >= -12.5) {
                if (input[5] >= 0.015) {
                    if (input[0] >= -7.5) {
                        if (input[0] >= -2.5) {
                            var22 = -0.0051467787;
                        } else {
                            var22 = -0.00479303;
                        }
                    } else {
                        if (input[1] >= 9.15) {
                            var22 = -0.0029983465;
                        } else {
                            var22 = -0.0008321064;
                        }
                    }
                } else {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 26.5) {
                            var22 = -0.005329862;
                        } else {
                            var22 = -0.0068069063;
                        }
                    } else {
                        if (input[1] >= 50.815002) {
                            var22 = -0.0061448235;
                        } else {
                            var22 = -0.0048772306;
                        }
                    }
                }
            } else {
                if (input[0] >= -20.0) {
                    if (input[5] >= 0.005) {
                        if (input[1] >= 26.25) {
                            var22 = -0.00034723352;
                        } else {
                            var22 = 0.0024959284;
                        }
                    } else {
                        if (input[7] >= 1.9745655) {
                            var22 = -0.002279082;
                        } else {
                            var22 = -0.004513136;
                        }
                    }
                } else {
                    if (input[2] >= 18.5) {
                        if (input[1] >= 50.864998) {
                            var22 = -0.0023440425;
                        } else {
                            var22 = 0.00018824606;
                        }
                    } else {
                        if (input[2] >= 13.5) {
                            var22 = 0.003127522;
                        } else {
                            var22 = 0.006912184;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[1] >= 7.9750004) {
                    if (input[0] >= -12.5) {
                        if (input[1] >= 9.96) {
                            var22 = -0.004880899;
                        } else {
                            var22 = -0.0019090169;
                        }
                    } else {
                        if (input[5] >= -3.02) {
                            var22 = -0.0014002416;
                        } else {
                            var22 = -0.0050494284;
                        }
                    }
                } else {
                    if (input[5] >= -1.9949999) {
                        var22 = 0.004453798;
                    } else {
                        var22 = -0.0033745721;
                    }
                }
            } else {
                if (input[2] >= 20.5) {
                    var22 = -0.0050524753;
                } else {
                    if (input[2] >= 9.5) {
                        var22 = -0.0053952388;
                    } else {
                        var22 = -0.0066653527;
                    }
                }
            }
        }
    }
    float var23;
    if (input[0] >= -12.5) {
        if (input[3] >= -99.985) {
            if (input[0] >= -7.5) {
                if (input[1] >= 15.245) {
                    if (input[5] >= -1.795) {
                        if (input[0] >= -2.5) {
                            var23 = -0.0044858265;
                        } else {
                            var23 = -0.004417976;
                        }
                    } else {
                        var23 = -0.004406993;
                    }
                } else {
                    if (input[7] >= 1.4204924) {
                        var23 = -0.0045450586;
                    } else {
                        if (input[1] >= 6.41) {
                            var23 = 0.0005156823;
                        } else {
                            var23 = -0.0029522507;
                        }
                    }
                }
            } else {
                if (input[1] >= 11.745) {
                    if (input[5] >= 1.285) {
                        if (input[7] >= 1.474612) {
                            var23 = -0.004268529;
                        } else {
                            var23 = 0.0012150645;
                        }
                    } else {
                        if (input[1] >= 62.215) {
                            var23 = -0.0010662851;
                        } else {
                            var23 = -0.0044457675;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[1] >= 6.8599997) {
                            var23 = -0.004302609;
                        } else {
                            var23 = -0.003704273;
                        }
                    } else {
                        if (input[1] >= 11.73) {
                            var23 = 0.0011061445;
                        } else {
                            var23 = -0.0035950541;
                        }
                    }
                }
            }
        } else {
            if (input[4] >= -95.0) {
                var23 = -0.004413852;
            } else {
                if (input[1] >= 52.275) {
                    var23 = -0.0050382717;
                } else {
                    if (input[0] >= -7.5) {
                        var23 = -0.0047659082;
                    } else {
                        if (input[7] >= 1.4796565) {
                            var23 = -0.0045720423;
                        } else {
                            var23 = -0.0009474194;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -1.495) {
            if (input[0] >= -20.0) {
                if (input[1] >= 21.785) {
                    if (input[7] >= 1.974331) {
                        if (input[7] >= 1.9823005) {
                            var23 = -0.004049722;
                        } else {
                            var23 = 0.004932177;
                        }
                    } else {
                        if (input[1] >= 51.15) {
                            var23 = -0.0054382076;
                        } else {
                            var23 = -0.004382189;
                        }
                    }
                } else {
                    if (input[1] >= 21.765) {
                        if (input[3] >= -97.994995) {
                            var23 = -0.0033466748;
                        } else {
                            var23 = 0.0038480125;
                        }
                    } else {
                        if (input[7] >= 1.4835689) {
                            var23 = -0.003730341;
                        } else {
                            var23 = 0.000021043123;
                        }
                    }
                }
            } else {
                if (input[1] >= 41.355) {
                    if (input[1] >= 41.465) {
                        if (input[1] >= 53.0) {
                            var23 = -0.0022546656;
                        } else {
                            var23 = -0.0030433435;
                        }
                    } else {
                        if (input[1] >= 41.445) {
                            var23 = 0.010953094;
                        } else {
                            var23 = -0.0010436645;
                        }
                    }
                } else {
                    if (input[5] >= 10.105) {
                        if (input[7] >= 9.96755) {
                            var23 = -0.0019311374;
                        } else {
                            var23 = -0.0045546605;
                        }
                    } else {
                        if (input[7] >= 9.984011) {
                            var23 = -0.005808896;
                        } else {
                            var23 = -0.0037054915;
                        }
                    }
                }
            }
        } else {
            var23 = -0.0044670436;
        }
    }
    float var24;
    if (input[0] >= -12.5) {
        if (input[3] >= -99.715) {
            if (input[0] >= -7.5) {
                if (input[3] >= -68.365) {
                    var24 = -0.0041609197;
                } else {
                    if (input[5] >= -1.795) {
                        if (input[0] >= -2.5) {
                            var24 = -0.0040417383;
                        } else {
                            var24 = -0.0039787334;
                        }
                    } else {
                        var24 = -0.003966056;
                    }
                }
            } else {
                if (input[3] >= -79.405) {
                    if (input[3] >= -79.395004) {
                        if (input[7] >= 1.5230885) {
                            var24 = -0.0035711818;
                        } else {
                            var24 = -0.0015972846;
                        }
                    } else {
                        var24 = 0.004149364;
                    }
                } else {
                    if (input[5] >= 0.755) {
                        if (input[7] >= 1.4801254) {
                            var24 = -0.0038659086;
                        } else {
                            var24 = -0.0001227551;
                        }
                    } else {
                        var24 = -0.0040015536;
                    }
                }
            }
        } else {
            if (input[4] >= -95.0) {
                var24 = -0.0039726016;
            } else {
                var24 = -0.004228122;
            }
        }
    } else {
        if (input[5] >= -1.555) {
            if (input[0] >= -20.0) {
                if (input[3] >= -99.865005) {
                    if (input[3] >= -68.515) {
                        if (input[3] >= -68.18) {
                            var24 = -0.002807425;
                        } else {
                            var24 = 0.000061112085;
                        }
                    } else {
                        if (input[7] >= 1.7634715) {
                            var24 = -0.0034117864;
                        } else {
                            var24 = -0.0038074665;
                        }
                    }
                } else {
                    if (input[6] >= 3.5) {
                        if (input[7] >= 4.4908214) {
                            var24 = -0.0036808513;
                        } else {
                            var24 = 0.0024232129;
                        }
                    } else {
                        if (input[7] >= 1.504657) {
                            var24 = -0.004079504;
                        } else {
                            var24 = -0.0022524279;
                        }
                    }
                }
            } else {
                if (input[7] >= 9.984011) {
                    var24 = -0.0054348293;
                } else {
                    if (input[7] >= 9.974315) {
                        if (input[7] >= 9.981665) {
                            var24 = -0.0017742178;
                        } else {
                            var24 = 0.008652152;
                        }
                    } else {
                        if (input[7] >= 9.967903) {
                            var24 = -0.0053760638;
                        } else {
                            var24 = -0.0031387748;
                        }
                    }
                }
            }
        } else {
            if (input[3] >= -81.575) {
                var24 = -0.00088290445;
            } else {
                var24 = -0.004020455;
            }
        }
    }
    return NAN + (var0 + var1 + var2 + var3 + var4 + var5 + var6 + var7 + var8 + var9 + var10 + var11 + var12 + var13 + var14 + var15 + var16 + var17 + var18 + var19 + var20 + var21 + var22 + var23 + var24);
}

volatile float result;
int main(void) {
    float input[8] = {-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f};
    result = score(input);
    return 0;
}
