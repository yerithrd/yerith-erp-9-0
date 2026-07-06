/*
 * yerith-erp-spinbox.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-spinbox.hpp"


#include "src/windows/yerith-erp-window-commons.hpp"


void YerithSpinBox::setYerithEnabled(bool enabled)
{
    _originalPaletteBeforeMissingInformation = palette();

    QDoubleSpinBox::setReadOnly(!enabled);

    if (!isReadOnly())
    {
        setPalette(YerithUtils::YERITH_WHITE_PALETTE);
        setBackgroundRole(QPalette::WindowText);
        setForegroundRole(QPalette::Window);
    }
    else
    {
        setPalette(YerithUtils::YERITH_BLACK_PALETTE);
        setBackgroundRole(QPalette::Window);
        setForegroundRole(QPalette::WindowText);
    }
}


void YerithSpinBox::initializations()
{
    connect(this,
            SIGNAL(valueChanged(double)),
            this,
            SLOT(set_this_qspiN_box_Widget_Modified(double)));


    connect(this,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(set_this_qspiN_box_Widget_Modified(const QString &)));
}


bool YerithSpinBox::checkField()
{
    if (0 == value())
    {
        setPalette(YerithUtils::YERITH_RED_PALETTE);

        return false;
    }

    setPalette(_originalPaletteBeforeMissingInformation);

    return true;
}


void YerithSpinBox::clearField()
{
    clear();

    setPalette(_originalPaletteBeforeMissingInformation);
}


void YerithSpinBox::displayValue(double intValue)
{
    setValue(intValue);
    setYerithEnabled(false);
}


void YerithSpinBox::Set_widget_modified(bool widget_Modified)
{
    _widget_Modified = widget_Modified;

    SET_PARENT_WINDOW_OF_WIDGET_MODIFIED(this);

    if (0 != _parent_windows)
    {
        _parent_windows->set_yerith_WindowModified(true);
    }
}


