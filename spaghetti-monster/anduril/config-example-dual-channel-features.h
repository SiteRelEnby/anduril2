// This is an *EXAMPLE* configuration file for a build. To use this, you would find the right file for your light's hardware via version check, and add this configuration modified as appropriate to how you want your light to work to the end.

// overheat protection
#define DEFAULT_THERM_CEIL 45  // try not to get hotter than this (in C)
// Comment out to disable automatic calibration on factory reset
//   - If so, be sure to set THERM_CAL_OFFSET to the correct calibration offset
//   - Calibration can still be overridden in temperature check mode
// Or uncomment to use the default auto-calibrate on factory reset
//
// To determine THERM_CAL_OFFSET, comment out USE_THERM_AUTOCALIBRATE to
// disable auto-calibration, compile and flash, let flashlight rest at a known
// temperature, then enter temp check mode (do NOT enter calibration mode).
//
// THERM_CAL_OFFSET = known_temperature - temp_check_blinks + THERM_CAL_OFFSET
//
// (include THERM_CAL_OFFSET in sum as it might already be a non-zero number)
#define USE_THERM_AUTOCALIBRATE

// Include a simplified UI for non-enthusiasts?
#define USE_SIMPLE_UI

//but don't default to it:
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

///// Ramp mode options /////

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_RELEASE_T
#define B_TIMING_OFF B_TIMEOUT_T

// default ramp style: 0 = smooth, 1 = stepped
#define RAMP_STYLE 0

// smooth ramp speed: 1, 2, 3, 4, ...  for 1X speed, 1/2, 1/3rd, 1/4th, ...
#define USE_RAMP_SPEED_CONFIG

// after ramping, how long until the direction resets to "up"?
#define AUTO_REVERSE_TIME (TICKS_PER_SECOND * 2 / 3)

// add runtime option for whether hold-from-off should ramp or stay at moon
#define USE_RAMP_AFTER_MOON_CONFIG

// short blip when crossing from "click" to "hold" from off
// (helps the user hit moon mode exactly, instead of holding too long
//  or too short)
#define MOON_TIMING_HINT  // only applies if B_TIMING_ON == B_PRESS_T
// short blips while ramping
#define BLINK_AT_RAMP_MIDDLE
//#define BLINK_AT_RAMP_FLOOR
#define BLINK_AT_RAMP_CEIL
//#define BLINK_AT_STEPS  // whenever a discrete ramp mode is passed in smooth mode

// Uncomment for Anduril1 "Ramp 2C" behavior:
//   - Ramp 2C goes to turbo (advanced UI) or ceiling (simple UI), like in Anduril1
// Or comment out to use Anduril2 behavior instead:
//   - Ramp 2C goes to ceiling, unless already at ceiling or in simple UI.
//     (Advanced UI ceiling 2C goes to turbo)
//#define USE_2C_MAX_TURBO
// Or uncomment to let the user decide which style they want:
#define USE_2C_STYLE_CONFIG
// 0 = no turbo
// 1 = A1 style: Off 2C = ceil, On 2C = turbo
// 2 = A2 style: Off 2C = ceil, On 2C = ceil, Ramped ceil 2C = turbo
// All styles allow momentary turbo in advanced UI
#define DEFAULT_2C_STYLE 2  // default to Anduril 2 style
#define DEFAULT_2C_STYLE_SIMPLE 0  // no turbo at all

// make the ramps configurable by the user
#define USE_RAMP_CONFIG

// adds a runtime option to switch between automatic memory (default)
// and manual memory (only available if compiled in)
// (manual memory makes 1-click-from-off start at the same level each time)
// (the level can be set explicitly with 10 clicks from on,
// or the user can go back to automatic with 10H)
#define USE_MANUAL_MEMORY
// if enabled, user can use "hybrid memory"
// The light will use automatic or manual memory level, depending on how long
// the light was off.  Short off = automatic, long off = manual.
// This also remaps 10C/10H:
// - 10C toggles manual mem on/off at current level.
// - 10H configures the timer value.
#define USE_MANUAL_MEMORY_TIMER

// enable sunset timer (ramp-down and automatic shutoff)
// timer is available in regular ramp mode and candle mode
#define USE_SUNSET_TIMER


///// What to do when power is connected /////
// factory reset function erases user's runtime configuration in eeprom
#define USE_FACTORY_RESET
//#define USE_SOFT_FACTORY_RESET  // only needed on models which can't use hold-button-at-boot

// dual-switch support (second switch is a tail clicky)
// (currently incompatible with factory reset)
//#define START_AT_MEMORIZED_LEVEL


///// extra modes (enable / disable / configure each mode) /////

// enable beacon mode
#define USE_BEACON_MODE

// enable/disable various strobe modes
#define USE_BIKE_FLASHER_MODE
#define USE_PARTY_STROBE_MODE
#define USE_TACTICAL_STROBE_MODE
#define USE_LIGHTNING_MODE
#define USE_CANDLE_MODE

// boring strobes nobody really likes, but sometimes flashlight companies want
// (these replace the fun strobe group,
//  so don't enable them at the same time as any of the above strobes)
//#define USE_POLICE_STROBE_MODE
#define USE_SOS_MODE

// enable a mode for locking the light for safe carry
#define USE_LOCKOUT_MODE
// should lockout mode function as a momentary moon mode?
#define USE_MOON_DURING_LOCKOUT_MODE
// add an optional setting to lock the light after being off for a while
#define USE_AUTOLOCK

// enable momentary mode
#define USE_MOMENTARY_MODE

// enable tactical mode
#define USE_TACTICAL_MODE

//configure user settings
#define SIMPLE_UI_FLOOR 10    // simple UI floor
#define SIMPLE_UI_CEIL  100   // simple UI ceiling
#define SIMPLE_UI_STEPS 5     // simple UI stepped ramp length
#define USE_SIMPLE_UI_RAMPING_TOGGLE //enable ramp style switch in Simple UI

#define RAMP_SMOOTH_FLOOR   1   // smooth ramp floor
#define RAMP_SMOOTH_CEIL    130 // smooth ramp ceiling
#define RAMP_DISCRETE_FLOOR 1   // smooth ramp floor
#define RAMP_DISCRETE_CEIL   130 // stepped ramp ceiling
#define RAMP_DISCRETE_STEPS 10  // stepped ramp length

// enable voltage readout via aux/switch when on (see also RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF and RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW for modded versions)
//#define USE_AUX_RGB_LEDS_WHILE_ON
//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30 // Sets the threshold at which to switch the voltage RGB aux off
//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50 //Sets the threshold at which to switch the voltage RGB aux to low mode
// disable voltage readout via aux when on
//#undef USE_AUX_RGB_LEDS_WHILE_ON

//#define DEFAULT_MANUAL_MEMORY 50       //ramp level (1-150)
//#define DEFAULT_MANUAL_MEMORY_TIMER 60 //minutes

//#define DEFAULT_AUTOLOCK_TIME 60       //minutes

// enable a shortcut for +10 in number entry mode
// (click for +1, hold for +10)
#define USE_NUMBER_ENTRY_PLUS10

// cut clock speed at very low modes for better efficiency
// (defined here so config files can override it)
#define USE_DYNAMIC_UNDERCLOCKING

// if the aux LEDs oscillate between "full battery" and "empty battery"
// while in "voltage" mode, enable this to reduce the amplitude of
// those oscillations
//#define USE_LOWPASS_WHILE_ASLEEP

#endif

#define USE_LOW_VOLTAGE_WARNING    //enable feature
#define VOLTAGE_WARN_DELAY_TICKS 40    //(makes sense if it's 50% in awake and 50% in asleep state). 40 = ~5s
#define VOLTAGE_WARN_HIGH_RAMP_LEVEL 75 //level above which we expect some voltage drop that could make battery appear low for a while when switched off
//(TODO: unimplemmented so far)#define VOLTAGE_WARN_INSTANT 28 //always warn instantly if voltage drops below this level (even with voltage drop)

#define TACTICAL_LEVELS RAMP_SIZE,(RAMP_SIZE+2),100

//new features to default to enabled because they don't do unexpected things that could be bad
#define USE_FIREWORK_MODE
#define USE_BEACON_ON_CONFIG
#define USE_BEACON_BRIGHTNESS_RAMP
//#define BLINK_ONCE_AUX_TIME_4MS 10 //40ms
#define BLINK_ONCE_AUX_TIME_4MS 15 //60ms
#define BLINK_LOCK_REMINDER

#define BLINK_NUMBERS_WITH_AUX //enables entire feature
#define BLINK_NUMBERS_WITH_AUX_DEFAULT_SETTING 2 //1: aux low, 2: aux high, 3+ main emitter ramp level
#define BLINK_NUMBERS_WITH_AUX_COLOUR 0x14 //cyan
/*
    0b00000001,  // 0: red: high 0x01
    0b00000101,  // 1: yellow: 0x05
    0b00000100,  // 2: green: 0x04
    0b00010100,  // 3: cyan: 0x14
    0b00010000,  // 4: blue: 0x10
    0b00010001,  // 5: purple: 0x11
    0b00010101,  // 6: white: 0x15
*/

#define RGB_LED_OFF_DEFAULT 0x27 //high, disco
#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow
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

//new features to keep matching default behaviour by default
#define DISABLE_MANUAL_MEMORY_ENTRY_VALUE 0

//things that will make it more like upstream if uncommented but that are annoying, so leaving them here commented for the user to decide
//#define USE_MAIN_LEDS_FOR_ALL_BLINKS

//similarly, things a user may reasonably want to disable for all their lights
//#define DISABLE_MOMENTARY_TURBO_FROM_LOCK
//#define DISABLE_UNLOCK_TO_TURBO

//custom mappings - 200% turbo, individual turbo modes:
//mappings from ON:
#define SUNSET_TIMER_HOLD_EVENT EV_click10_hold //moving stuff out of the way: Sunset mode to 10H
#define RAMP_STYLE_TOGGLE_EVENT EV_9clicks                                 // Ramp toggle to 9C
#define RAMP_CONFIG_HOLD_EVENT EV_click8_hold                              // ramp config to 8H
#define MANUAL_MEMORY_SAVE_CLICK_EVENT EV_10clicks             //default
#undef LOCK_FROM_ON_EVENT                                                  // Disable lock from ramp
#define MOMENTARY_CLICK_EVENT EV_11clicks                                  // Momentary mode to 11C

//mappings from OFF:
#define MOMENTARY_CLICK_EVENT_OFF MOMENTARY_CLICK_EVENT                    // Momentary mode to 11C

//mappings from strobes:
#define MOMENTARY_CLICK_EVENT_STROBE MOMENTARY_CLICK_EVENT                 // Momentary mode to 11C

//mappings from off/lock:
#define AUX_CONFIG_CLICK_EVENT EV_8clicks                                  // Aux config to 8C/H to make it harder to accidentally hit
#define AUX_CONFIG_HOLD_EVENT EV_click8_hold
#define AUX_CONFIG_HOLD_RELEASE_EVENT EV_click8_hold
#define TACTICAL_MODE_CLICK_EVENT EV_9clicks                               // Tactical mode to 9C

#undef CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT                              // Disable configurable channel switch as we are enabling both at once
#undef CHANNEL_SWITCH_CONFIGURABLE_HOLD_RELEASE_EVENT

#define CHANNEL_SWITCH_ONLY_CLICK_EVENT EV_3clicks                         // 3C: Switch channels
#define CHANNEL_RAMP_ONLY_HOLD_EVENT EV_click3_hold                        // 3H: Ramp channels
#define CHANNEL_RAMP_ONLY_RELEASE_EVENT EV_click3_hold_release

#define DUALCHANNEL_2C_ALWAYS_USE_SINGLE_CHANNEL                           // (2C as always single channel turbo)
#define TURBO_200_CLICK_EVENT EV_4clicks                                   // 4C: 200% turbo
#define TURBO_200_MOMENTARY_HOLD_EVENT EV_click4_hold                      // 4H: momentary 200%
#define TURBO_200_MOMENTARY_RELEASE_EVENT EV_click4_hold_release

#define CHANNEL_1_TURBO_CLICK_EVENT EV_5clicks                             // 5C: Turbo 1
#define CHANNEL_1_TURBO_HOLD_EVENT EV_click5_hold                          // 5H: Momentary Turbo 1
#define CHANNEL_1_TURBO_HOLD_RELEASE_EVENT EV_click5_hold_release

#define CHANNEL_2_TURBO_CLICK_EVENT EV_6clicks                             // 6C: Turbo 2
#define CHANNEL_2_TURBO_HOLD_EVENT EV_click6_hold                          // 6H: Momentary turbo 2
#define CHANNEL_2_TURBO_HOLD_RELEASE_EVENT EV_click6_hold_release

//disable simple UI by default
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0

