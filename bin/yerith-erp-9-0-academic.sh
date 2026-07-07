#!/bin/bash
# @author: Dr.-Ing. XAVIER NOUNDOU
# 

[ -f /etc/environment ] && . /etc/environment

export QT_SCALE_FACTOR=${EXP_QT_SCALE_FACTOR}

if [ $YERITH_ERP_3_0_HOME_FOLDER ]; then
    "$YERITH_ERP_3_0_HOME_FOLDER"/bin/yerith-erp-9-0-academic --gui --style cde
else
    echo "Please set the environment variable: 
    		YERITH_ERP_3_0_HOME_FOLDER (file '/etc/environment' or
		in your '.bashrc' file, and, in, file: '.xsessionrc'),
		before you could use yerith-erp-9.0 !"
fi

export QT_SCALE_FACTOR=
