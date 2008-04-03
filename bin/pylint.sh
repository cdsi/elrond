#!/bin/bash

GRIMA_HOME=$(dirname $0)/..
export GRIMA_HOME

. ${GRIMA_HOME}/etc/common

exec python.sh $(which pylint) "$@"
