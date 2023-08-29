// Wurkkos TS25, modelled after the TS10 but with RGB Aux
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-wurkkos-ts25.h"

///////////////////////////////////////////////////////
#define NUM_MAIN_CHANNELS 1 //TODO: is this still needed with the refactor?
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 150,75,(RAMP_SIZE+2)

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow
#define BLINK_LOCK_REMINDER
#undef LOCK_FROM_ON_EVENT

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#define DEFAULT_AUTOLOCK_TIME 60
