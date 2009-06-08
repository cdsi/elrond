#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond_record ${SQLITE3} ${SQLITE3FLAGS} ${ELROND_SQLITE3FLAGS} "$@"
exec ${SQLITE3} ${SQLITE3FLAGS} ${ELROND_SQLITE3FLAGS} "$@"
