// Noctigon K1 12V config options for Anduril
// Copyright (C) 2019-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

//copied from K1-12V. Other boost D1s use the DM11 boost fw, but B35AM came with K1 for some reason. Not sure why but keeping it that way.

#include "cfg-noctigon-k1-12v.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1634
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 1 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
#define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

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

// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#undef B_TIMING_ON
#undef B_TIMING_OFF
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

