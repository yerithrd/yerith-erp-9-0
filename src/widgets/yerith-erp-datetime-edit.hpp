/*
 * yerith-erp-datetime-edit.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_WIDGETS_YERITH_DATETIME_EDIT_HPP_
#define SRC_WIDGETS_YERITH_DATETIME_EDIT_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"


#include "src/windows/yerith-erp-window-commons.hpp"


#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QCalendarWidget>

class QPoint;
class QDateTimeEdit;
class QCalendarWidget;
class QMainWindow;

class YerithERPWindows;
class YerithLogger;

class YerithDateTimeEdit : public QDateTimeEdit
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

	YerithDateTimeEdit(QWidget *parent = 0);

    inline ~YerithDateTimeEdit()
    {
        delete _calendarWidget;
    }

    bool checkField(const QPalette *aPalette = 0);

    void setYerithEnabled(bool enabled);

    void setYerithERPDateTimeEditDisplayFormat();

    void setStartDate(QDate startDate);

    inline void setMyDate(QDate aDate)
    {
        setDate(aDate);
    }





    virtual inline bool is_widget_modified()
    {
        return _widget_Modified;
    }

    virtual void Set_widget_modified(bool widget_Modified);


    inline QCalendarWidget *getCalendarWidget()
    {
        return _calendarWidget;
    }


    virtual inline YerithWindowsCommons *GET_parent_windows()
    {
        return _parent_windows;
    }

    virtual inline void Set_parent_windows(YerithWindowsCommons *A_parent_windows)
    {
        _parent_windows = A_parent_windows;
    }

public slots:

    virtual inline void set_this_qdate_Time_EDIT_Widget_Modified(const QDate &date)
    {
        Set_widget_modified(true);
    }

    virtual inline void set_this_qdate_Time_EDIT_Widget_Modified(const QDateTime &datetime)
    {
        Set_widget_modified(true);
    }

    virtual void set_this_qdate_Time_EDIT_Widget_Modified(const QTime &time)
    {
        Set_widget_modified(true);
    }


    virtual inline void clearField()
    {
        reset();
    }


    virtual inline void reset()
    {
        setDate(_startDate);
    }


protected:

    bool _widget_Modified;

    YerithWindowsCommons    *_parent_windows;


private:

    YerithLogger *_logger;

    QPalette _originalPaletteBeforeMissingInformation;

    QDate _startDate;

    QCalendarWidget *_calendarWidget;


};


#endif /* SRC_WIDGETS_YERITH_DATETIME_EDIT_HPP_ */
