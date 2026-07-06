/*
 * yerith-web-systems-main-parser_XML_Tag_Element.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_WEB_SYSTEMS_MAIN_PARSER_XML_TAG_ELEMENT_HPP_
#define _YERITH_WEB_SYSTEMS_MAIN_PARSER_XML_TAG_ELEMENT_HPP_


#include "yerith-erp-xml-parser-widget-element.hpp"


#include <QXmlStreamReader>


class YERITH_WEB_SYSTEMS_MAIN_GENERATOR;


class YerithERPWindows;
class Yerith_ERP_Xml_Parser_Widget_Element;
class QXmlStreamReader;


class Yerith_ERP_Xml_Parser___Main_Parser
{
public:

    Yerith_ERP_Xml_Parser___Main_Parser(YERITH_WEB_SYSTEMS_MAIN_GENERATOR *A_web_systems_main_generator_POINTER);


    virtual inline ~Yerith_ERP_Xml_Parser___Main_Parser()
    {
    }


    virtual inline QString Get_LAST_RETURNED_WIDGET_ELEMENT___a_widget_xml_class_name
                        (QXmlStreamAttributes   &yri_current_Widget_START_element_attributes,
                         QString                a_value_attribute_to_query)
    {
        return
            yri_current_Widget_START_element_attributes.value(a_value_attribute_to_query).toString();
    }


public slots:

    virtual Yerith_ERP_Xml_Parser_Widget_Element *
    handle_XML_TAG_Element(QString     tag_name,
                           QString     A_property_name,
                           QString     A_property_Class = YerithUtils::EMPTY_STRING,
                           QString     A_property_name_to_FIND_now_geometry = YerithUtils::EMPTY_STRING,
                           bool       *A_METHOD_TO_call() = 0,
                           bool        A_Condition_boolean = false);


protected:

    QXmlStreamReader                    *_yri_An_xml_stream_Reader;

    YERITH_WEB_SYSTEMS_MAIN_GENERATOR   *_yri_web_systems_main_generator_POINTER;

    YerithERPWindows                    *_all_windows;
};








#endif //_YERITH_WEB_SYSTEMS_MAIN_PARSER_XML_TAG_ELEMENT_HPP_


