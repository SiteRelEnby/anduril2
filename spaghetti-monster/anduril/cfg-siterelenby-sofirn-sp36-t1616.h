// Sofirn SP36 (small Q8) config options for Anduril using the Attiny1616
// Copyright (C) 2021-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-sofirn-sp36-t1616.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1616
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 1 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#undef USE_AUX_RGB_LEDS
#undef USE_AUX_RGB_LEDS_WHILE_ON

//#undef DEFAULT_CHANNEL_MODE
//#undef DEFAULT_BLINK_CHANNEL
//#undef BLINK_ONCE_TIME
//#define DEFAULT_CHANNEL_MODE CM_MAIN
//#define DEFAULT_BLINK_CHANNEL CM_AUX

#undef BLINK_ONCE_TIME
#define BLINK_ONCE_TIME 8

#undef RAMP_SMOOTH_FLOOR
#define RAMP_SMOOTH_FLOOR 2

#define RAMP_SMOOTH_CEIL  150
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 11

#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL 150
#define SIMPLE_UI_STEPS 5

#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 150,75,(RAMP_SIZE+2)

#ifndef BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_MIDDLE
#endif

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#ifdef LOCK_FROM_ON_EVENT
#undef LOCK_FROM_ON_EVENT
#endif

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#define DEFAULT_AUTOLOCK_TIME 60

// low: 1
// high: 2
// blinking (3)
#ifdef INDICATOR_LED_DEFAULT_MODE
#undef INDICATOR_LED_DEFAULT_MODE
#define INDICATOR_LED_DEFAULT_MODE ((1<<2) + 2)
#endif
