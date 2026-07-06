/*
 * yerith-erp-radio-button.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_RADIO_BUTTON_HPP_
#define YERITH_ERP_RADIO_BUTTON_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include <QtWidgets/QRadioButton>

class QToolBar;
class YerithPOSAdminWindowsCommons;
class YerithWindowsCommons;

class YerithRadioButton : public QRadioButton
{

public:

    YERITH_CLASS_OPERATORS

    inline YerithRadioButton(const QString &text, QWidget *parent = 0)
    :QRadioButton(text,
                  parent),
     _widget_Modified(false),
     _parent_windows(0)
    {
        connect(this,
                SIGNAL(toggled(bool)),
                this,
                SLOT(set_this_radio_button_Widget_Modified(bool)));
    }

    inline YerithRadioButton(QWidget *parent = 0):QRadioButton(parent)
    {
    }

    inline ~YerithRadioButton()
    {
    }

    void setYerithEnabled(bool              enabled,
                          const QPalette    *a_qpalette_FOR_not_enabling = 0);


    virtual inline bool is_widget_modified()
    {
        return _widget_Modified;
    }

    virtual void Set_widget_modified(bool widget_Modified);


    virtual inline YerithWindowsCommons *GET_parent_windows()
    {
        return _parent_windows;
    }

    virtual inline void Set_parent_windows(YerithWindowsCommons *A_parent_windows)
    {
        _parent_windows = A_parent_windows;
    }


public slots:

    virtual inline void set_this_radio_button_Widget_Modified(bool checked)
    {
        Set_widget_modified(true);
    }


protected:

    bool _widget_Modified;

    YerithWindowsCommons    *_parent_windows;
};


#endif /* YERITH_ERP_RADIO_BUTTON_HPP_ */
