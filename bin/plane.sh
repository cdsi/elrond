#!/bin/sh

ELROND_HOME="$(dirname "$0")"/..
export ELROND_HOME

. "${ELROND_HOME}"/etc/common

OPTION="$1"

case "${OPTION}" in
        *restore-defaults)
                rm -f "${ELROND_ETC}"/plane.ini
                shift
        ;;
esac

if [ ! -f "${ELROND_ETC}"/plane.ini ]; then
        cp "${ELROND_ETC}"/plane.ini.in "${ELROND_ETC}"/plane.ini
fi

exec python.sh "${ELROND_BIN}"/plane.py "$@"
