# for gchart's UPDI adapter
avrdude -p attiny1616 -c serialupdi -Uflash:v:${1} || exit 1
