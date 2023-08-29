#!/bin/sh

# Usage: build-all.sh [pattern]
# If pattern given, only build targets which match.

# added by SiteRelEnby:
# MOD_CFG_H: mod config file to load
# EXACT_BUILD_TARGET: If set, don't glob target names

if [ ! -z "$1" ]; then
  SEARCH="$1"
fi

UI=anduril

date '+#define VERSION_NUMBER "%Y-%m-%d"' > version.h

PASS=0
FAIL=0
PASSED=''
FAILED=''

for TARGET in cfg-*.h ; do

  # maybe limit builds to a specific pattern
  if [ ! -z "$SEARCH" ]; then
    if [[ -z "${EXACT_BUILD_TARGET}" ]]
    then
      echo "$TARGET" | grep -i "$SEARCH" > /dev/null
    else
       echo "$TARGET" | grep -E -i "cfg-${SEARCH}.h$" > /dev/null
    fi
    if [ 0 != $? ]; then continue ; fi
  fi

  # friendly name for this build
  NAME=$(echo "$TARGET" | perl -ne '/cfg-(.*).h/ && print "$1\n";')
  echo "===== $NAME ====="

  # figure out MCU type
  ATTINY=$(grep 'ATTINY:' $TARGET | awk '{ print $3 }')
  if [ -z "$ATTINY" ]; then ATTINY=85 ; fi

  # try to compile
if [[ ! -z "${MOD_CFG_H}" ]]
then
  echo ../../bin/build.sh $ATTINY "$UI" "-DCFG_H=${TARGET}" "-DMOD_CFG_H=${MOD_CFG_H}"
  ../../bin/build.sh $ATTINY "$UI" "-DCFG_H=${TARGET}" "-DMOD_CFG_H=${MOD_CFG_H}"
else
  echo ../../bin/build.sh $ATTINY "$UI" "-DCFG_H=${TARGET}"
  ../../bin/build.sh $ATTINY "$UI" "-DCFG_H=${TARGET}"
fi

  # track result, and rename compiled files
  if [ 0 = $? ] ; then
    mv -f "$UI".hex "$UI".$NAME.hex
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
if [ 0 != $FAIL ]; then
  echo "FAIL:$FAILED"
fi
if [ 0 == $PASS ]; then exit 1 ; fi #return nonzero if all builds failed
