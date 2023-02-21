# anduril2

Anduril2 originally by [ToyKeeper](https://code.launchpad.net/~toykeeper/flashlight-firmware/anduril2), mods by @SiteRelEnby.

Also includes a script (`make-git-repo.sh`) to create a clean version of the upstream anduril2 repo, and a few more useful build utilities. Dependencies are git, bzr, and normal shell utilities, and [anduril-buildenv-docker](https://github.com/SiteRelEnby/anduril-buildenv-docker) included as a submodule.

## UI reference

Ri0ght now this fork has only been tested by me on dual channel lights (D4S and DM1.12). Single channel support may be coming soon; at the moment some behaviour may be undefined and there isn't a compelling reason to run this fork on single channel lights (yet...).

## Roadmap

* New aux modes
* A few new optional mode shortcuts I've had the idea of for a while
* Additional configuration
* Fix a few kludges
* Some kind of script to automatically make a custom build with the user's preferred config the factory reset default
