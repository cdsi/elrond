#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

cd ${ELROND_HOME}

aclocal
automake --add-missing --copy --force-missing --foreign
autoconf
