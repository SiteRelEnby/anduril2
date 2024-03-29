# anduril2

Anduril2 originally by [ToyKeeper](https://code.launchpad.net/~toykeeper/flashlight-firmware/anduril2), mods by @SiteRelEnby.

This is my own modded version of anduril2. Definitely an ongoing project, the idea eventually is to make configurable custom builds simple, so allowing anduril to exceed the limits of its MCU size by adding new features and making it easy to modify by enabling, disabling, or moving features. It's somewhat of a perpetual work in progress (after a hard day writing code, I write code to relax...).

# The quick info

* I generally keep the underlying codebase reasonably up to date with ToyKeeper's releases. Sometimes I will merge in patches early.
* Lots of new features. The section outlining them all probably needs rewriting.
* I make releases semi-arbitrarily when I feel there have been enough changes to justify one. I will usuually build custom builds for all of my lights, as well as each configuration listed in [example configurations](#example-configurations). These are intended to be relatively general purpose, and should be built for all lights they make sense for. If you have a good idea for one, open an issue or otherwise let me know.
* The eventual goal is to make it reasonably simple to build your own configuration via some kind of interactive script/UI... If you're interested (especially if you can make UIs, I hate doing that), let me know.

# Current upstream version this mod is based on

[multi-channel branch](https://bazaar.launchpad.net/~toykeeper/flashlight-firmware/multi-channel): Revision [762](https://bazaar.launchpad.net/~toykeeper/flashlight-firmware/multi-channel/revision/762)

There is an older branch based on the old 2-channel only code at `main_2channelonly`, consider that archived and not in active development.

# Changes from upstream

The goal for this fork is to be reasonably modular - if you don't want/need a feature, it can be enabled or disabled. Ideally, it should be usable for someone familiar with anduril, e.g. by default 7H, 9H, and 10H config menus stay in the same place. Most of the extra options and configuration is done at build-time using feature flags (there just isn't enough space to make everything configurable). In general, avoiding removing functionality completely, just giving the user the option if they want it.

## Custom mode mappings

The main feature of this fork. Many functions can be remapped by changing a define in your light's header file. For default anduril mappings:
```
//mappings from ON:
#define EVENT_SUNSET_TIMER_HOLD EV_click5_hold
#define RAMP_STYLE_TOGGLE_EVENT EV_3clicks
#define EVENT_RAMP_CONFIG_HOLD EV_click7_hold
#define MOMENTARY_CLICK_EVENT EV_5clicks
#define LOCK_FROM_ON_EVENT EV_4clicks

//not yet implemented for multichannel:
#define MANUAL_MEMORY_SAVE_CLICK_EVENT EV_10clicks

// mappings from OFF:
#define MOMENTARY_CLICK_EVENT_OFF MOMENTARY_CLICK_EVENT //can set a separate shortcut from off mode

// mappings from strobe mode:
#define MOMENTARY_CLICK_EVENT_STROBE MOMENTARY_CLICK_EVENT //can set a separate shortcut from strobe mode

// mappings from off/lock state:
#define EVENT_AUX_CONFIG EV_7clicks
#define EVENT_AUX_CONFIG_HOLD EV_click7_hold
#define EVENT_AUX_CONFIG_HOLD_RELEASE EV_click7_hold
#define EVENT_TACTICAL_MODE EV_6clicks
```

Some stock features can be disabled completely by unsetting their event as well. This will save some image size as well:
```
#undef LOCK_FROM_ON_EVENT
```

Mappings for new features (see below for an explanation of these features). Adding each of these will generally add a small amount of size to the generated image:
```
// mappings from ON:
#define MOMENTARY_TURBO_1_EVENT EV_5clicks
#define TURBO_SHORTCUT_1_CHANNEL CM_CH1
#define MOMENTARY_TURBO_1_EVENT EV_click5_hold
#define MOMENTARY_TURBO_1_EVENT EV_click5_hold_release
#define MOMENTARY_TURBO_2_EVENT EV_5clicks
#define TURBO_SHORTCUT_2_CHANNEL CM_CH2
#define MOMENTARY_TURBO_2_EVENT EV_click6_hold
#define MOMENTARY_TURBO_2_EVENT EV_click6_hold_release
#define EVENT_PREVIOUS_CHANNEL EV_4clicks
#define EVENT_AUX_WHILE_ON_TOGGLE EV_8clicks

// mappings from OFF:
#define EVENT_CHANNEL_CYCLE_OFF_HOLD EV_click4_hold
#define EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE EV_click4_hold_release
#define EVENT_CHANNEL_CYCLE_ON_HOLD EV_click8_hold
#define EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE EV_click8_hold_release
#define EVENT_CHANNEL_CYCLE_LOCK_HOLD EV_click3_hold

//mappings from LOCKOUT:
#define EVENT_CHANNEL_CYCLE_LOCK_HOLD EV_click3_hold
```

Some example files to look at as examples for your own build:
* `spaghetti-monster/anduril/cfg-siterelenby-emisar-2ch-aux.h`

Note that the build does not (TODO: currently?) check for conflicts, which may cause weird things to happen, or may just cause the function to not work.

## All lights

* Remappable shortcuts. A work in progress, see above for details.
  * Remappable default functionality:
    * Momentary mode (default 5C)
    * Sunset timer (default 5H)
    * Lock from on (default 4H - can also be disabled by unsetting)
    * Ramp config menu (default 7H)
    * Channel mode config (default 9H from on)
    * Stepped/smooth ramp toggle (default 3C single channel, 6C multichannel)
    * Aux colour/mode config (default 7C/H)
    * Tactical mode (default 6C - can also be disabled by unsetting)
    * Save manual memory (default 10C) - can also be disabled by unsetting)
    * Cycle channels when locked (default 3H - can also be disabled by unsetting)
  * New features:
    * Dual channel turbo shortcuts
    * Max (200%) turbo shortcut
    * Channel cycle - continues to cycle through channels when held. Somewhat of a placeholder for future support of >2 channels but also works fine with two.
    * Blink RGB aux (if present) when locked on 1/2C (`BLINK_LOCK_REMINDER`)
    * Option to always use RGB aux when on (even on lights with forward facing aux) (`USE_AUX_RGB_LEDS_WHILE_ON`)
      * Voltage aux can be switched on/off while on if `EVENT_AUX_WHILE_ON_TOGGLE` is defined
      * If `USE_AUX_WHILE_ON_CONFIG`, adds extra items to off->9H menu:
        * 3rd item: 1C disable aux voltage while on, 2+C enable
        * 4th item: Set threshold for which voltage aux are enabled on LOW brightness (clicks minus 1 = ramp level, e.g. 1C = always if not enabled for high instead, n clicks: enable low at n-1 (i.e. 2C for level 1, 151+C for always disabled)
        * 5th item: Set threshold for which voltage aux are enabled on HIGH brightness (clicks minus 1 = ramp level, e.g. 1C = always high, 51C = enable high at level 50, 151+C = never use high)
    * Remember lockout state across battery changes - enabled with `USE_LOCKOUT_MEMORY`
    * Build-time configuration for some additional stuff (in its own section)
    * [Tactical mode](https://budgetlightforum.com/t/why-i-still-use-anduril-1-for-edc-anduril-2-lacking-an-anduril-1-feature-suggestion-and-request-for-programmer/217573). This is actually a new upstream feature that has not made it into any releases yet. Enable with `USE_TACTICAL_MODE`
      * Default 6C from off to enter/exit (remappable in this fork with `TACTICAL_MODE_CLICK_EVENT`). Tactical mode has 3 different momentary level slots that can be configured to be either level 1-150 as normal, or levels above 151 which correspond to strobe modes (151 == party strobe, 152 == tactical strobe, 153 == lightning mode, 154 == candle mode, etc...)
      * Tactical mode controls:
        * 1H: Tactical slot 1
        * 2H: Tactical slot 2
        * 3H: Tactical slot 3
        * 6C (unless remapped): Exit tactical mode
        * 7H: tactical mode config menu. Enter the level for each slot.
          * Slots can be preconfigured in your header file with `TACTICAL_LEVELS` - e.g. `TACTICAL_LEVELS RAMP_SIZE,(RAMP_SIZE+2),100` for turbo/strobe/high.
    * Post-off voltage (anothhr new upstream feature). When the light is switched off, displays the voltage for a few seconds using RGB aux before resuming normal off/lockout aux pattern. Configurable from the 7H menu on battcheck mode - second item is the number of seconds to display for (0C to disable)
      * Added a third item to the menu, which sets the level at which high brightness is used rather than low to (clicks - 1). e.g. 0C ignored, 1C = use low aux after the light was on at level 1 only, 11C = use low aux after the light was on at <= level 10, etc.)
    * 3H from lock for turbo (enable with `USE_3H_TURBO_FROM_LOCK`)
    * Option to have the aux stay on high in off/lockout mode for a configurable timeout, then go to the user-configured mode.
      * Enable feature with `USE_LOCKOUT_HIGH_AUX_TIMER` / `USE_OFF_HIGH_AUX_TIMER`. Set the default (in minutes) with `USE_LOCKOUT_HIGH_AUX_TIMER_DEFAULT` / `USE_OFF_HIGH_AUX_TIMER_DEFAULT` (e.g. `#define USE_LOCKOUT_HIGH_AUX_TIMER_DEFAULT 30`)
        * Optional: `LOCKOUT_HIGH_AUX_CLICKS`. Set to `1` to only set high aux when locked from 1C, or `2` to only set high aux when locked from 2C.
      * Configure at runtime on the 10H from lockout mode, 2nd/3rd items (TODO: configuring this for off mode from lockout mode is janky af but I can't think of a better way right now). 1 click = 1 minute / 0 clicks = disable.

## Multichannel lights only
* Configurable shortcuts to specific channel mode turbo modes (`TURBO_SHORTCUT_1_CHANNEL`, `EVENT_TURBO_SHORTCUT_1`, `EVENT_TURBO_SHORTCUT_1_MOMENTARY`, `EVENT_TURBO_SHORTCUT_1_MOMENTARY_RELEASE`) and maximum (i.e. 200%) (`EVENT_TURBO_MAX`, `TURBO_MAX_CHANNEL` `EVENT_TURBO_MAX_MOMENTARY`, `EVENT_TURBO_MAX_MOMENTARY_RELEASE`)
* Previous channel (`EVENT_PREVIOUS_CHANNEL`)
* Cycle through channel modes in off or ramp mode, similarly to in lockout mode (`EVENT_CHANNEL_CYCLE_OFF_HOLD`, `EVENT_CHANNEL_CYCLE_OFF_HOLD_RELEASE`, `EVENT_CHANNEL_CYCLE_ON_HOLD`, `EVENT_CHANNEL_CYCLE_ON_HOLD_RELEASE`)
  * Remappable for lockout mode (`EVENT_CHANNEL_CYCLE_LOCK_HOLD`)
* Options to disable 3H being momentary turbo on channelmodes without args (aka "turboing yourself in the face made easy"). `NO_ARG_3H_OVERRIDE = 1` = blink on 3H instead of doing anything else, `NO_ARG_3H_OVERRIDE = 2` = force ramping mode on 3H. Leave unset to have 3H falling through to momentary turbo. 4H remains momentary turbo with any of these set.

## Config menus
This mod adds items to config menus, so the exact size and order of config menus may vary depending on what you have enabled.

In general, if *everything* was enabled, config menus should be as follows (not bothering to list ones that aren't changed). Mod-added options are in bold:

* Voltage config (7H from battcheck mode):
  * Voltage calibration
  * Post-off voltage seconds
  * **Post-off voltage brightness threshold**
* Lockout config (10H from lockout mode):
  * Autolock minutes
  * **Minutes to force high aux when locked**
  * **Minutes to force high aux when off** (yes, I am aware configuring this for off mode from lockout mode is janky af but I can't think of a better way right now...)
* Global settings config (9H from off):
  * Tint ramp config
  * Jumpstart config
  * **RGB voltage aux while on - enable/disable**
  * **RGB voltage aux while on - low threshold**
  * **RGB voltage aux while on - high threshold**

## Features todo

Old features still to be ported to multichannel (subject to change):
* More configurable beacon mode
* [Starryalley](https://github.com/starryalley/Anduril2) aux modes
* Blink aux/button red in off/lockout modes when battery is <= 3.2V
* More configurable blinks using aux?
* Options to only use momentary mode from lock after enough time has passed to make sure it was only 1H (`WAIT_FOR_MOMENTARY_WHEN_LOCKED` / `MOMENTARY_WHEN_LOCKED_DELAY`)
* More aux modes
  * Low with high blink (the default off/low/high blink mode bothers me for a reason I can't quite work out)
* Changes to saving manual memory?
* Manual EEPROM save instead of automatic
* Momentary opposite channel mode (e.g. `#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT_RELEASE EV_click4_hold_release` `#define MOMENTARY_OPPOSITE_CHANNEL_HOLD_EVENT EV_click4_hold`
* 3H from lock for turbo on multichannel lights

# Build-time configuration

## Building a custom image

Get your light's default firmware and locate the correct header file, as this contains important hardware-specific config. Make a copy of it, and modify the following variables to your preference. These settings will persist across a factory reset (making it much more convenient to build an image once, then if your settings ever get messed up, you can factory reset to go back to *your* settings. Most of these are fairly self-explanatory. Note that the first half *SHOULD* work in stock unmodified anduril too, but this has not been tested by me personally. See above for build-time settings added by mods.

## Complete configuration reference
<details>
  <summary>This is probably out of date. It may well still be useful but really needs going through...</summary>
### Stock compatible config

**This is probably out of date as I haven't gone through it for multichannel yet. Most of it probably still works but some may not.**

```
//#define SIMPLE_UI_ACTIVE 0    // disable simple UI by default/from factory reset

//#define SIMPLE_UI_FLOOR 10    // simple UI floor
//#define SIMPLE_UI_CEIL  100   // simple UI ceiling
//#define SIMPLE_UI_STEPS 5     // simple UI stepped ramp length
//#define USE_SIMPLE_UI_RAMPING_TOGGLE //enable ramp style switch in Simple UI

//#define RAMP_SMOOTH_FLOOR   1   // smooth ramp floor
//#define RAMP_SMOOTH_CEIL    130 // smooth ramp ceiling
//#define RAMP_DISCRETE_FLOOR 1   // smooth ramp floor
//#define RAMP_DISCRETE_CEIL   130 // stepped ramp ceiling
//#define RAMP_DISCRETE_STEPS 10  // stepped ramp length

// enable voltage readout via aux/switch when on (see also RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF and RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW for modded versions)
//#define USE_AUX_RGB_LEDS_WHILE_ON
// disable voltage readout via aux when on
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
// NOTE: on from lockout is more complicated since there is no way to directly configure it. See `MOMENTARY_WHEN_LOCKED_DELAY` in next section.

//#define DEFAULT_2C_STYLE 1  // 0: no turbo. 1: 2C always turbo. 2: 2C goes to top of ramp, or turbo if already at top
//#define DEFAULT_2C_STYLE_SIMPLE 2  // same but for Simple UI.

//#define USE_TACTICAL_MODE //enable tactical mode. See also TACTICAL_MODE_CLICK_EVENT
//#define TACTICAL_LEVELS 150,(RAMP_SIZE+2),100 //set default tactical levels (max+1 = party strobe, max+2 = tactical strobe, etc...)

//#undef USE_THERM_AUTOCALIBRATE //disable automatic thermal calibration on reset/first boot. Set this if you are going to calibrate your MCU's temperature directly and don't want anduril to change it.

//#define RGB_LED_OFF_DEFAULT 0x27 //high, disco
//#define RGB_LED_LOCKOUT_DEFAULT 0x18 //low, rainbow
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
//TODO: how is temperature set? this table works for both stock and modded AFAIK... :thonk: too much bit twiddling for one day.

//voltage calibration
//this 7 by default, value added to the measured voltage (e.g. 5 is 0.25V, 6 is 0.3V, 7 is 0.35V) before the
//user's calibration setting from 7H from battcheck if any. By changing this, if you know your light's MCU is off by a bit this will allow calibration
//to persist through reflashes and factory resets
//#define VOLTAGE_PRECALIBRATION 7

//sets indicator LED mode, for non-RGB aux
//
//unmodded:
//1: low, 2: high, 3: blinking (if TICK_DURING_STANDBY is set)
//Format: ((lockout_mode <<2) + off_mode))
//
//modded:
//0: off 1: low 2: high
//if TICK_DURING_STANDBY is set, 3: blinking 4: blinking low, 5: blinking high 6: breathing
//Format: ((lockout_mode <<4) + off_mode)
//e.g. for lockout low, off high:
//#define INDICATOR_LED_DEFAULT_MODE ((1<<4) + 2)
```
### Modded-only config

TODO: redo this with multichannel.

For now, check out my main development config: [cfg-siterelenby-emisar-2ch-aux](spaghetti-monster/cfg-siterelenby-emisar-2ch-aux.h), [my button mappings](spaghetti-monster/anduril/mod-config-siterelenby.h), and [stock-compatible mappings](spaghetti-monster/anduril/mod-config-defaults.h)
</details>

## Example mod configs and prebuilt modded versions
### Example configurations

TODO: more detail on making your own config?

A few mod configs to serve as examples as well as let people try out some modded features without needing to build their own config from scratch

* [spaghetti-monster/anduril/mod-config-aux-while-on.h](spaghetti-monster/anduril/mod-config-aux-while-on.h)
  * Uses BLINK_LOCK_REMINDER (with red aux if aux are RGB)
  * Fully configurable RGB voltage while on (8C to switch on/off, all three aux voltage options enabled (see [config menus](#config-menus)
  * Fully configurable post-off voltage (configurable brightness)
  * 3H turbo from lockout mode
* [spaghetti-monster/anduril/mod-config-aux-while-on-4c-prev.h](spaghetti-monster/anduril/mod-config-aux-while-on-4c-prev.h)
  * Uses BLINK_LOCK_REMINDER (with red aux if aux are RGB)
  * Fully configurable RGB voltage while on (8C to switch on/off, all three aux voltage options enabled (see [config menus](#config-menus)
  * Fully configurable post-off voltage (configurable brightness)
  * 3H turbo from lockout mode
  * 4C ramp -> lockout removed and replaced with 4C previous channel
* [spaghetti-monster/anduril/mod-config-siterelenby.h](spaghetti-monster/anduril/mod-config-siterelenby.h) - my personal mod config, changes relatively often as this fork is developed and upstream changes, but is a good example of how complex things can get

### Building your own modded version

The easiest way is to create a mod-config file (see examples above) and pass that to the builder.

One shortcut that can be taken is if you want all the default button mappings, in your mod-config, you can use

```
#include "mod-config-defaults.h"
```
This will load a set of stock-compatible button mappings (that can still be remapped afterwards).

To load mod-config files, the default build scripts have been modified:

[`spaghetti-monster/anduril/build-all.sh`](spaghetti-monster/anduril/build-all.sh) modified to take extra environment variables:
* `EXACT_BUILD_TARGET`: Disables globbing, e.g. calling `EXACT_BUILD_TARGET=1 build-all.sh emisar-2ch` will **only** build `emisar-2ch` and not other targets with a matching name (e.g. `emisar-2ch-fet`).
* `MOD_CFG_H`: An additional config file to load, intended for configuration of mods. This is loaded after the build target config (e.g. `cfg-emisar-2ch.h`) but before any core anduril/FSM code is loaded, so it is safe to enable/disable features here.

`build.sh` (in the root of the repo) is a simple script to make it easier to build using Docker. This script supports passing through the environment vars mentioned above. In addition, it makes an attempt to handle different OS environments, and also passes the current git commit hash to the Docker builder. e.g. `EXACT_BUILD_TARGET=1 MOD_CFG_H="mod-config-aux-while-on.h" ./build.sh emisar-2ch`

Alternatively, you can create a variant build target with a customised `cfg.h`. The easiest way to do that is to `#include` the base config for the light you are building for, then apply your customisations in the file after the include. A simple example, if you just wanted `emisar-2ch` but not starting in simple UI, would be:
```
#include "cfg-emisar-2ch.h"
#undef SIMPLE_UI_ACTIVE
#define SIMPLE_UI_ACTIVE 0
```

You can change most things this way, and can also include your mod config here instead of using `MOD_CFG_H` (make sure you do this **AFTER** including the base cfg.h...). This allows you to override elements of your mod config for specific lights. For examples, see `spaghetti-monster/anduril/cfg-siterelenby-*.h`. One example below:

<details>
  <summary>example custom build target loading a mod-config and applying further customisations</summary>

Example:

```
// include the base hwdef
#include "cfg-emisar-2ch.h"

// load default button mappings
#include mod-config-defaults.h

//make 4C previous channel instead of ramp -> lock
#undef LOCK_FROM_ON_EVENT
#define EVENT_PREVIOUS_CHANNEL EV_4clicks
```

</details>

At some point I might add support for a git submodule to load different popular user configs.

# Roadmap
* (Configurable?) optional time limit for momentary turbo mode from lock (just in case something wedges the button held)
* In progress: Make modifications and features user-configurable and modular
  * Modularise starryalley mods
    * Integrate startup modes? should be easy to make into a build time option
    * Integrate [6H aux control](https://github.com/starryalley/Anduril2#allow-the-use-of-auxindicator-led-in-lower-levels--default_level-level-6c6h-while-light-is-on) and voltage aux while on (as a mode under 6H functionality? would need to allow aux use at any ramp level. Need to wait for that fork to implement voltage mode there first or it's going to become a massive pain to merge and rebase on changes)
    * Incorporate more changes from [SammysHP](https://github.com/SammysHP/flashlight-firmware/wiki/Modifications-Overview)
 * `LOCKOUT_3H_ACTION` - configurable between momentary turbo and channel switching for dual channel lights
 * Make aux colour for blinking numbers configurable at runtime (9C menu item after which to use? No easy way to display which is being selected to the user. Adding a completely new button combination is easy but takes more MCU space. Or is just having the order be the s
amme as the aux colour selector for off/lock mode enough?)
 * Find something useful for 3C on single channel (jump to 50%? or user-definable level? back to memory?)
* `MOMENTARY_TURBO_FROM_LOCK_TIME_LIMIT` - limit momentary turbo from lock to this many seconds as an alternative to disabling it completely
* Using `memorized_level` for the low battery warning isn't ideal as some stuff doesn't write to that and is still high enough to cause voltage drop (e.g. momentary turbo mode)
* Option to save channel mix separately to level for manual memory
* Make beacon on time configuration faster betweeen blinks?
* Use something other than `memorized_level` for low battery warning as that doesn't catch every case where the light might encounter significant voltage drop, and probably also has false negatives sometimes.
* New aux modes
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?

# General disclaimer

I am not responsible if you brick or otherwise break your light for any reason (bad flash, wrong firmware, mods did something unexpected, etc.). In general, I always test my changes myself on at least one light but I don't keep all of mine up to date with every commit or even every relevant one.

# Builds and release

Release schedule is "whenever I feel it justifies one". I will build images for my lights for each release. These should be reasonably stable and tested as they are the lights I am thinking of when I hack on this.

In addition, all the supported default build targets will be built. These *should* use default anduril mappings with the features defined in `config-default.h`. Do not assume these builds are stable or bug-free, they are mostly provided for people to try it out. In the future I may make a repo for other people's configs to automate new firmware builds for to lower the knowledge demand of building this fork.

# Other stuff

Stuff that doesn't fit anywhere else

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

Also on Docker Hub: https://hub.docker.com/r/siterelenby/anduril-builder. Supported architectures are amd64, armv7, and arm64.

`docker pull siterelenby/anduril-builder:latest`

### Changes
* Fix bug (full path creation causes issues on some of my boxen when trying to mount a filesystem with subdirs, and is in general useless)
* Added a proper entrypoint script
  * Checks for the source directory being mounted at different paths under `/src`
  * Return non-zero on build failure (useful for CI/CD pipelines etc.)

## Scripts

* `build.sh`: Build anduril. With no args, will build all possible targets (equivalent to running `build-all.sh` but handles running the docker image transparently. For Linux/MacOS/WSL2/Cygwin (please tell me if it works on anything else if you try it ;))
* `preprocess_debug.sh` - runs gcc's preprocessor, creating the actual source file (with includes, ifdefs, etc. all handled) that is actually fed to the compiler. Useful for debugging ifdefs and similar. Usage example: `TARGET=cfg-wurkkos-ts10.h MCU=attiny1616 bash -x preprocess_debug.sh`
* `build-docker-image.sh`: build a local copy of the `anduril-buildenv-docker` image

Example build scripts and header files for my lights (`build-siterelenby-*` and `spaghetti-monster/anduril/cfg-siterelenby*.h`) including a few extra default settings vs the default model header files.

Build scripts and image should work fine with the default codebase as well (in the future these may move to a submodule)
