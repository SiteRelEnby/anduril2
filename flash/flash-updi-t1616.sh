# for gchart's UPDI adapter
avrdude -p attiny1616 -c serialupdi -Uflash:w:${1} || exit 1
