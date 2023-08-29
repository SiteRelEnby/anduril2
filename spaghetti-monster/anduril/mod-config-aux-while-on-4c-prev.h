#pragma once

// Example mod config - loads defaults, with a few extra small features:
// - Blink lock reminder
// - Configurable RGB voltage while on
// - Configurable post-off voltage brightness

//We still want to load default button mappings here, mostly. This prevents it getting loaded in anduril.c later and clobbering these tweaks
#include "mod-config-defaults.h"

//we can also #define USER_CONFIG_LOADED to stop the defaults from being loaded.
//#define USER_CONFIG_LOADED

//#undef USE_3H_CHANNEL_RAMP_TURBO_FALLTHROUGH

//now setup custom stuff
#define BLINK_LOCK_REMINDER
#ifdef USE_AUX_RGB_LEDS
  #define BLINK_LOCK_REMINDER_CHANNEL CM_AUXRED
#else
  #define BLINK_LOCK_REMINDER_CHANNEL CM_AUX
#endif

#ifdef USE_AUX_RGB_LEDS
  #define USE_AUX_WHILE_ON_CONFIG
  #define USE_AUX_RGB_LEDS_WHILE_ON
  #define EVENT_AUX_WHILE_ON_TOGGLE EV_8clicks
  #define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH 50
  #define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW 20
#endif

#define USE_3H_TURBO_FROM_LOCK

#undef LOCK_FROM_ON_EVENT
#define EVENT_PREVIOUS_CHANNEL EV_4clicks
