// Emisar D4S config options for Anduril
#include "hwdef-Emisar_D4S.h"

// the button lights up
#define USE_INDICATOR_LED
// the aux LEDs are behind the main LEDs
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif
// enable blinking indicator LED while off
#define TICK_DURING_STANDBY
#define STANDBY_TICK_SPEED 3  // every 0.128 s
#define USE_FANCIER_BLINKING_INDICATOR

#ifdef RAMP_LENGTH
#undef RAMP_LENGTH
#endif

#define RAMP_LENGTH 150

// 3x7135 + FET
// ../../bin/level_calc.py 2 150 7135 1 11.2 450 FET 1 10 4000
// (with a x**9 curve instead of x**3)
// (because it made the ramp look better than accurate values)
#define PWM1_LEVELS 1,1,2,2,3,3,4,4,5,5,6,6,7,8,8,9,10,10,11,12,13,14,15,16,17,18,19,21,22,23,25,26,27,29,31,32,34,36,38,40,42,44,46,49,51,54,56,59,62,65,68,71,74,78,81,85,89,93,97,101,106,110,115,120,125,130,136,141,147,153,160,166,173,180,187,195,202,210,219,227,236,245,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,5,7,8,10,11,13,14,16,18,19,21,23,25,27,29,31,34,36,38,41,43,46,48,51,54,57,60,63,66,69,72,76,79,83,87,91,95,99,103,107,112,116,121,126,131,136,141,146,152,158,163,169,175,182,188,195,202,209,216,223,231,239,247,255
#define MAX_1x7135 83
#define HALFSPEED_LEVEL 13
#define QUARTERSPEED_LEVEL 6

// ceiling is level 120/150
#define RAMP_SMOOTH_CEIL (MAX_LEVEL*4/5)

// thermal regulation parameters
#ifdef MIN_THERM_STEPDOWN
#undef MIN_THERM_STEPDOWN  // this should be lower, because 3x7135 instead of 1x7135
#endif
#define MIN_THERM_STEPDOWN 60  // lowest value it'll step down to
#define THERM_FASTER_LEVEL (RAMP_SIZE-20)  // don't throttle back faster when high

// no need to be extra-careful on this light
#ifdef THERM_HARD_TURBO_DROP
#undef THERM_HARD_TURBO_DROP
#endif

#define THERMAL_WARNING_SECONDS 3
#define THERMAL_UPDATE_SPEED 2
#define THERM_PREDICTION_STRENGTH 4
