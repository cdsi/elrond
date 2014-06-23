#!/bin/sh -e

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

if [ "${SKIP_QUESTIONS}" = "" ]; then
        echo -n "Delete the database? [y/N] "
        read answer
        case "${answer}" in
                [yY]*)
                        elrond-db-delete.sh || true
                ;;
        esac
fi

elrond-db-load.sh || true
# TODO: [ $? != 0 ] && exit 1

exit 0
