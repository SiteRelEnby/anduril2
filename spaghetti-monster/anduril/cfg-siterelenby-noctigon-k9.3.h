// Noctigon K9.3 config options for Anduril
// Copyright (C) 2020-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-noctigon-k9.3.h"

/*
#define MODEL_NUMBER "0261"
#include "hwdef-emisar-2ch-fet.h"
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

// channel modes...
// CM_CH1, CM_CH2, CM_BOTH, CM_BLEND, CM_AUTO
// enable max brightness out of the box
#define DEFAULT_CHANNEL_MODE           CM_BLEND

#define USE_CONFIG_COLORS

// blink numbers on the main LEDs by default (but allow user to change it)
#define DEFAULT_BLINK_CHANNEL  CM_BLEND

#define POLICE_COLOR_STROBE_CH1        CM_CH1
#define POLICE_COLOR_STROBE_CH2        CM_CH2

// how much to increase total brightness at middle tint
// (0 = 100% brightness, 64 = 200% brightness)
#define TINT_RAMPING_CORRECTION 0  // none, linear regulator doesn't need it


// main LEDs
//   max regulated: ~1750 lm
//   FET: ~8000 lm
// 2nd LEDs
//   max regulated: ~1500 lm
#define RAMP_SIZE 150

// linear+FET ramp: maxreg at 110/150
// level_calc.py 4.3398 2 150 7135 1 0.1 1750 FET 1 10 6000 --pwm dyn:63:4096:255:3 --clock 8:16:0
// linear segment
#define PWM1_LEVELS 1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5,5,5,6,6,7,7,7,8,8,8,9,9,9,10,10,10,11,11,11,12,12,12,13,13,13,14,14,14,15,15,16,17,17,18,19,20,21,22,23,25,27,28,30,32,33,35,37,39,42,44,46,49,51,54,57,59,62,65,69,72,75,79,83,87,91,95,99,103,108,113,118,123,128,133,139,145,151,157,163,169,176,183,190,197,205,213,221,229,237,246,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
// DD FET segment
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,25,29,34,38,43,48,53,58,64,69,75,80,86,92,98,105,111,118,124,131,138,145,153,160,168,176,184,192,201,209,218,227,236,245,255
// PWM TOPS values
#define PWM3_LEVELS 4096,3746,3391,3029,2662,2293,1922,1553,2591,2163,1745,1341,1986,1836,1526,1901,1644,1402,1603,1400,1212,1329,1170,1232,1097,974,1012,907,812,836,754,681,695,631,574,582,532,487,491,451,415,417,386,356,357,331,307,308,286,286,284,265,264,261,258,255,251,247,253,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

// linear-only ramp
// level_calc.py 3.11 1 150 7135 1 0.1 1750 --pwm dyn:64:4096:255:3 --clock 8:16:0
#define PWM4_LEVELS 1,1,1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,6,6,6,7,7,7,8,8,8,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,14,14,14,15,15,16,17,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,33,34,35,37,38,39,41,42,44,45,47,48,50,52,53,55,57,59,61,63,65,67,69,71,73,75,77,79,82,84,86,89,91,94,97,99,102,105,107,110,113,116,119,122,125,128,132,135,138,141,145,148,152,156,159,163,167,170,174,178,182,186,190,195,199,203,208,212,217,221,226,230,235,240,245,250,255
// PWM_TOPS values for linear-only ramp
#define PWM5_LEVELS 4096,3681,3247,2794,2328,1856,2937,2393,1860,2690,2273,1875,2281,1959,1658,1893,1646,1774,1569,1381,1466,1309,1166,1224,1104,996,1033,942,858,882,810,746,687,634,586,604,561,522,487,454,425,397,409,385,362,341,321,302,311,295,279,286,271,257,263,250,255,258,246,249,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

#define DEFAULT_LEVEL      60
#define MAX_1x7135         110
#define MAX_Nx7135         MAX_1x7135
#define HALFSPEED_LEVEL    16
#define QUARTERSPEED_LEVEL 8

#define RAMP_SMOOTH_FLOOR  10  // level 1 is unreliable (?)
#define RAMP_SMOOTH_CEIL   110
// 10, 26, 43, [60], 76, 93, 110
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// 10, 35, [60], 85, 110
#define SIMPLE_UI_FLOOR  RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL   RAMP_DISCRETE_CEIL
#define SIMPLE_UI_STEPS  5

// stop panicking at ~25% power or ~1000 lm
#define THERM_FASTER_LEVEL 100
#define MIN_THERM_STEPDOWN 60  // should be above highest dyn_pwm level

#define USE_POLICE_COLOR_STROBE_MODE
#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 110,30,(RAMP_SIZE+3)  // high, low, police strobe

// use the brightest setting for strobe
#define STROBE_BRIGHTNESS MAX_LEVEL
// slow down party strobe; this driver can't pulse for 1ms or less
#define PARTY_STROBE_ONTIME 2
// TODO: change speed per channel mode
// (the FET is really fast, but the regulator is not)
//#undef PARTY_STROBE_ONTIME

// the default of 26 looks a bit flat, so increase it
#define CANDLE_AMPLITUDE 33

// the power regulator is a bit slow, so push it harder for a quick response from off
#define DEFAULT_JUMP_START_LEVEL 10
#define BLINK_BRIGHTNESS 30
#define BLINK_ONCE_TIME 12  // longer blink, since main LEDs are slow

#define THERM_CAL_OFFSET 5

// don't blink while ramping
#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif
*/

#undef DEFAULT_CHANNEL_MODE
#undef DEFAULT_BLINK_CHANNEL
#undef POLICE_COLOR_STROBE_CH1
#undef POLICE_COLOR_STROBE_CH2
#undef BLINK_ONCE_TIME
#define DEFAULT_CHANNEL_MODE CM_CH1
#define DEFAULT_BLINK_CHANNEL CM_AUXCYN

#undef BLINK_ONCE_TIME
#define BLINK_ONCE_TIME 10

#undef RAMP_SMOOTH_FLOOR
#define RAMP_SMOOTH_FLOOR 3

#define RAMP_SMOOTH_CEIL  110 //TODO: keep 110 for this light, or use 150? 110 is max regulated
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 11

// safe limit highest regulated power (no FET or turbo)
#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL 120
#define SIMPLE_UI_STEPS 5

// stop panicking at ~1500 lm
#define THERM_FASTER_LEVEL 130
#define MIN_THERM_STEPDOWN 65  // should be above highest dyn_pwm level

#define USE_POLICE_COLOR_STROBE_MODE
#define POLICE_COLOR_STROBE_CH1 CM_AUXBLU
#define POLICE_COLOR_STROBE_CH2 CM_AUXRED
#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 150,75,(RAMP_SIZE+2)

#ifndef BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_MIDDLE
#endif

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

// need to fix voltage aux when channel mode is aux
#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 70
#define BLINK_LOCK_REMINDER
//#define BLINK_LOCK_REMINDER_CHANNEL

#undef LOCK_FROM_ON_EVENT

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#define DEFAULT_AUTOLOCK_TIME 60

#define NUM_MAIN_CHANNELS 2
#include "button-mapping-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading
