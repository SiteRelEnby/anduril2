// Emisar 2-channel generic config options for Anduril
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#define MODEL_NUMBER "0135"

#include "cfg-emisar-2ch.h"
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

