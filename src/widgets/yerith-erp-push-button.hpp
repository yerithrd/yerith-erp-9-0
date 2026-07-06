/*
 * yerith-erp-push-button.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_WIDGETS_YERITH_PUSH_BUTTON_HPP_
#define SRC_WIDGETS_YERITH_PUSH_BUTTON_HPP_


#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include "src/windows/yerith-erp-window-commons.hpp"


#include <QtWidgets/QPushButton>


class YerithWindowsCommons;
class YerithTableViewWITHpagination;
class YerithSqlTableModel;


class YerithPushButton:public QPushButton
{
Q_OBJECT public:

    YERITH_CLASS_OPERATORS

    inline YerithPushButton(QWidget *w)
           :QPushButton(w),
            _widget_Modified(false),
            _is_yerith_pushbutton_authorized_for_current_user(false),
            _yerithCurWindowSqlTableModel(0),
            _receiver(0),
            _func(0),
            _parent_windows(0)
    {
    }

    inline YerithPushButton(const QString &s,
                            QWidget       *w)
           :QPushButton(s, w),
            _is_yerith_pushbutton_authorized_for_current_user(false),
            _yerithCurWindowSqlTableModel(0),
            _receiver(0),
            _func(0),
            _parent_windows(0)
    {
    }

    inline YerithPushButton(const QIcon     &i,
                            const QString   &s,
                            QWidget         *w)
           :QPushButton(i, s, w),
            _is_yerith_pushbutton_authorized_for_current_user(false),
            _yerithCurWindowSqlTableModel(0),
            _receiver(0),
            _func(0),
            _parent_windows(0)
    {
    }


    ~YerithPushButton();


    inline bool isAuthorizedForCurrentUser()
    {
        return _is_yerith_pushbutton_authorized_for_current_user;
    }

    void setAuthorizedForCurrentUser(bool authorized);

    virtual inline void setEnabled(bool enable)
    {
        setAuthorizedForCurrentUser(enable);
    }


    virtual inline bool is_widget_modified()
    {
        return _widget_Modified;
    }

//    virtual void Set_widget_modified(bool widget_Modified);


    virtual inline YerithWindowsCommons *GET_parent_windows()
    {
        return _parent_windows;
    }

    virtual inline void Set_parent_windows(YerithWindowsCommons *A_parent_windows)
    {
        _parent_windows = A_parent_windows;
    }


    void enable(const QObject *receiver,
                const char *f);


    void disable(const QObject *receiver);


    void enable_WITH_SQL_TABLE_MODEL_AS_CALL_ARGUMENT(YerithAbstractClassYerithSearchWindow         *receiver,
                                                      YerithAbstractClassYerithSearchWindow::fptr    func,
                                                      YerithSqlTableModel                           **aYerithSqlTableModel_IN);


public slots:

//    virtual inline void set_this_qpushbutton_Widget_Modified()
//    {
//        Set_widget_modified(true);
//    }

    void call_view_page_function();


private:

    bool _widget_Modified;

    bool _is_yerith_pushbutton_authorized_for_current_user;

    YerithSqlTableModel **_yerithCurWindowSqlTableModel;

    YerithAbstractClassYerithSearchWindow *_receiver;

    YerithAbstractClassYerithSearchWindow::fptr _func;

    YerithWindowsCommons    *_parent_windows;
};


#endif /* SRC_WIDGETS_YERITH_PUSH_BUTTON_HPP_ */
