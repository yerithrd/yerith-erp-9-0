/*
 * yerith-erp-DETAILS-DUN-GROUPE-DE-PAIE-hr-window.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-DETAILS-DUN-GROUPE-DE-PAIE-hr-window.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/process/yerith-erp-process.hpp"

#include "src/users/yerith-erp-users.hpp"

#include "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.hpp"

#include "src/utils/yerith-erp-sqltable-model.hpp"

#include "src/widgets/yerith-erp-qcheckbox.hpp"


#include <QtSql/QSqlRecord>


YerithDetailsDunGroupeDePaieWindow::YerithDetailsDunGroupeDePaieWindow()
:YerithWindowsCommons(),
 _logger(new YerithLogger("YerithDetailsDunGroupeDePaieWindow"))
{
    _windowName = QString("%1 - %2")
    				.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                         QObject::tr("DÉTAILS D'UN GROUPE DE PAIE"));

    _windowName_WITH_NO_MAINTENANCE = _windowName;

    setupUi(this);

    mySetupUi(this);

    QMESSAGE_BOX_STYLE_SHEET =
    		QString("QMessageBox {background-color: rgb(%1);}"
                    "QMessageBox QLabel {color: rgb(%2);}")
				.arg(COLOUR_RGB_STRING_YERITH_YELLOW_254_254_0,
                     COLOUR_RGB_STRING_YERITH_BLACK_0_0_0);



    setup_Date_JOUR_de_Paye___GROUPBOX();


    doubleSpinBox_details_DUN_GROUPE_DE_PAIE_pourcentage_du_rabais->setMaximum(100.0);

    doubleSpinBox_details_DUN_GROUPE_DE_PAIE_pourcentage_du_rabais->setYerithEnabled(false);


    setupLineEdits();


    textEdit_details_DUN_GROUPE_DE_PAIE_description->setYerithEnabled(false);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionModifierLeJourDEPAYE, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnulerLENREGISTREMENTDuJourDEPAYE, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregistrerLeJourDEPAYE, false);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionChanger_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionRETOUR, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionGroupesDemployes, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenuFOURNISSEURS, false);


    pushButton_annuler_lenregistrement_du_jour_de_paye->disable(this);
    pushButton_modifier_le_jour_de_paye->disable(this);
    pushButton_enregistrer->disable(this);
    pushButton_menu_fournisseurs->disable(this);
    pushButton_RETOUR->disable(this);


    /** Menu actions */
    connect(actionModifierLeJourDEPAYE,
            SIGNAL(triggered()),
            this,
            SLOT(Modify_Date_JOUR_de_Paye()));


    connect(actionAnnulerLENREGISTREMENTDuJourDEPAYE,
            SIGNAL(triggered()),
            this,
            SLOT(Cancel__enregistrer___DATE_DE_PAYE()));


    connect(actionEnregistrerLeJourDEPAYE,
            SIGNAL(triggered()),
            this,
            SLOT(Enregistrer__DATE_DE_PAYE()));



    connect(actionChanger_utilisateur, SIGNAL(triggered()), this, SLOT(changer_utilisateur()));
    connect(actionAppeler_aide, SIGNAL(triggered()), this, SLOT(help()));
    connect(actionDeconnecter_utilisateur, SIGNAL(triggered()), this, SLOT(deconnecter_utilisateur()));
    connect(actionGroupesDemployes, SIGNAL(triggered()), this, SLOT(GROUPES_DE_PAIE_hr()));
    connect(actionMenuFOURNISSEURS, SIGNAL(triggered()), this, SLOT(fournisseurs()));
    connect(actionRETOUR, SIGNAL(triggered()), this, SLOT(GROUPES_DE_PAIE_hr()));
    connect(actionFermeture, SIGNAL(triggered()), this, SLOT(fermeture()));
    connect(actionA_propos, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(actionInformationEntreprise, SIGNAL(triggered()), this, SLOT(infosEntreprise()));
    connect(actionQui_suis_je, SIGNAL(triggered()), this, SLOT(qui_suis_je()));


#ifdef YERITH_CLIENT

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);

#else //YERITH_SERVER, YERITH_STANDALONE, YERITH_ACADEMIC_EVALUSATION_VERSION

    connect(actionAdministration, SIGNAL(triggered()), this, SLOT(administration()));

#endif


    setup_Date_JOUR_de_Paye___GROUPBOX();


    setupShortcuts();
}


YerithDetailsDunGroupeDePaieWindow::~YerithDetailsDunGroupeDePaieWindow()
{
    delete _logger;
}


bool YerithDetailsDunGroupeDePaieWindow::Modify_Date_JOUR_de_Paye(bool AskConfirmation /* = true */)
{
    if (AskConfirmation)
    {
        QString retMsg;

        retMsg = QObject::tr("Souhaitez Vous continuer avec la "
                             "modification de la date de payement "
                             "des salaires du groupe de paye : \"%1\" ?")
                    .arg(_Nom_du_groupe_de_PAYE);

        if (QMessageBox::Ok ==
                YerithQMessageBox::question(this,
                                            QObject::tr("CONTINUER avec 1 modification de la date de PAYE"),
                                            retMsg,
                                            QMessageBox::Cancel,
                                            QMessageBox::Ok))
        {
            _Cancel_MODIFICATION_request_Object
                ->Set_Currently_performing_modifications(true);
        }
        else
        {
            YerithQMessageBox::information(this,
                                           QObject::tr("ANNULER avec 1 modification de la date de PAYE"),
                                           QObject::tr("Vous avez annulé la modification de la date de PAYE !"),
                                           QMessageBox::Ok);

            _Cancel_MODIFICATION_request_Object
                ->Set_Currently_performing_modifications(false);

            return false;
        }
    }


    if (_Cancel_MODIFICATION_request_Object->Is_Currently_performing_modifications())
    {
        lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
            ->setEnabled(true);
    }
    else
    {
        lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
            ->setEnabled(false);
    }


    return _Cancel_MODIFICATION_request_Object
                ->Is_Currently_performing_modifications();
}


void YerithDetailsDunGroupeDePaieWindow::Cancel__enregistrer___DATE_DE_PAYE()
{
    _Cancel_MODIFICATION_request_Object
        ->set_First__MODIFICATION_CANCELLATION_MESSAGE
        (QObject::tr("VOUS étiez entrain de modifier 1 groupe de paye.\n"
                     "Souhaiter vous annuler\n"
                     "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
        ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
        (QObject::tr("Vous avez annulé(e) 1 modification d'1 groupe de paye !"));

    _Cancel_MODIFICATION_request_Object
        ->Set_Window__MODIFICATION_CANCELLATION_TITLE
        (QObject::tr("ANNULER 1 modification d'1 groupe de paye !"));


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


        lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
            ->setEnabled(false);


        clear_all_fields();

        YerithWindowsCommons::rendreInvisible();
    }
}


void YerithDetailsDunGroupeDePaieWindow::Enregistrer__DATE_DE_PAYE()
{
    QString retMsg;

    retMsg = QObject::tr("Souhaitez Vous continuer avec "
                         "L'ENREGISTREMENT de la date de payement "
                         "des salaires du groupe de paye : \"%1\" ?")
                .arg(_Nom_du_groupe_de_PAYE);


    if (QMessageBox::Ok ==
            YerithQMessageBox::question(this,
                                        QObject::tr("CONTINUER avec L'ENREGISTREMENT de la date de PAYE"),
                                        retMsg,
                                        QMessageBox::Cancel,
                                        QMessageBox::Ok))
    {
    }
    else
    {
        Cancel__enregistrer___DATE_DE_PAYE();

        return ;
    }


    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;

    if (! _Cancel_MODIFICATION_request_Object->Is_Currently_performing_modifications())
    {
        YerithQMessageBox::information(this,
                                       QObject::tr("ANNULER L'ENREGISTREMENT de la date de PAYE"),
                                       QObject::tr("Vous avez annulé L'ENREGISTREMENT de la date de PAYE !"),
                                       QMessageBox::Ok);

        return ;
    }


    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
        ->setEnabled(false);


    QSqlRecord record;

    _allWindows->_GROUPES_DE_PAIE_Window->SQL_QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW(record);

    QString PayGroup_designation = GET_SQL_RECORD_DATA(record,
                                                       YerithDatabaseTableColumn::DESIGNATION);

    QString jour_LINEEDIT_de_paye = lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye->text();

    record.setValue(YerithDatabaseTableColumn::DATE_JOUR_DE_PAYE,
                    jour_LINEEDIT_de_paye);


    bool success =_allWindows->_GROUPES_DE_PAIE_Window
                        ->SQL_UPDATE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW(record);

    if (success)
    {
        Set_Succeeded_INSERTION_to_DB_Tables_Bit(true);


        lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
            ->setText(jour_LINEEDIT_de_paye);
    }

    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;
}


void YerithDetailsDunGroupeDePaieWindow::clear_all_fields()
{
    textEdit_details_DUN_GROUPE_DE_PAIE_description->clearField();

    comboBox_DETAILS_UN_GROUPE_DE_PAIE_localisation->clearField();

    tableWidget_details_dun_groupe_de_paie_groupes_demployes_participants->yerithClearTableWidgetContent();

    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye->clearField();
    lineEdit_details_DUN_GROUPE_DE_PAIE_reference->clearField();
    lineEdit_details_DUN_GROUPE_DE_PAIE_designation->clearField();
    lineEdit_details_dun_GroupeDePaie_MONTANT_A_PAYER->clearField();
    lineEdit_details_DUN_GROUPE_DE_PAIE_ligne_budgetaire->clearField();


    reset_window_widgets_modification_Bit();
}


void YerithDetailsDunGroupeDePaieWindow::setup_Date_JOUR_de_Paye___GROUPBOX()
{
    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
        ->setText(QString::number(31));


    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye->setYerithEnabled(false);
}


void YerithDetailsDunGroupeDePaieWindow::setupLineEdits()
{
    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye->setYerithEnabled(false);
    lineEdit_details_DUN_GROUPE_DE_PAIE_reference->setYerithEnabled(false);
    lineEdit_details_DUN_GROUPE_DE_PAIE_designation->setYerithEnabled(false);
    lineEdit_details_DUN_GROUPE_DE_PAIE_ligne_budgetaire->setYerithEnabled(false);
    lineEdit_details_dun_GroupeDePaie_MONTANT_A_PAYER->setYerithEnabled(false);
}


void YerithDetailsDunGroupeDePaieWindow::definirPasDeRole()
{
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionModifierLeJourDEPAYE, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnulerLENREGISTREMENTDuJourDEPAYE, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregistrerLeJourDEPAYE, false);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionChanger_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionRETOUR, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionGroupesDemployes, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenuFOURNISSEURS, false);


    pushButton_annuler_lenregistrement_du_jour_de_paye->disable(this);
    pushButton_modifier_le_jour_de_paye->disable(this);
    pushButton_enregistrer->disable(this);
    pushButton_menu_fournisseurs->disable(this);
    pushButton_RETOUR->disable(this);
}


void YerithDetailsDunGroupeDePaieWindow::definirManager()
{
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionModifierLeJourDEPAYE, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnulerLENREGISTREMENTDuJourDEPAYE, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregistrerLeJourDEPAYE, true);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionChanger_utilisateur, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionRETOUR, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionGroupesDemployes, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenuFOURNISSEURS, true);


    pushButton_annuler_lenregistrement_du_jour_de_paye->enable(this, SLOT(Cancel__enregistrer___DATE_DE_PAYE()));
    pushButton_modifier_le_jour_de_paye->enable(this, SLOT(Modify_Date_JOUR_de_Paye()));
    pushButton_enregistrer->enable(this, SLOT(Enregistrer__DATE_DE_PAYE()));
    pushButton_menu_fournisseurs->enable(this, SLOT(fournisseurs()));
    pushButton_RETOUR->enable(this, SLOT(GROUPES_DE_PAIE_hr()));
}


void YerithDetailsDunGroupeDePaieWindow::rendreInvisible()
{
    if (GET___Succeeded___INSERTION_to_DB_Tables_Bit())
    {
        clear_all_fields();

        _Nom_du_groupe_de_PAYE.clear();

        comboBox_DETAILS_UN_GROUPE_DE_PAIE_localisation->clear();

        setup_Date_JOUR_de_Paye___GROUPBOX();

        YerithWindowsCommons::rendreInvisible();
    }
    else
    {
        _Cancel_MODIFICATION_request_Object
        ->set_First__MODIFICATION_CANCELLATION_MESSAGE
        (QObject::tr("VOUS étiez entrain de modifier la "
                     "date de payement. Souhaiter vous annuler "
                     "ceci en sortant de cette fenêtre du programme ?"));

        _Cancel_MODIFICATION_request_Object
        ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
        (QObject::tr("Vous avez annulé la modification de la date de PAYE !"));

        _Cancel_MODIFICATION_request_Object
        ->Set_Window__MODIFICATION_CANCELLATION_TITLE
        (QObject::tr("ANNULER avec 1 modification de la date de PAYE"));


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



            _Nom_du_groupe_de_PAYE.clear();

            comboBox_DETAILS_UN_GROUPE_DE_PAIE_localisation->clear();

            setup_Date_JOUR_de_Paye___GROUPBOX();


            clear_all_fields();


            YerithWindowsCommons::rendreInvisible();
        }
    }
}


void YerithDetailsDunGroupeDePaieWindow::
		rendreVisible(YerithSqlTableModel *curClient_LOYALTY_PROGRAM_TableModel,
				      YerithSqlTableModel *stocksTableModel)
{

	HANDLE_rendering_IF_ALLOWED_PREVIOUSLY_With___Direct_modification_entry();


	retranslateUi(this);


    _curStocksTableModel = stocksTableModel;

    _curPAY_GROUP_TableModel = curClient_LOYALTY_PROGRAM_TableModel;

    //qDebug() << "++ last selected row: " << YerithERPWindows::get_last_lister_selected_row_db_ID();

    setup_Date_JOUR_de_Paye___GROUPBOX();

    showPayGroup_PROGRAM_DETAIL();

    YERITH_set_windowName_TRANSLATED(YerithMainWindow::get_TRANSLATED_WindowName("DÉTAILS D'UN GROUPE DE PAIE"),
    								 _curPAY_GROUP_TableModel);

    RESET_Bits_Showing_Cancellation_Modification_REQUEST_Needed();

    setVisible(true);
}


void YerithDetailsDunGroupeDePaieWindow::showPayGroup_PROGRAM_DETAIL()
{
    QSqlRecord record;


    QString DATE_JOUR_de_PAYE_string;

    QString designation_GROUPE_DE_PAIE;

    QString ligne_budgetaire_GROUPE_DE_PAIE;

    QString montant_a_payer;

    double pourcentage_tax_imposable;


    _allWindows->_GROUPES_DE_PAIE_Window
					->SQL_QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW(record);


    lineEdit_details_DUN_GROUPE_DE_PAIE_reference
		->setText(GET_SQL_RECORD_DATA(record,
									  YerithDatabaseTableColumn::REFERENCE_GROUPE_DE_PAIE_hr));

    DATE_JOUR_de_PAYE_string =
        GET_SQL_RECORD_DATA(record,
                            YerithDatabaseTableColumn::JOUR_DE_PAIE_DU_MOIS);


    designation_GROUPE_DE_PAIE =
        GET_SQL_RECORD_DATA(record,
                            YerithDatabaseTableColumn::DESIGNATION);


    _Nom_du_groupe_de_PAYE = designation_GROUPE_DE_PAIE;


    ligne_budgetaire_GROUPE_DE_PAIE  =
        GET_SQL_RECORD_DATA(record,
                            YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);


    montant_a_payer =
        GET_SQL_RECORD_DATA(record,
                            YerithDatabaseTableColumn::MONTANT_A_PAYER_MENSUEL);


    pourcentage_tax_imposable =
        GET_SQL_RECORD_DATA(record,
                            YerithDatabaseTableColumn::POURCENTAGE_TAXES_IMPOSABLES).toDouble();

    QDEBUG_STRING_OUTPUT_2_N("pourcentage_tax_imposable",
                              pourcentage_tax_imposable);

    doubleSpinBox_details_DUN_GROUPE_DE_PAIE_pourcentage_du_rabais
		->setValue(pourcentage_tax_imposable);


    lineEdit_details_DUN_GROUPE_DE_PAIE_designation
		->setText(designation_GROUPE_DE_PAIE);

    lineEdit_details_DUN_GROUPE_DE_PAIE_ligne_budgetaire
        ->setText(ligne_budgetaire_GROUPE_DE_PAIE);

    lineEdit_details_dun_GroupeDePaie_MONTANT_A_PAYER
		->setText(GET_CURRENCY_STRING_NUM(montant_a_payer.toDouble()));


    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye
        ->setText(DATE_JOUR_de_PAYE_string);


    QDEBUG_STRING_OUTPUT_2("DATE_JOUR_de_PAYE_string",
                            DATE_JOUR_de_PAYE_string);


    comboBox_DETAILS_UN_GROUPE_DE_PAIE_localisation
		->addItem(GET_SQL_RECORD_DATA(record, YerithDatabaseTableColumn::LOCALISATION));


    doubleSpinBox_details_DUN_GROUPE_DE_PAIE_pourcentage_du_rabais
		->setValue(GET_SQL_RECORD_DATA(record,
									   YerithDatabaseTableColumn::POURCENTAGE_TAXES_IMPOSABLES).toDouble());


    textEdit_details_DUN_GROUPE_DE_PAIE_description
		->setText(GET_SQL_RECORD_DATA(record,
									  YerithDatabaseTableColumn::DESCRIPTION_GROUPE_DE_PAIE_HR));

    tableWidget_details_dun_groupe_de_paie_groupes_demployes_participants
		->yerithClearTableWidgetContent();


    QString SELECT_ALL_employee_GROUP_PARTICIPATING
				(QString("select %1, %2, %3, %4 from %5 where %6='%7'")
					.arg(YerithDatabaseTableColumn::ID,
                         YerithDatabaseTableColumn::DESIGNATION,
                         YerithDatabaseTableColumn::REFERENCE_GROUPE_DEMPLOYES_hr,
                         YerithDatabaseTableColumn::MEMBRES_DU_GROUPE_db_ID,
                         YerithDatabase::GROUPES_DEMPLOYES_hr,
                         YerithDatabaseTableColumn::GROUPE_DE_PAIE_HR,
                         designation_GROUPE_DE_PAIE));


    QSqlQuery aQSqlQuery;

    int query_size = YerithUtils::execQuery(aQSqlQuery,
                                        	SELECT_ALL_employee_GROUP_PARTICIPATING);

    if (query_size <= 0)
    {
        return;
    }

    QString EMPLOYEE_group_db_ID;
    QString designation;
    QString reference_GROUPE_DEMPLOYES;
    QStringList EMPLOYEE_group_member_db_ID;

    while (aQSqlQuery.next())
    {
        EMPLOYEE_group_db_ID = aQSqlQuery.value(YerithDatabaseTableColumn::ID).toString();

        designation = aQSqlQuery.value(YerithDatabaseTableColumn::DESIGNATION).toString();

        reference_GROUPE_DEMPLOYES =
        		aQSqlQuery.value(YerithDatabaseTableColumn::REFERENCE_GROUPE_DEMPLOYES_hr).toString();

        EMPLOYEE_group_member_db_ID.clear();

        YerithUtils::SPLIT_STAR_SEPARATED_DB_STRING
						(EMPLOYEE_group_member_db_ID,
                         aQSqlQuery.value(YerithDatabaseTableColumn::MEMBRES_DU_GROUPE_db_ID).toString());

        tableWidget_details_dun_groupe_de_paie_groupes_demployes_participants
			->insert_group(EMPLOYEE_group_db_ID,
						   designation,
						   reference_GROUPE_DEMPLOYES,
						   QString::number(EMPLOYEE_group_member_db_ID.size()));
    }
}


void YerithDetailsDunGroupeDePaieWindow::reset_window_widgets_modification_Bit()
{
    textEdit_details_DUN_GROUPE_DE_PAIE_description->Set_widget_modified(false);

    comboBox_DETAILS_UN_GROUPE_DE_PAIE_localisation->Set_widget_modified(false);

    //tableWidget_details_dun_groupe_de_paie_groupes_demployes_participants->Set_widget_modified(false);

    lineEdit_details_DUN_GROUPE_DE_PAIE_date_de_paye->Set_widget_modified(false);
    lineEdit_details_DUN_GROUPE_DE_PAIE_reference->Set_widget_modified(false);
    lineEdit_details_DUN_GROUPE_DE_PAIE_designation->Set_widget_modified(false);
    lineEdit_details_dun_GroupeDePaie_MONTANT_A_PAYER->Set_widget_modified(false);
    lineEdit_details_DUN_GROUPE_DE_PAIE_ligne_budgetaire->Set_widget_modified(false);


    set_yerith_WindowModified(false);

    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithDetailsDunGroupeDePaieWindow::setupShortcuts()
{
    setupShortcutActionMessageDaide(*actionAppeler_aide);
    setupShortcutActionQuiSuisJe(*actionQui_suis_je);
}
