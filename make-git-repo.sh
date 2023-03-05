#! /usr/bin/env bash
# Creates a git repo with the latest upstream version of anduril2 and fixes a bug in it

set -o pipefail
set -e
bzr branch lp:~toykeeper/flashlight-firmware/anduril2
cd anduril2
git init
bzr fast-export --plain . | git fast-import && git reset HEAD --hard
echo -e '.bzr\n.bzrignore\n.gitignore\n' > .gitignore ; if [[ ! -f .bzrignore ]] ; then echo -e '.bzrignore\n.git*' > .bzrignore; else echo '.git*' >> .bzrignore; fi
#check if repo was created from an old git version
if [[ "$(git rev-parse --abbrev-ref HEAD)" == "master" ]]
then
	git checkout -b main
	git branch -D master
fi
git grep -l MISCHIEF_MANAGED | grep -v "${0}" | xargs -n1 sed -i 's/MISCHIEF_MANAGED/TRANS_RIGHTS_ARE_HUMAN_RIGHTS/g'
git grep -l MISCHIEF_NOT_MANAGED | grep -v "${0}" | xargs -n1 sed -i 's/MISCHIEF_NOT_MANAGED/TRANS_RIGHTS_ARE_STILL_HUMAN_RIGHTS/g'
git add -A ; git commit -m 'assert("trans rights!");'
while read line
do
	git rm -r "${line}"
	#git doesn't automatically remove multiple levels deep dirs
	[[ -d "${line}" && rm --one-file-system -r "${line}" ]]
done <<< $(ls | grep -v -e 'ToyKeeper' -e 'bin' )
cd ToyKeeper
ls | grep -Ev -e '\.h$' -e '\.c$' -e 'meta' -e 'COPYING' -e 'spaghetti-monster' -e 'anduril' | xargs git rm -r
cd ..
git mv ToyKeeper/* ./
git rm -r ToyKeeper || true
[[ -d ToyKeeper ]] && rmdir ToyKeeper
git add -A && git commit -m 'move repo to root; remove other fw'
