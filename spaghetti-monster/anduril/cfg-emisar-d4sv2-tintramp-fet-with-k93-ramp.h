// Emisar D4S V2 tint-ramping (plus FET) config options for Anduril (based on Noctigon K9.3)
#include "cfg-emisar-d4sv2-tintramp.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0136"
// ATTINY: 1634

// enable the FET channel, even though it's ... kinda funky
#undef PWM_CHANNELS
#define PWM_CHANNELS 2

// main LEDs
//   output: unknown, 2000 lm?
//   FET: unknown, 3000 lm?
// 2nd LEDs
//   output: unknown, 2000 lm?
#define RAMP_LENGTH 150
#undef DEFAULT_LEVEL

#undef PWM_TOPS
#undef PWM_TOP
#undef PWM1_LEVELS
#undef PWM2_LEVELS
#undef PWM3_LEVELS
//////////////////// ORIGINAL RAMP TABLES ////////////////////////////
// These use different PWM_TOP values so aren't directly comparable
// The K9.3 has a unique(?) dual channel config with a separate ramp for each linear while the D4S uses the same one for both

//D4Sv2 ramps (dynamic PWM):
//#define PWM1_LEVELS 2,2,2,3,3,4,4,5,6,7,8,9,10,11,13,14,16,17,19,21,23,25,28,30,33,35,38,41,44,47,50,54,57,60,64,67,71,74,78,81,84,88,91,94,97,99,101,103,105,106,107,107,107,106,105,102,99,95,90,84,77,68,58,47,34,36,38,40,42,44,47,49,52,54,57,60,63,66,69,73,76,80,83,87,91,96,100,104,109,114,119,124,130,135,141,147,153,160,166,173,180,187,195,203,211,219,228,236,245,255,264,274,285,295,306,317,329,340,353,365,378,391,405,419,433,448,463,479,495,511,530,550,570,591,612,634,657,680,705,730,755,782,809,837,865,895,925,957,989,1022 //linear
//#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,14,27,45,68,96,129,166,208,255 //FET
//#define PWM_TOPS 16383,13234,9781,13826,9593,13434,9973,12021,12900,13193,13150,12899,12508,12023,12666,11982,12181,11422,11393,11247,11018,10731,10826,10434,10365,9927,9767,9565,9332,9076,8806,8693,8395,8096,7928,7626,7439,7143,6948,6665,6393,6203,5946,5700,5465,5187,4926,4681,4451,4195,3957,3700,3463,3213,2983,2718,2476,2231,1986,1742,1501,1245,997,756,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511

//K9.3-tintramp-fet ramps (dynamic PWM)
#define PWM1_LEVELS 1,1,1,2,2,3,3,4,5,6,7,8,9,10,12,13,15,16,18,20,22,24,27,29,32,34,37,40,43,46,49,53,56,59,63,66,70,73,77,80,83,87,90,93,96,98,100,103,104,105,106,107,106,105,104,101,98,94,89,83,76,67,57,46,33,35,37,39,41,43,46,48,51,53,56,59,62,65,68,72,75,79,83,86,91,95,99,104,108,113,118,123,129,135,140,146,153,159,166,172,179,187,194,202,210,218,227,236,245,254,264,274,284,295,306,317,328,340,352,365,378,391,405,419,433,448,463,479,495,511,501,485,469,453,433,413,391,369,345,321,295,267,237,207,177,143,108,74,38,0 //linear (both)
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,13,21,29,39,49,60,71,83,95,108,122,137,152,167,184,201,218,236,255 //FET
#define PWM_TOPS 16383,13233,9780,13825,9592,13434,9971,12020,12899,13192,13149,12898,12507,12022,12665,11981,12180,11421,11392,11246,11017,10730,10825,10433,10364,9926,9766,9564,9331,9075,8805,8692,8394,8095,7927,7625,7438,7142,6947,6664,6392,6202,5945,5699,5464,5186,4925,4726,4450,4194,3956,3734,3462,3212,2982,2717,2475,2230,1985,1741,1500,1244,996,755,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511
#undef PWM_CHANNELS
#define PWM_CHANNELS 2

//K9.3-219 ramps (PWM_TOP=1023)
//define PWM1_LEVELS 0,0,1,1,2,2,3,3,4,4,5,6,7,8,9,10,11,13,14,15,17,19,20,22,24,26,28,30,33,35,38,40,43,46,49,52,55,59,62,66,70,74,78,82,86,91,96,100,105,111,116,121,127,133,139,145,151,158,165,172,179,186,193,201,209,217,225,234,243,251,261,270,280,289,299,310,320,331,342,353,364,376,388,400,412,425,438,451,464,478,492,506,521,536,551,566,582,597,614,630,647,664,681,699,717,735,754,772,792,811,831,851,871,892,913,935,956,978,1001,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023 //linear1
// 65% FET power
//#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,34,52,71,90,110,129,149,169,190,211,233,254,275,298,320,343,366,389,413,437,461,485,510,535,560,586,612,639,665 //FET
//#define PWM3_LEVELS 0,0,1,1,2,2,3,3,4,4,5,5,6,7,8,9,10,11,12,13,15,16,17,18,20,21,23,24,26,27,29,31,33,35,37,39,41,43,45,48,50,53,55,58,61,63,66,69,72,75,79,82,85,89,92,96,100,104,108,112,116,120,125,129,134,138,143,148,153,158,163,169,174,180,185,191,197,203,209,215,222,228,235,242,248,255,263,270,277,285,292,300,308,316,324,333,341,350,359,368,377,386,395,405,414,424,434,444,454,465,475,486,497,508,519,531,542,554,566,578,590,603,615,628,641,654,667,680,694,708,722,736,750,765,779,794,809,825,840,856,872,888,904,920,937,954,971,988,1005,1023 //linear2, ramp table is almost but not exactly the same as linear1

/*
//TODO: not finished
//K9.3-219 ramps, with dynamic PWM, same PWM_TOPS ramp as K9.3-tintramp-fet for simplicity
//#define PWM1_LEVELS 1,1,1,2,2,3,3,4,5,6,7,8,9,10,12,13,15,16,18,20,22,24,27,29,32,34,37,40,43,46,49,53,56,59,63,66,70,73,77,80,83,87,90,93,96,98,100,103,104,105,106,107,106,105,104,101,98,94,89,83,76,67,57,46,33,35,37,39,41, 43,46,48,51,53,56,59,62,65,68,72,75,79,83,86,91,95,99,104,108,113,118,123,129,135,140,146,153,159,166,172,179,187,194,202,210,218,227,236,245,254,264,274,284,295,306,317,328,340,352,365,378,391,405,419,433,448,463,479,495,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511 //linear1 - ramp copied from K9.3-tintramp-fet PWM1_LEVELS with the drop off as FET comes in removed.
//#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,17,26,36,45,55,65,76,85,95,106,117,127,138,149,160,172,183,195,207,219,231,243,255,267,270,293,306,320,333 //FET - ramp copied from K9.3-219 PWM2_LEVELS and adjusted for dynamic PWM. PWM_TOP is 511 for every level the FET is used (121+) so we can just half the original value
//#define PWM3_LEVELS 1,1,1,2,2,3,3,4,4,5,5,6,7,8,9,10,11,12,13,15,16,17,27,29,32,34,37,40,43,46,49,53,56,59,63,66,70,73,77,80,83,87,90,93,96,98,100,103,104,105,106,107,106,105,104,101,98,94,89,83,76,67,57,46,33,35,37,39,41, 43,46,48,51,53,56,59,62,65,68,72,75,79,83,86,91,95,99,104,108,113,118,123,129,135,140,146,153,159,166,172,179,187,194,202,210,218,227,236,245,254,264,274,284,295,306,317,328,340,352,365,378,391,405,419,433,448,463,479,495,511, 511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511 //linear2 - copied from linear1 then manually tuned a bit to resemble the original's shape more
//#define PWM_TOPS 16383,13233,9780,13825,9592,13434,9971,12020,12899,13192,13149,12898,12507,12022,12665,11981,12180,11421,11392,11246,11017,10730,10825,10433,10364,9926,9766,9564,9331,9075,8805,8692,8394,8095,7927,7625,7438,7142,6947,6664,6392,6202,5945,5699,5464,5186,4925,4726,4450,4194,3956,3734,3462,3212,2982,2717,2475,2230,1985,1741,1500,1244,996,755,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511 //copied from K9.3-tintramp-fet
*/

#define DEFAULT_LEVEL 70
#undef MAX_1x7135
#define MAX_1x7135 130

#undef RAMP_SMOOTH_FLOOR
#define RAMP_SMOOTH_FLOOR 10  // level 1 is unreliable (?)
#undef RAMP_SMOOTH_CEIL
#define RAMP_SMOOTH_CEIL  130
// 10, 30, 50, [70], 90, 110, [130]
#undef RAMP_DISCRETE_FLOOR
#define RAMP_DISCRETE_FLOOR 10
#undef RAMP_DISCRETE_CEIL
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_STEPS
#define RAMP_DISCRETE_STEPS 7

// safe limit highest regulated power (no FET or turbo)
#undef SIMPLE_UI_FLOOR
#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_CEIL RAMP_DISCRETE_CEIL
#undef SIMPLE_UI_STEPS
#define SIMPLE_UI_STEPS 5

// stop panicking at ~2000 lm
#undef THERM_FASTER_LEVEL
#define THERM_FASTER_LEVEL 130
#undef MIN_THERM_STEPDOWN
#define MIN_THERM_STEPDOWN 65  // should be above highest dyn_pwm level

// speed up party strobe; the FET is really fast
#undef PARTY_STROBE_ONTIME

