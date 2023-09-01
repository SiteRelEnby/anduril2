// Noctigon DM11-noFET config options for Anduril
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-noctigon-dm11-nofet.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1634
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 1 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
#define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#undef DEFAULT_JUMP_START_LEVEL
#define DEFAULT_JUMP_START_LEVEL 15

#undef BLINK_ONCE_TIME
#define BLINK_ONCE_TIME 10

#undef RAMP_SMOOTH_FLOOR
#define RAMP_SMOOTH_FLOOR 3

#define RAMP_SMOOTH_CEIL  150
// 10, 30, 50, [70], 90, 110, [130]
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

#define DEFAULT_BLINK_CHANNEL CM_AUXWHT

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
