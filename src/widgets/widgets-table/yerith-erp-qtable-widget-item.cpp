/*
 * yerith-erp-qtable-widget-item.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-qtable-widget-item.hpp"




YerithQTableWidgetItem::YerithQTableWidgetItem(const QString     &text,
                                               bool              editable /* = true */)
    :QTableWidgetItem(text)
{
    if (!editable)
    {
         setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    }
    else
    {
        setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter | Qt::ItemIsEditable);
    }
}
