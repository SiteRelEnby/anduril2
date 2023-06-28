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

#if ((defined(EVENT_AUX_WHILE_ON_CONFIG) || defined(EVENT_AUX_WHILE_ON_TOGGLE)) && !defined(USE_AUX_RGB_LEDS_WHILE_ON))
  #define USE_AUX_RGB_LEDS_WHILE_ON
#endif

#ifdef USE_AUX_WHILE_ON_CONFIG

  #ifndef USE_AUX_RGB_LEDS_WHILE_ON
    #define USE_AUX_RGB_LEDS_WHILE_ON
  #endif

  #ifdef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW
    #ifdef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW
      #warning "`USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW` overrides `USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW`"
      #undef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW
    #endif
    #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW cfg.use_aux_while_on_threshold_low
  #endif

  #ifdef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH
    #ifdef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH
      #warning "`USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH` overrides `USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH`"
      #undef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH
    #endif
    #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH cfg.use_aux_while_on_threshold_high

  #endif

#else //not using USE_AUX_WHILE_ON_CONFIG

  #if !defined(USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW) && defined(USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW)
    #warning "`USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW` is defined but does nothing without `USE_AUX_WHILE_ON_CONFIG`, changing symbol to `USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW`"
    #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW
    #undef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW
  #endif

  #if !defined(USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH) && defined(USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH)
    #warning "`USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH` is defined but does nothing without `USE_AUX_WHILE_ON_CONFIG`, changing symbol to `USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH`"
    #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH
    #undef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH
  #endif

#endif
