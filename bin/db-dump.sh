#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)/..
export KOCHANSKI_HOME

. ${KOCHANSKI_HOME}/etc/common

sqlite3 -init ${KOCHANSKI_ETC}/db-dump.sql ${KOCHANSKI_DB}/kochanski.db \
	'.exit'
