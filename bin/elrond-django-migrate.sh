#!/bin/sh -e

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond-django-manage.sh syncdb --noinput
# TODO: elrond-django-manage.sh migrate elrond.www.appname
