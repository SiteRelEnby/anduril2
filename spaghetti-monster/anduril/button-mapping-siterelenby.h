#pragma once

#define BUTTON_MAPPINGS_DEFINED

#if defined(USE_MOMENTARY_MODE) && !defined(EVENT_MOMENTARY)
#define EVENT_MOMENTARY EV_12clicks
#endif

#if defined(EVENT_MOMENTARY) && !defined(EVENT_MOMENTARY_STROBE)
#define EVENT_MOMENTARY_STROBE EVENT_MOMENTARY
#endif

#if defined(USE_SUNSET_TIMER) && !defined(EVENT_HOLD_SUNSET_TIMER)
#define EVENT_HOLD_SUNSET_TIMER EV_click12_hold
#endif

#if !defined(NEXT_CHANNEL_MODE_EVENT)
#define NEXT_CHANNEL_MODE_EVENT EV_3clicks
#endif

#if !defined(PREV_CHANNEL_MODE_EVENT)
#define PREV_CHANNEL_MODE_EVENT EV_4clicks
#endif

#if !defined(TACTICAL_MODE_EVENT)
  #define TACTICAL_MODE_EVENT EV_9clicks
#endif

#if !defined(EVENT_RAMP_CONFIG)
  #define EVENT_RAMP_CONFIG EV_click7_hold
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



#define EVENT_CHANNEL_CYCLE_OFF_HOLD EV_click4_hold
#define EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE EV_click4_hold_release
#define EVENT_CHANNEL_CYCLE_ON_HOLD EV_click8_hold
#define EVENT_CHANNEL_CYCLE_LOCK_HOLD EV_click3_hold

#define USE_MOMENTARY_TURBO_FROM_LOCK

//#ifndef BLINK_ONCE_USE_CONFIGURED_BLINK_CHANNEL
//  #define BLINK_ONCE_USE_CONFIGURED_BLINK_CHANNEL
//#endif

#if NUM_CHANNEL_MODES > 1
//USE_AUX_RGB_LEDS_WHILE_ON 50
//USE_AUX_RGB_LEDS_LOW_WHILE_ON 20

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
