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
A fork of [anduril-buildenv-docker](https://github.com/SiteRelEnby/anduril-buildenv-docker) with a bug fixed.
Included as a submodule, to use it, run `git submodule update --init`. Note that to build the builder you will need a working [buildkit](https://docs.docker.com/build/buildkit) as well as base Docker - I will probably put it on Docker Hub at some point too if I remember to. Feel free to remind me to if you really need it built for you.

Example build scripts and header files for my lights (`build-siterelenby-*` and `./ToyKeeper/spaghetti-monster/anduril/cfg-siterelenby*.h`) including a few extra default settings vs the default model header files.

# Current upstream version this mod is based on

10/02/2023

# Changes from upstream

The goal is to keep reasonable commonality with base anduril, e.g. 7H, 9H, and 10H config menus stay in the same place; only things most people don't use that much like momentary and sunset modes or ramp style toggle should be moved. In general, avoiding removing functionality completely, just making stuff that gets in the way less easy to accidentally hit, and ideally adding some modularity for the user to decide which changes to include. Right now most changes are not modular.

## All lights

* Several less used options have been moved
  * Aux config moved to 8C/8H to make it harder to accidentally hit when trying to do 6C/H
    * TODO: Make this configurable at build-time? Since it might make more sense to keep aux on 7C for single channel lights.
  * Ramp style selection moved to 8C (does anyone really change ramps that often?...)
  * Momentary mode moved to 12C (may move again in the future)
  * Sunset timer moved to 12H
* Build-time configuration for some additional stuff (in its own section)
  * Using aux LEDs to display the battery voltage while the light is on. This is by default only enabled for lights with an RGB button but no RGB aux (e.g. K1), but can be enabled for any light by setting `USE_AUX_RGB_LEDS_WHILE_ON`. For lights with forward facing aux, added `RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF` and `RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW` to customise when the voltage is displayed, so if this causes a problem it can be disabled at low ramp levels.
* Use a less bzr/bizarre VCS
* Remove reference to bad childrens' fantasy novels by a terrible person. Please [read another book](https://knowyourmeme.com/memes/read-another-book).

## Dual channel lights only
* 2C now always goes to level 130 (single channel on maximum); 3C goes to 200%
* 4H for momentary opposite channel
  * At the moment this will invert the ramp, e.g. if you are at a 25/75% mix between the two channels it will flip to 75/25. I may make this behaviour configurable in the future with other options.
* 8H to use the *opposite* channel switching mode (e.g. if 3C is configured for instant switching, 8H will ramp between channels)
* Option to make the light start in instant switching mode by default via header file (currently kind of a kludge as it needs a rebuild to change - although fixing that is low priority as I just pick a channel and stick with it)
* Shortcuts to turbo modes for each channel (5C/6C)
* Momentary turbo modes for each channel (5H/6H)
* An option (in the header file for now) to switch which of the two channels is considered the first for 5-6C/H (might move this to the 9H menu later

# Build-time configuration

Some of the changes in this firmware are only configurable at build-time. Additional parameters for cfg header files added:
* `#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30`: Sets the threshold at which to switch the voltage RGB aux off
* `#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50`: Sets the threshold at which to switch the voltage RGB aux to low mode
* `#define USE_OPPOSITE_TINTRAMP_KLUDGE`: When defined, makes the light start in channel switching mode. A very inelegant solution but it works so not being redone for now. May be replaced with a better way in the future.

## Building a custom image

Get your light's default firmware and locate the header file. Make a copy of it, and modify the following variables to your preference. These settings will persist across a factory reset.

```
//disable simple UI by default
//#undef SIMPLE_UI_ACTIVE

//#define SIMPLE_UI_FLOOR       // simple UI floor
//#define SIMPLE_UI_CEIL  100   // simple UI ceiling
//#define SIMPLE_UI_STEPS 5     // simple UI stepped ramp length

//#define RAMP_SMOOTH_FLOOR   1   // smooth ramp floor
//#define RAMP_SMOOTH_CEIL    130 // smooth ramp ceiling
//#define RAMP_DISCRETE_FLOOR 1   // smooth ramp floor
//define RAMP_DISCRETE_CEIL   130 // stepped ramp ceiling
//#define RAMP_DISCRETE_STEPS 10  // stepped ramp length

//#define USE_AUX_RGB_LEDS_WHILE_ON //enable voltage readout via aux when on
//#undef USE_AUX_RGB_LEDS_WHILE_ON  //disable voltage readout via aux when on

//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_OFF 30 //at or below here, aux off while on
//#define RGB_VOLTAGE_WHILE_ON_THRESHOLD_LOW 50 //at or below here, aux low while on

//#define RAMP_STYLE 0 //0 is smooth, 1 is stepped

//#define DEFAULT_MANUAL_MEMORY 50       //ramp level (1-150)
//#define DEFAULT_MANUAL_MEMORY_TIMER 60 //minutes

//#define DEFAULT_AUTOLOCK_TIME 60       //minutes


```

# UI reference
Single channel lights should be working but are currently relatively low on additional features.

|Input|Dual channel modded|Dual channel stock|Single channel modded|Single channel stock|
|-----|-----------------|------------------|------------|-------------------------------|
|     | OFF MODE        |OFF MODE |OFF MODE |OFF MODE |
|1C|  On (memory) |On (memory) | On (memory) | On (memory)
|1H|  Moon | Moon | Moon | Moon |
|2C|  On (ceiling) | On (ceiling) | On (ceiling) | On (ceiling)
|2H|  Momentary 200% turbo | Momentary configured turbo | Momentary turbo | Momentary turbo |
|3C|  Blinky modes | Blinky modes | Blinky modes | Blinky modes |
|4C|  Lock | Lock | Lock | Lock |
|4H|  (nothing) | (nothing) | (nothing) | (nothing) |
|5C|  ch1 turbo | momentary mode | (nothing) | momentary mode |
|5H|  Momentary ch1 turbo | (nothing) | (nothing) | (nothing) |
|6C|  ch2 turbo | (nothing) | (nothing) | (nothing) |
|6H|  momentary ch2 turbo| (nothing) | (nothing) | (nothing) |
|7C|  (nothing) | aux brightness | (nothing) |aux brightness |
|7H|  (nothing) | aux mode | (nothing) | aux mode |
|8C|  aux brightness | (nothing) | aux brightness | (nothing) |
|8H|  aux modes | (nothing) | aux modes | (nothing) |
|9H|  globals config | globals config | globals config | globals config |
|10H| Simple UI config | simple UI config | simple UI config | simple UI config |
|12C| Momentary mode | (nothing) |  Momentary mode | (nothing) |
|13H| factory reset | factory reset | factory reset | factory reset |
|15C| version check | version check| version check | version check |
|  |  LOCK MODE| LOCK MODE | LOCK MODE | LOCK MODE |
|1H|  momentary moon | momentary moon|momentary moon|momentary moon|
|2H|  momentary floor/mem| momentary floor/mem| momentary floor/mem | momentary floor/mem
|3H|  channel switch (default) | channel switch | moon (ignored) | moon (ignored) |
|4C|  Unlock to memory | unlock to memory | unlock to mem | unlock to mem |
|4H|  unlock to floor | unlock to floor | unlock to floor | unlock to floor |
|5C|  unlock to ch1 turbo |unlock to turbo | unlock to turbo | unlock to turbo | 
|5H|  momentary ch1 turbo | moon (ignored) | moon (ignored) |  moon (ignored) |
|6C|  unlock to ch2 turbo | moon (ignored) | moon (ignored) | moon (ignored) |
|6H|  momentary ch2 turbo | moon (ignored) | moon (ignored) | moon (ignored) |
|7C|  (nothing) | aux brightness | (nothing) | aux brightness |
|7H|  (nothing) | aux mode | (nothing) | aux mode |
|8C|  aux brightness | (nothing) | aux brightness | (nothing) |
|8H|  aux mode | (nothing) | aux mode | (nothing) |
|10H| autolock config | autolock config| autolock config | autolock config |
|  |  RAMP MODE| RAMP MODE | RAMP MODE |RAMP MODE |
|1C|  off | off | off |off |
|1H|  ramp up | ramp up | ramp up | ramp up |
|2C|  single channel turbo | turbo | turbo | turbo |
|2H|  ramp down | ramp down | ramp down | ramp down |
|3C|  200% turbo | ramp style toggle | (nothing (TODO)) | ramp style |
|3H|  channel switch (default) | channel switch | momentary turbo | momentary turbo |
|4C|  off and lock | off and lock | off and lock | off and lock |
|4H|  momentary channel switch | (nothing) | (nothing) | (nothing)
|5C|  ch1 turbo | momentary mode | (nothing) | momentary mode | 
|5H|  momentary ch1 turbo| sunset mode | (nothing) | sunset mode | 
|6C|  ch2 turbo | (nothing) | (nothing) | (nothing) |
|6H|  momentary ch2 turbo | (nothing) | (nothing) | (nothing) |
|7H|  ramp config | ramp config | ramp config | ramp config
|8C|  ramp style toggle | (nothing) | ramp toggle | (nothing) |
|8H|  channel switch (opposite) |(nothing) |( nothing) | (nothing) |
|10C| save memory | save memory | save mem | save mem
|10H| ramp extras config | ramp extras config | ramp extras | ramp extras |
|12C| momentary mode | (nothing) | momentary mode | (nothing) | 
|12H| sunset mode | (nothing) | sunset mode | (nothing) |

## Roadmap

* TODO: momentary opposite channel from 4H in off mode?
* Find something useful for 3C on single channel
* Option (possibly in light-specific header file) to change which channel is considered channel 1 (as it stands the same value ended up being right for both of my lights but this obviously depends on the specific light)
* Possibly move momentary opposite channel to a higher button combo and the turbo shortcuts down (after some use of this fw, have discovered I use those more than momentary opposite at current ramp level)
* New aux modes
* New, possibly-optional mode shortcuts
* Move momentary mode somewhere else and make it harder to accidentally activate
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?
