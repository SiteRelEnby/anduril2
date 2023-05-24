// channel-modes.c: Multi-channel functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "channel-modes.h"

uint8_t channel_mode_state(Event event, uint16_t arg) {
    #ifdef USE_CHANNEL_MODE_ARGS
    static int8_t tint_ramp_direction = 1;
    static uint8_t prev_tint = 0;
    #if (defined(EVENT_TURBO_SHORTCUT_1) || defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) || defined(EVENT_TURBO_SHORTCUT_2) || defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY))
      static uint8_t prev_channel = 255;
      static uint8_t prev_level = 0;
//      #if (defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) || defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY))
//        static uint8_t momentary_from_lock = 0; //temporary variable to store if we are in a momentary mode from lockout_state for channel-specific turbo modes
//      #endif
    #endif
    #if ((NUM_CHANNEL_MODES > 1) && (defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) || (defined(EVENT_CHANNEL_CYCLE_ON_HOLD))))
      static uint8_t reset_level = 0;
    #endif
    // don't activate auto-tint modes unless the user hits the edge
    // and keeps pressing for a while
    static uint8_t past_edge_counter = 0;
    // bugfix: click-click-hold from off to strobes would invoke tint ramping
    // in addition to changing state...  so ignore any tint-ramp events which
    // don't look like they were meant to be here
    static uint8_t active = 0;
    uint8_t tint = cfg.channel_mode_args[cfg.channel_mode];
    #endif

    // it's possible that a light may need 3H but not 3C,
    // so try to detect if 3C is needed
    #if NUM_CHANNEL_MODES > 1
    // 3 clicks: next channel mode
    if ((event == NEXT_CHANNEL_MODE_EVENT)
    #ifdef DEFAULT_BLINK_CHANNEL
      )
    #else
      && (current_state != battcheck_state))
    #endif
    {
        uint8_t next = cfg.channel_mode;
        // go to next channel mode until we find one which is enabled
        // (and don't do any infinite loops if the user disabled them all)
        uint8_t count = 0;
        do {
            count ++;
            next = (next + 1) % NUM_CHANNEL_MODES;
        } while ((! channel_mode_enabled(next)) && count < NUM_CHANNEL_MODES);
        //} while ((! channel_modes_enabled[next]) && count < NUM_CHANNEL_MODES);

        // undo change if infinite loop detected (redundant?)
        //if (NUM_CHANNEL_MODES == count) next = cfg.channel_mode;

        // if mode hasn't changed, abort
        if (cfg.channel_mode == next)
            return EVENT_NOT_HANDLED;

        set_channel_mode(next);

        #ifndef USE_MANUAL_EEPROM_SAVE
        // remember after battery changes
        save_config();
        #endif
        return EVENT_HANDLED;
    } else

    #ifdef EVENT_PREVIOUS_CHANNEL
    if (event == EVENT_PREVIOUS_CHANNEL){
        //same as above but go backwards
        uint8_t next = cfg.channel_mode;
        uint8_t count = 0;
        do {
            count ++;

            //e.g. modes=6, current=2
            // --> next should be 1, 0, 5
            if (next > 0){ next--; }
            else if (next == 0) { next = (NUM_CHANNEL_MODES - 1); }
        } while ((! channel_mode_enabled(next)) && count < NUM_CHANNEL_MODES);
        //} while ((! channel_modes_enabled[next]) && count < NUM_CHANNEL_MODES);

        // undo change if infinite loop detected (redundant?)
        //if (NUM_CHANNEL_MODES == count) next = cfg.channel_mode;

        // if mode hasn't changed, abort
        if (cfg.channel_mode == next)
            return EVENT_NOT_HANDLED;

        set_channel_mode(next);
        #ifndef USE_MANUAL_EEPROM_SAVE
        // remember after battery changes
        save_config();
        #endif
        return EVENT_HANDLED;
    }
    #endif

    #endif  // if NUM_CHANNEL_MODES > 1

    #ifdef USE_CUSTOM_CHANNEL_3H_MODES
    // defer to mode-specific function if defined
    if (tint_ramp_modes[cfg.channel_mode]) {
        StatePtr tint_func = channel_3H_modes[cfg.channel_mode];
        return tint_func(cfg.channel_mode);
    } else
    #endif
    #ifdef USE_CHANNEL_MODE_ARGS
    #ifndef DONT_USE_DEFAULT_CHANNEL_ARG_MODE
    // click, click, hold: change the current channel's arg (like tint)
    if (event == EV_click3_hold) {
        ///// adjust value from 0 to 255
        // reset at beginning of movement
        if (! arg) {
            active = 1;  // first frame means this is for us
            past_edge_counter = 0;  // doesn't start until user hits the edge
        }
        // ignore event if we weren't the ones who handled the first frame
        if (! active) return EVENT_NOT_HANDLED;

        #ifdef USE_STEPPED_TINT_RAMPING
            if ((tint_ramp_direction > 0 && tint < 255) ||
                (tint_ramp_direction < 0 && tint > 0)) {
                // ramp slower in stepped mode
                if (cfg.tint_ramp_style && (arg % HOLD_TIMEOUT != 0))
                    return EVENT_HANDLED;

                const uint8_t step_size = (cfg.tint_ramp_style < 2)
                                        ? 1 : 254 / (cfg.tint_ramp_style-1);
                tint = nearest_tint_value(
                          tint + ((int16_t)step_size * tint_ramp_direction)
                          );
            }
        #else  // smooth tint ramping only
            if ((tint_ramp_direction > 0) && (tint < 255)) { tint ++; }
            else
            if ((tint_ramp_direction < 0) && (tint >   0)) { tint --; }
        #endif  // ifdef USE_STEPPED_TINT_RAMPING

        // if tint change stalled, let user know we hit the edge
        else if (prev_tint == tint) {
            if (past_edge_counter == 0) blip();
            past_edge_counter = 1;
        }
        prev_tint = tint;
        cfg.channel_mode_args[cfg.channel_mode] = tint;
        set_level(actual_level);
        return EVENT_HANDLED;
    }

    // click, click, hold, release: reverse direction for next ramp
    else if (event == EV_click3_hold_release) {
        active = 0;  // ignore next hold if it wasn't meant for us
        // reverse
        tint_ramp_direction = -tint_ramp_direction;
        if (0 == tint) tint_ramp_direction = 1;
        else if (255 == tint) tint_ramp_direction = -1;
        // remember tint after battery change
        cfg.channel_mode_args[cfg.channel_mode] = tint;
        save_config();
        // bug?: for some reason, brightness can seemingly change
        // from 1/150 to 2/150 without this next line... not sure why
        set_level(actual_level);
        return EVENT_HANDLED;
    }
    #endif  // ifndef DONT_USE_DEFAULT_CHANNEL_ARG_MODE
    #endif  // ifdef USE_CHANNEL_MODE_ARGS

    #if defined(USE_SIMPLE_UI)
    // remaining mappings aren't "simple", so stop here
    if (cfg.simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    #endif

    #if NUM_CHANNEL_MODES > 1
    // channel toggle menu on ... 9H?
    else if (event == EV_click9_hold) {
        push_state(channel_mode_config_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

#if defined(EVENT_TURBO_SHORTCUT_1) && (NUM_CHANNEL_MODES > 1)
  #ifndef TURBO_SHORTCUT_1_CHANNEL
    #define TURBO_SHORTCUT_1_CHANNEL 0 //first channel
  #endif
  else if (((event == EVENT_TURBO_SHORTCUT_1) || (event == EVENT_TURBO_SHORTCUT_2)) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){ //TODO: can this just be the event, or are there other states that need to be handled?
    //prev_channel = CH_MODE; don't need this as we're unlocking to on on this channel here
    set_channel_mode(TURBO_SHORTCUT_1_CHANNEL);
    set_state(steady_state, MAX_LEVEL);
    return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
  }
#endif

#if (defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) || defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY)) && (NUM_CHANNEL_MODES > 1)
  #if defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY) && !defined(EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE)
    #error "EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE not defined"
  #endif
  #if defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY) && !defined(EVENT_TURBO_SHORTCUT_2_MOMENTARY_RELEASE)
    #error "EVENT_TURBO_SHORTCUT_2_MOMENTARY_RELEASE not defined"
  #endif
  else if (((event == EVENT_TURBO_SHORTCUT_1_MOMENTARY) || (event == EVENT_TURBO_SHORTCUT_2_MOMENTARY)) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){
    uint8_t active = 0;
    uint8_t new_ch = 0;
    if ((!arg) && (!active)) {
      active = 1;
      prev_channel = CH_MODE; //save channel we were on the first time round and only *set* that channel then, since eventually arg wraps round to 0
      prev_level = actual_level;
      if (event == EVENT_TURBO_SHORTCUT_1_MOMENTARY){
        new_ch = TURBO_SHORTCUT_1_CHANNEL;
      }
      else {
        new_ch = TURBO_SHORTCUT_2_CHANNEL;
      }
      if (CH_MODE != new_ch) { set_channel_mode(new_ch); }
      if (current_state == lockout_state){
          momentary_from_lock = 1;
          //push_state(steady_state, MAX_LEVEL);
//          set_state(steady_state, arg);
        }
        set_level_and_therm_target(MAX_LEVEL);
      }
    return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

//        if (!arg) {
//            if (prev_channel == 255) { prev_channel = CH_MODE; prev_level = actual_level; set_channel_mode(TURBO_SHORTCUT_1_CHANNEL); set_channel_mode(TURBO_SHORTCUT_1_CHANNEL); } //save channel we were on the first time round and only *set* that channel then (since eventually arg wraps round to 0 which makes the LEDs blink otherwise when we channel switch (to the same channel), also resets thermal regulation
//            if (current_state == lockout_state){ momentary_from_lock = 1 ; set_state(steady_state, MAX_LEVEL); } //necessary to get it to stay on from lock? using push_state() doesn't seem to work.
//            return EVENT_HANDLED;
//        }
//  }
//  else if ((event == EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){
//  else if ((event == EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE) && (current_state == lockout_state)) {
  else if ((event == EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE) || (event == EVENT_TURBO_SHORTCUT_2_MOMENTARY_RELEASE)) {
    //prev_channel = 255; //reset
    if (momentary_from_lock == 1){
      momentary_from_lock = 0;
      set_state(lockout_state, 0);
      //pop_state();
    }
    active = 0;
    set_level_and_therm_target(prev_level);
    set_channel_mode(prev_channel);
    return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
  }
#endif

//#if ((NUM_CHANNEL_MODES > 1) && (defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) || defined(EVENT_CHANNEL_CYCLE_ON_HOLD))) //if we only want this to happen for lockout mode, no need to handle here
#if ((NUM_CHANNEL_MODES > 1) && (defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) || (defined(EVENT_CHANNEL_CYCLE_ON_HOLD))))
  else if (
  #if defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) && defined(EVENT_CHANNEL_CYCLE_ON_HOLD)
      (((event == EVENT_CHANNEL_CYCLE_OFF_HOLD) && (current_state == off_state)) || ((event == EVENT_CHANNEL_CYCLE_ON_HOLD) && (current_state == steady_state))  ) // || ((event == EVENT_CHANNEL_CYCLE_LOCK_HOLD) && (current_state == lockout_state)))
  #elif (defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) && !defined(EVENT_CHANNEL_CYCLE_ON_HOLD))
      ((event == EVENT_CHANNEL_CYCLE_OFF_HOLD) && (current_state == off_state))
  #else
      ((event == EVENT_CHANNEL_CYCLE_ON_HOLD) && (current_state == steady_state))
  #endif
  ){
//#ifdef USE_AUX_RGB_LEDS
//  setting_rgb_mode_now = 1;
//#endif
      if (actual_level == 0){
        //reset_level = memorized_level;
        reset_level = 1;
        set_level(memorized_level); //TODO: use another level?
      }
      else {
        reset_level = 0;
      }
      //from lockout-mode.c
      if (0 == (arg % TICKS_PER_SECOND)) {
      // pretend the user clicked 3 times to change channels
      return channel_mode_state(EV_3clicks, 0);
    }
  }

  #if defined(EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE) //only need release event for off mode, since lockout uses moon from holding anyway
  else if (
//  #if defined(EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE) && defined(EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE)
//      (((event == EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE) && (current_state == off_state)) || ((event == EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE) && (current_state == steady_state))  ) // || ((event == EVENT_CHANNEL_CYCLE_LOCK_HOLD) && (current_state == lockout_state)))
      (((event == EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE) && (current_state == off_state))      )// || ((event == EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE) && (current_state == steady_state))  ) // || ((event == EVENT_CHANNEL_CYCLE_LOCK_HOLD) && (current_state == lockout_state)))
  //      ((event == EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE) && (current_state == off_state))
//  #else
//      ((event == EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE) && (current_state == steady_state))
//  #endif
  ){
//    setting_rgb_mode_now = 0; //reset
    if (reset_level){ //needed for when using from off mode
      set_level(0);
      reset_level = 0;
    }
    return EVENT_HANDLED;
  }
#endif
#endif

  return EVENT_NOT_HANDLED;
}


#if NUM_CHANNEL_MODES > 1
void channel_mode_config_save(uint8_t step, uint8_t value) {
    // 1 menu item per channel mode, to enable or disable that mode
    step --;  // step is 1-based, channel modes are 0-based
    if (value) channel_mode_enable(step);
    else channel_mode_disable(step);
}

uint8_t channel_mode_config_state(Event event, uint16_t arg) {
    uint8_t ret;
    // make config steps match channel modes
    config_color_per_step = true;
    // 1 menu item per channel mode, to enable or disable that mode
    ret = config_state_base(
        event, arg,
        NUM_CHANNEL_MODES,
        channel_mode_config_save
        );
    // no other menu needs this
    config_color_per_step = false;
    return ret;
}
#endif


#if defined(USE_CHANNEL_MODE_ARGS) && defined(USE_STEPPED_TINT_RAMPING)
uint8_t nearest_tint_value(const int16_t target) {
    // const symbols for more readable code, will be removed by the compiler
    const uint8_t tint_min = 0;
    const uint8_t tint_max = 255;
    const uint8_t tint_range = tint_max - tint_min;

    // only equal mix of both channels
    if (1 == cfg.tint_ramp_style) return (tint_min + tint_max) >> 1;

    if (target < tint_min) return tint_min;
    if (target > tint_max) return tint_max;
    if (0 == cfg.tint_ramp_style) return target;  // smooth ramping

    const uint8_t step_size = tint_range / (cfg.tint_ramp_style-1);

    uint8_t tint_result = tint_min;
    for (uint8_t i=0; i<cfg.tint_ramp_style; i++) {
        tint_result = tint_min
                    + (i * (uint16_t)tint_range / (cfg.tint_ramp_style-1));
        int16_t diff = target - tint_result;
        if (diff <= (step_size>>1)) return tint_result;
    }
    return tint_result;
}
#endif

