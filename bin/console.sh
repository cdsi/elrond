#!/bin/sh

ELROND_HOME="$(dirname "$0")"/..
export ELROND_HOME

. "${ELROND_HOME}"/etc/common

OPTION="$1"

case "${OPTION}" in
        *restore-defaults)
                rm -f "${ELROND_ETC}"/console.ini
                shift
        ;;
esac

if [ ! -f "${FARAMIR_ETC}"/console.ini ]; then
        cp "${FARAMIR_ETC}"/console.ini.in "${FARAMIR_ETC}"/console.ini
fi

exec python.sh "${ELROND_BIN}"/console.py "$@"
