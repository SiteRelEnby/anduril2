// Emisar 2-channel generic (plus FET) config options for Anduril (based on Noctigon K9.3)
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "cfg-emisar-2ch-fet.h"
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

