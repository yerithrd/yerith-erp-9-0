/*
 * yerith-erp-text-edit.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_WIDGETS_YERITH_TEXT_EDIT_HPP_
#define SRC_WIDGETS_YERITH_TEXT_EDIT_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include "src/utils/yerith-erp-utils.hpp"

#include <QtWidgets/QTextEdit>

class YerithUtils;

class YerithTextEdit:public QTextEdit
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


    inline YerithTextEdit(QWidget *parent = 0)
    :QTextEdit(parent),
     _widget_Modified(false),
     _parent_windows(0),
     _originalPaletteBeforeMissingInformation(palette())
    {
        initializations();
    }


    inline YerithTextEdit(const QString &text,
                          QWidget       *parent)
    :QTextEdit(text, parent),
     _widget_Modified(false),
     _parent_windows(0),
     _originalPaletteBeforeMissingInformation(palette())
    {
        initializations();
    }


    virtual inline ~YerithTextEdit()
    {
    }


    virtual void initializations();


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


    bool checkField();

    void setYerithPOSTextEditDisplayFormat();

    void setVisible(bool visible);

    void clearField();

    void setYerithEnabled(bool enabled);

    QString toPlainTextForLatex() const;

    inline QString toPlainText() const
    {
        return QTextEdit::toPlainText().trimmed();
    }


public slots:

    virtual inline void set_this_text_edit_Widget_Modified()
    {
        Set_widget_modified(true);
    }


protected:

    bool _widget_Modified;

    YerithWindowsCommons    *_parent_windows;


private:

    QPalette _originalPaletteBeforeMissingInformation;
};


#endif /* SRC_WIDGETS_YERITH_TEXT_EDIT_HPP_ */
