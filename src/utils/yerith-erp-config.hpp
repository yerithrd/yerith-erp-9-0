/*
 * yerith-erp-config.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_YERITH_CONFIG_HPP_
#define SRC_YERITH_CONFIG_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include <QtCore/QDate>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>

class YerithERPConfig
{
public:

    YERITH_CLASS_OPERATORS

    static QString _db_type;

    static QString _db_name;

    static QString _db_ip_address;

    static QString _db_user_name;

    static QString _db_user_pwd;

    static QString _db_connection_options;

    static bool ouvrirRegistreDeCaisse;

    static bool ___function___REMOVE_DETAILED_INPUT_entrer_stock;

    static bool ___yri_web_system_opens_Directly_in_browser_Webly;

    static bool ___Feature___DONT_SAVE_SALES_HISTORY___;

    static bool Show_yri_web_system_detailed___Ouput_also_in_Console;

    static bool Show_yri_web_system_Ouput_also_in_Console;

    static bool Show_Yri_WEB__System__Window_TAB;

    static bool Show_Yr_Db_Runtime_VERIFICATION_monitoring_Window_TAB;

    static bool SHOW_DATABASE_RAW;

    static QString currency;

    static QString IP_ADDRESS_NETWORK_printer;

    static QString BLANKING_timing___SECONDS;

    static QString printer;

    static QString fullpathToBACKUP_YERITH_ERP_3_DIRECTORY;

    static QString pathToPdfCOMPANY_LOGO;

    static QString pathToPdfReader;

    static QString pathToThermalPrinterDeviceFile;

    static QString pathToLatexSystemRootFolder;

    static QString receiptFormat;

    static QString receiptType;

    static QString salesStrategy;

    static QString YERITH_ERP_9_0_yri_web_system_last_web_html_PaGE;

    static QString YERITH_ERP_3_0_yri_web_system_MoziLLa_FirefoX___ID;

    static QString YRI_DB_RUNTIME_VERIF_SYSTEM_DAEMON_ID_STR;

    static QString YRI_DB_RUNTIME_VERIF_SYSTEM_DAEMON_ID;

    static QString YERITH_ERP_3_0_SYSTEM_DAEMON_ID_STR;

    static QString YERITH_ERP_3_0_SYSTEM_DAEMON_ID;

    static QString YERITH_ERP_3_0_yri_web_system_MoziLLa_FirefoX___HOME_FOLDER;

    static QString YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER;

    static QString YERITH_ERP_3_0_yri_db_runtime_verif_HOME_FOLDER;

    static QString YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER;

    static QString YERITH_ERP_3_0_HOME_FOLDER;

    static QString YERITH_ERP_3_0_USER_LOCAL_SETTINGS_FOLDER;

    static QString FILE_ABSOLUTEPATH_YERITH_ERP_3_0_SYSTEM_LOCAL_CONFIGURATION_PROPERTY_FILE;

    static QString FILE_ABSOLUTEPATH_YERITH_ERP_3_0_MANUEL_DE_LUTILISATEUR_MANAGER;

    static QString FILE_ABSOLUTEPATH_YERITH_ERP_3_0_MANUEL_DE_LUTILISATEUR_MANAGER_EN;

    static uint periode_permise_de_retour_pour_articLES;

    static uint backup_restore_yerith_erp_3_time_interval;

    static uint alert_period_time_interval;

    static uint alert_quantity_time_interval;

    static uint pagination_number_of_table_rows;

    static uint MAX_Widgets_Discovered_row_COUNT;

    static uint MAX_LAST_SIGNALS_SOURCE_TARGET_COUNT;

    static uint LINE_FEED_CHARACTER_COUNT_FOR_THERMAL_SMALL_PRINTING;

    static uint max_string_display_length;

    static double tva_value;

    static QString annee_depart_rapports_chiffre_affaire_value;

    static QString annee_depart_pour_la_pagination;

    static QString pathToMARIA_DB_BASE_DIR;

    static QString mozillaFirefoxWEBbrowserBinaryFullPath;

    static QString temporaryFilesDir;

    static QString THIS_SITE_LOCALISATION_NAME;

    static bool _distantSiteConnected;

    static QString _connectedSite;

    static QString _connectedSiteIPAddress;

    static const QString RECEIPT_FORMAT_PETIT;

    static const QString RECEIPT_FORMAT_GRAND_A5PAPER;

    static const QString RECEIPT_FORMAT_GRAND_A4PAPER;

    static const QString STRATEGIE_VENTE_SORTIE_ALL;

    static const QString STRATEGIE_VENTE_SORTIE_FIFO;

    static const QString STRATEGIE_VENTE_SORTIE_LIFO;

    static const QString STRATEGIE_VENTE_SORTIE_FEFO;

    static const int Show_Yri_WEB__System_Window;

    static const int HIDE_Yri_WEB__System_Window;

    static const int Show_Yr_Db_Runtime_VERIFICATION_monitoring_Window;

    static const int HIDE_Yr_Db_Runtime_VERIFICATION_monitoring_Window;

    static const int SHOW_DATABASE_RAW_table_column;

    static const int HIDE_DATABASE_RAW_table_column;

    static const int OPEN_CASH_DRAWER;

    static const int CLOSE_CASH_DRAWER;

    static const unsigned int CONFIG_ALERT_PERIOD_TIME_INTERVAL;

    static const unsigned int CONFIG_ALERT_QUANTITY_TIME_INTERVAL;

    static const unsigned int CONFIG_TVA_VALUE;

    static const unsigned int CONFIG_SALES_STRATEGY;

    static const unsigned int CONFIG_CURRENCY;

    static const unsigned int CONFIG_PAGINATION_PAGE_BEGIN_YEAR;

    static const unsigned int CONFIG_BACKUP_DATABASE_YERITH_ERP_3_TIME_INTERVAL;

    static const unsigned int CONFIG_DIRECTORY_FULL_PATH_FOR_BACKUP_DATABASE_YERITH_ERP_3;

    static const unsigned int CONFIG_BLANKING_TIMING;


    //static const SALES_STRATEGY getSalesStrategy(QString salesStrategyValue);

    inline static QString pathToPs2Pdf()
    {
        return QString("%1/ps2pdf").arg(pathToLatexSystemRootFolder);
    }

    inline static QString pathToDvips()
    {
        return QString("%1/dvips").arg(pathToLatexSystemRootFolder);
    }

    inline static QString pathToLatex()
    {
        return QString("%1/latex").arg(pathToLatexSystemRootFolder);
    }

    inline static QString pathToPdfLatex()
    {
        return QString("%1/pdflatex").arg(pathToLatexSystemRootFolder);
    }

    inline static QString pathToLualatex()
    {
        return QString("%1/lualatex").arg(pathToLatexSystemRootFolder);
    }

    inline static QDate GET_YERITH_BUSINESS_DASHBOARD_DEFAULT_START_DATE()
    {
        return
                        QDate(YerithERPConfig::
                              annee_depart_rapports_chiffre_affaire_value.toInt(), 1, 1);
    }

    inline static QDate GET_YERITH_PAGING_DEFAULT_START_DATE()
    {
        return QDate(YerithERPConfig::annee_depart_pour_la_pagination.toInt(),
                     1, 1);
    }

    static void initYerithConfig(QString initCfg);

    static void saveYerithConfig();
};

#endif /* SRC_YERITH_CONFIG_HPP_ */
