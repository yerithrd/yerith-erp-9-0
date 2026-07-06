/*
 * yerith-erp-xml-parser-widget-element.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-xml-parser-widget-element.hpp"


#include "yerith-web-systems-main-generator.hpp"



bool Yerith_ERP_Xml_Parser_Widget_Element::is_Single_XML_TAG_Content_Value_STRING()
{
    if (YerithUtils::isEqualCaseInsensitive(_a_widget_xml_tag_name_VALUE_str, YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_X_geometry_keyword)     ||
        YerithUtils::isEqualCaseInsensitive(_a_widget_xml_tag_name_VALUE_str, YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_Y_geometry_keyword)     ||
        YerithUtils::isEqualCaseInsensitive(_a_widget_xml_tag_name_VALUE_str, YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_WIDTH_geometry_keyword) ||
        YerithUtils::isEqualCaseInsensitive(_a_widget_xml_tag_name_VALUE_str, YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_HEIGHT_geometry_keyword))
    {
        return true;
    }

    return false;
}


QString Yerith_ERP_Xml_Parser_Widget_Element::toString__No_Geometry()
{
    if (is_Not_Single_XML_TAG_Content_Value_STRING())
    {
        return QObject::tr("<%1 | '%2' | '%3'>")
               .arg(_a_widget_xml_tag_name,
                    _a_widget_xml_class_name,
                    _a_widget_xml_name);
    }
    else
    {
        return QObject::tr("<%1 | '%2' | '%3' | '%4'>")
               .arg(_a_widget_xml_tag_name,
                    _a_widget_xml_class_name,
                    _a_widget_xml_name,
                    _a_widget_xml_tag_name_VALUE_str);
    }
}


QString Yerith_ERP_Xml_Parser_Widget_Element::toString()
{
    if (is_Not_Single_XML_TAG_Content_Value_STRING())
    {
        return QObject::tr("<%1 | '%2' | %3'> \n"
                           "\t<x='%5', y='%6', width='%7', height='%8'>")
                   .arg(_a_widget_xml_tag_name,
                        _a_widget_xml_class_name,
                        _a_widget_xml_name,
                        Get___geometry_X_axis_position(),
                        Get___geometry_Y_axis_position(),
                        Get___geometry_WIDTH(),
                        Get___geometry_HEIGHT());
    }
    else
    {
        return QObject::tr("<%1 | '%2' | %3' | '%4'> \n"
                           "\t<x='%5', y='%6', width='%7', height='%8'>")
                   .arg(_a_widget_xml_tag_name,
                        _a_widget_xml_class_name,
                        _a_widget_xml_name,
                        _a_widget_xml_tag_name_VALUE_str,
                        Get___geometry_X_axis_position(),
                        Get___geometry_Y_axis_position(),
                        Get___geometry_WIDTH(),
                        Get___geometry_HEIGHT());
    }
}
