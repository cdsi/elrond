#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec python.sh ${PYLINT} ${PYLINTFLAGS} ${ELROND_PYLINTFLAGS} "$@"
