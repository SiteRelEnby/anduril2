// Wurkkos TS10 (originally used Sofirn SP36-t1616 firmware) config options for Anduril using the Attiny1616
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-wurkkos-ts10.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1616
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 1 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
//#define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage //single-colour aux only
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#define BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_CEIL

#define DEFAULT_2C_STYLE_SIMPLE 2
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define DEFAULT_LEVEL 50

#define TACTICAL_LEVELS 150,80,(RAMP_SIZE+2)

#define USE_3H_TURBO_FROM_LOCK

#define DEFAULT_MANUAL_MEMORY 50
#define DEFAULT_MANUAL_MEMORY_TIMER 30

#define DEFAULT_AUTOLOCK_TIME 30

#undef INDICATOR_LED_DEFAULT_MODE
//off high (2), lockout low (1)
//TODO: starryalley aux patterns
//left shift 4 bits instead of 2 because there are more aux modes than default
//#define INDICATOR_LED_DEFAULT_MODE ((1<<4) + 2)

//default aux patterns, but low (1) for lock, high (2) for unlocked
#define INDICATOR_LED_DEFAULT_MODE ((1<<2) + 2)
