#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec mongo "$@" elrond < ${ELROND_ETC}/elrond-mongodb-delete.js
