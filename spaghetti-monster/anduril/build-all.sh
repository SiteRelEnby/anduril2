#!/bin/sh

for TARGET in \
  BLF_GT \
  BLF_Q8 \
  EMISAR_D4 \
  EMISAR_D4S \
  FW3A \
  ; do
  echo "===== $TARGET ====="
  ../../../bin/build-85.sh anduril "-DFSM_${TARGET}_DRIVER"
  mv -f anduril.hex anduril.$TARGET.hex
done
