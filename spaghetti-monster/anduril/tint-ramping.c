
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
    //static uint8_t momentary_opposite_active = 0;
    static uint8_t prev_level = 0;
    #ifdef CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT
    static uint8_t channel_switch = 0;
    #endif
    #if defined(CHANNEL_1_TURBO_HOLD_EVENT) || defined (CHANNEL_2_TURBO_HOLD_EVENT)
    static uint8_t momentary_from_lock = 0; //temporary variable to store if we are in a momentary mode from lockout_state for channel-specific turbo modes
    #endif

    // making this match TK's idea: https://budgetlightforum.com/t/how-do-you-lock-your-lights/217263/7
    // 3C: currently, instant switch channels. In the future, switch between different defined tint ramps (https://budgetlightforum.com/t/group-buy-lt1s-pro-with-anduril2-nichia-519a-660nm-red-leds/71123/298)

    if (0) {}

    #ifdef CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT
    else if (event == CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT) {
        ///// tint-toggle mode
        // toggle once on first frame; ignore other frames
        if (tint_style){ //this would normally mean it's in instant channel switching mode, but see the FIXME below
            #ifdef USE_OPPOSITE_TINTRAMP_KLUDGE //FIXME: this is an ugly hack. see siterelenby-dm112 .h file
            channel_switch = 0;
            #else
            channel_switch = 1;
            #endif
        }
        else { //normally in channel ramping mode, see FIXME
            #ifdef USE_OPPOSITE_TINTRAMP_KLUDGE //FIXME: this is an ugly hack. see siterelenby-dm112 .h file
            channel_switch = 1;
            #else
            channel_switch = 0;
            #endif
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
    else if (event == CHANNEL_SWITCH_CONFIGURABLE_HOLD_RELEASE_EVENT) {
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
    #endif

    #ifdef CHANNEL_SWITCH_ONLY_CLICK_EVENT
    else if (event == CHANNEL_SWITCH_ONLY_CLICK_EVENT) {
            // force tint to be 1 or 254
            if (tint != 254) { tint = 1; tint_ramp_direction = -1; }
            else { tint_ramp_direction = 1; }
            // invert between 1 and 254
            tint = tint ^ 0xFF;
            set_level(actual_level);
            return EVENT_HANDLED;
        }
    #endif

    #ifdef CHANNEL_CYCLE_HOLD_EVENT
    else if (event == CHANNEL_CYCLE_HOLD_EVENT) {
            if (arg == 0){
                // force tint to be 1 or 254
                if (tint != 254) { tint = 1; }
                // invert between 1 and 254
                tint = tint ^ 0xFF;
                set_level(actual_level);
            }
            //keep alternating current channels if held. In the future this will cycle through all available channels for >2.
            else if ((arg % 32) == 0){ //every 32 frames (TODO: configurable?)
                tint = tint ^ 0xFF;
                set_level(actual_level);
            }
            return EVENT_HANDLED;
        }
    #endif


    #if defined(CHANNEL_RAMP_ONLY_HOLD_EVENT) && defined(CHANNEL_RAMP_ONLY_RELEASE_EVENT)
    else if ( event == CHANNEL_RAMP_ONLY_HOLD_EVENT) {
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
    else if (event == CHANNEL_RAMP_ONLY_RELEASE_EVENT) {
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
    #endif

    //TODO: These should probably be moved to their own file?

    //disable special tint ramping stuff when in strobe/momentary mode to avoid Weird Things happening (but we want this to work when off/locked)
    else if ((current_state != strobe_state) && (current_state != momentary_state)){

        // momentary opposite channel
        #ifdef MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT
        if (event == MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT) {
            if (! arg) {  // first frame only, to allow thermal regulation to work
                //if (momentary_opposite_active == 0) {
                  //invert tint ramp
                  //momentary_opposite_active = 1;
                  tint = tint ^ 0xFF;
                  set_level(actual_level);
                  return EVENT_HANDLED;
                //}
            }
            else {
                return EVENT_HANDLED;
            }
            //TODO: have a way to make it all or nothing switch (below) or ramp inversion (above)
            //if (tint >= 129) { tint = 1; }
            //else { tint = 254; }
        }
        //return to first channel on release
        else if (event == MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT_RELEASE) {
            tint = tint ^ 0xFF;
            //momentary_opposite_active = 0;
            //if (tint >= 129) { tint = 1; }
            //else { tint = 254; }
            //set_level_and_therm_target(memorized_level);
            set_level(actual_level);
            return EVENT_HANDLED;
        }
        #endif //MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT

        #ifdef TURBO_200_CLICK_EVENT
        else if (event == TURBO_200_CLICK_EVENT){
            if (target_level == MAX_LEVEL) { //if we're already at 200%
                set_level_and_therm_target(memorized_level); //go back to previous level if we set it
            }
            else {
                memorized_level = nearest_level(actual_level); //save previous level
                set_level_and_therm_target(MAX_LEVEL);
            }
            //set_level_and_therm_target(turbo_level);
            //memorized_level = nearest_level(actual_level);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        #endif


        #if defined(USE_TINT_RAMPING) && defined(DUALCHANNEL_2C_ALWAYS_USE_SINGLE_CHANNEL)
        //2C: single channel ceiling, and exit to previous if already there
        else if (event == EV_2clicks){
            if (target_level == ramp_ceil) { //if we're already at 200%
                set_level_and_therm_target(memorized_level); //go back to previous level if we set it (TODO: does this work right if ramped manually to ceiling?)
            }
            else {
                memorized_level = nearest_level(actual_level); //save previous level
                set_level_and_therm_target(ramp_ceil); //go to ceiling
            }
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        #endif //if defined(USE_TINT_RAMPING) && defined(DUALCHANNEL_2C_ALWAYS_USE_SINGLE_CHANNEL)

        #if defined(TURBO_200_MOMENTARY_HOLD_EVENT) && defined (TURBO_200_MOMENTARY_HOLD_RELEASE_EVENT)
        else if (event == TURBO_200_MOMENTARY_HOLD_EVENT){
            //momentary 200%
            if (!arg){
                memorized_level = nearest_level(actual_level); //save previous level
                set_level_and_therm_target(MAX_LEVEL);
            }
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        else if (event == TURBO_200_MOMENTARY_HOLD_RELEASE_EVENT){
            set_level_and_therm_target(memorized_level);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        #endif


        //channel-specific turbo shortcuts
        //these should probably really be their own file?

        #if (defined(CHANNEL_1_TURBO_CLICK_EVENT) && !defined(DISABLE_UNLOCK_TO_TURBO))
          else if ((event == CHANNEL_1_TURBO_CLICK_EVENT) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){ //TODO: can this just be the event, or are there other states that need to be handled?
        #endif
        #if (defined(CHANNEL_1_TURBO_CLICK_EVENT) && defined(DISABLE_UNLOCK_TO_TURBO))
          else if ((event == CHANNEL_1_TURBO_CLICK_EVENT) && ((current_state == steady_state) || (current_state == off_state))){
        #endif //#ifndef DISABLE_UNLOCK_TO_TURBO
        #if defined(CHANNEL_1_TURBO_CLICK_EVENT)
            tint = 254;
            set_level_and_therm_target(130);
            set_state(steady_state, 130);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
        }
        #endif //if defined(CHANNEL_1_TURBO_CLICK_EVENT)

        #ifdef CHANNEL_1_TURBO_HOLD_EVENT
          //if ((event == CHANNEL_1_TURBO_HOLD_EVENT) && ((current_state == steady_state) || (current_state == off_state))){ //TODO?
          else if ((event == CHANNEL_1_TURBO_HOLD_EVENT) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){
            if (!arg) {
                prev_tint = tint;
                prev_level = actual_level;
                tint = 254;
                if (current_state == lockout_state){ momentary_from_lock = 1 ; set_state(steady_state, arg); } //necessary to get it to stay on from lock? using push_state() doesn't seem to work.
                set_level_and_therm_target(130);
            }
            return EVENT_HANDLED;
        }
        #endif //ifdef CHANNEL_1_TURBO_HOLD_EVENT

        ////#ifndef USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING
        ////else if (event == EV_click5_hold_release){
        ////#else
        ////else if (((event == EV_click4_hold_release) && (current_state == steady_state)) || ((event == EV_click5_hold_release) && current_state != steady_state)) { //4H when on, otherwise 5H
        ////#endif
        #ifdef CHANNEL_1_TURBO_HOLD_RELEASE_EVENT
            //if ((event == CHANNEL_1_TURBO_HOLD_RELEASE_EVENT) && ((current_state == steady_state) || (current_state == off_state))){ //TODO?
          else if ((event == CHANNEL_1_TURBO_HOLD_RELEASE_EVENT) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){
            if (momentary_from_lock == 1){ set_state(lockout_state, arg); momentary_from_lock = 0; }
            tint = prev_tint;
            set_level_and_therm_target(prev_level);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
          }
        #endif //#ifdef CHANNEL_1_TURBO_HOLD_RELEASE_EVENT

        //5/6C: channel 2 turbo shortcut
        ////#ifndef USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING
        ////else if (event == EV_6clicks) {
        ////#else
        ////else if (((event == EV_5clicks) && (current_state == steady_state)) || ((event == EV_6clicks) && current_state != steady_state)) { //5H when on, otherwise 6H
        ////#endif
        #if (defined(CHANNEL_2_TURBO_CLICK_EVENT) && !defined(DISABLE_UNLOCK_TO_TURBO))
          else if ((event == CHANNEL_2_TURBO_CLICK_EVENT) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){
        #endif
        #if (defined(CHANNEL_2_TURBO_CLICK_EVENT) && defined(DISABLE_UNLOCK_TO_TURBO))
          else if ((event == CHANNEL_2_TURBO_CLICK_EVENT) && ((current_state == steady_state) || (current_state == off_state))){
        #endif //#ifndef DISABLE_UNLOCK_TO_TURBO
        #if defined(CHANNEL_2_TURBO_CLICK_EVENT)
          if (! arg){
            tint = 1;
            set_level_and_therm_target(130);
            set_state(steady_state, 130);
            if (current_state != lockout_state) {return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;}
          }
        }
        #endif //if defined(CHANNEL_2_TURBO_CLICK_EVENT)

        //5/6H: Momentary channel 2 turbo
        ////#ifndef USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING
        ////else if (event == EV_click6_hold) {
        ////#else
        ////else if (((event == EV_click5_hold) && (current_state == steady_state)) || ((event == EV_click6_hold) && current_state != steady_state)) { //5H when on, otherwise 6H
        ////#endif
        #ifdef CHANNEL_2_TURBO_HOLD_EVENT
          //if ((event == CHANNEL_2_TURBO_HOLD_EVENT) && ((current_state == steady_state) || (current_state == off_state))){ //TODO?
          else if ((event == CHANNEL_2_TURBO_HOLD_EVENT) && ((current_state == steady_state) || (current_state == off_state) || (current_state == lockout_state))){
            if (!arg){
                prev_tint = tint;
                prev_level = actual_level;
                tint = 1;
                if (current_state == lockout_state){ momentary_from_lock = 1 ; set_state(steady_state, arg); } //necessary to get it to stay on from lock? using push_state() doesn't seem to work.
                set_level_and_therm_target(130);
            }
            return EVENT_HANDLED;
        }
        #endif

        #ifdef CHANNEL_2_TURBO_HOLD_RELEASE_EVENT
          else if (event == CHANNEL_2_TURBO_HOLD_RELEASE_EVENT) {
            if (momentary_from_lock == 1){ set_state(lockout_state, arg); momentary_from_lock = 0; }
            tint = prev_tint;
            set_level_and_therm_target(prev_level);
            return TRANS_RIGHTS_ARE_HUMAN_RIGHTS;
          }
        #endif

    } //disable special tint ramping stuff when in strobe mode to avoid Weird Things happening

    return EVENT_NOT_HANDLED;
}


#endif

