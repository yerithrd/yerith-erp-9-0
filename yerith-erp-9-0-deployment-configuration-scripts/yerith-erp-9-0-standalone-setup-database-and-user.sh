#!/bin/bash
#@author: Dr.-Ing. XAVIER NOUNDOU

MAINDB="YERITH_RD_YDE_Ahala"
USER_NAME="yerith_erp_9"
PASSWDDB="1234567"
echo "Enter MariaDB administrative password YERITH-ERP-9.0 database and user !"
sudo mysql -uroot -p -e "CREATE DATABASE ${MAINDB} CHARACTER SET = 'utf8'; CREATE USER ${USER_NAME}@'%' IDENTIFIED BY '${PASSWDDB}'; GRANT ALL PRIVILEGES ON *.* TO '${USER_NAME}'@'%'; FLUSH PRIVILEGES;"
mysql_ret_code="$?"
exit 0
