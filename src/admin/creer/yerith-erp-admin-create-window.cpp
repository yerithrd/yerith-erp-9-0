/*
 * yerith-erp-admin-create-window.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-admin-create-window.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/widgets/yerith-erp-push-button-PASSWORD.hpp"

#include "src/utils/yerith-erp-payment-processing-information.hpp"


#include "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.hpp"


#include <QtCore/QDebug>

#include <QtCore/QRegExp>


#include <QtGui/QRegExpValidator>


#include <QtWidgets/QDesktopWidget>


#include <QtSql/QSqlError>

#include <QtSql/QSqlRecord>

#include <QtSql/QSqlQuery>






QMap<QString, QLabel *> YerithAdminCreateWindow::_ComboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_Idx___To___labels_PLUS_Minus_signs;


QString YerithAdminCreateWindow::_Label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_entrees_dargents =
        QObject::tr("2.) montant de la LIGNE BUDGÉTAIRE - entrées d'argents");


QString YerithAdminCreateWindow::_Label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_sorties_dargents =
        QObject::tr("1.) montant de la LIGNE BUDGÉTAIRE - SORTIES d'argents");





YerithAdminCreateWindow::YerithAdminCreateWindow()
:YerithPOSAdminWindowsCommons(QObject::tr("administration ~ créer")),
 _logger(new YerithLogger("YerithAdminCreateWindow"))
{
    setupUi(this);

    mySetupUi(this);


    QMESSAGE_BOX_STYLE_SHEET =
                    QString("QMessageBox {background-color: rgb(%1);}"
                            "QMessageBox QLabel {color: rgb(%2);}")
						.arg(COLOUR_RGB_STRING_YERITH_DARK_GREEN_47_67_67,
							 COLOUR_RGB_STRING_YERITH_WHITE_255_255_255);

    setupLineEdits();

    setupDateTimeEdits();


    password_push_button_Line_Edit_initializations();


    checkBox_creer_NOM_DEPARTEMENT_AUTRE_stocks_objets_PHYSIQUES->setYerithEnabled(true);



    _ComboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_Idx___To___labels_PLUS_Minus_signs
        .insert(YerithAdminCreateWindow::_Label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_entrees_dargents,
                 label_Ligne_budgetaire_ENTREES);


    _ComboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_Idx___To___labels_PLUS_Minus_signs
        .insert(YerithAdminCreateWindow::_Label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_sorties_dargents,
                 label_Ligne_budgetaire_SORTIES);




    comboBox_creer_nom_departement->setYerithEditable(true);
    comboBox_creer_fournisseur->setYerithEditable(true);

    comboBox_creer_alerte_designation->setYerithEditable(true);


    setupValidators();


    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);

    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 false);

    pushButton_menu->enable(this, SLOT(Main_MENU()));


    pushButton_selectionner_image->enable(this,
                                          SLOT(selectionner_image_Un___utilisateur()));

    pushButton_supprimer_image->enable(this,
                                          SLOT(supprimer_image_Un___utilisateur()));


    pushButton_creer_charge_financiere_ANNULER->enable(this, SLOT(annuler()));
    pushButton_creer_utilisateur_annuler->enable(this, SLOT(annuler()));
    pushButton_creer_localisation_annuler->enable(this, SLOT(annuler()));
    pushButton_creer_departements_de_produits_annuler->enable(this, SLOT(annuler()));
    pushButton_creer_categorie_annuler->enable(this, SLOT(annuler()));
    pushButton_creer_ligne_budgetaire_ANNULER->enable(this, SLOT(annuler()));
    pushButton_creer_compte_bancaire_annuler->enable(this, SLOT(annuler()));
    pushButton_creer_alerte_annuler->enable(this, SLOT(annuler()));
    pushButton_creer_remise_annuler->enable(this, SLOT(annuler()));



    pushButton_creer_charge_financiere_VALIDER->enable(this, SLOT(creer_charge_financiere()));

    pushButton_creer_utilisateur_valider->enable(this, SLOT(creer_utilisateur___With___PROGRESS_BAR()));


    pushButton_creer_localisation_valider->enable(this, SLOT(creer_localisation___With___PROGRESS_BAR()));

    pushButton_creer_departements_de_produits_valider
		->enable(this, SLOT(creer_departements_de_produits()));

    pushButton_creer_categorie_valider->enable(this, SLOT(creer_categorie()));

    pushButton_creer_LIGNE_budgetaire_VALIDER
		->enable(this, SLOT(creer_ligne_budgetaire()));

    pushButton_creer_compte_bancaire_valider
		->enable(this, SLOT(creer_compte_bancaire()));

    pushButton_creer_alerte_valider->enable(this, SLOT(creer_alerte()));

    pushButton_creer_remise_valider->enable(this, SLOT(creer_remise()));


    pushButton_lister->enable(this, SLOT(lister()));
    pushButton_modifier->enable(this, SLOT(lister()));


    connect(checkBox_reactiver_departement_CMD_REPETITION,
    		SIGNAL(stateChanged(int)),
            this,
			SLOT(handle_reactiver_departement_CMD_REPETITION(int)));


    connect(lineEdit_creer_CHARGE_FINANCIERE_tva_value,
    		SIGNAL(textChanged(const QString &)),
            this,
			SLOT(calculate_tva_value(const QString &)));


    connect(lineEdit_creer_prix_dachat_alunite,
    		SIGNAL(textChanged(const QString &)),
            this,
			SLOT(display_montant_prix_dachat_total(const QString &)));


    connect(doubleSpinBox_quantite,
    		SIGNAL(valueChanged(double)),
            this,
			SLOT(display_montant_prix_dachat_totalby_spinbox(double)));


    connect(actionStocks, SIGNAL(triggered()), this, SLOT(lister()));
    connect(actionMenu, SIGNAL(triggered()), this, SLOT(Main_MENU()));
    connect(actionModifier, SIGNAL(triggered()), this, SLOT(lister()));

    /** Menu actions */
    connect(actionChanger_utilisateur, SIGNAL(triggered()), this,
            SLOT(changer_utilisateur()));
    connect(actionDeconnecter_utilisateur, SIGNAL(triggered()), this,
            SLOT(deconnecter_utilisateur()));
    connect(actionAppeler_aide, SIGNAL(triggered()), this, SLOT(help()));
    connect(actionFermeture, SIGNAL(triggered()), this, SLOT(fermeture()));
    connect(actionA_propos, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(actionRetournerMenuPrincipal, SIGNAL(triggered()), this,
            SLOT(retour_menu_principal()));
    connect(actionQui_suis_je, SIGNAL(triggered()), this,
            SLOT(qui_suis_je()));



    connect(lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE,
    		SIGNAL(textChanged(const QString &)),
			this,
			SLOT(HANDLE_lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE(const QString &)));


    connect(comboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE,
    		SIGNAL(currentTextChanged(const QString &)),
			this,
			SLOT(HANDLE_comboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE(const QString &)));


    connect(comboBox_creer_alerte_designation,
            SIGNAL(currentTextChanged(const QString &)), this,
            SLOT(showProduitInfo(const QString &)));

    connect(comboBox_creer_alerte_destinataire,
            SIGNAL(currentTextChanged(const QString &)), this,
            SLOT(showDestinataireNomComplet(const QString &)));


    connect(radioButton_creer_alerte_quantite, SIGNAL(clicked(bool)), this,
            SLOT(radioButtons_quantite()));

    connect(radioButton_creer_alerte_periode_temps, SIGNAL(clicked(bool)),
            this, SLOT(radioButtons_periode_temps()));

    connect(tabWidget_creer,
    		SIGNAL(currentChanged(int)),
			this,
            SLOT(handleCurrentChanged()));

    connect(tabWidget_creer, SIGNAL(currentChanged(int)), this,
            SLOT(handleCurrentChanged()));

    checkBox_reactiver_departement_CMD_REPETITION->setCheckState(Qt::Checked);
    checkBox_reactiver_departement_CMD_REPETITION->setCheckState(Qt::Unchecked);
}


void YerithAdminCreateWindow::definirPasDeRole()
{
    _logger->log("definirPasDeRole");
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                                 false);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 false);
}


void YerithAdminCreateWindow::definirAdministrateur()
{
    _logger->log("definirAdministrateur");
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                                 true);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 false);
}


void YerithAdminCreateWindow::definirManager()
{
    _logger->log("definirManager");
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                                 true);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 true);
}


void YerithAdminCreateWindow::
        swap_values___LABEL_entrees_sorties_DargEnts(QLabel *new_visible_Entrees_Sorties_Dargents_QLABEL)
{
    if (0 != new_visible_Entrees_Sorties_Dargents_QLABEL)
    {
        if (label_Ligne_budgetaire_ENTREES == new_visible_Entrees_Sorties_Dargents_QLABEL)
        {
            label_Ligne_budgetaire_ENTREES->setVisible(true);
            label_Ligne_budgetaire_SORTIES->setVisible(false);

            lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE
                ->setYerithEnabled(false);

            lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE
                ->setVisible(false);
        }
        else
        {
            label_Ligne_budgetaire_SORTIES->setVisible(true);
            label_Ligne_budgetaire_ENTREES->setVisible(false);

            lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE
                ->setYerithEnabled(true);

            lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE
                ->setVisible(true);
        }
    }
}


void YerithAdminCreateWindow::handle_reactiver_departement_CMD_REPETITION(int state)
{
    if (checkBox_reactiver_departement_CMD_REPETITION->isChecked())
    {
        doubleSpinBox_creer_charge_financiere_CMD_REPETITION->setYerithEnabled(true);
    }
    else
    {
        doubleSpinBox_creer_charge_financiere_CMD_REPETITION->setYerithEnabled(false);
    }
}


void YerithAdminCreateWindow::setupValidators()
{
    lineEdit_creer_localisation_nom
		->setValidator(&YerithUtils::STRING_FOR_YERITH_ERP_3_0_db_column_name_VALIDATOR);


    lineEdit_creer_alerte_quantite_en_stock
        ->setValidator(&YerithUtils::UintValidator);

    lineEdit_creer_alerte_quantite
        ->setValidator(&YerithUtils::UintValidator);


    lineEdit_creer_prix_dachat_alunite
        ->setValidator(&YerithUtils::UintValidator);

    lineEdit_creer_prix_dachat_total
        ->setValidator(&YerithUtils::UintValidator);


    lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE
        ->setValidator(&YerithUtils::UintValidator);

    lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE
        ->setValidator(&YerithUtils::UintValidator);

    lineEdit_creer_remise_quantite_en_stock
        ->setValidator(&YerithUtils::UintValidator);

    lineEdit_creer_remise_montant
        ->setValidator(&YerithUtils::UintValidator);
}


void YerithAdminCreateWindow::show_item_CHARGE_FINANCIERE(bool from_charge_financiere_window /* = false */)
{
    YerithSqlTableModel *CHARGES_FINANCIERES_TableModel =
        &_allWindows->getSqlTableModel_charges_financieres();


    CHARGES_FINANCIERES_TableModel
		->yerithSetFilter_WITH_where_clause
			(QString("%1 = '%2'")
				.arg(YerithDatabaseTableColumn::ID,
					 YerithERPWindows::get_last_lister_selected_row_db_ID()));


	QSqlRecord record = CHARGES_FINANCIERES_TableModel->record(0);


	lineEdit_creer_reference
		->setText(GET_SQL_RECORD_DATA(record,
				  YerithDatabaseTableColumn::REFERENCE));

	lineEdit_creer_designation
		->setText(GET_SQL_RECORD_DATA(record,
				  YerithDatabaseTableColumn::DESIGNATION));

	comboBox_creer_nom_departement
		->find_AND_SET_CURRENT_INDEX
			(GET_SQL_RECORD_DATA(record,
			 YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT));

	comboBox_creer_LIGNE_BUDGETAIRE
		->find_AND_SET_CURRENT_INDEX
			(GET_SQL_RECORD_DATA(record,
			 YerithDatabaseTableColumn::CATEGORIE));

	comboBox_creer_fournisseur
		->find_AND_SET_CURRENT_INDEX
			(GET_SQL_RECORD_DATA(record,
			 YerithDatabaseTableColumn::NOM_ENTREPRISE_FOURNISSEUR));

	doubleSpinBox_quantite
		->setValue(GET_SQL_RECORD_DATA(record, YerithDatabaseTableColumn::QUANTITE_TOTALE)
                    .toDouble());


    double prix_dachat_a_lunite =
        qAbs(GET_SQL_RECORD_DATA(record, YerithDatabaseTableColumn::PRIX_UNITAIRE)
                .toDouble());


	lineEdit_creer_prix_dachat_alunite->setText(QString::number(prix_dachat_a_lunite));


	double prix_dachat = 0.0;


	YerithPOSUser *currentUser = YerithUtils::getAllWindows()->getUser();

	if (0 != currentUser)
	{
		if (currentUser->isManager())
		{
			prix_dachat =
					GET_SQL_RECORD_DATA(record,
							YerithDatabaseTableColumn::PRIX_DACHAT).toDouble();
		}
	}


	lineEdit_creer_prix_dachat_total->setText(GET_CURRENCY_STRING_NUM(prix_dachat));


	textEdit_creer_une_CHARGE_FINANCIERE->setText(GET_SQL_RECORD_DATA(record,
			YerithDatabaseTableColumn::DESCRIPTION_charge_financiere));
}


void YerithAdminCreateWindow::setupLineEdits()
{
	lineEdit_creer_prix_dachat_total->setYerithEnabled(false);


	lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE->setYerithEnabled(false);

    lineEdit_creer_remise_montant->setYerithEnabled(false);

    //lineEdit_creer_localisation_nom->setValidator(&YerithUtils::STRING_FOR_YERITH_ERP_3_0_VALIDATOR_DB_COLUMN_NAME);

    lineEdit_creer_CHARGE_FINANCIERE_tva_value->setValidator(&YerithUtils::POSITIVE_DoubleValidator);

    lineEdit_creer_prix_dachat_alunite->setValidator(&YerithUtils::POSITIVE_DoubleValidator);

    lineEdit_creer_remise_montant->setValidator(&YerithUtils::POSITIVE_DoubleValidator);

    lineEdit_creer_alerte_quantite->setValidator(&YerithUtils::UintValidator);

    lineEdit_creer_utilisateur_mot_passe_1->setEchoMode(QLineEdit::Password);

    lineEdit_creer_utilisateur_verification->setEchoMode(QLineEdit::Password);


    connect(lineEdit_creer_remise_designation_article,
            SIGNAL(textChanged(const QString &)),
			this,
            SLOT(showProduitInfo(const QString &)));
}


void YerithAdminCreateWindow::setupDateTimeEdits()
{
    dateEdit_creer_utilisateur_date_naissance->setStartDate(GET_CURRENT_DATE);
    dateEdit_creer_localisation_date_ouverture->setStartDate(GET_CURRENT_DATE);

    dateEdit_creer_alerte_date_debut->setStartDate(GET_CURRENT_DATE);
    dateEdit_creer_alerte_date_fin->setStartDate(GET_CURRENT_DATE);

    dateEdit_creer_remise_date_debut->setStartDate(GET_CURRENT_DATE);
    dateEdit_creer_remise_date_fin->setStartDate(GET_CURRENT_DATE);
}


void YerithAdminCreateWindow::rendreVisible(YerithSqlTableModel *stocksTableModel,
                                            unsigned selectedSujetAction,
											bool 	 a_show_item_CHARGE_FINANCIERE /* = false */,
											bool     from_charge_financiere_window /* = false */ )
{
    HANDLE_rendering_IF_ALLOWED_PREVIOUSLY_With___Direct_modification_entry();


    ___retranslateUi();


    _curStocksTableModel = stocksTableModel;

    tabWidget_creer->setCurrentIndex(selectedSujetAction);

    clear_utilisateur_all_fields();

    clear_departements_de_produits_all_fields();

    clear_categorie_all_fields();

    clear_CHARGE_FINANCIERE_all_fields();

    clear_LIGNE_BUDGETAIRE_all_fields();

    clear_compte_bancaire_all_fields();

    clear_localisation_all_fields();

    clear_alerte_all_fields();

    clear_remise_all_fields();


    comboBox_nom_departement_produit
        ->populateComboBoxRawString(YerithDatabase::DEPARTEMENTS_PRODUITS,
                                    YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT);

    comboBox_creer_alerte_designation
        ->populateComboBoxRawString(YerithDatabase::STOCKS,
                                    YerithDatabaseTableColumn::DESIGNATION);


    lineEdit_creer_remise_designation_article
        ->setupMyStaticQCompleter(YerithDatabase::STOCKS,
                                  YerithDatabaseTableColumn::DESIGNATION);


    lineEdit_creer_utilisateur_localisation->setYerithEnabled(false);


    lineEdit_creer_utilisateur_localisation
        ->setText(YerithERPConfig::THIS_SITE_LOCALISATION_NAME);


    populateUtilisateurComboBoxes();

    populate_CHARGE_FINANCIERE_ComboBoxes();

    populate_LIGNE_BUDGETAIRE_ComboBoxes();

    populateRemiseComboBoxes();

    populateAlerteComboBoxes();

    populateLocalisationComboBoxes();




    creer_departements_de_produits_check_fields();

    creer_categorie_check_fields();

    creer_charge_financiere_CHECK_fields();

    creer_ligne_budgetaire_CHECK_fields();

    creer_compte_bancaire_check_fields();

    creer_localisation_check_fields();


    creer_utilisateur_check_fields_entry();

    creer_alerte_check_fields_entry();

    creer_remise_check_fields_entry();


    lineEdit_creer_categorie_nom->setFocus();

    comboBox_creer_nom_departement->setFocus();

	lineEdit_creer_INTITULE_de_la_LIGNE_BUDGETAIRE->setFocus();

	lineEdit_creer_compte_bancaire_intitule_du_compte_bancaire->setFocus();

	lineEdit_creer_utilisateur_prenom->setFocus();

	comboBox_label_creer_localisation_adresse_ip->setFocus();

	lineEdit_creer_remise_nom->setFocus();

    lineEdit_creer_departements_de_produits_nom->setFocus();


    if (a_show_item_CHARGE_FINANCIERE)
    {
    	show_item_CHARGE_FINANCIERE(from_charge_financiere_window);
    }


    RESET_Bits_Showing_Cancellation_Modification_REQUEST_Needed();

    setVisible(true);
}


QString YerithAdminCreateWindow::get_currently_Selected_Object_For_WORK()
{
    QString currently_modiFied_object;

    switch (tabWidget_creer->currentIndex())
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:
        currently_modiFied_object = QObject::tr("Utilisateur");
		break;

    case SUJET_ACTION_LOCALISATION:
        currently_modiFied_object = QObject::tr("LOCALISATION");
        break;

    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:
        currently_modiFied_object = QObject::tr("Département");
		break;

    case SUJET_ACTION_CATEGORIE:
        currently_modiFied_object = QObject::tr("Catégorie");
        break;

    case SUJET_ACTION_ligne_budgetaire:
        currently_modiFied_object = QObject::tr("LIGNE BUDÉGTAIRE");
        break;

    case SUJET_ACTION_COMPTE_BANCAIRE:
        currently_modiFied_object = QObject::tr("Compte bancaire");
        break;

    case SUJET_ACTION_REMISE:
        currently_modiFied_object = QObject::tr("Remise");
        break;

    case SUJET_ACTION_ALERTE:
        currently_modiFied_object = QObject::tr("Alerte");
        break;

    case SUJET_ACTION_CHARGE_FINANCIERE:
        currently_modiFied_object = QObject::tr("Charge financière");
        break;

    default:
        break;
    }

    return currently_modiFied_object;
}


void YerithAdminCreateWindow::rendreInvisible()
{
    QString currently_modiFied_object = get_currently_Selected_Object_For_WORK();

    if (GET___Succeeded___INSERTION_to_DB_Tables_Bit())
    {
        dateEdit_creer_utilisateur_date_naissance->reset();
        dateEdit_creer_localisation_date_ouverture->reset();
        dateEdit_creer_alerte_date_debut->reset();
        dateEdit_creer_alerte_date_fin->reset();

        YerithPOSAdminWindowsCommons::rendreInvisible();
    }
    else
    {
        _Cancel_MODIFICATION_request_Object
            ->set_First__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("VOUS étiez entrain de faire 1 insertion -- %1 (administration).\n"
                             "Souhaiter vous annuler\n"
                             "ceci en sortant de cette fenêtre du programme ?")
                    .arg(currently_modiFied_object));


        _Cancel_MODIFICATION_request_Object
            ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("Vous avez annulé(e) 1 insertion -- %1 (administration) !")
                  .arg(currently_modiFied_object));


        _Cancel_MODIFICATION_request_Object
            ->Set_Window__MODIFICATION_CANCELLATION_TITLE
                (QObject::tr("ANNULER 1 insertion -- %1 (administration) ")
                  .arg(currently_modiFied_object));


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


            dateEdit_creer_utilisateur_date_naissance->reset();
            dateEdit_creer_localisation_date_ouverture->reset();
            dateEdit_creer_alerte_date_debut->reset();
            dateEdit_creer_alerte_date_fin->reset();

            YerithPOSAdminWindowsCommons::rendreInvisible();
        }
    }
}


void YerithAdminCreateWindow::showDestinataireNomComplet(const QString &destinataireId)
{
    _logger->log("showDestinataireNomComplet(const QString &)",
                 QString("destinataireId: %1").arg(destinataireId));

    QString
    strQuery(QString("SELECT %1 FROM %2 WHERE %3 = '%4'").arg
             (YerithDatabaseTableColumn::NOM_COMPLET, YerithDatabase::USERS,
              YerithDatabaseTableColumn::NOM_UTILISATEUR, destinataireId));

    QSqlQuery query(strQuery);

    QSqlRecord rec = query.record();

    if (query.last())
    {
        QString destinataireId_nom_complet(query.value(0).toString());

        lineEdit_creer_alerte_nom_destinataire
            ->setText(destinataireId_nom_complet);
    }
}


void YerithAdminCreateWindow::HANDLE_comboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE(const QString &text_changed)
{
    QLabel *_current_Visible_QLABEL_entrees_sorties_dargents =
                _ComboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_Idx___To___labels_PLUS_Minus_signs
                    .value(comboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE->currentText());


    swap_values___LABEL_entrees_sorties_DargEnts(_current_Visible_QLABEL_entrees_sorties_dargents);


    lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE
        ->setText(GET_DOUBLE_STRING(text_changed.toDouble()));
}


void YerithAdminCreateWindow::showProduitInfo(const QString &nomProduit)
{
    _logger->log("showProduitInfo(const QString &)",
                 QString("designation: %1").arg(nomProduit));

    double stock_dalerte = 0.0;

    double quantite_en_stock = 0.0;

    QString sqlNomProduit(YerithUtils::prepareSqlStr(nomProduit));

    QString
    strQuery(QString("SELECT %1 FROM %2 WHERE %3 = '%4'").arg
             (YerithDatabaseTableColumn::QUANTITE_TOTALE,
              YerithDatabase::STOCKS, YerithDatabaseTableColumn::DESIGNATION,
              sqlNomProduit));

    QSqlQuery query(strQuery);
    QSqlRecord rec = query.record();

    while (query.next())
    {
        quantite_en_stock += query.value(0).toDouble();
    }

    query.clear();

    strQuery =
                    QString("SELECT %1 FROM %2 WHERE %3 = '%4'").arg
                    (YerithDatabaseTableColumn::STOCK_DALERTE, YerithDatabase::STOCKS,
                     YerithDatabaseTableColumn::DESIGNATION, sqlNomProduit);

    if (query.exec(strQuery))
    {
        rec = query.record();

        if (query.next())
        {
            stock_dalerte = query.value(0).toDouble();
        }
    }

    switch (tabWidget_creer->currentIndex())
    {
    case SUJET_ACTION_ALERTE:
        lineEdit_creer_alerte_quantite_en_stock->setText(QString::number
                                                         (quantite_en_stock,
                                                          'f', 0));
        lineEdit_creer_alerte_stock_dalerte->
        setText(QString::number(stock_dalerte, 'f', 0));
        break;

    case SUJET_ACTION_REMISE:
        lineEdit_creer_remise_quantite_en_stock->setText(QString::number
                                                         (quantite_en_stock,
                                                          'f', 0));
        break;

    default:
        break;
    }

    showDatePeremption(nomProduit);
}

void YerithAdminCreateWindow::showDatePeremption(const QString &nomProduit)
{
    _logger->log("showDatePeremption",
                 QString("designation: %1").arg(nomProduit));

    QString sqlNomProduit(YerithUtils::prepareSqlStr(nomProduit));

    QString
    strQuery(QString("SELECT %1 FROM %2 WHERE %3 = '%4'").arg
             (YerithDatabaseTableColumn::DATE_PEREMPTION,
              YerithDatabase::STOCKS, YerithDatabaseTableColumn::DESIGNATION,
              sqlNomProduit));

    QSqlQuery query(strQuery);

    QSqlRecord rec = query.record();

    QDate date_peremption;
    QDate date_peremption_tmp;

    unsigned c = 0;

    while (query.next())
    {
        date_peremption_tmp = query.value(0).toDate();
        if (0 == c)
        {
            date_peremption = date_peremption_tmp;
            ++c;
        }
        else
        {
            if (date_peremption_tmp < date_peremption)
            {
                date_peremption = date_peremption_tmp;
            }
        }
    }

    switch (tabWidget_creer->currentIndex())
    {
    case SUJET_ACTION_ALERTE:
        lineEdit_creer_alerte_date_peremption->setText(date_peremption.
                                                       toString(YerithUtils::
                                                                DATE_FORMAT));
        break;

    case SUJET_ACTION_REMISE:
        lineEdit_creer_remise_date_peremption->setText(date_peremption.
                                                       toString(YerithUtils::
                                                                DATE_FORMAT));
        break;

    default:
        break;
    }
}


void YerithAdminCreateWindow::lister()
{
    QString currently_modiFied_object = get_currently_Selected_Object_For_WORK();

    _Cancel_MODIFICATION_request_Object
        ->set_First__MODIFICATION_CANCELLATION_MESSAGE
            (QObject::tr("VOUS étiez entrain de faire 1 insertion -- %1 (administration).\n"
                         "Souhaiter vous annuler\n"
                         "ceci en sortant de cette fenêtre du programme ?")
                .arg(currently_modiFied_object));

    _Cancel_MODIFICATION_request_Object
        ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
            (QObject::tr("Vous avez annulé(e) 1 insertion -- %1 (administration) !")
                .arg(currently_modiFied_object));

    _Cancel_MODIFICATION_request_Object
        ->Set_Window__MODIFICATION_CANCELLATION_TITLE
            (QObject::tr("ANNULER 1 insertion -- %1 (administration)")
                .arg(currently_modiFied_object));


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


        _allWindows->_adminListerWindow
            ->rendreVisible(tabWidget_creer->currentIndex());

        rendreInvisible();
    }
}


void YerithAdminCreateWindow::annuler()
{
    QString currently_modiFied_object = get_currently_Selected_Object_For_WORK();

    _Cancel_MODIFICATION_request_Object
        ->set_First__MODIFICATION_CANCELLATION_MESSAGE
        (QObject::tr("VOUS étiez entrain de faire 1 insertion -- %1 (administration).\n"
                     "Souhaiter vous annuler\n"
                     "ceci en sortant de cette fenêtre du programme ?")
            .arg(currently_modiFied_object));

    _Cancel_MODIFICATION_request_Object
        ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
        (QObject::tr("Vous avez annulé(e) 1 insertion -- %1 (administration) !")
            .arg(currently_modiFied_object));

    _Cancel_MODIFICATION_request_Object
        ->Set_Window__MODIFICATION_CANCELLATION_TITLE
        (QObject::tr("ANNULER 1 insertion -- %1 (administration)")
            .arg(currently_modiFied_object));


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


        clear_utilisateur_all_fields();

        clear_departements_de_produits_all_fields();

        clear_categorie_all_fields();

        clear_compte_bancaire_all_fields();

        clear_localisation_all_fields();

        clear_alerte_all_fields();

        clear_remise_all_fields();


        _allWindows->_adminWindow->rendreVisible(_curStocksTableModel);

        rendreInvisible();
    }
}


void YerithAdminCreateWindow::radioButtons_quantite()
{
    dateEdit_creer_alerte_date_fin->setYerithEnabled(false);
    dateEdit_creer_alerte_date_debut->setYerithEnabled(false);

    comboBox_creer_alerte_condition->setEnabled(true);
    lineEdit_creer_alerte_quantite->setYerithEnabled(true);

    if (radioButton_creer_alerte_periode_temps->isChecked())
    {
        radioButton_creer_alerte_periode_temps->setChecked(false);
    }
}


void YerithAdminCreateWindow::radioButtons_periode_temps()
{
    dateEdit_creer_alerte_date_fin->setYerithEnabled(true);
    dateEdit_creer_alerte_date_debut->setYerithEnabled(true);

    comboBox_creer_alerte_condition->setEnabled(false);
    lineEdit_creer_alerte_quantite->setYerithEnabled(false);

    if (radioButton_creer_alerte_quantite->isChecked())
    {
        radioButton_creer_alerte_quantite->setChecked(false);
    }
}


void YerithAdminCreateWindow::handleCurrentChanged()
{
    clear_utilisateur_all_fields();

    clear_localisation_all_fields();

    clear_departements_de_produits_all_fields();

    clear_categorie_all_fields();

    clear_compte_bancaire_all_fields();

    clear_alerte_all_fields();

    clear_remise_all_fields();

    populateUtilisateurComboBoxes();

    populateAlerteComboBoxes();

    populateLocalisationComboBoxes();

    creer_utilisateur_check_fields_entry();

    creer_departements_de_produits_check_fields();

    creer_categorie_check_fields();

    creer_compte_bancaire_check_fields();

    creer_localisation_check_fields();

    creer_alerte_check_fields_entry();

    creer_remise_check_fields_entry();



	_allWindows->_adminWindow->_curAdminSujetAction =
			(enum AdminSujetAction) tabWidget_creer->currentIndex();



    switch (tabWidget_creer->currentIndex())
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ utilisateurs"));
		break;


    case SUJET_ACTION_LOCALISATION:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ LOCALISATIONS"));
        break;


    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ départements"));
		break;


    case SUJET_ACTION_CATEGORIE:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ catégories"));
        break;


    case SUJET_ACTION_ligne_budgetaire:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ LIGNES BUDÉGTAIRES"));
        break;


    case SUJET_ACTION_COMPTE_BANCAIRE:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ comptes bancaires"));
        break;


    case SUJET_ACTION_REMISE:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ remises"));
        break;


    case SUJET_ACTION_ALERTE:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ alertes"));
        break;


    case SUJET_ACTION_CHARGE_FINANCIERE:

        _windowName = QString("%1 - %2")
                    			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                    				 QObject::tr("administration ~ créer ~ charges financières"));
        break;

    default:
        break;
    }

    setWindowTitle(_windowName);
}


void YerithAdminCreateWindow::calculate_tva_value(const QString &VALEUR_TVA)
{
	_VALEUR_TVA = VALEUR_TVA.toDouble() / 100.0 ;

	display_montant_prix_dachat_total(lineEdit_creer_prix_dachat_alunite->text());

	display_montant_prix_dachat_totalby_spinbox(doubleSpinBox_quantite->value());
}


void YerithAdminCreateWindow::
		display_montant_prix_dachat_total(const QString &prix_dachat_alunite)
{
    double qte_totale = doubleSpinBox_quantite->value();

    double montant_PRIX_DACHAT_TOTAL =
    		qte_totale * lineEdit_creer_prix_dachat_alunite->text().toDouble();


    _MONTANT_TVA_CHARGE_FINANCIERE = _VALEUR_TVA * montant_PRIX_DACHAT_TOTAL;


    _montant_PRIX_DACHAT_TOTAL = _MONTANT_TVA_CHARGE_FINANCIERE +
    							 montant_PRIX_DACHAT_TOTAL;


    lineEdit_creer_prix_dachat_total
		->setText(GET_CURRENCY_STRING_NUM(_montant_PRIX_DACHAT_TOTAL));
}


void YerithAdminCreateWindow::
		display_montant_prix_dachat_totalby_spinbox(double quantite)
{
    double qte_totale = doubleSpinBox_quantite->value();

    double montant_PRIX_DACHAT_TOTAL =
    		qte_totale * lineEdit_creer_prix_dachat_alunite->text().toDouble();


    _MONTANT_TVA_CHARGE_FINANCIERE = _VALEUR_TVA * montant_PRIX_DACHAT_TOTAL;


    _montant_PRIX_DACHAT_TOTAL = _MONTANT_TVA_CHARGE_FINANCIERE +
    							 montant_PRIX_DACHAT_TOTAL;


    lineEdit_creer_prix_dachat_total
		->setText(GET_CURRENCY_STRING_NUM(_montant_PRIX_DACHAT_TOTAL));
}


void YerithAdminCreateWindow::password_push_button_Line_Edit_initializations()
{
    _push_button_password =
        new YerithPushButtonPASSWORD(this,
                                     lineEdit_creer_utilisateur_mot_passe_1,
                                     pushButton_cacher_le_mot_de_passe,
                                     pushButton_CREER_voir_le_mot_de_passe);


    _push_button_password_Verification =
        new YerithPushButtonPASSWORD(this,
                                     lineEdit_creer_utilisateur_verification,
                                     pushButton_cacher_le_mot_de_passe_2_verification,
                                     pushButton_CREER_voir_le_mot_de_passe_2_verification);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____UTILISATEUR()
{
    dateEdit_creer_utilisateur_date_naissance->Set_widget_modified(false);

    lineEdit_creer_utilisateur_prenom->Set_widget_modified(false);
    lineEdit_creer_utilisateur_nom->Set_widget_modified(false);
    lineEdit_creer_utilisateur_lieu_naissance->Set_widget_modified(false);
    lineEdit_creer_utilisateur_ville->Set_widget_modified(false);
    lineEdit_creer_utilisateur_province_etat->Set_widget_modified(false);
    lineEdit_creer_utilisateur_pays->Set_widget_modified(false);
    lineEdit_creer_utilisateur_boite_postale->Set_widget_modified(false);
    lineEdit_creer_utilisateur_email->Set_widget_modified(false);
    lineEdit_creer_utilisateur_numero_telephone_1->Set_widget_modified(false);
    lineEdit_creer_utilisateur_numero_telephone_2->Set_widget_modified(false);
    lineEdit_creer_utilisateur_id->Set_widget_modified(false);
    lineEdit_creer_utilisateur_mot_passe_1->Set_widget_modified(false);
    lineEdit_creer_utilisateur_verification->Set_widget_modified(false);
    lineEdit_creer_utilisateur_localisation->Set_widget_modified(false);

    comboBox_creer_utilisateur_titre->Set_widget_modified(false);
    comboBox_creer_utilisateur_role->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____LOCALISATION()
{
    comboBox_creer_localisation_base_donnees->Set_widget_modified(false);
    comboBox_label_creer_localisation_adresse_ip->Set_widget_modified(false);

    textEdit_creer_localisation_description_lieu->Set_widget_modified(false);

    dateEdit_creer_localisation_date_ouverture->Set_widget_modified(false);


    lineEdit_creer_localisation_nom->Set_widget_modified(false);
    lineEdit_creer_localisation_numero_unique->Set_widget_modified(false);
    lineEdit_creer_localisation_quartier->Set_widget_modified(false);
    lineEdit_creer_localisation_ville->Set_widget_modified(false);
    lineEdit_creer_localisation_province_etat->Set_widget_modified(false);
    lineEdit_creer_localisation_pays->Set_widget_modified(false);
    lineEdit_creer_localisation_boite_postale->Set_widget_modified(false);
    lineEdit_creer_localisation_email->Set_widget_modified(false);
    lineEdit_creer_localisation_numero_telephone_1->Set_widget_modified(false);
    lineEdit_creer_localisation_numero_telephone_2->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____DEPARTEMENTS_DE_PRODUITS()
{
    checkBox_creer_NOM_DEPARTEMENT_AUTRE_stocks_objets_PHYSIQUES->Set_widget_modified(false);

    lineEdit_creer_departements_de_produits_nom->Set_widget_modified(false);

    textEdit_creer_departements_de_produits_description->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____CATEGORIE()
{
    comboBox_nom_departement_produit->Set_widget_modified(false);

    lineEdit_creer_categorie_nom->Set_widget_modified(false);

    textEdit_creer_categorie_description->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____CHARGE_FINANCIERE()
{
    comboBox_creer_nom_departement->Set_widget_modified(false);
    comboBox_creer_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    comboBox_creer_fournisseur->Set_widget_modified(false);

    checkBox_reactiver_departement_CMD_REPETITION->Set_widget_modified(false);

    doubleSpinBox_creer_charge_financiere_CMD_REPETITION->Set_widget_modified(false);
    doubleSpinBox_quantite->Set_widget_modified(false);

    lineEdit_creer_reference->Set_widget_modified(false);
    lineEdit_creer_designation->Set_widget_modified(false);
    lineEdit_creer_prix_dachat_alunite->Set_widget_modified(false);
    lineEdit_creer_prix_dachat_total->Set_widget_modified(false);

    textEdit_creer_une_CHARGE_FINANCIERE->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____LIGNE_BUDGETAIRE()
{
    comboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    comboBox_INTITULE_DU_COMPTE_BANCAIRE->Set_widget_modified(false);

    lineEdit_creer_INTITULE_de_la_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    lineEdit_creer_montant_de_la_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE->Set_widget_modified(false);

    textEdit_creer_une_LIGNE_budgetaire->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____COMPTE_BANCAIRE()
{
    lineEdit_creer_compte_bancaire_reference_du_compte_bancaire->Set_widget_modified(false);
    lineEdit_creer_compte_bancaire_intitule_du_compte_bancaire->Set_widget_modified(false);
    lineEdit_creer_compte_bancaire_institut_bancaire->Set_widget_modified(false);

    textEdit_creer_compte_bancaire_description_du_compte->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____REMISE()
{
    dateEdit_creer_remise_date_debut->Set_widget_modified(false);
    dateEdit_creer_remise_date_fin->Set_widget_modified(false);

    spinBox_remise_pourcentage->Set_widget_modified(false);

    lineEdit_creer_remise_designation_article->Set_widget_modified(false);
    lineEdit_creer_remise_nom->Set_widget_modified(false);
    lineEdit_creer_remise_montant->Set_widget_modified(false);
    lineEdit_creer_remise_quantite_en_stock->Set_widget_modified(false);
    lineEdit_creer_remise_date_peremption->Set_widget_modified(false);

    textEdit_creer_remise_message->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit____ALERTE()
{
    radioButton_creer_alerte_quantite->Set_widget_modified(false);
    radioButton_creer_alerte_periode_temps->Set_widget_modified(false);

    dateEdit_creer_alerte_date_debut->Set_widget_modified(false);
    dateEdit_creer_alerte_date_fin->Set_widget_modified(false);

    comboBox_creer_alerte_designation->Set_widget_modified(false);
    comboBox_creer_alerte_destinataire->Set_widget_modified(false);
    comboBox_creer_alerte_condition->Set_widget_modified(false);

    lineEdit_creer_alerte_nom->Set_widget_modified(false);
    lineEdit_creer_alerte_quantite->Set_widget_modified(false);

    textEdit_creer_alerte_message->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminCreateWindow::reset_window_widgets_modification_Bit()
{
    switch (tabWidget_creer->currentIndex())
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:
        reset_window_widgets_modification_Bit____UTILISATEUR();
		break;

    case SUJET_ACTION_LOCALISATION:
        reset_window_widgets_modification_Bit____LOCALISATION();
        break;

    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:
        reset_window_widgets_modification_Bit____DEPARTEMENTS_DE_PRODUITS();
		break;


    case SUJET_ACTION_CATEGORIE:
        reset_window_widgets_modification_Bit____CATEGORIE();
        break;

    case SUJET_ACTION_ligne_budgetaire:
        reset_window_widgets_modification_Bit____LIGNE_BUDGETAIRE();
        break;

    case SUJET_ACTION_COMPTE_BANCAIRE:
        reset_window_widgets_modification_Bit____COMPTE_BANCAIRE();
        break;

    case SUJET_ACTION_REMISE:
        reset_window_widgets_modification_Bit____REMISE();
        break;

    case SUJET_ACTION_ALERTE:
        reset_window_widgets_modification_Bit____ALERTE();
        break;

    case SUJET_ACTION_CHARGE_FINANCIERE:
        reset_window_widgets_modification_Bit____CHARGE_FINANCIERE();
        break;

    default:
        break;
    }
}


void YerithAdminCreateWindow::hideEvent(QHideEvent *hideEvent)
{
    dateEdit_creer_utilisateur_date_naissance->reset();
    dateEdit_creer_localisation_date_ouverture->reset();
    dateEdit_creer_alerte_date_debut->reset();
    dateEdit_creer_alerte_date_fin->reset();
    dateEdit_creer_remise_date_debut->reset();
    dateEdit_creer_remise_date_fin->reset();
}




#include "creer-utilisateur.cpp"

#include "creer-localisation.cpp"

#include "creer-departements-de-produits.cpp"

#include "creer-categorie.cpp"

#include "creer-CHARGE_FINANCIERE.cpp"

#include "creer-LIGNE_BUDGETAIRE.cpp"

#include "creer-alerte.cpp"

#include "creer-remise.cpp"

#include "creer-compte-bancaire.cpp"
