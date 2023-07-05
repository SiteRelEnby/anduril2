avrdude -p t1634 -c usbasp -u -Uflash:w:${1} || exit 1
