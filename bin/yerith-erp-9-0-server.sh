#!/bin/bash
# @author: Dr.-Ing. XAVIER NOUNDOU
# 

[ -f /etc/environment ] && . /etc/environment

if [ $YERITH_ERP_3_0_HOME_FOLDER ]; then
    "$YERITH_ERP_3_0_HOME_FOLDER"/bin/yerith-erp-9-0-server --gui --style Windows
else
    echo "Please set the environment variable: 
    		YERITH_ERP_3_0_HOME_FOLDER (file '/etc/environment' or
		in your '.bashrc' file, and, in, file: '.xsessionrc'),
		before you could use yerith-erp-9.0 !"
fi
