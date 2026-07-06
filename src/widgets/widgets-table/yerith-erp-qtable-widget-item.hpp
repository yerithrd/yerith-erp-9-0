/*
 * yerith-erp-qtable-widget-item.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_QTABLE_WIDGET_ITEM_HPP_
#define YERITH_ERP_3_0_QTABLE_WIDGET_ITEM_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include <QtWidgets/QTableWidgetItem>

class YerithQTableWidgetItem : public QTableWidgetItem
{

public:

    YERITH_CLASS_OPERATORS


    inline YerithQTableWidgetItem()
    :QTableWidgetItem()
    {
        setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    }


    YerithQTableWidgetItem(const QString    &text,
                           bool             editable = true);


    inline YerithQTableWidgetItem(const QIcon   &icon,
                                  const QString &text)
    :QTableWidgetItem(icon, text)
    {
        setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    }


    inline ~YerithQTableWidgetItem()
    {
    }
};


#endif /* YERITH_ERP_3_0_QTABLE_WIDGET_ITEM_HPP_ */
