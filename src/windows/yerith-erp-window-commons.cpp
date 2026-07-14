/*
 * yerith-erp-window-commons.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */
#include "yerith-erp-window-commons.hpp"


#include "src/process/yerith-erp-process.hpp"

#include "src/utils/print_latex_pdf/yerith-erp-print_yerith_latex_util_pdf.hpp"

#include "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.hpp"

#include "src/widgets/yerith-erp-push-button.hpp"

#include "src/widgets/yerith-erp-select-db-qcheckbox.hpp"

#include <QtWidgets/QSplashScreen>

#include "src/dialogs/yerith-erp-generic-select-db-field-dialog.hpp"

#include "src/users/yerith-erp-user-manager.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/users/yerith-erp-users.hpp"


#include <QtSql/QSqlQuery>

#include <QtCore/QtMath>

#include <QtCore/QProcess>

#include <QtCore/QObject>

#include <QtCore/QTimer>

#include <QtWidgets/QDesktopWidget>


YerithERPWindows *YerithWindowsCommons::_allWindows(0);


uint YerithWindowsCommons::_YERITH_object_UOID__Count = 0;


YerithWindowsCommons   *YerithWindowsCommons::_Previously_Requested___Window_Frame = 0;


YerithWindowsCommons   *YerithWindowsCommons::_next_Requested___Window_Frame = 0;


YerithWindowsCommons   *YerithWindowsCommons::_CURRENTLY_Now_Requested___Window_Frame = 0;


YRIDBRUNTIMEVERIF_QMap  *YerithWindowsCommons::_next_Requested___Window_Frame__TO__CANCEL_REQUEST =
                                                new YRIDBRUNTIMEVERIF_QMap;


YRIDBRUNTIMEVERIF_QMap  *YerithWindowsCommons::____index_TO_WindowFrame =
                                                new YRIDBRUNTIMEVERIF_QMap;




const QStringList YerithWindowsCommons::_ALL_WINDOWS_FILTER_NUMERIC_CONDITIONS =
{
    ">=",

    "<=",

    ">",

    "<",

    "="
};


bool YerithWindowsCommons::USA_flag_English_ACTIVE_now_On(false);


bool YerithWindowsCommons::FRANCE_flag_francais_ACTIVE_now_On(false);



const QIcon YerithWindowsCommons::_Usa_flag_icon_File(":YERITH.JPG");


const QIcon YerithWindowsCommons::_FRANCE_drapeau_icon_File(":YERITH.JPG");


const uint YerithWindowsCommons::CHECKBOX_YERITH_FOR_DB_TABLE_COLUMN_FILTERING_WIDTH_SIZE = 250;



QString YerithWindowsCommons::STRING_MONDAY("lundi");

QString YerithWindowsCommons::STRING_TUESDAY("mardi");

QString YerithWindowsCommons::STRING_WEDNESDAY("mercredi");

QString YerithWindowsCommons::STRING_THURSDAY("jeudi");

QString YerithWindowsCommons::STRING_FRIDAY("vendredi");

QString YerithWindowsCommons::STRING_SATURDAY("samedi");

QString YerithWindowsCommons::STRING_SUNDAY("dimanche");



QString YerithWindowsCommons::_yerithTableView_FROM_WINDOWS_COMMONS_LAST_SELECTED_ROW__db_ID;


QPoint *YerithWindowsCommons::_centerPosition(new QPoint);



YerithWindowsCommons::~YerithWindowsCommons()
{
    if (0 != _yerith_PRINT_UTILITIES_TEX_TABLE)
    {
        delete _yerith_PRINT_UTILITIES_TEX_TABLE;
    }


    _varchar_dbtable_column_name_list.clear();

    _DBFieldNamesToPrintLeftAligned.clear();

    _dbtablecolumnNameToDBColumnIndex.clear();

    _visibleDBColumnNameStrList.clear();

    _visibleQCheckboxs.clear();



    YERITH_DELETE_FREE_POINTER_NOW(_Cancel_MODIFICATION_request_Object);

    YERITH_DELETE_FREE_POINTER_NOW(___Cancel_MODIFICATION_request_Object___Timer);

    YERITH_DELETE_FREE_POINTER_NOW(_WRITE_READ_YERITH_SEMAPHORE_APPLY_USER_SETTING_FILE_PROPERTIES);
}


void YerithWindowsCommons::initializations()
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    connect(YerithUtils::GET_a_yerith_utils_object_Instance_NOW(),
    		SIGNAL(Signal___QFileDialog___currentChanged()),
    		this,
            SLOT(Dummy___showEvent___For___QFILEDialogSignals()));


    connect(YerithUtils::GET_a_yerith_utils_object_Instance_NOW(),
    		SIGNAL(Signal___QFileDialog___directoryEntered()),
    		this,
            SLOT(Dummy___showEvent___For___QFILEDialogSignals()));


    _WRITE_READ_YERITH_SEMAPHORE_APPLY_USER_SETTING_FILE_PROPERTIES = new QSemaphore(1);
}


void YerithWindowsCommons::yerith_hide_columns()
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return;
    }

    unsigned int size = _NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME.size();

    for (unsigned int j = 0; j < size; ++j)
    {
        _yerithTableView_FROM_WINDOWS_COMMONS->hideColumn
        (_dbtablecolumnNameToDBColumnIndex.value
         (_NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME.at(j)));
    }
}


void YerithWindowsCommons::PRINT_OUTPUT_PRINTING_DEBUG_PARAMETERS()
{
    qDebug() << QString("_pageFROM: %1 - _pageTO: %2, | "
                        "_print_table_row_count: %3 | "
                        "_a4paper_printing_position: %4").arg(QString::number
                                                              (_page_from),
                                                              QString::number
                                                              (_page_to),
                                                              QString::number
                                                              (_print_table_row_count),
                                                              _a4paper_printing_position);
}


int YerithWindowsCommons::get_INT_last_selected_row_number()
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return -1;
    }

    return _yerithTableView_FROM_WINDOWS_COMMONS
                ->_map_dbID_TO_yerith_table_view_ROW_NUMBER
                    .value(getLastListerSelectedRow__ID(), -1);
}


bool YerithWindowsCommons::RECONDUCT_current_TableColumnUser__Viewing_Strings()
{
//    QDEBUG_STRING_OUTPUT_2("RECONDUCT_current_TableColumnUser__Viewing_Strings()",
//                            _windowName);

    bool copied_at_leat_ONE = false;

    bool ALREADY_CLEARED_target_map = false;


	QMapIterator<QString, QString> it(__Previous_TO_Reconduct_tableColumnToUserViewString);


	while (it.hasNext())
	{
        if (!ALREADY_CLEARED_target_map)
        {
            YerithDatabaseTableColumn::_tableColumnToUserViewString.clear();

            ALREADY_CLEARED_target_map = true;
        }

		it.next();

        YerithDatabaseTableColumn::_tableColumnToUserViewString
            .insert(it.key(),
                    it.value());

        copied_at_leat_ONE = true;
	}


	return copied_at_leat_ONE;
}


bool YerithWindowsCommons::SAVE_current_TableColumnUser__Viewing_Strings()
{
//    QDEBUG_STRING_OUTPUT_2("SAVE_current_TableColumnUser__Viewing_Strings()",
//                            _windowName);

    bool copied_at_leat_ONE = false;

    bool ALREADY_CLEARED_target_map = false;


	QMapIterator<QString, QString> it(YerithDatabaseTableColumn::_tableColumnToUserViewString);


	while (it.hasNext())
	{
        if (!ALREADY_CLEARED_target_map)
        {
            __Previous_TO_Reconduct_tableColumnToUserViewString.clear();

            ALREADY_CLEARED_target_map = true;
        }

		it.next();

        __Previous_TO_Reconduct_tableColumnToUserViewString
            .insert(it.key(),
                    it.value());

        copied_at_leat_ONE = true;
	}


	return copied_at_leat_ONE;
}


void YerithWindowsCommons::
        YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(QAction *anAction,
                                               bool     aBooleanValue)
{
    _MAP_actions_to_enable_on_positive_tableview_ROW_COUNT__TO__AUTHORIZED_FOR_CURRENT_USER
        .insert(anAction,
                aBooleanValue);

    anAction->setVisible(aBooleanValue);
}


void YerithWindowsCommons::
	setYerithTableView_FROM_WINDOWS_COMMONS
		(const QList <YerithTableView *> &aYerithTableView_FROM_WINDOWS_COMMONS_QLIST)
{
    if (aYerithTableView_FROM_WINDOWS_COMMONS_QLIST.size() <= 0)
    {
        return;
    }

    YerithTableView *curTableView = 0;

    curTableView = aYerithTableView_FROM_WINDOWS_COMMONS_QLIST.at(0);

    setYerithTableView_FROM_WINDOWS_COMMONS(curTableView);


    for (int k = 1; k < aYerithTableView_FROM_WINDOWS_COMMONS_QLIST.size();
            ++k)
    {
        curTableView = aYerithTableView_FROM_WINDOWS_COMMONS_QLIST.at(k);

        if (0 != curTableView)
        {
            connect(curTableView,
                    SIGNAL(clicked(const QModelIndex &)),
                    this,
                    SLOT(setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(const QModelIndex &)));

            connect(curTableView,
                    SIGNAL(pressed(const QModelIndex &)),
                    this,
                    SLOT(setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(const QModelIndex &)));
        }
    }
}


void YerithWindowsCommons::
	setYerithTableView_FROM_WINDOWS_COMMONS(YerithTableView *aYerithTableView_FROM_WINDOWS_COMMONS,
                                                bool a_setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID /* = true */)
{
    if (0 == aYerithTableView_FROM_WINDOWS_COMMONS)
    {
        return;
    }

    _yerithTableView_FROM_WINDOWS_COMMONS = aYerithTableView_FROM_WINDOWS_COMMONS;

    _CURRENT_TABLE_VIEW_font = const_cast<QFont *>(&_yerithTableView_FROM_WINDOWS_COMMONS->font());

    if (a_setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID)
    {
        connect(_yerithTableView_FROM_WINDOWS_COMMONS,
                SIGNAL(clicked(const QModelIndex &)),
                this,
                SLOT(setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(const QModelIndex &)));

        connect(_yerithTableView_FROM_WINDOWS_COMMONS,
                SIGNAL(pressed(const QModelIndex &)),
                this,
                SLOT(setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(const QModelIndex &)));
    }

    if (0 != _yerith_PRINT_UTILITIES_TEX_TABLE)
    {
        _yerith_PRINT_UTILITIES_TEX_TABLE
			->setYerithTableView(_yerithTableView_FROM_WINDOWS_COMMONS);
    }
}


void YerithWindowsCommons::Refresh__STATUS_Languages_Flagship(QAction &action_TRADUIRE_EN_ANGLAIS,
                                                              QAction &action_TRADUIRE_EN_FRANCAIS)
{
    CHANGER_DE_LANGUE__text__TRANSLATION(this);

    action_TRADUIRE_EN_ANGLAIS.setVisible(YerithWindowsCommons::USA_flag_English_ACTIVE_now_On);

    action_TRADUIRE_EN_FRANCAIS.setVisible(YerithWindowsCommons::FRANCE_flag_francais_ACTIVE_now_On);


    setVisible(false);

    setVisible(true);
}


bool YerithWindowsCommons::RESIZE_CHILD_OBJECT(QResizeEvent *event,
                                               QWidget *a_child_widget)
{
    if (0 == a_child_widget)
    {
        return false;
    }

    const QSize &previous_WINDOWS_size = event->oldSize();

    if (previous_WINDOWS_size.width() <= 0
            || previous_WINDOWS_size.height() <= 0)
    {
        return false;
    }

//      QDEBUG_STRING_OUTPUT_1("YerithWindowsCommons::RESIZE_CHILD_OBJECT");
    {
        YerithComboBox *a_combo_box_child_object =
                        dynamic_cast<YerithComboBox *>(a_child_widget);
        if (0 != a_combo_box_child_object)
        {
            YerithUtils::YERITH_resizeEvent(*a_combo_box_child_object,
                                            event->size(),
                                            previous_WINDOWS_size);
            return true;
        }
    }

    {
        YerithLineEdit *a_line_edit_child_object =
                        dynamic_cast<YerithLineEdit *>(a_child_widget);
        if (0 != a_line_edit_child_object)
        {
            YerithUtils::YERITH_resizeEvent(*a_line_edit_child_object,
                                            event->size(),
                                            previous_WINDOWS_size);
            return true;
        }
    }

    {
        YerithPushButton *a_pushbutton_child_object =
                        dynamic_cast<YerithPushButton *>(a_child_widget);
        if (0 != a_pushbutton_child_object)
        {
            YerithUtils::YERITH_resizeEvent(*a_pushbutton_child_object,
                                            event->size(),
                                            previous_WINDOWS_size);
            return true;
        }
    }

    {
        QLabel *a_qlabel_child_object = dynamic_cast<QLabel *>(a_child_widget);
        if (0 != a_qlabel_child_object)
        {
            YerithUtils::YERITH_resizeEvent(*a_qlabel_child_object,
                                            event->size(),
                                            previous_WINDOWS_size);
            return true;
        }
    }

    {
        YerithTableView *a_table_view_child_object =
                        dynamic_cast<YerithTableView *>(a_child_widget);
        if (0 != a_table_view_child_object)
        {
            a_table_view_child_object->YERITH_resizeEvent(event);
            return true;
        }
    }

    return true;
}


void YerithWindowsCommons::resizeEvent(QResizeEvent *event)
{
//      QDEBUG_STRING_OUTPUT_1("YerithWindowsCommons::resizeEvent");


    Handle__Events____Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING
        (event,
         false,
         "QResizeEvent");



    const QSize &previous_size = event->oldSize();

    if (previous_size.width() <= 0 || previous_size.height() <= 0)
    {
        return;
    }

    QList<QObject *> child_objects = children();

    QList<QObject *> grand_child_widgets;


    QWidget *a_child_widget = 0;

    QWidget *a_grand_child_widget = 0;


    QObject *a_child_object = 0;

    QObject *a_grand_child_object = 0;


    for (uint k = 0; k < child_objects.size(); ++k)
    {
        a_child_object = child_objects.at(k);

        if (0 == a_child_object)
        {
            continue;
        }

        a_child_widget = dynamic_cast<QWidget *>(a_child_object);

        if (0 != a_child_widget)
        {
            grand_child_widgets = a_child_widget->children();

            for (uint j = 0; j < grand_child_widgets.size(); ++j)
            {
                a_grand_child_object = grand_child_widgets.at(j);

                if (0 != a_grand_child_object)
                {
//                                      QDEBUG_STRING_OUTPUT_1("a_grand_child_object");

                    a_grand_child_widget =
                                    dynamic_cast<QWidget *>(a_grand_child_object);

                    if (0 != a_grand_child_widget)
                    {
//                                              QDEBUG_STRING_OUTPUT_1("a_grand_child_widget");

                        RESIZE_CHILD_OBJECT(event, a_grand_child_widget);
                    }
                }
            }
        }
    }
}


void YerithWindowsCommons::YERITH_ERP_WRAPPER_QACTION_SET_ENABLED_AUTOMATIC_CONSTRUCTOR_ONLY()
{
    QAction *current_qaction = 0;

    for (uint i = 0;
         i < _list_actions_to_enable_on_positive_tableview_ROW_COUNT.size();
         ++i)
    {
        current_qaction = _list_actions_to_enable_on_positive_tableview_ROW_COUNT.at(i);

        if (0 != current_qaction)
        {
            YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(current_qaction, false);
        }
    }
}


void YerithWindowsCommons::
	APPLY_USER_LOCAL_SETTINGS_PARAMETERS_TABLE_COLUMN_ORDER_from_settings_parameters
		(const QString &pageTableColumnOrder_STRING)
{
    _CURRENTLY_APPLYING_USER_FILE_SETTING_TABLE_COLUMN_ORDER = true;


    set_PARAMETER_TABLE_COLUMN_ORDER(pageTableColumnOrder_STRING);


    QStringList print_table_column_order = pageTableColumnOrder_STRING.split(";");


    if (print_table_column_order.size() > 0)
    {
        YerithTableView * a_yerith_table_view = GET_YERITH_TABLE_VIEW();

        if (0 != a_yerith_table_view)
        {
            QHeaderView *header_view = a_yerith_table_view->horizontalHeader();

            if (0 != header_view)
            {
                _visibleDBColumnNameStrList.clear();


                int a_logical_index = 0;

                QStringList a_tmp_list;


                int saved_VISUAL_INDEX;

                QString headerColumnData;


                for (uint k = 0; k < print_table_column_order.size(); ++k)
                {
                    if (!print_table_column_order.at(k).isEmpty())
                    {
                        a_tmp_list =
                                        print_table_column_order.at(k).split(":");

//                                              QDEBUG_QSTRINGLIST_OUTPUT("a_tmp_list", a_tmp_list);

                        headerColumnData = a_tmp_list.at(0);

                        _visibleDBColumnNameStrList.append(headerColumnData);

                        saved_VISUAL_INDEX = a_tmp_list.at(1).toInt();

                        a_logical_index =
                                        _dbtablecolumnNameToDBColumnIndex.value
                                        (headerColumnData);

//                                              QDEBUG_STRING_OUTPUT_1(QString("a_logical_index: %1, headerColumnData: %2, "
//                                                                                                         "current visualIndex: %3, "
//                                                                                                         "saved_VISUAL_INDEX: %4")
//                                                                                                      .arg(QString::number(a_logical_index),
//                                                                                                               headerColumnData,
//                                                                                                               QString::number(header_view->visualIndex(a_logical_index)),
//                                                                                                               QString::number(saved_VISUAL_INDEX)));

                        header_view->moveSection(header_view->visualIndex
                                                 (a_logical_index),
                                                 saved_VISUAL_INDEX);
                    }
                }
            }
        }
    }

    _CURRENTLY_APPLYING_USER_FILE_SETTING_TABLE_COLUMN_ORDER = false;
}


void YerithWindowsCommons::APPLY_USER_LOCAL_SETTINGS_PARAMETERS_QTABLEWIDGET(YerithWindowsCommons &a_window)
{
    _WRITE_READ_YERITH_SEMAPHORE_APPLY_USER_SETTING_FILE_PROPERTIES->acquire(1);

    YerithERPWindows *allWindows = YerithUtils::getAllWindows();

    if (0 != allWindows)
    {
        YerithPOSUser *aUser = allWindows->getUser();

        if (0 != aUser)
        {
            allWindows->_impressionDeDocumentDialog->_current_window_to_print = this;

            aUser->read_user_personal_PRINTING_PARAMETER_settings_QTABLEWIDGET(&a_window);

            QString yerith_qt_THIS_object_name = YERITH_QT_OBJECT_NAME(this);

            QString pageFrom_STRING =
                            aUser->get_PRINTING_PARAMETER_VALUE_page_from
                            (yerith_qt_THIS_object_name);

            QString pageTo_STRING =
                            aUser->get_PRINTING_PARAMETER_VALUE_page_to
                            (yerith_qt_THIS_object_name);

            QString pageTABLE_FONT_SIZE_STRING =
                            aUser->get_PARAMETER_VALUE_table_font_size
                            (yerith_qt_THIS_object_name);

            QString pageTablePrintRowCount_STRING =
                            aUser->get_PRINTING_PARAMETER_VALUE_print_table_row_count
                            (yerith_qt_THIS_object_name);

            QString pageTableRowCount_STRING =
                            aUser->get_PRINTING_PARAMETER_VALUE_USERSQL_table_row_count
                            (yerith_qt_THIS_object_name);

            QString pageTableColumnOrder_STRING =
                            aUser->get_PARAMETER_VALUE_table_column_order
                            (yerith_qt_THIS_object_name);

            QString pagePagePrinting_STRING =
                            aUser->get_PRINTING_PARAMETER_VALUE_printing_position
                            (yerith_qt_THIS_object_name);

            if (!pageFrom_STRING.isEmpty())
            {
                _page_from = pageFrom_STRING.toInt();
            }

            if (!pageTo_STRING.isEmpty())
            {
                _page_to = pageTo_STRING.toInt();
            }

            if (!pageTABLE_FONT_SIZE_STRING.isEmpty())
            {
            	_TABLE_FONT_SIZE = pageTABLE_FONT_SIZE_STRING.toUInt();

            	if (_TABLE_FONT_SIZE <= 4)
            	{
            		_TABLE_FONT_SIZE = 5;
            	}

            	if (0 != _CURRENT_TABLE_VIEW_font)
            	{
            		_CURRENT_TABLE_VIEW_font->setPointSize(_TABLE_FONT_SIZE);
            	}
            }

            if (!pageTableRowCount_STRING.isEmpty())
            {
                _USERSQL_table_row_count = pageTableRowCount_STRING.toUInt();

                if (0 != _QLINEEDIT_nombre_de_lignes_par_page)
                {
                    _QLINEEDIT_nombre_de_lignes_par_page->setText(pageTableRowCount_STRING);
                }
            }

            if (!pageTablePrintRowCount_STRING.isEmpty())
            {
                _print_table_row_count =
                                pageTablePrintRowCount_STRING.toUInt();
            }



            YerithAdminListerWindow *yr_admin_lister_window =
            		dynamic_cast<YerithAdminListerWindow *>(this);

            if (0 != yr_admin_lister_window)
            {
            	//I REINITIALIZE qtableview colum ordering
            	//since this is a new table view
            	_visibleDBColumnNameStrList.clear();
            }



            if (!pageTableColumnOrder_STRING.isEmpty())
            {
                APPLY_USER_LOCAL_SETTINGS_PARAMETERS_TABLE_COLUMN_ORDER_from_settings_parameters(pageTableColumnOrder_STRING);
            }

            if (!pagePagePrinting_STRING.isEmpty())
            {
                _a4paper_printing_position = pagePagePrinting_STRING;
            }
        }
    }

    _WRITE_READ_YERITH_SEMAPHORE_APPLY_USER_SETTING_FILE_PROPERTIES->release(1);
}


void YerithWindowsCommons::APPLY_USER_LOCAL_SETTINGS_PARAMETERS()
{
    _WRITE_READ_YERITH_SEMAPHORE_APPLY_USER_SETTING_FILE_PROPERTIES->acquire(1);

    YerithERPWindows *allWindows = YerithUtils::getAllWindows();

    if (0 != allWindows)
    {
        YerithPOSUser *aUser = allWindows->getUser();

        if (0 != aUser)
        {
            allWindows->_impressionDeDocumentDialog->_current_window_to_print = this;


            aUser->read_user_personal_PRINTING_PARAMETER_settings(this);


            QString yerith_qt_THIS_object_name = YERITH_QT_OBJECT_NAME(this);


            QString pageFrom_STRING =
            		aUser->get_PRINTING_PARAMETER_VALUE_page_from
						(yerith_qt_THIS_object_name);

            QString pageTo_STRING =
            		aUser->get_PRINTING_PARAMETER_VALUE_page_to
						(yerith_qt_THIS_object_name);

            QString pageTABLE_FONT_SIZE_STRING =
            		aUser->get_PARAMETER_VALUE_table_font_size
						(yerith_qt_THIS_object_name);

            QString pageTablePrintRowCount_STRING =
            		aUser->get_PRINTING_PARAMETER_VALUE_print_table_row_count
						(yerith_qt_THIS_object_name);

            QString pageTableRowCount_STRING =
            		aUser->get_PRINTING_PARAMETER_VALUE_USERSQL_table_row_count
						(yerith_qt_THIS_object_name);

            QString pageTableColumnOrder_STRING =
            		aUser->get_PARAMETER_VALUE_table_column_order
						(yerith_qt_THIS_object_name);

            QString pagePagePrinting_STRING =
            		aUser->get_PRINTING_PARAMETER_VALUE_printing_position
						(yerith_qt_THIS_object_name);


            if (!pageFrom_STRING.isEmpty())
            {
                _page_from = pageFrom_STRING.toInt();
            }


            if (!pageTo_STRING.isEmpty())
            {
                _page_to = pageTo_STRING.toInt();
            }


            if (!pageTABLE_FONT_SIZE_STRING.isEmpty())
            {
            	_TABLE_FONT_SIZE = pageTABLE_FONT_SIZE_STRING.toUInt();

            	if (_TABLE_FONT_SIZE <= 4)
            	{
            		_TABLE_FONT_SIZE = 5;
            	}

            	if (0 != _yerithTableView_FROM_WINDOWS_COMMONS)
            	{
            		_CURRENT_TABLE_VIEW_font->setPointSize(_TABLE_FONT_SIZE);
            	}
            }


            if (!pageTableRowCount_STRING.isEmpty())
            {
                _USERSQL_table_row_count = pageTableRowCount_STRING.toUInt();

                if (0 != _QLINEEDIT_nombre_de_lignes_par_page)
                {
                    _QLINEEDIT_nombre_de_lignes_par_page
						->setText(pageTableRowCount_STRING);
                }
            }


            if (!pageTablePrintRowCount_STRING.isEmpty())
            {
                _print_table_row_count =
                                pageTablePrintRowCount_STRING.toUInt();
            }


            YerithAdminListerWindow *yr_admin_lister_window =
            		dynamic_cast<YerithAdminListerWindow *>(this);

            if (0 != yr_admin_lister_window)
            {
            	//I REINITIALIZE qtableview colum ordering
            	//since this is a new table view
            	_visibleDBColumnNameStrList.clear();
            }


            if (!pageTableColumnOrder_STRING.isEmpty())
            {
                APPLY_USER_LOCAL_SETTINGS_PARAMETERS_TABLE_COLUMN_ORDER_from_settings_parameters
					(pageTableColumnOrder_STRING);
            }


            if (!pagePagePrinting_STRING.isEmpty())
            {
                _a4paper_printing_position = pagePagePrinting_STRING;
            }

            if (0 != _yerithTableView_FROM_WINDOWS_COMMONS)
            {
                tableView_show_or_hide_columns(*_yerithTableView_FROM_WINDOWS_COMMONS);
            }
        }
    }

    _WRITE_READ_YERITH_SEMAPHORE_APPLY_USER_SETTING_FILE_PROPERTIES->release(1);
}


void YerithWindowsCommons::setLeftAligned_FOR_YERITH_PDF_LATEX_PRINTING(const
                                                                        QString &
                                                                        dbtableColumnString)
{
    int columnIndexStocksID =
                    _dbtablecolumnNameToDBColumnIndex.value(dbtableColumnString);

    _DBFieldNamesToPrintLeftAligned.insert(columnIndexStocksID);

    _DBFieldNamesToPrintCenterAligned.remove(columnIndexStocksID);

    _DBFieldNamesToPrintRightAligned.remove(columnIndexStocksID);
}


void YerithWindowsCommons::setLeftAligned_FOR_YERITH_PDF_LATEX_PRINTING(int
                                                                        dbtableColumnIndex)
{
    _DBFieldNamesToPrintLeftAligned.insert(dbtableColumnIndex);

    _DBFieldNamesToPrintCenterAligned.remove(dbtableColumnIndex);

    _DBFieldNamesToPrintRightAligned.remove(dbtableColumnIndex);
}


void YerithWindowsCommons::setCenterAligned_FOR_YERITH_PDF_LATEX_PRINTING(const
                                                                          QString
                                                                          &
                                                                          dbtableColumnString)
{
    int columnIndexStocksID =
                    _dbtablecolumnNameToDBColumnIndex.value(dbtableColumnString);

    _DBFieldNamesToPrintCenterAligned.insert(columnIndexStocksID);

    _DBFieldNamesToPrintLeftAligned.remove(columnIndexStocksID);

    _DBFieldNamesToPrintRightAligned.remove(columnIndexStocksID);
}


void YerithWindowsCommons::setCenterAligned_FOR_YERITH_PDF_LATEX_PRINTING(int
                                                                          dbtableColumnIndex)
{
    _DBFieldNamesToPrintCenterAligned.insert(dbtableColumnIndex);

    _DBFieldNamesToPrintLeftAligned.remove(dbtableColumnIndex);

    _DBFieldNamesToPrintRightAligned.remove(dbtableColumnIndex);
}


void YerithWindowsCommons::setRightAligned_FOR_YERITH_PDF_LATEX_PRINTING(const
                                                                         QString &
                                                                         dbtableColumnString)
{
    int columnIndexStocksID =
                    _dbtablecolumnNameToDBColumnIndex.value(dbtableColumnString);

    _DBFieldNamesToPrintRightAligned.insert(columnIndexStocksID);

    _DBFieldNamesToPrintLeftAligned.remove(columnIndexStocksID);

    _DBFieldNamesToPrintCenterAligned.remove(columnIndexStocksID);
}


void YerithWindowsCommons::setRightAligned_FOR_YERITH_PDF_LATEX_PRINTING(int
                                                                         dbtableColumnIndex)
{
    _DBFieldNamesToPrintRightAligned.insert(dbtableColumnIndex);

    _DBFieldNamesToPrintLeftAligned.remove(dbtableColumnIndex);

    _DBFieldNamesToPrintCenterAligned.remove(dbtableColumnIndex);
}


void YerithWindowsCommons::on_print_actions_visibility_SET(bool isVisible)
{
    QAction *a_current_action = 0;

    QSetIterator <
    QAction * >a_set_iterator(_ACTIONS_TO_DISABLE_WHEN_NOT_PRINT_ACTION);

    while (a_set_iterator.hasNext())
    {
        a_current_action = a_set_iterator.next();

        if (0 != a_current_action)
        {
            a_current_action->setVisible(isVisible);
        }
    }
}


void YerithWindowsCommons::enableResizing()
{
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    setMinimumSize(width(), height());
}


void YerithWindowsCommons::mySetupUi(QMainWindow *aWindow)
{
    aWindow->setFixedSize(aWindow->width(), aWindow->height());
    aWindow->move(*_centerPosition);

    aWindow->setWindowTitle(QString("%1[*]")
                              .arg(getWindowName()));

    aWindow->setMouseTracking(true);


    _YERITH_object_UOID = YerithWindowsCommons::Yerith___generate____YERITH_object_UOID();


    _Cancel_MODIFICATION_request_Object =
                new YerithERPCancelModificationTimingObject(_allWindows,
                                                            this);


    ___Cancel_MODIFICATION_request_Object___Timer = new QTimer(this);


    if (YerithUtils::instanceOf__QMainWindow(this) &&
        0 != getQMainWindowToolBar())
    {
        connect(getQMainWindowToolBar(),
                SIGNAL(visibilityChanged(bool)),
                this,
                SLOT(DONT___Check__BLANK_Timing_Of_WindowFRAME(bool)));
    }


    connect(___Cancel_MODIFICATION_request_Object___Timer,
            SIGNAL(timeout()),
            this,
            SLOT(Check__BLANK_Timing_Of_WindowFRAME()));

        //WE start this timer only for window inerting-creating frame.
        //___Cancel_MODIFICATION_request_Object___Timer->start(2000);
}


bool
YerithWindowsCommons::SQL_UPDATE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW
(QSqlRecord &resultRecord_IN)
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
//              QDEBUG_STRING_OUTPUT_2("YerithWindowsCommons::SQL_UPDATE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW",
//                              QString("There is no SQL TABLE VIEW associated !"));

        return false;
    }

    int
    lastSelectRecord_ROW_NUMBER = get_INT_last_selected_row_number();

    QDEBUG_STRING_OUTPUT_2_N("lastSelectRecord_ROW_NUMBER", lastSelectRecord_ROW_NUMBER);

    YerithSqlTableModel *
    yerithTableViewSQL_TABLE_MODEL =
                    YerithERPWindows::getSqlTableModelFromName
                    (_yerithTableView_FROM_WINDOWS_COMMONS->getSqlTableName());

    if (0 == yerithTableViewSQL_TABLE_MODEL)
    {
              QDEBUG_STRING_OUTPUT_2("YerithWindowsCommons::SQL_UPDATE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW",
                              QString("There is no SQL TABLE MODEL for table view: %1")
                                      .arg(_yerithTableView_FROM_WINDOWS_COMMONS->getSqlTableName()));

        return false;
    }
    else
    {
    	_yerithTableView_FROM_WINDOWS_COMMONS->
    		construire_le_MAPPING_ORIGINAL_db_ID_VERS_db_row_Nr(*yerithTableViewSQL_TABLE_MODEL);
    }

      QDEBUG_STRING_OUTPUT_1(QString("row number: %1, db ID: %2")
                                                              .arg(QString::number(lastSelectRecord_ROW_NUMBER),
                                                                       GET_SQL_RECORD_DATA(resultRecord_IN,
                                                                                           YerithDatabaseTableColumn::ID)));
    QString db_ID = _yerithTableView_FROM_WINDOWS_COMMONS
    					->_MAP_lastSelected_Row__TO__DB_ID
							.value(QString::number(lastSelectRecord_ROW_NUMBER));


    int dbtableOriginalRowID = _yerithTableView_FROM_WINDOWS_COMMONS
    								->_MAP_ORIGINAL_NON_FILTERED_DB_ID__TO__ORIGINAL_DB_ROW
										.value(db_ID.toInt());

//      QDEBUG_STRING_OUTPUT_2("db_ID <--> db_ROW", QString("%1 <--> %2")
//                                                                      .arg(db_ID,
//                                                                               QString::number(dbtableOriginalRowID)));

    bool success = yerithTableViewSQL_TABLE_MODEL
    					->updateRecord(dbtableOriginalRowID,
                                       resultRecord_IN,
									   "src/windows/yerith-erp-window-commons.cpp",
									   830,
									   db_ID);

//      QDEBUG_STRING_OUTPUT_2(QString("update of SQL TABLE VIEW: %1")
//                                                              .arg(_yerithTableView_FROM_WINDOWS_COMMONS->getSqlTableName()),
//                                                      BOOL_TO_STRING(success));

    return success;
}


bool YerithWindowsCommons::SQL_QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW(QSqlRecord &resultRecord_IN_OUT)
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return false;
    }

    QString QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW_QUERY_STRING =
                QString("select * from %1 where %2 = '%3'")
                    .arg(_yerithTableView_FROM_WINDOWS_COMMONS->getSqlTableName(),
                         YerithDatabaseTableColumn::ID,
                         YerithWindowsCommons::get_last_lister_selected_row_db_ID());

//      QDEBUG_STRING_OUTPUT_2("QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW_QUERY_STRING",
//                      QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW_QUERY_STRING);

    QSqlQuery query;

    bool success = YerithUtils::execQuery(query,
                                          QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW_QUERY_STRING);

    if (success && query.next())
    {
        resultRecord_IN_OUT = query.record();

//              QDEBUG_STRING_OUTPUT_2("ID", GET_SQL_RECORD_DATA(resultRecord_IN_OUT, YerithDatabaseTableColumn::ID));

        return true;
    }

    return false;
}


bool YerithWindowsCommons::SQL_DELETE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW()
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return false;
    }

    QString
    REMOVE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW_QUERY_STRING(QString
                                                            ("DELETE FROM %1 WHERE %2 = '%3'").
                                                            arg
                                                            (_yerithTableView_FROM_WINDOWS_COMMONS->
                                                             getSqlTableName
                                                             (),
                                                             YerithDatabaseTableColumn::
                                                             ID,
                                                             YerithWindowsCommons::
                                                             get_last_lister_selected_row_db_ID
                                                             ()));

    return
                    YerithUtils::execQuery
                    (REMOVE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW_QUERY_STRING);
}


void YerithWindowsCommons::set_PARAMETER_TABLE_COLUMN_ORDER()
{
	if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
	{
		return ;
	}

    QHeaderView *a_current_print_table_header_view =
                    _yerithTableView_FROM_WINDOWS_COMMONS->horizontalHeader();

    if (0 == a_current_print_table_header_view)
    {
        return;
    }

    _table_COLUMN_ORDER.clear();


    QStringList yerithTableView_model_raw_visible_headers =
                    _yerithTableView_FROM_WINDOWS_COMMONS->getTableModelRawHeaders();

//      QDEBUG_QSTRINGLIST_OUTPUT("_yerithTableView_model_raw_visible_headers",
//                                                        _yerithTableView_model_raw_visible_headers);

    QString headerColumnData;

    for (uint i = 0; i < yerithTableView_model_raw_visible_headers.size(); ++i)
    {
        headerColumnData = yerithTableView_model_raw_visible_headers.at(i);

        if (!headerColumnData.isEmpty())
        {
//                      QDEBUG_STRING_OUTPUT_2("headerColumnData", headerColumnData);

            if (_visibleDBColumnNameStrList.contains(headerColumnData))
            {
                _table_COLUMN_ORDER.append(QString("%1:%2;").arg
                                           (headerColumnData,
                                            QString::number
                                            (a_current_print_table_header_view->
                                             visualIndex(i))));
            }
        }
    }

//      QDEBUG_STRING_OUTPUT_2("headerColumnData", headerColumnData);
}


void YerithWindowsCommons::incrementFontSize__OF_TABLE()
{
	if (0 != _yerithTableView_FROM_WINDOWS_COMMONS &&
		0 != _CURRENT_TABLE_VIEW_font)
	{
		_TABLE_FONT_SIZE = _CURRENT_TABLE_VIEW_font->pointSize();

		++_TABLE_FONT_SIZE;

		_CURRENT_TABLE_VIEW_font->setPointSize(_TABLE_FONT_SIZE);

		//QDEBUG_STRING_OUTPUT_2_N("incrementFontSize__OF_TABLE, _TABLE_FONT_SIZE",
		//						  _TABLE_FONT_SIZE);

		_yerithTableView_FROM_WINDOWS_COMMONS->hide();

		_yerithTableView_FROM_WINDOWS_COMMONS->resizeColumnsToContents();

		_yerithTableView_FROM_WINDOWS_COMMONS->show();

        YerithERPWindows *allWindows = YerithUtils::getAllWindows();

        YR_SAVE_USER_SETTINGS;
	}
}


void YerithWindowsCommons::decrementFontSize__OF_TABLE()
{
	if (0 != _yerithTableView_FROM_WINDOWS_COMMONS &&
		0 != _CURRENT_TABLE_VIEW_font)
	{
		_TABLE_FONT_SIZE = _CURRENT_TABLE_VIEW_font->pointSize();

		if (_TABLE_FONT_SIZE > 5)
		{
			--_TABLE_FONT_SIZE;

			_CURRENT_TABLE_VIEW_font->setPointSize(_TABLE_FONT_SIZE);

			_yerithTableView_FROM_WINDOWS_COMMONS->hide();

			_yerithTableView_FROM_WINDOWS_COMMONS->resizeColumnsToContents();

			_yerithTableView_FROM_WINDOWS_COMMONS->show();

            YerithERPWindows *allWindows = YerithUtils::getAllWindows();

            YR_SAVE_USER_SETTINGS;
		}
	}
}


void YerithWindowsCommons::
		CLOSE_SELECT_EXPORT_DB_DIALOG(YerithSqlTableModel 			*aSqlTableModel /* = 0 */,
									  YerithTableViewWITHpagination *a_table_view_to_list_show /* = 0 */)
{
	if (0 != _selectExportDBQDialog)
	{
		_selectExportDBQDialog->close();
	}
}


void YerithWindowsCommons::selectionner_champs_db_visibles(bool             SETUP_DIALOG_BOX_GEOMETRY,
														   bool             CHARGES_FINANCIERES_WINDOW,
														   QList<QString>   &CHARGES_FINANCIERES_WINDOW_Db_ColumnS,
														   QList<QString>   &CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STRS)
{
	if (0 != _selectExportDBQDialog)
	{
		if (0 != _selectExportDBQDialog->_associatedWindow)
		{
			YerithTableView *a_table_view =
					_selectExportDBQDialog->_associatedWindow->GET_YERITH_TABLE_VIEW();

			if (0 != a_table_view)
			{
				QString ASSOCIATED_qsql_database = a_table_view->getSqlTableName();

				delete _selectExportDBQDialog;

				_db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName.clear();

				setup_select_configure_dbcolumn(ASSOCIATED_qsql_database);
			}
		}
	}


	if (_visibleDBColumnNameStrList.size() >= 0)
    {
        _visibleQCheckboxs.clear();
        _visibleQCheckboxs.resize(_visibleDBColumnNameStrList.size());
    }


    SAVE_current_TableColumnUser__Viewing_Strings();


    QString aDBColumnName;

    QString aDBColumnName_VIEW_STRING;

    for (unsigned k = 0; k < _dbtablecolumnNameToDBColumnIndex.size(); ++k)
    {
        aDBColumnName = _dbtablecolumnNameToDBColumnIndex.key(k);

        if (_NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME.contains(aDBColumnName))
        {
            continue;
        }


        RECONDUCT_current_TableColumnUser__Viewing_Strings();


        if (! YerithERPConfig::SHOW_DATABASE_RAW)
        {
        	if (CHARGES_FINANCIERES_WINDOW)
        	{
                if (CHARGES_FINANCIERES_WINDOW_Db_ColumnS.size()
                        == CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STRS.size() &&

                    !CHARGES_FINANCIERES_WINDOW_Db_ColumnS.empty() &&

                    !CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STRS.empty())
                {
                    for (uint k = 0; k < CHARGES_FINANCIERES_WINDOW_Db_ColumnS.size(); ++k)
                    {
                        YerithDatabaseTableColumn::_tableColumnToUserViewString
                            .insert(CHARGES_FINANCIERES_WINDOW_Db_ColumnS.at(k),
                                    CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STRS.at(k));
                    }
                }
        	}

            aDBColumnName_VIEW_STRING =
                            YERITH_DATABASE_TABLE_COLUMN_TO_USER_VIEW_STRING(aDBColumnName);
        }
        else
        {
            aDBColumnName_VIEW_STRING = aDBColumnName;
        }


        if (!aDBColumnName_VIEW_STRING.isEmpty())
        {
            _db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName
				.insert(aDBColumnName_VIEW_STRING,
						aDBColumnName);
        }
    }


    //A QMAP AUTOMATICALLY SORT ITS KEYS !
    QStringList all_dbfieldColumnName_IN_ALPHABETIC_ORDER
					(_db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName.keys());


    if (SETUP_DIALOG_BOX_GEOMETRY)
    {
    	YerithSelectDBQCheckBox *aQCheckBox = 0;

    	for (unsigned k = 0; k < all_dbfieldColumnName_IN_ALPHABETIC_ORDER.size();
    			++k)
    	{
    		aQCheckBox = new YerithSelectDBQCheckBox(_selectExportDBQDialog,
    												 &_visibleDBColumnNameStrList);


    		aDBColumnName_VIEW_STRING = all_dbfieldColumnName_IN_ALPHABETIC_ORDER.at(k);

    		aDBColumnName =
    				_db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName
						.value(aDBColumnName_VIEW_STRING);

    		aQCheckBox->setObjectName(aDBColumnName);

    		aQCheckBox->setGeometry(QRect(getDialogBox_Xn_coordinate(k),
    								getDialogBox_Yn_coordinate(k),
									YerithWindowsCommons::CHECKBOX_YERITH_FOR_DB_TABLE_COLUMN_FILTERING_WIDTH_SIZE,
									25));

    		aQCheckBox->setText(aDBColumnName_VIEW_STRING);

    		if (_visibleDBColumnNameStrList.contains(aDBColumnName))
    		{
    			aQCheckBox->setChecked(true);
    		}

    		connect(aQCheckBox,
    				SIGNAL(clicked(bool)),
					aQCheckBox,
					SLOT(handle_visible_db_field_checkBox(bool)));

    		_visibleQCheckboxs.append(aQCheckBox);
    	}

    	_selectExportDBQDialog
			->setWindowTitle(QObject::tr("%1[*] - sélectionner des colones "
    									 "visibles ('%2' colones)")
								.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
									 QString::number(all_dbfieldColumnName_IN_ALPHABETIC_ORDER.size())));

    	_selectExportDBQDialog
			->setFixedSize(getDialogBox_LONGUEUR(all_dbfieldColumnName_IN_ALPHABETIC_ORDER.size()),
												 382.5);

    	_selectExportDBQDialog->showAsModalDialogWithParent(*this);
    }
}


void YerithWindowsCommons::selectionner_champs_db_visibles(bool     SETUP_DIALOG_BOX_GEOMETRY /* = true */,
														   bool     CHARGES_FINANCIERES_WINDOW /* = false */,
														   QString  CHARGES_FINANCIERES_WINDOW_Db_Column /* = YerithUtils::EMPTY_STRING*/,
														   QString  CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STR /* = YerithUtils::EMPTY_STRING*/)
{
	if (0 != _selectExportDBQDialog)
	{
		if (0 != _selectExportDBQDialog->_associatedWindow)
		{
			YerithTableView *a_table_view =
					_selectExportDBQDialog->_associatedWindow->GET_YERITH_TABLE_VIEW();

			if (0 != a_table_view)
			{
				QString ASSOCIATED_qsql_database = a_table_view->getSqlTableName();

				delete _selectExportDBQDialog;

				_db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName.clear();

				setup_select_configure_dbcolumn(ASSOCIATED_qsql_database);
			}
		}
	}


	if (_visibleDBColumnNameStrList.size() >= 0)
    {
        _visibleQCheckboxs.clear();
        _visibleQCheckboxs.resize(_visibleDBColumnNameStrList.size());
    }


    SAVE_current_TableColumnUser__Viewing_Strings();


    QString aDBColumnName;

    QString aDBColumnName_VIEW_STRING;

    for (unsigned k = 0; k < _dbtablecolumnNameToDBColumnIndex.size(); ++k)
    {
        aDBColumnName = _dbtablecolumnNameToDBColumnIndex.key(k);

        if (_NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME.contains(aDBColumnName))
        {
            continue;
        }


        RECONDUCT_current_TableColumnUser__Viewing_Strings();


        if (! YerithERPConfig::SHOW_DATABASE_RAW)
        {
        	if (CHARGES_FINANCIERES_WINDOW)
        	{
                if (!CHARGES_FINANCIERES_WINDOW_Db_Column.isEmpty() &&
                    !CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STR.isEmpty())
                {
                    YerithDatabaseTableColumn::_tableColumnToUserViewString
                        .insert(CHARGES_FINANCIERES_WINDOW_Db_Column,
                                CHARGES_FINANCIERES_WINDOW_Column_Custom_Viewing_STR);
                }
        	}
        	else
        	{
                YerithDatabaseTableColumn::_tableColumnToUserViewString
                    .insert(YerithDatabaseTableColumn::CATEGORIE ,
                            QObject::tr("Catégorie"));
        	}

            aDBColumnName_VIEW_STRING =
                            YERITH_DATABASE_TABLE_COLUMN_TO_USER_VIEW_STRING(aDBColumnName);
        }
        else
        {
            aDBColumnName_VIEW_STRING = aDBColumnName;
        }


        if (!aDBColumnName_VIEW_STRING.isEmpty())
        {
            _db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName
				.insert(aDBColumnName_VIEW_STRING,
						aDBColumnName);
        }
    }


    //A QMAP AUTOMATICALLY SORT ITS KEYS !
    QStringList all_dbfieldColumnName_IN_ALPHABETIC_ORDER
					(_db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName.keys());


    if (SETUP_DIALOG_BOX_GEOMETRY)
    {
    	YerithSelectDBQCheckBox *aQCheckBox = 0;

    	for (unsigned k = 0; k < all_dbfieldColumnName_IN_ALPHABETIC_ORDER.size();
    			++k)
    	{
    		aQCheckBox = new YerithSelectDBQCheckBox(_selectExportDBQDialog,
    												 &_visibleDBColumnNameStrList);


    		aDBColumnName_VIEW_STRING = all_dbfieldColumnName_IN_ALPHABETIC_ORDER.at(k);

    		aDBColumnName =
    				_db_VIEW_STRING_ALPHABETIC_ORDER_To_dbtablecolumnName
						.value(aDBColumnName_VIEW_STRING);

    		aQCheckBox->setObjectName(aDBColumnName);

    		aQCheckBox->setGeometry(QRect(getDialogBox_Xn_coordinate(k),
    								getDialogBox_Yn_coordinate(k),
									YerithWindowsCommons::CHECKBOX_YERITH_FOR_DB_TABLE_COLUMN_FILTERING_WIDTH_SIZE,
									25));

    		aQCheckBox->setText(aDBColumnName_VIEW_STRING);

    		if (_visibleDBColumnNameStrList.contains(aDBColumnName))
    		{
    			aQCheckBox->setChecked(true);
    		}

    		connect(aQCheckBox,
    				SIGNAL(clicked(bool)),
					aQCheckBox,
					SLOT(handle_visible_db_field_checkBox(bool)));

    		_visibleQCheckboxs.append(aQCheckBox);
    	}

    	_selectExportDBQDialog
			->setWindowTitle(QObject::tr("%1[*] - sélectionner des colones "
    									 "visibles ('%2' colones)")
								.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
									 QString::number(all_dbfieldColumnName_IN_ALPHABETIC_ORDER.size())));

    	_selectExportDBQDialog
			->setFixedSize(getDialogBox_LONGUEUR(all_dbfieldColumnName_IN_ALPHABETIC_ORDER.size()),
												 382.5);

    	_selectExportDBQDialog->showAsModalDialogWithParent(*this);
    }
}


void YerithWindowsCommons::handle_some_actions_tools_enabled()
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return;
    }

    bool enable_action = false;

    // enabling QAction on positive YERITHTABLEVIEW rowcount
    {
        QAction *anAction = 0;

        QMapIterator<QAction *, bool>
        	j(_MAP_actions_to_enable_on_positive_tableview_ROW_COUNT__TO__AUTHORIZED_FOR_CURRENT_USER);

        while (j.hasNext())
        {
            j.next();

            anAction = j.key();

            if (0 != anAction)
            {
                if (_list_actions_to_enable_on_positive_tableview_ROW_COUNT.contains(anAction))
                {
                    enable_action = (_yerithTableView_FROM_WINDOWS_COMMONS->rowCount() > 0);
                }
                else
                {
                    enable_action = true;
                }

                anAction->setVisible((j.value() && enable_action));
            }
        }
    }

    // enabling YerithPushButton on positive YERITHTABLEVIEW rowcount
    {
        enable_action = (_yerithTableView_FROM_WINDOWS_COMMONS->rowCount() > 0);

        int list_size = _list_yerith_pushbutton_to_enable_on_positive_tableview_ROW_COUNT.size();

        YerithPushButton *aYerithPushButton = 0;

        for (unsigned int j = 0; j < list_size; ++j)
        {
            aYerithPushButton = _list_yerith_pushbutton_to_enable_on_positive_tableview_ROW_COUNT.at(j);

            if (0 != aYerithPushButton)
            {
                aYerithPushButton
					->setVisible((aYerithPushButton->isAuthorizedForCurrentUser() && enable_action));
            }
        }
    }

    _yerithTableView_FROM_WINDOWS_COMMONS->resizeRowsToContents();

    _yerithTableView_FROM_WINDOWS_COMMONS->resizeColumnsToContents();
}


void YerithWindowsCommons::getManuelUtilisateurPDF()
{
    YerithPOSUser *user = _allWindows->getUser();

    if (user)
    {
        QStringList progArguments;

        QProcess aProcess;

        if (user->isManager() ||
        	user->isVendeur() ||
			user->isCaissier())
        {

        	if (YerithMainWindow::LANGUE_ANGLAISE)
        	{
                progArguments <<
                		YerithERPConfig::FILE_ABSOLUTEPATH_YERITH_ERP_3_0_MANUEL_DE_LUTILISATEUR_MANAGER_EN;
        	}
        	else
        	{
                progArguments <<
                		YerithERPConfig::FILE_ABSOLUTEPATH_YERITH_ERP_3_0_MANUEL_DE_LUTILISATEUR_MANAGER;
        	}

            aProcess.startDetached(YerithERPConfig::pathToPdfReader,
                                   progArguments);
        }
    }
}


void YerithWindowsCommons::infosEntreprise()
{
    YerithUtils::infosEntreprise(*this,
                                 _allWindows->getInfoEntreprise().toString());
}


void YerithWindowsCommons::charges_financieres()
{
    Set_next_Requested___Window_Frame(_allWindows->_charges_financieresWindow);

    rendreInvisible();

    _allWindows->_charges_financieresWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::achats_de_stocks()
{
    Set_next_Requested___Window_Frame(_allWindows->_achatsWindow);

    rendreInvisible();

    _allWindows->_achatsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::stocks()
{
    Set_next_Requested___Window_Frame(_allWindows->_stocksWindow);

    rendreInvisible();

    _allWindows->_stocksWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::afficherMarchandises()
{
    Set_next_Requested___Window_Frame(_allWindows->_marchandisesWindow);

    rendreInvisible();

    _allWindows->_marchandisesWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::alertes()
{
    Set_next_Requested___Window_Frame(_allWindows->_listerAlertesWindow);

    rendreInvisible();

    _allWindows->_listerAlertesWindow->rendreVisible(_curStocksTableModel);
}

void YerithWindowsCommons::SLOT_CREER_A_PARTIR_DE_CECI()
{
    Set_next_Requested___Window_Frame(_allWindows->_adminCreateWindow);

	_allWindows->_adminCreateWindow
		->rendreVisible(_curStocksTableModel,
                        SUJET_ACTION_CHARGE_FINANCIERE,
						true);
	rendreInvisible();
}


void YerithWindowsCommons::SLOT_CREER_A_PARTIR_DE_CECI_charge_financiere()
{
    Set_next_Requested___Window_Frame(_allWindows->_adminCreateWindow);

	_allWindows->_adminCreateWindow
		->rendreVisible(_curStocksTableModel,
                        SUJET_ACTION_CHARGE_FINANCIERE,
						true,
						true);
	rendreInvisible();
}


void YerithWindowsCommons::CREER_UN_GROUPE_DE_SALARIAL_hr()
{
    Set_next_Requested___Window_Frame(_allWindows->_CREER_GROUPE_DE_PAIE_hr_window);

    _allWindows->_CREER_GROUPE_DE_PAIE_hr_window->rendreVisible(_curStocksTableModel);

    rendreInvisible();
}


void YerithWindowsCommons::CREER_GROUPE_demployes_hr()
{
    _next_Requested___Window_Frame = _allWindows->_CREER_groupe_demployes_window;

    _allWindows->_CREER_groupe_demployes_window->rendreVisible(_curStocksTableModel);

    rendreInvisible();
}


void YerithWindowsCommons::GROUPES_demployes_hr()
{
    Set_next_Requested___Window_Frame(_allWindows->_groupe_demployes_window);

    _allWindows->_groupe_demployes_window->rendreVisible(_curStocksTableModel);

    rendreInvisible();
}


void YerithWindowsCommons::GROUPES_DE_PAIE_hr(bool only_set_visible_FALSE /* = false */)
{
    Set_next_Requested___Window_Frame(_allWindows->_GROUPES_DE_PAIE_Window);

    _allWindows->_GROUPES_DE_PAIE_Window->rendreVisible(_curStocksTableModel);

    if (only_set_visible_FALSE)
    {
        setVisible(false);
    }
    else
    {
        rendreInvisible();
    }
}


/**
 * This method calls 'Supplier / EMPLOYEE' window
 * frame and calls back the previous supplier
 * and / or Employee interface choice from user.
 *
 * IF the developer wants to command which is
 * to be shown, then following method
 * 'YerithWindowsCommons::fournisseurs_SPECIFIC_commanded(bool)
 * shall be called instead !
 */
void YerithWindowsCommons::fournisseurs()
{
    YerithWindowsCommons::fournisseurs_SPECIFIC_commanded
            (!_allWindows->_fournisseursWindow->is_Show_Employee());
}


void YerithWindowsCommons::fournisseurs_SPECIFIC_commanded(bool _show_supplier_boolean_value /* = true */)
{
    Set_next_Requested___Window_Frame(_allWindows->_fournisseursWindow);

    rendreInvisible();

    if (_show_supplier_boolean_value)
    {
        _allWindows->_fournisseursWindow->set_show_employee(false);

    }
    else
    {
        _allWindows->_fournisseursWindow->set_show_employee(true);
    }

    _allWindows->_fournisseursWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::groupes_de_clients()
{
    Set_next_Requested___Window_Frame(_allWindows->_groupesDeClientsWindow);

    rendreInvisible();

    _allWindows->_groupesDeClientsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::programmes_de_fidelite_clients()
{
    Set_next_Requested___Window_Frame(_allWindows->_programmesDeFideliteClientsWindow);

    rendreInvisible();

    _allWindows->_programmesDeFideliteClientsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::creer_un_programme_de_fidelite_clients()
{
    Set_next_Requested___Window_Frame(_allWindows->_creerUnProgrammeDeFideliteClientsWindow);

    rendreInvisible();

    _allWindows->_creerUnProgrammeDeFideliteClientsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::clients()
{
    Set_next_Requested___Window_Frame(_allWindows->_clientsWindow);

    rendreInvisible();

    _allWindows->_clientsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::sortir()
{
    Set_next_Requested___Window_Frame(_allWindows->_sortirWindow);

    rendreInvisible();

    _allWindows->_sortirWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::tableaux_de_bords()
{
    Set_next_Requested___Window_Frame(_allWindows->_statistiquesWindow);

    rendreInvisible();

    _allWindows->_statistiquesWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::mouvements_de_stocks()
{
    Set_next_Requested___Window_Frame(_allWindows->_mouvementsDeStocksWindow);

    _allWindows->_mouvementsDeStocksWindow->rendreVisible(_curStocksTableModel);

    rendreInvisible();
}


void YerithWindowsCommons::creerFournisseur(bool _show_supplier_boolean_value /* = true */)
{
    Set_next_Requested___Window_Frame(_allWindows->_creerFournisseurWindow);

    rendreInvisible();

    _allWindows->_creerFournisseurWindow
        ->rendreVisible(_curStocksTableModel,
                        _show_supplier_boolean_value);
}


void YerithWindowsCommons::creerCompteClient()
{
    Set_next_Requested___Window_Frame(_allWindows->_creerCompteClientWindow);

    rendreInvisible();

    _allWindows->_creerCompteClientWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::creerUnGroupeDeClients()
{
    Set_next_Requested___Window_Frame(_allWindows->_creerGroupeDeClientsWindow);

    rendreInvisible();

    _allWindows->_creerGroupeDeClientsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::vendre_au_COMPTE_CLIENT(bool sowItem /* = false */)
{
    Set_next_Requested___Window_Frame(_allWindows->_entrerWindow);

    rendreInvisible();

    _allWindows->_entrerWindow->rendreVisible(_curStocksTableModel,
    										  sowItem,
                                              0,
											  set_choice_sell_TO_CLIENT);
}


void YerithWindowsCommons::entrer_une_Dette_FINANCIERE()
{
    Set_next_Requested___Window_Frame(_allWindows->_entrerWindow);

    rendreInvisible();

    _allWindows->_entrerWindow->rendreVisible(_curStocksTableModel,
                                              true,
                                              0,
                                              set_choice_insert_FINANCIAL_EXPENSE_loan_Debt);
}


void YerithWindowsCommons::entrer_une_charge_financiere()
{
    Set_next_Requested___Window_Frame(_allWindows->_entrerWindow);

    rendreInvisible();

    _allWindows->_entrerWindow->rendreVisible(_curStocksTableModel,
                                              true,
                                              0,
                                              set_choice_insert_FINANCIAL_EXPENSE);
}


void YerithWindowsCommons::entrer()
{
    Set_next_Requested___Window_Frame(_allWindows->_entrerWindow);

    rendreInvisible();

    _allWindows->_entrerWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::paiements()
{
    Set_next_Requested___Window_Frame(_allWindows->_paiementsWindow);

    rendreInvisible();

    _allWindows->_paiementsWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::ventes()
{
    Set_next_Requested___Window_Frame(_allWindows->_ventesWindow);

    rendreInvisible();

    _allWindows->_ventesWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::vendre()
{
    Set_next_Requested___Window_Frame(_allWindows->_pdVenteWindow);

    rendreInvisible();

    _allWindows->_pdVenteWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::Main_MENU()
{
    Set_next_Requested___Window_Frame(_allWindows->_mainWindow);

    rendreInvisible();

    _allWindows->_mainWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::comptabilite()
{
    Set_next_Requested___Window_Frame(_allWindows->_comptabiliteWindow);

    rendreInvisible();

    _allWindows->_comptabiliteWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::SLOT_method___action_mariadb_management()
{
    Set_next_Requested___Window_Frame(_allWindows->_adminWindow);

    rendreInvisible();

    _allWindows->_adminWindow->rendreVisible(_curStocksTableModel,
                                             true,
                                             true);
}


void YerithWindowsCommons::lancer_yri_web_System()
{
    Set_next_Requested___Window_Frame(_allWindows->_adminWindow);

    if (_allWindows->_adminWindow != _CURRENTLY_Now_Requested___Window_Frame)
    {
        rendreInvisible();

        _allWindows->_adminWindow->rendreVisible(_curStocksTableModel,
                                                 true);
    }
    else
    {
        _allWindows->_adminWindow
            ->tabWidget_maintenance_verification_DATABASE
                ->setCurrentIndex(2);

        _allWindows->_adminWindow
            ->tabWidget_administration
                ->setCurrentIndex(YerithAdminWindow::YerithAdminWindowTabPositionsTypes::MAINTENANCE);

        _allWindows->_adminWindow
            ->tabWidget_maintenance_verification_DATABASE
                ->setVisible(true);
    }
}


void YerithWindowsCommons::administration()
{
    Set_next_Requested___Window_Frame(_allWindows->_adminWindow);

    rendreInvisible();

    _allWindows->_adminWindow
        ->tabWidget_administration
            ->setCurrentIndex(YerithAdminWindow::YerithAdminWindowTabPositionsTypes::OPERATIONS);

    _allWindows->_adminWindow->rendreVisible(_curStocksTableModel);
}


void YerithWindowsCommons::setup_select_configure_dbcolumn(const QString &aSqlTableName)
{
    _selectExportDBQDialog = new YerithERPGenericSelectDBFieldDialog(_allWindows,
    																 this);

    if (0 != getQMainWindowToolBar())
    {
        _selectExportDBQDialog->setPalette(getQMainWindowToolBar()->palette());
    }

    _selectExportDBQDialog->setStyleSheet(qMessageBoxStyleSheet());

	if (aSqlTableName.isEmpty())
	{
		return ;
	}

    QString strShowColumnQuery = QString("SHOW COLUMNS FROM %1")
    								.arg(aSqlTableName);

    QSqlQuery query;

    int querySize = YerithUtils::execQuery(query, strShowColumnQuery);

    unsigned int columnIdx = -1;

    for (int k = 0; k < querySize && query.next(); ++k)
    {
        QString fieldName(query.value(0).toString());

        QString type(query.value(1).toString());

        columnIdx = columnIdx + 1;

        if (type.contains(YerithUtils::DATABASE_MYSQL_VARCHAR_TYPE_STRING) ||
                YerithUtils::isEqualCaseInsensitive(fieldName,
                                                    YerithDatabaseTableColumn::ID))
        {
            _varchar_dbtable_column_name_list.insert(fieldName);
        }

        if (type.contains(YerithUtils::DATABASE_MYSQL_CHAR_TYPE_STRING) ||
                type.contains(YerithUtils::DATABASE_MYSQL_TIME_TYPE_STRING) ||
                type.contains(YerithUtils::DATABASE_MYSQL_DATE_TYPE_STRING))
        {
            _DBFieldNamesToPrintLeftAligned.insert(columnIdx);
        }
        else if (type.contains(YerithUtils::DATABASE_MYSQL_DOUBLE_TYPE_STRING)
                 || type.contains(YerithUtils::DATABASE_MYSQL_INT_TYPE_STRING))
        {
            _DBFieldNamesToPrintRightAligned.insert(columnIdx);
        }

        _dbtablecolumnNameToDBColumnIndex.insert(fieldName, columnIdx);
    }
}


void YerithWindowsCommons::updateYerithLineEditQCompleter(const QString &
                                                          currentDBColumnString)
{
    QString correspondingDBFieldKeyValue =
                    YERITH_USER_VIEW_STRING_TO_DATABASE_TABLE_COLUMN(currentDBColumnString);

    if (0 == _yerith_QComboBox_SearchDBFieldColumnString ||
            0 == _yerith_QLineEdit_SearchDBFieldColumnString ||
            correspondingDBFieldKeyValue.isEmpty())
    {
        return;
    }

    if (!correspondingDBFieldKeyValue.isEmpty())
    {
        if (!_yerith_references_dbColumnString.contains
                (correspondingDBFieldKeyValue))
        {
            _yerith_QLineEdit_SearchDBFieldColumnString->setupMyStaticQCompleter
            (_dbYerithSqlTableName_WINDOWS_TABLE_VIEW_FOR_SEARCH,
             correspondingDBFieldKeyValue, true);
        }
        else
        {
            _yerith_QLineEdit_SearchDBFieldColumnString->setupMyStaticQCompleter
            (_dbYerithSqlTableName_WINDOWS_TABLE_VIEW_FOR_SEARCH,
             correspondingDBFieldKeyValue, false);
        }
    }
}


void YerithWindowsCommons::CHANGER_DE_LANGUE(YerithWindowsCommons *a_calling_window)
{
	if (0 == a_calling_window ||
        0 == YerithERPWindows::_YERITH_ERP_PGI_APPLICATION)
	{
		return ;
	}

	if (!YerithMainWindow::LANGUE_ANGLAISE)
	{
		//QDEBUG_STRING_OUTPUT_1("YerithERPWindows::_ENGLISH_TRANSLATOR");

		YerithERPWindows::_YERITH_ERP_PGI_APPLICATION
			->installTranslator(YerithERPWindows::_ENGLISH_TRANSLATOR);

		YerithERPWindows::_YERITH_ERP_PGI_APPLICATION
			->removeTranslator(YerithERPWindows::_FRENCH_TRANSLATOR);


	    YerithMainWindow::LANGUE_ANGLAISE = true;
	}
	else
	{
		//QDEBUG_STRING_OUTPUT_1("YerithERPWindows::_FRENCH_TRANSLATOR");

		YerithERPWindows::_YERITH_ERP_PGI_APPLICATION
			->installTranslator(YerithERPWindows::_FRENCH_TRANSLATOR);

		YerithERPWindows::_YERITH_ERP_PGI_APPLICATION
			->removeTranslator(YerithERPWindows::_ENGLISH_TRANSLATOR);

	    YerithMainWindow::LANGUE_ANGLAISE = false;
	}


    YerithDatabaseTableColumn::RETRANSLATE();


	___retranslateUi();


	CHANGER_DE_LANGUE__text__TRANSLATION(a_calling_window);
}


void YerithWindowsCommons::Change_flag_language_Next_TO_TRANSlate(QAction &action_TRADUIRE_EN_ANGLAIS,
                                                                  QAction &action_TRADUIRE_EN_FRANCAIS)
{
    bool current_language_IS_French = (! YerithMainWindow::LANGUE_ANGLAISE);


    YerithWindowsCommons::CHANGER_DE_LANGUE(this);


    if (YerithMainWindow::LANGUE_ANGLAISE)
    {
        current_language_IS_French =
            CHANGER_DE_LANGUE__text__TRANSLATION(this);

        //QDEBUG_STRING_OUTPUT_1("++ _FRANCE_drapeau_icon_File");
    }
    else
    {
        current_language_IS_French =
            CHANGER_DE_LANGUE__text__TRANSLATION(this);

        //QDEBUG_STRING_OUTPUT_1("++ _Usa_flag_icon_File");
    }


    YerithWindowsCommons::FRANCE_flag_francais_ACTIVE_now_On = current_language_IS_French;

    YerithWindowsCommons::USA_flag_English_ACTIVE_now_On = !FRANCE_flag_francais_ACTIVE_now_On;


    Refresh__STATUS_Languages_Flagship(action_TRADUIRE_EN_ANGLAIS,
                                       action_TRADUIRE_EN_FRANCAIS);
}


bool YerithWindowsCommons::CHANGER_DE_LANGUE__text__TRANSLATION(YerithWindowsCommons *a_calling_window)
{
    if (0 == a_calling_window)
    {
//        QDEBUG_STRING_OUTPUT_2("YerithWindowsCommons::CHANGER_DE_LANGUE__text__TRANSLATION",
//                                "NO POINTER TO A CALLING WINDOW !");

        return (! YerithMainWindow::LANGUE_ANGLAISE);
    }


    STRING_MONDAY = QObject::tr("Lundi");

    STRING_TUESDAY = QObject::tr("Mardi");

    STRING_WEDNESDAY = QObject::tr("Mercredi");

    STRING_THURSDAY = QObject::tr("Jeudi");

    STRING_FRIDAY = QObject::tr("Vendredi");

    STRING_SATURDAY = QObject::tr("Samedi");

    STRING_SUNDAY = QObject::tr("Dimanche");


    ___retranslateUi();


    bool current_language_Is_French = YerithMainWindow::LANGUE_ANGLAISE;

    return current_language_Is_French;
}


void YerithWindowsCommons::DONT___Check__BLANK_Timing_Of_WindowFRAME(bool isVisible)
{
    if (isVisible)
    {
        if (0 != _Cancel_MODIFICATION_request_Object                                  &&
            _Cancel_MODIFICATION_request_Object->Is_Currently_performing_modifications())
        {
            start_TIMER_Now();
        }
    }
    else
    {
        stop_TIMER_Now();
    }
}


void YerithWindowsCommons::Check__BLANK_Timing_Of_WindowFRAME()
{
    static uint blank_timing_counter = 0;

    if (blank_timing_counter >= 1)
    {

        _Cancel_MODIFICATION_request_Object
            ->set_closing_from_blanking_timing(true);


        if (_Cancel_MODIFICATION_request_Object
                ->Get_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING())
        {
            _Cancel_MODIFICATION_request_Object
                ->Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING(false);

            restart_TIMER_Now();

            blank_timing_counter = 0;
        }
        else
        {
            if (isVisible())
            {
                _Cancel_MODIFICATION_request_Object
                    ->Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING(false);

                _Cancel_MODIFICATION_request_Object
                    ->yri_Cancel__ALL__modifications_On_This_Window_Frame_PAGE();

                blank_timing_counter = 0;

                QPixmap pixmap(":Yerith___XAVIER_NOUNDOU.JPG");

                QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);

                splash.show();

                splash.finish(this);

                deconnecter_utilisateur();
            }
        }
    }
    else
    {
        ++blank_timing_counter;
    }
}


void YerithWindowsCommons::CLOSE_WINDOW_COMMON_FOR_SEARCH_CONDITION_FILTERING_PURPOSE()
{
    YerithERPWindows *allWindows = YerithUtils::getAllWindows();

    if (0 != allWindows &&
            0 != allWindows->_recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW)
    {
        allWindows->_recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW->close();
    }
}


void YerithWindowsCommons::AJOUTER_CONDITION_DE_RECHERCHE()
{
    YerithERPWindows *allWindows = YerithUtils::getAllWindows();

    if (0 != allWindows)
    {
        if (0 != allWindows->_recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW)
        {
            allWindows->
            _recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW->_current_window_TABLE_TO_SEARCH_WITH_CONDITION_FILTERING
                = this;
        }

        QPalette &aPalette =
                        const_cast < QPalette & >(getQMainWindowToolBar()->palette());

        QStringList aQStringList;

        aQStringList.append(_varchar_dbtable_column_name_list.values());

        YerithUtils::REMOVE_QSTRING_LIST(aQStringList,
                                         get_NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME
                                         ());

        if (0 != _yerith_QComboBox_SearchDBFieldColumnString &&
                !_yerith_QComboBox_SearchDBFieldColumnString->isEmpty())
        {
            aQStringList.removeOne
            (YERITH_USER_VIEW_STRING_TO_DATABASE_TABLE_COLUMN
             (_yerith_QComboBox_SearchDBFieldColumnString->currentText()));
        }

        allWindows->
        _recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW->rendreVisible
        (aQStringList, aPalette);
    }
}


void YerithWindowsCommons::setup_print()
{
    if (!_is_pdf_printing_initialized)
    {
        INITIALIZE_PDF_PRINTING_AT_ONCE();

        _is_pdf_printing_initialized = true;
    }

    if (0 != getQMainWindowToolBar())
    {
        _allWindows->_impressionDeDocumentDialog->groupBox_IMPRESSION_DE_DOCUMENT
			->setPalette(getQMainWindowToolBar()->palette());

        _allWindows->_impressionDeDocumentDialog->radioButton_IMPRESSION_VERTICAL
			->setPalette(getQMainWindowToolBar()->palette());

        _allWindows->_impressionDeDocumentDialog->radioButton_IMPRESSION_HORIZONTAL
			->setPalette(getQMainWindowToolBar()->palette());
    }

    _allWindows->_impressionDeDocumentDialog->_current_window_to_print = this;

//      QDEBUG_STRING_OUTPUT_2("setup_print, setting setup_print to: ", YERITH_QT_OBJECT_NAME(this));

    _allWindows->_impressionDeDocumentDialog->showAsModalDialogWithParent(*this);
}


void YerithWindowsCommons::print_PDF_PREVIOUSLY_SETUP()
{
    if (0 == _yerith_PRINT_UTILITIES_TEX_TABLE)
    {
        INITIALIZE_PDF_PRINTING_AT_ONCE();
//              return ;
    }

    if (0 != _yerith_PRINT_UTILITIES_TEX_TABLE)
    {
        _yerith_PRINT_UTILITIES_TEX_TABLE->SET_NOMBRE_DE_LIGNES(_print_table_row_count);

        _yerith_PRINT_UTILITIES_TEX_TABLE
			->_LATEX_A4_PAPER_SPEC =_a4paper_printing_position;

        if (-1 == _page_from || -1 == _page_to)
        {
            imprimer_pdf_document_WITH_A_YERITH_PROGRESS_BAR();

            return;
        }
        else
        {
            if (_page_from > _page_to)
            {
                YerithQMessageBox::warning(this,
                                           QObject::tr("IMPRESSION, NUMÉRO DE PAGES"),
                                           QObject::tr("La numéro de la page de départ doit "
                                        		   	   "être inférieur au numéro de la page terminale"));
                return;
            }

            imprimer_pdf_document_WITH_A_YERITH_PROGRESS_BAR(_page_from,
                                                             _page_to);
            return;
        }
    }
}


void YerithWindowsCommons::setYerithLineEditQCompleterSearchFilter
        (QString &aYerithLineEditQCompleterSearchFilter_IN_OUT,
         bool GENERATE_Like_SQL_STMT /* = true*/)
{
    if (0 == _yerith_QComboBox_SearchDBFieldColumnString ||
        0 == _yerith_QLineEdit_SearchDBFieldColumnString)
    {
        return;
    }

    QString correspondingDBFieldKeyValue;

    QString aTableColumnFieldContentForANDSearch;

    correspondingDBFieldKeyValue
		.append(YERITH_USER_VIEW_STRING_TO_DATABASE_TABLE_COLUMN
					(_yerith_QComboBox_SearchDBFieldColumnString->currentText()));

    aTableColumnFieldContentForANDSearch
		.append(_yerith_QLineEdit_SearchDBFieldColumnString->text());

    if (!correspondingDBFieldKeyValue.isEmpty()      &&
        !aTableColumnFieldContentForANDSearch.isEmpty())
    {
        if (!aYerithLineEditQCompleterSearchFilter_IN_OUT.isEmpty())
        {
            aYerithLineEditQCompleterSearchFilter_IN_OUT.append(" AND ");
        }

        if (!GENERATE_Like_SQL_STMT)
        {
            aYerithLineEditQCompleterSearchFilter_IN_OUT
                .append(YerithUtils::generateSqlIs(correspondingDBFieldKeyValue,
                                                   aTableColumnFieldContentForANDSearch));
        }
        else
        {
            aYerithLineEditQCompleterSearchFilter_IN_OUT
                .append(YerithUtils::generateSqlLike(correspondingDBFieldKeyValue,
                                                     aTableColumnFieldContentForANDSearch));
        }
    }
}


void YerithWindowsCommons::tableView_show_or_hide_columns(YerithTableView &tableView_in_out)
{
    const QStringList &NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME =
                    get_NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME();

    const QStringList &tableView_in_out_RAW_HEADERS =
                    tableView_in_out.getTableModelRawHeaders();

    QMapIterator<QString, int> it(_dbtablecolumnNameToDBColumnIndex);

    QString db_table_column_name;

    while (it.hasNext())
    {
        it.next();

        db_table_column_name.clear();

        db_table_column_name.append(it.key());

        if (!NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME.contains(db_table_column_name) &&
        	tableView_in_out_RAW_HEADERS.contains(db_table_column_name)				  &&
			_visibleDBColumnNameStrList.contains(db_table_column_name))
        {
            tableView_in_out.showColumn(it.value());
        }
        else
        {
            tableView_in_out.hideColumn(it.value());
        }
    }

    tableView_in_out.resizeColumnsToContents();

    handle_some_actions_tools_enabled();
}


int YerithWindowsCommons::getDialogBox_LONGUEUR(unsigned int n)
{
    static unsigned int delta = 259;

    int result = qCeil(n / 12.0);

    return (result * delta);
}


int YerithWindowsCommons::getDialogBox_Yn_coordinate(unsigned int n)
{
#define N 12

    static unsigned int y[N] =
    { 7, 37, 67, 97, 127, 157, 187, 217, 247, 277, 307, 337 };

    unsigned int modyn = (n % N);

    return y[modyn];
}


int YerithWindowsCommons::getDialogBox_Xn_coordinate(unsigned int n)
{
    static unsigned int w =
                    YerithWindowsCommons::
                    CHECKBOX_YERITH_FOR_DB_TABLE_COLUMN_FILTERING_WIDTH_SIZE;

    static unsigned int X_0 = 11;

    int result = qFloor(n / 12);

    return (X_0 + (result * w));
}


void YerithWindowsCommons::qui_suis_je()
{
    YerithQMessageBox::information(this, QObject::tr("qui suis je ?"),
                                   _allWindows->getUser()->toString());
}


void YerithWindowsCommons::INITIALIZE_PDF_PRINTING_AT_ONCE()
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return;
    }

    if (_first_time_imprimer_pdf_document_call &&
    	0 != _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        if (_output_print_pdf_latexFileNamePrefix.isEmpty())
        {
            _output_print_pdf_latexFileNamePrefix.append(_windowName);
        }

        _yerith_PRINT_UTILITIES_TEX_TABLE =
        	new YerithTableViewPRINT_UTILITIES_TEX_TABLE(_output_print_pdf_latexFileNamePrefix,
        										 	 	 *this,
														 *_yerithTableView_FROM_WINDOWS_COMMONS);

        _first_time_imprimer_pdf_document_call = false;
    }

    if (0 != _yerith_PRINT_UTILITIES_TEX_TABLE 	   &&
        0 != _allWindows->_impressionDeDocumentDialog)
    {
        _allWindows->_impressionDeDocumentDialog
        	->_yerith_CURRENT_DOCUMENT_PRINT_UTILITIES_TEX_TABLE =
        			_yerith_PRINT_UTILITIES_TEX_TABLE;
    }

    return;
}


bool YerithWindowsCommons::imprimer_pdf_document_WITH_PAGES_SPECIFICATION(int *pageFROM,
                                                                          int *pageTO)
{
    if (0 == pageFROM || 0 == pageTO)
    {
        return false;
    }

    if (_latex_template_print_pdf_content.isEmpty())
    {
    	_latex_template_print_pdf_content = get_latex_template_print_pdf_content();
    }

    if (_latex_template_print_pdf_content.isEmpty() ||
        0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return false;
    }


    static bool first_time_call = true;

    if (_first_time_imprimer_pdf_document_call &&
    	0 != _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        if (_output_print_pdf_latexFileNamePrefix.isEmpty())
        {
            _output_print_pdf_latexFileNamePrefix.append(_windowName);
        }

        _yerith_PRINT_UTILITIES_TEX_TABLE =
        		new YerithTableViewPRINT_UTILITIES_TEX_TABLE(_output_print_pdf_latexFileNamePrefix,
        												     *this,
															 *_yerithTableView_FROM_WINDOWS_COMMONS);

        _first_time_imprimer_pdf_document_call = false;
    }

    if (0 != _yerith_PRINT_UTILITIES_TEX_TABLE 		&&
        0 != _allWindows->_impressionDeDocumentDialog)
    {
        _allWindows->_impressionDeDocumentDialog->
        	_yerith_CURRENT_DOCUMENT_PRINT_UTILITIES_TEX_TABLE =
                        _yerith_PRINT_UTILITIES_TEX_TABLE;
    }

    if (first_time_call)
    {
        first_time_call = false;

        return imprimer_pdf_document_WITH_PAGES_SPECIFICATION(pageFROM,
                                                              pageTO);
    }

    QString pdfOutputFileName;

    if (-1 == *pageFROM || -1 == *pageTO)
    {
        pdfOutputFileName =
        	_yerith_PRINT_UTILITIES_TEX_TABLE
				->print_YERITH_document_from_TableView(_latex_template_print_pdf_content,
        											   &_documentSpecificElements_FOR_PDF_LATEX_PRINTING);
    }
    else
    {
        pdfOutputFileName =
        	_yerith_PRINT_UTILITIES_TEX_TABLE
				->print_YERITH_document_from_TableView(*pageFROM,
													   *pageTO,
													   _latex_template_print_pdf_content,
                         	 	 	 	 	 	 	   &_documentSpecificElements_FOR_PDF_LATEX_PRINTING);
    }

    if (pdfOutputFileName.isEmpty())
    {
        return false;
    }

    YerithERPProcess::startPdfViewerProcess(pdfOutputFileName);

    return true;
}


bool YerithWindowsCommons::imprimer_pdf_document()
{
    int pageFROM = -1;

    int pageTO = -1;

    get_latex_template_print_pdf_content();

    return imprimer_pdf_document_WITH_PAGES_SPECIFICATION(&pageFROM, &pageTO);
}


void YerithWindowsCommons::changer_utilisateur()
{
    _allWindows->_changerUtilisateurDialog->setParent(this, Qt::Popup | Qt::Dialog);
    _allWindows->_changerUtilisateurDialog->show();
    _allWindows->_changerUtilisateurDialog->activateWindow();
}


void YerithWindowsCommons::deconnecter_utilisateur()
{
    YerithPOSUser *aUser = _allWindows->getUser();

    if (0 != aUser)
    {
        aUser->cleanup_user_personal_PRINTING_PARAMETER_settings();
    }

    // This enables user settings privacy.
    slot_reinitialiser_colones_db_visibles();

    _allWindows->definirPasDeRole();

    _allWindows->_mainWindow->show();

    rendreInvisible();
}


void YerithWindowsCommons::rendreVisible(YerithSqlTableModel *stocksTableModel)
{
    _curStocksTableModel = stocksTableModel;

    setVisible(true);
}


void YerithWindowsCommons::rendreInvisible()
{
    if (0 != _allWindows 											&&
        0 != _allWindows->_recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW)
    {
        _allWindows->_recherche_CONDITIONNELLE_SEARCH_FILTER_WINDOW->rendreInvisible();
    }

    STOP_Performing_MODIFICATIONS_handler();

    set_yerith_WindowModified(false);

    setVisible(false);
}


void YerithWindowsCommons::fill_table_columns_to_ignore(QList<int> &tableColumnsToIgnore_in_out)
{
    QMapIterator<QString, int> it(_dbtablecolumnNameToDBColumnIndex);

    QString curFieldColumn;

    while (it.hasNext())
    {
        it.next();

        curFieldColumn = it.key();

        if (curFieldColumn.isEmpty())
        {
            continue;
        }

        if (!_visibleDBColumnNameStrList.contains(curFieldColumn))
        {
            tableColumnsToIgnore_in_out.append(it.value());
        }
    }
}


void YerithWindowsCommons::
		getQModelIndex_db_VALUE_from_MODEL_INDEX(const QString 		&dbTableColumnName,
                                                 const QModelIndex 	&modelIndex,
                                                 QString 			& db_VALUE_in_out)
{
    db_VALUE_in_out.clear();

    int yerithTableViewColumnIndex_db_VALUE =
                    _dbtablecolumnNameToDBColumnIndex.value(dbTableColumnName);

    int selected_row_nr = modelIndex.row();

    QModelIndex id_row_qmodelindex_sibling =
                    modelIndex.sibling(selected_row_nr, yerithTableViewColumnIndex_db_VALUE);

    db_VALUE_in_out.append(YerithUtils::get_text(id_row_qmodelindex_sibling.data()));
}


void YerithWindowsCommons::getQModelIndex_dbID_from_MODEL_INDEX(const QModelIndex   &modelIndex,
                                                                QString             &db_ID_in_out)
{
    db_ID_in_out.clear();

    int yerithTableViewColumnIndex_dbID =
                    _dbtablecolumnNameToDBColumnIndex.value(YerithDatabaseTableColumn::ID);

    int selected_row_nr = modelIndex.row();

    QModelIndex id_row_qmodelindex_sibling =
                    modelIndex.sibling(selected_row_nr, yerithTableViewColumnIndex_dbID);

    db_ID_in_out.
    append(YerithUtils::get_text(id_row_qmodelindex_sibling.data()));
}


void YerithWindowsCommons::setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID()
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS)
    {
        return;
    }

    YerithPOSQStandardItemModel *model =
        _yerithTableView_FROM_WINDOWS_COMMONS->getStandardItemModel();

    if (0 == model                 ||
        0 == model->_curSqlTableModel)
    {
        return;
    }

    if (_yerithTableView_FROM_WINDOWS_COMMONS->rowCount() > 0)
    {
        QModelIndex aYerithTableViewIndex = model->index(0, 0);

        setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(aYerithTableViewIndex);

        _yerithTableView_FROM_WINDOWS_COMMONS->setCurrentIndex(aYerithTableViewIndex);
    }
    else
    {
        QModelIndex aYerithTableViewIndex =
                        model->create_ZERO_ZERO_MODEL_INDEX_FOR_TABLE_VIEWING();

        setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(aYerithTableViewIndex);
    }
}


void YerithWindowsCommons::
        setLast_YERITH_TABLE_VIEW_SelectedRow__db_ID(const QModelIndex &modelIndex)
{
    if (0 == _yerithTableView_FROM_WINDOWS_COMMONS          ||
        _yerithTableView_FROM_WINDOWS_COMMONS->rowCount() <= 0)
    {
        return;
    }

    QString db_ID;

    getQModelIndex_dbID_from_MODEL_INDEX(modelIndex, db_ID);

//      QDEBUG_STRING_OUTPUT_2("db_ID - 1", db_ID);

    if (!db_ID.isEmpty()      &&
        modelIndex.row() >= 0 &&
        modelIndex.column() >= 0)
    {
        _yerithTableView_FROM_WINDOWS_COMMONS->setCurrentIndex(modelIndex);
    }
    else
    {
        YerithPOSQStandardItemModel *model =
            _yerithTableView_FROM_WINDOWS_COMMONS->getStandardItemModel();

        if (0 != model)
        {
            QModelIndex aYerithTableViewIndex_2 = model->index(0, 0);

            getQModelIndex_dbID_from_MODEL_INDEX(aYerithTableViewIndex_2,
                                                 db_ID);

            _yerithTableView_FROM_WINDOWS_COMMONS
                ->setCurrentIndex(aYerithTableViewIndex_2);
        }
        else
        {
            QDEBUG_STRING_OUTPUT_1("couldn't create and set a default QMODELINDEX !");
        }
    }

    _yerithTableView_FROM_WINDOWS_COMMONS->setLastSelectedRow__ID(db_ID);

    //_yerithTableView_FROM_WINDOWS_COMMONS->selectRow(modelIndex.row());

    //_yerithTableView_FROM_WINDOWS_COMMONS->_MAP_lastSelected_Row__TO__DB_ID
	//	.insert(QString::number(modelIndex.row()),
	//			db_ID);

    _yerithTableView_FROM_WINDOWS_COMMONS_LAST_SELECTED_ROW__db_ID = db_ID;
}


void YerithWindowsCommons::imprimer_pdf_document_WITH_A_YERITH_PROGRESS_BAR()
{
    if (0 != _yerith_PRINT_UTILITIES_TEX_TABLE)
    {
        _yerith_PRINT_UTILITIES_TEX_TABLE->RESET_NOMBRE_DE_LIGNES_TABLEAU_STANDARD();
    }

    YerithProgressBar(this)(this, &YerithWindowsCommons::imprimer_pdf_document);
}


bool YerithWindowsCommons::
        SET___CURRENTLY_Now_Requested___Window_Frame
                (YerithWindowsCommons *a_currently_now_requested___Window_FRAME)
{
    static bool first_time_ever_call = true;

    if (first_time_ever_call)
    {
        ____index_TO_WindowFrame->setMaxSize(30);

        first_time_ever_call = false;
    }


    if (0 != a_currently_now_requested___Window_FRAME)
    {
        bool toCancel = YerithWindowsCommons::_next_Requested___Window_Frame__TO__CANCEL_REQUEST
                                                    ->contains(a_currently_now_requested___Window_FRAME
                                                                    ->Get_YERITH_object_UOID());

        if (toCancel)
        {
            return false;
        }


        YerithWindowsCommons::_CURRENTLY_Now_Requested___Window_Frame = a_currently_now_requested___Window_FRAME;


        ____index_TO_WindowFrame
                ->yri_insert_item(YerithWindowsCommons::_CURRENTLY_Now_Requested___Window_Frame->Get_YERITH_object_UOID(),
                                  YerithWindowsCommons::_CURRENTLY_Now_Requested___Window_Frame);
    }

    return true;
}


bool YerithWindowsCommons::Is_Timer_Active()
{
    bool timer_IS_active = true;

    if (0 != ___Cancel_MODIFICATION_request_Object___Timer)
    {
        int timer_remaining_TIME = ___Cancel_MODIFICATION_request_Object___Timer->remainingTime();

        if (-1 == timer_remaining_TIME ||
            0 == timer_remaining_TIME)
        {
//            QDEBUG_STRING_OUTPUT_2_N("YerithWindowsCommons::Is_Timer_Active; timer_remaining_TIME",
//                                      timer_remaining_TIME);
            return false;
        }

        timer_IS_active =
            ___Cancel_MODIFICATION_request_Object___Timer->isActive();

//        QDEBUG_STRING_OUTPUT_2("YerithWindowsCommons::Is_Timer_Active; timer_IS_active",
//                                BOOL_TO_STRING(timer_IS_active));
    }
    else
    {
        timer_IS_active = false;
    }

    return timer_IS_active;
}


 void YerithWindowsCommons::stop_TIMER_Now()
 {
    if (0 != ___Cancel_MODIFICATION_request_Object___Timer)
    {
//        QDEBUG_STRING_OUTPUT_2_N("YerithWindowsCommons::stop_TIMER_Now()",
//                                  Get_YERITH_object_UOID());

        ___Cancel_MODIFICATION_request_Object___Timer->stop();
    }
 }


 void YerithWindowsCommons::start_TIMER_Now()
 {
    if (0 != ___Cancel_MODIFICATION_request_Object___Timer)
    {
//        QDEBUG_STRING_OUTPUT_2_N("YerithWindowsCommons::start_TIMER_Now()",
//                                  Get_YERITH_object_UOID());

        ___Cancel_MODIFICATION_request_Object___Timer
            ->start(YerithERPConfig::BLANKING_timing___SECONDS.toUInt());
    }
 }


 void YerithWindowsCommons::
        Handle__Events____Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING(QEvent *an_event,
                                                                                      bool    debugging_FLAG, /* = false, */
                                                                                      QString debugging_msg /* = YerithUtils::EMPTY_STRING */)
 {
    if (debugging_FLAG)
    {
        QDEBUG_STRING_OUTPUT_2
            ("YerithWindowsCommons::Handle__Events____Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING; an_event",
             debugging_msg);
    }


    restart_TIMER_Now();

    YERITH_call_if_pointer_Not_NULL_pointER(_Cancel_MODIFICATION_request_Object,
                                            Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING(true));
 }


 void YerithWindowsCommons::restart_TIMER_Now()
 {
    if (0 != ___Cancel_MODIFICATION_request_Object___Timer)
    {
//        QDEBUG_STRING_OUTPUT_2_N("YerithWindowsCommons::restart_TIMER_Now()",
//                                  Get_YERITH_object_UOID());

        ___Cancel_MODIFICATION_request_Object___Timer->stop();

        ___Cancel_MODIFICATION_request_Object___Timer
            ->start(YerithERPConfig::BLANKING_timing___SECONDS.toUInt());
    }
 }


int YerithWindowsCommons::Get__Timer__RemainingTime()
{
    int remainNING_time = 0;

    if (0 != ___Cancel_MODIFICATION_request_Object___Timer)
    {
        remainNING_time =
            ___Cancel_MODIFICATION_request_Object___Timer
                ->remainingTime();
    }

    return remainNING_time;
}


void YerithWindowsCommons::Set_next_Requested___Window_Frame(YerithWindowsCommons *Next_Requested___Window_Frame)
{
    _Previously_Requested___Window_Frame = this;

    _next_Requested___Window_Frame = Next_Requested___Window_Frame;
}



bool YerithWindowsCommons::CANCEL_RENDERING_request()
{
    if (0 != YerithWindowsCommons::_next_Requested___Window_Frame)
    {
        YerithWindowsCommons::_next_Requested___Window_Frame__TO__CANCEL_REQUEST
            ->yri_insert_item(YerithWindowsCommons::_next_Requested___Window_Frame->Get_YERITH_object_UOID(),
                              0);
    }
}






