#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

for x in ${ELROND_EXTRAS}; do
	${ELROND_HOME}/extras/${x}/test.sh $*
	[ $? != 0 ] && echo "ERROR!!!" && exit 1
done

cd ${ELROND_HOME}

TARGET="$1"
TARGET=${TARGET:="test"}

db-delete.sh
db-create.sh

${PYTHON} ${PYTHONFLAGS} setup.py ${TARGET}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
