#!/bin/bash

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

ARCHIVE=$1

if [ "${ARCHIVE}" = "" ]; then
	echo "Usage: `basename $0` [archive]"
	exit 1
fi

exec dbxml_load -h ${ELROND_DB} ${ELROND_DB}/elrond.dbxml \
	< ${ARCHIVE}
