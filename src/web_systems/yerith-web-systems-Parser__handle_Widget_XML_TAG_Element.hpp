/*
 * yerith-web-systems-Parser__handle_Widget_XML_TAG_Element.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_WEB_SYSTEMS_MAIN_PARSER_HANDLE_WIDGET_XML_TAG_ELEMENT_HPP_
#define _YERITH_WEB_SYSTEMS_MAIN_PARSER_HANDLE_WIDGET_XML_TAG_ELEMENT_HPP_


#include "yerith-web-systems-main-parser_XML_Tag_Element.hpp"


#include "yerith-erp-xml-parser-widget-element.hpp"


#include "yerith-web-systems-main-generator.hpp"



class YERITH_WEB_SYSTEMS_MAIN_GENERATOR;

class Yerith_ERP_Xml_Parser___Main_Parser;


class Yerith_ERP_Xml_PARSER___handle_Widget_XML_TAG_Element : public Yerith_ERP_Xml_Parser___Main_Parser
{
public:

    inline Yerith_ERP_Xml_PARSER___handle_Widget_XML_TAG_Element(YERITH_WEB_SYSTEMS_MAIN_GENERATOR *A_web_systems_main_generator_POINTER)
    :Yerith_ERP_Xml_Parser___Main_Parser(A_web_systems_main_generator_POINTER)
    {
    }

    virtual inline ~Yerith_ERP_Xml_PARSER___handle_Widget_XML_TAG_Element()
    {
    }
};








#endif //_YERITH_WEB_SYSTEMS_MAIN_PARSER_HANDLE_WIDGET_XML_TAG_ELEMENT_HPP_


