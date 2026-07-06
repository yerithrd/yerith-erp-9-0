/*
 * yerith-web-systems-main-generator.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_WEB_SYSTEMS_MAIN_GENERATOR_HPP_
#define _YERITH_WEB_SYSTEMS_MAIN_GENERATOR_HPP_


#include "yerith-erp-xml-parser-widget-element.hpp"


#include <QXmlStreamReader>


class Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS;

class YerithERPWindows;
class Yerith_ERP_Xml_Parser_Widget_Element;
class QXmlStreamReader;


class YERITH_WEB_SYSTEMS_MAIN_GENERATOR
{
public:

    YERITH_WEB_SYSTEMS_MAIN_GENERATOR();

    virtual ~YERITH_WEB_SYSTEMS_MAIN_GENERATOR();


    virtual inline QString Get_current_processed_UI_File___full_path()
    {
        return _current_processed_UI_File___full_path;
    }

    virtual inline void set_current_processed_UI_File___full_path(QString a_ui_full_path)
    {
        _current_processed_UI_File___full_path = a_ui_full_path;
    }


    virtual inline QString Get_LAST_RETURNED_WIDGET_ELEMENT___a_widget_xml_name()
    {
        return
            (0 != _last_returned_Widget_Element) ?
                _last_returned_Widget_Element->_a_widget_xml_name :
                YerithUtils::EMPTY_STRING;
    }

    virtual inline QString Get_LAST_RETURNED_WIDGET_ELEMENT___a_widget_xml_class_name()
    {
        return
            (0 != _last_returned_Widget_Element) ?
                _last_returned_Widget_Element->_a_widget_xml_class_name :
                YerithUtils::EMPTY_STRING;
    }

    virtual inline QString Get_LAST_RETURNED_WIDGET_ELEMENT___a_widget_xml_tag_name()
    {
        return
            (0 != _last_returned_Widget_Element) ?
                _last_returned_Widget_Element->_a_widget_xml_tag_name :
                YerithUtils::EMPTY_STRING;
    }


    virtual inline bool add_An___XmlWidgetElementsFOR_HTML_web_generation
                            (Yerith_ERP_Xml_Parser_Widget_Element *an_erp_xml_parser_Widget_Element)
    {
        add_An___XmlWidgetElementsFOR_HTML_web_generation(_current_processed_UI_File___full_path,
                                                          an_erp_xml_parser_Widget_Element);
    }


    bool add_An___XmlWidgetElementsFOR_HTML_web_generation
                (QString                                A_processed_UI_File___full_path,
                 Yerith_ERP_Xml_Parser_Widget_Element  *an_erp_xml_parser_Widget_Element);


    virtual inline QXmlStreamReader *GET___yri_An_xml_stream_Reader()
    {
        return _yri_An_xml_stream_Reader;
    }


public slots:

    void display_recognized_UI_file_widgets(bool reset_all_qlabel_for_viewing_output = false);


    /**
     * Returns number of discovered widgets for the
     * current processed file '_current_processed_UI_File___full_path'
     * after a run of class method
     * 'process_Current_Registered_User_Interface___FILE'!
     */
    virtual int number_of_widgets_detected_Last_for_File(QString _current_processed_UI_File___full_path);


    /**
    * Returns 'True' only for a parser keyword
    * that is later on set as a last returned
    * element instance : 'class member variable
    *      "Yerith_ERP_Xml_Parser_Widget_Element *_last_returned_Widget_Element".
    */
    virtual inline bool is_a_PARSER_processing_KeyWord(QString a_PARSER_processing_KeyWord)
    {
        return
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_widget_keyword)         ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_name_keyword)           ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_class_keyword)          ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_geometry_keyword)       ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_X_geometry_keyword)     ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_Y_geometry_keyword)     ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_WIDTH_geometry_keyword) ||
            YerithUtils::isEqualCaseInsensitive(a_PARSER_processing_KeyWord, PARSER_HEIGHT_geometry_keyword);
    }


    /**
     * Returns number of discovered widgets for the
     * current processed file '_current_processed_UI_File___full_path' !
     */
    virtual int process_Current_Registered_User_Interface___FILE();


    virtual bool setCurrentStart_Element(Yerith_ERP_Xml_Parser_Widget_Element *A_start_Widget_Xml_Element);


private:

    inline
    Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *get_All___XmlWidgetElementsFOR_HTML_web_generation
                                                                (QString an_user_interface_file)
    {
        _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation.value(an_user_interface_file);
    }


public:

    #include "yerith-web-systems-main-generator___KeyWords.hpp"


protected:


    QXmlStreamAttributes    _yri_current_Widget_START_element_attributes;

    QXmlStreamReader        *_yri_An_xml_stream_Reader;


    QMap<QString, Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS *>     _yri_file___TO___XmlWidgetElementsFOR_HTML_web_generation;


    Yerith_ERP_Xml_Parser_Widget_Element *_last_returned_Widget_Element;

    Yerith_ERP_Xml_Parser_Widget_Element *_last_returned_Widget_SUB_Element;


    YerithERPWindows        *_all_windows;

    QString                 _current_start_element;

    QString                 _current_processed_UI_File___full_path;

};








#endif //_YERITH_WEB_SYSTEMS_MAIN_GENERATOR_HPP_


