// Noctigon KR4 config options for Anduril
// (and Emisar D4v2.5, which uses KR4 driver plus a button LED)
// Copyright (C) 2020-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-noctigon-kr4.h"
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
