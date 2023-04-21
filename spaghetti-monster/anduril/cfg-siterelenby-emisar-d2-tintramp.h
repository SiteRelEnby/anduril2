// based on cfg-emisar-d4sv2-tintramp.h

// Emisar D4S V2 tint-ramping config options for Anduril (based on Noctigon K9.3)
#define MODEL_NUMBER "0135"
#include "hwdef-Emisar_D4Sv2-tintramp.h"
#include "hank-cfg.h"
// ATTINY: 1634

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
// the aux LEDs are front-facing, so turn them off while main LEDs are on
// it also has an independent LED in the button
#define USE_BUTTON_LED
// TODO: the whole "indicator LED" thing needs to be refactored into
//       "aux LED(s)" and "button LED(s)" since they work a bit differently
// enabling this option breaks the button LED on D4v2.5
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

// has two channels of independent LEDs
#define USE_TINT_RAMPING
// how much to increase total brightness at middle tint
// (0 = 100% brightness, 64 = 200% brightness)
#define TINT_RAMPING_CORRECTION 0  // none, linear regulator doesn't need it

// main LEDs
//   output: unknown, 2000 lm?
//   FET: absent / unused?
// 2nd LEDs
//   output: unknown, 2000 lm?
#define RAMP_LENGTH 150
// abstract ramp (power is split between both sets of LEDs)
// 1-130: 0 to 100% power
// level_calc.py 5.01 1 130 7135 2 0.2 2000 --pwm dyn:64:16383:511
// 131 to 150: 101% to 200% power
// level_calc.py 6.44 1 150 7135 1 0.2 2000 --pwm dyn:74:16383:1022
#define PWM1_LEVELS 2,2,2,3,3,4,4,5,6,7,8,9,10,11,13,14,16,17,19,21,23,25,28,30,33,35,38,41,44,47,50,54,57,60,64,67,71,74,78,81,84,88,91,94,97,99,101,103,105,106,107,107,107,106,105,102,99,95,90,84,77,68,58,47,34,36,38,40,42,44,47,49,52,54,57,60,63,66,69,73,76,80,83,87,91,96,100,104,109,114,119,124,130,135,141,147,153,160,166,173,180,187,195,203,211,219,228,236,245,255,264,274,285,295,306,317,329,340,353,365,378,391,405,419,433,448,463,479,495,511,530,550,570,591,612,634,657,680,705,730,755,782,809,837,865,895,925,957,989,1022
#define PWM_TOPS 16383,13234,9781,13826,9593,13434,9973,12021,12900,13193,13150,12899,12508,12023,12666,11982,12181,11422,11393,11247,11018,10731,10826,10434,10365,9927,9767,9565,9332,9076,8806,8693,8395,8096,7928,7626,7439,7143,6948,6665,6393,6203,5946,5700,5465,5187,4926,4681,4451,4195,3957,3700,3463,3213,2983,2718,2476,2231,1986,1742,1501,1245,997,756,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511,511
#define DEFAULT_LEVEL 70
#define MAX_1x7135 150
#define HALFSPEED_LEVEL 10
#define QUARTERSPEED_LEVEL 2

#define USE_MANUAL_MEMORY_TIMER_FOR_TINT
//#define DEFAULT_MANUAL_MEMORY        DEFAULT_LEVEL
//#define DEFAULT_MANUAL_MEMORY_TIMER  10

//#define RAMP_SMOOTH_FLOOR 10  // level 1 is unreliable (?)
//#define RAMP_SMOOTH_CEIL  130
// 10, 30, 50, [70], 90, 110, [130]
//#define RAMP_DISCRETE_FLOOR 10
//#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
//#define RAMP_DISCRETE_STEPS 7

// safe limit highest regulated power (no FET or turbo)
//#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
//#define SIMPLE_UI_CEIL RAMP_DISCRETE_CEIL
//#define SIMPLE_UI_STEPS 5

// stop panicking at ~1500 lm
#define THERM_FASTER_LEVEL 130
#define MIN_THERM_STEPDOWN 65  // should be above highest dyn_pwm level

// use the brightest setting for strobe
#define STROBE_BRIGHTNESS MAX_LEVEL
// slow down party strobe; this driver can't pulse for 1ms or less
#define PARTY_STROBE_ONTIME 2

// the default of 26 looks a bit flat, so increase it
#define CANDLE_AMPLITUDE 33

// the power regulator is a bit slow, so push it harder for a quick response from off
#define DEFAULT_JUMP_START_LEVEL 21
#define BLINK_BRIGHTNESS DEFAULT_LEVEL
#define BLINK_ONCE_TIME 12  // longer blink, since main LEDs are slow

#define THERM_CAL_OFFSET 5

#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif

// for consistency with KR4 (not otherwise necessary though)
#define USE_SOFT_FACTORY_RESET


// work around bizarre bug: lockout mode fails when set to solid color blinking
#define USE_K93_LOCKOUT_KLUDGE

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

#define RAMP_CONFIG_HOLD_EVENT EV_click9_hold
#define MANUAL_MEMORY_SAVE_CLICK_EVENT EV_10clicks

#define AUX_CONFIG_CLICK_EVENT EV_8clicks
#define AUX_CONFIG_HOLD_EVENT EV_click8_hold
#define AUX_CONFIG_HOLD_RELEASE_EVENT EV_click8_hold_release

#define CHANNEL_1_TURBO_CLICK_EVENT EV_6clicks
#define CHANNEL_1_TURBO_HOLD_EVENT EV_click6_hold
#define CHANNEL_1_TURBO_HOLD_RELEASE_EVENT EV_click6_hold_release

#define CHANNEL_2_TURBO_CLICK_EVENT EV_5clicks
#define CHANNEL_2_TURBO_HOLD_EVENT EV_click5_hold
#define CHANNEL_2_TURBO_HOLD_RELEASE_EVENT EV_click5_hold_release

#define DUALCHANNEL_2C_ALWAYS_USE_SINGLE_CHANNEL

#define CHANNEL_RAMP_ONLY_HOLD_EVENT EV_click3_hold //ramp channels only (ignores 9H config) - saves a little bit of space if you only want ramping or are using CHANNEL_SWITCH_ONLY_CLICK_EVENT as well
#define CHANNEL_RAMP_ONLY_RELEASE_EVENT EV_click3_hold_release

#define CHANNEL_SWITCH_ONLY_CLICK_EVENT EV_3clicks

//#define CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT EV_click3_hold //default channel switch configurable in 9H config
//#define CHANNEL_SWITCH_CONFIGURABLE_HOLD_RELEASE_EVENT EV_click3_hold_release //default channel switch configurable in 9H config
#undef CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT
#undef CHANNEL_SWITCH_CONFIGURABLE_HOLD_RELEASE_EVENT
#undef LOCK_FROM_ON_EVENT
#define TURBO_200_CLICK_EVENT EV_4clicks
//#define TURBO_200_MOMENTARY_HOLD_EVENT EV_click7_hold
//#define TURBO_200_MOMENTARY_RELEASE_EVENT EV_click7_hold_release
#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT_RELEASE EV_click4_hold_release
#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT EV_click4_hold

#define MOMENTARY_CLICK_EVENT_OFF MOMENTARY_CLICK_EVENT
#define MOMENTARY_CLICK_EVENT_STROBE MOMENTARY_CLICK_EVENT
#define TACTICAL_MODE_CLICK_EVENT EV_9clicks
#define TACTICAL_LEVELS 150,(RAMP_SIZE+2),100

//disable simple UI by default
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
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
#define VOLTAGE_WARN_DELAY_TICKS 40    //(makes sense if it's 50% in awake and 50% in asleep state). 40 = ~5s
#define VOLTAGE_WARN_HIGH_RAMP_LEVEL 75 //level above which we expect some voltage drop that could make battery appear low for a while when switched off

#define DEFAULT_TINT 254
