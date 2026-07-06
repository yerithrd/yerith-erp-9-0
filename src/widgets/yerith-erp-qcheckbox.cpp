/*
 * yerith-erp-qcheckbox.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-qcheckbox.hpp"

#include "src/windows/yerith-erp-window-commons.hpp"


#include <QtCore/QDebug>



YerithERPQCheckBox::YerithERPQCheckBox(QWidget *parent)
:QCheckBox(parent),
 _state_changed_status_Variable___POINTER(0),
 _widget_Modified(false),
 _parent_windows(0)
{
    connect(this,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_variable_State_Changed_Status___implicitly(int)));

    connect(this,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(set_this_qcheck_box_Widget_Modified(int)));
}


void YerithERPQCheckBox::setReadOnly(bool isReadOnly)
{
    if (isReadOnly)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents, true);
        setFocusPolicy(Qt::NoFocus);
    }
    else
    {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
        setFocusPolicy(Qt::StrongFocus);
    }
}


void YerithERPQCheckBox::
		setYerithChecked(bool checked, const QString &text /*= YerithUtils::EMPTY_STRING*/)
{
    if (!YerithUtils::isEqualCaseInsensitive(text,
    										 YerithUtils::EMPTY_STRING))
    {
        setText(text);
    }

    setChecked(checked);
}


void YerithERPQCheckBox::setYerithEnabled(bool isEnabled)
{
    if (isEnabled)
    {
        setReadOnly(false);
        setEnabled(true);
    }
    else
    {
        setReadOnly(true);
        setEnabled(false);
    }
}


void YerithERPQCheckBox::handle_variable_State_Changed_Status___implicitly(int state)
{
    if (0 == _state_changed_status_Variable___POINTER)
    {
        return ;
    }

    if (Qt::Checked == state)
    {
        (*_state_changed_status_Variable___POINTER) = true;
    }
    else
    {
        (*_state_changed_status_Variable___POINTER) = false;
    }
}


void YerithERPQCheckBox::Set_widget_modified(bool widget_Modified)
{
    _widget_Modified = widget_Modified;

    SET_PARENT_WINDOW_OF_WIDGET_MODIFIED(this);

    if (0 != _parent_windows)
    {
        _parent_windows->set_yerith_WindowModified(true);
    }
}






