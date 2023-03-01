
/*
 * tint-ramping.c: Tint ramping functions for Anduril.
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

#ifndef TINT_RAMPING_C
#define TINT_RAMPING_C

#include "tint-ramping.h"

uint8_t tint_ramping_state(Event event, uint16_t arg) {
    static int8_t tint_ramp_direction = 1;
    static uint8_t prev_tint = 0;
    // don't activate auto-tint modes unless the user hits the edge
    // and keeps pressing for a while
    static uint8_t past_edge_counter = 0;
    // bugfix: click-click-hold from off to strobes would invoke tint ramping
    // in addition to changing state...  so ignore any tint-ramp events which
    // don't look like they were meant to be here
    static uint8_t active = 0;
    static uint8_t momentary_opposite_active = 0;
    static uint8_t prev_level = 0;
    static uint8_t channel_switch = 0;

    // click, click, hold: change the tint
    if ( (event == EV_click3_hold) || (event == EV_click8_hold )) {
        ///// tint-toggle mode
        // toggle once on first frame; ignore other frames
        if (tint_style){ //this would normally mean it's in instant channel switching mode, but see the FIXME below
            if (event == EV_click3_hold) {
                //3H: use channel switching as configured
                #ifdef USE_OPPOSITE_TINTRAMP_KLUDGE //FIXME: this is an ugly hack. see siterelenby-dm112 .h file
                channel_switch = 0;
                #else
                channel_switch = 1;
                #endif
            }
            else {
                //8H: Do the opposite.
                #ifdef USE_OPPOSITE_TINTRAMP_KLUDGE //FIXME: this is an ugly hack. see siterelenby-dm112 .h file
                channel_switch = 1;
                #else
                channel_switch = 0;
                #endif
            }
        }
        else { //normally in channel ramping mode, see FIXME
            if (event == EV_click3_hold) {
                //3H: use channel ramping as configured
                #ifdef USE_OPPOSITE_TINTRAMP_KLUDGE //FIXME: this is an ugly hack. see siterelenby-dm112 .h file
                channel_switch = 1;
                #else
                channel_switch = 0;
                #endif
            }
            else {
                //8H: Do the opposite.
                #ifdef USE_OPPOSITE_TINTRAMP_KLUDGE //FIXME: this is an ugly hack. see siterelenby-dm112 .h file
                channel_switch = 0;
                #else
                channel_switch = 1;
                #endif
            }
        }
        if (channel_switch == 1) {
            // only respond on first frame
            if (arg) return EVENT_NOT_HANDLED;

            // force tint to be 1 or 254
            if (tint != 254) { tint = 1; }
            // invert between 1 and 254
            tint = tint ^ 0xFF;
            set_level(actual_level);
            return EVENT_HANDLED;
        }

        ///// smooth tint-ramp mode
        // reset at beginning of movement
        if (! arg) {
            active = 1;  // first frame means this is for us
            past_edge_counter = 0;  // doesn't start until user hits the edge
        }
        // ignore event if we weren't the ones who handled the first frame
        if (! active) return EVENT_HANDLED;

        // change normal tints
        if ((tint_ramp_direction > 0) && (tint < 254)) {
            tint += 1;
        }
        else if ((tint_ramp_direction < 0) && (tint > 1)) {
            tint -= 1;
        }
        // if the user kept pressing long enough, go the final step
        if (past_edge_counter == 64) {
            past_edge_counter ++;
            tint ^= 1;  // 0 -> 1, 254 -> 255
            blip();
        }
        // if tint change stalled, let user know we hit the edge
        else if (prev_tint == tint) {
            if (past_edge_counter == 0) blip();
            // count up but don't wrap back to zero
            if (past_edge_counter < 255) past_edge_counter ++;
        }
        prev_tint = tint;
        set_level(actual_level);
        return EVENT_HANDLED;
    }

    // click, click, hold, release: reverse direction for next ramp
    else if ( (event == EV_click3_hold_release) || (event == EV_click8_hold_release) ) {
        active = 0;  // ignore next hold if it wasn't meant for us
        // reverse
        tint_ramp_direction = -tint_ramp_direction;
        if (tint <= 1) tint_ramp_direction = 1;
        else if (tint >= 254) tint_ramp_direction = -1;
        // remember tint after battery change
        save_config();
        // bug?: for some reason, brightness can seemingly change
        // from 1/150 to 2/150 without this next line... not sure why
        set_level(actual_level);
        return EVENT_HANDLED;
    }

    else if (current_state != strobe_state){ //disable special tint ramping stuff when in strobe mode to avoid Weird Things happening

        //4H: momentary opposite channel
        if (event == EV_click4_hold) {
            //if (! arg) {  // first frame only, to allow thermal regulation to work
                if (momentary_opposite_active == 0) {
                        //invert tint ramp
                        momentary_opposite_active = 1;
                        tint = tint ^ 0xFF;
                        set_level(actual_level);
                        return EVENT_HANDLED;
                }
            //}
            else {
                return EVENT_HANDLED;
            }
            //TODO: have a way to make it all or nothing switch (below) or ramp inversion (above)
            //if (tint >= 129) { tint = 1; }
            //else { tint = 254; }
        }
        //return to first channel on release
        else if (event == EV_click4_hold_release) {
            tint = tint ^ 0xFF;
            momentary_opposite_active = 0;
            //if (tint >= 129) { tint = 1; }
            //else { tint = 254; }
            //set_level_and_therm_target(memorized_level);
            set_level(actual_level);
            return EVENT_HANDLED;
        }

        //5C: Channel 1 turbo shortcut // TODO: config option to swap channels around?
        else if (event == EV_5clicks) {
            tint = 254;
            set_level_and_therm_target(130);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        //5H: Momentary channel 1 turbo
        else if (event == EV_click5_hold) {
            if (!arg) {
                prev_tint = tint;
                prev_level = actual_level;
                tint = 254;
                set_level_and_therm_target(130);
            }
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        else if (event == EV_click5_hold_release){
            //go back to ramp mode
            tint = prev_tint;
            set_level_and_therm_target(prev_level);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }

        //6C: channel 2 turbo shortcut
        else if (event == EV_6clicks) {
            tint = 1; //max flood on my dm1.12
            set_level_and_therm_target(130);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        //6H: Momentary channel 2 turbo
        else if (event == EV_click6_hold) {
            if (!arg){
                prev_tint = tint;
                prev_level = actual_level;
                tint = 1;
                set_level_and_therm_target(130);
            }
            return EVENT_HANDLED;
        }
        else if (event == EV_click6_hold_release){
            //go back to ramp mode
            tint = prev_tint;
            set_level_and_therm_target(prev_level);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
            //return EVENT_HANDLED;
        }
    } //disable special tint ramping stuff when in strobe mode to avoid Weird Things happening

    return EVENT_NOT_HANDLED;
}


#endif

