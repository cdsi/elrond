#!/bin/bash

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

sqlite3 -init ${ELROND_ETC}/elrond-db-archive.sql ${ELROND_DB}/elrond.db \
	'.exit' > ${ELROND_DB}/elrond.$(date +'%F-%s').sql
