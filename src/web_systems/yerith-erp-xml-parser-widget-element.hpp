/*
 * yerith-erp-xml-parser-widget-element.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_WEB_SYSTEMS_Widget_Element_HPP_
#define _YERITH_WEB_SYSTEMS_Widget_Element_HPP_


#include "src/utils/yerith-erp-utils.hpp"


class Yerith_ERP_Xml_Parser_Widget_Element : public QObject
{
    Q_OBJECT

public:


    YERITH_CLASS_OPERATORS


    inline Yerith_ERP_Xml_Parser_Widget_Element()
    :___geometry_X_axis_position(0),
     ___geometry_Y_axis_position(0),
     ___geometry_WIDTH(0),
     ___geometry_HEIGHT(0)
    {
    }

    inline Yerith_ERP_Xml_Parser_Widget_Element(QString A_widget_xml_tag_name)
    :___geometry_X_axis_position(0),
     ___geometry_Y_axis_position(0),
     ___geometry_WIDTH(0),
     ___geometry_HEIGHT(0),
     _a_widget_xml_tag_name(A_widget_xml_tag_name)
    {
    }


    virtual inline ~Yerith_ERP_Xml_Parser_Widget_Element()
    {
    }


    virtual bool is_Single_XML_TAG_Content_Value_STRING();


    virtual inline bool is_Not_Single_XML_TAG_Content_Value_STRING()
    {
        return (! is_Single_XML_TAG_Content_Value_STRING());
    }


    virtual QString toString__No_Geometry();

    virtual QString toString();


    virtual inline void print_With_Developer_string__No_Geometry_added(QString a_developer_string_added)
    {
        QDEBUG_STRING_OUTPUT_2(a_developer_string_added,
                               toString__No_Geometry());
    }


    virtual inline void print_With_Developer_string_added(QString a_developer_string_added)
    {
        QDEBUG_STRING_OUTPUT_2(a_developer_string_added,
                               toString());
    }


    virtual inline QString Get___geometry_X_axis_position()
    {
        return QString::number(___geometry_X_axis_position);
    }

    virtual inline QString Get___geometry_Y_axis_position()
    {
        return QString::number(___geometry_Y_axis_position);
    }

    virtual inline QString Get___geometry_WIDTH()
    {
        return QString::number(___geometry_WIDTH);
    }

    virtual inline QString Get___geometry_HEIGHT()
    {
        return QString::number(___geometry_HEIGHT);
    }


public:

    int ___geometry_X_axis_position;

    int ___geometry_Y_axis_position;

    int ___geometry_WIDTH;

    int ___geometry_HEIGHT;


    QString _a_widget_xml_tag_name;

    QString _a_widget_xml_class_name;

    QString _a_widget_xml_name;

    QString _a_widget_xml_tag_name_VALUE_str;

};



#endif //_YERITH_WEB_SYSTEMS_Widget_Element_HPP_


