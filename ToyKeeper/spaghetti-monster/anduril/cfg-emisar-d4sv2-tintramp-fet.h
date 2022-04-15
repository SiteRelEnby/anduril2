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
///// copy non-FET ramp, but add FET to the top 10 levels from 141 to 150
/* old
// level_calc.py 5.01 1 140 7135 1 0.2 2000 --pwm dyn:69:16383:511
// plus a FET segment
// abstract ramp (power is split between both sets of LEDs)
// level_calc.py 2 1 10 7135 5 50.0 3000 --pwm 255
// append: ,500,482,456,420,374,318,252,178,94,0
*/
/* also old
// level_calc.py 3 1 11 7135 511 2000 5000 --pwm 1022
// append: 549,589,633,679,728,780,836,894,957,1022
//#undef PWM1_LEVELS
//#define PWM1_LEVELS 1,1,1,2,2,3,3,4,5,5,6,7,8,9,10,12,13,14,16,18,19,21,23,25,27,30,32,35,37,40,43,45,48,51,54,58,61,64,67,70,74,77,80,83,86,89,92,95,97,99,101,103,105,106,106,107,106,106,104,102,100,96,92,87,81,73,65,56,45,33,35,37,39,41,43,45,47,49,52,54,57,59,62,65,68,71,74,78,81,85,89,92,96,100,105,109,114,118,123,128,133,139,144,150,156,162,168,175,181,188,195,202,210,217,225,233,242,250,259,268,278,287,297,307,318,328,339,351,362,374,386,399,412,425,438,452,466,481,496,511,549,589,633,679,728,780,836,894,957,1022
// append: ,511,511,511,511,511,511,511,511,511,511
//#undef PWM_TOPS
//#define PWM_TOPS 16383,13469,10296,14694,10845,14620,11496,13507,14400,11954,12507,12676,12605,12376,12036,12805,12240,11650,11882,11933,11243,11155,10988,10763,10497,10569,10223,10164,9781,9646,9475,9071,8870,8652,8422,8330,8077,7823,7569,7318,7169,6919,6676,6439,6209,5986,5770,5561,5305,5063,4834,4618,4413,4180,3925,3723,3468,3264,3016,2787,2576,2333,2111,1885,1658,1412,1189,968,734,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511
*/

// prepend: 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,14,27,45,68,96,129,166,208,255
#undef DEFAULT_LEVEL
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
