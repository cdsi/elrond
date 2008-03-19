#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)
. ${KOCHANSKI_HOME}/etc/common

for x in ${KOCHANSKI_EXTRAS}; do
	${KOCHANSKI_HOME}/extras/${x}/test.sh $*
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
done

cd ${KOCHANSKI_HOME}

TARGET="$1"
TARGET=${TARGET:="test"}

db-delete.sh
db-create.sh

${PYTHON} ${PYTHONFLAGS} setup.py ${TARGET}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
