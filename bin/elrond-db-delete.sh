#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec ${ELROND_BIN}/sqlite3.sh -init ${ELROND_ETC}/elrond-db-delete.sql ${ELROND_DB}/elrond.db \
	'.exit'
