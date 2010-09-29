#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

DISTCLEAN="$(cat ${ELROND_HOME}/distclean.list | sed -e 's/ /xYz/g')"

for x in ${DISTCLEAN}; do
        f=$(echo ${x} | sed -e 's/xYz/ /g';)
        rm -rf "${ELROND_HOME}"/"${f}"
done

# To re-create distclean.list:
#
# cd "${ELROND_HOME}"
# git clean -d -f -x
# yes | ./build.sh && ./test.sh
# git status -s | grep -e ^[?] | sed 's/^.. \+//' | sort > distclean.list
