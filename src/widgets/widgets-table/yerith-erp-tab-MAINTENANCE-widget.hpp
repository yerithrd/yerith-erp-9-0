/*
 * yerith-erp-tab-MAINTENANCE-widget.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_ERP_TAB_MAINTENANCE_WIDGET_HPP_
#define _YERITH_ERP_TAB_MAINTENANCE_WIDGET_HPP_


#include "yerith-erp-tab-widget.hpp"


class YerithERPTabWidget;


class YerithERPTab_MAINTENANCE_Widget : public YerithERPTabWidget
{

public:

    YERITH_CLASS_OPERATORS


    inline YerithERPTab_MAINTENANCE_Widget(QWidget *parent)
        :YerithERPTabWidget(parent),
         _all_windows(0)
    {
    }


    virtual inline ~YerithERPTab_MAINTENANCE_Widget()
    {
    }


    virtual void setVisible(bool visible);


protected:

    YerithERPWindows    *_all_windows;

};


#endif //_YERITH_ERP_TAB_MAINTENANCE_WIDGET_HPP_
