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

#if !defined(NEXT_CHANNEL_MODE_EVENT)
#define NEXT_CHANNEL_MODE_EVENT EV_3clicks
#endif

#if !defined(EVENT_PREVIOUS_CHANNEL)
#define EVENT_PREVIOUS_CHANNEL EV_4clicks
#endif

#if !defined(EVENT_TACTICAL_MODE)
  #define EVENT_TACTICAL_MODE EV_9clicks
#endif

#ifdef LOCK_FROM_ON_EVENT
#undef LOCK_FROM_ON_EVENT
#endif

#ifndef BLINK_LOCK_REMINDER
  #define BLINK_LOCK_REMINDER
#endif

//#ifndef MOMENTARY_TURBO_FROM_LOCK_EVENT
//  #define MOMENTARY_TURBO_FROM_LOCK_EVENT EV_click4_hold
//  #define MOMENTARY_TURBO_FROM_LOCK_EVENT_RELEASE EV_click4_hold_release
//  #undef EVENT_UNLOCK_TO_FLOOR
//#endif
#define EVENT_UNLOCK_TO_FLOOR EV_click4_hold
//#define EVENT_UNLOCK_TO_CEILING EV_click5_hold

#define EVENT_SUNSET_TIMER_HOLD EV_click12_hold

#define EVENT_AUX_WHILE_ON_TOGGLE EV_8clicks

#define USE_MOMENTARY_TURBO_FROM_LOCK

#define BLINK_CHANNEL_WITH_ARGS //TODO

#if NUM_CHANNEL_MODES > 1
  #define TURBO_SHORTCUT_1_CHANNEL CM_CH1
  #define EVENT_TURBO_SHORTCUT_1 EV_5clicks
  #define EVENT_TURBO_SHORTCUT_1_MOMENTARY EV_click5_hold
  #define EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE EV_click5_hold_release

  #define TURBO_SHORTCUT_2_CHANNEL CM_CH2
  #define EVENT_TURBO_SHORTCUT_2 EV_6clicks
  #define EVENT_TURBO_SHORTCUT_2_MOMENTARY EV_click6_hold
  #define EVENT_TURBO_SHORTCUT_2_MOMENTARY_RELEASE EV_click6_hold_release

  #define EVENT_TURBO_MAX EV_7clicks
  #define TURBO_MAX_CHANNEL CM_BOTH //this will usually be CM_BOTH? Probably different on 3+ channel lights where it makes sense to have this feature specifically
  #define EVENT_TURBO_MAX_MOMENTARY EV_click7_hold
  #define EVENT_TURBO_MAX_MOMENTARY_RELEASE EV_click7_hold_release

  #define EVENT_AUX_CONFIG EV_8clicks
  #define EVENT_AUX_CONFIG_HOLD EV_click8_hold
  #define EVENT_AUX_CONFIG_HOLD_RELEASE EV_click8_hold_release

  #define EVENT_RAMP_CONFIG_HOLD EV_click8_hold

  #define EVENT_CHANNEL_MODE_CONFIG_HOLD EV_click13_hold
  #define EVENT_CHANNEL_CYCLE_OFF_HOLD EV_click4_hold
  #define EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE EV_click4_hold_release
  #define EVENT_CHANNEL_CYCLE_ON_HOLD EV_click8_hold
  #define EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE EV_click8_hold_release
  #define EVENT_CHANNEL_CYCLE_LOCK_HOLD EV_click3_hold
#else
  #define EVENT_AUX_CONFIG EV_7clicks
  #define EVENT_AUX_CONFIG_HOLD EV_click7_hold
  #define EVENT_AUX_CONFIG_HOLD_RELEASE EV_click7_hold_release
  #if !defined(EVENT_RAMP_CONFIG_HOLD)
    #define EVENT_RAMP_CONFIG_HOLD EV_click7_hold
  #endif
#endif


#define USE_POST_OFF_VOLTAGE_BRIGHTNESS_CONFIG
#define DEFAULT_POST_OFF_VOLTAGE_BRIGHTNESS_THRESHOLD 0 //always use high

#define EVENT_RAMP_STYLE_TOGGLE EV_9clicks

#define USE_AUX_WHILE_ON_CONFIG
#define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW 15
#define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH 90

//#ifndef BLINK_ONCE_USE_CONFIGURED_BLINK_CHANNEL
//  #define BLINK_ONCE_USE_CONFIGURED_BLINK_CHANNEL
//#endif

#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 70
#if NUM_CHANNEL_MODES > 1

//#if (!defined(BLINK_LOCK_REMINDER_CHANNEL)) && defined (CM_AUXRED)
//  #define BLINK_LOCK_REMINDER_CHANNEL CM_AUXRED
//#endif

//BLINK_ONCE_USE_BLINKY_MODE_CHANNEL_SETTING

  #if !(defined(POWERON_BLINK_CHANNEL)) && (defined(CM_AUXBLU))
    #define POWERON_BLINK_CHANNEL CM_AUXBLU
  #endif

  #if !(defined(LOCKOUT_EXIT_BLINK_CHANNEL)) && (defined(CM_AUXCYN))
    #define LOCKOUT_EXIT_BLINK_CHANNEL CM_AUXCYN
  #endif

  #if !(defined(AUX_CONFIG_BLINK_CHANNEL)) && (defined(CM_AUXCYN))
    #define AUX_CONFIG_BLINK_CHANNEL CM_AUXCYN
  #endif

  #if !(defined(SIMPLE_UI_BLINK_CHANNEL)) && (defined(CM_AUXWHT))
    #define SIMPLE_UI_BLINK_CHANNEL CM_AUXWHT
  #endif

  #if !(defined(MOMENTARY_BLINK_CHANNEL)) && (defined(CM_AUXCYN))
    #define MOMENTARY_BLINK_CHANNEL CM_AUXCYN
  #endif

  #if !(defined(TACTICAL_BLINK_CHANNEL)) && (defined(CM_AUXRED))
    #define TACTICAL_BLINK_CHANNEL CM_AUXRED
  #endif

  #if !(defined(SAVE_MEMORY_BLINK_CHANNEL)) && (defined(CM_AUXWHT))
    #define SAVE_MEMORY_BLINK_CHANNEL CM_AUXWHT
  #endif

  #if !(defined(LOCK_BLINK_CHANNEL)) && (defined(CM_AUXRED))
    #define LOCK_BLINK_CHANNEL CM_AUXRED
  #endif
#endif
