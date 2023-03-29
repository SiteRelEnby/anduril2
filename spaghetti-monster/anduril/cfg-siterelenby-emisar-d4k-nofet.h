//based on cfg-noctigon-kr4-nofet.h

// Noctigon KR4 (fetless) config options for Anduril
// (and Noctigon KR1)
// (and Emisar D4v2 E21A, a.k.a. "D4v2.5")
#include "cfg-noctigon-kr4.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0212"
// ATTINY: 1634

// brightness w/ SST-20 4000K LEDs:
// 0/1023: 0.35 lm
// 1/1023: 2.56 lm
// max regulated: 1740 lm
#undef PWM_CHANNELS
#define PWM_CHANNELS 1
#define RAMP_LENGTH 150
// prioritize low lows, at risk of visible ripple
// level_calc.py 5.01 1 149 7135 1 0.3 1740 --pwm dyn:78:16384:255
#undef PWM1_LEVELS
#define PWM1_LEVELS 0,1,1,1,2,3,3,4,5,6,7,8,9,10,11,13,14,16,17,19,21,23,25,27,29,31,34,36,39,42,44,47,50,53,57,60,63,67,70,74,77,81,85,88,92,96,99,103,107,110,113,117,120,123,126,128,130,133,134,136,137,137,137,137,136,135,133,130,126,122,117,111,104,96,87,76,65,52,38,22,23,25,26,27,28,29,30,32,33,34,36,37,39,40,42,43,45,47,49,51,53,55,57,59,61,63,66,68,70,73,76,78,81,84,87,90,93,96,99,103,106,110,113,117,121,125,129,133,137,142,146,151,155,160,165,170,175,181,186,192,197,203,209,215,222,228,234,241,248,255
#undef PWM2_LEVELS
#undef PWM_TOPS
#define PWM_TOPS 16383,16383,12404,8140,11462,14700,11041,12947,13795,14111,14124,13946,13641,13248,12791,13418,12808,13057,12385,12428,12358,12209,12000,11746,11459,11147,11158,10793,10708,10576,10173,9998,9800,9585,9527,9278,9023,8901,8634,8486,8216,8053,7881,7615,7440,7261,7009,6832,6656,6422,6196,6031,5819,5615,5419,5190,4973,4803,4571,4386,4179,3955,3745,3549,3340,3145,2940,2729,2513,2312,2109,1903,1697,1491,1286,1070,871,662,459,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#undef DEFAULT_LEVEL
#define DEFAULT_LEVEL 50
#undef MAX_1x7135
#define MAX_1x7135 150

#undef RAMP_SMOOTH_FLOOR
#undef RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_FLOOR
#undef RAMP_DISCRETE_CEIL
#undef RAMP_DISCRETE_STEPS

//define RAMP_SMOOTH_FLOOR 11  // low levels may be unreliable
//#define RAMP_SMOOTH_CEIL  130
// 11, 30, [50], 70, 90, 110, 130  (plus [150] on turbo)
//#define RAMP_DISCRETE_FLOOR 11
//#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
//#define RAMP_DISCRETE_STEPS 7

// safe limit ~1000 lm (can sustain 900 lm)
#undef SIMPLE_UI_FLOOR
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL RAMP_DISCRETE_CEIL


// make candle mode wobble more
#define CANDLE_AMPLITUDE 32

// slow down party strobe; this driver can't pulse for 1ms or less
// (only needed on no-FET build)
#define PARTY_STROBE_ONTIME 2

// jump start a bit higher than base driver
#undef DEFAULT_JUMP_START_LEVEL
//#define DEFAULT_JUMP_START_LEVEL 25

// stop panicking at ~1300 lm
#undef THERM_FASTER_LEVEL
#define THERM_FASTER_LEVEL 140
#undef MIN_THERM_STEPDOWN
#define MIN_THERM_STEPDOWN 80  // must be > end of dynamic PWM range

/////////////////////////////////////////////////
#define DEFAULT_LEVEL 50
#define RAMP_SMOOTH_FLOOR 1  // low levels may be unreliable
#define RAMP_SMOOTH_CEIL  130
#define RAMP_DISCRETE_FLOOR 1
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 11
#define SIMPLE_UI_FLOOR 11
#define SIMPLE_UI_CEIL RAMP_SMOOTH_CEIL
#define SIMPLE_UI_STEPS 11
#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

#undef RGB_LED_OFF_DEFAULT //Hanklight default: 0x18
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
#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#define RAMP_STYLE 0 //smooth ramp default

//setup memory defaults
#define DEFAULT_MANUAL_MEMORY_TIMER 60
#define DEFAULT_MANUAL_MEMORY 50

//autolock defaults
#define USE_AUTOLOCK
#define DEFAULT_AUTOLOCK_TIME 60

#define BLINK_AT_RAMP_MIDDLE

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#define USE_3H_TURBO_FROM_LOCK
#define MOMENTARY_WHEN_LOCKED_DELAY 1

#define USE_FIREWORK_MODE

#define USE_BEACON_ON_CONFIG
#define USE_BEACON_BRIGHTNESS_RAMP

#define MOMENTARY_CLICK_EVENT EV_12clicks
#define SUNSET_TIMER_HOLD_EVENT EV_click12_hold
#define RAMP_STYLE_TOGGLE_EVENT EV_9clicks

#define RAMP_CONFIG_HOLD_EVENT EV_click7_hold
#define MANUAL_MEMORY_SAVE_CLICK_EVENT EV_10clicks

#define AUX_CONFIG_CLICK_EVENT EV_7clicks
#define AUX_CONFIG_HOLD_EVENT EV_click7_hold
#define AUX_CONFIG_HOLD_RELEASE_EVENT EV_click7_hold

#define MOMENTARY_CLICK_EVENT_OFF MOMENTARY_CLICK_EVENT
#define MOMENTARY_CLICK_EVENT_STROBE MOMENTARY_CLICK_EVENT
#define TACTICAL_MODE_CLICK_EVENT EV_9clicks
#define TACTICAL_LEVELS 150,(RAMP_SIZE+2),100

//disable simple UI by default
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
#undef DISABLE_MANUAL_MEMORY_ENTRY_VALUE
#define DISABLE_MANUAL_MEMORY_ENTRY_VALUE 3
