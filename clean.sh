#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)
. ${KOCHANSKI_HOME}/etc/common

cd ${KOCHANSKI_HOME}

${PYTHON} ${PYTHONFLAGS} setup.py ${TARGET}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

make -k uninstall distclean
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
