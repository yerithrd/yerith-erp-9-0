/*
 * yerith-erp-datetime-edit.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-datetime-edit.hpp"

#include "src/windows/yerith-erp-window-commons.hpp"

#include "src/yerith-erp-windows.hpp"
#include "src/utils/yerith-erp-logger.hpp"

#include <QtCore/QPoint>

YerithDateTimeEdit::YerithDateTimeEdit(QWidget *parent)
:QDateTimeEdit(parent),
 _widget_Modified(false),
 _parent_windows(0),
 _logger(new YerithLogger("YerithDateTimeEdit")),
 _calendarWidget(new QCalendarWidget)
{
    _calendarWidget->setMinimumDate(QDate(1900, 1, 1));

    _calendarWidget->setMaximumDate(QDate(70000, 1, 1));

    _calendarWidget->setGridVisible(true);


    setCalendarPopup(true);


    setCalendarWidget(_calendarWidget);


    if (YerithMainWindow::LANGUE_ANGLAISE)
    {
    	setLocale(YerithUtils::englishLocale);
    }
    else
    {
    	setLocale(YerithUtils::frenchLocale);
    }

    _originalPaletteBeforeMissingInformation = palette();

    setYerithERPDateTimeEditDisplayFormat();


    connect(this,
            SIGNAL(dateChanged(const QDate &)),
            this,
            SLOT(set_this_qdate_Time_EDIT_Widget_Modified(const QDate &)));

    connect(this,
            SIGNAL(dateTimeChanged(const QDateTime &)),
            this,
            SLOT(set_this_qdate_Time_EDIT_Widget_Modified(const QDateTime &)));

    connect(this,
            SIGNAL(timeChanged(const QTime &)),
            this,
            SLOT(set_this_qdate_Time_EDIT_Widget_Modified(const QTime &)));
}


bool YerithDateTimeEdit::checkField(const QPalette *aPalette /* = 0 */)
{
    if (GET_CURRENT_DATE > date())
    {
        if (0 != aPalette)
        {
            setPalette(*aPalette);
        }
        else
        {
            setPalette(YerithUtils::YERITH_RED_COLOR);
        }

        return false;
    }


    setPalette(_originalPaletteBeforeMissingInformation);

    return true;
}


void YerithDateTimeEdit::setYerithEnabled(bool enabled)
{
    QDateTimeEdit::setReadOnly(!enabled);

    setYerithERPDateTimeEditDisplayFormat();
}


void YerithDateTimeEdit::setYerithERPDateTimeEditDisplayFormat()
{
    if (isReadOnly())
    {
        setAlignment(Qt::AlignCenter);

        setPalette(YerithUtils::YERITH_BLACK_PALETTE);
    }
    else
    {
        setAlignment(Qt::AlignLeft);

        setPalette(YerithUtils::YERITH_WHITE_PALETTE);
    }
}


void YerithDateTimeEdit::setStartDate(QDate startDate)
{
    _startDate = startDate;

    setDate(_startDate);
}


void YerithDateTimeEdit::Set_widget_modified(bool widget_Modified)
{
    _widget_Modified = widget_Modified;

    SET_PARENT_WINDOW_OF_WIDGET_MODIFIED(this);

    if (0 != _parent_windows)
    {
        _parent_windows->set_yerith_WindowModified(true);
    }
}



