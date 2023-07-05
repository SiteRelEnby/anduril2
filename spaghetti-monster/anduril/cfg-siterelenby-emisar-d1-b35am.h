// Noctigon K1 12V config options for Anduril
// Copyright (C) 2019-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

//copied from K1-12V. Other boost D1s use the DM11 boost fw, but B35AM came with K1 for some reason. Not sure why but keeping it that way.

#pragma once

#define MODEL_NUMBER "0253"
#include "hwdef-Noctigon_K1-12V.h"
#include "hank-cfg.h"
// ATTINY: 1634

// Most K1 lights can run hotter than default, but the 12V model
// is known to have issues with the driver itself getting too hot.
// This then causes the main LEDs to turn off during use, because the
// boost chip's built-in protection activates.  So try to keep the
// temperature relatively low.
#undef DEFAULT_THERM_CEIL
#define DEFAULT_THERM_CEIL 45

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_INDICATOR_LED_WHILE_RAMPING


// level_calc.py cube 1 150 7135 0 4 1300
// (with max_pwm set to 1023)
// (level 0 is usable on this light)
#define RAMP_LENGTH 150
#define PWM1_LEVELS 0,0,1,1,2,2,3,3,4,5,5,6,7,8,9,10,11,12,13,14,15,16,17,19,20,22,23,25,26,28,30,31,33,35,37,39,42,44,46,48,51,53,56,59,61,64,67,70,73,76,80,83,86,90,94,97,101,105,109,113,117,122,126,130,135,140,144,149,154,159,165,170,175,181,187,193,198,204,211,217,223,230,236,243,250,257,264,271,279,286,294,302,310,318,326,334,343,351,360,369,378,387,397,406,416,426,436,446,456,466,477,488,499,510,521,532,544,555,567,579,591,604,616,629,642,655,668,682,695,709,723,737,751,766,780,795,810,825,841,856,872,888,904,921,937,954,971,988,1005,1023
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
#define RAMP_SMOOTH_CEIL  130
// 10, 30, [50], 70, 90, 110, 130
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// safe limit ~50% power
#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL 120
#define SIMPLE_UI_STEPS 5

// make candle mode wobble more
#define CANDLE_AMPLITUDE 32

// stop panicking at ~70% power or ~600 lm
#define THERM_FASTER_LEVEL 130

#define THERM_RESPONSE_MAGNITUDE 32  // smaller adjustments, this host changes temperature slowly
#define THERM_NEXT_WARNING_THRESHOLD 32  // more error tolerance before adjusting

// slow down party strobe; this driver can't pulse for 1ms or less
#define PARTY_STROBE_ONTIME 4

#define THERM_CAL_OFFSET 5

///////////////////////////////////////////////////////////////////////////

#undef RAMP_SMOOTH_FLOOR
#undef RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_FLOOR
#undef RAMP_DISCRETE_CEIL
#undef RAMP_DISCRETE_STEPS

#define RAMP_SMOOTH_FLOOR 2  // low levels may be unreliable
#define RAMP_SMOOTH_CEIL  150
// 11, 30, [50], 70, 90, 110, 130  (plus [150] on turbo)
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 11

#undef SIMPLE_UI_FLOOR
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL 100
#define SIMPLE_UI_STEPS 3
#define USE_SIMPLE_UI_RAMPING_TOGGLE

#define CANDLE_AMPLITUDE 32

#define DEFAULT_MANUAL_MEMORY 50
#define DEFAULT_MANUAL_MEMORY_TIMER 60
#define DEFAULT_AUTOLOCK_TIME 60

#define B_TIMING_ON B_TIMEOUT_T

#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define TACTICAL_LEVELS 150,100,(RAMP_SIZE+2)

#define USE_3H_TURBO_FROM_LOCK
#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT

#define RGB_LED_OFF_DEFAULT 0x37  // blinking, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#define NUM_MAIN_CHANNELS 1
#include "button-mapping-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

