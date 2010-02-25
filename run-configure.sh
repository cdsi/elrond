#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

OPTION="$1"

EXTENSIONFLAGS="--enable-java=${ELROND_SRC}/java --enable-python=${ELROND_SRC}/python"

case "${OPTION}" in
	*disable-extensions)
		EXTENSIONFLAGS="--enable-java=no --with-java=no \
			 --enable-python=no --with-python=no"
	;;
esac

./configure --disable-static --enable-coverage --enable-gtk-doc ${ELROND_CONFIGUREFLAGS} ${EXTENSIONFLAGS}
[ $? != 0 ] && echo "ERROR!!!" && exit 1

exit 0
