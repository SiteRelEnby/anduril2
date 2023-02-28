#! /usr/bin/env bash
set -e
set -o pipefail

if [[ "${NO_PUSH}" != "1" ]] && [[ "${REMOTE}" != "" ]]
then
	push_remote="${REMOTE}"
elif [[ "${NO_PUSH}" != "1" ]]
then
	push_remote="origin"
fi

if [[ "${UPSTREAM_BRANCH}" != "" ]]
then
	upstream_branch="${UPSTREAM_BRANCH}"
elif [[ "${*}" != "" ]]
then
	upstream_branch="${*}"
else
	upstream_branch="upstream"
fi

if [[ "${0}" == "-bash" ]]
then
mktemp_namepart="bash"
else
mktemp_namepart="$( sed -e 's/^\.\///' -e 's/^\.//' <<< ${0})"
fi
DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
if [[ "${DIR}" != "/tmp" ]]
then
	tempdir=$(mktemp --tmpdir=/tmp -d tmp.${BASHPID}_${mktemp_namepart}_XXXXXXXX)
else
	tempdir=$(mktemp -d) #running script from /tmp acts weirdly, not enough spoons to figure out rn
fi
unset mktemp_namepart mktemp_dir
cd ${tempdir}
bash -x ${DIR}/make-git-repo.sh
cd ${DIR}
git branch -D ${upstream_branch} || true
git checkout --orphan ${upstream_branch}
git remote add tempmerge ${tempdir}/anduril2 || true
git fetch tempmerge
#git merge tempmerge/main --allow-unrelated-histories
git reset --hard tempmerge/main
git remote remove tempmerge
if [[ "${NO_PUSH}" == "1" ]]
then
	exit 0
else
	#git push --force ${upstream_branch}
	git push ${push_remote} ${upstream_branch}
fi
