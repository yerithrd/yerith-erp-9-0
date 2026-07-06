/*
 * yerith-erp-radio-button.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "src/widgets/yerith-erp-radio-button.hpp"


#include "src/windows/yerith-erp-window-commons.hpp"



void YerithRadioButton::setYerithEnabled(bool              enabled,
                                         const QPalette    *a_qpalette_FOR_not_enabling /* = 0 */)
{
    setVisible(enabled);
    setEnabled(enabled);
}


void YerithRadioButton::Set_widget_modified(bool widget_Modified)
{
    _widget_Modified = widget_Modified;

    SET_PARENT_WINDOW_OF_WIDGET_MODIFIED(this);

    if (0 != _parent_windows)
    {
        _parent_windows->set_yerith_WindowModified(true);
    }
}
