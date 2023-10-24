#pragma once

#include "cfg-blf-lantern-t1616.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1616
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 2 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#ifndef BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_MIDDLE
#endif

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

// the button lights up
#define USE_INDICATOR_LED
// the button is visible while main LEDs are on
#define USE_INDICATOR_LED_WHILE_RAMPING
// off mode: high (2)
// lockout: blinking (3)
#define INDICATOR_LED_DEFAULT_MODE ((3<<2) + 2)

// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#undef B_TIMING_ON
#undef B_TIMING_OFF
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#undef DEFAULT_CHANNEL_MODE
#define DEFAULT_CHANNEL_MODE CM_BLEND

#undef INDICATOR_LED_DEFAULT_MODE
// ((mode_lockout<<2) + mode_off)
// 0: off
// 1: low
// 2: high
// 3: blinking
#define INDICATOR_LED_DEFAULT_MODE ((1<<2) + 2)

#ifndef USE_EXTENDED_SIMPLE_UI
  #define USE_EXTENDED_SIMPLE_UI
#endif
