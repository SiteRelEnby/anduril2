/*
 * off-mode.c: "Off" mode for Anduril.
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

#ifndef OFF_MODE_C
#define OFF_MODE_C

#include "off-mode.h"

#ifdef USE_SUNSET_TIMER
#include "sunset-timer.h"
#endif

uint8_t off_state(Event event, uint16_t arg) {
    #ifdef USE_TINT_RAMPING
    static uint8_t prev_tint;
    #endif
    // turn emitter off when entering state
    if (event == EV_enter_state) {
        #if defined(USE_AUX_RGB_LEDS) || defined(USE_INDICATOR_LED)
        aux_led_reset = 1;
        #endif
        set_level(0);
        #ifdef USE_INDICATOR_LED
        indicator_led_update(indicator_led_mode & 0xf, 0);
        #elif defined(USE_AUX_RGB_LEDS)
        rgb_led_update(rgb_led_off_mode, 0);
        #endif
        #ifdef USE_SUNSET_TIMER
        sunset_timer = 0;  // needs a reset in case previous timer was aborted
        #endif
        // sleep while off  (lower power use)
        // (unless delay requested; give the ADC some time to catch up)
        if (! arg) { go_to_standby = 1; }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // go back to sleep eventually if we got bumped but didn't leave "off" state
    else if (event == EV_tick) {
        if (arg > HOLD_TIMEOUT) {
            go_to_standby = 1;
            #ifdef USE_INDICATOR_LED
            indicator_led_update(indicator_led_mode & 0xf, 0);
            #elif defined(USE_AUX_RGB_LEDS)
            rgb_led_update(rgb_led_off_mode, arg);
            #endif
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #if defined(TICK_DURING_STANDBY)
    // blink the indicator LED, maybe
    else if (event == EV_sleep_tick) {
        #ifdef USE_MANUAL_MEMORY_TIMER
        // reset to manual memory level when timer expires
        if (manual_memory &&
                (arg >= (manual_memory_timer * SLEEP_TICKS_PER_MINUTE))) {
            memorized_level = manual_memory;
            #ifdef USE_TINT_RAMPING
            tint = manual_memory_tint;
            #endif
        }
        #endif

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
            indicator_led_update(indicator_led_mode & 0xf, arg);
            #elif defined(USE_AUX_RGB_LEDS)
            rgb_led_update(rgb_led_off_mode, arg);
            #endif
        }
        #ifdef USE_AUTOLOCK
            // lock the light after being off for N minutes
            uint16_t ticks = autolock_time * SLEEP_TICKS_PER_MINUTE;
            if ((autolock_time > 0)  && (arg > ticks)) {
                set_state(lockout_state, 0);
            }
        #endif  // ifdef USE_AUTOLOCK
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    #if (B_TIMING_ON == B_PRESS_T)
    // hold (initially): go to lowest level (floor), but allow abort for regular click
    else if (event == EV_click1_press) {
        set_level(nearest_level(1));
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif  // B_TIMING_ON == B_PRESS_T
    // hold: go to lowest level
    else if (event == EV_click1_hold) {
        #if (B_TIMING_ON == B_PRESS_T)
        #ifdef MOON_TIMING_HINT
        if (arg == 0) {
            // let the user know they can let go now to stay at moon
            blip();
        } else
        #endif
        #else  // B_RELEASE_T or B_TIMEOUT_T
        set_level(nearest_level(1));
        #endif
        #ifdef USE_RAMP_AFTER_MOON_CONFIG
        if (dont_ramp_after_moon) {
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        #endif
        // don't start ramping immediately;
        // give the user time to release at moon level
        //if (arg >= HOLD_TIMEOUT) {  // smaller
        if (arg >= (!ramp_style) * HOLD_TIMEOUT) {  // more consistent
            set_state(steady_state, 1);
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // hold, release quickly: go to lowest level (floor)
    else if (event == EV_click1_hold_release) {
        set_state(steady_state, 1);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #if (B_TIMING_ON != B_TIMEOUT_T)
    // 1 click (before timeout): go to memorized level, but allow abort for double click
    else if (event == EV_click1_release) {
        #if defined(USE_MANUAL_MEMORY) && !defined(USE_MANUAL_MEMORY_TIMER)
            // this clause probably isn't used by any configs any more
            // but is included just in case someone configures it this way
            if (manual_memory) {
                memorized_level = manual_memory;
                #ifdef USE_TINT_RAMPING
                tint = manual_memory_tint;
                #endif
            }
        #endif
        set_level(nearest_level(memorized_level));
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif  // if (B_TIMING_ON != B_TIMEOUT_T)
    // 1 click: regular mode
    else if (event == EV_1click) {
        #if (B_TIMING_ON != B_TIMEOUT_T)
        // brightness was already set; reuse previous value
        set_state(steady_state, actual_level);
        #else
        // FIXME: B_TIMEOUT_T breaks manual_memory and manual_memory_timer
        //        (need to duplicate manual mem logic here, probably)
        set_state(steady_state, memorized_level);
        #endif
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // click, hold: momentary at ceiling or turbo
    else if (event == EV_click2_hold) {
        uint8_t turbo_level;  // how bright is "turbo"?

        #if defined(USE_2C_STYLE_CONFIG)  // user can choose 2C behavior
            uint8_t style_2c = ramp_2c_style;
            #ifdef USE_SIMPLE_UI
            // simple UI has its own turbo config
            if (simple_ui_active) style_2c = ramp_2c_style_simple;
            #endif
            // 0  = ceiling
            // 1+ = full power
            if (0 == style_2c) turbo_level = nearest_level(MAX_LEVEL);
            else turbo_level = MAX_LEVEL;
        #else
            // simple UI: ceiling
            // full UI: full power
            #ifdef USE_SIMPLE_UI
            if (simple_ui_active) turbo_level = nearest_level(MAX_LEVEL);
            else
            #endif
            turbo_level = MAX_LEVEL;
        #endif

        set_level(turbo_level);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    else if (event == EV_click2_hold_release) {
        set_level(0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 2 clicks: highest mode (ceiling)
    else if (event == EV_2clicks) {
        set_state(steady_state, MAX_LEVEL);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 3 clicks (initial press): off, to prep for later events
    else if (event == EV_click3_press) {
        set_level(0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #ifdef USE_BATTCHECK
    // 3 clicks: battcheck mode / blinky mode group 1
    else if (event == EV_3clicks) {
        set_state(battcheck_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    #ifdef USE_LOCKOUT_MODE
    // 4 clicks: soft lockout
    else if (event == EV_4clicks) {
        blink_once();
        set_state(lockout_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    #if defined(USE_FACTORY_RESET) && defined(USE_SOFT_FACTORY_RESET)
    // 13 clicks and hold the last click: invoke factory reset (reboot)
    else if (event == EV_click13_hold) {
        reboot();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    #ifdef USE_VERSION_CHECK
    // 15+ clicks: show the version number
    else if (event == EV_15clicks) {
        set_state(version_check_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    #ifdef USE_SIMPLE_UI
    // 10 clicks, but hold last click: turn simple UI off (or configure it)
    else if ((event == EV_click10_hold) && (!arg)) {
        if (simple_ui_active) {  // turn off simple UI
            blink_once();
            simple_ui_active = 0;
            save_config();
        }
        else {  // configure simple UI ramp
            push_state(simple_ui_config_state, 0);
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

    ////////// Every action below here is blocked in the simple UI //////////
    if (simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    // 10 clicks: enable simple UI
    else if (event == EV_10clicks) {
        blink_once();
        simple_ui_active = 1;
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    // click, click, long-click: strobe mode
    #ifdef USE_STROBE_STATE
    else if (event == EV_click3_hold) {
        set_state(strobe_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #elif defined(USE_BORING_STROBE_STATE)
    else if (event == EV_click3_hold) {
        set_state(boring_strobe_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    #ifdef USE_MOMENTARY_MODE
    // 5 clicks: momentary mode
    //moved to 11C
    else if (event == EV_12clicks) {
        blink_once();
        set_state(momentary_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    #ifdef USE_INDICATOR_LED
    // 7 clicks: change indicator LED mode
    #if defined(USE_8C_AUX_CONFIG)
    else if (event == EV_8clicks) {
    #else
    else if (event == EV_7clicks) {
    #endif
        uint8_t mode = (indicator_led_mode & 0xf) + 1;
        #ifdef TICK_DURING_STANDBY
        mode = mode % 6;
        #else
        mode = mode % 3;
        #endif
        #ifdef INDICATOR_LED_SKIP_LOW
        if (mode == 1) { mode ++; }
        #endif
        indicator_led_mode = (indicator_led_mode & 0xf0) | mode;
        indicator_led_update(mode, 0);
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #elif defined(USE_AUX_RGB_LEDS)
    // 7 clicks: change RGB aux LED pattern
    #if defined(USE_8C_AUX_CONFIG)
    else if (event == EV_8clicks) {
    #else
    else if (event == EV_7clicks) {
    #endif
        uint8_t mode = (rgb_led_off_mode >> 4) + 1;
        mode = mode % RGB_LED_NUM_PATTERNS;
        rgb_led_off_mode = (mode << 4) | (rgb_led_off_mode & 0x0f);
        rgb_led_update(rgb_led_off_mode, 0);
        save_config();
        blink_once();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // 7 clicks (hold last): change RGB aux LED color
    #if defined(USE_8C_AUX_CONFIG)
    else if (event == EV_click8_hold) {
    #else
    else if (event == EV_click7_hold) {
    #endif
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (rgb_led_off_mode & 0x0f) + 1;
            mode = mode % RGB_LED_NUM_COLORS;
            rgb_led_off_mode = mode | (rgb_led_off_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(rgb_led_off_mode, arg);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #if defined(USE_8C_AUX_CONFIG)
    else if (event == EV_click8_hold_release) {
    #else
    else if (event == EV_click7_hold_release) {
    #endif
        setting_rgb_mode_now = 0;
        save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif  // end 7 clicks


    //5C: Channel 1 turbo shortcut // TODO: make this do something sensible on single channel lights. config option to swap channels around? CH1 should have the FET on most lights? which channel is which?
    #ifdef USE_TINT_RAMPING
    else if (event == EV_5clicks) {
        tint = 254;
        set_level_and_therm_target(130);
        set_state(steady_state, 130);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    //5H: Momentary throw channel (on DM1.12) turbo
    else if (event == EV_click5_hold) {
        prev_tint = tint;
        tint = 254;
        set_level_and_therm_target(130);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    else if (event == EV_click5_hold_release){
        //go back to off mode
        set_level(0);
        tint = prev_tint;
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }

    //6C: Flood channel turbo shortcut
    else if (event == EV_6clicks) {
        tint = 1;
        set_level_and_therm_target(130);
        set_state(steady_state, 130);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    //6H: Momentary flood channel (on DM1.12) turbo
    else if (event == EV_click6_hold) {
        prev_tint = tint;
        tint = 1;
        set_level_and_therm_target(130);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    else if (event == EV_click6_hold_release){
        //go back to off mode
        set_level(0);
        tint = prev_tint;
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    #ifdef USE_GLOBALS_CONFIG
    // 9 clicks, but hold last click: configure misc global settings
    else if ((event == EV_click9_hold) && (!arg)) {
        push_state(globals_config_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif

    return EVENT_NOT_HANDLED;
}


#endif

