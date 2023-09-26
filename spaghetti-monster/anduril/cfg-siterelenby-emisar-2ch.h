// Emisar 2-channel generic config options for Anduril
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-emisar-2ch.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1634
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 2 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
#ifndef USE_AUX_RGB_LEDS_WHILE_ON
  #define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage
#endif
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#ifndef BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_MIDDLE
#endif

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#undef RGB_LED_OFF_DEFAULT
#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#undef RGB_LED_LOCKOUT_DEFAULT
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#ifdef DEFAULT_BLINK_CHANNEL
  #undef DEFAULT_BLINK_CHANNEL
  #define DEFAULT_BLINK_CHANNEL CM_AUXCYN
#endif

#ifndef USE_AUX_RGB_LEDS_WHILE_ON
  #define USE_AUX_RGB_LEDS_WHILE_ON
#endif
#ifndef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW
  #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
#endif
#ifndef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH
  #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 70
#endif
#ifndef BLINK_LOCK_REMINDER
  #define BLINK_LOCK_REMINDER
#endif

#ifdef LOCK_FROM_ON_EVENT
  #undef LOCK_FROM_ON_EVENT
#endif

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#undef B_TIMING_ON
#undef B_TIMING_OFF
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T
