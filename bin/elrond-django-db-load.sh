#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec elrond-django-manage.sh loaddata "${ELROND_DB}"/elrond-django-db.json
