#!/bin/bash

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

exec dbxml_dump -h ${ELROND_DB} ${ELROND_DB}/elrond.dbxml \
	> ${ELROND_DB}/elrond.`date +'%F-%s'`.dbxml
