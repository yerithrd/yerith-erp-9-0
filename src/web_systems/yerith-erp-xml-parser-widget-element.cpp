/*
 * yerith-erp-xml-parser-widget-element.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-xml-parser-widget-element.hpp"


#include "yerith-web-systems-main-generator.hpp"



bool Yerith_ERP_Xml_Parser_Widget_Element::is_Single_XML_TAG_Content_Value_STRING()
{
    if (YerithUtils::isEqualCaseInsensitive(_a_widget_xml_tag_name_VALUE_str, YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_string_text_keyword)    ||
        YerithUtils::isEqualCaseInsensitive(_a_widget_xml_tag_name_VALUE_str, YERITH_WEB_SYSTEMS_MAIN_GENERATOR::PARSER_X_geometry_keyword)     ||
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


QString Yerith_ERP_Xml_Parser_Widget_Element::generate_SPEC_HTML_DSL_code()
{
    QString spec_html_dsl_code;

    if (_a_widget_xml_tag_name.isEmpty())
    {
        return "";
    }


    QString spec_html_dsl_KEYWORD;
    QString spec_html_dsl_PARAMETERS;



    if (YerithUtils::isEqualCaseInsensitive("YerithERPSiteTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPProductDepartmentTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPUserTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPBankAccountTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPCategoryTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPFinancialExpenseTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPAlertTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPAlertesTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPComptes_doperations_comptabilites_TableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPAchatsTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPClientsTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPProgrammesDeFideliteClientsTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPGroupesDePaieHRTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPFournisseursTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPGroupesDeClientsTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERP_CHARGES_FINANCIERES_TableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPVentesTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPPaiementsTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPStocksTableView", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("YerithERPMarchandisesTableView", _a_widget_xml_class_name) )
    {
        spec_html_dsl_PARAMETERS = QString("'%1'; ''")
                                    .arg(_a_widget_xml_name);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_table_view";
    }
    else if (YerithUtils::isEqualCaseInsensitive("YerithTableView", _a_widget_xml_class_name) ||
             YerithUtils::isEqualCaseInsensitive("QTableView", _a_widget_xml_class_name) )
    {
        spec_html_dsl_PARAMETERS = QString("'%1'; ''")
                                    .arg(_a_widget_xml_name);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_table_view";
    }
    else if (YerithUtils::isEqualCaseInsensitive("YerithDateTimeEdit", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("QDateTimeEdit", _a_widget_xml_class_name) )
    {
        spec_html_dsl_PARAMETERS = QString("'%1'; ''")
                                    .arg(_a_widget_xml_name);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_date_time_edit";
    }
    else if (YerithUtils::isEqualCaseInsensitive("YerithPushButton", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("QPushButton", _a_widget_xml_class_name) )
    {
        spec_html_dsl_PARAMETERS = QString("'%1'")
                                    .arg(_a_widget_xml_tag_name_VALUE_str);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_button";
    }
    else if (YerithUtils::isEqualCaseInsensitive("YerithComboBox", _a_widget_xml_class_name) ||
        YerithUtils::isEqualCaseInsensitive("QComboBox", _a_widget_xml_class_name) )
    {
        spec_html_dsl_PARAMETERS = QString("'%1'; ''")
                                    .arg(_a_widget_xml_name);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_combo_box";
    }
    else if (YerithUtils::isEqualCaseInsensitive("YerithERPQCheckBox", _a_widget_xml_class_name)    ||
            YerithUtils::isEqualCaseInsensitive("QCheckBox", _a_widget_xml_class_name))
    {
        spec_html_dsl_PARAMETERS = QString("'%1'; '%2'")
                                    .arg(_a_widget_xml_name,
                                         _a_widget_xml_tag_name_VALUE_str);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_check_box";
    }
    else if (YerithUtils::isEqualCaseInsensitive("YerithLineEdit", _a_widget_xml_class_name) ||
             YerithUtils::isEqualCaseInsensitive("QLineEdit", _a_widget_xml_class_name))
    {
        spec_html_dsl_PARAMETERS = QString("'%1'; ''")
                                    .arg(_a_widget_xml_name);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_input_text";
    }
    else if (YerithUtils::isEqualCaseInsensitive("QLabel", _a_widget_xml_class_name))
    {
        spec_html_dsl_PARAMETERS = QString("'%1'")
                                    .arg(_a_widget_xml_tag_name_VALUE_str);

        spec_html_dsl_KEYWORD = "yri_html_page_Widget_label_text";
    }


    QString type_And_ATTRIBUTES = QString("%1 (%2)   ")
                                    .arg(spec_html_dsl_KEYWORD,
                                         spec_html_dsl_PARAMETERS);

    QString geometry = QString("{ '%1'; '%2'; '%3'; '%4' };")
                        .arg(Get___geometry_X_axis_position(),
                             Get___geometry_Y_axis_position(),
                             Get___geometry_WIDTH(),
                             Get___geometry_HEIGHT());

    spec_html_dsl_code = type_And_ATTRIBUTES + geometry;


    return spec_html_dsl_code;
}
