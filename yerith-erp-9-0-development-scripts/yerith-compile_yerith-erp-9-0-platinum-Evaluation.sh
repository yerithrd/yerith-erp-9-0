#!/bin/bash
# @file: yerith-compile_yerith-erp-9-0-platinum-Evaluation.sh
# @author: Dr.-Ing. XAVIER NOUNDOU
# @email: YERITH.D@GMAIL.COM



if [[ "${@}" == *"s"* || "${@}" == *"h"* ]]; then
		yerith-compile_yerith-erp-9-0.sh -p -v YERITH_SERVER "${@}"
		exit
fi

if [[ "${@}" == *"e"* ]]; then
	OUT_CMD_TIME=$(time yerith-compile_yerith-erp-9-0.sh -p -v YERITH_SERVER "${@}" > /dev/null 2>&1) && \
		mv bin/yerith-erp-9-0 bin/yerith-erp-9-0-platinum-evaluation-ENGLISH-version
else
	OUT_CMD_TIME=$(time yerith-compile_yerith-erp-9-0.sh -p -v YERITH_SERVER "${@}" > /dev/null 2>&1) && \
		mv bin/yerith-erp-9-0 bin/yerith-erp-9-0-platinum-evaluation-version
fi

val=$(cat YERITH_SERVER.error.log | grep 'error\|ERROR\|Error' | wc -l)

if [ ${val} -eq 0 ]; then
		echo "[compilation avec succes]"
else
		echo "[compilation avec des erreurs (${val})]"
fi

echo ${OUT_CMD_TIME}
