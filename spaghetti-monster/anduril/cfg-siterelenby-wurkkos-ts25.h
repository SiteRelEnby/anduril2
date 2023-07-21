// Wurkkos TS25, modelled after the TS10 but with RGB Aux
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#define MODEL_NUMBER "0715"
#include "hwdef-wurkkos-ts25.h"
#include "wurkkos-cfg.h"
// ATTINY: 1616

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS

// don't turn on the aux LEDs while main LEDs are on
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V

#define RAMP_SIZE 150

#if 0  // 2022 version
// level 1 by hand, for the rest
// level_calc.py 7.01 2 149 7135 3 0.5 125 FET 1 10 1200 --pwm dyn:63:2048:255
#define PWM1_LEVELS 1,3,3,4,5,6,7,8,9,10,12,13,14,16,17,19,20,22,24,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,64,67,70,72,75,77,80,82,85,87,89,91,93,95,96,98,99,100,100,101,100,100,99,97,95,93,90,86,82,87,91,96,100,106,111,116,122,128,134,141,147,155,162,169,177,186,194,203,213,222,232,243,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,6,7,9,11,12,14,16,18,20,22,24,27,29,31,34,37,39,42,45,48,51,54,57,61,64,68,72,75,79,83,88,92,97,101,106,111,116,121,126,132,138,144,150,156,162,169,176,183,190,197,205,213,221,229,237,246,255
#define PWM_TOPS 2047,2047,1198,1322,1584,1676,1701,1691,1662,1622,1774,1703,1631,1692,1613,1639,1558,1564,1559,1478,1464,1444,1420,1392,1361,1329,1331,1293,1256,1246,1207,1192,1152,1133,1094,1074,1035,1013,991,954,932,897,875,842,820,790,760,731,704,678,646,622,593,566,534,510,478,452,423,393,364,338,310,280,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#define MAX_1x7135 90
#define HALFSPEED_LEVEL 2
#define QUARTERSPEED_LEVEL 2
#endif

// 7135 at 75/150
// level_calc.py 5.7895 2 150 7135 1 0.1 130 FET 1 10 3000 --pwm dyn:74:4096:255:3
// (with some manual tweaks)
#define PWM1_LEVELS  1,1,2,3,3,4,5,6,7,8,9,11,12,13,15,16,18,19,21,23,26,27,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,71,74,76,78,80,82,85,87,90,93,96,100,103,107,112,116,122,127,133,140,147,154,163,171,182,192,203,215,228,241,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
// non-zero part of FET channel calculated with:
//   level_calc.py 3 1 75 7135 1 200 3000
//   (FIXME? there's a visible bump when the FET kicks in, even with just 1/255)
#define PWM2_LEVELS  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,10,11,13,14,16,17,19,21,22,24,26,28,30,32,34,37,39,41,44,46,48,51,54,56,59,62,65,68,71,74,77,81,84,87,91,94,98,102,106,110,114,118,122,126,130,135,139,144,148,153,158,163,168,173,178,184,189,195,200,206,212,218,224,230,236,242,248,255
#define PWM_TOPS     4095,2701,3200,3586,2518,2778,2834,2795,2705,2587,2455,2582,2412,2247,2256,2091,2062,1907,1860,1802,1737,1605,1542,1477,1412,1347,1284,1222,1162,1105,1050,997,946,898,853,810,768,730,693,658,625,594,564,536,503,485,462,439,418,398,384,366,353,340,327,319,307,298,292,284,280,273,269,266,263,260,258,256,256,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

#define MAX_1x7135 75
#define DEFAULT_LEVEL 50
#define MIN_THERM_STEPDOWN 60
#define HALFSPEED_LEVEL 20
#define QUARTERSPEED_LEVEL 5

#define RAMP_SMOOTH_FLOOR    1
#define RAMP_SMOOTH_CEIL     150
// 20 38 56 [75] 93 111 130
#define RAMP_DISCRETE_FLOOR  10
#define RAMP_DISCRETE_CEIL   150
#define RAMP_DISCRETE_STEPS  11

// at Wurkkos's request, reduce the Simple UI ceiling a little bit
// 25 50 [75] 100 125
#define SIMPLE_UI_FLOOR  25
#define SIMPLE_UI_CEIL   125
#define SIMPLE_UI_STEPS  5

// stop panicking at ~50% power
#define THERM_FASTER_LEVEL 120  // throttle back faster when high

// show each channel while it scroll by in the menu
#define USE_CONFIG_COLORS

// blink numbers on the main LEDs by default
// (so battcheck will be visible while charging)
#define DEFAULT_BLINK_CHANNEL  CM_AUXCYN
// blink numbers on the aux LEDs by default
//#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT

// use aux red + aux blue for police strobe
#define USE_POLICE_COLOR_STROBE_MODE
#define POLICE_STROBE_USES_AUX
#define POLICE_COLOR_STROBE_CH1        CM_AUXRED
#define POLICE_COLOR_STROBE_CH2        CM_AUXBLU

// don't blink mid-ramp
//#ifdef BLINK_AT_RAMP_MIDDLE
//#undef BLINK_AT_RAMP_MIDDLE
//#endif

///////////////////////////////////////////////////////

#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 150,75,(RAMP_SIZE+2)

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
#define RGB_LED_OFF_DEFAULT 0x28 //high, rainbow
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow
#define USE_AUX_RGB_LEDS_WHILE_ON
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_LOW 20
#define USE_AUX_RGB_LEDS_WHILE_ON_THRESHOLD_HIGH 70
#define BLINK_LOCK_REMINDER
#undef LOCK_FROM_ON_EVENT

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_TIMEOUT_T
#define B_TIMING_OFF B_TIMEOUT_T

#define DEFAULT_AUTOLOCK_TIME 60

#define NUM_MAIN_CHANNELS 1 //TODO: is this still needed with the refactor?
#include "button-mapping-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading
