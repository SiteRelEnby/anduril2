#! /usr/bin/env bash
set -e
set -o pipefail
if [[ "${0}" == "-bash" ]]
then
mktemp_namepart="bash"
else
mktemp_namepart="$( sed -e 's/^\.\///' -e 's/^\.//' <<< ${0})"
fi
tempdir=$(mktemp --tmpdir=/tmp -d tmp.${BASHPID}_${mktemp_namepart}_XXXXXXXX)
unset mktemp_namepart mktemp_dir
DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd ${tempdir}
bash -x ${DIR}/make-git-repo.sh
cd ${DIR}
git branch -D upstream || true
git checkout --orphan upstream
git remote add tempmerge ${tempdir}/anduril2 || true
git fetch tempmerge
git merge tempmerge/main --allow-unrelated-histories
git remote remove tempmerge
git push --force upstream
