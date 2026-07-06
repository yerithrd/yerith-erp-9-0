/*
 * yerith_dynamic_taint_analysis_directives.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith_dynamic_taint_analysis_directives.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/utils/yerith-erp-utils.hpp"




YerithDynamicTaintAnalysisDirectives::YerithDynamicTaintAnalysisDirectives()
:_all_windows(0)
{
    _all_windows = YerithUtils::getAllWindows();
}



bool YerithDynamicTaintAnalysisDirectives::
        is_a_TAINTED_value(QString a_Potential_tainted_value_Variable_pointer)
{
//    if (0 != _all_windows)
//    {
//        _all_windows->getSqlTableModel___yri_db_runtime_verif();
//    }

    return false;
}


bool YerithDynamicTaintAnalysisDirectives::
        is_a_sanitizer_method(QString a_Potential_Sanitizing_method)
{


    return false;
}



