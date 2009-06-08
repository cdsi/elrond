#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond_record ${PYTHON} ${PYTHONFLAGS} ${ELROND_PYTHONFLAGS} "$@"
exec ${PYTHON} ${PYTHONFLAGS} ${ELROND_PYTHONFLAGS} "$@"
