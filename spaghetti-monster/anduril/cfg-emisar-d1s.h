// Emisar D1S config options for Anduril
// Copyright (C) 2018-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// same as Emisar D4, mostly
#include "hwdef-emisar-d4.h"
#include "cfg-emisar-d4.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0122"

// safe limit ~50% power
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_CEIL 120

// stop panicking at ~90% power or ~1200 lm (D1S has a good power-to-thermal-mass ratio)
#ifdef THERM_FASTER_LEVEL
#undef THERM_FASTER_LEVEL
#endif
#define THERM_FASTER_LEVEL 144  // throttle back faster when high

// too big, turn off extra features
//#undef USE_TACTICAL_MODE
