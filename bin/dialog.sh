#!/bin/sh

ELROND_HOME="$(dirname "$0")"/..
export ELROND_HOME

. "${ELROND_HOME}"/etc/common

OPTION="$1"

case "${OPTION}" in
        *restore-defaults)
                rm -f "${ELROND_ETC}"/dialog.ini
                shift
        ;;
esac

if [ ! -f "${FARAMIR_ETC}"/dialog.ini ]; then
        cp "${FARAMIR_ETC}"/dialog.ini.in "${FARAMIR_ETC}"/dialog.ini
fi

exec python.sh "${ELROND_BIN}"/dialog.py "$@"
