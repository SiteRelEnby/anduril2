#pragma once

#include "cfg-emisar-d1v2-nofet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_MAIN_CHANNELS 1
#include "mod-config-siterelenby.h"
#define USER_CONFIG_L0ADED //prevent defaults from loading

#undef RAMP_SMOOTH_FLOOR
#undef RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_FLOOR
#undef RAMP_DISCRETE_CEIL
#undef RAMP_DISCRETE_STEPS

#define RAMP_SMOOTH_FLOOR 2  // low levels may be unreliable
#define RAMP_SMOOTH_CEIL  150
// 11, 30, [50], 70, 90, 110, 130  (plus [150] on turbo)
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 11

#undef SIMPLE_UI_FLOOR
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_FLOOR RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL 100
#define SIMPLE_UI_STEPS 3
#define USE_SIMPLE_UI_RAMPING_TOGGLE

#define CANDLE_AMPLITUDE 32

#define DEFAULT_MANUAL_MEMORY 50
#define DEFAULT_MANUAL_MEMORY_TIMER 60
#define DEFAULT_AUTOLOCK_TIME 60

#define B_TIMING_ON B_TIMEOUT_T

#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define TACTICAL_LEVELS 150,100,(RAMP_SIZE+2)

#define USE_3H_TURBO_FROM_LOCK
#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT

#define RGB_LED_OFF_DEFAULT 0x37  // blinking, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow
