#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

libtoolize --automake --copy --force
aclocal ${ELROND_ACLOCALFLAGS}
autoheader
automake --add-missing --copy --force-missing --foreign
autoconf
