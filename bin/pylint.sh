#!/bin/sh -e

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec "${ELROND_BIN}"/python.sh ${PYLINT} ${PYLINTFLAGS} ${ELROND_PYLINTFLAGS} "$@"
