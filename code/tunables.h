#pragma once


#define qsFPmargin 123 // 0 300
#define qsFPseeMargin 15 // -100 100

#define qsBetaFail 517 // 0 1024

#define corrplexityMargin 119 // 0 300

#define rfpBaseD2 40 // 0 70
#define rfpImprovingD2 16 // 0 40
#define rfpCorrplexityD2 27 // 0 40
#define rfpWorseningD2 6 // 0 40
#define rfpCutnodeD2 0 // 0 40
#define rfpBaseD1 9 // 0 70
#define rfpImprovingD1 4 // 0 40
#define rfpCorrplexityD1 6 // 0 40
#define rfpWorseningD1 1 // 0 40
#define rfpCutnodeD1 5 // 0 40
#define rfpBaseD0 2 // 0 70
#define rfpImprovingD0 5 // 0 40
#define rfpCorrplexityD0 1 // 0 40
#define rfpWorseningD0 4 // 0 40
#define rfpCutnodeD0 2 // 0 40
#define rfpFail 546 // 0 1024

#define nmpBaseMargin 37 // 0 80
#define nmpDepthMargin 1302 // 0 10240
#define nmpDepth2Margin 1071 // 0 10240
#define nmpRbase 4979 // 0 10240 250
#define nmpRdepth 203 // 0 1024 12
#define nmpRimproving 150 // 0 3072
#define nmpRcutnode -130 // -4096 4096
#define nmpRmargin 254 // 50 500
#define nmpRmarginClamp 4651 // 512 10240

#define razorBaseD2 102 // 100 400
#define razorImprovingD2 38 // 0 70
#define razorBaseD1 37 // 0 300
#define razorImprovingD1 9 // 0 70
#define razorBaseD0 269 // 0 400
#define razorImprovingD0 7 // 0 70
#define razorFPmargin 40 // 0 150
#define razorRFPmargin 268 // 0 500

#define probcutBase 313 // 0 500
#define probcutImproving 62 // 0 100
#define probcutFail 994 // 0 1024

#define singextMarginDepth 982 // 0 1024
#define dextMarginBase 14478 // 0 15360
#define dextMarginHistory 7 // 0 10
#define trextMarginBase 79 // 0 80

#define lmpBaseD2 1463 // 0 4096
#define lmpImprovingD2 393 // 0 1024
#define lmpTTcaptureD2 180 // 0 1024
#define lmpBaseD1 336 // 0 4096
#define lmpImprovingD1 85 // 0 1024
#define lmpTTcaptureD1 310 // 0 1024
#define lmpBaseD0 2365 // 0 5120
#define lmpImprovingD0 86 // 0 1024
#define lmpTTcaptureD0 104 // 0 1024
#define lmpHistoryThreshold 470 // -1280 1280

#define historyBaseD2 226 // 0 800
#define historyImprovingD2 4 // 0 200
#define historyTTcaptureD2 17 // 0 200
#define historyBaseD1 258 // 0 800
#define historyImprovingD1 54 // 0 200
#define historyTTcaptureD1 32 // 0 200
#define historyBaseD0 149 // 0 800
#define historyImprovingD0 50 // 0 200
#define historyTTcaptureD0 24 // 0 200

#define fpBaseD2 157 // 0 500
#define fpImprovingD2 25 // 0 200
#define fpTTcaptureD2 57 // 0 200
#define fpHistoryD2 23 // 0 200
#define fpBaseD1 17 // 0 500
#define fpImprovingD1 31 // 0 200
#define fpTTcaptureD1 2 // 0 200
#define fpHistoryD1 1 // 0 200
#define fpBaseD0 37 // 0 500
#define fpImprovingD0 25 // 0 200
#define fpTTcaptureD0 21 // 0 200
#define fpHistoryD0 32 // 0 200

#define seeQBaseD0 43 // 0 500
#define seeQHistoryD0 22 // 0 200
#define seeQBaseD1 98 // 0 500
#define seeQHistoryD1 17 // 0 200
#define seeQBaseD2 39 // 0 500
#define seeQHistoryD2 0 // 0 200

#define seeNBaseD0 109 // 0 500
#define seeNHistoryD0 74 // 0 200
#define seeNBaseD1 19 // 0 500
#define seeNHistoryD1 61 // 0 200
#define seeNBaseD2 64 // 0 500
#define seeNHistoryD2 22 // 0 200

#define lmrDivisor 298 // 0 2048 20
#define lmrBase 472 // 0 4096
#define lmrPv 478 // 0 4096 120
#define lmrHistory 1176 // 0 4096 120
#define lmrImproving 131 // 0 4096 120
#define lmrTTcapture 817 // 0 4096 120
#define lmrExact 862 // 0 4096 120
#define lmrCutnode 956 // 0 4096 120
#define lmrTtpv 483 // 0 4096 120
#define lmrCorrplex 849 // 0 4096 120
#define lmrCapture 972 // 0 4096 120
#define lmrSee 1880 // 0 4096 120
#define lmrKiller 1301 // 0 4096 120

#define historyBonusD0 1133 // -1600 1600
#define historyBonusD1 40 // 0 1600
#define historyBonusD2 85 // 0 1600
#define historyMaluseD0 787 // -1600 1600
#define historyMaluseD1 304 // 0 1600
#define historyMaluseD2 4 // 0 1600

#define aspirationWindowSize 20 // 15 200
#define aspirationWindowMult 1957 // 1800 10240 200

#define bmStab0 2560 // 300 5120 *
#define bmStab1 1229 // 300 5120 *
#define bmStab2 922 // 300 5120 *
#define bmStab3 819 // 300 5120 *
#define bmStab4 768 // 300 5120 *
#define nodesTM 1741 // 1200 4096 *

#define historyScoreFromTo 719 // 0 2048
#define historyScorePieceTo 666 // 0 2048
#define historyScorePly1 959 // 0 2048
#define historyScorePly2 812 // 0 2048
#define historyScorePly4 268 // 0 2048

#define corrhistPawn 147 // 0 1024 12
#define corrhistMinor 140 // 0 1024 12
#define corrhistColor 136 // 0 1024 12
#define corrhistFromTo 188 // 0 1024 12
#define corrhistPly1 154 // 0 1024 12

#define seePawn 60 // 0 300
#define seeKnight 498 // 0 800
#define seeBishop 588 // 0 800
#define seeRook 551 // 0 1200
#define seeQueen 695 // 0 2500

#define qsBadCapturesMargin 153 // 0 500
#define badCapturesBase 227 // 0 500
#define badCapturesHistory 288 // 0 500

#define moveOrderHistoryScore 49 // 0 1600
#define moveOrderPawn 163 // 0 300
#define moveOrderKnight 494 // 0 800
#define moveOrderBishop 268 // 0 800
#define moveOrderRook 701 // 0 1200
#define moveOrderQueen 1411 // 0 2500

#define matScalePawn 122 // 0 200
#define matScaleKnight 281 // 100 500
#define matScaleBishop 339 // 100 500
#define matScaleRook 623 // 300 800
#define matScaleQueen 916 // 500 1400
#define matScaleBase 23200 // 10000 40000
