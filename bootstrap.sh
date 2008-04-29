#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

libtoolize --automake --copy --force
ACLOCALFLAGS=
XXX="/opt/libtool/share/aclocal /opt/pkg-config/share/aclocal /opt/glib/share/aclocal ${ELROND_M4}"
for x in ${XXX}; do
        if [ ! -d ${x} ]; then
                continue
        fi
        ACLOCALFLAGS="-I ${x} ${ACLOCALFLAGS}"
done
aclocal ${ACLOCALFLAGS}
autoheader
automake --add-missing --copy --force-missing --foreign
autoconf
