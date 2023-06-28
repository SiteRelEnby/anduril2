#pragma once

//sets up some dependencies for modded functionality that have to be defined very early in the code

#if (defined(BLINK_LOCK_REMINDER) && !defined(USE_BLINK_CHANNEL))
  #define USE_BLINK_CHANNEL
#endif

#if (defined(BLINK_LOCK_REMINDER) && !defined(USE_AUX_LED_OVERRIDE))
  #define USE_AUX_LED_OVERRIDE
#endif

#if (( \
  (defined(LOCKOUT_EXIT_BLINK_CHANNEL)) || \
  (defined(AUX_CONFIG_BLINK_CHANNEL)) || \
  (defined(SIMPLE_UI_BLINK_CHANNEL)) || \
  (defined(MOMENTARY_BLINK_CHANNEL)) || \
  (defined(TACTICAL_BLINK_CHANNEL)) || \
  (defined(SAVE_MEMORY_BLINK_CHANNEL)) || \
  (defined(LOCK_BLINK_CHANNEL)) || \
  (defined(POWERON_BLINK_CHANNEL)) || \
  (defined(LOCKOUT_EXIT_BLINK_CHANNEL)) || \
  (defined(AUX_CONFIG_BLINK_CHANNEL)) || \
  (defined(SIMPLE_UI_BLINK_CHANNEL)) || \
  (defined(MOMENTARY_BLINK_CHANNEL)) || \
  (defined(TACTICAL_BLINK_CHANNEL)) || \
  (defined(SAVE_MEMORY_BLINK_CHANNEL)) || \
  (defined(LOCK_BLINK_CHANNEL))) && (!defined(USE_BLINK_CHANNEL)))
#error "need to set `USE_BLINK_CHANNEL` to use event-specific channel blinks (e.g. AUX_CONFIG_BLINK_CHANNEL)"
#define USE_BLINK_CHANNEL
#endif

#ifdef USE_BLINK_CHANNEL
  #define USE_AUX_LED_OVERRIDE
#endif

#if (defined(EVENT_AUX_WHILE_ON_TOGGLE) && !defined(USE_AUX_WHILE_ON_CONFIG))
  #error "`EVENT_AUX_WHILE_ON_TOGGLE` needs `USE_AUX_WHILE_ON_CONFIG` (TODO: these could be separated?)" //TODO
#endif
