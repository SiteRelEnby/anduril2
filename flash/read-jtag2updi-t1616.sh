#! /usr/bin/env bash
#for some rewireable UPDI adapters used for e.g. Sofirn Q8

[[ -z "${1}" ]] && echo "usage: PORT=com6 ${0} <output file>" >&2 && exit 1

if [[ -z "${PORT}" ]]
then
        echo "Need a port. e.g.: $ PORT=COM6 ${0} <input file>" >&2
        exit 1
fi

avrdude -p attiny1616 -c jtag2updi -P ${PORT} -Uflash:r:${1} || exit 1

if [[ "${?}" != "0" ]]
then
	echo "avrdude failed. Make sure you have the right COM port (tried ${PORT}). # PORT=com8 ./${0} <output file>" >&2
	exit 1
fi
