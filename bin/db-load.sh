#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)/..
export KOCHANSKI_HOME

. ${KOCHANSKI_HOME}/etc/common

db-create.sh

dbxml -h ${KOCHANSKI_DB} -s ${KOCHANSKI_ETC}/db-load.dbxml
