#! /usr/bin/env bash
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
docker run --rm -v ${SCRIPTPATH}:/src -i -t anduril-builder:latest siterelenby-noctigon-dm112-tintramp-fet
