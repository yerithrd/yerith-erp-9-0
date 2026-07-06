#!/bin/bash

set -e

sudo rm -rf "${YERITH_ERP_3_0_HOME_FOLDER}/yerith-erp-9-0-standalone-configurations-data-ENGLISH"

"${YERITH_ERP_3_0_HOME_FOLDER}"/yerith-erp-9-0-development-scripts/ENGLISH/yerith-create-dpkg_yerith-erp-9-0-configurations-data-ENGLISH.sh \
	-v standalone
