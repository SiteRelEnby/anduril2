avrdude -p t1634 -c usbasp -Uflash:w:${1} || exit 1
