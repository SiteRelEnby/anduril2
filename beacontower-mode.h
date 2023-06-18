/*
 * beacontower-mode.h: Beacon/Obstruction Tower mode for Anduril.
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

#ifndef BEACONTOWER_MODE_H
#define BEACONTOWER_MODE_H

// beacon tower flash timing (30FPS default)
uint8_t beacontower_seconds = 2;

// beacon mode
uint8_t beacontower_state(Event event, uint16_t arg);

inline void beacontower_mode_iter();

#endif
