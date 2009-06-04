#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec ${JAVA} ${JAVAFLAGS} ${ELROND_JAVAFLAGS} "$@"
