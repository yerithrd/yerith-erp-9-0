/*
 * yerith-erp-xml-parser-QLIST___widget-element.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_WEB_SYSTEMS___LIST___Widget_Element_HPP_
#define _YERITH_WEB_SYSTEMS___LIST___Widget_Element_HPP_


#include "src/utils/yerith-erp-utils.hpp"


#include <QtCore/QList>


class Yerith_ERP_Xml_Parser_Widget_Element;


class Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS : public QObject
{
    Q_OBJECT

public:


    YERITH_CLASS_OPERATORS


    inline Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS(QString an_USER_INTERFACE_ui_file___For___HTML__Web__Generation)
    :___An___USER_INTERFACE_ui_file___For___HTML__Web__Generation(an_USER_INTERFACE_ui_file___For___HTML__Web__Generation)
    {
    }


    virtual inline ~Yerith_ERP_Xml_Parser___QLIST__Of___Widget_ElementS()
    {
    }


    //Convenience method for compatibility with QtCore/QList.
    virtual inline int indexOf(Yerith_ERP_Xml_Parser_Widget_Element &value,
                               int from = 0)
    {
        return ___all___xml_widget_elements_for_html_web_generation
                .indexOf(&value,
                         from);
    }


    //Convenience method for compatibility with QtCore/QList.
    virtual inline Yerith_ERP_Xml_Parser_Widget_Element *get_element(uint position_in_qlist)
    {
        return
            ___all___xml_widget_elements_for_html_web_generation.at
                (position_in_qlist);
    }


    //Convenience method for compatibility with QtCore/QList.
    virtual inline int count(Yerith_ERP_Xml_Parser_Widget_Element &an_item_list_element)
    {
        return
            ___all___xml_widget_elements_for_html_web_generation.count
                (&an_item_list_element);
    }

    //Convenience method for compatibility with QtCore/QList.
    virtual inline int count()
    {
        return ___all___xml_widget_elements_for_html_web_generation.count();
    }

    //Convenience method for compatibility with QtCore/QList.
    virtual inline void append(QList<Yerith_ERP_Xml_Parser_Widget_Element *> & some_list_items)
    {
        ___all___xml_widget_elements_for_html_web_generation
            .append(some_list_items);
    }


    virtual inline void append_an_USER_Interface_File_Element
                            (Yerith_ERP_Xml_Parser_Widget_Element *an_erp_xml_parser_Widget_Element)
    {
        ___all___xml_widget_elements_for_html_web_generation
            .append(an_erp_xml_parser_Widget_Element);
    }


    virtual inline QString GET___UI___File___Name()
    {
        return ___An___USER_INTERFACE_ui_file___For___HTML__Web__Generation;
    }


    virtual inline int get_size()
    {
        return ___all___xml_widget_elements_for_html_web_generation.size();
    }


protected:

    QList<Yerith_ERP_Xml_Parser_Widget_Element *> ___all___xml_widget_elements_for_html_web_generation;


private:

    QString ___An___USER_INTERFACE_ui_file___For___HTML__Web__Generation;

};



#endif //_YERITH_WEB_SYSTEMS___LIST___Widget_Element_HPP_


