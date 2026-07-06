#!/bin/bash
# @author: Dr.-Ing. XAVIER NOUNDOU

sudo service mysql stop

sudo /usr/bin/mariadbd-safe &

sleep 5s

sudo expect /tmp/yerith-erp-9-0-configure-mysql-server-set-root-pwd.exp
