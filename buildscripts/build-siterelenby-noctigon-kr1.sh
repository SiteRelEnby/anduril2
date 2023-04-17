#! /usr/bin/env bash
set -e -o pipefail
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
# For running from root dir:
#docker run --rm -v ${SCRIPTPATH}:/src -e COMMITHASH="$(git rev-parse --short HEAD)" -t anduril-builder:latest siterelenby-noctigon-kr1-nofet
# For running from a subdir:
# SCRIPTPATH was set above so it's known-good
BUILDPATH="$(cd ${SCRIPTPATH} && cd .. && pwd -P )"
docker run --rm -v ${BUILDPATH}:/src -e COMMITHASH="$(git rev-parse --short HEAD)" -i anduril-builder:latest siterelenby-noctigon-kr1-nofet
