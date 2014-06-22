#!/bin/sh -e

ELROND_HOME=$(dirname $0)
. ${ELROND_HOME}/etc/common

find ${ELROND_HOME} -name Makefile.in | xargs rm -f

find ${ELROND_HOME} -name "*.pyc" | xargs rm -f
rm -f ${ELROND_LIB}/python/*

exit 0
