#!/bin/bash

GRIMA_HOME=$(dirname $0)
. ${GRIMA_HOME}/etc/common

find ${GRIMA_HOME} -name Makefile.in | xargs rm -f
find ${GRIMA_HOME} -name "*.pyc" | xargs rm -f
rm -f ${GRIMA_LIB}/python/*

exit 0
