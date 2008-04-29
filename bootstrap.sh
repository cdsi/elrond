#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

libtoolize --automake --copy --force
aclocal ${ACLOCALFLAGS}
autoheader
automake --add-missing --copy --force-missing --foreign
autoconf
