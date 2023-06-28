// Emisar D1v2 (linear only, no DDFET) config options for Anduril
// (2022 re-issue / update of old D1)
// Copyright (C) 2022-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// ATTINY: 1634
// similar to a Noctigon KR4, sort of
#include "cfg-noctigon-kr4-nofet.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0125"

// some models use a simple button LED, others use RGB...
// ... so include support for both
#define USE_BUTTON_LED
// the aux LEDs are in the button, so use them while main LEDs are on
#define USE_AUX_RGB_LEDS
#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_INDICATOR_LED_WHILE_RAMPING

// safe limit: same as regular ramp
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_CEIL RAMP_SMOOTH_CEIL

///////////////////////////////////////////
#define DEFAULT_BLINK_CHANNEL CM_AUXWHT
#define USE_CONFIG_COLORS

#define USE_AUX_WHILE_ON_CONFIG
#define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW 15
#define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH 45

#define EVENT_AUX_WHILE_ON_TOGGLE EV_8clicks


//testing...
//#define B_TIMING_ON B_TIMEOUT_T
