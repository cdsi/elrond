#!/bin/sh -e

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

ARCHIVE=$1

if [ "${ARCHIVE}" = "" ]; then
	echo "Usage: $(basename $0) archive"
	exit 1
fi

exec ${ELROND_BIN}/sqlite3.sh -init ${ELROND_ETC}/elrond-db-restore.sql ${ELROND_DB}/elrond.db \
        < ${ARCHIVE}
