#!/bin/sh

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

echo -n "Delete the database? [y/N] "
read answer
case "${answer}" in
	[yY]*)
                elrond-db-delete.sh
	;;
esac

elrond-db-load.sh
# TODO: [ $? != 0 ] && exit 1

exit 0
