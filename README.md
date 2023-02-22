# anduril2

Anduril2 originally by [ToyKeeper](https://code.launchpad.net/~toykeeper/flashlight-firmware/anduril2), mods by @SiteRelEnby.

Also includes a script (`make-git-repo.sh`) to create a clean version of the upstream anduril2 repo, and a few more useful build utilities. Dependencies are git, bzr, and normal shell utilities, and [anduril-buildenv-docker](https://github.com/SiteRelEnby/anduril-buildenv-docker) included as a submodule. Note that to build the builder you will need buildkit as well as base Docker - I will probably put it on Docker Hub at some point too if I remember to.

# Current upstream release based on

10/02/2023

# Changes from upstream

* 2C now always goes to level 130 (single channel on maximum); 3C goes to 200%
* 8H to use the *opposite* channel switching mode (e.g. if 3C is configured for instant switching, 8H will ramp between channels)
* 4H for momentary opposite channel
  * At the moment this will invert the ramp, e.g. if you are at a 25/75% mix between the two channels it will flip to 75/25. I may make this behaviour configurable in the future with other options.
* Option to make the light start in instant switching mode by default via header file (currently kind of a kludge as it needs a rebuild to change)
* Shortcuts to turbo modes for each channel on dual-channel lights (5C/6C)
  * Note that this fw has so far not been tested on single channel lights and will probably do weird things on them.
* Momentary turbo modes for each channel (5H/6H)
* An option (in the header file for now) to switch which of the two channels is considered the first (5C/H) (might move this to the 9H menu later)
* Several less used options have been moved
  * Aux config moved to 8C/8H to make it harder to accidentally hit from 6C/H
  * Ramp style selection moved to 9C (does anyone reqlly change ramps that often?...)
  * Momentary mode moved to 12C (may move again in the future)
  * Sunset timer moved to 12H
* Use a less bzr/bizarre VCS
* Remove reference to bad childrens' fantasy novels by a terrible person. Please read another book.

## UI reference
Right now this fork has only been tested by me on dual channel lights (D4S and DM1.12). Single channel support may be coming soon; at the moment some behaviour may be undefined and there isn't a compelling reason to run this fork on single channel lights (yet...).

|Input|Dual channel modded|Dual channel stock|
|-----|-----------------|------------------|
|     | OFF MODE        |OFF MODE |
|1C|  On (memory) |On (memory) |
|1H|  Moon | Moon |
|2C|  On (ceiling) | On (ceiling) |
|2H|  Momentary 200% turbo | Momentary turbo (based on ramp config) |
|3C|  Blinky modes | Blinky modes |
|4C|  Lock | Lock |
|4H|  (nothing) (TODO: momentary opposite channel?) | (nothing) |
|5C|  ch1 turbo | momentary mode |
|5H|  Momentary ch1 turbo | (nothing) |
|6C|  ch2 turbo | (nothing) |
|6H|  momentary ch2 turbo| (nothing) |
|7C|  (nothing) | cycle aux brightness |
|7H|  (nothing) | cycle aux modes |
|8C|  cycle aux brightness | (nothing) |
|8H|  cycle aux modes | (nothing) |
|9H|  globals config | globals config |
|10H| Simple UI config | simple UI config |
|12C| Momentary mode (TODO: move to 12H??) | (nothing) |
|13H| factory reset | factory reset |
|15C| version check | version check|
|  |  LOCK MODE| LOCK MODE |
|1H|  momentary moon | momentary moon|
|2H|  momentary floor/memory | momentary floor/memory |
|3H|  channel switch (default) | channel switch |
|4C|  Unlock to memory | unlock to memory |
|4H|  unlock to floor | unlock to floor |
|5C|  unlock to ch1 turbo |unlock to turbo |
|5H|  momentary ch1 turbo | moon (ignored) |
|6C|  unlock to ch2 turbo | moon (ignored) |
|6H|  momentary ch2 turbo | moon (ignored) |
|7C|  (nothing) | cycle aux brightness |
|7H|  (nothing) | cycle aux mode |
|8C|  cycle aux brightness | (nothing) |
|8H|  cycle aux mode | (nothing) |
|10H| autolock config | autolock config|
|  |  RAMP MODE| RAMP MODE |
|1C|  off | off |
|1H|  ramp up | ramp up |
|2C|  single channel turbo | turbo |
|2H|  ramp down | ramp down |
|3C|  200% turbo | ramp style toggle |
|3H|  channel switch (default) | channel switch |
|4C|  off and lock | off and lock |
|4H|  momentary channel switch | (nothing) |
|5C|  ch1 turbo | momentary mode |
|5H|  momentary ch1 turbo| sunset mode |
|6C|  ch2 turbo | (nothing) |
|6H|  momentary ch2 turbo | (nothing) |
|7H|  ramp config menu | ramp config menu |
|8H|  channel switch (opposite) |(nothing) |
|9C|  ramp style toggle | (nothing) |
|10C| save memory | save memory |
|10H| ramp extras config | ramp extras config |
|12C| momentary mode | (nothing) |
|12H| sunset mode | (nothing) |

## Roadmap

* Single channel compatibility
* Option (possibly in light-specific header file) to change which channel is considered channel 1 (as it stands the same value ended up bring right for both of my lights but this obviously depends on the specific light)
* New aux modes
* New, possibly-optional mode shortcuts
* Move momentary mode somewhere else and make it harder to accidentally activate
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?
