#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

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

if [ "${EVERYTHING}" = "1" ] || [ "${JUST_JAVA}" = "1" ]; then
	if [ -f build.xml ]; then
		${ELROND_BIN}/ant.sh clean
		[ $? != 0 ] && echo "ERROR!!!" && exit 1
	fi
fi
if [ "${EVERYTHING}" = "1" ] || [ "${JUST_PYTHON}" = "1" ]; then
	${ELROND_BIN}/python.sh setup.py clean
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
fi
if [ "${EVERYTHING}" = "1" ] || [ "${BACKENDS}" = "1" ]; then
	${ELROND_BIN}/make.sh -k uninstall distclean
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
fi

if [ -x ${ELROND_HOME}/clean-local.sh ]; then
	${ELROND_HOME}/clean-local.sh
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
fi

exit 0
