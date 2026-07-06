/*
 * yerith-erp-qcheckbox.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_WIDGETS_YERITH_QCHECKBOX_HPP_
#define SRC_WIDGETS_YERITH_QCHECKBOX_HPP_


#include "src/utils/yerith-erp-utils.hpp"


#include <QtWidgets/QCheckBox>


class YerithERPQCheckBox : public QCheckBox
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

	YerithERPQCheckBox(QWidget *parent);

    virtual inline ~YerithERPQCheckBox()
    {
    }


    virtual inline void reset_to_Checked()
    {
        setChecked(true);
    }


    virtual inline void clear()
    {
        setChecked(false);
    }


    virtual inline void Set_state_changed_status_Variable___POINTER
                            (bool *a_state_changed_status_Variable___POINTER)
    {
        _state_changed_status_Variable___POINTER =
                a_state_changed_status_Variable___POINTER;
    }

    virtual inline bool *get_state_changed_status_Variable___POINTER()
    {
        return _state_changed_status_Variable___POINTER;
    }


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


    void setReadOnly(bool isReadOnly);

    void setYerithChecked(bool checked,
    					  const QString &text = YerithUtils::EMPTY_STRING);

    void setYerithEnabled(bool isEnabled);


public slots:

    virtual void handle_variable_State_Changed_Status___implicitly(int state);

    virtual inline void set_this_qcheck_box_Widget_Modified(int state)
    {
        Set_widget_modified(true);
    }


private:

    bool *_state_changed_status_Variable___POINTER;

    bool _widget_Modified;

    YerithWindowsCommons    *_parent_windows;

};

#endif /* SRC_WIDGETS_YERITH_QCHECKBOX_HPP_ */
