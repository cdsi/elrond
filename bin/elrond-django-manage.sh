#!/bin/sh -e

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

DJANGO_SETTINGS_MODULE=elrond.www.settings
export DJANGO_SETTINGS_MODULE

exec python.sh ${ELROND_BIN}/elrond-django-manage.py "$@" -v 0
