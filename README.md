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

## All lights

* Remappable shortcuts. At the moment, some have been moved with no specific option to move back, but that's a work in progress. Currently remappable functions:
  * Aux colour/mode
  * Dual channel turbo shortcuts
  * 200% turbo shortcut
* Ramp style selection moved to 8C (does anyone really change ramps that often?...)
* Momentary mode moved to 12C (may move again in the future)
* Sunset timer moved to 12H
* Options to disable some features
  * `DISABLE_4C_LOCK_FROM_RAMP`: Disable 4C ramp-> off/lock (4C from off is not changed)
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
  * 2H in beacon mode to set the time the light is on (1 blink = 100ms) (`USE_BEACON_ON_CONFIG`). Each blink while held is 100ms of time on.
    * Added 3/4H in beacon mode to increase/decrease brightness without exiting. This is not strictly a *new* feature as beacon mode normally uses the last ramped level, it just allows on the fly adjustment. Enabled with `USE_BEACON_BRIGHTNESS_RAMP`.
    * Note that there is no thermal regulation in this mode so don't overheat your light - test it before leaving it unattended.
  * Green aux LEDs on power-on instead of blinking main LEDs (can be disabled with `USE_MAIN_LEDS_FOR_ALL_BLINKS`
  * Temperature aux LED mode (after voltage in the cycle)
* Added options to only use momentary mode from lock after enough time has passed to make sure it was only 1H (`WAIT_FOR_MOMENTARY_WHEN_LOCKED` / `MOMENTARY_WHEN_LOCKED_DELAY`)
* Made the default aux blinking mode blink more often and intensely
* Build-time configuration for some additional stuff (in its own section)
  * Using aux LEDs to display the battery voltage while the light is on. This is by default only enabled for lights with an RGB button but no RGB aux (e.g. K1), but can be enabled for any light by setting `USE_AUX_RGB_LEDS_WHILE_ON` in the relevant header file. For lights with forward facing aux, added `RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF` and `RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW` to customise when the voltage is displayed, so if this causes a problem it can be disabled at low ramp levels. These also come in useful as a way to mark a specific level in the ramp with a visual cue (e.g. having the LED go to high at your thermally sustainable level).
  * `DISABLE_4C_LOCK_FROM_RAMP`: Disable 4C to lock while the light is on
* Move aux to a different combo:
```
#define AUX_CONFIG_CLICK_EVENT = EV_8clicks
```
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
* Momentary opposite channel mode (4H) for momentary opposite channel
  * At the moment this will invert the ramp, e.g. if you are at a 25/75% mix between the two channels it will flip to 75/25. I may make this behaviour configurable in the future with other options.
* 8H to use the *opposite* channel switching mode (e.g. if 3C is configured for instant switching, 8H will ramp between channels)
* `DEFAULT_TINT` build-time option
* Option to make the light start in instant switching mode by default via header file (currently kind of a kludge as it needs a rebuild to change - although fixing that is low priority as it's not something that many people probably want to change much)
* Shortcuts to turbo modes for each channel (5C/6C)
* Momentary turbo modes for each channel (5H/6H)
* An option (in the header file for now) to switch which of the two channels is considered the first for 5-6C/H (might move this to the 9H menu later, see note on defaulting to instant switching)

## Single channel lights only
* 3H from lock for turbo (can be disabled with `DISABLE_MOMENTARY_TURBO_FROM_LOCK`)

# Lights tested with
These are lights that I own. Currently all of them are running this fork. Not every single commit or release will be tested on every single light.

* D4Sv2 (dual channel, FET)
* DM1.12 (FET on flood channel. based on D4Sv2 header file)
* K1
* KR1
* DT8K (based on KR4 header file)
* D4 (boost driver; no FET)

# Build-time configuration

Some of the changes in this firmware are only configurable at build-time. Additional parameters for cfg header files added:
* `#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30`: Sets the threshold at which to switch the voltage RGB aux off
* `#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50`: Sets the threshold at which to switch the voltage RGB aux to low mode
* `#define USE_OPPOSITE_TINTRAMP_KLUDGE`: When defined, makes the light start in channel switching mode. A very inelegant solution but it works so not being redone for now. May be replaced with a better way in the future.

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

//==========   settings related to my mods, will be ignored in stock anduril:

//#define MOMENTARY_WHEN_LOCKED_DELAY 2 //number of ticks to wait before activating momentary mode when locked - prevents a flash when inputting a higher number of clicks.

// default channel mix for when the light first starts up or is reset. Can be set to any value 1-254.
//#define DEFAULT_TINT 1
//#define DEFAULT_TINT 128
//#define DEFAULT_TINT 254

//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30 //at or below here, aux off while on
//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50 //at or below here, aux low while on
//#define USE_OPPOSITE_TINTRAMP_KLUDGE //start in channel switching mode rather than ramping

//#define USE_FIREWORK_MODE //enable fireworks mode

//#define DISABLE_4C_LOCK_FROM_RAMP //disable 4C -> lock while on

//#define DISABLE_UNLOCK_TO_TURBO //disables 5C/6C from lock shortcuts to unlock to turbo

// Delay momentary from lock until input is confirmed to definitely be 1H - prevents main LEDs flashing when doing more clicks from lock.
// This setting guarantees a flash will be avoided when unlocking, but might be too slow for many people (including me) - see MOMENTARY_WHEN_LOCKED_DELAY for an alternative.
//#define WAIT_FOR_MOMENTARY_WHEN_LOCKED

// Delay momentary from lock by this many clock ticks (default HOLD_TIMEOUT is 24), useful for a shorter delay than WAIT_FOR_MOMENTARY_WHEN_LOCKED.
// I find that 2 is enough for me, at least on LEDs with a somewhat high Vf (e.g. 519A, W1/W2), but if you click a bit more slowly or have lower Vf, 3-4 might be good.
//#define MOMENTARY_WHEN_LOCKED_DELAY 2

//#define DISABLE_MOMENTARY_TURBO_FROM_LOCK

//#define USE_MAIN_LEDS_FOR_ALL_BLINKS //disable using aux/button LED for lock/unlock/poweron blinks instead of the main LEDs.
//#define BLINK_ONCE_AUX_TIME_4MS 10 //when using aux instead of main LEDs, aux stay on green for this long (4ms increments)

// TODO: #define MOMENTARY_TURBO_FROM_LOCK_TIME_LIMIT 30 //limit momentary turbo from lock to this many seconds as an alternative to disabling it completely

//#define USE_BEACON_ON_CONFIG //in beacon mode, 2H to set on time - each blink is 100ms.
//#define USE_BEACON_BRIGHTNESS_RAMP //in beacon mode, 3/4H to ramp brightness up/down

//#define 2C_TURBO_ALWAYS_USE_SINGLE_CHANNEL //ignore 7H turbo config on dual channel lights and always go to single channel at 100%.
```

# UI reference
Stuff that is not changed at all (e.g. thermal and voltage calibration) is not mentioned here.

|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock|Feature flags|
|-----|-------------------|------------------|---------------------|--------------------|-------------|
|     |OFF MODE         |OFF MODE |OFF MODE |OFF MODE | |
|1C|  On (memory) |On (memory) | On (memory) | On (memory) |
|1H|  Moon | Moon | Moon | Moon | |
|2C|  On (ceiling) | On (ceiling) | On (ceiling) | On (ceiling) | |
|2H|  Momentary turbo (based on 10H turbo config) | Momentary configured turbo | Momentary turbo | Momentary turbo | `DEFAULT_2C_STYLE`<br />`DEFAULT_2C_STYLE_SIMPLE`<br />`2C_TURBO_ALWAYS_USE_SINGLE_CHANNEL` |
|3C|  Blinky modes | Blinky modes | Blinky modes | Blinky modes | |
|3H|  Candle/strobe modes | Candle/strobes | Candle/strobes | Candle/strobes | `USE_FIREWORK_MODE` |
|4C|  Lock | Lock | Lock | Lock | |
|4H|  (nothing) | (nothing) | (nothing) | (nothing) | |
|5C|  ch1 turbo | momentary mode | (nothing) | momentary mode | |
|5H|  Momentary ch1 turbo | (nothing) | (nothing) | (nothing) | |
|6C|  ch2 turbo | (nothing) | (nothing) | (nothing) | |
|6H|  momentary ch2 turbo| (nothing) | (nothing) | (nothing) | |
|7C|  aux brightness<br />(no `USE_8C_AUX_CONFIG`) | aux brightness | aux brightness<br />(no `USE_8C_AUX_CONFIG`) | aux brightness | `USE_8C_AUX_CONFIG` |
|7H|  aux mode<br />(no `USE_8C_AUX_CONFIG`) | aux mode | aux mode<br />(no `USE_8C_AUX_CONFIG`) | aux mode | `USE_8C_AUX_CONFIG` |
|8C|  aux brightness<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | aux brightness<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | `USE_8C_AUX_CONFIG` |
|8H|  aux mode<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | aux mode<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | `USE_8C_AUX_CONFIG` |
|9H|  globals config | globals config | globals config | globals config | |
|10H| Simple UI config | simple UI config | simple UI config | simple UI config | |
|12C| Momentary mode | (nothing) | Momentary mode | (nothing) | |
|13H| factory reset | factory reset | factory reset | factory reset | |
|15C| version check | version check| version check | version check | |
|   |LOCK MODE| LOCK MODE | LOCK MODE | LOCK MODE | |
|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock | |
|1H|  momentary moon | momentary moon | momentary moon | momentary moon | |
|2H|  momentary floor/mem | momentary floor/mem| momentary floor/mem | momentary floor/mem | |
|3C|  unlock and stay off | unlock and stay off | unlock and stay off | unlock and stay off | `USE_MAIN_LEDS_FOR_ALL_BLINKS` |
|3H|  channel switch (default) | channel switch | momentary turbo | moon (ignored) | `DISABLE_MOMENTARY_TURBO_FROM_LOCK` |
|4C|  Unlock to memory | unlock to memory | unlock to mem | unlock to mem | |
|4H|  unlock to floor | unlock to floor | unlock to floor | unlock to floor | |
|5C|  unlock to ch1 turbo | unlock to turbo | unlock to turbo | unlock to turbo | `DISABLE_UNLOCK_TO_TURBO` |
|5H|  momentary ch1 turbo | moon (ignored) | moon (ignored) | moon (ignored) | |
|6C|  unlock to ch2 turbo | moon (ignored) | moon (ignored) | moon (ignored) | `DISABLE_UNLOCK_TO_TURBO` |
|6H|  momentary ch2 turbo | moon (ignored) | moon (ignored) | moon (ignored) | |
|7C|  aux brightness<br />(no `USE_8C_AUX_CONFIG`) | aux brightness | aux brightness<br />(no `USE_8C_AUX_CONFIG`) | aux brightness | `USE_8C_AUX_CONFIG` |
|7H|  aux mode<br />(no `USE_8C_AUX_CONFIG`) | aux mode | aux mode<br />(no `USE_8C_AUX_CONFIG`) | aux mode | `USE_8C_AUX_CONFIG` |
|8C|  aux brightness<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | aux brightness<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | `USE_8C_AUX_CONFIG` |
|8H|  aux mode<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | aux mode<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | `USE_8C_AUX_CONFIG` |
|10H| autolock config | autolock config| autolock config | autolock config | |
|   | RAMP MODE| RAMP MODE | RAMP MODE |RAMP MODE | |
|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock | |
|1C|  off | off | off |off | |
|1H|  ramp up | ramp up | ramp up | ramp up | |
|2C|  Turbo (based on 10H turbo config) | turbo (configured) | turbo (configured) | turbo (configured) | `DEFAULT_2C_STYLE`<br />`DEFAULT_2C_STYLE_SIMPLE` |
|2H|  ramp down | ramp down | ramp down | ramp down | |
|3C|  200% turbo | ramp style toggle | (nothing (TODO)) | ramp style | |
|3H|  channel switch (default) | channel switch | momentary turbo | momentary turbo | |
|4C|  <ul><li>off and lock</li><li>ch1 turbo</li></ul> | off and lock | <ul><li>off and lock</li><li>(nothing)</li></ul> | off and lock | <ul><li>`USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING`</li><li>`DISABLE_4C_LOCK_FROM_RAMP`</li><li>`USE_MAIN_LEDS_FOR_ALL_BLINKS`</li></ul> |
|4H|  <ul><li>momentary channel switch</li><li>momentary ch1 turbo</li></ul> | (nothing) | (nothing) | (nothing) | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING`|
|5C|  <ul><li>ch1 turbo</li><li>ch2 turbo</li></ul> | momentary mode | (nothing) | momentary mode | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|5H|  <ul><li>momentary ch1 turbo</li><li>momentary ch1 turbo</li></ul> | sunset mode | (nothing) | sunset mode | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|6C|  <ul><li>ch2 turbo</li><li>(nothing)</li></ul> | (nothing) | (nothing) | (nothing) | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|6H|  <ul><li>momentary ch2 turbok</li><li>momentary channel switch</li></ul> | (nothing) | (nothing) | (nothing) | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|10C| save memory | save memory | save mem | save mem | |
|10H| ramp extras config | ramp extras config | ramp extras | ramp extras | |
|12C| momentary mode | (nothing) | momentary mode | (nothing) | |
|12H| sunset mode | (nothing) | sunset mode | (nothing) | |
|   | STROBE MODES | STROBE MODES | STROBE MODES | STROBE MODES | |
|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock| |
|1C|  off | off | off | off | |
|1H|  brightness up | brightness up | brightness up | brightness up | |
|2C|  next mode | next mode | next mode | next mode | |
|2H|  brightness down | brightness down | brightness down | brightness down | |
|3C|  prev mode | (nothing) | prev mode | (nothing) | |
|3H|  tint ramp/switch (not all modes) | tint ramp/switch (not all modes) | (nothing) | (nothing) | |
|4C|  reduce candle/lightning activity<br />reduce fireworks brightness | (nothing) | reduce candle/lightning activity<br />reduce fireworks brightness | (nothing) | |
|4H|  cycle candle mode style | (nothing) | candle mode style | (nothing) | |
|5C|  increase candle/lighting activity | (nothing) | (nothing) | (nothing) | |
|6C|  reset candle/lightning activity<br />reset fireworks brightness | (nothing) | reset candle/lightning activity<br />reset fireworks brightness | (nothing) | |
|7C|  toggle aux (candle mode only) | (nothing) | toggle candle aux | (nothing) | |
|  |  BLINKY MODES | BLINKY MODES | BLINKY MODES | BLINKY MODES | |
|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock| |
|2C|  next mode | next mode | next mode | next mode | |
|2H|  BEACON MODE: set time light is on for | (nothing) | BEACON MODE: set time light is on for | (nothing) | `USE_BEACON_ON_CONFIG` | |
|3H|  BEACON MODE: ramp brightness up/down | (nothing) | BEACON MODE: ramp brightness up/down | (nothing) | `USE_BEACON_BRIGHTNESS_RAMP` | |
|4H|  BEACON MODE: ramp brightness down | (nothing) | BEACON MODE: ramp brightness down | (nothing) | `USE_BEACON_BRIGHTNESS_RAMP` | |

# Roadmap
* (Configurable?) optional time limit for momentary turbo mode from lock (just in case something wedges the button held)
* Modularise most stuff e.g. dual channel turbo modes into a separate file and make it optional at build time
  * Modularise starryalley mods
    * Integrate startup modes? should be easy to make into a build time option
    * Integrate [6H aux control](https://github.com/starryalley/Anduril2#allow-the-use-of-auxindicator-led-in-lower-levels--default_level-level-6c6h-while-light-is-on) and voltage aux while on (as a mode under 6H functionality? would need to allow aux use at any ramp level)
    * Incorporate more changes from [SammysHP](https://github.com/SammysHP/flashlight-firmware/wiki/Modifications-Overview)
* When blinking aux red for low battery, wait for a while (blink 1-2x only? blink orange for the first 5-10 seconds then red if it remains low?) after running the light on a high setting to not trigger the warning unnecessarfily due to voltage sag from putting load on the battery
  * How often is the battery voltage read?
* Make beacon on time configuration faster betweeen blinks?
* Better integrate multiple modifications to some parts of aux LED code
* Find something useful for 3C on single channel (jump to 50%? or user-definable level? back to memory?)
* Option (possibly in light-specific header file) to change which channel is considered channel 1 (as it stands the same value ended up being right for both of my lights but this obviously depends on the specific light)
* New aux modes
* New mode shortcuts
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?

# General disclaimer

I am not responsible if you brick or otherwise break your light for any reason (bad flash, wrong firmware, mods did something unexpected, etc.). In general, I always test my changes myself on at least one light but I don't keep all of mine up to date with every commit or even every relevant one.
