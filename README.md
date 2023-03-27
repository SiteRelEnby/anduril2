# anduril2

Anduril2 originally by [ToyKeeper](https://code.launchpad.net/~toykeeper/flashlight-firmware/anduril2), mods by @SiteRelEnby.

# Other stuff
## Git repo scripts

* `make-git-repo.sh`: script to create a clean version of the upstream anduril2 repo (for merging purposes or your own hacking). Dependencies are git, bzr, and normal shell utilities
* `update-upstream-branch.sh`: script to create a branch with a clean version of the upstream code. Mostly for my own use in building and modding but included in case they prove useful to someone else. Takes environment vars (TODO: args as well):
  * `NO_PUSH`: set to `1` will not push the created branch.
  * `UPSTREAM_BRANCH`: name of the branch to create for upstream code. Defaults to `upstream` if unset.
  * `REMOTE`: name of the remote to push to; if not specified, defaults to `origin`.

# Build utilities

## anduril-buildenv-docker

A fork of [anduril-buildenv-docker](https://github.com/SiteRelEnby/anduril-buildenv-docker)

Included as a submodule, to use it, run `git submodule update --init`. Note that to build the builder you will need a working [buildkit](https://docs.docker.com/build/buildkit) as well as base Docker.

Also on Docker Hub: https://hub.docker.com/r/siterelenby/anduril-builder

`docker pull siterelenby/anduril-builder:latest`

Note that my automated docker builds of my own projects and tools are multiarch but I have only personally tested on amd64, I can't think of any specific reason it wouldn't work on ARM though.

### Changes
* Fix bug (full path creation causes issues on some of my boxen when trying to mount a filesystem with subdirs, and is in general useless)
* Added a proper entrypoint script
  * Checks for the source directory being mounted at different paths under `/src`
  * Return non-zero on build failure (useful for CI/CD pipelines etc.)

## Scripts

Example build scripts and header files for my lights (`build-siterelenby-*` and `spaghetti-monster/anduril/cfg-siterelenby*.h`) including a few extra default settings vs the default model header files.

Build scripts and image should work fine with the default codebase as well (in the future these may move to a submodule)

# Current upstream version this mod is based on

10/02/2023

# Changes from upstream

The goal for this fork is to be reasonably modular - if you don't want/need a feature, it can be enabled or disabled. Ideally, it should be usable for someone familiar with anduril, e.g. by default 7H, 9H, and 10H config menus stay in the same place. Most ofthe extra options and configuration is done at build-time using feature flags (there just isn't enough space to make everything configurable). In general, avoiding removing functionality completely, just giving the user the option if they want it.

## Custom mode mappings

The main feature of this fork. Many functions can be remapped by changing a define in your light's header file. For default anduril mappings:
```
//mappings from ON:
#define SUNSET_TIMER_HOLD_EVENT EV_click5_hold
#define RAMP_STYLE_TOGGLE_EVENT EV_3clicks
#define RAMP_CONFIG_HOLD_EVENT EV_click7_hold
#define MANUAL_MEMORY_SAVE_CLICK_EVENT EV_10clicks
#define MOMENTARY_CLICK_EVENT EV_5clicks
#define LOCK_FROM_ON_EVENT EV_4clicks

// mappings from OFF:
#define MOMENTARY_CLICK_EVENT_OFF MOMENTARY_CLICK_EVENT //can set a separate shortcut from off mode

// mappings from strobe mode:
#define MOMENTARY_CLICK_EVENT_STROBE MOMENTARY_CLICK_EVENT //can set a separate shortcut from strobe mode

// mappings from off/lock state:
#define AUX_CONFIG_CLICK_EVENT EV_8clicks
#define AUX_CONFIG_HOLD_EVENT EV_click8_hold
#define AUX_CONFIG_HOLD_RELEASE_EVENT EV_click8_hold

// mappings from any state other than momentary:
#define CHANNEL_SWITCH_CONFIGURABLE_HOLD_EVENT EV_click3_hold //default channel switch configurable in 9H config
#define CHANNEL_SWITCH_CONFIGURABLE_HOLD_RELEASE_EVENT EV_click3_hold_release //default channel switch configurable in 9H config

```

Some stock features can be disabled completely by unsetting their event as well:
```
#undef LOCK_FROM_ON_EVENT
```

Mappings for new features (see below for an explanation of these features):
```
// mappings from ON:
#define TURBO_200_CLICK_EVENT EV_4clicks
#define TURBO_200_MOMENTARY_HOLD_EVENT EV_click7_hold
#define TURBO_200_MOMENTARY_RELEASE_EVENT EV_click7_hold_release

//#define LOCK_FROM_ON_EVENT EV_4clicks
#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT_RELEASE EV_click4_hold_release
#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT EV_click4_hold

#define CHANNEL_SWITCH_ONLY_CLICK_EVENT EV_3clicks //always switches instantly between channels

#define CHANNEL_CYCLE_HOLD_EVENT EV_click7_hold //switches instantly between channels, and continues to cycle channels if held longer. This is somewhat a placeholder for future support for more than 2 channels.

#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT_RELEASE EV_click4_hold_release
#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT EV_click4_hold

```

Some example files to look at as examples for your own build:
* `spaghetti-monster/anduril/cfg-siterelenby-emisar-d4sv2-tintramp-fet.h`
* `spaghetti-monster/anduril/cfg-siterelenby-noctigon-dm112-tintramp-fet.h`

Note that the build does not (currently?) check for conflicts, which may cause weird things to happen, or may just cause the function to not work.

## All lights

* Remappable shortcuts. A work in progress, see above for details.
  * Remappable default functionality:
    * Momentary mode (default 5C)
    * Sunset timer (default 5H)
    * Lock from on (default 4H - can also be entirely disabled)
    * Tint/channel ramping (default 3H)
    * Ramp config menu (default 7H)
    * Stepped/smooth ramp toggle (default 3C)
    * Aux colour/mode (default 7C/H)
  * New features:
    * Dual channel turbo shortcuts
    * 200% turbo shortcut
* 2H in beacon mode to set the time the light is on (1 blink = 100ms) (`USE_BEACON_ON_CONFIG`). Each blink while held is 100ms of time on.
* Added 3/4H in beacon mode to increase/decrease brightness without exiting. This is not strictly a *new* feature as beacon mode normally uses the last ramped level, it just allows on the fly adjustment. Enabled with `USE_BEACON_BRIGHTNESS_RAMP`.
  * Note that there is no thermal regulation in this mode so don't overheat your light - test it before leaving it unattended.
* Incorporated some changes from [starryalley](https://github.com/starryalley/Anduril2):
  * Candle and strobe code is now a direct port:
    * Strobe modes reordered (candle, lightning, fireworks, party strobe, tactical strobe, dual channel modes) to avoid accidentally blinding the user.
    * 2C to cycle to next strobe, 3C to cycle to previous.
    * 4C to decrease candle/lighting mode activity, 5C to increase, 6C to reset
    * 4H in candle mode to change candle style (3 options)
    * 7C in candle mode to toggle aux LEDs
    * Additional strobe mode: Fireworks mode (`USE_FIREWORK_MODE`), after lightning mode
    * On tint ramping lights, two additional strobe modes to switch and ramp between channels (after tactical strobe mode)
  * Blink aux/button red in off/lockout modes when battery is <= 3.2V
      * Increased the speed and time in an on state of the breathing animation (aux will still switch off entirely below 3V)
  * If aux LEDs are present, use those for lock/unlock/poweron blinks instead of main LEDs (can be disabled by building with `USE_MAIN_LEDS_FOR_ALL_BLINKS`, e.g. on lights where feedback from the aux is hard to see)
  * Temperature aux LED mode (after voltage in the cycle)
* Added options to only use momentary mode from lock after enough time has passed to make sure it was only 1H (`WAIT_FOR_MOMENTARY_WHEN_LOCKED` / `MOMENTARY_WHEN_LOCKED_DELAY`)
* Made the default aux blinking mode blink more often and intensely
* Build-time configuration for some additional stuff (in its own section)
  * Using aux LEDs to display the battery voltage while the light is on.
    * This is by default only enabled for lights with an RGB button but no RGB aux (e.g. K1), but can be enabled for any light by setting `USE_AUX_RGB_LEDS_WHILE_ON` in the relevant header file.
    * For lights with forward facing aux, added `RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF` and `RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW` to customise when the voltage is displayed, so if this causes a problem it can be disabled at low ramp levels. These also come in useful as a way to mark a specific level in the ramp with a visual cue (e.g. having the LED go to high at your thermally sustainable level).
* Use a less bzr/bizarre VCS
* Remove reference to bad childrens' fantasy novels by a terrible person. Please [read another book](https://knowyourmeme.com/memes/read-another-book).

## Dual channel lights only
* `DUALCHANNEL_2C_ALWAYS_USE_SINGLE_CHANNEL`: When set, 2C now always goes to level 130 (single channel on maximum) instead of using 7H configured mode
* Shortcuts to channels 1 and 2 turbo modes, including momentary. This needs configuration in a light-specific header file:
```
#define CHANNEL_1_TURBO_CLICK_EVENT EV_5clicks
#define CHANNEL_1_TURBO_HOLD_EVENT EV_click5_hold
#define CHANNEL_1_TURBO_HOLD_RELEASE_EVENT EV_click5_hold_release

#define CHANNEL_2_TURBO_CLICK_EVENT EV_6clicks
#define CHANNEL_2_TURBO_HOLD_EVENT EV_click6_hold
#define CHANNEL_2_TURBO_HOLD_RELEASE_EVENT EV_click6_hold_release
```
* Momentary opposite channel mode (e.g. `#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT_RELEASE EV_click4_hold_release` `#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT EV_click4_hold`
  * At the moment this will invert the ramp, e.g. if you are at a 25/75% mix between the two channels it will flip to 75/25. I may make this behaviour configurable in the future with other options.
* Mappable shortcuts for instant channel switching only and for ramping only, ignoring 7H config (`CHANNEL_RAMP_ONLY_HOLD_EVENT`, `CHANNEL_RAMP_ONLY_RELEASE_EVENT`, `CHANNEL_SWITCH_ONLY_CLICK_EVENT`)
* `DEFAULT_TINT` build-time option
* Option to make the light start in instant switching mode by default via header file (currently kind of a kludge as it just inverts the two states, so the 9H options are swapped round from normal too when enabled - although fixing that is low priority as it's not something that many people probably want to change much) (`USE_OPPOSITE_TINTRAMP_KLUDGE`)
* Shortcuts to turbo modes for each channel (`CHANNEL_1_TURBO_CLICK_EVENT`, `CHANNEL_2_TURBO_CLICK_EVENT`)
* Momentary turbo modes for each channel (`CHANNEL_1_TURBO_HOLD_EVENT`, `CHANNEL_1_TURBO_HOLD_RELEASE_EVENT`,  `CHANNEL_2_TURBO_HOLD_EVENT`, `CHANNEL_2_TURBO_HOLD_RELEASE_EVENT`)

## Single channel lights only
* 3H from lock for turbo (can be disabled with `DISABLE_MOMENTARY_TURBO_FROM_LOCK`). This does not work for dual channel lights by default because channel swiching on 3H will override it. TODO: 5H? Something like `LOCKOUT_3H_ACTION`? (should probably force 200% in case the user is on the wrong channel?)

# Lights tested with
These are lights that I own. Currently all of them are running this fork. Not every single commit or release will be tested on every single light.

* D4Sv2 (dual channel, FET)
* DM1.12 (FET on flood channel. based on D4Sv2 header file)
* K1
* KR1
* DT8K (based on KR4 header file)
* D4 (boost driver; no FET)

# Build-time configuration


## Building a custom image

Get your light's default firmware and locate the correct header file, as this contains important hardware-specific config. Make a copy of it, and modify the following variables to your preference. These settings will persist across a factory reset (making it much more convenient to build an image once, then if your settings ever get messed up, you can factory reset to go back to *your* settings. Most of these are fairly self-explanatory. Note that the first half *SHOULD* work in stock unmodified anduril too, but this has not been tested by me personally. See above for build-time settings added by mods.

```
//#define SIMPLE_UI_ACTIVE 0    // disable simple UI by default/from factory reset

//#define SIMPLE_UI_FLOOR 10    // simple UI floor
//#define SIMPLE_UI_CEIL  100   // simple UI ceiling
//#define SIMPLE_UI_STEPS 5     // simple UI stepped ramp length
//#define USE_SIMPLE_UI_RAMPING_TOGGLE //enable ramp style switch in Simple UI

//#define RAMP_SMOOTH_FLOOR   1   // smooth ramp floor
//#define RAMP_SMOOTH_CEIL    130 // smooth ramp ceiling
//#define RAMP_DISCRETE_FLOOR 1   // smooth ramp floor
//define RAMP_DISCRETE_CEIL   130 // stepped ramp ceiling
//#define RAMP_DISCRETE_STEPS 10  // stepped ramp length

//enable voltage readout via aux/switch when on (see also RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF and RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW for modded versions)
//#define USE_AUX_RGB_LEDS_WHILE_ON
//disable voltage readout via aux when on
//#undef USE_AUX_RGB_LEDS_WHILE_ON

//#define RAMP_STYLE 0 //0 is smooth, 1 is stepped

//#define DEFAULT_MANUAL_MEMORY 50       //ramp level (1-150)
//#define DEFAULT_MANUAL_MEMORY_TIMER 60 //minutes

//#define DEFAULT_AUTOLOCK_TIME 60       //minutes

//#define DEFAULT_THERM_CEIL 50          //degrees

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
//#define B_TIMING_OFF B_TIMEOUT_T //only turn the light off when sure that's what the user wanted, causes 'delayed' off (default)
//#define B_TIMING_ON B_RELEASE_T //more immediate on, but causes a blink when selecting a higher button combo from off mode (default)
//#define B_TIMING_ON B_TIMEOUT_T //wait before coming on - prevents a blink when doing other actions (config, lock, etc.) but adds a delay to 1C -> on
// NOTE: on from lockout is more complicated since there is no way to directly configure it. TODO: should be simple enough to add a delay that's longer than RELEASE_TIMEOUT before momentary from lock...

//#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
//#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.
```

Settings related to my mods, will be ignored in stock anduril:
```
#define USE_AUX_RGB_LEDS_WHILE_ON //show voltage using RGB aux even if this isn't just a button LED
#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30 // Sets the threshold at which to switch the voltage RGB aux off
#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50 //Sets the threshold at which to switch the voltage RGB aux to low mode
#define USE_OPPOSITE_TINTRAMP_KLUDGE: When defined, makes the light start in channel switching mode. A very inelegant solution but it works so not being redone for now. May be replaced with a better way in the future.

// Delay momentary from lock until input is confirmed to definitely be 1H - prevents main LEDs flashing when doing more clicks from lock.
// This setting guarantees a flash will be avoided when unlocking, but might be too slow for many people (including me) - see MOMENTARY_WHEN_LOCKED_DELAY for an alternative.
//#define WAIT_FOR_MOMENTARY_WHEN_LOCKED

#define MOMENTARY_WHEN_LOCKED_DELAY 2 //number of ticks to wait (default for HOLD_TIMEOUT is 24) before activating momentary mode when locked - prevents a flash when inputting a higher number of clicks, without waiting for the full HOLD_TIMEOUT delay with WAIT_FOR_MOMENTARY_WHEN_LOCKED. 1-2 is fine at least for lights with higher Vf, but depends on the user's preference. >4 is probably excessive.

// default channel mix for when the light first starts up or is reset. Can be set to any value 1-254.
#define DEFAULT_TINT 1
//#define DEFAULT_TINT 128
//#define DEFAULT_TINT 254

//#define USE_OPPOSITE_TINTRAMP_KLUDGE //start in channel switching mode rather than ramping

//#define USE_FIREWORK_MODE //enable fireworks mode

//#undef DISABLE_4C_LOCK_FROM_RAMP //undefining this flag allows the feature to be entirely disabled

//#define DISABLE_UNLOCK_TO_TURBO //disables 5C/6C from lock shortcuts to unlock to turbo

//#define DISABLE_MOMENTARY_TURBO_FROM_LOCK

//#define USE_MAIN_LEDS_FOR_ALL_BLINKS //disable using aux/button LED for lock/unlock/poweron blinks instead of the main LEDs.
//#define BLINK_ONCE_AUX_TIME_4MS 10 //when using aux instead of main LEDs, aux stay on green for this long (4ms increments)

// TODO: #define MOMENTARY_TURBO_FROM_LOCK_TIME_LIMIT 30 //limit momentary turbo from lock to this many seconds as an alternative to disabling it completely

//#define USE_BEACON_ON_CONFIG //in beacon mode, 2H to set on time - each blink is 100ms.
//#define USE_BEACON_BRIGHTNESS_RAMP //in beacon mode, 3/4H to ramp brightness up/down

//#define 2C_TURBO_ALWAYS_USE_SINGLE_CHANNEL //ignore 7H turbo config on dual channel lights and always go to single channel at 100%.
```

# Roadmap
* (Configurable?) optional time limit for momentary turbo mode from lock (just in case something wedges the button held)
* In progress: Make modifications and features user-configurable and modular
  * Modularise starryalley mods
    * Integrate startup modes? should be easy to make into a build time option
    * Integrate [6H aux control](https://github.com/starryalley/Anduril2#allow-the-use-of-auxindicator-led-in-lower-levels--default_level-level-6c6h-while-light-is-on) and voltage aux while on (as a mode under 6H functionality? would need to allow aux use at any ramp level. Need to wait for that fork to implement voltage mode there first)
    * Incorporate more changes from [SammysHP](https://github.com/SammysHP/flashlight-firmware/wiki/Modifications-Overview)
* When blinking aux red for low battery, wait for a while (blink 1-2x only? blink orange for the first 5-10 seconds then red if it remains low?) after running the light on a high setting to not trigger the warning unnecessarily due to voltage sag from putting load on the battery
  * How often is the battery voltage read?
* `LOCKOUT_3H_ACTION` - configurable between momentary turbo and channel ramping/switching for dual channel lights
* Make beacon on time configuration faster betweeen blinks?
* Better integrate multiple modifications to some parts of aux LED code
* Find something useful for 3C on single channel (jump to 50%? or user-definable level? back to memory?)
* New aux modes
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?

# General disclaimer

I am not responsible if you brick or otherwise break your light for any reason (bad flash, wrong firmware, mods did something unexpected, etc.). In general, I always test my changes myself on at least one light but I don't keep all of mine up to date with every commit or even every relevant one.
