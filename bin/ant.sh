#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond_record ${ANT} ${ANTFLAGS} ${ELROND_ANTFLAGS} "$@"
exec ${ANT} ${ANTFLAGS} ${ELROND_ANTFLAGS} "$@"
