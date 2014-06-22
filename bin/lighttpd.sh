#!/bin/sh -e

ELROND_HOME=$(dirname $0)/..
export ELROND_HOME

. ${ELROND_HOME}/etc/common

print_usage_and_die()
{
    echo "Usage: $(basename $0) [--start | --stop | --make-cert]"
    exit 1
}

OPTION="$1"

case "${OPTION}" in
    *start)
	lighttpd -f ${ELROND_ETC}/lighttpd.conf
	;;
    *stop)
	[ -f ${ELROND_RUN}/lighttpd.pid ] && \
	    kill $(cat ${ELROND_RUN}/lighttpd.pid)
	;;
    *make-cert)
	/usr/sbin/make-ssl-cert /usr/share/ssl-cert/ssleay.cnf \
	    ${ELROND_ETC}/lighttpd.pem --force-overwrite
	;;
    *)
	print_usage_and_die
	;;
esac
