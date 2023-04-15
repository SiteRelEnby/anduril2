#!/bin/sh

# Usage: build-all.sh [pattern]
# If pattern given, only build targets which match.

if [ ! -z "$1" ]; then
  SEARCH="$1"
fi

UI=anduril

date '+#define VERSION_NUMBER "%Y%m%d"' > version.h

PASS=0
FAIL=0
PASSED=''
FAILED=''

for TARGET in cfg-*.h ; do

  # maybe limit builds to a specific pattern
  if [ ! -z "$SEARCH" ]; then
    echo "$TARGET" | grep -i "$SEARCH" > /dev/null
    if [ 0 != $? ]; then continue ; fi
  fi

  # friendly name for this build
  NAME=$(echo "$TARGET" | perl -ne '/cfg-(.*).h/ && print "$1\n";')
  echo "===== $NAME ====="

  # figure out MCU type
  ATTINY=$(grep 'ATTINY:' $TARGET | awk '{ print $3 }')
  if [ -z "$ATTINY" ]; then ATTINY=85 ; fi

  # try to compile
  echo ../../bin/build.sh $ATTINY "$UI" "-DCONFIGFILE=${TARGET}"
  ../../bin/build.sh $ATTINY "$UI" "-DCONFIGFILE=${TARGET}"

  # track result, and rename compiled files
  if [ 0 = $? ] ; then
    if [ -z "${COMMITHASH}" ]
    then
      mv -f "$UI".hex "$UI".$NAME.hex
    else
      mv -f "$UI".hex "$UI".$NAME.${COMMITHASH}.hex
    fi
    PASS=$(($PASS + 1))
    PASSED="$PASSED $NAME"
  else
    echo "ERROR: build failed"
    FAIL=$(($FAIL + 1))
    FAILED="$FAILED $NAME"
  fi

done

# summary
echo "===== $PASS builds succeeded, $FAIL failed ====="
#echo "PASS: $PASSED"
exitcode=0
if [ 0 != $FAIL ]; then
  echo "FAIL:$FAILED"
  if [ 0 != $PASS ]; then
    #at least some builds passed, but not all
    exitcode=1
  else
    #everything failed
    exitcode=2
  fi
fi
exit $exitcode
