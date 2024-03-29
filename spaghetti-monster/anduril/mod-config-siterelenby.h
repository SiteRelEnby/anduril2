#pragma once

#define BUTTON_MAPPINGS_DEFINED

#if defined(USE_MOMENTARY_MODE) && !defined(EVENT_MOMENTARY)
#define EVENT_MOMENTARY EV_12clicks
#endif

#if defined(EVENT_MOMENTARY) && !defined(EVENT_MOMENTARY_STROBE)
#define EVENT_MOMENTARY_STROBE EVENT_MOMENTARY
#endif

#if defined(USE_SUNSET_TIMER) && !defined(EVENT_SUNSET_TIMER_HOLD)
#define EVENT_SUNSET_TIMER_HOLD EV_click12_hold
#endif

#if (NUM_CHANNEL_MODES > 1)
  #if !defined(NEXT_CHANNEL_MODE_EVENT)
    #define NEXT_CHANNEL_MODE_EVENT EV_3clicks
  #endif

  #if !defined(EVENT_PREVIOUS_CHANNEL)
    #define EVENT_PREVIOUS_CHANNEL EV_4clicks
  #endif
#endif

#if !defined(EVENT_TACTICAL_MODE) //default setting that might be unset for specific lights e.g. t85
  #define EVENT_TACTICAL_MODE EV_9clicks
#endif
#ifndef TACTICAL_LEVELS
  #define TACTICAL_LEVELS 150,75,(RAMP_SIZE+2)
#endif

#ifdef LOCK_FROM_ON_EVENT
#undef LOCK_FROM_ON_EVENT
#endif

#ifndef BLINK_LOCK_REMINDER
  #define BLINK_LOCK_REMINDER
#endif

#undef DEFAULT_MANUAL_MEMORY_TIMER
#define DEFAULT_MANUAL_MEMORY_TIMER 60
#undef DEFAULT_MANUAL_MEMORY
#define DEFAULT_MANUAL_MEMORY 50
#define DEFAULT_AUTOLOCK_TIME 60

#ifndef DEFAULT_2C_STYLE
  #define DEFAULT_2C_STYLE 1
#endif
#ifndef DEFAULT_2C_STYLE_SIMPLE
  #define DEFAULT_2C_STYLE_SIMPLE 2
#endif
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

//#ifndef MOMENTARY_TURBO_FROM_LOCK_EVENT
//  #define MOMENTARY_TURBO_FROM_LOCK_EVENT EV_click4_hold
//  #define MOMENTARY_TURBO_FROM_LOCK_EVENT_RELEASE EV_click4_hold_release
//  #undef EVENT_UNLOCK_TO_FLOOR
//#endif
#define EVENT_UNLOCK_TO_FLOOR EV_click4_hold
#define EVENT_UNLOCK_TO_CEILING EV_5clicks

#ifdef USE_AUX_RGB_LEDS_WHILE_ON
  #define EVENT_AUX_WHILE_ON_TOGGLE EV_8clicks
#endif

#undef RAMP_SMOOTH_FLOOR
#undef RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_FLOOR
#undef RAMP_DISCRETE_CEIL
#undef RAMP_DISCRETE_STEPS
#undef SIMPLE_UI_FLOOR
#undef SIMPLE_UI_CEIL
#undef SIMPLE_UI_STEPS
#define RAMP_SMOOTH_FLOOR    2 //even with dynamic PWM, 1 doesn't work with all lights
#define RAMP_SMOOTH_CEIL     150
#define RAMP_DISCRETE_FLOOR  10
#define RAMP_DISCRETE_CEIL   150
#define RAMP_DISCRETE_STEPS  11
#define SIMPLE_UI_FLOOR  25
#define SIMPLE_UI_CEIL   125
#define SIMPLE_UI_STEPS  5

#if (NUM_CHANNEL_MODES > 1)
  #define EVENT_CHANNEL_CYCLE_OFF_HOLD EV_click4_hold
  #define EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE EV_click4_hold_release
  #define EVENT_CHANNEL_CYCLE_ON_HOLD EV_click8_hold
  #define EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE EV_click8_hold_release

  #if (NUM_MAIN_CHANNELS == 2)
    #define TURBO_SHORTCUT_1_CHANNEL CM_CH1
    #define TURBO_SHORTCUT_2_CHANNEL CM_CH2
    #define TURBO_MAX_CHANNEL CM_BOTH //this will usually be CM_BOTH? Probably different on 3+ channel lights where it makes sense to have this feature specifically
  #endif

  #if (NUM_MAIN_CHANNELS == 3)
    #define TURBO_SHORTCUT_1_CHANNEL CM_MAIN2 //TODO: with 3+ it makes sense to make configurable at runtime? maybe one day
    #define TURBO_SHORTCUT_2_CHANNEL CM_LED3
    //#define TURBO_SHORTCUT_2_CHANNEL CM_LED4
    #define TURBO_MAX_CHANNEL CM_ALL
  #endif

  //generic config for any number of channels
  #if (NUM_MAIN_CHANNELS > 1)
    #define NO_ARG_3H_OVERRIDE 1
    #define EVENT_CHANNEL_CYCLE_LOCK_HOLD EV_click3_hold
    #undef USE_3H_TURBO_FROM_LOCK
    #define EVENT_CHANNEL_MODE_CONFIG_HOLD EV_click13_hold
    #define EVENT_TURBO_SHORTCUT_1 EV_5clicks
    #define EVENT_TURBO_SHORTCUT_1_MOMENTARY EV_click5_hold
    #define EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE EV_click5_hold_release

    #define EVENT_TURBO_SHORTCUT_2 EV_6clicks
    #define EVENT_TURBO_SHORTCUT_2_MOMENTARY EV_click6_hold
    #define EVENT_TURBO_SHORTCUT_2_MOMENTARY_RELEASE EV_click6_hold_release

    #define EVENT_TURBO_MAX EV_7clicks
    #define EVENT_TURBO_MAX_MOMENTARY EV_click7_hold
    #define EVENT_TURBO_MAX_MOMENTARY_RELEASE EV_click7_hold_release

    #define EVENT_AUX_CONFIG EV_8clicks
    #define EVENT_AUX_CONFIG_HOLD EV_click8_hold
    #define EVENT_AUX_CONFIG_HOLD_RELEASE EV_click8_hold_release

    #define EVENT_RAMP_CONFIG_HOLD EV_click9_hold
  #else //NUM_MAIN_CHANNELS = 1
    #define USE_3H_TURBO_FROM_LOCK
    #undef EVENT_CHANNEL_CYCLE_LOCK_HOLD
    #define EVENT_CHANNEL_MODE_CONFIG_HOLD EV_click9_hold
    #define EVENT_AUX_CONFIG EV_7clicks
    #define EVENT_AUX_CONFIG_HOLD EV_click7_hold
    #define EVENT_AUX_CONFIG_HOLD_RELEASE EV_click7_hold_release
    #if !defined(EVENT_RAMP_CONFIG_HOLD)
      #define EVENT_RAMP_CONFIG_HOLD EV_click7_hold
    #endif
  #endif
#endif

#define USE_POST_OFF_VOLTAGE_BRIGHTNESS_CONFIG
#define DEFAULT_POST_OFF_VOLTAGE_BRIGHTNESS_THRESHOLD 0 //always use high
#define DISABLE_POST_OFF_VOLTAGE_AFTER_BLINK

#define EVENT_RAMP_STYLE_TOGGLE EV_9clicks

#define USE_LOCKOUT_HIGH_AUX_TIMER
#define LOCKOUT_HIGH_AUX_CLICKS 2
#undef USE_OFF_HIGH_AUX_TIMER

#ifdef USE_AUX_RGB_LEDS
  #ifdef RGB_LED_OFF_DEFAULT
    #undef RGB_LED_OFF_DEFAULT
  #endif
  #define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
  #ifdef RGB_LED_LOCKOUT_DEFAULT
    #undef RGB_LED_LOCKOUT_DEFAULT
  #endif
  #define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow
#endif

#ifdef USE_AUX_RGB_LEDS_WHILE_ON
  #define USE_AUX_WHILE_ON_CONFIG
  #ifndef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW
//    #warning "setting USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW to default"
    #define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW 15
  #endif
  #ifndef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH
//    #warning "setting USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH to default"
    #define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH 45
  #endif

  #ifndef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW
    #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
  #endif
  #ifndef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH
    #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 70
  #endif
#endif

#if NUM_CHANNEL_MODES > 1
  //#define USE_BLINK_CHANNEL
  //BLINK_ONCE_USE_BLINKY_MODE_CHANNEL_SETTING

  #if (defined(USE_AUX_RGB_LEDS))
    //RGB aux
    #if (!defined(BLINK_LOCK_REMINDER_CHANNEL) )// && (defined (CM_AUXRED)))
      #define BLINK_LOCK_REMINDER_CHANNEL CM_AUXRED
    #endif
    #if !(defined(POWERON_BLINK_CHANNEL))// && (defined(CM_AUXBLU))
      #define POWERON_BLINK_CHANNEL CM_AUXBLU
    #endif

    #if !(defined(LOCKOUT_EXIT_BLINK_CHANNEL))// && (defined(CM_AUXCYN))
      #define LOCKOUT_EXIT_BLINK_CHANNEL CM_AUXCYN
    #endif

    #if !(defined(AUX_CONFIG_BLINK_CHANNEL))// && (defined(CM_AUXCYN))
      #define AUX_CONFIG_BLINK_CHANNEL CM_AUXCYN
    #endif

    #if !(defined(SIMPLE_UI_BLINK_CHANNEL))// && (defined(CM_AUXWHT))
      #define SIMPLE_UI_BLINK_CHANNEL CM_AUXWHT
    #endif

    #if !(defined(MOMENTARY_BLINK_CHANNEL))// && (defined(CM_AUXCYN))
      #define MOMENTARY_BLINK_CHANNEL CM_AUXCYN
    #endif

    #if !(defined(TACTICAL_BLINK_CHANNEL))// && (defined(CM_AUXRED))
      #define TACTICAL_BLINK_CHANNEL CM_AUXRED
    #endif

    #if !(defined(SAVE_MEMORY_BLINK_CHANNEL))// && (defined(CM_AUXWHT))
      #define SAVE_MEMORY_BLINK_CHANNEL CM_AUXWHT
    #endif

    #if !(defined(LOCK_BLINK_CHANNEL))// && (defined(CM_AUXRED))
      #define LOCK_BLINK_CHANNEL CM_AUXRED
    #endif
  #else
    //no RGB :c
    #if (defined(USE_INDICATOR_LED)) || (defined(USE_BUTTON_LED))
      #if (!defined(BLINK_LOCK_REMINDER_CHANNEL) )
        // BLINK_CHANNEL should map to whatever blink is configured to
        #define BLINK_LOCK_REMINDER_CHANNEL BLINK_CHANNEL
      #endif

      #if (!defined(BLINK_LOCK_REMINDER_CHANNEL) )
        #define BLINK_LOCK_REMINDER_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(POWERON_BLINK_CHANNEL))
        #define POWERON_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(LOCKOUT_EXIT_BLINK_CHANNEL))
        #define LOCKOUT_EXIT_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(AUX_CONFIG_BLINK_CHANNEL))
        #define AUX_CONFIG_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(SIMPLE_UI_BLINK_CHANNEL))
        #define SIMPLE_UI_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(MOMENTARY_BLINK_CHANNEL))
        #define MOMENTARY_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(TACTICAL_BLINK_CHANNEL))
        #define TACTICAL_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(SAVE_MEMORY_BLINK_CHANNEL))
        #define SAVE_MEMORY_BLINK_CHANNEL BLINK_CHANNEL
      #endif

      #if !(defined(LOCK_BLINK_CHANNEL))
        #define LOCK_BLINK_CHANNEL BLINK_CHANNEL
      #endif
    #endif
  #endif
#endif
