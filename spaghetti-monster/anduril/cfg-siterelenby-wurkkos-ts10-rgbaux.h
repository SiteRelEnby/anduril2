#pragma once

#include "cfg-wurkkos-ts10-rgbaux.h"

// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1616
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 1 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
//#define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage //no point in this light as there's no switch LED
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#define BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_CEIL

#undef RAMP_SMOOTH_CEIL
#define RAMP_SMOOTH_CEIL 150
#undef DEFAULT_2C_STYLE
#define DEFAULT_2C_STYLE 1

#define DEFAULT_2C_STYLE_SIMPLE 2
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define DEFAULT_LEVEL 50

#define TACTICAL_LEVELS 150,80,(RAMP_SIZE+2)

#define USE_3H_TURBO_FROM_LOCK

#define DEFAULT_MANUAL_MEMORY 50
#define DEFAULT_MANUAL_MEMORY_TIMER 30

#define DEFAULT_AUTOLOCK_TIME 30

#undef RGB_LED_OFF_DEFAULT
#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#undef RGB_LED_LOCKOUT_DEFAULT
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#undef B_TIMING_ON
#undef B_TIMING_OFF
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

