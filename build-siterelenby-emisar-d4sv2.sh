#! /usr/bin/env bash
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
docker run --rm -v ${SCRIPTPATH}:/src -e COMMITHASH="$(git rev-parse --short HEAD)" -t anduril-builder:latest siterelenby-emisar-d4sv2-tintramp-fet
# For running from a subdir:
# SCRIPTPATH was set above so it's known-good
#BUILDPATH="$(cd ${SCRIPTPATH} && cd .. && pwd -P )"
#docker run --rm -v ${BUILDPATH}:/src -e COMMITHASH="$(git rev-parse --short HEAD)" -i -t anduril-builder:latest siterelenby-emisar-d4sv2-tintramp-fet
