/*
 * yerith-erp_web_SYSTEM_discovered_Widgets-table-view.hpp
 *
 * Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _SRC_ADMIN_YERITH_ERP_WEB_SYSTEMS_DISCOVERED_WIDGETS_TABLE_VIEW_HPP_
#define _SRC_ADMIN_YERITH_ERP_WEB_SYSTEMS_DISCOVERED_WIDGETS_TABLE_VIEW_HPP_



#include "src/widgets/widgets-table/yerith-erp-table-widget.hpp"


#include "src/web_systems/yerith-erp-xml-parser-widget-element.hpp"



class Yerith_ERP_Xml_Parser_Widget_Element;


class YerithERPWEBsystemDiscoveredWidgetsTableWidget : public YerithTableWidget
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

	inline YerithERPWEBsystemDiscoveredWidgetsTableWidget(QWidget *parent = 0)
	:YerithTableWidget(parent),
	 _xml_tag_name_Item(0),
     _xml_class_name_Item(0),
     _xml_name_Item(0),
     _value_str_Item(0),
     _X_axis_geometry_Item(0),
     _Y_axis_geometry_Item(0),
     _WIDTH_axis_geometry_Item(0),
     _HEIGHT_axis_geometry_Item(0)
	{
		setRowCount(YerithERPConfig::MAX_Widgets_Discovered_row_COUNT);
	}


	virtual inline ~YerithERPWEBsystemDiscoveredWidgetsTableWidget()
	{
	}


    virtual inline int addArticle(Yerith_ERP_Xml_Parser_Widget_Element &a_yerith_ERP_Xml_Parser_Widget_Element)
    {
        addArticle(a_yerith_ERP_Xml_Parser_Widget_Element._a_widget_xml_tag_name,
                   a_yerith_ERP_Xml_Parser_Widget_Element._a_widget_xml_class_name,
                   a_yerith_ERP_Xml_Parser_Widget_Element._a_widget_xml_name,
                   a_yerith_ERP_Xml_Parser_Widget_Element._a_widget_xml_tag_name_VALUE_str,
                   a_yerith_ERP_Xml_Parser_Widget_Element.Get___geometry_X_axis_position(),
                   a_yerith_ERP_Xml_Parser_Widget_Element.Get___geometry_Y_axis_position(),
                   a_yerith_ERP_Xml_Parser_Widget_Element.Get___geometry_WIDTH(),
                   a_yerith_ERP_Xml_Parser_Widget_Element.Get___geometry_HEIGHT());
    }


    int addArticle(QString XML_tag_name_Item,
                   QString XML_class_name_Item,
                   QString XML_name_Item,
                   QString Value_str_Item,
                   QString My_X_axis_geometry_Item,
                   QString My_Y_axis_geometry_Item,
                   QString My_WIDTH_axis_geometry_Item,
                   QString My_HEIGHT_axis_geometry_Item);



    static const unsigned int _XML_TAG_NAME_ITEM;

    static const unsigned int _XML_CLASS_NAME_ITEM;

    static const unsigned int _XML_NAME_ITEM;

    static const unsigned int _VALUE_STR_ITEM;

    static const unsigned int _X_AXIS_GEOMETRY_ITEM;

    static const unsigned int _Y_AXIS_GEOMETRY_ITEM;

    static const unsigned int _WIDTH_AXIS_GEOMETRY_ITEM;

    static const unsigned int _HEIGHT_AXIS_GEOMETRY_ITEM;



private:

	YerithQTableWidgetItem *_xml_tag_name_Item;

	YerithQTableWidgetItem *_xml_class_name_Item;

	YerithQTableWidgetItem *_xml_name_Item;

	YerithQTableWidgetItem *_value_str_Item;

	YerithQTableWidgetItem *_X_axis_geometry_Item;

	YerithQTableWidgetItem *_Y_axis_geometry_Item;

	YerithQTableWidgetItem *_WIDTH_axis_geometry_Item;

	YerithQTableWidgetItem *_HEIGHT_axis_geometry_Item;
};


#endif // _SRC_ADMIN_YERITH_ERP_WEB_SYSTEMS_DISCOVERED_WIDGETS_TABLE_VIEW_HPP_
