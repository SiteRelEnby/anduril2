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

## All lights

* Several less used options have been moved
  * Aux config moved to 8C/8H to make it harder to accidentally hit from 6C/H
  * Ramp style selection moved to 9C (does anyone reqlly change ramps that often?...)
  * Momentary mode moved to 12C (may move again in the future)
  * Sunset timer moved to 12H
* Use a less bzr/bizarre VCS
* Remove reference to bad childrens' fantasy novels by a terrible person. Please [read another book](https://knowyourmeme.com/memes/read-another-book).

## Dual channel lights only
* 2C now always goes to level 130 (single channel on maximum); 3C goes to 200%
* 8H to use the *opposite* channel switching mode (e.g. if 3C is configured for instant switching, 8H will ramp between channels)
* 4H for momentary opposite channel
  * At the moment this will invert the ramp, e.g. if you are at a 25/75% mix between the two channels it will flip to 75/25. I may make this behaviour configurable in the future with other options.
* Option to make the light start in instant switching mode by default via header file (currently kind of a kludge as it needs a rebuild to change)
* Shortcuts to turbo modes for each channel on dual-channel lights (5C/6C)
  * Note that this fw has so far not been tested on single channel lights and will probably do weird things on them.
* Momentary turbo modes for each channel (5H/6H)
* An option (in the header file for now) to switch which of the two channels is considered the first (5C/H) (might move this to the 9H menu later)

# UI reference
Right now this fork has only been tested by me on dual channel lights (D4S and DM1.12). Single channel support may be coming soon; at the moment some behaviour may be undefined and there isn't a compelling reason to run this fork on single channel lights (yet...).

|Input|Dual channel modded|Dual channel stock|Single channel modded
|-----|-----------------|------------------|------------|
|     | OFF MODE        |OFF MODE |OFF MODE |
|1C|  On (memory) |On (memory) | On (memory) |
|1H|  Moon | Moon | Moon |
|2C|  On (ceiling) | On (ceiling) | On (ceiling) |
|2H|  Momentary 200% turbo | Momentary configured turbo | Momentary turbo
|3C|  Blinky modes | Blinky modes | Blinky modes |
|4C|  Lock | Lock | Lock |
|4H|  (nothing) | (nothing) | (nothing) | 
|5C|  ch1 turbo | momentary mode | momentary mode | 
|5H|  Momentary ch1 turbo | (nothing) | (nothing) |
|6C|  ch2 turbo | (nothing) | (nothing) |
|6H|  momentary ch2 turbo| (nothing) | (nothing) |
|7C|  (nothing) | aux brightness | aux brightness |
|7H|  (nothing) | aux mode | aux brightness |
|8C|  aux brightness | (nothing) |
|8H|  aux modes | (nothing) | (nothing) |
|9H|  globals config | globals config | globals config |
|10H| Simple UI config | simple UI config | simple UI config |
|12C| Momentary mode (TODO: move to 12H??) | (nothing) | (nothing) |
|13H| factory reset | factory reset | factory reset
|15C| version check | version check| version check |
|  |  LOCK MODE| LOCK MODE | LOCK MODE |
|1H|  momentary moon | momentary moon|momentary moon|
|2H|  momentary floor/memory | momentary floor/memory | momentary floor/memory |
|3H|  channel switch (default) | channel switch | moon (ignored) |
|4C|  Unlock to memory | unlock to memory | unlock to mem |
|4H|  unlock to floor | unlock to floor | unlock to floor |
|5C|  unlock to ch1 turbo |unlock to turbo | unlock to turbo
|5H|  momentary ch1 turbo | moon (ignored) | moon (ignored) |
|6C|  unlock to ch2 turbo | moon (ignored) | moon (ignored) |
|6H|  momentary ch2 turbo | moon (ignored) | moon (ignored) |
|7C|  (nothing) | aux brightness | aux brightness |
|7H|  (nothing) | aux mode | aux mode |
|8C|  aux brightness | (nothing) | (nothing) |
|8H|  aux mode | (nothing) | (nothing) |
|10H| autolock config | autolock config| (nothing) |
|  |  RAMP MODE| RAMP MODE | RAMP MODE |
|1C|  off | off | off |
|1H|  ramp up | ramp up | ramp up |
|2C|  single channel turbo | turbo | turbo |
|2H|  ramp down | ramp down | ramp down |
|3C|  200% turbo | ramp style toggle | ramp style |
|3H|  channel switch (default) | channel switch | momentary turbo |
|4C|  off and lock | off and lock | off and lock |
|4H|  momentary channel switch | (nothing) | (nothing) |
|5C|  ch1 turbo | momentary mode | momentary mode |
|5H|  momentary ch1 turbo| sunset mode | sunset mode |
|6C|  ch2 turbo | (nothing) | (nothing) |
|6H|  momentary ch2 turbo | (nothing) | (nothing) |
|7H|  ramp config menu | ramp config menu | ramp config |
|8H|  channel switch (opposite) |(nothing) |( nothing) |
|9C|  ramp style toggle | (nothing) | (nothing) |
|10C| save memory | save memory | save mem |
|10H| ramp extras config | ramp extras config | ramp extras |
|12C| momentary mode | (nothing) | (nothing) |
|12H| sunset mode | (nothing) | (nothing) |

## Roadmap

* Single channel compatibility/reason-for-this-mod-to-exist
* TODO: momentary opposite channel from 4H in off mode?
* Option (possibly in light-specific header file) to change which channel is considered channel 1 (as it stands the same value ended up being right for both of my lights but this obviously depends on the specific light)
* Possibly move momentary opposite channel to a higher button combo and the turbo shortcuts down (after some use of this fw, have discovered I use those more than momentary opposite at current ramp level)
* New aux modes
* New, possibly-optional mode shortcuts
* Move momentary mode somewhere else and make it harder to accidentally activate
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?
