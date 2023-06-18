/*
 * beacontower-mode.c Beacon/Obstruction Tower mode for Anduril.
 *
 * 2020 - loneoceans
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


/*
 Beacon-Tower mode:

 	Similar to Beacon, but emulates the gradual turn on and off of traditional
    large incandescent bulbs of obstruction/beacon towers. The brightness and 
    the flashes per seconds (FPS) are configurable, with the default being the 
    standard 30 FPM, with roughly 50% duty cycle (slightly more for On).

       - Brightness is the user's last-ramped level, so set this in 
         ramping mode before starting beacon mode.

       - FPM is configured by holding the button. The light will blink
         once per second while holding the button. Release it after the 
         desired amount of time has passed, to set a new beacon flashing
         interval. 

         For example, to set a 5-second interval , hold the button for 5 seconds.

         Suppose the period of the light is set as t seconds:
         
         - Turn on ramp = nominally ~t/8s at ramp level ~60.
         - On at full brightness = 7/16*t s 
         - Turn off ramp = nominally ~t/4s at ramp level ~60
         - Off = 3/16 *ts
         
         Increasing the brightness also increases the time taken to ramp up
         and down, just like an incandescent would.

 Access from blinky / utility modes; the sequence is:

  - Battery check.
  - Temperature check (if light has a temperature sensor).
  - Beacon mode.
  - SOS mode (if enabled).
  - Beacon Tower mode (if enabled).
  
*/

#ifndef BEACONTOWER_MODE_C
#define BEACONTOWER_MODE_C

#include "beacontower-mode.h"

inline void beacontower_mode_iter() {
    // one iteration of main loop()
    if (! button_last_state) {
    	for (uint8_t i =0; i<memorized_level;i++){
    		set_level(i);
    		nice_delay_ms(2);
    	}
    	set_level(memorized_level);
        nice_delay_ms(beacontower_seconds*438);
		for (uint8_t i  = memorized_level;i>0;i--){
    		set_level(i);
            if (i>30) {nice_delay_ms(5);}
            else {nice_delay_ms(8);}
    	}
        set_level(0);
        nice_delay_ms(beacontower_seconds*188);
    }
}

uint8_t beacontower_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == EV_1click) {
        set_state(off_state, 0);
        return MISCHIEF_MANAGED;
    }
    // TODO: use sleep ticks to measure time between pulses,
    //       to save power

    // 2 clicks: next blinky mode
    else if (event == EV_2clicks) {
    	#if defined(USE_BATTCHECK_MODE)
        set_state(battcheck_state, 0);
        #elif defined(USE_THERMAL_REGULATION)
        set_state(tempcheck_state, 0);
        #elif defined(USE_BEACON_MODE)
        set_state(beacon_state, 0);
        #elif defined(USE_SOS_MODE) && defined(USE_SOS_MODE_IN_BLINKY_GROUP)
        set_state(sos_state, 0);
        #endif
        return MISCHIEF_MANAGED;
    }
    // hold: configure beacon tower timing
    else if (event == EV_click1_hold) {
        if (0 == (arg % TICKS_PER_SECOND)) {
            blink_once();
        }
        return MISCHIEF_MANAGED;
    }
    // release hold: save new timing
    else if (event == EV_click1_hold_release) {
        beacontower_seconds = 1 + (arg / TICKS_PER_SECOND);
        save_config();
        // to save beacontower_seconds? TODO
        return MISCHIEF_MANAGED;
    }
    return EVENT_NOT_HANDLED;
}


#endif

