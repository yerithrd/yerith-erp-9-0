/*
 * yerith-erp-alert-table-view.hpp
 *
 * Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_YERITH_ADMIN_ALERT_TABLE_VIEW_HPP_
#define SRC_YERITH_ADMIN_ALERT_TABLE_VIEW_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include "src/widgets/yerith-erp-qstandard-item-model.hpp"

#include "src/admin/widgets/table-view/yerith-erp-ADMIN-UPPER-TABLE-VIEW-CLASS.hpp"


#include <QtSql/QSqlTableModel>

class YerithSqlTableModel;

class YerithPOSQStandardItemModel;

class YerithERPAlertTableView : public yerithERPAdminUpperTableViewClass
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


	YerithERPAlertTableView();


    YerithERPAlertTableView(QWidget *parent);


    virtual inline ~YerithERPAlertTableView()
    {
    }
};


#endif /* SRC_YERITH_ADMIN_ALERT_TABLE_VIEW_HPP_ */
