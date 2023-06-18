
/* LUME1-FF-6AF Driver with ATTINY1616
 *
 *  Configuration File for 2022 Lume1 Driver with 6A Buck + FET
 *  Used in FireflyLite E12R, E07X, PL09mu etc (2022)
 *
 *  Anduril 2 Firmware by Selene Scriven (R653)
 *  - Lume1-FF-6AF
 *  - 27 Dec 2022
 *  - Attiny1616
 * 
 *  For more information: 
 *  - www.loneoceans.com/labs/
 *  - Manual: http://toykeeper.net/torches/fsm/anduril2/anduril-manual.txt
 */

#define MODEL_NUMBER "0481"         // lume1-ff-6af 2022 with attiny1616
#include "hwdef-lume1-ff-6af.h"

//***************************************
//**       THERMAL SETTINGS            **
//***************************************

// set this light for 50C thermal ceiling
#undef DEFAULT_THERM_CEIL
#define DEFAULT_THERM_CEIL 55
//#define MAX_THERM_CEIL 70 // default maximum value

// drop from turbo at therm_ceil+TURBO_TEMP_EXTRA
#define TURBO_TEMP_EXTRA 7 // in celsius

// stop panicking at ~3A (not sure of this numbers yet since it depends on the host..)
#define THERM_FASTER_LEVEL 125			   	 // About 8.9W
#define MIN_THERM_STEPDOWN 88			          // About 2.2W
#define THERM_NEXT_WARNING_THRESHOLD 16		 // accumulate less error before adjusting (default 24)
#define THERM_RESPONSE_MAGNITUDE 64  	   	 // bigger adjustments (default 64)

// easier access to thermal config mode, similar to Emisar, Noctigon
#define USE_TENCLICK_THERMAL_CONFIG

// optional, makes initial turbo step-down faster so first peak isn't as hot
// FET mode can run very very hot, so be extra careful
//#define THERM_HARD_TURBO_DROP

//***************************************
//**      RAMPS AND OPERATIONS         **
//***************************************

// Uncomment to get Max Turbo on 2C from Off
//#define USE_2C_MAX_TURBO

// enable 2 click turbo
#define DEFAULT_2C_STYLE 1

// set this light to use stepped ramp by default (instead of smooth)
#undef RAMP_STYLE
#define RAMP_STYLE 1

// the entire ramp is regulated; don't blink halfway up
#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif

// We're abusing the Dynamic PWM functionality to set the VREF instead of PWM TOP (from GChart's work)
#ifdef USE_SET_LEVEL_GRADUALLY
#undef USE_SET_LEVEL_GRADUALLY
#endif

// NOTE: in ramp-mode-fsm.h, USE_SET_LEVEL_GRADUALLY is set anyway
// Disabling gradual ramping will require overhauling the ramp code
// Uncomment the following for most flashlights
//#define USE_SET_LEVEL_GRADUALLY_SUNSET

// Enable usage of multiple power paths
#define USE_MULTIPLE_POWER_PATH

// RAMP TABLE FOR BEHAVIOR USING LEVELS 1-149 as BUCK, 150 as FET
#define RAMP_LENGTH 150
//#define RAMP_LENGTH 149
#define USE_DYN_PWM

// NOTE --> RAMP TABLES MUST CORRESPOND TO THESE VALUES!
#define LED_PATH1_PIN_LEVEL_MIN 1
#define LED_PATH2_PIN_LEVEL_MIN 13
#define LED_PATH3_PIN_LEVEL_MIN 48
#define LED_FET_PIN_LEVEL_MIN 150

#define PWM_CHANNELS 2
#define PWM_BITS 8 

// =========== UDR x^4 curves ===========

// for 255 DAC UDR - with FET

// New ramp level with UDR is ~13.7million dynamic range (up from 3million)
#define PWM1_LEVELS 1, 2, 7, 17, 35, 65, 111, 39, 135, 198, 206, 170, 3, 4, 14, 18, 5, 28, 34, 41, 11, 22, 26, 83, 97, 113, 131, 151, 38, 197, 82, 253, 142, 160, 179, 88, 163, 181, 200, 221, 146, 160, 176, 192, 210, 229, 249, 13, 14, 15, 17, 18, 7, 21, 5, 24, 26, 28, 30, 7, 34, 36, 14, 15, 16, 46, 49, 19, 55, 58, 62, 65, 69, 16, 28, 80, 31, 89, 94, 36, 23, 24, 25, 26, 28, 29, 30, 32, 33, 35, 36, 38, 39, 41, 43, 45, 46, 48, 50, 52, 55, 57, 59, 61, 64, 66, 69, 71, 74, 76, 79, 82, 85, 88, 91, 94, 98, 101, 104, 108, 112, 115, 119, 123, 127, 131, 135, 139, 144, 148, 153, 158, 162, 167, 172, 177, 183, 188, 194, 199, 205, 211, 217, 223, 229, 235, 242, 248, 255, 0
// note - level 1 is basically invisible, level 2 is visible, level 3 is ultra low
// for 255 PWM FET
#define PWM2_LEVELS 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255
// NOTE: CMPn = BOTTOM will produce a static low signal on WOn while CMPn > TOP will produce a static high signal on

// for NO-FET UDR (149 levels)
//#define PWM1_LEVELS 1, 2, 7, 17, 35, 65, 111, 39, 135, 198, 206, 170, 3, 4, 14, 18, 5, 28, 34, 41, 11, 22, 26, 83, 97, 113, 131, 151, 38, 197, 82, 253, 142, 160, 179, 88, 163, 181, 200, 221, 146, 160, 176, 192, 210, 229, 249, 13, 14, 15, 17, 18, 7, 21, 5, 24, 26, 28, 30, 7, 34, 36, 14, 15, 16, 46, 49, 19, 55, 58, 62, 65, 69, 16, 28, 80, 31, 89, 94, 36, 23, 24, 25, 26, 28, 29, 30, 32, 33, 35, 36, 38, 39, 41, 43, 45, 46, 48, 50, 52, 55, 57, 59, 61, 64, 66, 69, 71, 74, 76, 79, 82, 85, 88, 91, 94, 98, 101, 104, 108, 112, 115, 119, 123, 127, 131, 135, 139, 144, 148, 153, 158, 162, 167, 172, 177, 183, 188, 194, 199, 205, 211, 217, 223, 229, 235, 242, 248, 255
// for NO-FET FET (149 levels)
//#define PWM2_LEVELS 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

#define PWM_TOPS 16, 16, 16, 16, 16, 16, 16, 18, 17, 17, 20, 18, 20, 20, 16, 16, 18, 16, 16, 16, 18, 20, 20, 16, 16, 16, 16, 16, 18, 16, 20, 16, 17, 17, 17, 18, 20, 20, 20, 20, 18, 18, 18, 18, 18, 18, 18, 16, 16, 16, 16, 16, 20, 16, 18, 16, 16, 16, 16, 18, 16, 16, 20, 20, 20, 16, 16, 20, 16, 16, 16, 16, 16, 18, 20, 16, 20, 16, 16, 20, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18    
#define PWM2_TOPS 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255

#ifdef USE_DYNAMIC_UNDERCLOCKING
#undef USE_DYNAMIC_UNDERCLOCKING
#endif

//#define MAX_1x7135 34
//#define HALFSPEED_LEVEL 14
//#define QUARTERSPEED_LEVEL 6

#define DEFAULT_LEVEL 61  // About ~0.5W
#define MAX_1x7135 88     // About ~2.2W

#define RAMP_SMOOTH_FLOOR 8
#define RAMP_SMOOTH_CEIL 149  // Level 150 is when Buck is off and FET is ON 100%

#define RAMP_DISCRETE_FLOOR 8
#define RAMP_DISCRETE_CEIL RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 5

#define SIMPLE_UI_FLOOR 13
#define SIMPLE_UI_CEIL 142  // 142 for 5A max
#define SIMPLE_UI_STEPS 5

// Turn on Buck from level 1 to 149, but not 150
// Level 150 is when Buck is off and FET is ON 100%
#define LED_ENABLE_PIN_LEVEL_MIN 1
#define LED_ENABLE_PIN_LEVEL_MAX 149

//***************************************
//**       AUX LEDs and MISC           **
//***************************************

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
#define AUXLED_RGB_DIFFERENT_PORTS 

// it has no independent LED in the button
//#define USE_BUTTON_LED

// off mode: low (1)
// lockout: blinking (3)
//#define INDICATOR_LED_DEFAULT_MODE ((3<<2) + 1)

// the button lights up
//#define USE_INDICATOR_LED

// the button is visible while main LEDs are on
//#define USE_INDICATOR_LED_WHILE_RAMPING

// the aux LEDs are front-facing, so turn them off while main LEDs are on
// TODO: the whole "indicator LED" thing needs to be refactored into
//       "aux LED(s)" and "button LED(s)" since they work a bit differently
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

#define RGB_LED_OFF_DEFAULT 0x18  // low, voltage
#define RGB_LED_LOCKOUT_DEFAULT 0x37  // blinking, rainbow

// enable blinking aux LEDs
#define TICK_DURING_STANDBY
#define STANDBY_TICK_SPEED 3  // every 0.128 s
//#define STANDBY_TICK_SPEED 4  // every 0.256 s
//#define STANDBY_TICK_SPEED 5  // every 0.512 s

#define USE_SOS_MODE
#define USE_SOS_MODE_IN_BLINKY_GROUP

#define USE_BEACONTOWER_MODE

// party strobe on-time
#define PARTY_STROBE_ONTIME 4

// attiny1616 has enough space to smooth out voltage readings
#define USE_VOLTAGE_LOWPASS

// can't reset the normal way because power is connected before the button
#define USE_SOFT_FACTORY_RESET   // can reset with 13H but why not include this as well..

// ======================================