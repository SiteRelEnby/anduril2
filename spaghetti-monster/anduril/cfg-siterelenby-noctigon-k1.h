//copied from cfg-noctigon-k1.h

// Noctigon K1 config options for Anduril
//#define MODEL_NUMBER "0251"
#define MODEL_NUMBER "6903"
#include "hwdef-Noctigon_K1.h"
#include "hank-cfg.h"
// ATTINY: 1634

// this light can safely run a bit hotter than most
#undef DEFAULT_THERM_CEIL
#define DEFAULT_THERM_CEIL 55

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
#define USE_AUX_RGB_LEDS_WHILE_ON
//#define USE_INDICATOR_LED_WHILE_RAMPING
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif
#ifdef RGB_LED_OFF_DEFAULT
#undef RGB_LED_OFF_DEFAULT
#endif
#ifdef RGB_LED_LOCKOUT_DEFAULT
#undef RGB_LED_LOCKOUT_DEFAULT
#endif
#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

// ../../bin/level_calc.py cube 1 150 7135 1 4 1300
// (with max_pwm set to 1023)
// (level 0 flickers and isn't relevant on a thrower, so it's omitted)
#define RAMP_LENGTH 150
#define PWM1_LEVELS 1,1,2,2,3,3,4,4,5,6,6,7,8,9,10,11,12,13,14,15,16,17,18,20,21,23,24,26,27,29,31,32,34,36,38,40,43,45,47,49,52,54,57,60,62,65,68,71,74,77,81,84,87,91,95,98,102,106,110,114,118,122,127,131,136,141,145,150,155,160,166,171,176,182,188,193,199,205,211,218,224,231,237,244,251,258,265,272,280,287,295,303,310,319,327,335,344,352,361,370,379,388,397,407,416,426,436,446,457,467,477,488,499,510,521,533,544,556,568,580,592,604,617,629,642,655,668,682,695,709,723,737,751,766,781,795,810,826,841,857,872,888,904,921,937,954,971,988,1005,1023
#define MAX_1x7135 50

// the entire ramp is regulated; don't blink halfway up
#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif

// don't slow down at low levels; this isn't that sort of light
// (it needs to stay at full speed for the 10-bit PWM to work)
#ifdef USE_DYNAMIC_UNDERCLOCKING
#undef USE_DYNAMIC_UNDERCLOCKING
#endif

#define RAMP_SMOOTH_FLOOR 1
#define RAMP_SMOOTH_CEIL  150
// 10, 30, [50], 70, 90, 110, 130
#define RAMP_DISCRETE_FLOOR 1
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 10

// safe limit ~75% power
#define SIMPLE_UI_FLOOR 10
#define SIMPLE_UI_CEIL 120
#define SIMPLE_UI_STEPS 5
#define USE_SIMPLE_UI_RAMPING_TOGGLE
#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

//disable simple UI by default
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0


// make candle mode wobble more
#define CANDLE_AMPLITUDE 32

// stop panicking at ~70% power or ~600 lm
#define THERM_FASTER_LEVEL 130

#define THERM_RESPONSE_MAGNITUDE 32  // smaller adjustments, this host changes temperature slowly
#define THERM_NEXT_WARNING_THRESHOLD 32  // more error tolerance before adjusting

// slow down party strobe; this driver can't pulse for 1ms or less
#define PARTY_STROBE_ONTIME 2

#define THERM_CAL_OFFSET 5

/////////////////////////////////////////////////////////////

//0x00 = off    Low     High    Blinking
//R             0x10    0x20    0x30
//R+G           0x11    0x21    0x31
//G             0x12    0x22    0x32
//G+B           0x13    0x23    0x33
//B             0x14    0x24    0x34
//R+B           0x15    0x25    0x35
//R+G+B         0x16    0x26    0x36
//Disco         0x17    0x27    0x37
//Rainbow       0x18    0x28    0x38
//Voltage       0x19    0x29    0x39
#define RGB_LED_OFF_DEFAULT 0x27 //high, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#define TICK_DURING_STANDBY

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_RELEASE_T
#define B_TIMING_OFF B_TIMEOUT_T

//setup memory defaults
#define DEFAULT_MANUAL_MEMORY_TIMER 60
#define DEFAULT_MANUAL_MEMORY 50

//autolock defaults
#define USE_AUTOLOCK
#define DEFAULT_AUTOLOCK_TIME 60

#undef RGB_LED_OFF_DEFAULT
#undef RGB_LED_LOCKOUT_DEFAULT
//setup aux properly
//0x00 = off    Low     High    Blinking
//R             0x10    0x20    0x30
//R+G           0x11    0x21    0x31
//G             0x12    0x22    0x32
//G+B           0x13    0x23    0x33
//B             0x14    0x24    0x34
//R+B           0x15    0x25    0x35
//R+G+B         0x16    0x26    0x36
//Disco         0x17    0x27    0x37
//Rainbow       0x18    0x28    0x38
//Voltage       0x19    0x29    0x39
#define RGB_LED_OFF_DEFAULT 0x27 //high, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T
#define USE_FIREWORK_MODE

#define MOMENTARY_WHEN_LOCKED_DELAY 2

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
#define USE_SIMPLE_UI_RAMPING_TOGGLE
#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

#define USE_BEACON_ON_CONFIG
