#pragma once

#include "cfg-fw3x-lume1.h"
// the following line always needs to be included in the *base* build target for build.sh to work (TODO: fix?)
// ATTINY: 1634
//////////////////////////////////////////////////////////////////////////////
//
// Define some vars that are needed for the mod config to set stuff up properly
#define NUM_MAIN_CHANNELS 1 //tell it this light has 2 'main' channels (for setting up shortcuts etc)
//#define USE_AUX_RGB_LEDS_WHILE_ON //this needs to be set to enable configurable RGB voltage //no point in this light as there's no switch LED
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

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
