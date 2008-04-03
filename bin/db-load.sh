#!/bin/bash

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

db-create.sh

sqlite3 -init ${ELROND_ETC}/db-load.sql ${ELROND_DB}/elrond.db \
	'.exit'
