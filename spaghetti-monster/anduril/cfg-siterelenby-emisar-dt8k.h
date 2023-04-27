//copied from cfg-noctigon-kr4.h

// Noctigon KR4 config options for Anduril
// (and Emisar D4v2.5, which uses KR4 driver plus a button LED)
#define MODEL_NUMBER "0211"
#include "hwdef-Noctigon_KR4.h"
#include "hank-cfg.h"
// ATTINY: 1634

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
// the aux LEDs are front-facing, so turn them off while main LEDs are on
//#define USE_AUX_RGB_LEDS_WHILE_ON
// it also has an independent LED in the button (D4v2.5 titanium/brass only)
#define USE_BUTTON_LED
// TODO: the whole "indicator LED" thing needs to be refactored into
//       "aux LED(s)" and "button LED(s)" since they work a bit differently
// enabling this option breaks the button LED on D4v2.5
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif


// brightness w/ SST-20 4000K LEDs:
// 0/1023: 0.35 lm
// 1/1023: 2.56 lm
// max regulated: 1740 lm
// FET: ~3700 lm
#define RAMP_LENGTH 150
#define USE_DYN_PWM
// nice low lows, but might have visible ripple on some lights:
// maxreg at 130, dynamic PWM: level_calc.py 5.01 2 149 7135 1 0.3 1740 FET 1 10 3190 --pwm dyn:64:16384:255
// (plus one extra level at the beginning for moon)
#define PWM1_LEVELS 0,1,1,2,2,3,4,5,6,7,8,9,11,12,14,16,17,19,22,24,26,29,31,34,37,40,43,46,49,53,56,60,63,67,71,74,78,82,86,89,93,96,99,103,105,108,110,112,114,115,116,116,115,114,112,109,106,101,95,89,81,71,60,48,34,19,20,21,22,23,24,26,27,28,30,31,32,34,36,37,39,41,43,45,47,49,51,53,56,58,61,63,66,69,72,75,78,81,84,88,91,95,99,103,107,111,115,119,124,129,133,138,143,149,154,159,165,171,177,183,189,196,203,210,217,224,231,239,247,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,20,30,41,52,63,75,87,99,112,125,138,151,165,179,194,208,224,239,255
#define PWM_TOPS 16383,16383,11750,14690,9183,12439,13615,13955,13877,13560,13093,12529,13291,12513,12756,12769,11893,11747,12085,11725,11329,11316,10851,10713,10518,10282,10016,9729,9428,9298,8971,8794,8459,8257,8043,7715,7497,7275,7052,6753,6538,6260,5994,5798,5501,5271,5006,4758,4525,4268,4030,3775,3508,3263,3010,2752,2517,2256,1998,1763,1512,1249,994,749,497,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
// less ripple, but lows are a bit higher than ideal:
// maxreg at 130, dynamic PWM: level_calc.py 5.01 2 149 7135 1 0.3 1740 FET 1 10 3190 --pwm dyn:64:4096:255
// (plus one extra level at the beginning for moon)
//#define PWM1_LEVELS 0,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,6,7,8,8,9,10,11,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,32,33,33,34,34,34,34,34,34,33,32,31,30,28,26,24,21,19,20,21,22,23,24,26,27,28,30,31,32,34,36,37,39,41,43,45,47,49,51,53,56,58,61,63,66,69,72,75,78,81,84,88,91,95,99,103,107,111,115,119,124,129,133,138,143,149,154,159,165,171,177,183,189,196,203,210,217,224,231,239,247,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
//#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,20,30,41,52,63,75,87,99,112,125,138,151,165,179,194,208,224,239,255
//#define PWM_TOPS 4095,4095,3760,3403,3020,2611,2176,3582,3062,2515,1940,3221,2761,2283,2998,2584,3004,2631,2899,2555,2735,2836,2538,2606,2636,2638,2387,2382,2361,2328,2286,2238,2185,2129,2070,2010,1949,1887,1826,1766,1706,1648,1591,1536,1482,1429,1379,1329,1242,1199,1122,1084,1016,953,895,842,791,723,659,602,549,482,422,367,302,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#define MAX_1x7135 130
#define DEFAULT_LEVEL 50
#define HALFSPEED_LEVEL 12
#define QUARTERSPEED_LEVEL 4

//#define RAMP_SMOOTH_FLOOR 11  // low levels may be unreliable
//#define RAMP_SMOOTH_CEIL  130
// 11 30 [50] 70 90 110 [130]
//#define RAMP_DISCRETE_FLOOR 11
//#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// safe limit ~30% power / ~1300 lm (can sustain 900 lm)
//#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
//#define SIMPLE_UI_CEIL 120
//#define SIMPLE_UI_STEPS 5

// stop panicking at ~1300 lm
#define THERM_FASTER_LEVEL 120
#define MIN_THERM_STEPDOWN 66  // must be > end of dynamic PWM range
// no longer needed, after switching to dynamic PWM
//#define THERM_NEXT_WARNING_THRESHOLD 16  // accumulate less error before adjusting
//#define THERM_RESPONSE_MAGNITUDE 128  // bigger adjustments

// slow down party strobe; this driver can't pulse for 1ms or less
// (only needed on no-FET build)
//#define PARTY_STROBE_ONTIME 2

#define THERM_CAL_OFFSET 5

// the power regulator is a bit slow, so push it harder for a quick response from off
#define DEFAULT_JUMP_START_LEVEL 21
#define BLINK_BRIGHTNESS DEFAULT_LEVEL
#define BLINK_ONCE_TIME 12

// can't reset the normal way because power is connected before the button
#define USE_SOFT_FACTORY_RESET

///////////////////////////////////////////////////////////

//disable simple UI by default
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define DEFAULT_LEVEL 50

#define SIMPLE_UI_FLOOR 11
#define SIMPLE_UI_CEIL 100
#define SIMPLE_UI_STEPS 5
#define USE_SIMPLE_UI_RAMPING_TOGGLE
#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

#undef RAMP_SMOOTH_FLOOR
#define RAMP_SMOOTH_FLOOR 1
#undef RAMP_SMOOTH_CEIL
#define RAMP_SMOOTH_CEIL  150
#undef RAMP_DISCRETE_FLOOR
#define RAMP_DISCRETE_FLOOR 1
#undef RAMP_DISCRETE_CEIL
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_STEPS
#define RAMP_DISCRETE_STEPS 10

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
#define RGB_LED_OFF_DEFAULT 0x20 //high, red
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#define RAMP_STYLE 0 //smooth ramp default

//setup memory defaults
#define DEFAULT_MANUAL_MEMORY_TIMER 30
#define DEFAULT_MANUAL_MEMORY 50

//autolock defaults
#define USE_AUTOLOCK
#define DEFAULT_AUTOLOCK_TIME 30

#define BLINK_AT_RAMP_MIDDLE

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#define USE_3H_TURBO_FROM_LOCK
#define MOMENTARY_WHEN_LOCKED_DELAY 1

#define DEFAULT_2C_STYLE 1  // 1: 2C for turbo. 2: 2C for top of ramp, or turbo if already ramped to top
#define DEFAULT_2C_STYLE_SIMPLE 2 //same for simple UI
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

#undef DISABLE_MANUAL_MEMORY_ENTRY_VALUE
#define DISABLE_MANUAL_MEMORY_ENTRY_VALUE 3

#define BLINK_NUMBERS_WITH_AUX //enables entire feature
#define BLINK_NUMBERS_WITH_AUX_DEFAULT_SETTING 2 //1: aux low, 2: aux high, 3+ main emitter ramp level
#define BLINK_NUMBERS_WITH_AUX_COLOUR 0x14 //cyan
/*
    0b00000001,  // 0: red: high 0x01
    0b00000101,  // 1: yellow: 0x05
    0b00000100,  // 2: green: 0x04
    0b00010100,  // 3: cyan: 0x14
    0b00010000,  // 4: blue: 0x10
    0b00010001,  // 5: purple: 0x11
    0b00010101,  // 6: white: 0x15
*/

#define USE_LOW_VOLTAGE_WARNING    //enable feature
#define VOLTAGE_WARN_DELAY_TICKS 40     //TODO: figure this out properly. (makes sense if it's 50% in awake and 50% in asleep state). 40 = ~5s
#define VOLTAGE_WARN_MAX_TICKS 500      //stop warning after this many ticks
#define VOLTAGE_WARN_HIGH_RAMP_LEVEL 75 //level above which we expect some voltage drop that could make battery appear low for a while when switched off
