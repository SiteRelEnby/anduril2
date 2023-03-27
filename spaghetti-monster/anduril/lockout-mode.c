/*
 * lockout-mode.c: Lockout mode for Anduril.
 *
 * Copyright (C) 2017 Selene Scriven
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOCKOUT_MODE_C
#define LOCKOUT_MODE_C

#include "lockout-mode.h"

uint8_t lockout_state(Event event, uint16_t arg) {
    //var for momentary channel-specific turbo
    #ifdef USE_TINT_RAMPING
    static uint8_t prev_tint;
    #endif

    if (0) {} //placeholder

    #ifdef USE_MOON_DURING_LOCKOUT_MODE
      // momentary(ish) moon mode during lockout
      // button is being held
      #ifdef USE_AUX_RGB_LEDS
        // don't turn on during RGB aux LED configuration
        #ifdef AUX_CONFIG_HOLD_EVENT
          else if (event == AUX_CONFIG_HOLD_EVENT) { set_level(0); }
        #else
          else if (event == EV_click7_hold) { set_level(0); }
        #endif
      #endif
      #ifndef DISABLE_MOMENTARY_TURBO_FROM_LOCK
        #ifdef USE_3H_TURBO_FROM_LOCK
          // 3H: momentary turbo
          if (event == EV_click3_hold){
            if (!arg){
              set_level_and_therm_target(150); //TODO: use 2C_STYLE?
              return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
            }
          }
          else if (event == EV_click3_hold_release){
            set_level(0);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
          }
        #endif
      #endif //ifndef DISABLE_MOMENTARY_TURBO_FROM_LOCK
      else if ((event & (B_CLICK | B_PRESS)) == (B_CLICK | B_PRESS)) {
        #ifdef MOMENTARY_WHEN_LOCKED_DELAY
        if (arg > MOMENTARY_WHEN_LOCKED_DELAY) { //only use momentary if it is a longer hold than the user specified timeout (which can be less than HOLD_TIMEOUT)
        #else
        #ifdef WAIT_FOR_MOMENTARY_WHEN_LOCKED
        if (arg > HOLD_TIMEOUT) { //only use momentary if it is definitely 1H (not if the user is trying to do more clicks)
        #endif //ifdef WAIT_FOR_MOMENTARY_WHEN_LOCKED
        #endif //ifdef MOMENTARY_WHEN_LOCKED_DELAY
        // hold: lowest floor
        // click, hold: highest floor (or manual mem level)
        uint8_t lvl = ramp_floors[0];
        if ((event & 0x0f) == 2) {  // second click
            if (ramp_floors[1] > lvl) lvl = ramp_floors[1];
            #ifdef USE_MANUAL_MEMORY
            if (manual_memory) lvl = manual_memory;
            #endif
        } else {  // anything except second click
            if (ramp_floors[1] < lvl) lvl = ramp_floors[1];
        }
        set_level(lvl);
        #ifdef WAIT_FOR_MOMENTARY_WHEN_LOCKED
        }
        #else
        #ifdef MOMENTARY_WHEN_LOCKED_DELAY
        }
        #endif
        #endif
    }
    // button was released
    else if ((event & (B_CLICK | B_PRESS)) == (B_CLICK)) {
        set_level(0);
    }
    #endif  // ifdef USE_MOON_DURING_LOCKOUT_MODE

    // regular event handling
    // conserve power while locked out
    // (allow staying awake long enough to exit, but otherwise
    //  be persistent about going back to sleep every few seconds
    //  even if the user keeps pressing the button)
    #ifdef USE_INDICATOR_LED
    if (event == EV_enter_state) {
        indicator_led_update(indicator_led_mode >> 4, 0);
    } else
    #elif defined(USE_AUX_RGB_LEDS)
    if (event == EV_enter_state) {
        rgb_led_update(rgb_led_lockout_mode, 0);
    } else
    #endif
    if (event == EV_tick) {
        if (arg > HOLD_TIMEOUT) {
            go_to_standby = 1;
            #ifdef USE_INDICATOR_LED
            indicator_led_update(indicator_led_mode >> 4, 0);
            #elif defined(USE_AUX_RGB_LEDS)
            rgb_led_update(rgb_led_lockout_mode, arg);
            #endif
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #if defined(TICK_DURING_STANDBY)
    else if (event == EV_sleep_tick) {
        #ifdef DUAL_VOLTAGE_FLOOR
        if (((voltage < VOLTAGE_LOW_SAFE) && (voltage > DUAL_VOLTAGE_FLOOR)) || (voltage < DUAL_VOLTAGE_LOW_LOW_SAFE)) {
        #else
        if (voltage < VOLTAGE_LOW_SAFE) {
        #endif
            #ifdef USE_INDICATOR_LED
            indicator_led_update(6, arg);
            #elif defined(USE_AUX_RGB_LEDS)
            rgb_led_update(RGB_RED|RGB_BREATH, arg);
            #else
            if (0 == (arg & 0x1f)) blink_once();
            #endif
        } else {
            #ifdef USE_INDICATOR_LED
            indicator_led_update(indicator_led_mode >> 4, arg);
            #elif defined(USE_AUX_RGB_LEDS)
            rgb_led_update(rgb_led_lockout_mode, arg);
            #endif
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    // 3 clicks: exit and turn off
    else if (event == EV_3clicks) {
        blink_once_aux();
        set_state(off_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 4 clicks: exit and turn on
    else if (event == EV_4clicks) {
        #ifdef USE_MANUAL_MEMORY
        // FIXME: memory timer is totally ignored
        if (manual_memory)
            set_state(steady_state, manual_memory);
        else
        #endif
        set_state(steady_state, memorized_level);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 4 clicks, but hold last: exit and start at floor
    else if (event == EV_click4_hold) {
        //blink_once();
        blip();
        // reset button sequence to avoid activating anything in ramp mode
        current_event = 0;
        // ... and back to ramp mode
        set_state(steady_state, 1);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #ifndef USE_TINT_RAMPING
    #ifndef DISABLE_UNLOCK_TO_TURBO
    // 5 clicks: exit and turn on at ceiling level
    else if (event == EV_5clicks) {
        set_state(steady_state, MAX_LEVEL);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif //ifndef DISABLE_UNLOCK_TO_TURBO
    #endif //ifndef USE_TINT_RAMPING

    ////////// Every action below here is blocked in the simple UI //////////
    #ifdef USE_SIMPLE_UI
    if (simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    #endif

    #ifdef USE_AUTOLOCK
    // 10H: configure the autolock option
    else if (event == EV_click10_hold) {
        push_state(autolock_config_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    #if defined(USE_INDICATOR_LED)
    // 7/8 clicks: rotate through indicator LED modes (lockout mode)
    #if defined(AUX_CONFIG_CLICK_EVENT)
    else if (event == AUX_CONFIG_CLICK_EVENT) {
    #else
    else if (event == EV_7clicks) {
    #endif
        #if defined(USE_INDICATOR_LED)
            uint8_t mode = indicator_led_mode >> 4;
            #ifdef TICK_DURING_STANDBY
            mode = (mode + 1) % 6;
            #else
            mode = (mode + 1) % 3;
            #endif
            #ifdef INDICATOR_LED_SKIP_LOW
            if (mode == 1) { mode ++; }
            #endif
            indicator_led_mode = (mode << 4) + (indicator_led_mode & 0xf);
            indicator_led_update(mode, 0);
        #elif defined(USE_AUX_RGB_LEDS)
        #endif
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

    #elif defined(USE_AUX_RGB_LEDS)
    // 7 clicks: change RGB aux LED pattern
    #if defined(AUX_CONFIG_CLICK_EVENT)
    else if (event == AUX_CONFIG_CLICK_EVENT) {
    #else
    else if (event == EV_7clicks) {
    #endif
        uint8_t mode = (rgb_led_lockout_mode >> 4) + 1;
        mode = mode % RGB_LED_NUM_PATTERNS;
        rgb_led_lockout_mode = (mode << 4) | (rgb_led_lockout_mode & 0x0f);
        rgb_led_update(rgb_led_lockout_mode, 0);
        save_config();
        blink_once();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 7H: change RGB aux LED color
    #if defined(AUX_CONFIG_HOLD_EVENT)
    else if (event == AUX_CONFIG_HOLD_EVENT) {
    #else
    else if (event == EV_click7_hold) {
    #endif
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (rgb_led_lockout_mode & 0x0f) + 1;
            mode = mode % RGB_LED_NUM_COLORS;
            rgb_led_lockout_mode = mode | (rgb_led_lockout_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(rgb_led_lockout_mode, arg);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 7H, release: save new color
    #if defined(AUX_CONFIG_HOLD_RELEASE_EVENT)
    else if (event == AUX_CONFIG_HOLD_RELEASE_EVENT) {
    #else
    else if (event == EV_click7_hold_release) {
    #endif
        setting_rgb_mode_now = 0;
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    return EVENT_NOT_HANDLED;
}

#ifdef USE_AUTOLOCK
// set the auto-lock timer to N minutes, where N is the number of clicks
void autolock_config_save(uint8_t step, uint8_t value) {
    autolock_time = value;
}

uint8_t autolock_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 1, autolock_config_save);
}
#endif  // #ifdef USE_AUTOLOCK


#endif

