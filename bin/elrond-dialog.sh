#!/bin/sh

ELROND_HOME="$(dirname "$0")"/..
export ELROND_HOME

. "${ELROND_HOME}"/etc/common

OPTION="$1"

case "${OPTION}" in
        *restore-defaults)
                rm -f "${ELROND_ETC}"/elrond-dialog-widget.ini
                shift
        ;;
esac

if [ ! -f "${ELROND_ETC}"/elrond-dialog-widget.ini ]; then
        cp "${ELROND_ETC}"/elrond-dialog-widget.ini.in "${ELROND_ETC}"/elrond-dialog-widget.ini
fi

echo $$ > "${ELROND_RUN}"/elrond-dialog.pid

exec python.sh "${ELROND_BIN}"/elrond-dialog.py "$@"
