#!/bin/sh -e

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond_record ${MAKE} ${MAKEFLAGS} ${ELROND_MAKEFLAGS} "$@"
exec ${MAKE} ${MAKEFLAGS} ${ELROND_MAKEFLAGS} "$@"
