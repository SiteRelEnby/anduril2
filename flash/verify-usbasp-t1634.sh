avrdude -p t1634 -c usbasp -Uflash:v:${1} || exit 1
