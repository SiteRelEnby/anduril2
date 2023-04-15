#! /usr/bin/env bash

# This is a script I use to automate building hex files for releases. Can probably be adapted for other uses.

docker run --rm -v $(pwd -P):/src -e COMMITHASH="$(git rev-parse --short HEAD)" -t anduril-builder:latest
retval=${?}

echo 'These are the default build targets that use attiny1634. They have not been tested by me (as the saying goes, "Hey, it compiles! Ship it!"), and are provided in the hope they may be useful to someone.' > README.txt
tar -vczf default-build-targets.tar.gz README.txt *.hex
zip default-build-targets.zip README.txt *.hex

exit ${retval}
