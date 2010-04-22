#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

GTKDOCSIZE="$(which gtkdocize 2> /dev/null)"
if [ -x "${GTKDOCSIZE}" ]; then
        "${GTKDOCSIZE}" --copy --flavour no-tmpl
else
        echo "EXTRA_DIST=" > "${ELROND_HOME}"/gtk-doc.make
fi
libtoolize --automake --copy --force
aclocal ${ACLOCALFLAGS} ${ELROND_ACLOCALFLAGS}
autoheader
automake --add-missing --copy --force-missing --foreign
autoconf
