/*
 * misc.c: Misc extra functions for Anduril.
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

#ifndef MISC_C
#define MISC_C

#include "misc.h"

/* no longer used
void blink_confirm(uint8_t num) {
    uint8_t brightness = actual_level;
    uint8_t bump = actual_level + BLINK_BRIGHTNESS;
    if (bump > MAX_LEVEL) bump = 0;
    for (; num>0; num--) {
        set_level(bump);
        delay_4ms(10/4);
        set_level(brightness);
        if (num > 1) { delay_4ms(100/4); }
    }
}
*/

// make a short, visible pulse
// (either brighter or darker, depending on current brightness)
#ifndef BLINK_ONCE_TIME
#define BLINK_ONCE_TIME 10
#endif
#ifndef BLINK_BRIGHTNESS
#define BLINK_BRIGHTNESS (MAX_LEVEL/6)
#endif
void blink_once() {
    uint8_t brightness = actual_level;
    uint8_t bump = brightness + BLINK_BRIGHTNESS;
    if (bump > MAX_LEVEL) bump = 0;

    set_level(bump);
    delay_4ms(BLINK_ONCE_TIME/4);
    set_level(brightness);
}

void blink_once_aux(uint8_t blink_once_aux_colour) {
    #ifdef USE_MAIN_LEDS_FOR_ALL_BLINKS //feature flag to retain old behaviour
      blink_once();
    #endif

    #ifndef USE_MAIN_LEDS_FOR_ALL_BLINKS
      #if defined(USE_AUX_RGB_LEDS) && !defined(NO_AUX)
        rgb_led_update(blink_once_aux_colour|RGB_HIGH, 0);
        delay_4ms(BLINK_ONCE_AUX_TIME_4MS);
        rgb_led_update(RGB_OFF, 0);
      #endif //if defined(USE_AUX_RGB_LEDS) && !defined(NO_AUX)
      #if defined(USE_INDICATOR_LED) && !defined(NO_AUX) //indicator LED only
        indicator_led(2);
        delay_4ms(BLINK_ONCE_AUX_TIME_4MS);
        indicator_led(0);
      #endif
      #if defined (USE_BUTT0N_LED) && !defined(NO_AUX)
        button_led_set(2);
        delay_4ms(BLINK_ONCE_AUX_TIME_4MS);
        button_led_set(0);
      #endif
      #if ((!defined(USE_INDICATOR_LED)) && ((!defined(USE_BUTT0N_LED)) && (!defined(USE_AUX_RGB_LEDS))) || (defined(NO_AUX)))
        // or fall back to main emitter if we have no AUX LED and no indicator LED
        blink_once();
      #endif
    #endif //ifndef USE_MAIN_LEDS_FOR_ALL_BLINKS
    #if ((defined(NO_AUX)) || (defined(USE_MAIN_LEDS_FOR_ALL_BLINKS)))
      // use main emitter if USE_MAIN_LEDS_FOR_ALL_BLINKS
      blink_once();
    #endif //ifndef USE_MAIN_LEDS_FOR_ALL_BLINKS
    delay_4ms(2); //short delay so the blink doesn't get lost if the aux then go to any high mode
}

void blink_some(uint8_t times) {
    blink_once();
    for (uint8_t i = 1; i < times; i++) {
        delay_4ms(100); //about 0.4s
        blink_once();
    }
}

// Just go dark for a moment to indicate to user that something happened
void blip() {
    blip_ms(12);
}

// ms must be multiples of 4
void blip_ms(uint8_t ms) {
    uint8_t temp = actual_level;
    set_level(0);
    delay_4ms(ms/4);
    set_level(temp);
}


#endif

