// Noctigon KR4 (no DD FET) config options for Anduril
// Copyright (C) 2020-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// (and Noctigon KR1)
// (and Emisar D4v2 E21A, a.k.a. "D4v2.5")
#define HWDEF_C_FILE hwdef-noctigon-kr4-nofet.c
#include "cfg-noctigon-kr4-nofet.h"
// ATTINY: 1634
///////////////////////////////////////////////////////////

#define USE_AUX_WHILE_ON_CONFIG
#ifndef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW
  #define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_LOW 20
#endif
#ifndef USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH
  #define USE_AUX_WHILE_ON_CONFIG_DEFAULT_THRESHOLD_HIGH 50
#endif
 #ifndef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW
  #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
#endif
#ifndef USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH
  #define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 50
#endif

#define EVENT_AUX_WHILE_ON_TOGGLE EV_8clicks
