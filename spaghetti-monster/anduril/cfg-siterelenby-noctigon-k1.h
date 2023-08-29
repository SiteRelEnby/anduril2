// Noctigon K1 config options for Anduril
// Copyright (C) 2019-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-noctigon-k1.h"

////////////////////////////////
#define NUM_MAIN_CHANNELS 1
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading


#define TICK_DURING_STANDBY

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_RELEASE_T
#define B_TIMING_OFF B_TIMEOUT_T

//setup memory defaults
#define DEFAULT_MANUAL_MEMORY_TIMER 60
#define DEFAULT_MANUAL_MEMORY 50

//autolock defaults
#define USE_AUTOLOCK
#define DEFAULT_AUTOLOCK_TIME 60

#undef RGB_LED_OFF_DEFAULT
#undef RGB_LED_LOCKOUT_DEFAULT
//setup aux properly
//0x00 = off    Low     High    Blinking
//R             0x10    0x20    0x30
//R+G           0x11    0x21    0x31
//G             0x12    0x22    0x32
//G+B           0x13    0x23    0x33
//B             0x14    0x24    0x34
//R+B           0x15    0x25    0x35
//R+G+B         0x16    0x26    0x36
//Disco         0x17    0x27    0x37
//Rainbow       0x18    0x28    0x38
//Voltage       0x19    0x29    0x39
#define RGB_LED_OFF_DEFAULT 0x27 //high, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T
#define USE_FIREWORK_MODE

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
#define USE_SIMPLE_UI_RAMPING_TOGGLE
#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

#define USE_3H_TURBO_FROM_LOCK

#undef LOCK_FROM_ON_EVENT
// need to fix voltage aux when channel mode is aux
#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 70
#define BLINK_LOCK_REMINDER
