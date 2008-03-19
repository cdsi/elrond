#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)/..
export KOCHANSKI_HOME

. ${KOCHANSKI_HOME}/etc/common

exec dbxml_dump -h ${KOCHANSKI_DB} ${KOCHANSKI_DB}/kochanski.dbxml \
	> ${KOCHANSKI_DB}/kochanski.`date +'%F-%s'`.dbxml
