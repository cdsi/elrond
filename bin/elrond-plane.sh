#!/bin/sh

ELROND_HOME="$(dirname "$0")"/..
export ELROND_HOME

. "${ELROND_HOME}"/etc/common

OPTION="$1"

case "${OPTION}" in
        *restore-defaults)
                rm -f "${ELROND_ETC}"/elrond-plane-widget.ini
                shift
        ;;
esac

if [ ! -f "${ELROND_ETC}"/elrond-plane-widget.ini ]; then
        cp "${ELROND_ETC}"/elrond-plane-widget.ini.in "${ELROND_ETC}"/elrond-plane-widget.ini
fi

echo $$ > "${ELROND_RUN}"/elrond-plane.pid

exec python.sh "${ELROND_BIN}"/elrond-plane.py "$@"
