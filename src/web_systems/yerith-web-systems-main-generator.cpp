/*
 * yerith-web-systems-main-generator.hpp
 *
 * For generating web code source files.
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-web-systems-main-generator.hpp"

#include "yerith-erp-xml-parser-QLIST___widget-element.hpp"


#include "yerith-web-systems-main-parser_XML_Tag_Element.hpp"


#include "src/yerith-erp-windows.hpp"

#include "src/utils/yerith-erp-utils.hpp"



#include "yerith-web-systems-main-generator___KeyWords.cpp"



YERITH_WEB_SYSTEMS_MAIN_GENERATOR::YERITH_WEB_SYSTEMS_MAIN_GENERATOR()
:_yri_An_xml_stream_Reader(0),
 _last_returned_Widget_Element(0),
 _last_returned_Widget_SUB_Element(0),
 _all_windows(0)
{
    _yri_An_xml_stream_Reader = new QXmlStreamReader;

    _all_windows = YerithUtils::getAllWindows();
}


YERITH_WEB_SYSTEMS_MAIN_GENERATOR::~YERITH_WEB_SYSTEMS_MAIN_GENERATOR()
{
	QMapIterator<QString, Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *>
            it(_yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation);


    Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *lIST_of_all_elements;


	while (it.hasNext())
	{
        it.next();

        lIST_of_all_elements = it.value();
        YERITH_DELETE_FREE_POINTER_NOW(lIST_of_all_elements);
	}


	_yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation.clear();
}


bool YERITH_WEB_SYSTEMS_MAIN_GENERATOR::
        add_An___XmlWidgetElementsFOR_HTML_web_generation
                (QString                                 A_processed_UI_File___full_path,
                 Yerith_ERP_Xml_Parser_Widget_Element   *an_erp_xml_parser_Widget_Element)
{
    bool element_was_added = false;


    if (0 == an_erp_xml_parser_Widget_Element)
    {
        return element_was_added;
    }


    Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *cur_list_of_All_File_ELEMENTS = 0;

    bool new_qlist_items = false;

    if (! _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation.contains
                (A_processed_UI_File___full_path))
    {
        cur_list_of_All_File_ELEMENTS =
            new Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS
                    (A_processed_UI_File___full_path);

        new_qlist_items = true;
    }
    else
    {
        cur_list_of_All_File_ELEMENTS =
            _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation
                    .value(A_processed_UI_File___full_path);
    }


    if (0 != cur_list_of_All_File_ELEMENTS)
    {
        cur_list_of_All_File_ELEMENTS
            ->append_an_USER_Interface_File_Element
                    (an_erp_xml_parser_Widget_Element);

        if (new_qlist_items)
        {
            QDEBUG_STRING_OUTPUT_2("A_processed_UI_File___full_path added !",
                                    A_processed_UI_File___full_path);

            _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation
                .insert(A_processed_UI_File___full_path,
                        cur_list_of_All_File_ELEMENTS);
        }

        element_was_added = true;
    }


    return element_was_added;
}


void YERITH_WEB_SYSTEMS_MAIN_GENERATOR::
        display_recognized_UI_file_widgets(bool reset_all_qlabel_for_viewing_output /* = false */)
{
    QDEBUG_STRING_OUTPUT_1("YERITH_WEB_SYSTEMS_MAIN_GENERATOR::display_recognized_UI_file_widgets");

    if (0 == _all_windows)
    {
        return ;
    }

    if (0 == _all_windows->_adminWindow)
    {
        return ;
    }


    _all_windows->_adminWindow
        ->tableWidget_lister_Widgets_discovered_1
            ->yerithClearTableWidgetContent();


    _all_windows->_adminWindow
        ->tableWidget_lister_Widgets_discovered_2
            ->yerithClearTableWidgetContent();


	QMapIterator<QString, Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *>
            it_admin_WebSYSTEM_visualization_Widgets(_yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation);


    Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *all_xml_widget_elements = 0;

    Yerith_ERP_Xml_Parser_Widget_Element *next_element = 0;


    uint max_it_counter = (2 * YerithERPConfig::MAX_Widgets_Discovered_row_COUNT);

    int it_counter = 0;


	while (it_admin_WebSYSTEM_visualization_Widgets.hasNext() &&
           it_counter < max_it_counter)
	{
        it_admin_WebSYSTEM_visualization_Widgets.next();

        all_xml_widget_elements = it_admin_WebSYSTEM_visualization_Widgets.value();


        if (0 != all_xml_widget_elements)
        {
            for (uint i = 0; i < all_xml_widget_elements->get_size(); ++i)
            {
                next_element = all_xml_widget_elements->get_element(i);

                if (0 != next_element)
                {
                    if (it_counter < YerithERPConfig::MAX_Widgets_Discovered_row_COUNT)
                    {
                        _all_windows->_adminWindow
                            ->tableWidget_lister_Widgets_discovered_1->addArticle(*next_element);
                    }
                    else
                    {
                        _all_windows->_adminWindow
                            ->tableWidget_lister_Widgets_discovered_2->addArticle(*next_element);
                    }

                    ++it_counter;
                }
            }
        }

	}

    if (0 != _all_windows)
    {
        _all_windows->_adminWindow
            ->tabWidget_maintenance_web_SYSTEM_tab->setVisible(true);

        if (0 == it_counter)
        {
            _all_windows->_adminWindow
                ->tabWidget_maintenance_web_SYSTEM_tab->setVisible(false);
        }
        else
        {

            _all_windows->_adminWindow
                ->tabWidget_maintenance_web_SYSTEM_tab
                    ->setTabVisible(YerithAdminWindow::Widget_TAB_ONE, true);

            _all_windows->_adminWindow
                ->tabWidget_maintenance_web_SYSTEM_tab
                    ->setTabVisible(YerithAdminWindow::Widget_TAB_Statistics, true);


            if (it_counter >= YerithERPConfig::MAX_Widgets_Discovered_row_COUNT)
            {
                _all_windows->_adminWindow
                    ->tabWidget_maintenance_web_SYSTEM_tab
                        ->setTabVisible(YerithAdminWindow::Widget_TAB_Two, true);
            }
            else
            {
                _all_windows->_adminWindow
                    ->tabWidget_maintenance_web_SYSTEM_tab
                        ->setTabVisible(YerithAdminWindow::Widget_TAB_Two, false);
            }


            _all_windows->_adminWindow
                ->tabWidget_maintenance_web_SYSTEM_tab
                    ->setTabVisible(YerithAdminWindow::Widget_TAB_Preview_Source_Code_YERITH_WEB_DSL_9_0, true);
        }
    }
}


int YERITH_WEB_SYSTEMS_MAIN_GENERATOR::
        number_of_widgets_detected_Last_for_File
            (QString _current_processed_UI_File___full_path)
{
    int number_of_widgets_detected_by_Parser = 0;


    Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *all_widgets_for_this_processed_file_currently = 0;


    all_widgets_for_this_processed_file_currently =
        _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation
            .value(_current_processed_UI_File___full_path);


    if (0 != all_widgets_for_this_processed_file_currently)
    {
        number_of_widgets_detected_by_Parser =
            all_widgets_for_this_processed_file_currently
                ->get_size();
    }

    return number_of_widgets_detected_by_Parser;
}


int YERITH_WEB_SYSTEMS_MAIN_GENERATOR::
            process_Current_Registered_User_Interface___FILE()
{
    _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation.clear();


    int number_of_widgets_detected_by_Parser = 0;


    QDEBUG_STRING_OUTPUT_2("process_Current_Registered_User_Interface___FILE | current ui file.",
                            _current_processed_UI_File___full_path);

    if (_current_processed_UI_File___full_path.isEmpty())
    {
        QDEBUG_STRING_OUTPUT_1("process_Current_Registered_User_Interface___FILE | aborting because of empty path.");

        emit _all_windows->_adminWindow->SIGNAL_INCREMENT_PROGRESS_BAR(10);

        return 0;
    }


    _yri_An_xml_stream_Reader = new QXmlStreamReader;


    QString aWebUiFile_string_content =
                YerithUtils::import_WEB_system_UI_file_content
                    (Get_current_processed_UI_File___full_path());


    emit _all_windows->_adminWindow->SIGNAL_INCREMENT_PROGRESS_BAR(30);


//    QDEBUG_STRING_OUTPUT_2("aWebUiFile_string_content",
//                            aWebUiFile_string_content);


    _yri_An_xml_stream_Reader->addData(aWebUiFile_string_content);


    emit _all_windows->_adminWindow->SIGNAL_INCREMENT_PROGRESS_BAR(45);


    enum QXmlStreamReader::TokenType type___next_token;


    QString next_token;

    QString next_token_NAME;

    QString next_token_TEXT;

    QString next_token_ELEMENT_TEXT;


    bool last_sub_element_Visited = false;


    Yerith_ERP_Xml_Parser___Main_Parser
        handle_Widget_XML_TAG_Element_parser_Instance(this);



    while (!_yri_An_xml_stream_Reader->atEnd())
    {
        type___next_token = _yri_An_xml_stream_Reader->readNext();

        next_token = _yri_An_xml_stream_Reader->tokenString();
        next_token_NAME = _yri_An_xml_stream_Reader->name().toString();

        switch(type___next_token)
        {
            case QXmlStreamReader::StartElement:

                if (YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_widget_keyword, next_token_NAME))
                {
                    last_sub_element_Visited = false;

                    _last_returned_Widget_Element =
                        handle_Widget_XML_TAG_Element_parser_Instance
                            .handle_XML_TAG_Element(next_token_NAME,
                                                    YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_name_keyword,
                                                    YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_class_keyword);

                    setCurrentStart_Element(_last_returned_Widget_Element);
                }
                else if (YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_property_keyword, next_token_NAME))
                {
                    _last_returned_Widget_SUB_Element =
                        handle_Widget_XML_TAG_Element_parser_Instance
                            .handle_XML_TAG_Element(next_token_NAME,
                                                    YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_name_keyword,
                                                    YerithUtils::EMPTY_STRING,
                                                    YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_geometry_keyword);
                }
                else if (YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_X_geometry_keyword, next_token_NAME))
                {
                    if (0 != _last_returned_Widget_Element &&
                        YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_property_keyword,
                                                            _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name))
                    {
                        _last_returned_Widget_SUB_Element =
                            handle_Widget_XML_TAG_Element_parser_Instance
                                .handle_XML_TAG_Element(next_token_NAME,
                                                        YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_X_geometry_keyword);

                        if (0 != _last_returned_Widget_SUB_Element)
                        {
                            _last_returned_Widget_Element->___geometry_X_axis_position =
                                _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name_VALUE_str.toInt();

                            setCurrentStart_Element(_last_returned_Widget_SUB_Element);
                        }
                    }
                }
                else if (YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_Y_geometry_keyword, next_token_NAME))
                {
                    if (0 != _last_returned_Widget_Element &&
                        YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_X_geometry_keyword,
                                                             _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name))
                    {
                        _last_returned_Widget_SUB_Element =
                            handle_Widget_XML_TAG_Element_parser_Instance
                                .handle_XML_TAG_Element(next_token_NAME,
                                                        YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_Y_geometry_keyword);

                        if (0 != _last_returned_Widget_SUB_Element)
                        {
                            _last_returned_Widget_Element->___geometry_Y_axis_position =
                                _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name_VALUE_str.toInt();

                            setCurrentStart_Element(_last_returned_Widget_SUB_Element);
                        }
                    }
                }
                else if (YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_WIDTH_geometry_keyword, next_token_NAME))
                {
                    if (0 != _last_returned_Widget_Element &&
                        YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_Y_geometry_keyword,
                                                             _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name))
                    {
                        _last_returned_Widget_SUB_Element =
                            handle_Widget_XML_TAG_Element_parser_Instance
                                .handle_XML_TAG_Element(next_token_NAME,
                                                        YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_WIDTH_geometry_keyword);

                        if (0 != _last_returned_Widget_SUB_Element)
                        {
                            _last_returned_Widget_Element->___geometry_WIDTH =
                                _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name_VALUE_str.toInt();

                            setCurrentStart_Element(_last_returned_Widget_SUB_Element);
                        }
                    }
                }
                else if (YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_HEIGHT_geometry_keyword, next_token_NAME))
                {
                    if (0 != _last_returned_Widget_Element &&
                        YerithUtils::isEqualCaseInsensitive(YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_WIDTH_geometry_keyword,
                                                             _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name))
                    {
                        _last_returned_Widget_SUB_Element =
                            handle_Widget_XML_TAG_Element_parser_Instance
                                .handle_XML_TAG_Element(next_token_NAME,
                                                        YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_HEIGHT_geometry_keyword);

                        if (0 != _last_returned_Widget_SUB_Element)
                        {
                            _last_returned_Widget_Element->___geometry_HEIGHT =
                                _last_returned_Widget_SUB_Element->_a_widget_xml_tag_name_VALUE_str.toInt();

                            setCurrentStart_Element(_last_returned_Widget_SUB_Element);

                            last_sub_element_Visited = true;
                        }
                    }
                }
                break;

            default:
                break;
        }


        if (true == last_sub_element_Visited                                            &&
            0 != _last_returned_Widget_SUB_Element                                      &&
            0 != _last_returned_Widget_Element                                          &&
            YerithUtils::isEqualCaseInsensitive(PARSER_widget_keyword, next_token_NAME) &&
            YerithERPConfig::Show_yri_web_system_Ouput_also_in_Console)
        {
            if (! YerithERPConfig::Show_yri_web_system_detailed___Ouput_also_in_Console)
            {
                _last_returned_Widget_Element
                    ->print_With_Developer_string__No_Geometry_added
                        (QString("handle_XML_TAG_Element : %1")
                            .arg(next_token_NAME));
            }
            else
            {
                _last_returned_Widget_Element
                    ->print_With_Developer_string_added
                        (QString("handle_XML_TAG_Element - det. : %1")
                            .arg(next_token_NAME));
            }
        }
    }


    number_of_widgets_detected_by_Parser =
        number_of_widgets_detected_Last_for_File(_current_processed_UI_File___full_path);


    _all_windows
        ->_adminWindow
            ->SET_value___Of___label_importer_fichier_UI___number_widgets
                (number_of_widgets_detected_by_Parser);


    display_recognized_UI_file_widgets();


    if (_yri_An_xml_stream_Reader->hasError())
    {
        QDEBUG_STRING_OUTPUT_2("QXmlStreamReader error",
                                _yri_An_xml_stream_Reader->errorString());
    }


    emit _all_windows->_adminWindow->SIGNAL_INCREMENT_PROGRESS_BAR(88);


    _yri_An_xml_stream_Reader->clear();


    delete _yri_An_xml_stream_Reader;


    emit _all_windows->_adminWindow->SIGNAL_INCREMENT_PROGRESS_BAR(98);


    return number_of_widgets_detected_by_Parser;
}


bool YERITH_WEB_SYSTEMS_MAIN_GENERATOR::
        setCurrentStart_Element(Yerith_ERP_Xml_Parser_Widget_Element *A_start_Widget_Xml_Element)
{
    bool a_New_current_start_element_SET = false;

    if (0 != A_start_Widget_Xml_Element)
    {
        _current_start_element = A_start_Widget_Xml_Element->_a_widget_xml_name;

        a_New_current_start_element_SET = true;
    }

    return a_New_current_start_element_SET;
}



