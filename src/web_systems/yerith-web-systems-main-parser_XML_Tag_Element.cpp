/*
 * yerith-web-systems-main-parser_XML_Tag_Element.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-web-systems-main-parser_XML_Tag_Element.hpp"


#include "yerith-web-systems-main-generator.hpp"



Yerith_ERP_Xml_Parser___Main_Parser::Yerith_ERP_Xml_Parser___Main_Parser(YERITH_WEB_SYSTEMS_MAIN_GENERATOR *A_web_systems_main_generator_POINTER)
:_yri_An_xml_stream_Reader(0),
 _yri_web_systems_main_generator_POINTER(A_web_systems_main_generator_POINTER),
 _all_windows(0)
{
    if (0 != A_web_systems_main_generator_POINTER)
    {
        _yri_An_xml_stream_Reader = A_web_systems_main_generator_POINTER->GET___yri_An_xml_stream_Reader();
    }
}


Yerith_ERP_Xml_Parser_Widget_Element *
Yerith_ERP_Xml_Parser___Main_Parser::handle_XML_TAG_Element(QString     tag_name,
                                                            QString     A_property_name,
                                                            QString     A_property_Class /* = YerithUtils::EMPTY_STRING */,
                                                            QString     A_property_name_to_FIND_now_geometry /* = YerithUtils::EMPTY_STRING */,
                                                            bool       *A_METHOD_TO_call() /* = 0 */,
                                                            bool        A_Condition_boolean /* = false */)
{
    if (0 == _yri_An_xml_stream_Reader)
    {
        QDEBUG_STRING_OUTPUT_1("Please set a non null pointer of _yri_web_systems_main_generator_POINTER->_yri_An_xml_stream_Reader");
        return 0;
    }

    if (0 == _yri_web_systems_main_generator_POINTER)
    {
        QDEBUG_STRING_OUTPUT_1("Please set a non null pointer as an instance of class YERITH_WEB_SYSTEMS_MAIN_GENERATOR");
        return 0;
    }


    Yerith_ERP_Xml_Parser_Widget_Element *next_token___WIDGET_Property_class = 0;


    next_token___WIDGET_Property_class = new Yerith_ERP_Xml_Parser_Widget_Element(tag_name);


    QString next_property_NAME;

    QString next_token;

    QString next_token_NAME;

    QString current_token_TEXT;

    QString a_tmp_str;


    enum QXmlStreamReader::TokenType type___next_token;

    bool a_valid_NEXT___Token_processed = false;

    bool is_geometry_property_Name = true;


    QXmlStreamAttributes yri_current_Widget_START_element_attributes;

    yri_current_Widget_START_element_attributes = _yri_An_xml_stream_Reader->attributes();

    do
    {
        type___next_token = _yri_An_xml_stream_Reader->readNext();

        next_token = _yri_An_xml_stream_Reader->tokenString();

        next_token_NAME = _yri_An_xml_stream_Reader->name().toString();

        next_property_NAME =
                    yri_current_Widget_START_element_attributes.value(A_property_name).toString().trimmed();


        if (! A_property_name_to_FIND_now_geometry.isEmpty())
        {
            is_geometry_property_Name =
                YerithUtils::isEqualCaseInsensitive(A_property_name_to_FIND_now_geometry,
                                                    next_property_NAME);

//            QDEBUG_STRING_OUTPUT_2(QString("A_property_name: (%1) | A_property_name_to_FIND_now_geometry")
//                                     .arg(A_property_name),
//                                   BOOL_TO_STRING(is_geometry_property_Name));
        }


        if (is_geometry_property_Name)
        {
            current_token_TEXT = _yri_An_xml_stream_Reader->text().toString().trimmed();

            next_token___WIDGET_Property_class->_a_widget_xml_name = next_property_NAME;

            if (! A_property_Class.isEmpty())
            {
                a_tmp_str = Get_LAST_RETURNED_WIDGET_ELEMENT___a_widget_xml_class_name
                                    (yri_current_Widget_START_element_attributes,
                                     A_property_Class);
            }
            else
            {
                a_tmp_str = _yri_web_systems_main_generator_POINTER
                                ->Get_LAST_RETURNED_WIDGET_ELEMENT___a_widget_xml_name();
            }


            next_token___WIDGET_Property_class->_a_widget_xml_class_name = a_tmp_str;

            next_token___WIDGET_Property_class->_a_widget_xml_tag_name_VALUE_str = current_token_TEXT;


            a_valid_NEXT___Token_processed = true;

            if (0 != A_METHOD_TO_call)
            {
                a_valid_NEXT___Token_processed = (*A_METHOD_TO_call)();
            }


            if (a_valid_NEXT___Token_processed             &&
                YerithUtils::isEqualCaseInsensitive("widget",
                                                    tag_name))
            {
                _yri_web_systems_main_generator_POINTER
                    ->add_An___XmlWidgetElementsFOR_HTML_web_generation(next_token___WIDGET_Property_class);
            }

        }
    }
    while ( A_Condition_boolean &&
            !_yri_An_xml_stream_Reader->atEnd());


    return next_token___WIDGET_Property_class;
}






