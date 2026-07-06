/*
 * yerith-erp-alert-table-view.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-alert-table-view.hpp"


	YerithERPAlertTableView::YerithERPAlertTableView()
    :yerithERPAdminUpperTableViewClass()
    {
        _stdItemModel->_curTableView = this;

        _database_table_column_Int_To_Bool_Viewing
            .append(YerithDatabaseTableColumn::ALERTE_RESOLUE);
    }

    YerithERPAlertTableView::YerithERPAlertTableView(QWidget *parent)
    :yerithERPAdminUpperTableViewClass(parent)
    {
        _stdItemModel->_curTableView = this;

        _database_table_column_Int_To_Bool_Viewing
            .append(YerithDatabaseTableColumn::ALERTE_RESOLUE);
    }
