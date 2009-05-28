#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

for x in ${ELROND_EXTRAS}; do
	${ELROND_HOME}/extras/${x}/distclean.sh "$@"
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
done

DISTCLEAN="$(cat ${ELROND_HOME}/distclean.list | sed -e 's/ /xYz/g')"

for x in ${DISTCLEAN}; do
        f=$(echo ${x} | sed -e 's/xYz/ /g';)
        rm -rf "${ELROND_HOME}"/"${f}"
done
