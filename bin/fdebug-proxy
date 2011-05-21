#!/bin/sh
HOSTNAME=`cat ./hostname`
PORT=`cat ./port`
MAX_CON=`cat ./maxconnections`
FDEBUGD="../release/fdebug-proxy"

exec /usr/bin/tcpserver -D -v -R -l $HOSTNAME -c "$MAX_CON" 0 $PORT $FDEBUGD >>/var/log/fdebug/proxy.log 2>&1


