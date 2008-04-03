#!/bin/bash

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond-db-create.sh

sqlite3 -init ${ELROND_ETC}/elrond-db-load.sql ${ELROND_DB}/elrond.db \
	'.exit'