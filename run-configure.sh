#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

./configure ${ELROND_CONFIGUREFLAGS}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
