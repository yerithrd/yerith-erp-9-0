/*
 * yerith-erp-progress-bar.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-progress-bar.hpp"


#include "src/admin/yerith-erp-admin-windows-commons.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/windows/yerith-erp-window-commons.hpp"


YerithProgressBar::YerithProgressBar(YerithPOSAdminWindowsCommons *aYerithParentAdminWindow,
                                     QString PROGRESS_BAR_TEXT_COLOR_RGB_simple_spec /* = "rgb(0, 255, 70)" */)
:QProgressBar((QWidget *) aYerithParentAdminWindow),
 _setup(false)
{
    setVisible(false);

    QString RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND
				= COLOUR_RGB_STRING_YERITH_FIREBRICK_RED_255_48_48;

    if (0 != aYerithParentAdminWindow)
    {
        QToolBar *aYerithCommonWindowToolBar =
        		aYerithParentAdminWindow->getQMainWindowToolBar();

        if (0 != aYerithCommonWindowToolBar)
        {
            const QColor &aQColor = aYerithCommonWindowToolBar->palette().color(QPalette::Button);

            RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND =
                            QString("%1, %2, %3").arg(QString::number(aQColor.red()),
                                                      QString::number(aQColor.green()),
                                                      QString::number(aQColor.blue()));
        }
    }

    setStyleSheet(QString("QProgressBar "
                          "{text-align: center; "
                          "border: 2px solid white; "
                          "border-radius: 1px; color: %1;}"
                          "QProgressBar::chunk {"
                          "background-color: rgb(%2); "
                          "color: rgb(%3); "
                          "width: 3px;}")
    				.arg(PROGRESS_BAR_TEXT_COLOR_RGB_simple_spec,
                         RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND,
    					 COLOUR_RGB_STRING_YERITH_DARK_GREEN_47_67_67));

    int width = qCeil(((QMainWindow *) parent())->width() / 2.0);

    int X = qCeil(width / 2.0);

    int Y = qCeil(((QMainWindow *) parent())->height() / 2.0);

    setFixedWidth(width);

    move(X, Y);
}


YerithProgressBar::YerithProgressBar(YerithWindowsCommons *aYerithParentWindow,
                                     QString PROGRESS_BAR_TEXT_COLOR_RGB_simple_spec /* '= "rgb(0, 0, 0)" */)
:QProgressBar((QWidget *) aYerithParentWindow),
 _setup(false)
{
    setVisible(false);

    QString RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND
				= COLOUR_RGB_STRING_YERITH_FIREBRICK_RED_255_48_48;

    if (0 != aYerithParentWindow)
    {
        QToolBar *aYerithCommonWindowToolBar =
        		aYerithParentWindow->getQMainWindowToolBar();

        YerithERPWindows *all_windows = YerithUtils::getAllWindows();


        if (0 != all_windows)
        {
            if (aYerithParentWindow == all_windows->_paiementsWindow ||
                aYerithParentWindow == all_windows->_ventesWindow)

            {
                ___FORE_GROUND_STYLESHEET_SPECIFICATION_RGB =
                        COLOUR_RGB_STRING_YERITH_INDIGO_83_0_125;
            }
        }


        if (0 != aYerithCommonWindowToolBar)
        {
            if (___FORE_GROUND_STYLESHEET_SPECIFICATION_RGB.isEmpty())
            {
                const QColor &aQColor =
                        aYerithCommonWindowToolBar->palette().color(QPalette::Button);

                RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND =
                                QString("%1, %2, %3").arg(QString::number(aQColor.red()),
                                                          QString::number(aQColor.green()),
                                                          QString::number(aQColor.blue()));
            }
            else
            {
                RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND =
                    ___FORE_GROUND_STYLESHEET_SPECIFICATION_RGB;
            }
        }
    }

//    QDEBUG_STRING_OUTPUT_2("YerithProgressBar; ___FORE_GROUND_STYLESHEET_SPECIFICATION_RGB",
//                            ___FORE_GROUND_STYLESHEET_SPECIFICATION_RGB);

    setStyleSheet(QString("QProgressBar "
                          "{text-align: center; "
                          "border: 2px solid white; "
                          "border-radius: 1px; color: %1;}"
                          "QProgressBar::chunk {"
                          "background-color: rgb(%2); "
                          "color: rgb(%3); "
                          "width: 3px;}")
    				.arg(PROGRESS_BAR_TEXT_COLOR_RGB_simple_spec,
                         RGB_COLOR_TO_DISPLAY_AT_YERITH_PROGRESS_BAR_BACKGROUND,
    					 COLOUR_RGB_STRING_YERITH_DARK_GREEN_47_67_67));

    int width = qCeil(((QMainWindow *) parent())->width() / 2.0);

    int X = qCeil(width / 2.0);

    int Y = qCeil(((QMainWindow *) parent())->height() / 2.0);

    setFixedWidth(width);

    move(X, Y);
}


YerithProgressBar::YerithProgressBar(YerithWindowsCommons *aYerithParentWindow,
                                     QString FOREGROUND_STYLESHEET_SPECIFICATION_RGB,
                                     QString PROGRESS_BAR_TEXT_COLOR_RGB_simple_spec)
:___FORE_GROUND_STYLESHEET_SPECIFICATION_RGB(FOREGROUND_STYLESHEET_SPECIFICATION_RGB)
{
    YerithProgressBar(aYerithParentWindow,
                      PROGRESS_BAR_TEXT_COLOR_RGB_simple_spec);

    Set_back_ground_stylesheet_specification_AS_QString(FOREGROUND_STYLESHEET_SPECIFICATION_RGB);
}

