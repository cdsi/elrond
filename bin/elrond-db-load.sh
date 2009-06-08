#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond-db-create.sh

exec ${ELROND_BIN}/sqlite3.sh -init ${ELROND_ETC}/elrond-db-load.sql ${ELROND_DB}/elrond.db \
	'.exit'
