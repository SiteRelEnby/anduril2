# anduril2

Anduril2 originally by [ToyKeeper](https://code.launchpad.net/~toykeeper/flashlight-firmware/anduril2), mods by @SiteRelEnby.

Also includes a script (`make-git-repo.sh`) to create a clean version of the upstream anduril2 repo, and a few more useful build utilities. Dependencies are git, bzr, and normal shell utilities, and [anduril-buildenv-docker](https://github.com/SiteRelEnby/anduril-buildenv-docker) included as a submodule. Note that to build the builder you will need buildkit as well as base Docker - I will probably put it on Docker Hub at some point too if I remember to.

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

(TODO)

## Roadmap

* Single channel compatibility
* New aux modes
* New, possibly-optional mode shortcuts
* Move momentary mode somewhere else and make it harder to accidentally activate
* Additional configuration options
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default?
