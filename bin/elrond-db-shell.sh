#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

sqlite3 -init ${ELROND_ETC}/elrond-db-shell.sql ${ELROND_DB}/elrond.db
