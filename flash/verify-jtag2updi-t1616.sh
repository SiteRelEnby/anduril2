#for some rewireable UPDI adapters used for e.g. Sofirn Q8
avrdude -p attiny1616 -c jtag2updi -Uflash:v:${1} || exit 1
