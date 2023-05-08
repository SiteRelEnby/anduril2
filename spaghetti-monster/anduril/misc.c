// misc.c: Misc extra functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

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
    #ifdef BLINK_ONCE_USE_BLINKY_MODE_CHANNEL_SETTING
      static uint8_t orig_channel = cfg.channel_mode;
    #elif defined(BLINK_ONCE_CHANNEL)
      static uint8_t orig_channel = cfg.channel_mode;
      set_channel_mode(BLINK_LOCK_REMINDER_CHANNEL);
    #else
      uint8_t brightness = actual_level;
      uint8_t bump = brightness + BLINK_BRIGHTNESS;
      if (bump > MAX_LEVEL) bump = 0;

      set_level(bump);
      delay_4ms(BLINK_ONCE_TIME/4);
      set_level(brightness);
    #endif
}

void blink_once_channel(uint8_t channel) {
  #if (NUM_CHANNEL_MODES == 1)
    blink_once();
  #else
    uint8_t brightness = actual_level;
    if (cfg.channel_mode == channel){
      blink_once();
    }
    else {
      uint8_t orig_channel = cfg.channel_mode;
      set_level(0);
      set_channel_mode(channel);
      set_level(BLINK_BRIGHTNESS);
      delay_4ms(BLINK_ONCE_TIME/4);
      set_channel_mode(orig_channel);
      set_level(brightness);
    }
  #endif

//    #ifdef BLINK_ONCE_USE_BLINKY_MODE_CHANNEL_SETTING
//      static uint8_t orig_channel = cfg.channel_mode;
//      set_channel_mode(cfg.blink_channel);
//    #elif defined(BLINK_ONCE_CHANNEL)
//      static uint8_t orig_channel = cfg.channel_mode;
//      set_channel_mode(BLINK_ONCE_CHANNEL);
//    #else
//    #endif
}


// Just go dark for a moment to indicate to user that something happened
void blip() {
    uint8_t temp = actual_level;
    set_level(0);
    delay_4ms(3);
    set_level(temp);
}

