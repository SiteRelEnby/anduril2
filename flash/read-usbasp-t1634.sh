#! /usr/bin/env bash

[[ -z "${1}" ]] && echo "usage: ${0} <output file>" >&2 && exit 1

avrdude -p t1634 -c usbasp -Uflash:r:${1} || exit 1
