#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

FILENAME="$1"

if [ "${FILENAME}" = "" ]; then
    FILENAME="${ELROND_DATA}"/elrond-django-load.json
fi

exec elrond-django-manage.sh dumpdata --natural | python.sh -mjson.tool > "${FILENAME}"
