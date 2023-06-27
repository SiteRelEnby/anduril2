// Sofirn SP36 (small Q8) config options for Anduril using the Attiny1616 (also used for Q8 Plus)
// same as  the  BLF Q8, mostly
#include "cfg-blf-q8-t1616.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0614"
// ATTINY: 1616

// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V

// the high button LED mode on this light uses too much power
// off mode: low (1)
// lockout: blinking (3)
#ifdef INDICATOR_LED_DEFAULT_MODE
#undef INDICATOR_LED_DEFAULT_MODE
//#ifdef ANDURIL_SITERELENBY_MOD
//#define INDICATOR_LED_DEFAULT_MODE ((3<<4) + 1) //more modes; shift 4 bits left instead of 2
//#else
//#define INDICATOR_LED_DEFAULT_MODE ((3<<2) + 1)
//#endif
#endif

//I just don't like blinking mode...
#define INDICATOR_LED_DEFAULT_MODE ((1<<4) + 2) //high unlocked (IDGAF, I use autolock), low locked (TODO: much slower blink after locked for a certain time?)

#define BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_CEIL

// stop panicking at ~60% power or ~3000 lm
#ifdef THERM_FASTER_LEVEL
#undef THERM_FASTER_LEVEL
#endif
#define THERM_FASTER_LEVEL 130


#undef DEFAULT_LEVEL
#define DEFAULT_LEVEL 70

#undef RAMP_SMOOTH_FLOOR
#define RAMP_SMOOTH_FLOOR 1
#undef RAMP_SMOOTH_CEIL
#define RAMP_SMOOTH_CEIL 150
#undef RAMP_DISCRETE_FLOOR
#define RAMP_DISCRETE_FLOOR 1
#undef RAMP_DISCRETE_CEIL
#define RAMP_DISCRETE_CEIL RAMP_SMOOTH_CEIL
#undef RAMP_DISCRETE_STEPS
#define RAMP_DISCRETE_STEPS 11

#undef SIMPLE_UI_FLOOR
#define SIMPLE_UI_FLOOR 10
#undef SIMPLE_UI_CEIL
#define SIMPLE_UI_CEIL 100
#undef SIMPLE_UI_STEPS
#define SIMPLE_UI_STEPS 5
#define USE_SIMPLE_UI_RAMPING_TOGGLE
#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

//disable simple UI by default
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

#define DEFAULT_MANUAL_MEMORY_TIMER 60
#define DEFAULT_MANUAL_MEMORY 50
#define USE_AUTOLOCK
#define DEFAULT_AUTOLOCK_TIME 60
#define BLINK_AT_RAMP_MIDDLE
#define USE_FIREWORK_MODE
#define USE_3H_TURBO_FROM_LOCK
#define MOMENTARY_WHEN_LOCKED_DELAY 1
#define USE_BEACON_ON_CONFIG
#define USE_BEACON_BRIGHTNESS_RAMP
//use 3 instead of 0 to disable manual memory from 10H while on, option 2
#undef DISABLE_MANUAL_MEMORY_ENTRY_VALUE
#define DISABLE_MANUAL_MEMORY_ENTRY_VALUE 3


#define MOMENTARY_CLICK_EVENT EV_12clicks
#define SUNSET_TIMER_HOLD_EVENT EV_click12_hold
#define RAMP_STYLE_TOGGLE_EVENT EV_9clicks

#define RAMP_CONFIG_HOLD_EVENT EV_click7_hold
#define MANUAL_MEMORY_SAVE_CLICK_EVENT EV_10clicks

#define AUX_CONFIG_CLICK_EVENT EV_7clicks
#define AUX_CONFIG_HOLD_EVENT EV_click7_hold
#define AUX_CONFIG_HOLD_RELEASE_EVENT EV_click7_hold

#define MOMENTARY_CLICK_EVENT_OFF MOMENTARY_CLICK_EVENT
#define MOMENTARY_CLICK_EVENT_STROBE MOMENTARY_CLICK_EVENT
#define TACTICAL_MODE_CLICK_EVENT EV_9clicks
#define TACTICAL_LEVELS 150,45,(RAMP_SIZE+2)

