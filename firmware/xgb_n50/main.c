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
    float var25;
    if (input[2] >= 30.5) {
        if (input[2] >= 48.5) {
            if (input[5] >= -2.3449998) {
                if (input[3] >= -99.535) {
                    if (input[2] >= 97.5) {
                        if (input[3] >= -86.665) {
                            var25 = -0.0036870108;
                        } else {
                            var25 = -0.0038442684;
                        }
                    } else {
                        if (input[1] >= 14.915) {
                            var25 = -0.0036311012;
                        } else {
                            var25 = -0.0034547586;
                        }
                    }
                } else {
                    if (input[2] >= 59.5) {
                        if (input[2] >= 90.5) {
                            var25 = -0.004092534;
                        } else {
                            var25 = -0.0038919356;
                        }
                    } else {
                        if (input[1] >= 34.175) {
                            var25 = -0.0038181306;
                        } else {
                            var25 = -0.0029417735;
                        }
                    }
                }
            } else {
                var25 = -0.0035791348;
            }
        } else {
            if (input[1] >= 26.71) {
                if (input[1] >= 39.775) {
                    if (input[2] >= 33.5) {
                        if (input[1] >= 53.905) {
                            var25 = -0.0037366827;
                        } else {
                            var25 = -0.0035616432;
                        }
                    } else {
                        if (input[5] >= -1.965) {
                            var25 = -0.003992027;
                        } else {
                            var25 = -0.0036057215;
                        }
                    }
                } else {
                    if (input[5] >= -0.005) {
                        if (input[5] >= 0.155) {
                            var25 = -0.0035770375;
                        } else {
                            var25 = -0.0027135634;
                        }
                    } else {
                        var25 = -0.003606553;
                    }
                }
            } else {
                if (input[5] >= -2.815) {
                    if (input[3] >= -85.365005) {
                        if (input[1] >= 13.485001) {
                            var25 = -0.0035879635;
                        } else {
                            var25 = -0.0027902778;
                        }
                    } else {
                        if (input[1] >= 13.16) {
                            var25 = -0.0022528213;
                        } else {
                            var25 = -0.000260041;
                        }
                    }
                } else {
                    if (input[1] >= 11.885) {
                        if (input[5] >= -2.8449998) {
                            var25 = -0.0014755738;
                        } else {
                            var25 = -0.0037066692;
                        }
                    } else {
                        if (input[3] >= -89.755005) {
                            var25 = -0.00464267;
                        } else {
                            var25 = -0.0038264156;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -0.005) {
            if (input[3] >= -99.375) {
                if (input[1] >= 11.115) {
                    if (input[1] >= 42.46) {
                        if (input[2] >= 22.5) {
                            var25 = -0.0039294916;
                        } else {
                            var25 = -0.0033606917;
                        }
                    } else {
                        if (input[3] >= -94.905) {
                            var25 = -0.003167875;
                        } else {
                            var25 = -0.0022984531;
                        }
                    }
                } else {
                    if (input[3] >= -78.145004) {
                        if (input[5] >= 40.18) {
                            var25 = 0.004231266;
                        } else {
                            var25 = -0.0025367234;
                        }
                    } else {
                        if (input[7] >= 9.602751) {
                            var25 = 0.0038392988;
                        } else {
                            var25 = -0.000008904899;
                        }
                    }
                }
            } else {
                if (input[1] >= 50.25) {
                    if (input[2] >= 17.5) {
                        if (input[7] >= 4.5723333) {
                            var25 = -0.0033069109;
                        } else {
                            var25 = -0.004410354;
                        }
                    } else {
                        if (input[2] >= 7.5) {
                            var25 = -0.0015505132;
                        } else {
                            var25 = 0.004632365;
                        }
                    }
                } else {
                    if (input[2] >= 23.5) {
                        if (input[1] >= 32.364998) {
                            var25 = -0.0024562674;
                        } else {
                            var25 = -0.0005514024;
                        }
                    } else {
                        if (input[7] >= 1.507901) {
                            var25 = -0.00054753927;
                        } else {
                            var25 = -0.003912573;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 7.795) {
                if (input[5] >= -2.565) {
                    if (input[1] >= 33.47) {
                        if (input[5] >= -2.5349998) {
                            var25 = -0.0036111895;
                        } else {
                            var25 = -0.0020165273;
                        }
                    } else {
                        if (input[1] >= 33.17) {
                            var25 = 0.00044496745;
                        } else {
                            var25 = -0.0029331571;
                        }
                    }
                } else {
                    if (input[3] >= -99.985) {
                        if (input[3] >= -82.705) {
                            var25 = -0.0016720247;
                        } else {
                            var25 = -0.0035739504;
                        }
                    } else {
                        if (input[2] >= 20.5) {
                            var25 = -0.0036259338;
                        } else {
                            var25 = -0.0037743256;
                        }
                    }
                }
            } else {
                if (input[5] >= -2.02) {
                    if (input[3] >= -81.075) {
                        var25 = 0.00083177537;
                    } else {
                        var25 = 0.0073192976;
                    }
                } else {
                    if (input[3] >= -82.58501) {
                        var25 = -0.00070915854;
                    } else {
                        var25 = -0.0038248838;
                    }
                }
            }
        }
    }
    float var26;
    if (input[0] >= -20.0) {
        if (input[0] >= -12.5) {
            if (input[4] >= -95.0) {
                if (input[5] >= 22.61) {
                    var26 = -0.0034324217;
                } else {
                    if (input[5] >= 22.59) {
                        if (input[0] >= -7.5) {
                            var26 = -0.0015901625;
                        } else {
                            var26 = 0.005978741;
                        }
                    } else {
                        if (input[1] >= 3.085) {
                            var26 = -0.0032225356;
                        } else {
                            var26 = -0.0020327454;
                        }
                    }
                }
            } else {
                if (input[5] >= 0.285) {
                    if (input[0] >= -7.5) {
                        if (input[5] >= 6.815) {
                            var26 = -0.00325023;
                        } else {
                            var26 = -0.0033258905;
                        }
                    } else {
                        if (input[5] >= 24.795) {
                            var26 = -0.0024558573;
                        } else {
                            var26 = -0.003112405;
                        }
                    }
                } else {
                    if (input[1] >= 50.315002) {
                        if (input[1] >= 57.23) {
                            var26 = -0.0039119986;
                        } else {
                            var26 = -0.003606985;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var26 = -0.0035187602;
                        } else {
                            var26 = -0.0033253194;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= 0.285) {
                if (input[5] >= 15.875) {
                    if (input[5] >= 15.915) {
                        if (input[7] >= 9.933895) {
                            var26 = -0.0041511925;
                        } else {
                            var26 = -0.0023191047;
                        }
                    } else {
                        if (input[1] >= 10.53) {
                            var26 = 0.0031062388;
                        } else {
                            var26 = -0.0020368074;
                        }
                    }
                } else {
                    if (input[7] >= 4.786912) {
                        if (input[7] >= 4.7904243) {
                            var26 = -0.0027181224;
                        } else {
                            var26 = 0.0050057783;
                        }
                    } else {
                        if (input[1] >= 2.875) {
                            var26 = -0.003078679;
                        } else {
                            var26 = 0.0013254414;
                        }
                    }
                }
            } else {
                if (input[5] >= -2.9650002) {
                    if (input[6] >= 3.5) {
                        if (input[7] >= 4.495761) {
                            var26 = -0.0029789514;
                        } else {
                            var26 = 0.002845898;
                        }
                    } else {
                        if (input[1] >= 51.15) {
                            var26 = -0.0041981167;
                        } else {
                            var26 = -0.0032206753;
                        }
                    }
                } else {
                    var26 = -0.0032420314;
                }
            }
        }
    } else {
        if (input[5] >= -0.005) {
            if (input[1] >= 37.184998) {
                if (input[1] >= 37.205) {
                    if (input[1] >= 47.075) {
                        if (input[1] >= 62.355003) {
                            var26 = 0.0050929836;
                        } else {
                            var26 = -0.0017614237;
                        }
                    } else {
                        if (input[1] >= 46.245003) {
                            var26 = -0.0035904408;
                        } else {
                            var26 = -0.0022297732;
                        }
                    }
                } else {
                    var26 = 0.008336068;
                }
            } else {
                if (input[5] >= 9.055) {
                    if (input[5] >= 35.489998) {
                        if (input[1] >= 0.65) {
                            var26 = 0.008083153;
                        } else {
                            var26 = -0.0025100303;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var26 = -0.0027239844;
                        } else {
                            var26 = -0.0036079255;
                        }
                    }
                } else {
                    if (input[5] >= 0.915) {
                        if (input[7] >= 1.5678015) {
                            var26 = -0.002469555;
                        } else {
                            var26 = -0.00009818645;
                        }
                    } else {
                        if (input[1] >= 24.3) {
                            var26 = -0.0027362215;
                        } else {
                            var26 = -0.0030793473;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 46.655) {
                var26 = -0.003371447;
            } else {
                if (input[1] >= 4.985) {
                    if (input[5] >= -0.48000002) {
                        if (input[1] >= 6.035) {
                            var26 = -0.004429495;
                        } else {
                            var26 = -0.0011267542;
                        }
                    } else {
                        if (input[5] >= -0.505) {
                            var26 = -0.0003858421;
                        } else {
                            var26 = -0.0032557414;
                        }
                    }
                } else {
                    if (input[5] >= -0.97) {
                        if (input[1] >= 4.815) {
                            var26 = 0.005957499;
                        } else {
                            var26 = -0.0007903371;
                        }
                    } else {
                        if (input[5] >= -1.2) {
                            var26 = -0.00066502433;
                        } else {
                            var26 = -0.003313989;
                        }
                    }
                }
            }
        }
    }
    float var27;
    if (input[2] >= 38.5) {
        if (input[5] >= -2.1750002) {
            if (input[2] >= 51.5) {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 78.5) {
                            var27 = -0.0028437132;
                        } else {
                            var27 = -0.0029246022;
                        }
                    } else {
                        if (input[2] >= 91.5) {
                            var27 = -0.0031520117;
                        } else {
                            var27 = -0.0029701495;
                        }
                    }
                } else {
                    if (input[1] >= 36.085) {
                        if (input[0] >= -20.0) {
                            var27 = -0.003394976;
                        } else {
                            var27 = -0.0037565161;
                        }
                    } else {
                        if (input[2] >= 75.5) {
                            var27 = -0.0033942093;
                        } else {
                            var27 = -0.002607433;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[1] >= 6.705) {
                        var27 = -0.002975619;
                    } else {
                        if (input[0] >= -7.5) {
                            var27 = -0.0032938973;
                        } else {
                            var27 = 0.0022077777;
                        }
                    }
                } else {
                    if (input[1] >= 43.605) {
                        if (input[6] >= 7.5) {
                            var27 = -0.0035008297;
                        } else {
                            var27 = -0.0029569392;
                        }
                    } else {
                        if (input[1] >= 23.18) {
                            var27 = -0.0020502652;
                        } else {
                            var27 = -0.00015931953;
                        }
                    }
                }
            }
        } else {
            var27 = -0.0029001283;
        }
    } else {
        if (input[5] >= -0.255) {
            if (input[0] >= -12.5) {
                if (input[5] >= 0.015) {
                    if (input[0] >= -7.5) {
                        if (input[1] >= 10.655) {
                            var27 = -0.0030101268;
                        } else {
                            var27 = -0.0037437424;
                        }
                    } else {
                        if (input[1] >= 14.17) {
                            var27 = -0.0019872405;
                        } else {
                            var27 = -0.00041810304;
                        }
                    }
                } else {
                    if (input[2] >= 25.5) {
                        if (input[1] >= 18.315) {
                            var27 = -0.003218701;
                        } else {
                            var27 = -0.001305014;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var27 = -0.0045995987;
                        } else {
                            var27 = -0.0033263084;
                        }
                    }
                }
            } else {
                if (input[2] >= 17.5) {
                    if (input[1] >= 51.6) {
                        if (input[1] >= 58.255) {
                            var27 = -0.0046047173;
                        } else {
                            var27 = -0.0026978918;
                        }
                    } else {
                        if (input[2] >= 28.5) {
                            var27 = -0.0013016517;
                        } else {
                            var27 = 0.00061195757;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[6] >= 3.5) {
                            var27 = 0.0020846545;
                        } else {
                            var27 = -0.0018749489;
                        }
                    } else {
                        if (input[2] >= 13.5) {
                            var27 = 0.003794709;
                        } else {
                            var27 = 0.0073002386;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[5] >= -2.815) {
                    if (input[0] >= -7.5) {
                        if (input[1] >= 19.09) {
                            var27 = -0.0029040107;
                        } else {
                            var27 = -0.0037010803;
                        }
                    } else {
                        if (input[2] >= 37.5) {
                            var27 = 0.0013391129;
                        } else {
                            var27 = -0.0016675998;
                        }
                    }
                } else {
                    if (input[0] >= -7.5) {
                        var27 = -0.002835024;
                    } else {
                        if (input[1] >= 42.940002) {
                            var27 = -0.0029087886;
                        } else {
                            var27 = -0.0030167361;
                        }
                    }
                }
            } else {
                if (input[5] >= -2.08) {
                    if (input[5] >= -1.415) {
                        var27 = 0.0050903424;
                    } else {
                        if (input[2] >= 36.0) {
                            var27 = 0.0019680837;
                        } else {
                            var27 = -0.00030250216;
                        }
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[5] >= -2.135) {
                            var27 = -0.0005109135;
                        } else {
                            var27 = -0.00303399;
                        }
                    } else {
                        if (input[2] >= 9.5) {
                            var27 = -0.0033006892;
                        } else {
                            var27 = -0.004507421;
                        }
                    }
                }
            }
        }
    }
    float var28;
    if (input[2] >= 38.5) {
        if (input[4] >= -95.0) {
            if (input[2] >= 100.5) {
                if (input[1] >= 12.845) {
                    var28 = -0.002631611;
                } else {
                    if (input[0] >= -7.5) {
                        var28 = -0.0025763267;
                    } else {
                        if (input[1] >= 7.99) {
                            var28 = -0.0028562208;
                        } else {
                            var28 = -0.0031313205;
                        }
                    }
                }
            } else {
                if (input[1] >= 6.3900003) {
                    if (input[1] >= 6.6549997) {
                        if (input[1] >= 6.68) {
                            var28 = -0.002615853;
                        } else {
                            var28 = -0.000720116;
                        }
                    } else {
                        if (input[2] >= 40.5) {
                            var28 = -0.0029834686;
                        } else {
                            var28 = -0.00040357263;
                        }
                    }
                } else {
                    if (input[0] >= -12.5) {
                        if (input[1] >= 6.375) {
                            var28 = -0.0011201021;
                        } else {
                            var28 = -0.002704677;
                        }
                    } else {
                        if (input[2] >= 57.5) {
                            var28 = -0.0021260206;
                        } else {
                            var28 = -0.00007410094;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[2] >= 76.5) {
                        var28 = -0.002530392;
                    } else {
                        if (input[1] >= 35.675) {
                            var28 = -0.0025857077;
                        } else {
                            var28 = -0.0026987563;
                        }
                    }
                } else {
                    if (input[1] >= 7.1949997) {
                        var28 = -0.0027037447;
                    } else {
                        if (input[2] >= 62.5) {
                            var28 = -0.0027224484;
                        } else {
                            var28 = 0.0010303006;
                        }
                    }
                }
            } else {
                if (input[2] >= 55.5) {
                    if (input[1] >= 35.735) {
                        if (input[0] >= -20.0) {
                            var28 = -0.0030870633;
                        } else {
                            var28 = -0.0034556796;
                        }
                    } else {
                        if (input[2] >= 72.5) {
                            var28 = -0.00304541;
                        } else {
                            var28 = -0.0023862238;
                        }
                    }
                } else {
                    if (input[1] >= 43.6) {
                        if (input[1] >= 51.105) {
                            var28 = -0.0032600784;
                        } else {
                            var28 = -0.0027852273;
                        }
                    } else {
                        if (input[1] >= 20.17) {
                            var28 = -0.0020478424;
                        } else {
                            var28 = 0.000022782615;
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] >= -12.5) {
            if (input[0] >= -7.5) {
                if (input[4] >= -95.0) {
                    if (input[1] >= 11.565001) {
                        if (input[0] >= -2.5) {
                            var28 = -0.002638851;
                        } else {
                            var28 = -0.002513931;
                        }
                    } else {
                        if (input[7] >= 1.4293125) {
                            var28 = -0.0033947881;
                        } else {
                            var28 = 0.0011798128;
                        }
                    }
                } else {
                    if (input[2] >= 23.5) {
                        if (input[1] >= 9.424999) {
                            var28 = -0.0027953908;
                        } else {
                            var28 = -0.003603369;
                        }
                    } else {
                        if (input[2] >= 9.5) {
                            var28 = -0.0031867374;
                        } else {
                            var28 = -0.004501381;
                        }
                    }
                }
            } else {
                if (input[1] >= 13.51) {
                    if (input[1] >= 32.92) {
                        if (input[2] >= 23.5) {
                            var28 = -0.002783765;
                        } else {
                            var28 = -0.0025189575;
                        }
                    } else {
                        if (input[4] >= -85.0) {
                            var28 = -0.0027266804;
                        } else {
                            var28 = -0.001848832;
                        }
                    }
                } else {
                    if (input[1] >= 6.885) {
                        if (input[1] >= 6.96) {
                            var28 = -0.0010455278;
                        } else {
                            var28 = -0.0060975784;
                        }
                    } else {
                        if (input[1] >= 6.395) {
                            var28 = 0.0045691705;
                        } else {
                            var28 = -0.000000028839954;
                        }
                    }
                }
            }
        } else {
            if (input[4] >= -95.0) {
                if (input[1] >= 16.619999) {
                    if (input[2] >= 20.5) {
                        if (input[0] >= -20.0) {
                            var28 = -0.002615907;
                        } else {
                            var28 = -0.0027235204;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var28 = -0.0028162566;
                        } else {
                            var28 = -0.0030150602;
                        }
                    }
                } else {
                    if (input[4] >= -85.0) {
                        if (input[1] >= 4.135) {
                            var28 = -0.0027744442;
                        } else {
                            var28 = 0.00030031565;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var28 = 0.0016028552;
                        } else {
                            var28 = -0.001606044;
                        }
                    }
                }
            } else {
                if (input[2] >= 24.5) {
                    if (input[1] >= 36.47) {
                        if (input[0] >= -20.0) {
                            var28 = -0.0031281305;
                        } else {
                            var28 = -0.0015781317;
                        }
                    } else {
                        if (input[7] >= 4.47829) {
                            var28 = 0.0004454675;
                        } else {
                            var28 = -0.0013011309;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[1] >= 54.4) {
                            var28 = -0.0035244336;
                        } else {
                            var28 = 0.00005833982;
                        }
                    } else {
                        if (input[2] >= 13.5) {
                            var28 = 0.0024388183;
                        } else {
                            var28 = 0.006288887;
                        }
                    }
                }
            }
        }
    }
    float var29;
    if (input[0] >= -20.0) {
        if (input[0] >= -12.5) {
            if (input[3] >= -99.985) {
                if (input[0] >= -2.5) {
                    if (input[1] >= 12.465) {
                        if (input[5] >= -2.955) {
                            var29 = -0.0023985207;
                        } else {
                            var29 = -0.0023363205;
                        }
                    } else {
                        var29 = -0.0025233233;
                    }
                } else {
                    if (input[5] >= 1.645) {
                        if (input[0] >= -7.5) {
                            var29 = -0.0023495324;
                        } else {
                            var29 = -0.002220594;
                        }
                    } else {
                        if (input[3] >= -99.975006) {
                            var29 = -0.0023545518;
                        } else {
                            var29 = -0.0016389864;
                        }
                    }
                }
            } else {
                if (input[4] >= -95.0) {
                    var29 = -0.002340934;
                } else {
                    if (input[1] >= 45.065002) {
                        if (input[1] >= 59.445) {
                            var29 = -0.0029817054;
                        } else {
                            var29 = -0.0026391717;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var29 = -0.0025684051;
                        } else {
                            var29 = -0.0024075627;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= 0.285) {
                if (input[3] >= -99.615005) {
                    if (input[3] >= -89.095) {
                        if (input[1] >= 28.375) {
                            var29 = 0.0020166792;
                        } else {
                            var29 = -0.0018329531;
                        }
                    } else {
                        if (input[6] >= 3.5) {
                            var29 = -0.0019740053;
                        } else {
                            var29 = -0.002286851;
                        }
                    }
                } else {
                    if (input[1] >= 18.49) {
                        if (input[3] >= -99.634995) {
                            var29 = 0.0023671256;
                        } else {
                            var29 = -0.002082;
                        }
                    } else {
                        var29 = 0.006620606;
                    }
                }
            } else {
                if (input[1] >= 59.775) {
                    if (input[4] >= -95.0) {
                        var29 = -0.0023123508;
                    } else {
                        if (input[1] >= 61.9) {
                            var29 = -0.0017569702;
                        } else {
                            var29 = -0.0043251147;
                        }
                    }
                } else {
                    if (input[1] >= 59.75) {
                        var29 = 0.0052932356;
                    } else {
                        if (input[1] >= 59.17) {
                            var29 = -0.001188653;
                        } else {
                            var29 = -0.0023464567;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -1.805) {
            if (input[1] >= 44.695) {
                if (input[6] >= 3.5) {
                    if (input[1] >= 45.065002) {
                        if (input[1] >= 55.895) {
                            var29 = -0.00032468812;
                        } else {
                            var29 = -0.0013579206;
                        }
                    } else {
                        if (input[1] >= 45.004997) {
                            var29 = 0.009415104;
                        } else {
                            var29 = -0.00080178323;
                        }
                    }
                } else {
                    if (input[1] >= 56.879997) {
                        if (input[1] >= 61.295) {
                            var29 = -0.008964159;
                        } else {
                            var29 = -0.0033313152;
                        }
                    } else {
                        if (input[1] >= 56.595) {
                            var29 = 0.0040391623;
                        } else {
                            var29 = -0.0014498894;
                        }
                    }
                }
            } else {
                if (input[1] >= 44.575) {
                    if (input[1] >= 44.684998) {
                        if (input[6] >= 3.5) {
                            var29 = -0.0015346557;
                        } else {
                            var29 = -0.007892792;
                        }
                    } else {
                        if (input[1] >= 44.67) {
                            var29 = 0.00090419914;
                        } else {
                            var29 = -0.0036146254;
                        }
                    }
                } else {
                    if (input[1] >= 36.92) {
                        if (input[1] >= 36.995003) {
                            var29 = -0.0017837273;
                        } else {
                            var29 = 0.00062519114;
                        }
                    } else {
                        if (input[5] >= 14.045) {
                            var29 = -0.002598387;
                        } else {
                            var29 = -0.002003543;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 42.785) {
                var29 = -0.002436766;
            } else {
                var29 = -0.0023673081;
            }
        }
    }
    float var30;
    if (input[2] >= 29.5) {
        if (input[2] >= 48.5) {
            if (input[4] >= -95.0) {
                if (input[5] >= -2.3649998) {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 78.5) {
                            var30 = -0.0020899945;
                        } else {
                            var30 = -0.0021626719;
                        }
                    } else {
                        if (input[2] >= 81.5) {
                            var30 = -0.0024989438;
                        } else {
                            var30 = -0.0019756022;
                        }
                    }
                } else {
                    if (input[2] >= 75.5) {
                        var30 = -0.0020942183;
                    } else {
                        if (input[1] >= 15.385) {
                            var30 = -0.0021172506;
                        } else {
                            var30 = -0.0022171584;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        if (input[5] >= 0.225) {
                            var30 = -0.002097501;
                        } else {
                            var30 = -0.0018680716;
                        }
                    } else {
                        if (input[5] >= 25.025002) {
                            var30 = -0.0017989547;
                        } else {
                            var30 = -0.002195475;
                        }
                    }
                } else {
                    if (input[1] >= 35.754997) {
                        if (input[2] >= 53.5) {
                            var30 = -0.0027099557;
                        } else {
                            var30 = -0.0023656029;
                        }
                    } else {
                        if (input[2] >= 72.5) {
                            var30 = -0.0025240202;
                        } else {
                            var30 = -0.0018391078;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 27.904999) {
                if (input[1] >= 39.085) {
                    if (input[2] >= 35.5) {
                        if (input[1] >= 47.885002) {
                            var30 = -0.0021763186;
                        } else {
                            var30 = -0.0020825507;
                        }
                    } else {
                        if (input[5] >= -2.0749998) {
                            var30 = -0.0024500068;
                        } else {
                            var30 = -0.0021329694;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[0] >= -12.5) {
                            var30 = -0.0021393616;
                        } else {
                            var30 = -0.001943509;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var30 = -0.002192767;
                        } else {
                            var30 = -0.0006184413;
                        }
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    if (input[0] >= -2.5) {
                        if (input[1] >= 12.48) {
                            var30 = -0.0024047382;
                        } else {
                            var30 = -0.002998008;
                        }
                    } else {
                        if (input[1] >= 17.994999) {
                            var30 = -0.0018503724;
                        } else {
                            var30 = -0.0022825703;
                        }
                    }
                } else {
                    if (input[5] >= -1.665) {
                        if (input[0] >= -12.5) {
                            var30 = -0.00085652614;
                        } else {
                            var30 = 0.000041356645;
                        }
                    } else {
                        if (input[5] >= -1.725) {
                            var30 = -0.0040542516;
                        } else {
                            var30 = -0.0022832842;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[5] >= -2.5549998) {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        if (input[5] >= 14.525) {
                            var30 = -0.003242375;
                        } else {
                            var30 = -0.0020382097;
                        }
                    } else {
                        if (input[1] >= 6.875) {
                            var30 = -0.0011153661;
                        } else {
                            var30 = 0.0019418973;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[1] >= 17.265) {
                            var30 = 0.0001657977;
                        } else {
                            var30 = 0.0040168012;
                        }
                    } else {
                        if (input[2] >= 27.5) {
                            var30 = 0.0033554079;
                        } else {
                            var30 = -0.0034790125;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[1] >= 8.94) {
                        if (input[0] >= -7.5) {
                            var30 = -0.0020581626;
                        } else {
                            var30 = -0.0021398747;
                        }
                    } else {
                        var30 = 0.00035929345;
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[1] >= 43.690002) {
                            var30 = -0.0020773865;
                        } else {
                            var30 = -0.0022359814;
                        }
                    } else {
                        if (input[1] >= 13.514999) {
                            var30 = -0.0023879046;
                        } else {
                            var30 = 0.0009539418;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[0] >= -12.5) {
                    if (input[5] >= 0.285) {
                        if (input[0] >= -7.5) {
                            var30 = -0.0022570314;
                        } else {
                            var30 = -0.00055493094;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var30 = -0.003421188;
                        } else {
                            var30 = -0.0024788356;
                        }
                    }
                } else {
                    if (input[5] >= 0.005) {
                        if (input[5] >= 14.625) {
                            var30 = 0.005577631;
                        } else {
                            var30 = 0.001775463;
                        }
                    } else {
                        if (input[2] >= 16.5) {
                            var30 = -0.0012626814;
                        } else {
                            var30 = 0.0009932456;
                        }
                    }
                }
            } else {
                if (input[2] >= 14.5) {
                    if (input[1] >= 60.835) {
                        if (input[6] >= 3.5) {
                            var30 = -0.0026826968;
                        } else {
                            var30 = -0.007931784;
                        }
                    } else {
                        if (input[2] >= 18.5) {
                            var30 = 0.0012321589;
                        } else {
                            var30 = 0.0033862093;
                        }
                    }
                } else {
                    if (input[1] >= 60.114998) {
                        if (input[1] >= 60.620003) {
                            var30 = 0.0028555768;
                        } else {
                            var30 = -0.0062055043;
                        }
                    } else {
                        if (input[1] >= 56.45) {
                            var30 = 0.015180859;
                        } else {
                            var30 = 0.0051158387;
                        }
                    }
                }
            }
        }
    }
    float var31;
    if (input[2] >= 28.5) {
        if (input[2] >= 38.5) {
            if (input[4] >= -95.0) {
                if (input[2] >= 100.5) {
                    if (input[5] >= -2.41) {
                        if (input[0] >= -7.5) {
                            var31 = -0.001869595;
                        } else {
                            var31 = -0.0023397773;
                        }
                    } else {
                        var31 = -0.001880315;
                    }
                } else {
                    if (input[1] >= 6.0950003) {
                        if (input[0] >= -12.5) {
                            var31 = -0.0019163712;
                        } else {
                            var31 = -0.0018926986;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var31 = -0.0018920958;
                        } else {
                            var31 = -0.0012743331;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[0] >= -7.5) {
                        if (input[5] >= 0.375) {
                            var31 = -0.0019033205;
                        } else {
                            var31 = -0.001761167;
                        }
                    } else {
                        if (input[1] >= 6.3199997) {
                            var31 = -0.0019765666;
                        } else {
                            var31 = -0.0014368267;
                        }
                    }
                } else {
                    if (input[2] >= 55.5) {
                        if (input[1] >= 31.105) {
                            var31 = -0.0024036348;
                        } else {
                            var31 = -0.0020785055;
                        }
                    } else {
                        if (input[1] >= 43.605) {
                            var31 = -0.0022967511;
                        } else {
                            var31 = -0.0012580784;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 32.03) {
                if (input[6] >= 3.5) {
                    if (input[0] >= -20.0) {
                        if (input[5] >= -1.215) {
                            var31 = -0.0020967796;
                        } else {
                            var31 = -0.0018801084;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var31 = -0.0020037927;
                        } else {
                            var31 = -0.0010057372;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[0] >= -20.0) {
                            var31 = -0.0018796053;
                        } else {
                            var31 = -0.0020161967;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var31 = -0.0019647588;
                        } else {
                            var31 = -0.0026089582;
                        }
                    }
                }
            } else {
                if (input[5] >= -0.365) {
                    if (input[0] >= -7.5) {
                        if (input[0] >= -2.5) {
                            var31 = -0.0022961344;
                        } else {
                            var31 = -0.0017991413;
                        }
                    } else {
                        if (input[6] >= 3.5) {
                            var31 = 0.000109179935;
                        } else {
                            var31 = -0.0009212663;
                        }
                    }
                } else {
                    if (input[5] >= -3.19) {
                        if (input[0] >= -12.5) {
                            var31 = -0.0018600876;
                        } else {
                            var31 = -0.00066617475;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var31 = -0.0018231074;
                        } else {
                            var31 = -0.0020572057;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 7.05) {
                if (input[0] >= -20.0) {
                    if (input[5] >= -2.5549998) {
                        if (input[0] >= -7.5) {
                            var31 = -0.0018970169;
                        } else {
                            var31 = -0.00011871414;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var31 = -0.0018505115;
                        } else {
                            var31 = -0.0019545595;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        if (input[2] >= 20.5) {
                            var31 = -0.0019734446;
                        } else {
                            var31 = -0.002189344;
                        }
                    } else {
                        if (input[1] >= 58.98) {
                            var31 = -0.0019651125;
                        } else {
                            var31 = -0.003849832;
                        }
                    }
                }
            } else {
                if (input[5] >= 13.81) {
                    if (input[0] >= -12.5) {
                        if (input[5] >= 26.825) {
                            var31 = -0.0033957863;
                        } else {
                            var31 = -0.0015832471;
                        }
                    } else {
                        var31 = 0.0008723428;
                    }
                } else {
                    if (input[5] >= -1.285) {
                        if (input[5] >= 3.025) {
                            var31 = 0.0018735941;
                        } else {
                            var31 = 0.0062743463;
                        }
                    } else {
                        if (input[5] >= -2.135) {
                            var31 = -0.00039605013;
                        } else {
                            var31 = -0.0025886467;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[0] >= -12.5) {
                    if (input[5] >= 0.53499997) {
                        if (input[0] >= -7.5) {
                            var31 = -0.0020036676;
                        } else {
                            var31 = -0.00040572506;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var31 = -0.003111834;
                        } else {
                            var31 = -0.002269374;
                        }
                    }
                } else {
                    if (input[2] >= 14.5) {
                        if (input[1] >= 53.184998) {
                            var31 = -0.0034108222;
                        } else {
                            var31 = -0.00017081008;
                        }
                    } else {
                        if (input[1] >= 57.175) {
                            var31 = 0.006770123;
                        } else {
                            var31 = 0.0019684318;
                        }
                    }
                }
            } else {
                if (input[2] >= 18.5) {
                    if (input[1] >= 49.5) {
                        if (input[6] >= 3.5) {
                            var31 = -0.00010964637;
                        } else {
                            var31 = -0.0024060588;
                        }
                    } else {
                        if (input[1] >= 31.599998) {
                            var31 = 0.0013254416;
                        } else {
                            var31 = 0.0037234218;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        if (input[1] >= 50.27) {
                            var31 = 0.0018958852;
                        } else {
                            var31 = 0.0045964643;
                        }
                    } else {
                        if (input[1] >= 60.135002) {
                            var31 = -0.0036845435;
                        } else {
                            var31 = 0.010035059;
                        }
                    }
                }
            }
        }
    }
    float var32;
    if (input[0] >= -20.0) {
        if (input[1] >= 59.425) {
            if (input[4] >= -95.0) {
                var32 = -0.0016988941;
            } else {
                if (input[0] >= -7.5) {
                    if (input[5] >= 15.655001) {
                        var32 = 0.0005724871;
                    } else {
                        var32 = -0.0017473467;
                    }
                } else {
                    if (input[7] >= 1.783973) {
                        if (input[7] >= 4.7641687) {
                            var32 = -0.0027287654;
                        } else {
                            var32 = -0.003839785;
                        }
                    } else {
                        if (input[7] >= 1.7749541) {
                            var32 = 0.0033108832;
                        } else {
                            var32 = -0.0023411256;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 59.415) {
                if (input[7] >= 9.681759) {
                    if (input[0] >= -12.5) {
                        var32 = -0.0009239685;
                    } else {
                        if (input[7] >= 9.773305) {
                            var32 = 0.0016615316;
                        } else {
                            var32 = -0.000004624327;
                        }
                    }
                } else {
                    var32 = 0.01666153;
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[5] >= -2.1750002) {
                        if (input[5] >= 0.015) {
                            var32 = -0.0017121853;
                        } else {
                            var32 = -0.0018173599;
                        }
                    } else {
                        if (input[1] >= 6.375) {
                            var32 = -0.0017084843;
                        } else {
                            var32 = -0.0030048895;
                        }
                    }
                } else {
                    if (input[5] >= 2.065) {
                        if (input[1] >= 36.405) {
                            var32 = -0.0021368149;
                        } else {
                            var32 = -0.0014087145;
                        }
                    } else {
                        if (input[1] >= 59.17) {
                            var32 = -0.00021353828;
                        } else {
                            var32 = -0.0017016741;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -2.06) {
            if (input[1] >= 40.5) {
                if (input[1] >= 40.525) {
                    if (input[1] >= 59.345) {
                        if (input[1] >= 59.92) {
                            var32 = -0.0019458447;
                        } else {
                            var32 = -0.0069354693;
                        }
                    } else {
                        if (input[1] >= 57.795) {
                            var32 = 0.00084301684;
                        } else {
                            var32 = -0.0010706667;
                        }
                    }
                } else {
                    var32 = 0.010062638;
                }
            } else {
                if (input[7] >= 1.4935164) {
                    if (input[7] >= 9.668745) {
                        if (input[7] >= 9.67148) {
                            var32 = -0.0011615775;
                        } else {
                            var32 = 0.008466372;
                        }
                    } else {
                        if (input[1] >= 39.655) {
                            var32 = -0.0022995514;
                        } else {
                            var32 = -0.001476271;
                        }
                    }
                } else {
                    if (input[7] >= 1.455317) {
                        var32 = -0.0064022825;
                    } else {
                        var32 = -0.0010963202;
                    }
                }
            }
        } else {
            if (input[1] >= 52.059998) {
                var32 = -0.0018358937;
            } else {
                if (input[1] >= 39.645) {
                    var32 = -0.0017598419;
                } else {
                    if (input[1] >= 7.215) {
                        var32 = -0.0017185027;
                    } else {
                        var32 = -0.0019312503;
                    }
                }
            }
        }
    }
    float var33;
    if (input[0] >= -12.5) {
        if (input[4] >= -95.0) {
            if (input[3] >= -58.655) {
                if (input[7] >= 9.963695) {
                    if (input[0] >= -5.0) {
                        var33 = -0.0008116633;
                    } else {
                        var33 = 0.00045488199;
                    }
                } else {
                    if (input[1] >= 0.96500003) {
                        if (input[1] >= 1.3299999) {
                            var33 = -0.001721073;
                        } else {
                            var33 = -0.0027397554;
                        }
                    } else {
                        if (input[1] >= 0.93) {
                            var33 = 0.0011136577;
                        } else {
                            var33 = -0.0013771089;
                        }
                    }
                }
            } else {
                if (input[1] >= 2.34) {
                    if (input[5] >= 31.265) {
                        var33 = 0.0017238444;
                    } else {
                        if (input[1] >= 6.645) {
                            var33 = -0.0015430559;
                        } else {
                            var33 = -0.0013976028;
                        }
                    }
                } else {
                    if (input[1] >= 2.2) {
                        if (input[5] >= 29.91) {
                            var33 = -0.0010159379;
                        } else {
                            var33 = 0.0058838683;
                        }
                    } else {
                        var33 = -0.0018233847;
                    }
                }
            }
        } else {
            if (input[3] >= -98.265) {
                if (input[0] >= -7.5) {
                    if (input[1] >= 16.125) {
                        if (input[1] >= 16.134998) {
                            var33 = -0.0015519018;
                        } else {
                            var33 = 0.0026346303;
                        }
                    } else {
                        if (input[3] >= -89.2) {
                            var33 = -0.0016127164;
                        } else {
                            var33 = -0.0021868197;
                        }
                    }
                } else {
                    if (input[1] >= 11.795) {
                        if (input[7] >= 1.4797735) {
                            var33 = -0.0015307727;
                        } else {
                            var33 = 0.00114038;
                        }
                    } else {
                        if (input[3] >= -82.785) {
                            var33 = -0.0012695027;
                        } else {
                            var33 = -0.0005384895;
                        }
                    }
                }
            } else {
                if (input[1] >= 49.545) {
                    if (input[0] >= -7.5) {
                        if (input[1] >= 60.03) {
                            var33 = -0.0013734656;
                        } else {
                            var33 = -0.0016992098;
                        }
                    } else {
                        if (input[3] >= -99.765) {
                            var33 = -0.0012995313;
                        } else {
                            var33 = -0.0019135065;
                        }
                    }
                } else {
                    if (input[7] >= 9.720575) {
                        if (input[7] >= 9.728317) {
                            var33 = -0.0015212802;
                        } else {
                            var33 = 0.0016573895;
                        }
                    } else {
                        if (input[7] >= 9.716461) {
                            var33 = -0.003649701;
                        } else {
                            var33 = -0.0016543737;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -2.815) {
            if (input[7] >= 1.4907175) {
                if (input[7] >= 4.4404573) {
                    if (input[7] >= 4.5199056) {
                        if (input[7] >= 9.939636) {
                            var33 = -0.0009079703;
                        } else {
                            var33 = -0.001316446;
                        }
                    } else {
                        if (input[7] >= 4.466353) {
                            var33 = -0.00009836949;
                        } else {
                            var33 = 0.0051009175;
                        }
                    }
                } else {
                    if (input[1] >= 56.465) {
                        if (input[1] >= 61.225) {
                            var33 = -0.0065306085;
                        } else {
                            var33 = -0.0032035478;
                        }
                    } else {
                        if (input[7] >= 1.98401) {
                            var33 = -0.0034752141;
                        } else {
                            var33 = -0.0014051845;
                        }
                    }
                }
            } else {
                if (input[7] >= 1.487809) {
                    if (input[1] >= 55.1) {
                        var33 = -0.0025238998;
                    } else {
                        var33 = -0.007407967;
                    }
                } else {
                    if (input[7] >= 1.4636455) {
                        if (input[7] >= 1.474369) {
                            var33 = -0.0028444154;
                        } else {
                            var33 = -0.00036134513;
                        }
                    } else {
                        if (input[1] >= 57.995003) {
                            var33 = -0.0010564536;
                        } else {
                            var33 = -0.007780231;
                        }
                    }
                }
            }
        } else {
            if (input[3] >= -90.255005) {
                if (input[3] >= -83.005005) {
                    var33 = -0.0024023936;
                } else {
                    if (input[3] >= -83.025) {
                        if (input[0] >= -20.0) {
                            var33 = -0.0008932748;
                        } else {
                            var33 = 0.0017850854;
                        }
                    } else {
                        if (input[1] >= 3.5149999) {
                            var33 = -0.001720901;
                        } else {
                            var33 = -0.0009742472;
                        }
                    }
                }
            } else {
                var33 = -0.0015594818;
            }
        }
    }
    float var34;
    if (input[0] >= -20.0) {
        if (input[5] >= 0.565) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[3] >= -93.425) {
                        if (input[3] >= -78.925) {
                            var34 = -0.0014465508;
                        } else {
                            var34 = -0.001380524;
                        }
                    } else {
                        if (input[3] >= -99.415) {
                            var34 = -0.001461225;
                        } else {
                            var34 = -0.00037948854;
                        }
                    }
                } else {
                    if (input[5] >= 24.795) {
                        if (input[3] >= -75.020004) {
                            var34 = -0.00082960725;
                        } else {
                            var34 = 0.0031468992;
                        }
                    } else {
                        if (input[5] >= 13.46) {
                            var34 = -0.0011549416;
                        } else {
                            var34 = -0.0013601934;
                        }
                    }
                }
            } else {
                if (input[3] >= -99.375) {
                    if (input[7] >= 1.9057624) {
                        if (input[7] >= 1.9153745) {
                            var34 = -0.0011102896;
                        } else {
                            var34 = 0.0069096857;
                        }
                    } else {
                        if (input[5] >= 6.025) {
                            var34 = -0.0011235658;
                        } else {
                            var34 = -0.0015451014;
                        }
                    }
                } else {
                    if (input[7] >= 9.924048) {
                        if (input[7] >= 9.973158) {
                            var34 = -0.0014991155;
                        } else {
                            var34 = 0.009389165;
                        }
                    } else {
                        if (input[7] >= 4.624693) {
                            var34 = -0.0010413177;
                        } else {
                            var34 = 0.00078130903;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -0.14500001) {
                if (input[7] >= 4.599846) {
                    if (input[0] >= -12.5) {
                        if (input[7] >= 4.602402) {
                            var34 = -0.0014924094;
                        } else {
                            var34 = 0.0018325059;
                        }
                    } else {
                        if (input[7] >= 9.939988) {
                            var34 = -0.0007022372;
                        } else {
                            var34 = -0.0013249647;
                        }
                    }
                } else {
                    if (input[7] >= 4.596992) {
                        var34 = -0.005314292;
                    } else {
                        if (input[7] >= 1.7529216) {
                            var34 = -0.0015927618;
                        } else {
                            var34 = -0.0014339163;
                        }
                    }
                }
            } else {
                if (input[5] >= -0.215) {
                    if (input[0] >= -7.5) {
                        if (input[7] >= 9.864803) {
                            var34 = -0.0005849157;
                        } else {
                            var34 = -0.0012805043;
                        }
                    } else {
                        if (input[7] >= 4.7212954) {
                            var34 = -0.000743261;
                        } else {
                            var34 = 0.006402347;
                        }
                    }
                } else {
                    if (input[3] >= -80.255005) {
                        if (input[6] >= 7.5) {
                            var34 = 0.000546058;
                        } else {
                            var34 = -0.001414742;
                        }
                    } else {
                        if (input[3] >= -80.955) {
                            var34 = -0.0012620122;
                        } else {
                            var34 = -0.0013883503;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -2.06) {
            if (input[7] >= 1.505324) {
                if (input[7] >= 9.984011) {
                    var34 = -0.0029049816;
                } else {
                    if (input[7] >= 9.981195) {
                        if (input[7] >= 9.981665) {
                            var34 = -0.00037481255;
                        } else {
                            var34 = 0.0070029083;
                        }
                    } else {
                        if (input[7] >= 9.967199) {
                            var34 = -0.0025499554;
                        } else {
                            var34 = -0.0010632727;
                        }
                    }
                }
            } else {
                if (input[3] >= -98.715) {
                    if (input[3] >= -93.975) {
                        var34 = 0.00027593898;
                    } else {
                        var34 = 0.0039826813;
                    }
                } else {
                    if (input[7] >= 1.4750235) {
                        if (input[7] >= 1.4833889) {
                            var34 = -0.004182601;
                        } else {
                            var34 = -0.009239486;
                        }
                    } else {
                        if (input[7] >= 1.463176) {
                            var34 = 0.0026012347;
                        } else {
                            var34 = -0.005528033;
                        }
                    }
                }
            }
        } else {
            if (input[3] >= -92.16) {
                var34 = -0.0015564013;
            } else {
                if (input[5] >= -2.625) {
                    if (input[6] >= 3.5) {
                        if (input[7] >= 4.55271) {
                            var34 = -0.00081216;
                        } else {
                            var34 = -0.000043829346;
                        }
                    } else {
                        var34 = -0.0013541345;
                    }
                } else {
                    var34 = -0.001411956;
                }
            }
        }
    }
    float var35;
    if (input[2] >= 24.5) {
        if (input[2] >= 38.5) {
            if (input[4] >= -95.0) {
                if (input[2] >= 100.5) {
                    if (input[1] >= 8.24) {
                        if (input[3] >= -92.125) {
                            var35 = -0.0013235672;
                        } else {
                            var35 = -0.0012243959;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var35 = -0.0012047355;
                        } else {
                            var35 = -0.0017157047;
                        }
                    }
                } else {
                    if (input[1] >= 8.295) {
                        if (input[1] >= 10.915) {
                            var35 = -0.0012497172;
                        } else {
                            var35 = -0.0013456194;
                        }
                    } else {
                        if (input[1] >= 8.285) {
                            var35 = 0.002335345;
                        } else {
                            var35 = -0.0011672963;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[3] >= -99.845) {
                        if (input[0] >= -7.5) {
                            var35 = -0.0012429999;
                        } else {
                            var35 = -0.0013535393;
                        }
                    } else {
                        if (input[2] >= 45.5) {
                            var35 = -0.0011315636;
                        } else {
                            var35 = -0.0013374117;
                        }
                    }
                } else {
                    if (input[2] >= 53.5) {
                        if (input[1] >= 36.325) {
                            var35 = -0.0018328734;
                        } else {
                            var35 = -0.0014791322;
                        }
                    } else {
                        if (input[1] >= 43.605) {
                            var35 = -0.0016000693;
                        } else {
                            var35 = -0.0007397152;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 33.205) {
                if (input[1] >= 33.22) {
                    if (input[0] >= -20.0) {
                        if (input[4] >= -95.0) {
                            var35 = -0.0012375206;
                        } else {
                            var35 = -0.0014677523;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var35 = -0.0013241693;
                        } else {
                            var35 = -0.0006480151;
                        }
                    }
                } else {
                    if (input[0] >= -12.5) {
                        var35 = -0.00060389895;
                    } else {
                        var35 = -0.006892285;
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    if (input[0] >= -2.5) {
                        if (input[1] >= 12.075) {
                            var35 = -0.0014305402;
                        } else {
                            var35 = -0.0021569529;
                        }
                    } else {
                        if (input[7] >= 9.83666) {
                            var35 = -0.00066277373;
                        } else {
                            var35 = -0.0012249154;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[1] >= 4.415) {
                            var35 = -0.0011217006;
                        } else {
                            var35 = 0.0027420202;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var35 = -0.0005506168;
                        } else {
                            var35 = 0.0005072769;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 11.09) {
                if (input[0] >= -12.5) {
                    if (input[1] >= 27.395) {
                        if (input[3] >= -80.33) {
                            var35 = -0.00047571908;
                        } else {
                            var35 = -0.001221403;
                        }
                    } else {
                        if (input[1] >= 27.279999) {
                            var35 = 0.004815121;
                        } else {
                            var35 = -0.00039291984;
                        }
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[1] >= 43.66) {
                            var35 = -0.0012085041;
                        } else {
                            var35 = -0.0013268584;
                        }
                    } else {
                        if (input[2] >= 9.5) {
                            var35 = -0.0014550633;
                        } else {
                            var35 = -0.0018175436;
                        }
                    }
                }
            } else {
                if (input[3] >= -91.3) {
                    if (input[3] >= -85.845) {
                        if (input[3] >= -83.395004) {
                            var35 = 0.0041551357;
                        } else {
                            var35 = -0.0014706627;
                        }
                    } else {
                        var35 = 0.0072350875;
                    }
                } else {
                    if (input[0] >= -20.0) {
                        var35 = 0.0012364477;
                    } else {
                        var35 = -0.0018214238;
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[0] >= -12.5) {
                    if (input[3] >= -99.895004) {
                        if (input[0] >= -7.5) {
                            var35 = -0.0012728487;
                        } else {
                            var35 = 0.0005534099;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var35 = -0.002517564;
                        } else {
                            var35 = -0.0016085318;
                        }
                    }
                } else {
                    if (input[7] >= 4.4751234) {
                        if (input[2] >= 14.5) {
                            var35 = 0.0006627294;
                        } else {
                            var35 = 0.0036622472;
                        }
                    } else {
                        if (input[1] >= 41.004997) {
                            var35 = -0.0018696593;
                        } else {
                            var35 = 0.0010294629;
                        }
                    }
                }
            } else {
                if (input[2] >= 13.5) {
                    if (input[1] >= 60.875) {
                        if (input[7] >= 9.696852) {
                            var35 = 0.00022137017;
                        } else {
                            var35 = -0.006389609;
                        }
                    } else {
                        if (input[1] >= 60.695) {
                            var35 = 0.013157116;
                        } else {
                            var35 = 0.0023289106;
                        }
                    }
                } else {
                    if (input[1] >= 53.16) {
                        if (input[1] >= 59.795) {
                            var35 = 0.0015572754;
                        } else {
                            var35 = 0.00905489;
                        }
                    } else {
                        if (input[1] >= 47.28) {
                            var35 = -0.0018231921;
                        } else {
                            var35 = 0.007850615;
                        }
                    }
                }
            }
        }
    }
    float var36;
    if (input[0] >= -20.0) {
        if (input[1] >= 37.265) {
            if (input[4] >= -95.0) {
                if (input[3] >= -80.68) {
                    if (input[3] >= -80.665) {
                        if (input[7] >= 9.768033) {
                            var36 = -0.00015989298;
                        } else {
                            var36 = -0.0009555188;
                        }
                    } else {
                        var36 = 0.0025403975;
                    }
                } else {
                    if (input[3] >= -91.795) {
                        if (input[0] >= -7.5) {
                            var36 = -0.0011379544;
                        } else {
                            var36 = -0.0013443286;
                        }
                    } else {
                        if (input[3] >= -91.815) {
                            var36 = -0.00074836775;
                        } else {
                            var36 = -0.001116958;
                        }
                    }
                }
            } else {
                if (input[1] >= 54.735) {
                    if (input[0] >= -7.5) {
                        if (input[3] >= -84.11) {
                            var36 = 0.0001792688;
                        } else {
                            var36 = -0.0011364309;
                        }
                    } else {
                        if (input[1] >= 54.955) {
                            var36 = -0.0016785404;
                        } else {
                            var36 = -0.0027099592;
                        }
                    }
                } else {
                    if (input[7] >= 9.983474) {
                        var36 = -0.0024614304;
                    } else {
                        if (input[1] >= 53.895) {
                            var36 = -0.0007617539;
                        } else {
                            var36 = -0.0011772743;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 37.254997) {
                if (input[4] >= -95.0) {
                    var36 = -0.0010580766;
                } else {
                    if (input[3] >= -97.915) {
                        var36 = -0.0011669053;
                    } else {
                        if (input[7] >= 1.6616166) {
                            var36 = 0.0066804304;
                        } else {
                            var36 = -0.0007532302;
                        }
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    if (input[1] >= 18.025002) {
                        if (input[3] >= -92.435) {
                            var36 = -0.0011062833;
                        } else {
                            var36 = -0.0011496445;
                        }
                    } else {
                        if (input[1] >= 8.305) {
                            var36 = -0.0011744933;
                        } else {
                            var36 = -0.001254314;
                        }
                    }
                } else {
                    if (input[3] >= -80.575) {
                        if (input[7] >= 1.484583) {
                            var36 = -0.00088883657;
                        } else {
                            var36 = 0.0021540846;
                        }
                    } else {
                        if (input[4] >= -95.0) {
                            var36 = -0.0011303559;
                        } else {
                            var36 = -0.0010313558;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[3] >= -90.005005) {
                if (input[4] >= -85.0) {
                    if (input[7] >= 1.5881691) {
                        if (input[7] >= 1.7133136) {
                            var36 = -0.0011583148;
                        } else {
                            var36 = -0.0017812367;
                        }
                    } else {
                        if (input[1] >= 4.6549997) {
                            var36 = -0.0010855042;
                        } else {
                            var36 = 0.0039775777;
                        }
                    }
                } else {
                    if (input[3] >= -86.05) {
                        if (input[7] >= 1.524796) {
                            var36 = -0.0009315246;
                        } else {
                            var36 = 0.0034749582;
                        }
                    } else {
                        if (input[6] >= 3.5) {
                            var36 = 0.00083990546;
                        } else {
                            var36 = -0.0019502938;
                        }
                    }
                }
            } else {
                if (input[3] >= -90.425) {
                    if (input[4] >= -85.0) {
                        var36 = -0.0010864581;
                    } else {
                        var36 = -0.0020282576;
                    }
                } else {
                    if (input[3] >= -90.695) {
                        if (input[3] >= -90.685) {
                            var36 = -0.0005944932;
                        } else {
                            var36 = 0.0032451488;
                        }
                    } else {
                        if (input[1] >= 50.715) {
                            var36 = -0.0012112363;
                        } else {
                            var36 = -0.0011359653;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 37.165) {
                if (input[1] >= 37.205) {
                    if (input[1] >= 61.72) {
                        if (input[7] >= 9.630975) {
                            var36 = 0.0006261549;
                        } else {
                            var36 = -0.0064912634;
                        }
                    } else {
                        if (input[1] >= 60.35) {
                            var36 = 0.0010610563;
                        } else {
                            var36 = -0.00067467766;
                        }
                    }
                } else {
                    if (input[1] >= 37.184998) {
                        var36 = 0.0074894144;
                    } else {
                        if (input[6] >= 3.5) {
                            var36 = 0.0009882193;
                        } else {
                            var36 = -0.0018882673;
                        }
                    }
                }
            } else {
                if (input[1] >= 1.02) {
                    if (input[1] >= 36.225) {
                        if (input[1] >= 36.315002) {
                            var36 = -0.0013823365;
                        } else {
                            var36 = -0.0033876982;
                        }
                    } else {
                        if (input[1] >= 36.11) {
                            var36 = 0.00074454804;
                        } else {
                            var36 = -0.0010075052;
                        }
                    }
                } else {
                    if (input[7] >= 1.607638) {
                        if (input[1] >= 0.83000004) {
                            var36 = 0.0034650785;
                        } else {
                            var36 = -0.0008067616;
                        }
                    } else {
                        var36 = 0.00815492;
                    }
                }
            }
        }
    }
    float var37;
    if (input[2] >= 30.5) {
        if (input[2] >= 40.5) {
            if (input[4] >= -95.0) {
                if (input[5] >= -2.3449998) {
                    if (input[2] >= 100.5) {
                        if (input[3] >= -84.384995) {
                            var37 = -0.0011104321;
                        } else {
                            var37 = -0.0012723658;
                        }
                    } else {
                        if (input[7] >= 9.983108) {
                            var37 = -0.00008524953;
                        } else {
                            var37 = -0.0010239059;
                        }
                    }
                } else {
                    if (input[2] >= 75.5) {
                        if (input[3] >= -82.354996) {
                            var37 = -0.000026792195;
                        } else {
                            var37 = -0.0009906943;
                        }
                    } else {
                        if (input[3] >= -99.985) {
                            var37 = -0.0010247956;
                        } else {
                            var37 = -0.0010090569;
                        }
                    }
                }
            } else {
                if (input[3] >= -99.965) {
                    if (input[2] >= 92.5) {
                        if (input[3] >= -92.385) {
                            var37 = -0.0010978119;
                        } else {
                            var37 = -0.0012533151;
                        }
                    } else {
                        if (input[7] >= 9.962504) {
                            var37 = -0.00081981247;
                        } else {
                            var37 = -0.0010350305;
                        }
                    }
                } else {
                    if (input[2] >= 53.5) {
                        if (input[2] >= 90.5) {
                            var37 = -0.0014178642;
                        } else {
                            var37 = -0.0012339114;
                        }
                    } else {
                        if (input[7] >= 4.7889633) {
                            var37 = -0.0010781469;
                        } else {
                            var37 = -0.00088440423;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= 1.545) {
                if (input[3] >= -95.835) {
                    if (input[5] >= 8.455) {
                        if (input[5] >= 8.67) {
                            var37 = -0.0008039111;
                        } else {
                            var37 = -0.0026004307;
                        }
                    } else {
                        if (input[3] >= -74.009995) {
                            var37 = -0.001792446;
                        } else {
                            var37 = -0.00047816895;
                        }
                    }
                } else {
                    if (input[7] >= 4.93114) {
                        if (input[3] >= -97.92) {
                            var37 = -0.0008795851;
                        } else {
                            var37 = 0.00018268003;
                        }
                    } else {
                        if (input[7] >= 1.576096) {
                            var37 = -0.0016049773;
                        } else {
                            var37 = -0.00029901683;
                        }
                    }
                }
            } else {
                if (input[5] >= 1.515) {
                    if (input[2] >= 35.5) {
                        var37 = -0.0015215803;
                    } else {
                        var37 = -0.006295718;
                    }
                } else {
                    if (input[5] >= -1.665) {
                        if (input[7] >= 1.521119) {
                            var37 = -0.000884084;
                        } else {
                            var37 = -0.0019864948;
                        }
                    } else {
                        if (input[3] >= -81.854996) {
                            var37 = -0.002314266;
                        } else {
                            var37 = -0.0010302053;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[5] >= -1.085) {
                if (input[3] >= -66.925) {
                    if (input[2] >= 29.5) {
                        if (input[4] >= -85.0) {
                            var37 = -0.0015515962;
                        } else {
                            var37 = 0.0031597398;
                        }
                    } else {
                        if (input[7] >= 9.909607) {
                            var37 = 0.00034073045;
                        } else {
                            var37 = -0.0023454144;
                        }
                    }
                } else {
                    if (input[3] >= -71.03) {
                        if (input[7] >= 1.803551) {
                            var37 = 0.0025702014;
                        } else {
                            var37 = -0.001009183;
                        }
                    } else {
                        if (input[3] >= -72.56) {
                            var37 = -0.00250315;
                        } else {
                            var37 = -0.0006787055;
                        }
                    }
                }
            } else {
                if (input[5] >= -3.725) {
                    if (input[7] >= 9.964879) {
                        var37 = 0.0020060434;
                    } else {
                        if (input[7] >= 9.711752) {
                            var37 = -0.0013006731;
                        } else {
                            var37 = -0.00087154144;
                        }
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[3] >= -85.755005) {
                            var37 = -0.001128191;
                        } else {
                            var37 = -0.0010272315;
                        }
                    } else {
                        if (input[3] >= -99.994995) {
                            var37 = -0.0009939424;
                        } else {
                            var37 = -0.0011079584;
                        }
                    }
                }
            }
        } else {
            if (input[3] >= -99.205) {
                if (input[7] >= 9.634466) {
                    if (input[3] >= -97.075) {
                        if (input[3] >= -74.495) {
                            var37 = 0.002987374;
                        } else {
                            var37 = -0.0006481045;
                        }
                    } else {
                        if (input[3] >= -97.14) {
                            var37 = 0.0087506445;
                        } else {
                            var37 = 0.0005535506;
                        }
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[7] >= 9.551619) {
                            var37 = -0.001972923;
                        } else {
                            var37 = -0.00094190374;
                        }
                    } else {
                        if (input[7] >= 1.5363005) {
                            var37 = -0.0005908123;
                        } else {
                            var37 = -0.0011382638;
                        }
                    }
                }
            } else {
                if (input[2] >= 10.5) {
                    if (input[7] >= 4.8996363) {
                        if (input[2] >= 24.5) {
                            var37 = -0.00039853188;
                        } else {
                            var37 = 0.00088132033;
                        }
                    } else {
                        if (input[7] >= 1.5077465) {
                            var37 = -0.00038865194;
                        } else {
                            var37 = -0.0021777507;
                        }
                    }
                } else {
                    if (input[2] >= 4.5) {
                        if (input[7] >= 1.4702945) {
                            var37 = 0.0024192056;
                        } else {
                            var37 = -0.0037636783;
                        }
                    } else {
                        var37 = 0.010499227;
                    }
                }
            }
        }
    }
    float var38;
    if (input[2] >= 27.5) {
        if (input[2] >= 40.5) {
            if (input[5] >= -2.3649998) {
                if (input[3] >= -99.055) {
                    if (input[2] >= 85.5) {
                        if (input[1] >= 14.075) {
                            var38 = -0.0009571221;
                        } else {
                            var38 = -0.0010804691;
                        }
                    } else {
                        if (input[1] >= 18.525002) {
                            var38 = -0.0009459424;
                        } else {
                            var38 = -0.0007799731;
                        }
                    }
                } else {
                    if (input[2] >= 55.5) {
                        if (input[1] >= 9.504999) {
                            var38 = -0.0011538159;
                        } else {
                            var38 = 0.0013284063;
                        }
                    } else {
                        if (input[1] >= 32.345) {
                            var38 = -0.0009535832;
                        } else {
                            var38 = -0.000074542746;
                        }
                    }
                }
            } else {
                if (input[2] >= 75.5) {
                    if (input[1] >= 3.5700002) {
                        var38 = -0.0008915813;
                    } else {
                        if (input[2] >= 99.0) {
                            var38 = -0.00040717173;
                        } else {
                            var38 = 0.0011498438;
                        }
                    }
                } else {
                    if (input[1] >= 15.475) {
                        if (input[5] >= -2.4050002) {
                            var38 = -0.00062476745;
                        } else {
                            var38 = -0.00091155356;
                        }
                    } else {
                        if (input[2] >= 45.5) {
                            var38 = -0.0010043235;
                        } else {
                            var38 = -0.0013699388;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 39.035) {
                if (input[5] >= -2.065) {
                    if (input[2] >= 33.5) {
                        if (input[1] >= 53.870003) {
                            var38 = -0.0014413912;
                        } else {
                            var38 = -0.00084383687;
                        }
                    } else {
                        if (input[1] >= 45.755) {
                            var38 = -0.0011954111;
                        } else {
                            var38 = -0.0018119066;
                        }
                    }
                } else {
                    if (input[2] >= 35.5) {
                        if (input[2] >= 37.5) {
                            var38 = -0.00089451467;
                        } else {
                            var38 = -0.00086178334;
                        }
                    } else {
                        if (input[2] >= 31.5) {
                            var38 = -0.0009360003;
                        } else {
                            var38 = -0.00088425365;
                        }
                    }
                }
            } else {
                if (input[5] >= -3.0549998) {
                    if (input[3] >= -99.955) {
                        if (input[1] >= 13.485001) {
                            var38 = -0.0007125347;
                        } else {
                            var38 = -0.00010680593;
                        }
                    } else {
                        if (input[7] >= 4.499542) {
                            var38 = 0.00057675247;
                        } else {
                            var38 = -0.00063051464;
                        }
                    }
                } else {
                    if (input[1] >= 13.275) {
                        if (input[3] >= -83.215) {
                            var38 = -0.00020646378;
                        } else {
                            var38 = -0.0009740763;
                        }
                    } else {
                        if (input[3] >= -90.009995) {
                            var38 = -0.0016764591;
                        } else {
                            var38 = -0.0011130174;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -0.215) {
            if (input[3] >= -98.505005) {
                if (input[1] >= 25.61) {
                    if (input[7] >= 9.981134) {
                        if (input[7] >= 9.981735) {
                            var38 = -0.000617575;
                        } else {
                            var38 = 0.0056442055;
                        }
                    } else {
                        if (input[2] >= 22.5) {
                            var38 = -0.0009911113;
                        } else {
                            var38 = -0.00066843024;
                        }
                    }
                } else {
                    if (input[3] >= -94.89) {
                        if (input[7] >= 9.600763) {
                            var38 = 0.0014759869;
                        } else {
                            var38 = -0.000501456;
                        }
                    } else {
                        if (input[7] >= 4.513236) {
                            var38 = 0.0150185665;
                        } else {
                            var38 = -0.00062154856;
                        }
                    }
                }
            } else {
                if (input[1] >= 50.25) {
                    if (input[2] >= 17.5) {
                        if (input[1] >= 50.39) {
                            var38 = -0.0011171239;
                        } else {
                            var38 = -0.004792199;
                        }
                    } else {
                        if (input[1] >= 61.3) {
                            var38 = -0.0034802835;
                        } else {
                            var38 = 0.000641338;
                        }
                    }
                } else {
                    if (input[7] >= 1.5832396) {
                        if (input[7] >= 1.5943615) {
                            var38 = 0.0005034729;
                        } else {
                            var38 = 0.0060929577;
                        }
                    } else {
                        if (input[1] >= 35.4) {
                            var38 = -0.0012626502;
                        } else {
                            var38 = 0.0017813354;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 5.56) {
                if (input[5] >= -0.485) {
                    if (input[2] >= 15.5) {
                        if (input[3] >= -90.34) {
                            var38 = -0.0012903626;
                        } else {
                            var38 = -0.0019587537;
                        }
                    } else {
                        var38 = 0.0007665711;
                    }
                } else {
                    if (input[5] >= -0.78499997) {
                        if (input[7] >= 4.492919) {
                            var38 = -0.00078696414;
                        } else {
                            var38 = 0.0024377503;
                        }
                    } else {
                        if (input[3] >= -99.955) {
                            var38 = -0.00090245384;
                        } else {
                            var38 = -0.0009596458;
                        }
                    }
                }
            } else {
                if (input[3] >= -91.3) {
                    var38 = 0.0052796216;
                } else {
                    var38 = -0.0016299774;
                }
            }
        }
    }
    float var39;
    if (input[2] >= 32.5) {
        if (input[5] >= -0.17500001) {
            if (input[0] >= -12.5) {
                if (input[3] >= -99.905) {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 75.5) {
                            var39 = -0.00075942354;
                        } else {
                            var39 = -0.0008723669;
                        }
                    } else {
                        if (input[2] >= 41.5) {
                            var39 = -0.00095141;
                        } else {
                            var39 = -0.00031194187;
                        }
                    }
                } else {
                    if (input[2] >= 45.5) {
                        if (input[0] >= -7.5) {
                            var39 = -0.00056777406;
                        } else {
                            var39 = -0.0007432586;
                        }
                    } else {
                        if (input[1] >= 25.689999) {
                            var39 = -0.00089038786;
                        } else {
                            var39 = -0.0028211188;
                        }
                    }
                }
            } else {
                if (input[2] >= 58.5) {
                    if (input[1] >= 31.075) {
                        if (input[0] >= -20.0) {
                            var39 = -0.001055105;
                        } else {
                            var39 = -0.0015427917;
                        }
                    } else {
                        if (input[2] >= 83.5) {
                            var39 = -0.0012482135;
                        } else {
                            var39 = -0.0006942259;
                        }
                    }
                } else {
                    if (input[1] >= 26.59) {
                        if (input[1] >= 49.254997) {
                            var39 = -0.0014465012;
                        } else {
                            var39 = -0.0007134111;
                        }
                    } else {
                        if (input[3] >= -82.955) {
                            var39 = 0.0015045848;
                        } else {
                            var39 = 0.00005784367;
                        }
                    }
                }
            }
        } else {
            if (input[3] >= -80.335) {
                if (input[1] >= 12.735001) {
                    if (input[2] >= 39.0) {
                        var39 = -0.0008494255;
                    } else {
                        if (input[1] >= 28.455) {
                            var39 = -0.00075407047;
                        } else {
                            var39 = 0.0025634964;
                        }
                    }
                } else {
                    if (input[2] >= 90.5) {
                        if (input[0] >= -12.5) {
                            var39 = -0.00073228474;
                        } else {
                            var39 = 0.0025774352;
                        }
                    } else {
                        var39 = 0.0049060564;
                    }
                }
            } else {
                if (input[2] >= 35.5) {
                    if (input[1] >= 6.04) {
                        if (input[5] >= -1.355) {
                            var39 = -0.000882765;
                        } else {
                            var39 = -0.00081566116;
                        }
                    } else {
                        if (input[3] >= -80.96001) {
                            var39 = 0.0022778062;
                        } else {
                            var39 = -0.00069899805;
                        }
                    }
                } else {
                    if (input[5] >= -0.255) {
                        if (input[0] >= -20.0) {
                            var39 = 0.002855478;
                        } else {
                            var39 = -0.0010118656;
                        }
                    } else {
                        if (input[5] >= -0.56) {
                            var39 = -0.002097288;
                        } else {
                            var39 = -0.0008558267;
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] >= -20.0) {
            if (input[1] >= 30.445) {
                if (input[0] >= -12.5) {
                    if (input[5] >= -0.56) {
                        if (input[5] >= 0.445) {
                            var39 = -0.00077807996;
                        } else {
                            var39 = -0.001469284;
                        }
                    } else {
                        if (input[5] >= -0.6) {
                            var39 = 0.0009266321;
                        } else {
                            var39 = -0.0007959975;
                        }
                    }
                } else {
                    if (input[5] >= 0.005) {
                        if (input[2] >= 19.5) {
                            var39 = -0.00031530412;
                        } else {
                            var39 = 0.0055889715;
                        }
                    } else {
                        if (input[2] >= 16.5) {
                            var39 = -0.0008723844;
                        } else {
                            var39 = -0.00021459154;
                        }
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    if (input[1] >= 18.04) {
                        if (input[0] >= -2.5) {
                            var39 = -0.00094925304;
                        } else {
                            var39 = -0.0005886259;
                        }
                    } else {
                        if (input[5] >= 29.725) {
                            var39 = -0.0021254192;
                        } else {
                            var39 = -0.0011705592;
                        }
                    }
                } else {
                    if (input[5] >= -2.97) {
                        if (input[2] >= 23.5) {
                            var39 = 0.00061608286;
                        } else {
                            var39 = 0.005444887;
                        }
                    } else {
                        if (input[1] >= 12.995) {
                            var39 = -0.0009285856;
                        } else {
                            var39 = -0.0016116578;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.625) {
                if (input[2] >= 17.5) {
                    if (input[1] >= 50.434998) {
                        if (input[7] >= 4.58891) {
                            var39 = 0.000023083723;
                        } else {
                            var39 = -0.002270132;
                        }
                    } else {
                        if (input[7] >= 1.4930475) {
                            var39 = 0.0015899917;
                        } else {
                            var39 = -0.0048849415;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        if (input[1] >= 58.385002) {
                            var39 = -0.0019400325;
                        } else {
                            var39 = 0.0035762023;
                        }
                    } else {
                        if (input[7] >= 1.5953159) {
                            var39 = 0.0097174905;
                        } else {
                            var39 = 0.0017549575;
                        }
                    }
                }
            } else {
                if (input[2] >= 9.5) {
                    if (input[2] >= 20.5) {
                        if (input[3] >= -92.759995) {
                            var39 = -0.0014518871;
                        } else {
                            var39 = -0.00086923764;
                        }
                    } else {
                        var39 = -0.0010286089;
                    }
                } else {
                    if (input[1] >= 58.98) {
                        var39 = -0.0008449019;
                    } else {
                        var39 = -0.0025792017;
                    }
                }
            }
        }
    }
    float var40;
    if (input[2] >= 34.5) {
        if (input[5] >= -2.1750002) {
            if (input[0] >= -12.5) {
                if (input[3] >= -99.765) {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 78.5) {
                            var40 = -0.00067996496;
                        } else {
                            var40 = -0.00077882083;
                        }
                    } else {
                        if (input[2] >= 40.5) {
                            var40 = -0.00085618783;
                        } else {
                            var40 = -0.00037831764;
                        }
                    }
                } else {
                    if (input[2] >= 46.5) {
                        if (input[0] >= -7.5) {
                            var40 = -0.0005109112;
                        } else {
                            var40 = -0.00066551234;
                        }
                    } else {
                        if (input[1] >= 25.439999) {
                            var40 = -0.0008128265;
                        } else {
                            var40 = -0.003497952;
                        }
                    }
                }
            } else {
                if (input[2] >= 65.5) {
                    if (input[2] >= 97.5) {
                        if (input[6] >= 3.5) {
                            var40 = -0.0012405223;
                        } else {
                            var40 = -0.0010837679;
                        }
                    } else {
                        if (input[1] >= 25.675) {
                            var40 = -0.0011242401;
                        } else {
                            var40 = -0.0007639249;
                        }
                    }
                } else {
                    if (input[1] >= 24.65) {
                        if (input[1] >= 43.105) {
                            var40 = -0.0010227549;
                        } else {
                            var40 = -0.00063047704;
                        }
                    } else {
                        if (input[3] >= -82.015) {
                            var40 = 0.00085746584;
                        } else {
                            var40 = -0.000007543558;
                        }
                    }
                }
            }
        } else {
            if (input[2] >= 75.5) {
                if (input[1] >= 3.5700002) {
                    if (input[0] >= -12.5) {
                        var40 = -0.0007326967;
                    } else {
                        if (input[5] >= -3.02) {
                            var40 = -0.00082185643;
                        } else {
                            var40 = -0.00070905825;
                        }
                    }
                } else {
                    if (input[2] >= 99.0) {
                        var40 = -0.00035186321;
                    } else {
                        var40 = 0.0011273016;
                    }
                }
            } else {
                if (input[1] >= 15.415) {
                    if (input[1] >= 22.78) {
                        if (input[2] >= 35.5) {
                            var40 = -0.0007347199;
                        } else {
                            var40 = -0.00077391125;
                        }
                    } else {
                        if (input[5] >= -2.605) {
                            var40 = -0.00040167375;
                        } else {
                            var40 = -0.0007825791;
                        }
                    }
                } else {
                    if (input[3] >= -82.259995) {
                        if (input[1] >= 8.115) {
                            var40 = 0.0013303576;
                        } else {
                            var40 = -0.00070059096;
                        }
                    } else {
                        if (input[2] >= 58.5) {
                            var40 = -0.0008175687;
                        } else {
                            var40 = -0.0010205199;
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] >= -12.5) {
            if (input[3] >= -99.165) {
                if (input[0] >= -7.5) {
                    if (input[1] >= 9.385) {
                        if (input[1] >= 9.514999) {
                            var40 = -0.00075437705;
                        } else {
                            var40 = 0.002702071;
                        }
                    } else {
                        if (input[6] >= 7.5) {
                            var40 = -0.0020076025;
                        } else {
                            var40 = -0.0014549553;
                        }
                    }
                } else {
                    if (input[5] >= 1.19) {
                        if (input[1] >= 4.485) {
                            var40 = 0.0000011063225;
                        } else {
                            var40 = 0.0034013966;
                        }
                    } else {
                        if (input[3] >= -79.535) {
                            var40 = 0.0038721994;
                        } else {
                            var40 = -0.0007703485;
                        }
                    }
                }
            } else {
                if (input[5] >= -4.585) {
                    if (input[2] >= 23.5) {
                        if (input[1] >= 50.045) {
                            var40 = -0.0006495823;
                        } else {
                            var40 = -0.0011798725;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var40 = -0.0020448978;
                        } else {
                            var40 = -0.0011330672;
                        }
                    }
                } else {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 20.5) {
                            var40 = -0.0006867979;
                        } else {
                            var40 = -0.0006410001;
                        }
                    } else {
                        if (input[2] >= 20.5) {
                            var40 = -0.0007543311;
                        } else {
                            var40 = -0.0007189042;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.815) {
                if (input[2] >= 20.5) {
                    if (input[1] >= 35.555) {
                        if (input[0] >= -20.0) {
                            var40 = -0.0012269014;
                        } else {
                            var40 = -0.00016465268;
                        }
                    } else {
                        if (input[1] >= 20.03) {
                            var40 = 0.0008387775;
                        } else {
                            var40 = 0.0020865265;
                        }
                    }
                } else {
                    if (input[1] >= 43.730003) {
                        if (input[0] >= -20.0) {
                            var40 = -0.00004857599;
                        } else {
                            var40 = 0.002249313;
                        }
                    } else {
                        if (input[1] >= 37.730003) {
                            var40 = 0.0026878677;
                        } else {
                            var40 = 0.0054421886;
                        }
                    }
                }
            } else {
                if (input[3] >= -90.515) {
                    if (input[3] >= -87.225) {
                        var40 = -0.0019286752;
                    } else {
                        var40 = -0.0013377154;
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[1] >= 43.705) {
                            var40 = -0.0007149658;
                        } else {
                            var40 = -0.00082960835;
                        }
                    } else {
                        if (input[1] >= 13.514999) {
                            var40 = -0.00092296273;
                        } else {
                            var40 = 0.0010475985;
                        }
                    }
                }
            }
        }
    }
    float var41;
    if (input[2] >= 28.5) {
        if (input[4] >= -95.0) {
            if (input[2] >= 39.5) {
                if (input[5] >= -2.3449998) {
                    if (input[2] >= 100.5) {
                        if (input[0] >= -7.5) {
                            var41 = -0.0006094006;
                        } else {
                            var41 = -0.0009930573;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var41 = -0.0006949287;
                        } else {
                            var41 = -0.00039529856;
                        }
                    }
                } else {
                    if (input[2] >= 75.5) {
                        if (input[3] >= -82.354996) {
                            var41 = -0.000037745704;
                        } else {
                            var41 = -0.00064908015;
                        }
                    } else {
                        if (input[3] >= -99.985) {
                            var41 = -0.00067356223;
                        } else {
                            var41 = -0.0006619802;
                        }
                    }
                }
            } else {
                if (input[5] >= -0.48000002) {
                    if (input[0] >= -7.5) {
                        if (input[5] >= 9.924999) {
                            var41 = -0.0011460799;
                        } else {
                            var41 = -0.00063055044;
                        }
                    } else {
                        if (input[0] >= -12.5) {
                            var41 = 0.00036456154;
                        } else {
                            var41 = 0.0018034077;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[5] >= -0.555) {
                            var41 = -0.0013407399;
                        } else {
                            var41 = -0.00065473205;
                        }
                    } else {
                        if (input[5] >= -2.6100001) {
                            var41 = 0.0014561093;
                        } else {
                            var41 = -0.00075060746;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[2] >= 44.5) {
                    if (input[3] >= -99.265) {
                        if (input[0] >= -7.5) {
                            var41 = -0.0006393149;
                        } else {
                            var41 = -0.00075299974;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var41 = -0.00048122366;
                        } else {
                            var41 = -0.00061393686;
                        }
                    }
                } else {
                    if (input[3] >= -55.43) {
                        var41 = -0.0020240222;
                    } else {
                        if (input[3] >= -94.445) {
                            var41 = -0.00064628234;
                        } else {
                            var41 = -0.00078634016;
                        }
                    }
                }
            } else {
                if (input[2] >= 51.5) {
                    if (input[0] >= -20.0) {
                        if (input[2] >= 103.5) {
                            var41 = -0.0009734323;
                        } else {
                            var41 = -0.0007753601;
                        }
                    } else {
                        if (input[2] >= 81.5) {
                            var41 = -0.0011793687;
                        } else {
                            var41 = -0.0009235392;
                        }
                    }
                } else {
                    if (input[7] >= 1.5129111) {
                        if (input[3] >= -98.015) {
                            var41 = 0.00025809114;
                        } else {
                            var41 = -0.00058696297;
                        }
                    } else {
                        if (input[2] >= 36.5) {
                            var41 = -0.0012008921;
                        } else {
                            var41 = -0.0048071225;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[0] >= -12.5) {
                if (input[5] >= 4.5) {
                    if (input[2] >= 26.5) {
                        if (input[3] >= -84.94) {
                            var41 = -0.0014152053;
                        } else {
                            var41 = 0.0003899276;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var41 = -0.00069417607;
                        } else {
                            var41 = 0.001257967;
                        }
                    }
                } else {
                    if (input[5] >= 3.81) {
                        if (input[0] >= -7.5) {
                            var41 = -0.00019420544;
                        } else {
                            var41 = 0.0034170863;
                        }
                    } else {
                        if (input[5] >= 3.725) {
                            var41 = -0.0023779215;
                        } else {
                            var41 = -0.0006312835;
                        }
                    }
                }
            } else {
                if (input[5] >= -3.02) {
                    if (input[3] >= -90.425) {
                        if (input[5] >= 2.285) {
                            var41 = 0.002589052;
                        } else {
                            var41 = -0.002651461;
                        }
                    } else {
                        if (input[7] >= 4.7366467) {
                            var41 = 0.0014405658;
                        } else {
                            var41 = 0.0066692582;
                        }
                    }
                } else {
                    if (input[2] >= 20.5) {
                        if (input[3] >= -90.354996) {
                            var41 = -0.0016349392;
                        } else {
                            var41 = -0.0006845949;
                        }
                    } else {
                        if (input[2] >= 9.5) {
                            var41 = -0.0008167647;
                        } else {
                            var41 = -0.0011779381;
                        }
                    }
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[0] >= -12.5) {
                    if (input[3] >= -99.895004) {
                        if (input[0] >= -7.5) {
                            var41 = -0.000751597;
                        } else {
                            var41 = 0.00026202123;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var41 = -0.0016782118;
                        } else {
                            var41 = -0.0010303915;
                        }
                    }
                } else {
                    if (input[3] >= -90.23) {
                        if (input[3] >= -88.22) {
                            var41 = 0.004210978;
                        } else {
                            var41 = 0.009215627;
                        }
                    } else {
                        if (input[7] >= 4.6680613) {
                            var41 = 0.0008779931;
                        } else {
                            var41 = -0.00047936506;
                        }
                    }
                }
            } else {
                if (input[2] >= 14.5) {
                    if (input[7] >= 1.4942205) {
                        if (input[7] >= 1.8735249) {
                            var41 = 0.0013655407;
                        } else {
                            var41 = 0.0026857283;
                        }
                    } else {
                        if (input[2] >= 20.5) {
                            var41 = -0.001263766;
                        } else {
                            var41 = -0.0038652958;
                        }
                    }
                } else {
                    if (input[7] >= 1.557668) {
                        if (input[7] >= 9.90093) {
                            var41 = -0.000023044795;
                        } else {
                            var41 = 0.0054294546;
                        }
                    } else {
                        if (input[2] >= 11.0) {
                            var41 = -0.009269798;
                        } else {
                            var41 = 0.0030515045;
                        }
                    }
                }
            }
        }
    }
    float var42;
    if (input[2] >= 29.5) {
        if (input[2] >= 65.5) {
            if (input[4] >= -95.0) {
                if (input[3] >= -92.274994) {
                    if (input[4] >= -85.0) {
                        if (input[1] >= 1.015) {
                            var42 = -0.0006004857;
                        } else {
                            var42 = -0.0009471585;
                        }
                    } else {
                        if (input[2] >= 103.5) {
                            var42 = -0.00072038325;
                        } else {
                            var42 = -0.0006445194;
                        }
                    }
                } else {
                    if (input[2] >= 75.5) {
                        if (input[3] >= -99.985) {
                            var42 = -0.00058878644;
                        } else {
                            var42 = -0.00057657674;
                        }
                    } else {
                        if (input[1] >= 15.76) {
                            var42 = -0.0005903598;
                        } else {
                            var42 = -0.0006521168;
                        }
                    }
                }
            } else {
                if (input[3] >= -99.965) {
                    if (input[1] >= 4.725) {
                        if (input[3] >= -90.705) {
                            var42 = -0.0006056964;
                        } else {
                            var42 = -0.00067135337;
                        }
                    } else {
                        if (input[3] >= -70.325) {
                            var42 = -0.000706547;
                        } else {
                            var42 = -0.0011049572;
                        }
                    }
                } else {
                    if (input[7] >= 4.6011896) {
                        if (input[2] >= 101.5) {
                            var42 = -0.0010141822;
                        } else {
                            var42 = -0.0008035569;
                        }
                    } else {
                        if (input[7] >= 4.5957766) {
                            var42 = 0.0006538543;
                        } else {
                            var42 = -0.0007104738;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 21.965) {
                if (input[1] >= 39.145) {
                    if (input[4] >= -95.0) {
                        if (input[2] >= 35.5) {
                            var42 = -0.0005924262;
                        } else {
                            var42 = -0.00061620615;
                        }
                    } else {
                        if (input[2] >= 33.5) {
                            var42 = -0.0006694619;
                        } else {
                            var42 = -0.0010122786;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[1] >= 22.355) {
                            var42 = -0.0006055206;
                        } else {
                            var42 = -0.0007358819;
                        }
                    } else {
                        if (input[3] >= -99.975006) {
                            var42 = -0.00062475406;
                        } else {
                            var42 = -0.00036538328;
                        }
                    }
                }
            } else {
                if (input[4] >= -85.0) {
                    if (input[3] >= -58.72) {
                        if (input[2] >= 51.5) {
                            var42 = -0.0006355861;
                        } else {
                            var42 = -0.0017000657;
                        }
                    } else {
                        if (input[3] >= -59.059998) {
                            var42 = 0.0046537365;
                        } else {
                            var42 = -0.00067653874;
                        }
                    }
                } else {
                    if (input[3] >= -77.785) {
                        if (input[3] >= -77.270004) {
                            var42 = -0.00058394135;
                        } else {
                            var42 = -0.0015399476;
                        }
                    } else {
                        if (input[1] >= 10.765) {
                            var42 = -0.00029114794;
                        } else {
                            var42 = 0.0005136646;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 7.665) {
                if (input[1] >= 9.415) {
                    if (input[1] >= 19.82) {
                        if (input[3] >= -99.075) {
                            var42 = -0.0005752232;
                        } else {
                            var42 = -0.0006262403;
                        }
                    } else {
                        if (input[1] >= 19.075) {
                            var42 = 0.00057369313;
                        } else {
                            var42 = -0.00048209075;
                        }
                    }
                } else {
                    if (input[7] >= 1.9273784) {
                        if (input[3] >= -76.130005) {
                            var42 = -0.0014540845;
                        } else {
                            var42 = -0.0027301137;
                        }
                    } else {
                        if (input[1] >= 8.595) {
                            var42 = 0.0021059324;
                        } else {
                            var42 = -0.0010031874;
                        }
                    }
                }
            } else {
                if (input[3] >= -72.825) {
                    if (input[3] >= -71.62) {
                        if (input[3] >= -66.905) {
                            var42 = -0.0016088303;
                        } else {
                            var42 = 0.0023725275;
                        }
                    } else {
                        if (input[1] >= 5.13) {
                            var42 = -0.0019731293;
                        } else {
                            var42 = -0.006631352;
                        }
                    }
                } else {
                    if (input[7] >= 4.6354322) {
                        if (input[1] >= 7.2) {
                            var42 = 0.004856748;
                        } else {
                            var42 = -0.00037214963;
                        }
                    } else {
                        if (input[7] >= 1.621261) {
                            var42 = 0.0074211434;
                        } else {
                            var42 = 0.00034746763;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 54.835) {
                if (input[2] >= 14.5) {
                    if (input[2] >= 18.5) {
                        if (input[1] >= 54.845) {
                            var42 = -0.00089020695;
                        } else {
                            var42 = -0.009656302;
                        }
                    } else {
                        if (input[7] >= 1.5165055) {
                            var42 = -0.0033080874;
                        } else {
                            var42 = 0.009204186;
                        }
                    }
                } else {
                    if (input[7] >= 1.867216) {
                        if (input[1] >= 56.79) {
                            var42 = 0.0021383485;
                        } else {
                            var42 = 0.00010627087;
                        }
                    } else {
                        if (input[1] >= 59.050003) {
                            var42 = 0.00055058737;
                        } else {
                            var42 = -0.0025977034;
                        }
                    }
                }
            } else {
                if (input[3] >= -97.104996) {
                    if (input[1] >= 2.245) {
                        if (input[1] >= 34.525) {
                            var42 = -0.00055240234;
                        } else {
                            var42 = -0.0002238468;
                        }
                    } else {
                        if (input[3] >= -54.53) {
                            var42 = -0.0010949441;
                        } else {
                            var42 = 0.005298688;
                        }
                    }
                } else {
                    if (input[2] >= 8.5) {
                        if (input[1] >= 29.07) {
                            var42 = 0.00009061156;
                        } else {
                            var42 = 0.0016570737;
                        }
                    } else {
                        if (input[7] >= 4.434096) {
                            var42 = 0.007441947;
                        } else {
                            var42 = 0.002412594;
                        }
                    }
                }
            }
        }
    }
    float var43;
    if (input[2] >= 28.5) {
        if (input[2] >= 47.5) {
            if (input[0] >= -7.5) {
                if (input[2] >= 78.5) {
                    if (input[4] >= -95.0) {
                        if (input[5] >= -2.275) {
                            var43 = -0.0005006929;
                        } else {
                            var43 = -0.00053544936;
                        }
                    } else {
                        if (input[5] >= 0.02) {
                            var43 = -0.00046435348;
                        } else {
                            var43 = -0.00015940673;
                        }
                    }
                } else {
                    if (input[1] >= 21.915) {
                        if (input[4] >= -95.0) {
                            var43 = -0.00054277823;
                        } else {
                            var43 = -0.00049660145;
                        }
                    } else {
                        if (input[2] >= 61.5) {
                            var43 = -0.00060635945;
                        } else {
                            var43 = -0.000707082;
                        }
                    }
                }
            } else {
                if (input[5] >= -2.335) {
                    if (input[1] >= 40.585) {
                        if (input[0] >= -20.0) {
                            var43 = -0.000677663;
                        } else {
                            var43 = -0.0011527602;
                        }
                    } else {
                        if (input[2] >= 66.5) {
                            var43 = -0.0007128939;
                        } else {
                            var43 = -0.000408398;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[5] >= -2.3850002) {
                            var43 = -0.00013511455;
                        } else {
                            var43 = -0.00053759705;
                        }
                    } else {
                        if (input[1] >= 16.78) {
                            var43 = -0.00051143614;
                        } else {
                            var43 = -0.0005451481;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 26.724998) {
                if (input[2] >= 31.5) {
                    if (input[1] >= 58.475) {
                        if (input[0] >= -20.0) {
                            var43 = -0.0005370442;
                        } else {
                            var43 = -0.0017642025;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var43 = -0.0005446159;
                        } else {
                            var43 = -0.000455509;
                        }
                    }
                } else {
                    if (input[5] >= -1.705) {
                        if (input[7] >= 4.8779826) {
                            var43 = -0.00048000226;
                        } else {
                            var43 = -0.001037706;
                        }
                    } else {
                        if (input[5] >= -1.725) {
                            var43 = 0.0014964051;
                        } else {
                            var43 = -0.00052749476;
                        }
                    }
                }
            } else {
                if (input[0] >= -7.5) {
                    if (input[1] >= 18.015) {
                        if (input[0] >= -2.5) {
                            var43 = -0.00072723615;
                        } else {
                            var43 = -0.0003971675;
                        }
                    } else {
                        if (input[7] >= 9.598595) {
                            var43 = -0.000496099;
                        } else {
                            var43 = -0.0009997494;
                        }
                    }
                } else {
                    if (input[5] >= -1.485) {
                        if (input[1] >= 25.785) {
                            var43 = 0.0023928732;
                        } else {
                            var43 = 0.00042227306;
                        }
                    } else {
                        if (input[5] >= -1.535) {
                            var43 = -0.0023176644;
                        } else {
                            var43 = -0.0006715033;
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] >= -20.0) {
            if (input[0] >= -12.5) {
                if (input[4] >= -95.0) {
                    if (input[5] >= 18.635) {
                        if (input[2] >= 27.5) {
                            var43 = -0.0009344378;
                        } else {
                            var43 = -0.001925893;
                        }
                    } else {
                        if (input[1] >= 7.05) {
                            var43 = -0.0005134325;
                        } else {
                            var43 = 0.0070773484;
                        }
                    }
                } else {
                    if (input[5] >= 0.29000002) {
                        if (input[0] >= -7.5) {
                            var43 = -0.0006434335;
                        } else {
                            var43 = 0.00015138874;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var43 = -0.0015023368;
                        } else {
                            var43 = -0.0009305994;
                        }
                    }
                }
            } else {
                if (input[5] >= 0.005) {
                    if (input[7] >= 9.602751) {
                        if (input[1] >= 37.09) {
                            var43 = -0.00000063687565;
                        } else {
                            var43 = 0.004540211;
                        }
                    } else {
                        if (input[7] >= 4.9566317) {
                            var43 = -0.003116237;
                        } else {
                            var43 = 0.0017862747;
                        }
                    }
                } else {
                    if (input[5] >= -3.0349998) {
                        if (input[7] >= 4.921468) {
                            var43 = 0.0008150555;
                        } else {
                            var43 = -0.0006590361;
                        }
                    } else {
                        if (input[1] >= 11.9) {
                            var43 = -0.00058424333;
                        } else {
                            var43 = -0.002452602;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -1.285) {
                if (input[2] >= 16.5) {
                    if (input[1] >= 51.6) {
                        if (input[7] >= 9.639772) {
                            var43 = 0.0015681526;
                        } else {
                            var43 = -0.0016133108;
                        }
                    } else {
                        if (input[1] >= 31.599998) {
                            var43 = 0.0012658187;
                        } else {
                            var43 = 0.0033225052;
                        }
                    }
                } else {
                    if (input[1] >= 46.34) {
                        if (input[1] >= 53.44) {
                            var43 = 0.00426352;
                        } else {
                            var43 = -0.00008213504;
                        }
                    } else {
                        if (input[7] >= 9.7242565) {
                            var43 = -0.00066973193;
                        } else {
                            var43 = 0.0056351316;
                        }
                    }
                }
            } else {
                if (input[2] >= 9.5) {
                    if (input[2] >= 20.5) {
                        if (input[1] >= 5.12) {
                            var43 = -0.0005674328;
                        } else {
                            var43 = -0.001785725;
                        }
                    } else {
                        var43 = -0.0006897118;
                    }
                } else {
                    if (input[1] >= 58.98) {
                        var43 = -0.00052817323;
                    } else {
                        var43 = -0.002063682;
                    }
                }
            }
        }
    }
    float var44;
    if (input[2] >= 28.5) {
        if (input[4] >= -95.0) {
            if (input[7] >= 1.4213135) {
                if (input[2] >= 100.5) {
                    if (input[0] >= -7.5) {
                        if (input[5] >= -2.275) {
                            var44 = -0.00043113282;
                        } else {
                            var44 = -0.0004797834;
                        }
                    } else {
                        if (input[5] >= -1.915) {
                            var44 = -0.0007720178;
                        } else {
                            var44 = -0.00046658266;
                        }
                    }
                } else {
                    if (input[5] >= -0.265) {
                        if (input[0] >= -12.5) {
                            var44 = -0.0004955181;
                        } else {
                            var44 = -0.0000145168815;
                        }
                    } else {
                        if (input[5] >= -0.425) {
                            var44 = -0.0007207514;
                        } else {
                            var44 = -0.0004850668;
                        }
                    }
                }
            } else {
                var44 = -0.0015351031;
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[2] >= 44.5) {
                    if (input[3] >= -99.935) {
                        if (input[0] >= -7.5) {
                            var44 = -0.00046104385;
                        } else {
                            var44 = -0.000540276;
                        }
                    } else {
                        if (input[2] >= 75.5) {
                            var44 = -0.00024445786;
                        } else {
                            var44 = -0.00040376588;
                        }
                    }
                } else {
                    if (input[7] >= 9.982205) {
                        if (input[2] >= 30.5) {
                            var44 = -0.00056669995;
                        } else {
                            var44 = -0.0035049394;
                        }
                    } else {
                        if (input[3] >= -86.56) {
                            var44 = -0.0004313936;
                        } else {
                            var44 = -0.0005665335;
                        }
                    }
                }
            } else {
                if (input[2] >= 47.5) {
                    if (input[2] >= 92.5) {
                        if (input[0] >= -20.0) {
                            var44 = -0.00069958554;
                        } else {
                            var44 = -0.0009222555;
                        }
                    } else {
                        if (input[3] >= -99.015) {
                            var44 = -0.00040271654;
                        } else {
                            var44 = -0.0006668934;
                        }
                    }
                } else {
                    if (input[3] >= -95.89) {
                        if (input[3] >= -91.59) {
                            var44 = -0.00016548259;
                        } else {
                            var44 = 0.0017128699;
                        }
                    } else {
                        if (input[7] >= 4.484642) {
                            var44 = -0.00027217667;
                        } else {
                            var44 = -0.000742149;
                        }
                    }
                }
            }
        }
    } else {
        if (input[0] >= -12.5) {
            if (input[3] >= -99.715) {
                if (input[0] >= -7.5) {
                    if (input[0] >= -2.5) {
                        if (input[5] >= -2.96) {
                            var44 = -0.00068641466;
                        } else {
                            var44 = -0.00044992482;
                        }
                    } else {
                        if (input[3] >= -92.215) {
                            var44 = -0.00028979333;
                        } else {
                            var44 = -0.0005097922;
                        }
                    }
                } else {
                    if (input[5] >= -1.2850001) {
                        if (input[2] >= 18.5) {
                            var44 = 0.00017395438;
                        } else {
                            var44 = 0.0023736458;
                        }
                    } else {
                        if (input[5] >= -1.645) {
                            var44 = -0.0025823521;
                        } else {
                            var44 = -0.00050371507;
                        }
                    }
                }
            } else {
                if (input[4] >= -95.0) {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 20.5) {
                            var44 = -0.00044215596;
                        } else {
                            var44 = -0.00039481992;
                        }
                    } else {
                        if (input[2] >= 20.5) {
                            var44 = -0.0005000587;
                        } else {
                            var44 = -0.00046799897;
                        }
                    }
                } else {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 21.5) {
                            var44 = -0.00093563966;
                        } else {
                            var44 = -0.0017747296;
                        }
                    } else {
                        if (input[7] >= 9.930143) {
                            var44 = -0.0020573242;
                        } else {
                            var44 = -0.0006393547;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.96) {
                if (input[2] >= 17.5) {
                    if (input[0] >= -20.0) {
                        if (input[3] >= -99.994995) {
                            var44 = 0.001668727;
                        } else {
                            var44 = -0.000346411;
                        }
                    } else {
                        if (input[7] >= 1.463176) {
                            var44 = 0.0009574406;
                        } else {
                            var44 = -0.0062426785;
                        }
                    }
                } else {
                    if (input[7] >= 1.4985545) {
                        if (input[7] >= 1.531616) {
                            var44 = 0.0019328333;
                        } else {
                            var44 = 0.0070614377;
                        }
                    } else {
                        if (input[7] >= 1.497514) {
                            var44 = -0.0078217145;
                        } else {
                            var44 = -0.001117973;
                        }
                    }
                }
            } else {
                if (input[2] >= 20.5) {
                    if (input[3] >= -88.04) {
                        var44 = -0.0013124848;
                    } else {
                        if (input[3] >= -99.994995) {
                            var44 = -0.0006004695;
                        } else {
                            var44 = -0.00048635295;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        var44 = -0.0006072322;
                    } else {
                        if (input[0] >= -20.0) {
                            var44 = -0.00054142304;
                        } else {
                            var44 = -0.001428912;
                        }
                    }
                }
            }
        }
    }
    float var45;
    if (input[1] >= 59.425) {
        if (input[4] >= -95.0) {
            if (input[3] >= -92.69) {
                if (input[4] >= -85.0) {
                    var45 = -0.00038752196;
                } else {
                    var45 = -0.00067665894;
                }
            } else {
                if (input[0] >= -7.5) {
                    var45 = -0.00038759407;
                } else {
                    var45 = -0.00043340065;
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[3] >= -99.875) {
                        if (input[3] >= -84.345) {
                            var45 = 0.0009886634;
                        } else {
                            var45 = -0.0004121429;
                        }
                    } else {
                        if (input[0] >= -2.5) {
                            var45 = 0.00013903479;
                        } else {
                            var45 = -0.00006914638;
                        }
                    }
                } else {
                    if (input[7] >= 9.931435) {
                        var45 = -0.003403391;
                    } else {
                        if (input[7] >= 9.905604) {
                            var45 = 0.0015779209;
                        } else {
                            var45 = -0.00083703327;
                        }
                    }
                }
            } else {
                if (input[7] >= 9.636059) {
                    if (input[1] >= 61.3) {
                        if (input[1] >= 61.92) {
                            var45 = 0.000033620167;
                        } else {
                            var45 = 0.008794981;
                        }
                    } else {
                        if (input[1] >= 60.82) {
                            var45 = -0.005489116;
                        } else {
                            var45 = -0.00036522394;
                        }
                    }
                } else {
                    if (input[7] >= 4.9139676) {
                        if (input[7] >= 9.517208) {
                            var45 = -0.0042541195;
                        } else {
                            var45 = -0.0074018924;
                        }
                    } else {
                        if (input[7] >= 4.5780535) {
                            var45 = -0.0007476277;
                        } else {
                            var45 = -0.0027338376;
                        }
                    }
                }
            }
        }
    } else {
        if (input[1] >= 59.415) {
            if (input[7] >= 9.690667) {
                if (input[7] >= 9.773305) {
                    if (input[0] >= -12.5) {
                        var45 = -0.00022075616;
                    } else {
                        var45 = 0.001183261;
                    }
                } else {
                    var45 = -0.00039843097;
                }
            } else {
                if (input[4] >= -95.0) {
                    var45 = -0.0011758272;
                } else {
                    var45 = 0.015433261;
                }
            }
        } else {
            if (input[0] >= -20.0) {
                if (input[7] >= 9.983474) {
                    if (input[4] >= -95.0) {
                        if (input[3] >= -81.845) {
                            var45 = -0.001280095;
                        } else {
                            var45 = -0.0004548337;
                        }
                    } else {
                        if (input[1] >= 46.565002) {
                            var45 = -0.0019949477;
                        } else {
                            var45 = -0.0013268145;
                        }
                    }
                } else {
                    if (input[7] >= 9.983108) {
                        if (input[7] >= 9.983239) {
                            var45 = 0.0009426674;
                        } else {
                            var45 = 0.002883837;
                        }
                    } else {
                        if (input[1] >= 29.775002) {
                            var45 = -0.00044452623;
                        } else {
                            var45 = -0.00041853808;
                        }
                    }
                }
            } else {
                if (input[7] >= 1.4935164) {
                    if (input[7] >= 1.4980915) {
                        if (input[7] >= 1.4991815) {
                            var45 = -0.00040018823;
                        } else {
                            var45 = -0.0059973234;
                        }
                    } else {
                        if (input[1] >= 30.77) {
                            var45 = 0.0058053834;
                        } else {
                            var45 = 0.0014563345;
                        }
                    }
                } else {
                    if (input[1] >= 54.095) {
                        if (input[1] >= 55.120003) {
                            var45 = -0.0013515003;
                        } else {
                            var45 = -0.007081887;
                        }
                    } else {
                        if (input[7] >= 1.475258) {
                            var45 = -0.004065677;
                        } else {
                            var45 = -0.00081473956;
                        }
                    }
                }
            }
        }
    }
    float var46;
    if (input[0] >= -20.0) {
        if (input[1] >= 3.435) {
            if (input[1] >= 43.735) {
                if (input[5] >= -1.795) {
                    if (input[0] >= -7.5) {
                        if (input[1] >= 53.875) {
                            var46 = -0.00031341988;
                        } else {
                            var46 = -0.00042628968;
                        }
                    } else {
                        if (input[1] >= 54.445) {
                            var46 = -0.0008926933;
                        } else {
                            var46 = -0.0005241249;
                        }
                    }
                } else {
                    if (input[7] >= 1.4214311) {
                        if (input[5] >= -1.805) {
                            var46 = 0.00066144025;
                        } else {
                            var46 = -0.00037737034;
                        }
                    } else {
                        var46 = 0.001291064;
                    }
                }
            } else {
                if (input[1] >= 43.715) {
                    if (input[4] >= -95.0) {
                        if (input[5] >= 2.795) {
                            var46 = 0.00067110284;
                        } else {
                            var46 = -0.00035929223;
                        }
                    } else {
                        if (input[7] >= 1.6344686) {
                            var46 = 0.00054594903;
                        } else {
                            var46 = 0.010610829;
                        }
                    }
                } else {
                    if (input[7] >= 9.9435215) {
                        if (input[7] >= 9.9455595) {
                            var46 = -0.0003036024;
                        } else {
                            var46 = 0.0046220585;
                        }
                    } else {
                        if (input[7] >= 9.929087) {
                            var46 = -0.00056497444;
                        } else {
                            var46 = -0.00039144768;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= 13.38) {
                if (input[0] >= -7.5) {
                    if (input[7] >= 9.8406105) {
                        if (input[7] >= 9.855578) {
                            var46 = -0.00028307547;
                        } else {
                            var46 = 0.0017475978;
                        }
                    } else {
                        if (input[5] >= 16.45) {
                            var46 = -0.0005292226;
                        } else {
                            var46 = 0.00034414107;
                        }
                    }
                } else {
                    if (input[7] >= 1.4979196) {
                        if (input[5] >= 39.195) {
                            var46 = -0.00092169706;
                        } else {
                            var46 = 0.00021395968;
                        }
                    } else {
                        var46 = 0.0039789816;
                    }
                }
            } else {
                if (input[7] >= 4.782854) {
                    if (input[5] >= 7.835) {
                        if (input[7] >= 9.670297) {
                            var46 = 0.0013498905;
                        } else {
                            var46 = -0.00048925244;
                        }
                    } else {
                        var46 = -0.0014104877;
                    }
                } else {
                    if (input[5] >= 8.42) {
                        var46 = 0.0048870365;
                    } else {
                        if (input[1] >= 2.9650002) {
                            var46 = -0.00022788942;
                        } else {
                            var46 = 0.00033458183;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -2.06) {
            if (input[7] >= 1.5134549) {
                if (input[1] >= 36.92) {
                    if (input[1] >= 58.135002) {
                        if (input[7] >= 1.6950951) {
                            var46 = -0.00040093056;
                        } else {
                            var46 = -0.0037009728;
                        }
                    } else {
                        if (input[1] >= 57.795) {
                            var46 = 0.0059212074;
                        } else {
                            var46 = -0.00008341008;
                        }
                    }
                } else {
                    if (input[1] >= 36.754997) {
                        if (input[6] >= 3.5) {
                            var46 = -0.0024887659;
                        } else {
                            var46 = -0.0008390679;
                        }
                    } else {
                        if (input[7] >= 1.712258) {
                            var46 = -0.00030275725;
                        } else {
                            var46 = -0.000012149262;
                        }
                    }
                }
            } else {
                if (input[5] >= 1.285) {
                    if (input[5] >= 7.5899997) {
                        var46 = 0.0006708302;
                    } else {
                        var46 = 0.004110645;
                    }
                } else {
                    if (input[1] >= 56.02) {
                        if (input[1] >= 57.31) {
                            var46 = -0.0016994957;
                        } else {
                            var46 = 0.010713378;
                        }
                    } else {
                        if (input[7] >= 1.475258) {
                            var46 = -0.0033068103;
                        } else {
                            var46 = -0.0011570374;
                        }
                    }
                }
            }
        } else {
            if (input[5] >= -2.16) {
                if (input[7] >= 4.7848577) {
                    var46 = -0.0014467017;
                } else {
                    var46 = -0.00034554538;
                }
            } else {
                if (input[1] >= 7.215) {
                    if (input[1] >= 38.934998) {
                        if (input[1] >= 52.565002) {
                            var46 = -0.00044582;
                        } else {
                            var46 = -0.0004182207;
                        }
                    } else {
                        if (input[1] >= 7.375) {
                            var46 = -0.00039667735;
                        } else {
                            var46 = -0.000049589693;
                        }
                    }
                } else {
                    if (input[1] >= 7.1949997) {
                        if (input[4] >= -85.0) {
                            var46 = -0.00017970084;
                        } else {
                            var46 = -0.0017220993;
                        }
                    } else {
                        if (input[1] >= 7.14) {
                            var46 = 0.00020126217;
                        } else {
                            var46 = -0.0005207504;
                        }
                    }
                }
            }
        }
    }
    float var47;
    if (input[0] >= -20.0) {
        if (input[1] >= 59.765) {
            if (input[0] >= -12.5) {
                if (input[0] >= -7.5) {
                    if (input[5] >= 15.155001) {
                        var47 = 0.00095490116;
                    } else {
                        if (input[5] >= 3.315) {
                            var47 = -0.0005110094;
                        } else {
                            var47 = -0.00027615082;
                        }
                    }
                } else {
                    if (input[1] >= 59.775) {
                        if (input[1] >= 62.035) {
                            var47 = -0.0008457219;
                        } else {
                            var47 = -0.00039182586;
                        }
                    } else {
                        var47 = -0.0029833037;
                    }
                }
            } else {
                if (input[4] >= -95.0) {
                    if (input[1] >= 61.989998) {
                        if (input[7] >= 1.7620704) {
                            var47 = -0.00037631576;
                        } else {
                            var47 = -0.00016262525;
                        }
                    } else {
                        var47 = -0.00027488245;
                    }
                } else {
                    if (input[6] >= 3.5) {
                        if (input[1] >= 59.955) {
                            var47 = -0.0024210827;
                        } else {
                            var47 = -0.005421295;
                        }
                    } else {
                        if (input[1] >= 61.190002) {
                            var47 = -0.0026540558;
                        } else {
                            var47 = -0.00014554766;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 59.754997) {
                if (input[7] >= 4.712942) {
                    var47 = 0.000077505414;
                } else {
                    var47 = 0.006742505;
                }
            } else {
                if (input[1] >= 1.355) {
                    if (input[1] >= 1.565) {
                        if (input[7] >= 9.983474) {
                            var47 = -0.00057452597;
                        } else {
                            var47 = -0.00035402528;
                        }
                    } else {
                        if (input[0] >= -7.5) {
                            var47 = -0.0003187117;
                        } else {
                            var47 = 0.002534653;
                        }
                    }
                } else {
                    if (input[7] >= 4.72606) {
                        if (input[0] >= -7.5) {
                            var47 = -0.0005129468;
                        } else {
                            var47 = -0.002589385;
                        }
                    } else {
                        if (input[5] >= 29.125) {
                            var47 = -0.0004288617;
                        } else {
                            var47 = 0.0030542668;
                        }
                    }
                }
            }
        }
    } else {
        if (input[5] >= -2.08) {
            if (input[7] >= 1.463176) {
                if (input[1] >= 60.83) {
                    if (input[7] >= 9.805265) {
                        if (input[7] >= 9.846157) {
                            var47 = -0.0010102873;
                        } else {
                            var47 = 0.009743332;
                        }
                    } else {
                        if (input[7] >= 4.518305) {
                            var47 = -0.0020014325;
                        } else {
                            var47 = -0.004060027;
                        }
                    }
                } else {
                    if (input[1] >= 60.705) {
                        if (input[6] >= 3.5) {
                            var47 = 0.01157767;
                        } else {
                            var47 = -0.00014165007;
                        }
                    } else {
                        if (input[1] >= 58.385002) {
                            var47 = -0.0015419837;
                        } else {
                            var47 = -0.00018494016;
                        }
                    }
                }
            } else {
                if (input[1] >= 36.625) {
                    if (input[1] >= 57.995003) {
                        var47 = -0.0010179564;
                    } else {
                        var47 = -0.0049167643;
                    }
                } else {
                    var47 = 0.00008596182;
                }
            }
        } else {
            if (input[5] >= -2.165) {
                if (input[4] >= -85.0) {
                    var47 = 0.00006707385;
                } else {
                    if (input[6] >= 3.5) {
                        var47 = -0.0013895731;
                    } else {
                        var47 = -0.0004647502;
                    }
                }
            } else {
                if (input[1] >= 38.955) {
                    if (input[1] >= 52.035) {
                        if (input[1] >= 58.09) {
                            var47 = -0.0003502103;
                        } else {
                            var47 = -0.000412849;
                        }
                    } else {
                        var47 = -0.0003760258;
                    }
                } else {
                    if (input[1] >= 8.219999) {
                        if (input[5] >= -3.165) {
                            var47 = -0.000019051678;
                        } else {
                            var47 = -0.00035569986;
                        }
                    } else {
                        if (input[5] >= -9.415) {
                            var47 = -0.0005137722;
                        } else {
                            var47 = -0.00036262255;
                        }
                    }
                }
            }
        }
    }
    float var48;
    if (input[2] >= 20.5) {
        if (input[2] >= 38.5) {
            if (input[0] >= -12.5) {
                if (input[3] >= -99.265) {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 78.5) {
                            var48 = -0.00028372894;
                        } else {
                            var48 = -0.0003336141;
                        }
                    } else {
                        if (input[2] >= 41.5) {
                            var48 = -0.00036016182;
                        } else {
                            var48 = -0.00008302495;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[2] >= 43.5) {
                            var48 = -0.00032388628;
                        } else {
                            var48 = -0.00029986765;
                        }
                    } else {
                        if (input[2] >= 58.5) {
                            var48 = -0.00017126712;
                        } else {
                            var48 = -0.0003069384;
                        }
                    }
                }
            } else {
                if (input[4] >= -95.0) {
                    if (input[3] >= -76.56) {
                        if (input[2] >= 58.5) {
                            var48 = -0.0006646425;
                        } else {
                            var48 = 0.00073961704;
                        }
                    } else {
                        if (input[1] >= 6.0200005) {
                            var48 = -0.00031769322;
                        } else {
                            var48 = 0.00003272544;
                        }
                    }
                } else {
                    if (input[1] >= 43.605) {
                        if (input[0] >= -20.0) {
                            var48 = -0.00057347975;
                        } else {
                            var48 = -0.0007841561;
                        }
                    } else {
                        if (input[2] >= 62.5) {
                            var48 = -0.00051992753;
                        } else {
                            var48 = -0.00012841665;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 38.835) {
                if (input[4] >= -95.0) {
                    if (input[3] >= -80.215) {
                        if (input[6] >= 7.5) {
                            var48 = 0.0017334989;
                        } else {
                            var48 = -0.000646047;
                        }
                    } else {
                        if (input[3] >= -91.795) {
                            var48 = -0.00039672927;
                        } else {
                            var48 = -0.00030347795;
                        }
                    }
                } else {
                    if (input[0] >= -20.0) {
                        if (input[0] >= -7.5) {
                            var48 = -0.0003085438;
                        } else {
                            var48 = -0.0007528059;
                        }
                    } else {
                        if (input[1] >= 58.255) {
                            var48 = -0.0019920121;
                        } else {
                            var48 = 0.00014408474;
                        }
                    }
                }
            } else {
                if (input[0] >= -12.5) {
                    if (input[0] >= -2.5) {
                        if (input[1] >= 12.075) {
                            var48 = -0.00046996027;
                        } else {
                            var48 = -0.0011595686;
                        }
                    } else {
                        if (input[3] >= -95.225006) {
                            var48 = -0.00014915544;
                        } else {
                            var48 = -0.00043047257;
                        }
                    }
                } else {
                    if (input[4] >= -95.0) {
                        if (input[3] >= -92.54) {
                            var48 = 0.00051307556;
                        } else {
                            var48 = -0.0004028678;
                        }
                    } else {
                        if (input[2] >= 23.5) {
                            var48 = 0.00062603306;
                        } else {
                            var48 = 0.0021113497;
                        }
                    }
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 13.514999) {
                if (input[0] >= -12.5) {
                    if (input[3] >= -77.395004) {
                        var48 = 0.0011912945;
                    } else {
                        if (input[1] >= 40.940002) {
                            var48 = -0.00029952725;
                        } else {
                            var48 = -0.00022990866;
                        }
                    }
                } else {
                    if (input[2] >= 9.5) {
                        if (input[0] >= -20.0) {
                            var48 = -0.00041423464;
                        } else {
                            var48 = -0.00043964604;
                        }
                    } else {
                        if (input[0] >= -20.0) {
                            var48 = -0.00037620717;
                        } else {
                            var48 = -0.0011654459;
                        }
                    }
                }
            } else {
                if (input[3] >= -89.770004) {
                    var48 = 0.0045660865;
                } else {
                    var48 = 0.0008813076;
                }
            }
        } else {
            if (input[0] >= -12.5) {
                if (input[3] >= -99.229996) {
                    if (input[0] >= -7.5) {
                        if (input[3] >= -92.244995) {
                            var48 = -0.000098876386;
                        } else {
                            var48 = -0.000528739;
                        }
                    } else {
                        if (input[1] >= 54.684998) {
                            var48 = -0.0030526228;
                        } else {
                            var48 = 0.0014475894;
                        }
                    }
                } else {
                    if (input[0] >= -7.5) {
                        if (input[2] >= 9.5) {
                            var48 = -0.0012005903;
                        } else {
                            var48 = -0.0043665185;
                        }
                    } else {
                        if (input[1] >= 50.809998) {
                            var48 = -0.0012371559;
                        } else {
                            var48 = -0.00015331825;
                        }
                    }
                }
            } else {
                if (input[2] >= 10.5) {
                    if (input[1] >= 54.29) {
                        if (input[6] >= 7.5) {
                            var48 = 0.0016134664;
                        } else {
                            var48 = -0.0021050966;
                        }
                    } else {
                        if (input[1] >= 52.445) {
                            var48 = 0.0043371175;
                        } else {
                            var48 = 0.001348832;
                        }
                    }
                } else {
                    if (input[1] >= 58.34) {
                        if (input[0] >= -20.0) {
                            var48 = 0.003907404;
                        } else {
                            var48 = -0.0015444923;
                        }
                    } else {
                        if (input[1] >= 53.940002) {
                            var48 = 0.010370493;
                        } else {
                            var48 = 0.0044182646;
                        }
                    }
                }
            }
        }
    }
    float var49;
    if (input[2] >= 27.5) {
        if (input[2] >= 62.5) {
            if (input[5] >= -2.0949998) {
                if (input[3] >= -98.774994) {
                    if (input[2] >= 85.5) {
                        if (input[1] >= 11.005) {
                            var49 = -0.00032096097;
                        } else {
                            var49 = -0.00040836545;
                        }
                    } else {
                        if (input[3] >= -98.475006) {
                            var49 = -0.00029848033;
                        } else {
                            var49 = -0.0000057430184;
                        }
                    }
                } else {
                    if (input[1] >= 41.105) {
                        if (input[3] >= -99.985) {
                            var49 = -0.00020641838;
                        } else {
                            var49 = -0.00056757766;
                        }
                    } else {
                        if (input[1] >= 8.43) {
                            var49 = -0.0003950642;
                        } else {
                            var49 = 0.0013978889;
                        }
                    }
                }
            } else {
                if (input[3] >= -82.115005) {
                    if (input[6] >= 7.5) {
                        if (input[1] >= 16.03) {
                            var49 = 0.0008499175;
                        } else {
                            var49 = -0.00018200379;
                        }
                    } else {
                        var49 = -0.00022560854;
                    }
                } else {
                    if (input[3] >= -99.985) {
                        if (input[1] >= 5.975) {
                            var49 = -0.00028459055;
                        } else {
                            var49 = -0.00036888345;
                        }
                    } else {
                        if (input[2] >= 75.5) {
                            var49 = -0.00026955333;
                        } else {
                            var49 = -0.00027936764;
                        }
                    }
                }
            }
        } else {
            if (input[1] >= 0.96500003) {
                if (input[1] >= 19.985) {
                    if (input[1] >= 39.245003) {
                        if (input[4] >= -95.0) {
                            var49 = -0.00028322334;
                        } else {
                            var49 = -0.00036430891;
                        }
                    } else {
                        if (input[5] >= -2.9250002) {
                            var49 = -0.00021724349;
                        } else {
                            var49 = -0.000301051;
                        }
                    }
                } else {
                    if (input[5] >= -2.065) {
                        if (input[3] >= -86.854996) {
                            var49 = -0.00021437205;
                        } else {
                            var49 = 0.00059574895;
                        }
                    } else {
                        if (input[1] >= 7.29) {
                            var49 = -0.00039720544;
                        } else {
                            var49 = -0.0010988923;
                        }
                    }
                }
            } else {
                if (input[3] >= -53.22) {
                    if (input[1] >= 0.78499997) {
                        if (input[1] >= 0.93) {
                            var49 = 0.0011164316;
                        } else {
                            var49 = -0.00037722662;
                        }
                    } else {
                        var49 = -0.0028426235;
                    }
                } else {
                    var49 = 0.008276905;
                }
            }
        }
    } else {
        if (input[4] >= -95.0) {
            if (input[1] >= 7.4399996) {
                if (input[1] >= 9.615) {
                    if (input[1] >= 11.075) {
                        if (input[1] >= 15.255) {
                            var49 = -0.00029009275;
                        } else {
                            var49 = -0.00092872756;
                        }
                    } else {
                        if (input[1] >= 10.934999) {
                            var49 = 0.003614882;
                        } else {
                            var49 = -0.00051693904;
                        }
                    }
                } else {
                    if (input[2] >= 23.5) {
                        if (input[3] >= -76.130005) {
                            var49 = -0.00063982507;
                        } else {
                            var49 = -0.002688295;
                        }
                    } else {
                        var49 = 0.0018315986;
                    }
                }
            } else {
                if (input[1] >= 7.21) {
                    var49 = 0.00708116;
                } else {
                    if (input[3] >= -86.095) {
                        if (input[3] >= -81.655) {
                            var49 = -0.00060812215;
                        } else {
                            var49 = -0.0026669074;
                        }
                    } else {
                        var49 = 0.004599691;
                    }
                }
            }
        } else {
            if (input[1] >= 29.064999) {
                if (input[2] >= 7.5) {
                    if (input[1] >= 50.045) {
                        if (input[2] >= 17.5) {
                            var49 = -0.0005851382;
                        } else {
                            var49 = 0.000017648807;
                        }
                    } else {
                        if (input[1] >= 50.03) {
                            var49 = 0.01457835;
                        } else {
                            var49 = 0.00011542535;
                        }
                    }
                } else {
                    if (input[1] >= 57.495003) {
                        if (input[2] >= 5.0) {
                            var49 = -0.0010794146;
                        } else {
                            var49 = 0.008850026;
                        }
                    } else {
                        if (input[1] >= 55.835) {
                            var49 = 0.008027848;
                        } else {
                            var49 = 0.00343716;
                        }
                    }
                }
            } else {
                if (input[3] >= -94.885) {
                    if (input[1] >= 3.435) {
                        if (input[3] >= -94.134995) {
                            var49 = 0.00024152178;
                        } else {
                            var49 = -0.0027688006;
                        }
                    } else {
                        if (input[1] >= 2.3600001) {
                            var49 = 0.006478882;
                        } else {
                            var49 = 0.0014905267;
                        }
                    }
                } else {
                    if (input[2] >= 25.5) {
                        if (input[3] >= -95.979996) {
                            var49 = 0.00691434;
                        } else {
                            var49 = 0.00022689665;
                        }
                    } else {
                        if (input[1] >= 21.395) {
                            var49 = 0.005828531;
                        } else {
                            var49 = 0.00004533902;
                        }
                    }
                }
            }
        }
    }
    return NAN + (var0 + var1 + var2 + var3 + var4 + var5 + var6 + var7 + var8 + var9 + var10 + var11 + var12 + var13 + var14 + var15 + var16 + var17 + var18 + var19 + var20 + var21 + var22 + var23 + var24 + var25 + var26 + var27 + var28 + var29 + var30 + var31 + var32 + var33 + var34 + var35 + var36 + var37 + var38 + var39 + var40 + var41 + var42 + var43 + var44 + var45 + var46 + var47 + var48 + var49);
}

volatile float result;
int main(void) {
    float input[8] = {-10.0f, 45.0f, 15.0f, -82.0f, -90.0f, 8.0f, 5.0f, 4.2f};
    result = score(input);
    return 0;
}
