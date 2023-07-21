// lockout-mode.c: Lockout mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "lockout-mode.h"

#if (defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) || defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY)) || (defined(USE_3H_TURBO_FROM_LOCK))
  static uint8_t momentary_from_lock = 0; //temporary variable to store if we are in a momentary mode from lockout_state for channel-specific turbo modes
#endif
#if (defined(USE_3H_TURBO_FROM_LOCK) && (NUM_CHANNEL_MODES > 1))
  uint8_t prev_channel_mode = 0;
#endif

#ifdef USE_BLINK_CHANNEL
extern volatile uint8_t blink_channel_count;
extern volatile uint16_t blink_channel_ontime;
extern volatile uint16_t blink_channel_offtime;
extern volatile uint8_t blink_channel_channel;
#endif

void lockout_led_update(uint16_t arg){
  #ifdef USE_INDICATOR_LED
    #ifdef USE_LOCKOUT_HIGH_AUX_TIMER
      if (arg < (cfg.lockout_high_aux_timer * SLEEP_TICKS_PER_MINUTE)){
        indicator_led_update(2, arg); //force high
        }
      else {
    #endif
        indicator_led_update(cfg.indicator_led_mode & 0x03, arg);
    #ifdef USE_LOCKOUT_HIGH_AUX_TIMER
      }
    #endif
    #elif defined(USE_AUX_RGB_LEDS)
      #ifdef USE_LOCKOUT_HIGH_AUX_TIMER
      if (arg < (cfg.lockout_high_aux_timer * SLEEP_TICKS_PER_MINUTE)){
        //force high mode with selected pattern
        uint8_t rgb_led_mode = cfg.rgb_led_lockout_mode;
        rgb_led_mode &= 0x0F; //clear upper 4 bits
        rgb_led_mode |= 0x20; //set the upper 4 the way we want (i.e. 0x0010), this time with a bitwise OR to preserve the actual colour setting
        rgb_led_update(rgb_led_mode, arg);
      }
      else {
      #endif

      #ifndef USE_AUX_LED_OVERRIDE
        rgb_led_update(cfg.rgb_led_lockout_mode, arg);
      #else
        if (! aux_led_override){ rgb_led_update(cfg.rgb_led_lockout_mode, arg); }
      #endif
    #endif
    #ifdef USE_LOCKOUT_HIGH_AUX_TIMER
      }
    #endif
}

uint8_t lockout_state(Event event, uint16_t arg) {
    #ifdef USE_MOON_DURING_LOCKOUT_MODE
    // momentary(ish) moon mode during lockout
    // button is being held
    #ifdef USE_AUX_RGB_LEDS
    // don't turn on during RGB aux LED configuration
    if (event == EVENT_AUX_CONFIG_HOLD) { set_level(0); } else
    #endif

    //TODO: how to handle having both momentary lock turbo and channel cycling? I mostly want this on throwers and not multiple main LED lights, but might be diffrent for other people?
    //  -> shift others up one? have cycle be remappable?
    #ifdef USE_3H_TURBO_FROM_LOCK
      // 3H: momentary turbo
      if (event == EV_click3_hold){
        momentary_from_lock = 1;
        //if ((!arg) && (setting_rgb_mode_now == 0)){
        if (!arg){
          #if (NUM_CHANNEL_MODES > 1)
            #ifdef USE_3H_TURBO_FROM_LOCK_FORCE_CHANNEL
              prev_channel_mode = CH_MODE;
              set_channel_mode(3H_TURBO_FROM_LOCK_FORCE_CHANNEL);
            #elif defined(CHANNEL_AUX_OVERRIDE) //we don't want to use an aux channel for this...
              if (channel_uses_aux(CH_MODE)){
                prev_channel_mode = CH_MODE;
                #if defined(CM_MAIN) //probably a single (main) channel light
                  set_channel_mode(CM_MAIN);
                #elif defined(CM_CH1) //assume ch1 is the closest thing to a main
                  set_channel_mode(CM_CH1);
                #elif defined(DEFAULT_CHANNEL_MODE)
                  #warning "using DEFAULT_CHANNEL_MODE for 3H from lock"
                  set_channel_mode(DEFAULT_CHANNEL_MODE);
                #else
                  #error "neither CM_MAIN or CM_CH1 exist. Set a channel for 3H turbo from lock by defining `USE_3H_TURBO_FROM_LOCK_FORCE_CHANNEL`)"
                #endif
                }
            #endif
          #endif
          //set_state(steady_state,150); //TODO: use 2C_STYLE? config for dual channel?
          set_level_and_therm_target(150); //TODO: use 2C_STYLE? config for dual channel?
          return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
      }
      else if (event == EV_click3_hold_release){
        set_level(0);
        momentary_from_lock = 0;
        #if (NUM_CHANNEL_MODES > 1)
          set_channel_mode(prev_channel_mode);
        #endif
        set_state(lockout_state,0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
      }
    #endif


    #ifdef BLINK_LOCK_REMINDER
    if (((event == EV_1click) || (event == EV_2clicks)) && (current_state != tactical_state)){
        //remind user light is locked
        blink_channel_count = 3;
        blink_channel_ontime = 60;
        blink_channel_offtime = 60;
        blink_channel_channel = BLINK_LOCK_REMINDER_CHANNEL;

        return EVENT_HANDLED;
    } else
    #endif

#if ((defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) || defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY) || defined(EVENT_TURBO_MAX_MOMENTARY))) || (defined(USE_3H_TURBO_FROM_LOCK))
if (!momentary_from_lock) { //also used in channel-modes.c
#endif
    if ((event & (B_CLICK | B_PRESS)) == (B_CLICK | B_PRESS)) {
        // hold: lowest floor
        // click, hold: highest floor (or manual mem level)
        uint8_t lvl = cfg.ramp_floors[0];
        if (1 == (event & 0x0f)) {  // first click
            if (cfg.ramp_floors[1] < lvl) lvl = cfg.ramp_floors[1];
        } else {  // 2nd click or later
            if (cfg.ramp_floors[1] > lvl) lvl = cfg.ramp_floors[1];
            #ifdef USE_MANUAL_MEMORY
            if (cfg.manual_memory) lvl = cfg.manual_memory;
            #endif
        }
        set_level(lvl);
    }
    // button was released
    else if ((event & (B_CLICK | B_PRESS)) == (B_CLICK)) {
        set_level(0);
    }
    #endif  // ifdef USE_MOON_DURING_LOCKOUT_MODE
#if (defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) || defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY) || defined(EVENT_TURBO_MAX_MOMENTARY)) || (defined(USE_3H_TURBO_FROM_LOCK))
}
#endif

    // regular event handling
    // conserve power while locked out
    // (allow staying awake long enough to exit, but otherwise
    //  be persistent about going back to sleep every few seconds
    //  even if the user keeps pressing the button)
    if (event == EV_enter_state) {
        ticks_since_on = 0;
        #if defined(USE_AUX_RGB_LEDS)

        #ifdef USE_AUX_LED_OVERRIDE
          aux_led_override = 0;
        #endif
        #endif
        #ifdef USE_INDICATOR_LED
            // redundant, sleep tick does the same thing
            // indicator_led_update(cfg.indicator_led_mode >> 2, 0);
        #elif defined(USE_AUX_RGB_LEDS)
            rgb_led_update(cfg.rgb_led_lockout_mode, 0);
        #endif
    }

    else if (event == EV_tick) {
        if (arg > HOLD_TIMEOUT) {
            go_to_standby = 1;
            #ifdef USE_INDICATOR_LED
            // redundant, sleep tick does the same thing
            //indicator_led_update(cfg.indicator_led_mode >> 2, arg);
            //#elif defined(USE_AUX_RGB_LEDS)
              //#ifdef USE_AUX_LED_OVERRIDE
                //if (! aux_led_override) {
                  //rgb_led_update(cfg.rgb_led_lockout_mode, arg);
                //}
              //#else
                //rgb_led_update(cfg.rgb_led_lockout_mode, arg);
              //#endif
            #endif
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

    #if defined(TICK_DURING_STANDBY) && (defined(USE_INDICATOR_LED) || defined(USE_AUX_RGB_LEDS))
    else if (event == EV_sleep_tick) {
        if (ticks_since_on < 255) ticks_since_on ++;
        #ifdef USE_MANUAL_MEMORY_TIMER
        // reset to manual memory level when timer expires
        if (cfg.manual_memory &&
                (arg >= (cfg.manual_memory_timer * SLEEP_TICKS_PER_MINUTE))) {
            manual_memory_restore();
        }
        #endif

        lockout_led_update(arg);

        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    // 3 clicks: exit and turn off
    else if (event == EV_3clicks) {
        #ifdef LOCKOUT_EXIT_BLINK_CHANNEL
//        blink_digit_channel(1, 200, 75, LOCKOUT_EXIT_BLINK_CHANNEL);
          blink_channel_count = 1;
          blink_channel_ontime = 500;
          blink_channel_offtime = 100;
          blink_channel_channel = LOCKOUT_EXIT_BLINK_CHANNEL;
        #else
          blink_once();
        #endif
        set_state(off_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

    // 4 clicks: exit and turn on
    else if (event == EV_4clicks) {
        #if defined(USE_MANUAL_MEMORY) && !defined(USE_MANUAL_MEMORY_TIMER)
        // this clause probably isn't used by any configs any more
        // but is included just in case someone configures it this way
        if (cfg.manual_memory)
            set_state(steady_state, cfg.manual_memory);
        else
        #endif
        set_state(steady_state, memorized_level);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

    #ifdef EVENT_UNLOCK_TO_FLOOR
    // 4 clicks, but hold last: exit and start at floor
    else if (event == EVENT_UNLOCK_TO_FLOOR) {
        //blink_once();
        blip();
        // reset button sequence to avoid activating anything in ramp mode
        current_event = 0;
        // ... and back to ramp mode
        set_state(steady_state, 1);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    #ifdef EVENT_UNLOCK_TO_CEILING
    // 5 clicks: exit and turn on at ceiling level
    else if (event == EVENT_UNLOCK_TO_CEILING) {
        set_state(steady_state, MAX_LEVEL);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    //#if ((NUM_CHANNEL_MODES > 1) && ((!defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) || (!defined(EVENT_CHANNEL_CYCLE_ON_HOLD)))))
    // 3H: next channel mode
    #if (NUM_CHANNEL_MODES > 1)
    #ifdef EVENT_CHANNEL_CYCLE_LOCK_HOLD
    else if (event == EVENT_CHANNEL_CYCLE_LOCK_HOLD) {
        if (0 == (arg % TICKS_PER_SECOND)) {
            // pretend the user clicked 3 times to change channels
            return channel_mode_state(EV_3clicks, 0);
        }
    }
    #endif
    #endif

    ////////// Every action below here is blocked in the (non-Extended) Simple UI //////////

    #if defined(USE_SIMPLE_UI) && !defined(USE_EXTENDED_SIMPLE_UI)
    if (cfg.simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    #endif  // if simple UI but not extended simple UI

    #if defined(USE_INDICATOR_LED)
    // 7 clicks: rotate through indicator LED modes (lockout mode)
    else if (event == EVENT_AUX_CONFIG) {
        #if defined(USE_INDICATOR_LED)
            uint8_t mode = cfg.indicator_led_mode >> 2;
            #ifdef TICK_DURING_STANDBY
            mode = (mode + 1) & 3;
            #else
            mode = (mode + 1) % 3;
            #endif
            #ifdef INDICATOR_LED_SKIP_LOW
            if (mode == 1) { mode ++; }
            #endif
            cfg.indicator_led_mode = (mode << 2) + (cfg.indicator_led_mode & 0x03);
            // redundant, sleep tick does the same thing
            //indicator_led_update(cfg.indicator_led_mode >> 2, arg);
        #elif defined(USE_AUX_RGB_LEDS)
        #endif
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #elif defined(USE_AUX_RGB_LEDS)
    // 7 clicks: change RGB aux LED pattern
    else if (event == EVENT_AUX_CONFIG) {
        uint8_t mode = (cfg.rgb_led_lockout_mode >> 4) + 1;
        mode = mode % RGB_LED_NUM_PATTERNS;
        cfg.rgb_led_lockout_mode = (mode << 4) | (cfg.rgb_led_lockout_mode & 0x0f);
        rgb_led_update(cfg.rgb_led_lockout_mode, 0);
        save_config();
        #ifdef AUX_CONFIG_BLINK_CHANNEL
          blink_once();
//          blink_digit_channel(1, 200, 75, AUX_CONFIG_BLINK_CHANNEL);
          blink_channel_count = 1;
          blink_channel_ontime = 500;
          blink_channel_offtime = 100;
          blink_channel_channel = AUX_CONFIG_BLINK_CHANNEL;

        #else
          blink_once();
        #endif
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 7H: change RGB aux LED color
    else if (event == EVENT_AUX_CONFIG_HOLD) {
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (cfg.rgb_led_lockout_mode & 0x0f) + 1;
            mode = mode % RGB_LED_NUM_COLORS;
            cfg.rgb_led_lockout_mode = mode | (cfg.rgb_led_lockout_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 7H, release: save new color
    else if (event == EVENT_AUX_CONFIG_HOLD_RELEASE) {
        setting_rgb_mode_now = 0;
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    #if defined(USE_EXTENDED_SIMPLE_UI) && defined(USE_SIMPLE_UI)
    ////////// Every action below here is blocked in the Extended Simple UI //////////
    if (cfg.simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    #endif  // if extended simple UI

    #ifdef USE_AUTOLOCK
    // 10H: configure the autolock option
    else if (event == EV_click10_hold) {
        push_state(autolock_config_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    return EVENT_NOT_HANDLED;
}

#ifdef USE_AUTOLOCK
// set the auto-lock timer to N minutes, where N is the number of clicks
void autolock_config_save(uint8_t step, uint8_t value) {
  if (1 == step) {
    cfg.autolock_time = value;
  }
#if (defined(USE_LOCKOUT_HIGH_AUX_TIMER) || (defined(USE_OFF_HIGH_AUX_TIMER)))
    if (2 == step) {
    #if (defined(USE_LOCKOUT_HIGH_AUX_TIMER) && !defined(USE_OFF_HIGH_AUX_TIMER))
      cfg.lockout_high_aux_timer = value;
    #elif (!defined(USE_LOCKOUT_HIGH_AUX_TIMER) && defined(USE_OFF_HIGH_AUX_TIMER))
      cfg.off_high_aux_timer = value;
    #else //bothisgood.gif
      cfg.lockout_high_aux_timer = value;
    }
    if (3 == step){
      cfg.off_high_aux_timer = value;
  #endif
    }
#endif
}

uint8_t autolock_config_state(Event event, uint16_t arg) {
  #if (!defined(USE_LOCKOUT_HIGH_AUX_TIMER) && !defined(USE_OFF_HIGH_AUX_TIMER))
  const uint8_t num_config_steps = 1;
  #elif (defined(USE_LOCKOUT_HIGH_AUX_TIMER) && defined(USE_OFF_HIGH_AUX_TIMER))
  const uint8_t num_config_steps = 3; //3 goes before 2 to solve logic precedence issues
  #elif (defined(USE_LOCKOUT_HIGH_AUX_TIMER) || defined(USE_OFF_HIGH_AUX_TIMER))
  const uint8_t num_config_steps = 2;
  #else
    #error "cosmic ray detected"
  #endif
  return config_state_base(event, arg, num_config_steps, autolock_config_save);
}
#endif  // #ifdef USE_AUTOLOCK

