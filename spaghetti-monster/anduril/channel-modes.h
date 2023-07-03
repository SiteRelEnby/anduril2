// channel-modes.h: Multi-channel functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

// not actually a mode, more of a fallback under other modes
uint8_t channel_mode_state(Event event, uint16_t arg);

#if NUM_CHANNEL_MODES > 1
uint8_t channel_mode_config_state(Event event, uint16_t arg);
#endif

    #if (NUM_CHANNEL_MODES > 1)
      #if((defined(EVENT_CHANNEL_CYCLE_OFF_HOLD) || (defined(EVENT_CHANNEL_CYCLE_ON_HOLD))))
        static uint8_t reset_level = 0;
      #endif
    #endif

#if defined(USE_CHANNEL_MODE_ARGS) && defined(USE_STEPPED_TINT_RAMPING)
// calculate the nearest tint value which would be valid at the moment
uint8_t nearest_tint_value(const int16_t target);
#endif

