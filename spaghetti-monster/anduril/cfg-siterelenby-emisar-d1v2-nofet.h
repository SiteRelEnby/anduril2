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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

#define NUM_MAIN_CHANNELS 1
#include "button-mapping-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading
