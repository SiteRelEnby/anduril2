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

A fork of [anduril-buildenv-docker](https://github.com/SiteRelEnby/anduril-buildenv-docker) with a bug fixed.
Included as a submodule, to use it, run `git submodule update --init`. Note that to build the builder you will need a working [buildkit](https://docs.docker.com/build/buildkit) as well as base Docker.

Also on docker hub: https://hub.docker.com/r/siterelenby/anduril-builder

`docker pull siterelenby/anduril-builder:latest`

Note that my docker hub builds are multiarch but I have only personally tested on amd64, I can't think of any specific reason it wouldn't work on ARM though.

## Scripts

Example build scripts and header files for my lights (`build-siterelenby-*` and `spaghetti-monster/anduril/cfg-siterelenby*.h`) including a few extra default settings vs the default model header files.

Build scripts and image should work fine with the default codebase as well.

# Current upstream version this mod is based on

10/02/2023

# Changes from upstream

The goal is to keep reasonable commonality with base anduril, e.g. 7H, 9H, and 10H config menus stay in the same place; only things most people don't use that much like momentary and sunset modes or ramp style toggle should be moved. In general, avoiding removing functionality completely, just making stuff that gets in the way less easy to accidentally hit, and ideally adding some modularity for the user to decide which changes to include. Right now most changes are not modular.

## All lights

* Several less used options have been moved
  * Aux config from off/lock can be moved to 8C/8H with `USE_8C_AUX_CONFIG` to make it harder to accidentally hit when trying to do 6C/H
  * Ramp style selection moved to 8C (does anyone really change ramps that often?...)
  * Momentary mode moved to 12C (may move again in the future)
  * Sunset timer moved to 12H
  * Option to disable 4C ramp-> off/lock (`DISABLE_4C_LOCK_FROM_RAMP`)
* Incorporated some changes from [starryalley](https://github.com/starryalley/Anduril2):
  * Candle and strobe modes should work the same way now
    * 2C to cycle to next strobe, 3C to cycle to previous.
    * 4C to decrease candle/lighting mode activity, 5C to increase, 6C to reset
    * 4H in candle mode to change candle style
    * 7C in candle mode to toggle aux LEDs
    * Additional strobe mode: Fireworks mode (`USE_FIREWORK_MODE`), after lightning mode
    * On tint ramping lights, two additional strobe modes to switch and ramp between channels (after tactical strobe mode)
    * Blink aux/button red in off/lockout modes when battery is <= 3.2V
      * Increased the speed and time in an on state of the breathing animation (aux will still switch off entirely below 3V)
  * Green aux LEDs on power-on instead of blinking main LEDs
  * Temperature aux LED mode (after voltage in the cycle)
* Added an option to only use momentary mode from lock after enough time has passed to make sure it was only 1H (`WAIT_FOR_1H_WHEN_LOCKED`)
* Made the default aux blinking mode blink more often and intensely
* Build-time configuration for some additional stuff (in its own section)
  * Using aux LEDs to display the battery voltage while the light is on. This is by default only enabled for lights with an RGB button but no RGB aux (e.g. K1), but can be enabled for any light by setting `USE_AUX_RGB_LEDS_WHILE_ON` in the relevant header file. For lights with forward facing aux, added `RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF` and `RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW` to customise when the voltage is displayed, so if this causes a problem it can be disabled at low ramp levels. These also come in useful as a way to mark a specific level in the ramp with a visual cue (e.g. having the LED go to high at your thermally sustainable level).
* Use a less bzr/bizarre VCS
* Remove reference to bad childrens' fantasy novels by a terrible person. Please [read another book](https://knowyourmeme.com/memes/read-another-book).

## Dual channel lights only
* 2C now always goes to level 130 (single channel on maximum); 3C goes to 200%
* 4H for momentary opposite channel (6H with `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING`)
  * At the moment this will invert the ramp, e.g. if you are at a 25/75% mix between the two channels it will flip to 75/25. I may make this behaviour configurable in the future with other options.
* Single channel turbo shortcuts
  * 5C from off/lock/ramp mode for channel 1, hold for momentary
  * 6C from off/lock/ramp mode for channel 2, hold for momentary
  * Option to have the turbo shortcuts from 4C/H and 5C/H instead (`USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING`).
    * Implies `DISABLE_4C_LOCK_FROM_RAMP` and moves momentary opposite channel to 6H to make room.
* 8H to use the *opposite* channel switching mode (e.g. if 3C is configured for instant switching, 8H will ramp between channels)
* `DEFAULT_TINT` build-time option
* Option to make the light start in instant switching mode by default via header file (currently kind of a kludge as it needs a rebuild to change - although fixing that is low priority as it's not something that many people probably want to change much)
* Shortcuts to turbo modes for each channel (5C/6C)
* Momentary turbo modes for each channel (5H/6H)
* An option (in the header file for now) to switch which of the two channels is considered the first for 5-6C/H (might move this to the 9H menu later, see note on defaulting to instant switching)

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

// default channel mix for when the light first starts up or is reset. Can be set to any value 1-254.
//#define DEFAULT_TINT 1
//#define DEFAULT_TINT 128
//#define DEFAULT_TINT 254

//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30 //at or below here, aux off while on
//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50 //at or below here, aux low while on
//#define USE_OPPOSITE_TINTRAMP_KLUDGE //start in channel switching mode rather than ramping
//#define USE_8C_AUX_CONFIG //configure aux with 8C/H instead of 7C/H

//#define USE_FIREWORK_MODE //enable fireworks mode

// Moves dual channel turbo shortcuts from 5/6 C/H to 4/5, for ramp mode only. Leaving this unset stays consistent with off/lock modes,
// but 4C/H functions might be uses less often, so adding an option to put the turbo modes first.
// This also moves momentary opposite channel to 6H and disables 4C to switch off and lock directly from ramp mode in order to make room.
//#define USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING

//#define DISABLE_4C_LOCK_FROM_RAMP //disable 4C -> lock without the above reordering.

//#define DISABLE_UNLOCK_TO_TURBO //disables 5C/6C from lock shortcuts to unlock to turbo

//#define WAIT_FOR_1H_WHEN_LOCKED //delay momentary moon from lock until input is confirmed to be 1H - prevents main LEDs flashing when doing more clicks from lock.
```

# UI reference
Single channel lights should be working but are currently relatively low on additional features.

|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock|Feature flags|
|-----|-------------------|------------------|---------------------|--------------------|-------------|
|     |OFF MODE         |OFF MODE |OFF MODE |OFF MODE | |
|1C|  On (memory) |On (memory) | On (memory) | On (memory) |
|1H|  Moon | Moon | Moon | Moon | |
|2C|  On (ceiling) | On (ceiling) | On (ceiling) | On (ceiling) | |
|2H|  Momentary 200% turbo | Momentary configured turbo | Momentary turbo | Momentary turbo | |
|3C|  Blinky modes | Blinky modes | Blinky modes | Blinky modes | |
|4C|  Lock | Lock | Lock | Lock | |
|4H|  (nothing) | (nothing) | (nothing) | (nothing) | |
|5C|  ch1 turbo | momentary mode | (nothing) | momentary mode | |
|5H|  Momentary ch1 turbo | (nothing) | (nothing) | (nothing) | |
|6C|  ch2 turbo | (nothing) | (nothing) | (nothing) | |
|6H|  momentary ch2 turbo| (nothing) | (nothing) | (nothing) | |
|7C|  (nothing) | aux brightness | (nothing) |aux brightness | |
|7H|  (nothing) | aux mode | (nothing) | aux mode | |
|8C|  aux brightness | (nothing) | aux brightness | (nothing) | |
|8H|  aux modes | (nothing) | aux modes | (nothing) | |
|9H|  globals config | globals config | globals config | globals config | |
|10H| Simple UI config | simple UI config | simple UI config | simple UI config | |
|12C| Momentary mode | (nothing) | Momentary mode | (nothing) | |
|13H| factory reset | factory reset | factory reset | factory reset | |
|15C| version check | version check| version check | version check | |
|   |LOCK MODE| LOCK MODE | LOCK MODE | LOCK MODE | |
|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock | |
|1H|  momentary moon | momentary moon|momentary moon|momentary moon | |
|2H|  momentary floor/mem| momentary floor/mem| momentary floor/mem | momentary floor/mem | |
|3H|  channel switch (default) | channel switch | moon (ignored) | moon (ignored) | |
|4C|  Unlock to memory | unlock to memory | unlock to mem | unlock to mem | |
|4H|  unlock to floor | unlock to floor | unlock to floor | unlock to floor | |
|5C|  unlock to ch1 turbo |unlock to turbo | unlock to turbo | unlock to turbo | `DISABLE_UNLOCK_TO_TURBO` |
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
|2C|  single channel turbo | turbo | turbo | turbo | |
|2H|  ramp down | ramp down | ramp down | ramp down | |
|3C|  200% turbo | ramp style toggle | (nothing (TODO)) | ramp style | |
|3H|  channel switch (default) | channel switch | momentary turbo | momentary turbo | |
|4C|  <ul><li>off and lock</li><li>ch1 turbo</li></ul> | off and lock | <ul><li>off and lock</li><li>(nothing)</li></ul> | off and lock | <ul><li>`USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING`</li><li>`DISABLE_4C_LOCK_FROM_RAMP`</li></ul> |
|4H|  <ul><li>momentary channel switch</li><li>momentary ch1 turbo</li></ul> | (nothing) | (nothing) | (nothing) | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING`|
|5C|  <ul><li>ch1 turbo</li><li>ch2 turbo</li></ul> | momentary mode | (nothing) | momentary mode | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|5H|  <ul><li>momentary ch1 turbo</li><li>momentary ch1 turbo</li></ul> | sunset mode | (nothing) | sunset mode | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|6C|  <ul><li>ch2 turbo</li><li>(nothing)</li></ul> | (nothing) | (nothing) | (nothing) | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|6H|  <ul><li>momentary ch2 turbok</li><li>momentary channel switch</li></ul> | (nothing) | (nothing) | (nothing) | `USE_DUAL_TURBO_SHORTCUTS_FROM_4C_WHEN_RAMPING` |
|7C|  aux brightness<br />(no `USE_8C_AUX_CONFIG`) | aux brightness | aux brightness<br />(no `USE_8C_AUX_CONFIG`) | aux brightness | `USE_8C_AUX_CONFIG` |
|7H|  aux mode<br />(no `USE_8C_AUX_CONFIG`) | aux mode | aux mode<br />(no `USE_8C_AUX_CONFIG`) | aux mode | `USE_8C_AUX_CONFIG` |
|8C|  aux brightness<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | aux brightness<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | `USE_8C_AUX_CONFIG` |
|8H|  aux mode<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | aux mode<br />(with  `USE_8C_AUX_CONFIG`) | (nothing) | `USE_8C_AUX_CONFIG` |
|10C| save memory | save memory | save mem | save mem | |
|10H| ramp extras config | ramp extras config | ramp extras | ramp extras | |
|12C| momentary mode | (nothing) | momentary mode | (nothing) | |
|12H| sunset mode | (nothing) | sunset mode | (nothing) | |
|   | STROBE MODES | STROBE MODES | STROBE MODES | STROBE MODES | |
|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock|
|1C|  off | off | off | off |
|1H|  brightness up | brightness up | brightness up | brightness up |
|2C|  next mode | next mode | next mode | next mode |
|2H|  brightness down | brightness down | brightness down | brightness down |
|3C|  prev mode | (nothing) | prev mode | (nothing) |
|3H|  tint ramp/switch (not all modes) | tint ramp/switch (not all modes) | (nothing) | (nothing) |
|4C|  reduce candle/lightning activity<br />reduce fireworks brightness | (nothing) | reduce candle/lightning activity<br />reduce fireworks brightness | (nothing) |
|4H|  cycle candle mode style | (nothing) | candle mode style | (nothing) |
|5C|  increase candle/lighting activity | (nothing) | (nothing) | (nothing) |
|6C|  reset candle/lightning activity<br />reset fireworks brightness | (nothing) | reset candle/lightning activity<br />reset fireworks brightness | (nothing) |
|7C|  toggle aux (candle mode only) | (nothing) | toggle candle aux | (nothing) |


## Roadmap
* Modularise most stuff e.g. dual channel turbo modes into a separate file and make it optional at build time
  * Modularise starryalley mods
    * Integrate startup modes? should be easy to make into a build time option
* Better integrate multiple modifications to some parts of aux LED code
* TODO: momentary opposite channel from 4H in off mode?
* Find something useful for 3C on single channel
* Option (possibly in light-specific header file) to change which channel is considered channel 1 (as it stands the same value ended up being right for both of my lights but this obviously depends on the specific light)
* Possibly move momentary opposite channel to a higher button combo and the turbo shortcuts down (after some use of this fw, have discovered I use those more than momentary opposite at current ramp level)
* New aux modes
* New mode shortcuts
* Option to delay momentary moon/memory from lock by at least RELEASE_TIMEOUT to match configurability of B_TIMING_ON
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?
