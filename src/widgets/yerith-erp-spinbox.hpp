/*
 * yerith-erp-spinbox.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_SPINBOX_HPP_
#define YERITH_SPINBOX_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"


#include <QtWidgets/QDoubleSpinBox>


#include "src/utils/yerith-erp-utils.hpp"

class YerithUtils;

class YerithSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

    inline YerithSpinBox(QWidget *parent = 0)
        :QDoubleSpinBox(parent),
         _widget_Modified(false),
         _parent_windows(0)
    {
        initializations();
    }


    inline ~YerithSpinBox()
    {
    }

    virtual void initializations();

    bool checkField();

    void clearField();

    void displayValue(double intValue);

    inline double valueMultiplyBy(double aValue)
    {
        return value() * aValue;
    }

    void setYerithEnabled(bool enabled);


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

    virtual void set_this_qspiN_box_Widget_Modified(const QString &text)
    {
        Set_widget_modified(true);
    }

    virtual void set_this_qspiN_box_Widget_Modified(double i)
    {
        Set_widget_modified(true);
    }


protected:

    bool _widget_Modified;

    YerithWindowsCommons    *_parent_windows;


private:

    QPalette _originalPaletteBeforeMissingInformation;
};


#endif /* YERITH_SPINBOX_HPP_ */
