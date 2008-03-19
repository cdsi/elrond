#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)
. ${KOCHANSKI_HOME}/etc/common

for x in ${KOCHANSKI_EXTRAS}; do
	${KOCHANSKI_HOME}/extras/${x}/clean.sh $*
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
done

cd ${KOCHANSKI_HOME}

TARGET="$1"
TARGET=${TARGET:="clean"}

${PYTHON} ${PYTHONFLAGS} setup.py ${TARGET}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

make -k uninstall distclean
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
