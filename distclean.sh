#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

for extra in ${ELROND_EXTRAS}; do
	${extra}/distclean.sh "$@"
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
done

DISTCLEAN="$(cat ${ELROND_HOME}/distclean.list | sed -e 's/ /xYz/g')"

for x in ${DISTCLEAN}; do
        f=$(echo ${x} | sed -e 's/xYz/ /g';)
        rm -rf "${ELROND_HOME}"/"${f}"
done

# To re-create distclean.list:
#
# cd "${ELROND_HOME}"
# svn-clean
# yes | ./build.sh
# ./test.sh
# svn st --no-ignore | grep -e ^[I?] | grep -v 'extras/' | sed 's/^. \+//' | sort > distclean.list
