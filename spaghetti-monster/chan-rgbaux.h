// channel modes for RGB aux LEDs
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

void set_level_auxred(uint8_t level);
void set_level_auxyel(uint8_t level);
void set_level_auxgrn(uint8_t level);
void set_level_auxcyn(uint8_t level);
void set_level_auxblu(uint8_t level);
void set_level_auxprp(uint8_t level);
void set_level_auxwht(uint8_t level);

#if (defined(USE_SET_LEVEL_AUXMIX) && defined(USE_CHANNEL_MODE_ARGS))
void set_level_auxmix(uint8_t level); //there's probably a better way to do this, but it'll do for now.
#endif

bool gradual_tick_null(uint8_t gt);

