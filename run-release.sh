#! /usr/bin/env bash

# This is a script I use to automate building hex files for releases. Can probably be adapted for other uses.

cleanup(){
	rm spaghetti-monster/anduril/*.hex
}
build_images(){
	docker run --rm -v $(pwd -P):/src -e COMMITHASH="$(git rev-parse --short HEAD)" -t anduril-builder:latest
}

#Build default targets
build_images
tar -vczf default-build-targets.tar.gz spaghetti-monster/anduril/*.hex
zip default-build-targets.zip spaghetti-monster/anduril/*.hex
cleanup

# Generate preconfigured builds:
# basic-new-features-only:
for cfgfile in $(ls spaghetti-monster/anduril/cfg-*.h | grep -v -e default -e example -e siterelenby)
do
	cfgname=$(basename ${cfgfile} | sed -e 's/^cfg-//' -e 's/\.h//')
	cat ${cfgfile} > spaghetti-monster/anduril/cfg-ci-${cfgname}-basic-new-features-only.h
	cat spaghetti-monster/anduril/config-example-basic-new-features-only.h >> spaghetti-monster/anduril/cfg-ci-${cfgname}-basic-new-features-only.h

	build_images
	tar -vczf basic-new-features-only.tar.gz $(ls spaghetti-monster/anduril/*.hex | grep basic-new-features-only)
	zip basic-new-features-only.zip $(ls spaghetti-monster/anduril/*.hex | grep basic-new-features-only)
	cleanup
done

# dual-channel-features:
# This one only makes sense for dual channel lights. Unfortunately these are defined various ways, including inheritance, and some in the filename and some not, so hardcoding a list:
for cfgfile in "spaghetti-monster/anduril/cfg-blf-lantern-t1616.h
spaghetti-monster/anduril/cfg-blf-lantern-t1616.h
spaghetti-monster/anduril/cfg-emisar-d4sv2-tintramp-fet.h
spaghetti-monster/anduril/cfg-emisar-d4sv2-tintramp.h
spaghetti-monster/anduril/cfg-noctigon-k9.3-tintramp-219.h
spaghetti-monster/anduril/cfg-noctigon-k9.3-tintramp-fet.h
spaghetti-monster/anduril/cfg-noctigon-k9.3-tintramp-nofet.h
spaghetti-monster/anduril/cfg-noctigon-k9.3.h
spaghetti-monster/anduril/cfg-noctigon-kr4-tintramp.h
spaghetti-monster/anduril/cfg-siterelenby-emisar-d2-tintramp.h
spaghetti-monster/anduril/cfg-siterelenby-emisar-d4sv2-tintramp-fet.h
spaghetti-monster/anduril/cfg-siterelenby-noctigon-dm112-tintramp-fet.h"
do
	cfgname=$(basename ${cfgfile} | sed -e 's/^cfg-//' -e 's/\.h//')
	cat ${cfgfile} > spaghetti-monster/anduril/cfg-ci-${cfgname}-basic-new-features-only.h
	cat spaghetti-monster/anduril/config-example-dual-channel-features.h >> spaghetti-monster/anduril/cfg-ci-${cfgname}-dual-channel-features.h
	build_images
	tar -vczf dual-channel-features.tar.gz $(ls spaghetti-monster/anduril/*.hex | grep dual-channel-features)
	zip dual-channel-features.zip $(ls spaghetti-monster/anduril/*.hex | grep dual-channel-features)
	cleanup
done

