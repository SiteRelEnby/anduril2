#! /usr/bin/env bash

set -e -o pipefail

if [[ -z `which docker` ]]
then
	echo -e "docker not installed. This script is mostly a convenience script to use the docker builder - to run a build locally, avr-gcc needs to be installed, then run spaghetti-monster/anduril/build-all.sh directly\nsee: https://github.com/SiteRelEnby/anduril2/issues/3\nFor more info on installing the build toolchain locally, see https://budgetlightforum.com/t/anduril-2/62656/328" >&2
	exit 1
fi

if [[ $(uname -a | grep -i cygwin) ]]
then
	#cygwin handles paths differently and needs converting. By default cygwin will use e.g. /cygdrive/c/foo, we need that to be //c/foo for Docker on Windows. There are two possibilities here, we are in cygwin's fs, or in the mounted windows fs (/cygdrive).
	SCRIPTPATH_CYGWIN="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
	if [[ "${SCRIPTPATH_CYGWIN}" =~ "^/cygdrive" ]]
	then
		SCRIPTPATH="$(sed 's|cygdrive||' <<< \"${SCRIPTPATH_CYGWIN}\")" #e.g. /cygdrive/c/users/foo -> //c/users/foo
	else
		CYGWIN_PATH=$(cygpath -m -w /)
		SCRIPTPATH="${CYGWIN_PATH}/${SCRIPTPATH_CYGWIN}"
	fi
else
	#case for linux/mac/WSL
	SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
fi

# For running from root dir:
docker run --rm -v ${SCRIPTPATH}:/src -e MOD_CFG_H="${MOD_CFG_H}" -e EXACT_BUILD_TARGET="${EXACT_BUILD_TARGET}" -e COMMITHASH="$(git rev-parse --short HEAD)" -t anduril-builder:latest ${*}
retval=$?
# For running from a subdir:
# SCRIPTPATH was set above so it's known-good
#BUILDPATH="$(cd ${SCRIPTPATH} && cd .. && pwd -P )"
#docker run --rm -v ${BUILDPATH}:/src -e COMMITHASH="$(git rev-parse --short HEAD)" -i -t anduril-builder:latest noctigon-k1-siterelenby

git checkout -- spaghetti-monster/anduril/version.h
exit ${retval}
