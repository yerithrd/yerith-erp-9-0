/*
 * yerith-erp-text-edit.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-text-edit.hpp"


#include "src/windows/yerith-erp-window-commons.hpp"


#include "src/utils/yerith-erp-utils.hpp"


#include <QtGui/QTextBlock>



void YerithTextEdit::initializations()
{
    setYerithPOSTextEditDisplayFormat();

    connect(this,
            SIGNAL(cursorPositionChanged()),
            this,
            SLOT(set_this_text_edit_Widget_Modified()));
}


void YerithTextEdit::Set_widget_modified(bool widget_Modified)
{
    _widget_Modified = widget_Modified;

    SET_PARENT_WINDOW_OF_WIDGET_MODIFIED(this);

    if (0 != _parent_windows)
    {
        _parent_windows->set_yerith_WindowModified(true);
    }
}


bool YerithTextEdit::checkField()
{
    if (toPlainText().isEmpty())
    {
        setPalette(YerithUtils::YERITH_RED_PALETTE);

        return false;
    }

    setPalette(_originalPaletteBeforeMissingInformation);

    return true;
}


void YerithTextEdit::setYerithPOSTextEditDisplayFormat()
{
    if (!isReadOnly())
    {
        setTextColor(YerithUtils::YERITH_BLACK_COLOR);

        setPalette(YerithUtils::YERITH_WHITE_PALETTE);
    }
    else
    {
        setTextColor(YerithUtils::YERITH_WHITE_COLOR);

        setPalette(YerithUtils::YERITH_BLACK_PALETTE);
    }
}


void YerithTextEdit::setVisible(bool visible)
{
    QTextEdit::setVisible(visible);

    setYerithPOSTextEditDisplayFormat();
}


void YerithTextEdit::clearField()
{
    QTextEdit::clear();

    setPalette(_originalPaletteBeforeMissingInformation);

    setYerithPOSTextEditDisplayFormat();
}


void YerithTextEdit::setYerithEnabled(bool enabled)
{
    QTextEdit::setReadOnly(!enabled);

    setYerithPOSTextEditDisplayFormat();

    YerithUtils::yerithSetWidgetColor(this);
}


QString YerithTextEdit::toPlainTextForLatex() const
{
    QTextDocument *aTextDocument = document();

    if (0 == aTextDocument)
    {
        return YerithUtils::EMPTY_STRING;
    }

    QString result;

    QTextBlock it = aTextDocument->begin();

    while (it != aTextDocument->end())
    {
        result.append(QString("%1\\\\").arg(it.text()));

        it = it.next();
    }

    return YerithUtils::LATEX_IN_OUT_handleForeignAccents(result);
}


