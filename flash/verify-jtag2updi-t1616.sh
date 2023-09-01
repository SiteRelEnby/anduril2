#! /usr/bin/env bash
#for some rewireable UPDI adapters used for e.g. Sofirn Q8

if [[ -z "${PORT}" ]]
then
	echo "Need a port. e.g.: $ PORT=COM6 ${0}" >&2
	exit 1
fi
avrdude -p attiny1616 -c jtag2updi -P ${PORT} -Uflash:v:${1} || exit 1
