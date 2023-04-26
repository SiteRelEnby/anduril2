#! /usr/bin/env bash
usage(){
	echo "usage: TARGET=cfg-wurkkos-ts10.h MCU=attiny1616 preprocess_debug.sh"
	exit 1
}
if [[ -z "${TARGET}" ]] || [[ -z "${MCU}" ]]
then
	usage
fi

if [[ $(uname -a | grep -i cygwin) ]]
then
	#cygwin handles paths differently and needs converting. By default cygwin will use e.g. /cygdrive/c/foo, we need that to be //c/foo for Docker on Windows. There are two possibilities  here, we are in cygwin's fs, or in the mounted windows fs (/cygdrive).
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

ATTINY=$(sed 's/^attiny//' <<< "${MCU}")

docker run --rm -it -e TARGET="${TARGET}" -e MCU="${MCU}" -e ATTINY="${ATTINY}" --entrypoint=/bin/bash --rm -v ${SCRIPTPATH}:/src siterelenby/anduril-builder:latest -c "set -x ; set -e ; cd /src/spaghetti-monster/anduril || cd /src/ToyKeeper/spaghetti-monster/anduril ; avr-gcc -E -save-temps -v -DCONFIGFILE=${TARGET} -Wall -g -Os -mmcu=${MCU} -c -std=gnu99 -fgnu89-inline -fwhole-program -DATTINY=${ATTINY} -I.. -I../.. -I../../.. -fshort-enums -B /not/existing/gcc/dev/${MCU}/ -I /not/existing/include/ -c anduril.c 2>&1 > ${TARGET}_preprocessed.c ; sed '/^$/d' < ${TARGET}_preprocessed.c > ${TARGET}_preprocessed_clean.c"

