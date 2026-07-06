/*
 * yerith-erp-tab-MAINTENANCE-widget.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-tab-MAINTENANCE-widget.hpp"


#include "src/yerith-erp-windows.hpp"


#include "src/utils/yerith-erp-utils.hpp"



void YerithERPTab_MAINTENANCE_Widget::setVisible(bool visible)
{
    static bool first_runtime_execution_method_call = true;

    /*
    * Performing lazy initializations.
    */
    if (first_runtime_execution_method_call)
    {
        _all_windows = YerithUtils::getAllWindows();

        if (0 != _all_windows)
        {
            _all_windows->_adminWindow
                ->initialize_admin_importer_csv_tableau();

            _all_windows->_adminWindow
                ->initialize_admin_Maintenance_Web_SYSTEM_widget_discovered_tableau();

            _all_windows->_adminWindow
                ->Reset___yri_web_SYSTEM();

            _all_windows->_adminWindow
                ->tabWidget_maintenance_web_SYSTEM_tab->setVisible(true);

            _all_windows->_adminWindow
                ->pushButton_Web_SYSTEMS_reinitialiser->setVisible(true);

            first_runtime_execution_method_call = false;
        }
    }

    QTabWidget::setVisible(visible);
}



