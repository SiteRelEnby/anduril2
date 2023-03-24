/*
 * beacon-mode.c: Beacon mode for Anduril.
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

#ifndef BEACON_MODE_C
#define BEACON_MODE_C

#include "beacon-mode.h"

inline void beacon_mode_iter() {
    // one iteration of main loop()
    if (! button_last_state) {
        set_level(beacon_brightness); //TODO: set brightness?
        #ifdef USE_BEACON_ON_CONFIG
	nice_delay_ms(beacon_on_ms);
        #else
        nice_delay_ms(100);
        #endif
        set_level(0);
        nice_delay_ms(((beacon_seconds) * 1000) - 100);
    }
}

uint8_t beacon_state(Event event, uint16_t arg) {
    #ifdef USE_BEACON_BRIGHTNESS_RAMP
    static int8_t beacon_ramp_direction = 1;
    #endif
    if (event == EV_enter_state) {
        beacon_brightness = memorized_level;
    }

    // 1 click: off
    if (event == EV_1click) {
        set_state(off_state, 0);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // TODO: use sleep ticks to measure time between pulses,
    //       to save power

    // 2 clicks: next blinky mode
    else if (event == EV_2clicks) {
        #if defined(USE_SOS_MODE) && defined(USE_SOS_MODE_IN_BLINKY_GROUP)
        set_state(sos_state, 0);
        #elif defined(USE_BATTCHECK)
        set_state(battcheck_state, 0);
        #elif defined(USE_THERMAL_REGULATION)
        set_state(tempcheck_state, 0);
        #endif
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // hold: configure beacon timing
    #ifndef USE_BEACON_ON_CONFIG
    else if (event == EV_click1_hold) {
    #else
    else if ((event == EV_click1_hold) || (event == EV_click2_hold)) {
    #endif //ifndef USE_BEACON_ON_CONFIG
        if (0 == (arg % TICKS_PER_SECOND)) {
            blink_once();
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    // release hold: save new timing
    else if (event == EV_click1_hold_release) {
        beacon_seconds = 1 + (arg / TICKS_PER_SECOND);
        //save_config();
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #ifdef USE_BEACON_ON_CONFIG
    // 2C: configure time spent on
    else if (event == EV_click2_hold_release) {
        if (0 == (arg % TICKS_PER_SECOND)) {
            blink_once();
        }
    }
    #endif //ifdef USE_BEACON_ON_CONFIG

    #ifdef USE_BEACON_BRIGHTNESS_RAMP
    else if (event == EV_click3_hold) {
        if ( beacon_brightness < 150 ) { //TODO: configurable - use ceiling? have a bump at 130 on dual channel lights?
          beacon_brightness += beacon_ramp_direction;
          set_level(beacon_brightness);
        }
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    else if (event == EV_click2_hold_release) {
        beacon_on_ms = 100 + (arg / TICKS_PER_SECOND);
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    else if (event == EV_click4_hold) {
        beacon_ramp_direction = 1;
        if (beacon_brightness > 2) { //TODO: use ramp floor? Level 1 is unreliable for 519A lights.
            beacon_brightness --;
            set_level(beacon_brightness);
        }
        // if the button is stuck, err on the side of safety and ramp down
        else if ((arg > TICKS_PER_SECOND * 5
                    #ifdef USE_RAMP_SPEED_CONFIG
                    // FIXME: count from time actual_level hits mode_max,
                    //   not from beginning of button hold
                    * ramp_speed
                    #endif
                    ) && (actual_level >= mode_max)) {
            ramp_direction = -1;
        }
        #ifdef USE_LOCKOUT_MODE
        // if the button is still stuck, lock the light
        else if ((arg > TICKS_PER_SECOND * 10
                    #ifdef USE_RAMP_SPEED_CONFIG
                    // FIXME: count from time actual_level hits mode_min,
                    //   not from beginning of button hold
                    * ramp_speed
                    #endif
                    ) && (actual_level <= mode_min)) {
            blink_once();
            set_state(lockout_state, 0);
        }
        #endif
        memorized_level = nearest_level((int16_t)actual_level \
                          + (step_size * ramp_direction));
        #if defined(BLINK_AT_RAMP_CEIL) || defined(BLINK_AT_RAMP_MIDDLE)
        // only blink once for each threshold
        if ((memorized_level != actual_level) && (
                0  // for easier syntax below
                #ifdef BLINK_AT_RAMP_MIDDLE_1
                || (memorized_level == BLINK_AT_RAMP_MIDDLE_1)
                #endif
                #ifdef BLINK_AT_RAMP_MIDDLE_2
                || (memorized_level == BLINK_AT_RAMP_MIDDLE_2)
                #endif
                #ifdef BLINK_AT_RAMP_CEIL
                || (memorized_level == mode_max)
                #endif
                #ifdef BLINK_AT_RAMP_FLOOR
                || (memorized_level == mode_min)
                #endif
                )) {
            blip();
        }
        #endif
        #if defined(BLINK_AT_STEPS)
        uint8_t foo = ramp_style;
        ramp_style = 1;
        uint8_t nearest = nearest_level((int16_t)actual_level);
        ramp_style = foo;
        // only blink once for each threshold
        if ((memorized_level != actual_level) &&
                    (ramp_style == 0) &&
                    (memorized_level == nearest)
                    )
        {
            blip();
        }
        #endif
        set_level_and_therm_target(memorized_level);
        #ifdef USE_SUNSET_TIMER
        timer_orig_level = actual_level;
        #endif
        return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
    }
    #endif
    return EVENT_NOT_HANDLED;
}


#endif

