#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

libtoolize --automake --copy --force
aclocal -I ${ELROND_M4}
autoheader
automake --add-missing --copy --force-missing --foreign
autoconf
