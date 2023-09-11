// Emisar D4K 3-channel config options for Anduril
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#define MODEL_NUMBER "0151"
#include "cfg-emisar-d4k-3ch.h"
// ATTINY: 1634
/////////////////////////////////////////////////////////////////
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 3 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
#define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading


//enum channel_modes_e {
//    CM_MAIN2 = 0,
//    CM_LED3,
//    CM_LED4,
//    CM_ALL,
//    CM_BLEND34A,  // 8 / [16+16]
//    CM_BLEND34B,  // 16 / [16+8]
//    CM_HSV,
//    CM_AUTO3,
//    RGB_AUX_ENUMS
//};
// enable all main modes (CM_BLEND34B, CM_HSV, and CM_AUTO3 default to disabled)
#define CHANNEL_MODES_ENABLED 0b0000000011111111

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#define DEFAULT_BLINK_CHANNEL CM_AUXCYN

#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 25
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 75
#define BLINK_LOCK_REMINDER

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

