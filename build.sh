#!/bin/bash

KOCHANSKI_HOME=$(dirname $0)
. ${KOCHANSKI_HOME}/etc/common

TARGET="$1"
TARGET=${TARGET:="build"}

${PYTHON} ${PYTHONFLAGS} setup.py ${TARGET}
