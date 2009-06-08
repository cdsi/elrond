#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond_record ${JAVA} ${JAVAFLAGS} ${ELROND_JAVAFLAGS} "$@"
exec ${JAVA} ${JAVAFLAGS} ${ELROND_JAVAFLAGS} "$@"
