#!/bin/bash

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec dbxml -h ${ELROND_DB} -s ${ELROND_ETC}/db-test.dbxml
