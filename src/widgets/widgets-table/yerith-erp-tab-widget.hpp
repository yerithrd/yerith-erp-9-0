/*
 * yerith-erp-tab-widget.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_TAB_WIDGET_HPP_
#define YERITH_ERP_TAB_WIDGET_HPP_

#include <QtWidgets/QTabWidget>

#include "src/utils/yerith-erp-utils.hpp"


class YerithWindowsCommons;

class YerithUtils;

class YerithERPTabWidget : public QTabWidget
{

public:

    YERITH_CLASS_OPERATORS

    inline YerithERPTabWidget(QWidget *parent)
    :QTabWidget(parent)
    {
        _parent_window = (YerithWindowsCommons *) window();
    }

    inline ~YerithERPTabWidget()
    {
    }

    inline void resetYerithERPTabWidget()
    {
        setCurrentIndex(0);
    }


public:

    YerithWindowsCommons *_parent_window;

};


#endif /* YERITH_ERP_TAB_WIDGET_HPP_ */
