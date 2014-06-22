#!/bin/sh -e

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

elrond-django-migrate.sh
elrond-django-load.sh

exit 0
