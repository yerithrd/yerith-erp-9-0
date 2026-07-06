/*
 * yerith-erp-creer-UN-GROUPE-DE-PAIE-hr-window.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-creer-GROUPE-DE-PAIE-hr-window.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/utils/yerith-erp-database-table-column.hpp"

#include "src/users/yerith-erp-users.hpp"

#include "src/utils/yerith-erp-config.hpp"

#include <QtSql/QSqlQuery>

#include <QtSql/QSqlIndex>

#include "src/utils/yerith-erp-database-table-column.hpp"

#include "src/utils/yerith-erp-historique-stock.hpp"



#include "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.hpp"



YerithCreerUnGroupeDePaieWindow::YerithCreerUnGroupeDePaieWindow()
:YerithWindowsCommons(),
 _logger(new YerithLogger("YerithCreerUnGroupeDePaieWindow"))
{
    _windowName = QString("%1 - %2")
    				.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                         QObject::tr("CRÉER 1 GROUPE DE PAIE"));

    _windowName_WITH_NO_MAINTENANCE = _windowName;

    setupUi(this);

    mySetupUi(this);

    QMESSAGE_BOX_STYLE_SHEET =
                    QString("QMessageBox {background-color: rgb(%1);}"
                            "QMessageBox QLabel {color: rgb(%2);}").arg
                    (COLOUR_RGB_STRING_YERITH_GREEN_2_160_70,
                     COLOUR_RGB_STRING_YERITH_WHITE_255_255_255);


//    _NOT_VISIBLE_FOR_USER_DB_TABLE_COLUMN_NAME
//              << ;


    setup_select_configure_dbcolumn(YerithDatabase::GROUPES_DE_PAIE_hr );

    doubleSpinBox_creer_un_GroupeDePaie_pourcentage_TAXES_IMPOSABLES->setMinimum(0.0);

    doubleSpinBox_creer_un_GroupeDePaie_pourcentage_TAXES_IMPOSABLES->setMaximum(100.0);


    setupLineEdits();

    populateComboBoxes();


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionInformationEntreprise, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionA_propos, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionChanger_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_principal, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionFournisseurs, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAppeler_aide, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregistrer, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionFermeture, false);


    pushButton_annuler->disable(this);
    pushButton_menu_principal->disable(this);
    pushButton_FOURNISSEURS->disable(this);
    pushButton_enregistrer->disable(this);


    connect(lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(HANDLE_lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL_visualisation(const QString &)));


    /** Menu actions */
    connect(actionChanger_utilisateur, SIGNAL(triggered()), this, SLOT(changer_utilisateur()));
    connect(actionAppeler_aide, SIGNAL(triggered()), this, SLOT(help()));
    connect(actionDeconnecter_utilisateur, SIGNAL(triggered()), this, SLOT(deconnecter_utilisateur()));
    connect(actionMenu_principal, SIGNAL(triggered()), this, SLOT(Main_MENU()));
    connect(actionFournisseurs, SIGNAL(triggered()), this, SLOT(fournisseurs()));
    connect(actionAnnuler, SIGNAL(triggered()), this, SLOT(annuler_la_creation_dun_GROUPE_DE_PAIE_hr()));
    connect(actionEnregistrer, SIGNAL(triggered()), this, SLOT(creerEnregistrerUnGroupeDePaieHr()));
    connect(actionFermeture, SIGNAL(triggered()), this, SLOT(fermeture()));
    connect(actionA_propos, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(actionInformationEntreprise, SIGNAL(triggered()), this, SLOT(infosEntreprise()));
    connect(actionQui_suis_je, SIGNAL(triggered()), this, SLOT(qui_suis_je()));
    connect(actionAdministration, SIGNAL(triggered()), this, SLOT(administration()));



#ifdef YERITH_CLIENT
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
#endif

    setupShortcuts();
}


void YerithCreerUnGroupeDePaieWindow::deconnecter_utilisateur()
{
    clear_all_fields();
    YerithWindowsCommons::deconnecter_utilisateur();
}


void YerithCreerUnGroupeDePaieWindow::updatePopulateComboBoxes()
{
    QStringList new_items;

    new_items.append(YerithUtils::EMPTY_STRING);

    comboBox_creer_un_GroupeDePaie_ligne_budgetaire
        ->populateComboBoxRawString(YerithDatabase::LIGNES_BUDGETAIRES,
                                    YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);

    comboBox_creer_un_GroupeDePaie_ligne_budgetaire
        ->addItem_AFTER_POPULATE(new_items);


    //##############################


    new_items.clear();

    new_items.append(YerithUtils::EMPTY_STRING);

    new_items.append(YerithERPConfig::THIS_SITE_LOCALISATION_NAME);


    comboBox_creer_un_GroupeDePaie_localisation
        ->populateComboBoxRawString(YerithDatabase::LOCALISATIONS,
                                    YerithDatabaseTableColumn::NOM_LOCALISATION);

    comboBox_creer_un_GroupeDePaie_localisation
        ->addItem_AFTER_POPULATE(new_items);

}


void YerithCreerUnGroupeDePaieWindow::populateComboBoxes()
{
    comboBox_creer_un_GroupeDePaie_localisation
        ->populateComboBoxRawString(YerithDatabase::LOCALISATIONS,
                                    YerithDatabaseTableColumn::NOM_LOCALISATION);

    comboBox_creer_un_GroupeDePaie_ligne_budgetaire
        ->populateComboBoxRawString(YerithDatabase::LIGNES_BUDGETAIRES,
                                    YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);
}


void YerithCreerUnGroupeDePaieWindow::setupLineEdits()
{
    lineEdit_creer_un_GroupeDePaie_jour_de_paie_du_mois
        ->setValidator(&YerithUtils::jour_de_paie_du_mois_Validator);

    lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL_visualisation
        ->setYerithEnabled(false);

    lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL
        ->setValidator(&YerithUtils::POSITIVE_DoubleValidator);
}


void YerithCreerUnGroupeDePaieWindow::reset_window_widgets_modification_Bit()
{
    lineEdit_creer_un_GroupeDePaie_reference
        ->Set_widget_modified(false);

    lineEdit_creer_un_GroupeDePaie_designation
        ->Set_widget_modified(false);

    lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL_visualisation
        ->Set_widget_modified(false);

    lineEdit_creer_un_GroupeDePaie_jour_de_paie_du_mois
        ->Set_widget_modified(false);

    lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL
        ->Set_widget_modified(false);


    comboBox_creer_un_GroupeDePaie_localisation
        ->Set_widget_modified(false);

    doubleSpinBox_creer_un_GroupeDePaie_pourcentage_TAXES_IMPOSABLES
        ->Set_widget_modified(false);

    comboBox_creer_un_GroupeDePaie_ligne_budgetaire
        ->Set_widget_modified(false);

    textEdit_creer_un_GroupeDePaie_description
        ->Set_widget_modified(false);


    set_yerith_WindowModified(false);

    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithCreerUnGroupeDePaieWindow::setupShortcuts()
{
    setupShortcutActionMessageDaide(*actionAppeler_aide);
    setupShortcutActionQuiSuisJe(*actionQui_suis_je);
}


void YerithCreerUnGroupeDePaieWindow::definirPasDeRole()
{
    _logger->log("definirPasDeRole");

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionInformationEntreprise, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionA_propos, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionChanger_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                           false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_principal, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionFournisseurs, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAppeler_aide, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregistrer, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionFermeture, false);

    pushButton_annuler->disable(this);
    pushButton_menu_principal->disable(this);
    pushButton_FOURNISSEURS->disable(this);
    pushButton_enregistrer->disable(this);

}


void YerithCreerUnGroupeDePaieWindow::definirManager()
{
    _logger->log("definirManager");

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionInformationEntreprise, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionA_propos, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionChanger_utilisateur, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                           true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_principal, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionFournisseurs, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAppeler_aide, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregistrer, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionFermeture, true);


    pushButton_annuler->enable(this,
                               SLOT
                               (annuler_la_creation_dun_GROUPE_DE_PAIE_hr
                                ()));
    pushButton_menu_principal->enable(this, SLOT(Main_MENU()));
    pushButton_FOURNISSEURS->enable(this, SLOT(fournisseurs()));
    pushButton_enregistrer->enable(this,
                                   SLOT
                                   (creerEnregistrerUnGroupeDePaieHr
                                    ()));
}


bool YerithCreerUnGroupeDePaieWindow::payGroupAlreadyExists()
{
    bool result = false;

    YerithSqlTableModel &GROUPE_DE_PAIE_HR_TableModel =
                    _allWindows->getSqlTableModel_groupes_de_paie_hr();

    // ** check if customer account with same name exist
    result = YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*this,
                                                         GROUPE_DE_PAIE_HR_TableModel,
                                                         *lineEdit_creer_un_GroupeDePaie_designation,
                                                         QObject::tr("GROUPE DE PAIE hr"),
                                                         YerithDatabaseTableColumn::DESIGNATION);

    return result;
}


bool YerithCreerUnGroupeDePaieWindow::check_fields()
{
    bool result = false;


    bool GroupeDePaie_description_for_payment_memo_notes =
                textEdit_creer_un_GroupeDePaie_description->checkField();

    bool GroupeDePaie_designation =
                        lineEdit_creer_un_GroupeDePaie_designation->checkField();

    bool GroupeDePaie_Ligne_BUDGETAIRE_de_paiement =
                        comboBox_creer_un_GroupeDePaie_ligne_budgetaire->checkField();

    bool GroupeDePaie_JourDePaieVALIDE =
            lineEdit_creer_un_GroupeDePaie_jour_de_paie_du_mois->checkField();

    bool GroupeDePaie_MONTANT_A_PAYER =
    		lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL->checkField();

    result = GroupeDePaie_JourDePaieVALIDE                      &&
             GroupeDePaie_description_for_payment_memo_notes    &&
             GroupeDePaie_designation                           &&
    		 GroupeDePaie_Ligne_BUDGETAIRE_de_paiement          &&
    		 GroupeDePaie_MONTANT_A_PAYER;

    return result;
}


void YerithCreerUnGroupeDePaieWindow::clear_all_fields()
{
    lineEdit_creer_un_GroupeDePaie_reference->clear();

    lineEdit_creer_un_GroupeDePaie_designation->clearField();

    lineEdit_creer_un_GroupeDePaie_jour_de_paie_du_mois->clearField();

    lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL->clearField();

    textEdit_creer_un_GroupeDePaie_description->clear();

    doubleSpinBox_creer_un_GroupeDePaie_pourcentage_TAXES_IMPOSABLES->setValue(0.0);

    comboBox_creer_un_GroupeDePaie_ligne_budgetaire->resetYerithComboBox();

    comboBox_creer_un_GroupeDePaie_localisation->resetYerithComboBox();


    reset_window_widgets_modification_Bit();
}


void YerithCreerUnGroupeDePaieWindow::rendreInvisible()
{
    if (GET___Succeeded___INSERTION_to_DB_Tables_Bit())
    {
        clear_all_fields();

        setVisible(false);
    }
    else
    {
        _Cancel_MODIFICATION_request_Object
            ->set_First__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("VOUS étiez entrain de créer 1 groupe de PAIE.\n"
                             "Souhaiter vous annuler\n"
                             "ceci en sortant de cette fenêtre du programme ?"));


        _Cancel_MODIFICATION_request_Object
            ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("Vous avez annulé(e) 1 création d'1 groupe de PAIE !"));


        _Cancel_MODIFICATION_request_Object
            ->Set_Window__MODIFICATION_CANCELLATION_TITLE
                (QObject::tr("ANNULER 1 création d'1 groupe de PAIE !"));


        if (Is___YERITH_Cancellation_Request_Modification_Needed_NOW())
        {
            _Cancel_MODIFICATION_request_Object
                ->yri_Cancel__ALL__modifications_On_This_Window_Frame_PAGE();

            MACRO___CHECK__goto_Exit_anyway_this_window_Frame(_Cancel_MODIFICATION_request_Object)
        }
        else
        {
            MACRO___GOTO_LABEL___EXIT_ANYWAY_window_frame()

            _Cancel_MODIFICATION_request_Object
                ->Set_Currently_performing_modifications(false);

            clear_all_fields();

            setVisible(false);
        }
    }
}


void YerithCreerUnGroupeDePaieWindow::rendreVisible(YerithSqlTableModel *stocksTableModel)
{
    HANDLE_rendering_IF_ALLOWED_PREVIOUSLY_With___Direct_modification_entry();

	retranslateUi(this);

    _curStocksTableModel = stocksTableModel;

    updatePopulateComboBoxes();

    check_fields();

    lineEdit_creer_un_GroupeDePaie_designation->setFocus();

    setVisible(true);

    YERITH_set_windowName_TRANSLATED(YerithMainWindow::get_TRANSLATED_WindowName("CRÉER 1 GROUPE DE PAIE"),
    								 _curStocksTableModel);


    static bool first_Execution_time = true;

    if (first_Execution_time)
    {
        YerithQMessageBox::information(this,
                                       QObject::tr("LIGNE BUDGETAIRE"),
                                       QObject::tr("Créer 1 groupe DE PAYE nécessite "
                                                   "déjà avoir créée LIGNE BUDGETAIRE "
                                                   "à la section Administration !"));

        first_Execution_time = false;
    }


    RESET_Bits_Showing_Cancellation_Modification_REQUEST_Needed();
}


void YerithCreerUnGroupeDePaieWindow::annuler_la_creation_dun_GROUPE_DE_PAIE_hr()
{
    if (GET___Succeeded___INSERTION_to_DB_Tables_Bit())
    {
        clear_all_fields();

        setVisible(false);
    }
    else
    {
        _Cancel_MODIFICATION_request_Object
            ->set_First__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("VOUS étiez entrain de créer 1 groupe de PAIE.\n"
                             "Souhaiter vous annuler\n"
                             "ceci en sortant de cette fenêtre du programme ?"));


        _Cancel_MODIFICATION_request_Object
            ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("Vous avez annulé(e) 1 création d'1 groupe de PAIE !"));


        _Cancel_MODIFICATION_request_Object
            ->Set_Window__MODIFICATION_CANCELLATION_TITLE
                (QObject::tr("ANNULER 1 création d'1 groupe de PAIE !"));


        if (Is___YERITH_Cancellation_Request_Modification_Needed_NOW())
        {
            _Cancel_MODIFICATION_request_Object
                ->yri_Cancel__ALL__modifications_On_This_Window_Frame_PAGE();

            MACRO___CHECK__goto_Exit_anyway_this_window_Frame(_Cancel_MODIFICATION_request_Object)
        }
        else
        {
            MACRO___GOTO_LABEL___EXIT_ANYWAY_window_frame()

            _Cancel_MODIFICATION_request_Object
                ->Set_Currently_performing_modifications(false);

            clear_all_fields();


            GROUPES_DE_PAIE_hr(true);
        }
    }
}


bool YerithCreerUnGroupeDePaieWindow::creerEnregistrerUnGroupeDePaieHr()
{
    if (!check_fields())
    {
        if (QMessageBox::Ok ==
                YerithQMessageBox::warning(this,
                						   "",
                                           QObject::tr("Remplisser tous les champs obligatoires !")))
        {
        }
        else
        {
        }

        return false;
    }

    if (payGroupAlreadyExists())
    {
        return false;
    }

    QString retMsg(QObject::tr("LE GROUPE DE PAIE '"));

    YerithSqlTableModel &groupe_de_paie_HR_ProgramTableModel =
                    _allWindows->getSqlTableModel_groupes_de_paie_hr();


    QSqlRecord record = groupe_de_paie_HR_ProgramTableModel.record();


    QString new_pay_group_designation = lineEdit_creer_un_GroupeDePaie_designation->text();

    int NOUVEAU_GROUPE_PAIE_HR_db_ID =
    		YerithERPWindows::getNextIdSqlTableModel_groupes_de_paie_hr();

    record.setValue(YerithDatabaseTableColumn::ID, NOUVEAU_GROUPE_PAIE_HR_db_ID);

    record.setValue(YerithDatabaseTableColumn::DATE_CREATION,
                    DATE_TO_DB_FORMAT_STRING(GET_CURRENT_DATE));

    record.setValue(YerithDatabaseTableColumn::REFERENCE_GROUPE_DE_PAIE_hr,
    				lineEdit_creer_un_GroupeDePaie_reference->text());

    record.setValue(YerithDatabaseTableColumn::DESIGNATION,
                    new_pay_group_designation);

    if (!comboBox_creer_un_GroupeDePaie_ligne_budgetaire->isEmpty())
    {
        record.setValue(YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire,
                        comboBox_creer_un_GroupeDePaie_ligne_budgetaire->currentText());
    }

    if (!comboBox_creer_un_GroupeDePaie_localisation->isEmpty())
    {
        record.setValue(YerithDatabaseTableColumn::LOCALISATION,
                        comboBox_creer_un_GroupeDePaie_localisation->currentText());
    }


    record.setValue(YerithDatabaseTableColumn::DESCRIPTION_GROUPE_DE_PAIE_HR,
    				textEdit_creer_un_GroupeDePaie_description->toPlainText());

    record.setValue(YerithDatabaseTableColumn::JOUR_DE_PAIE_DU_MOIS,
                    lineEdit_creer_un_GroupeDePaie_jour_de_paie_du_mois->text().toDouble());

    record.setValue(YerithDatabaseTableColumn::MONTANT_A_PAYER_MENSUEL,
    				lineEdit_creer_un_GroupeDePaie_MONTANT_A_PAYER_MENSUEL->text().toDouble());

    record.setValue(YerithDatabaseTableColumn::POURCENTAGE_TAXES_IMPOSABLES,
                    doubleSpinBox_creer_un_GroupeDePaie_pourcentage_TAXES_IMPOSABLES->value());


    retMsg.append(lineEdit_creer_un_GroupeDePaie_designation->text());

    bool success = groupe_de_paie_HR_ProgramTableModel
    					.insertNewRecord(record,
    									 this,
										 "src/windows/supplier/yerith-erp-creer-UN-GROUPE-DE-PAIE-hr-window.cpp",
										 446,
										 new_pay_group_designation);

    if (!success)
    {
        retMsg.append(QObject::tr("' n'a pas pu être créer !"));

        YerithQMessageBox::warning(this,
                                   QObject::tr("CRÉER 1 GROUPE DE PAIE (hr)"),
                                   retMsg);
        return false;
    }


    Set_Succeeded_INSERTION_to_DB_Tables_Bit(true);


    STOP_Performing_MODIFICATIONS_handler();


    groupe_de_paie_HR_ProgramTableModel.select();

    retMsg.append(QObject::tr("' a été créer avec succès !"));

    YerithQMessageBox::information(this,
                                   QObject::tr
                                   ("CRÉER 1 GROUPE DE PAIE (hr)"),
                                   retMsg);

    clear_all_fields();

    GROUPES_DE_PAIE_hr();

    return true;
}
