// gChart's custom FET+1 driver config options for Anduril
#define MODEL_NUMBER "1618" // Golden Ratio... because I can
#include "hwdef-gchart-fet1-t1616.h"
// ATTINY: 1616

// the button lights up
#define USE_INDICATOR_LED
// the button is visible while main LEDs are on
#define USE_INDICATOR_LED_WHILE_RAMPING
// enable blinking indicator LED while off
#define TICK_DURING_STANDBY

#undef BLINK_AT_RAMP_MIDDLE

// Mostly borrowed from the D4 for now
#define RAMP_LENGTH 150
#define PWM1_LEVELS 1,1,2,2,3,3,4,4,5,6,7,8,9,10,12,13,14,15,17,19,20,22,24,26,29,31,34,36,39,42,45,48,51,55,59,62,66,70,75,79,84,89,93,99,104,110,115,121,127,134,140,147,154,161,168,176,184,192,200,209,217,226,236,245,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,5,7,8,9,11,12,14,15,17,19,20,22,24,25,27,29,31,33,35,37,39,41,43,45,48,50,52,55,57,59,62,64,67,70,72,75,78,81,84,87,90,93,96,99,102,105,109,112,115,119,122,126,129,133,137,141,144,148,152,156,160,165,169,173,177,182,186,191,195,200,205,209,214,219,224,229,234,239,244,250,255
#define MAX_1x7135 65
#define HALFSPEED_LEVEL 14
#define QUARTERSPEED_LEVEL 6

#define RAMP_SMOOTH_FLOOR 1
#define RAMP_SMOOTH_CEIL 120
// 10, 28, 46, [65], 83, 101, 120
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// stop panicking at ~30% power
#define THERM_FASTER_LEVEL 105

// enable 2 click turbo
#define USE_2C_MAX_TURBO
