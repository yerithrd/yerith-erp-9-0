#!/bin/bash

set -e

sudo rm -rf "${YERITH_ERP_3_0_HOME_FOLDER}/yerith-erp-9.0-server"

"${YERITH_ERP_3_0_HOME_FOLDER}"/yerith-erp-9-0-development-scripts/yerith-create-dpkg_yerith-erp-9-0.sh -v server
