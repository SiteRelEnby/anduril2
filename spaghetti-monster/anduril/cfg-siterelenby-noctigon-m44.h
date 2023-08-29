// Noctigon M44 config options for Anduril
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-noctigon-m44.h"

/////////////////////////////////////////////////////////////////////////////
#define NUM_MAIN_CHANNELS 2
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 150,75,(RAMP_SIZE+2)

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

#define DEFAULT_BLINK_CHANNEL CM_AUXCYN

#ifdef USE_AUX_RGB_LEDS_WHILE_ON
  #undef USE_AUX_RGB_LEDS_WHILE_ON //no RGB switch
#endif
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
#define DEFAULT_MANUAL_MEMORY_TIMER 60
