#!/bin/sh

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

elrond_record python.sh $(which pylint) "$@"
exec python.sh $(which pylint) "$@"
