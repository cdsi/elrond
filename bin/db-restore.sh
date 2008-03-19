#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)/..
export KOCHANSKI_HOME

. ${KOCHANSKI_HOME}/etc/common

ARCHIVE=$1

if [ "${ARCHIVE}" = "" ]; then
	echo "Usage: `basename $0` [archive]"
	exit 1
fi

exec dbxml_load -h ${KOCHANSKI_DB} ${KOCHANSKI_DB}/kochanski.dbxml \
	< ${ARCHIVE}
