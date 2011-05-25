#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond-django-manage.sh syncdb --noinput
elrond-django-manage.sh migrate elrond.www.impex
