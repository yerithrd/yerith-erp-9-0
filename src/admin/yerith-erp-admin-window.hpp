/*
 * yerith-erp-admin-window.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_ADMIN_YERITH_ADMIN_WINDOW_HPP_
#define SRC_ADMIN_YERITH_ADMIN_WINDOW_HPP_

#include "../../ui_yerith-erp-admin-window.h"


#include "yerith-erp-qtable-widget-admin-window-commons.hpp"

#include "src/admin/yerith-erp-admin-windows-commons.hpp"

#include "src/yerith-erp-windows.hpp"

#include "admin-actions-subjects.hpp"


#include <QtCore/QDebug>

#include <QtWidgets/QMessageBox>


class YERITH_WEB_SYSTEMS_MAIN_GENERATOR;
class YerithERPDatabaseTableColumnInfo;
class YerithSqlTableModel;
class YerithLogger;
class YerithDatabase;


class YerithAdminWindow : public YerithQTableWidgetAdminWindowsCommons,
    					  public Ui_YerithAdminWindow
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


    enum YerithAdminWindowTabPositionsTypes
    {
        CONNECTER_LOCALISATION  = 0,
        DONNEES_ENTREPRISE      = 1,
        IMPORTER_CSV_TABLEAU    = 2,
        MAINTENANCE             = 3,
        OPERATIONS              = 4,
        PARAMETRES_APPLICATION  = 5,
        SYSTEME_DALERTES        = 6
    };


    enum YerithAdminWindowTab___maintenance_verification_DATABASE___PositionsTypes
    {
        RUNTIME_Verification_tab_number = 0,
        DATABASE_tab_number             = 1,
        web_SYSTEM_tab_number           = 2,
        FEATURES_tab_number             = 3
    };


    enum YerithAdminWindowTab___web_system___PositionsTypes
    {
        Widget_TAB_ONE                                      = 0,
        Widget_TAB_Two                                      = 1,
        Widget_TAB_Statistics                               = 2,
        Widget_TAB_Preview_Source_Code_YERITH_WEB_DSL_9_0   = 3
    };


    YerithAdminWindow();

    virtual ~YerithAdminWindow();

    virtual inline QToolBar *getQMainWindowToolBar()
    {
        return toolBar_adminWindow;
    }

    inline void setImporterParlant(bool aValue)
    {
        _importer_parlant = aValue;
    }

    inline bool getImporterParlant()
    {
        return _importer_parlant;
    }

    void setupValidators();

    void PRINT_SIGNALS_SOURCE_TARGET_info();

    void initialize_admin_importer_csv_tableau();

    void initialize_admin_Maintenance_Web_SYSTEM_widget_discovered_tableau();

    virtual void definirPasDeRole();

    virtual void definirAdministrateur();

    virtual void definirManager();

    virtual void rendreVisible(YerithSqlTableModel *stocksTableModel                = 0,
                               bool                 show_web_system_develop         = false,
                               bool                 show_action_mariadb_management  = false);


public slots:

    virtual void ___retranslateUi();


    virtual void Reset___tabWidget_maintenance_web_SYSTEM_tab();

    virtual void Reset___yri_web_SYSTEM();


private:

    virtual void SET_value___Of___label_importer_fichier_UI___number_widgets_STR(QString a___number_of_widgets_Value,
                                                                                 bool    display_qlabel = false);

public slots:

    virtual void SET_value___Of___label_importer_fichier_UI___number_widgets(int    a___number_of_widgets_Value,
                                                                             bool   display_qlabel = false);


    virtual void Clear_value___Of___label_importer_fichier_UI___number_widgets();


	void DISABLE_YRI_WEB_SYSTEM_gui_elements();

	void ENABLE_YRI_WEB_SYSTEM_gui_elements();

	void DISABLE_YRI_DB_RUNTIME_VERIF_BUTTONS();

	void ENABLE_YRI_DB_RUNTIME_VERIF_BUTTONS(bool Stop_BUTTON_DIsabled = true);

    void stop_TESTING_MAINTENANCE();

    void start_TESTING_MAINTENANCE(bool Stop_BUTTON_DIsabled = true);

    void enableAllOperationsTabPushButtons();

    void disableAllOperationsTabPushButtons();

    void setCurrentAdminWindowTitle(enum YerithAdminWindowTabPositionsTypes
                                    tabPosition);

    void handleTabChanged(int);

    void action_creer();

    void action_lister();

    void action_modifier();

    void action_supprimer();

    void action_exporter();

    void action_importer();

    void action_effacer();

    void gerer_choix_action();

    void choose_Web_ui_file_to_import();

    void choose_fichier_csv_a_importer();

    void choose_path_mariadb_client_dir();

    void choose_path_pdfReader();

    void choose_path_thermalPrinterDeviceFile();

    void choose_path_latex_system_root_folder();

    void choose_repertoire_des_sauvegardes();

    void choose_mozilla_firefox_web_browser_binary_full_path();

    void choose_repertoire_fichiers_temporaires();

    void read_configuration();

    void handle__tabWidget_maintenance_verification_DATABASE(int current_index);

    void handleThermalPrinterConfiguration(const QString &addedPrinterValue);

    void read_entreprise_info_database_table(bool initalizationValues = true);

    void read_YERITH_ERP_3_0_SYSTEM_DAEMON_init_configuration();

    void read_app_parameters_init_configuration();

    void reinitialiser_YERITH_ERP_3_0_SYSTEM_DAEMON_configuration();

    void reinitialiser_app_parameters_configuration();

    void enregistrer_entreprise_info_database_table();

    void enregistrer_YERITH_ERP_3_0_SYSTEM_DAEMON_configuration();

    void enregistrer_system_local_app_parameters_configuration();

    void enregistrer_app_parameters_configuration();

    inline void set_DBUS_CONNECTION_ERROR_TO_CLIENT(bool v)
    {
    	_DBUS_CONNECTION_ERROR_TO_CLIENT = v;
    }

    void REFRESH_STATUS_OF_YRI_DB_RUNTIME_VERIF_PROCESS();

    void Slot_____enable_____pushButton_Web_SYSTEMS_valider(const QString &new_ui_interface__Full_Path);

    void YRI_WEB_SYSTEM_OPENS_DIRECTLY_IN_BROWSER_WEBLY();

    void START_YRI_DB_RUNTIME_VERIF_GUI();

    void START_YRI_DB_RUNTIME_VERIF_DAEMON_PROCESS();

    void STOP_YRI_DB_RUNTIME_VERIF_DAEMON_PROCESS();

    void set_colour_status_of_alert_daemon_process_buttons();

    void start_alert_daemon_process();

    void stop_alert_daemon_process();

    void set_localisation_adresse_ip_text();

    void connecter_localisation_db();

    void deconnecter_localisation_db();

    virtual void deconnecter_utilisateur();


protected slots:

    virtual inline void Change_flag_language_Next_TO_TRANSlate()
    {
        YerithWindowsCommons::Change_flag_language_Next_TO_TRANSlate(*action_TRADUIRE_EN_ANGLAIS,
                                                                     *action_TRADUIRE_EN_FRANCAIS);
    }

    virtual bool imprimer_UNE_LISTE(bool *full_list = 0);


protected:

    virtual void set_shortcuts();


private slots:

    void Handle___tabWidget_maintenance_web_SYSTEM_tab(int current_tab_index);


    void Handle___tabWidget_maintenance_verification_DATABASE(int current_tab_index);


    virtual void Open_page_in_firefox_mozilla_brower___yri_web_SYSTEM();


    virtual inline void process_Current_Registered_User_Interface___FILE___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminWindow::process_Current_Registered_User_Interface___FILE);
    }


    /**
     * Returns the number of widgets discovered.
     */
    int process_Current_Registered_User_Interface___FILE();


    inline void GET_runtime_verification_report_PDF()
    {
    }

	inline bool GET__DBUS_CONNECTION_ERROR_TO_CLIENT()
	{
		return _DBUS_CONNECTION_ERROR_TO_CLIENT;
	}

	void reinitialiser_la_derniere_selection_du_logo_de_lentreprise();

    void supprimer_logo_de_lentreprise();

    inline void selectionner_logo_de_lentreprise()
    {
        YerithUtils::selectionner_image(this, *label_logo_de_lentreprise);
    }

    void YERITH_ERP_3_populate_all_tables();

    void EXECUTER_COMMANDE_MAINTENANCE();

    void reinitialiser_AFFICHAGE_COMMANDE_MAINTENANCE();


    void handleCheckboxActiver___Show_Yr_Db_Runtime_VERIFICATION_monitoring_Window_TAB(int state);


    void handle_changer_commande_MAINTENANCE_OPERATION_SUJET_for_database(const QString &commande_MAINTENANCE,
                                                                          const QString &sqlTableName);

    void handle_changer_commande_MAINTENANCE_OPERATION(const QString &
                                                       commande_MAINTENANCE);

    void handle_changer_commande_MAINTENANCE_SUJET(const QString &
                                                   sqlTableName);

    inline void handle_changer_tableau_dimportation(const QString &
                                                    sqlTableName)
    {
        generate_table_header_mapping_entries_for_csv_import();
    }

    void handle_importer_parlant_checkBox(int aState);

    void choix_registre_de_caisse(const QString &);

    void reset_import_current_selected_csv_file();

    void import_current_selected_csv_file();

    bool generate_table_header_mapping_entries_for_csv_import();


private:

    void Reinitialize_COMBOBOXES();

    void populateComboBoxes();

    void cacher_autres_commandes_YERITH_LINE_EDIT(YerithLineEdit *
                                                  aYerithCommandLineEdit);

    void changer_commande_YERITH_LINE_EDIT(YerithLineEdit &
                                           aYerithCommandLineEdit,
                                           const QString &sqlTableName);

    void clear_csv_import_panel_content_mapping();

    void creer(enum AdminSujetAction selectedSujetAction);

    void lister(enum AdminSujetAction selectedSujetAction);

    void modifier(enum AdminSujetAction selectedSujetAction);

    inline void maintenance_exporter(enum AdminSujetAction selectedSujetAction)
    {
    }

    inline void maintenance_importer(enum AdminSujetAction selectedSujetAction)
    {
    }

    inline void maintenance_effacer(enum AdminSujetAction selectedSujetAction)
    {
    }

    static const int MAX_IMPORT_CSV_HEADER_SIZE;

    static const QString DATABASE_YERITH_ERP_3_0_KEYWORD;

    static QString CREER;
    static QString LISTER;
    static QString MODIFIER;
    static QString SUPPRIMER;
    static QString EXPORTER;
    static QString IMPORTER;
    static QString EFFACER;

    static QString COMPTE_UTILISATEUR;
    static QString LOCALISATION;
    static QString DEPARTEMENTS_DE_PRODUITS;
    static QString CATEGORIE;
    static QString LIGNE_BUDGETAIRE;
    static QString FOURNISSEUR;
    static QString ALERTE;
    static QString COMPTE_BANCAIRE;
    static QString REMISE;
    static QString BON_DE_COMMANDE;
    static QString DB;
    static QString TABLEAU;


    static QStringList comboBox_impression_sur_CHOICE_list;

    static QStringList comboBox_format_de_facture_CHOICE_list;

    QString _currentWindowTitle;
    QString _yerithAdminWindowTitleStart;


    bool _DBUS_CONNECTION_ERROR_TO_CLIENT;

    bool _importer_parlant;


public:

    enum AdminAction _curAdminAction;

    enum AdminSujetAction _curAdminSujetAction;

    enum AdminAction _curAdminMaintainAction;

    enum AdminSujetAction _curAdminSujetsMaintainAction;


    QMap<int, QLabel *> _widgetIndex__TO__xmltagelement;


private:

    YerithLogger *_logger;

    QStringList _curCsvFileToImportContentWordList;

    QList <YerithERPDatabaseTableColumnInfo *> _allDatabaseTableColumnInfo;

    YERITH_WEB_SYSTEMS_MAIN_GENERATOR *_a_YERITH_WEB_SYSTEMS_MAIN_GENERATOR_Instance;

    QMap<QString, bool> _dbTableColumnToIsNotNULL;

    QMap<QString, QString> _dbTableColumnToType;

    QMap<int, YerithERPDatabaseTableColumnInfo *> _csvContentIdxToDatabaseTableColumnInfo;

    QMap<int, YerithComboBox *> _csvContentIdxToSQLTableImportHeader;

    QMap<int, QLabel *> _csvContentIdxToCsvFileContentImportHeader;

    QMap<QString, AdminAction> *_actionsToConst;

    QMap<QString, AdminSujetAction> *_sujetActionsToConst;

    QString _current_selected_import_table;

    QString _localisation_adresse_ip;
};


#endif /* SRC_ADMIN_YERITH_ADMIN_WINDOW_HPP_ */
