#! /usr/bin/env bash

usage(){
	echo -e "\n${0} build-target\n\nEnv vars:\nBRANCH=branch to compare to\ne.g. \`BRANCH=DEV ${0} emisar-d1v2-nofet\`" >&2
	exit 1
}

cleanup_exit(){
	[[ "${DEBUG}" == "1" ]] && echo $TMP_DIR && exit 0
	rm -rf --one-file-system ${TMP_DIR}
	[[ ! -z "${rm_buildscript}" ]] && rm build.sh
	git checkout ${CUR_BRANCH}
	exit 2
}

[[ "${BRANCH}" == "" ]] && usage
[[ "${?}" == "0" ]] && usage

CUR_BRANCH=$(git rev-parse --abbrev-ref HEAD)
TMP_DIR=$(mktemp -d)

./build.sh ${1} 2> >(tee ${TMP_DIR}/build.err.1 >&2) | tee ${TMP_DIR}/build.out.1 #TODO: error goes to stdout, not err

if [[ "${?}" != "0" ]]
then
	if grep '../../../bin/build.sh: not found' ${TMP_DIR}/build.out.1 #TODO: error goes to stdout, not err
	then
		sed -i 's|\.\./\.\./\.\./bin/build.sh|../../bin/build.sh|' spaghetti-monster/anduril/build-all.sh
		echo "automatically fixing path in build_all.sh" >&2
		./build.sh ${1} 2> >(tee ${TMP_DIR}/build.err.1 >&2)
	else
		#failed for another reason
		cleanup_exit
	fi
fi

cp spaghetti-monster/anduril/anduril.cpp ${TMP_DIR}/anduril.${CUR_BRANCH}.cpp
git checkout -- spaghetti-monster/anduril/version.h

git checkout ${BRANCH} || cleanup_exit
if [[ ! -f ./build.sh ]]
then
	git checkout main build.sh || cleanup_exit
	rm_buildscript=1
fi

./build.sh ${1} 2> >(tee ${TMP_DIR}/build.err.2 >&2)  | tee ${TMP_DIR}/build.out.2 #TODO: error goes to stdout, not err
if [[ "${?}" != "0" ]]
then
	if grep '../../../bin/build.sh: not found' ${TMP_DIR}/build.out.2 #TODO: error goes to stdout, not err
	then
		sed -i 's|\.\./\.\./\.\./bin/build.sh|../../bin/build.sh|' spaghetti-monster/anduril/build-all.sh
		echo "automatically fixing path in build_all.sh" >&2
		./build.sh ${1} 2> >(tee ${TMP_DIR}/build.err.2 >&2)
	else
		#failed for another reason
		cleanup_exit
	fi
fi

cp spaghetti-monster/anduril/anduril.cpp ${TMP_DIR}/anduril.${BRANCH}.cpp

[[ ! -z "${rm_buildscript}" ]] && git restore --staged build.sh && rm build.sh
git checkout -- spaghetti-monster/anduril/version.h
git checkout ${CUR_BRANCH}

diff -w --side-by-side --suppress-common-lines ${TMP_DIR}/anduril.${CUR_BRANCH}.cpp ${TMP_DIR}/anduril.${BRANCH}.cpp | grep -E -v -e '^ +//' -e '^//' > diff.txt
[[ "${DEBUG}" == "1" ]] && echo $TMP_DIR && exit 0
rm -rf --one-file-system ${TMP_DIR}
