#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)
. ${KOCHANSKI_HOME}/etc/common

cd ${KOCHANSKI_HOME}

./configure ${KOCHANSKI_CONFIGUREFLAGS}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
