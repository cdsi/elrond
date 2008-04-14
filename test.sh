#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

for x in ${ELROND_EXTRAS}; do
	${ELROND_HOME}/extras/${x}/test.sh "$@"
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
done

if [ -x ${ELROND_HOME}/test-local.sh ]; then
        ${ELROND_HOME}/test-local.sh
        [ $? != 0 ] && echo "ERROR!!!" && exit 1
fi

EVERYTHING=1
OPTION=$1

case "${OPTION}" in
	*backends)
		EVERYTHING=0
		BACKENDS=1
	;;
	*python)
		EVERYTHING=0
		JUST_PYTHON=1
	;;
	*java)
		EVERYTHING=0
		JUST_JAVA=1
	;;
	*extensions)
		EVERYTHING=0
		JUST_PYTHON=1
		JUST_JAVA=1
	;;
esac

cd ${ELROND_HOME}

if [ "${EVERYTHING}" = "1" ] || [ "${BACKENDS}" = "1" ]; then
	true # TODO:
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
fi
if [ "${EVERYTHING}" = "1" ] || [ "${JUST_PYTHON}" = "1" ]; then
        python.sh setup.py test
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
fi
if [ "${EVERYTHING}" = "1" ] || [ "${JUST_JAVA}" = "1" ]; then
        if [ -f build.xml ]; then
                ant.sh test
                [ $? != 0 ] && echo "ERROR!!!" && exit 1
        fi
fi

exit 0
