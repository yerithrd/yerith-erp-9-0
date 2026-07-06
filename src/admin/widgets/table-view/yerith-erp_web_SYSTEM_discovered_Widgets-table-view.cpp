/*
 * yerith-erp_web_SYSTEM_discovered_Widgets-table-view.cpp
 *
 * Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp_web_SYSTEM_discovered_Widgets-table-view.hpp"



const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_XML_TAG_NAME_ITEM = 0;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_XML_CLASS_NAME_ITEM = 1;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_XML_NAME_ITEM = 2;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_VALUE_STR_ITEM = 3;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_X_AXIS_GEOMETRY_ITEM = 4;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_Y_AXIS_GEOMETRY_ITEM = 5;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_WIDTH_AXIS_GEOMETRY_ITEM = 6;

const unsigned int YerithERPWEBsystemDiscoveredWidgetsTableWidget::_HEIGHT_AXIS_GEOMETRY_ITEM = 7;



int YerithERPWEBsystemDiscoveredWidgetsTableWidget::
                        addArticle(QString XML_tag_name_Item,
                                   QString XML_class_name_Item,
                                   QString XML_name_Item,
                                   QString Value_str_Item,
                                   QString My_X_axis_geometry_Item,
                                   QString My_Y_axis_geometry_Item,
                                   QString My_WIDTH_axis_geometry_Item,
                                   QString My_HEIGHT_axis_geometry_Item)
{
    setRowHeight(_curRow, 1);

    setRowCount(_curRow + 1);

	_xml_tag_name_Item          = new YerithQTableWidgetItem(XML_tag_name_Item, false);
    _xml_class_name_Item        = new YerithQTableWidgetItem(XML_class_name_Item, false);
	_xml_name_Item              = new YerithQTableWidgetItem(XML_name_Item, false);
	_value_str_Item             = new YerithQTableWidgetItem(Value_str_Item, false);
	_X_axis_geometry_Item       = new YerithQTableWidgetItem(My_X_axis_geometry_Item, false);
	_Y_axis_geometry_Item       = new YerithQTableWidgetItem(My_Y_axis_geometry_Item, false);
	_WIDTH_axis_geometry_Item   = new YerithQTableWidgetItem(My_WIDTH_axis_geometry_Item, false);
	_HEIGHT_axis_geometry_Item  = new YerithQTableWidgetItem(My_HEIGHT_axis_geometry_Item, false);


    _mapListIdxToElement_db_ID.insert(_curRow, XML_tag_name_Item);

    unsigned idx = 0;

    //Each call to setItem triggers a call to YerithPointDeVenteWindow::handleQteChange
    setItem(_curRow, idx++, _xml_tag_name_Item);
    setItem(_curRow, idx++, _xml_class_name_Item);
    setItem(_curRow, idx++, _xml_name_Item);
    setItem(_curRow, idx++, _value_str_Item);
    setItem(_curRow, idx++, _X_axis_geometry_Item);
    setItem(_curRow, idx++, _Y_axis_geometry_Item);
    setItem(_curRow, idx++, _WIDTH_axis_geometry_Item);
    setItem(_curRow, idx++, _HEIGHT_axis_geometry_Item);


	_xml_tag_name_Item->setFlags(_myQStandardItemFlags);
	_xml_class_name_Item->setFlags(_myQStandardItemFlags);
	_xml_name_Item->setFlags(_myQStandardItemFlags);
	_value_str_Item->setFlags(_myQStandardItemFlags);
	_X_axis_geometry_Item->setFlags(_myQStandardItemFlags);
	_Y_axis_geometry_Item->setFlags(_myQStandardItemFlags);
	_WIDTH_axis_geometry_Item->setFlags(_myQStandardItemFlags);
	_HEIGHT_axis_geometry_Item->setFlags(_myQStandardItemFlags);


    selectRow(_curRow);

    resizeColumnsToContents();

    int lastCurRow = _curRow;

    if (_curRow < YerithERPConfig::MAX_Widgets_Discovered_row_COUNT)
    {
    	++_curRow;
    }
    else
    {
    	_curRow = 0;
    }

    emit addedYerithTableWidget();

    return lastCurRow;
}
