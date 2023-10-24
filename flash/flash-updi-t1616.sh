#! /usr/bin/env bash
# for gchart's UPDI adapter
[[ -z "${PORT}" ]] && PORT="com5" #COM port will vary, this is just my default on my main box I use for development. TODO: *nix versions of these
avrdude -p attiny1616 -c serialupdi -P ${PORT} -Uflash:w:${1}
if [[ "${?}" != "0" ]]
then
	echo "avrdude failed. Make sure you have the right COM port (tried ${PORT}). # PORT=com8 ./${0} <input file>" >&2
	exit 1
fi
