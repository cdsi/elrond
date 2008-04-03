#!/bin/bash

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

echo -n "Delete the database? [y/N] "
read answer
case "${answer}" in
	[yY]*)
		echo "Deleting: ${ELROND_DB}"
		rm -f "${ELROND_DB}"/*
	;;
esac

elrond-db-load.sh > ${ELROND_LOG}/db.log 2>&1
[ $? != 0 ] && grep 'ERROR!!!' ${ELROND_LOG}/db.log && exit 1

exit 0
