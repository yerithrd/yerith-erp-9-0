/*
 * yerith-erp-admin-modifier-window.cpp
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-admin-modifier-window.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/widgets/yerith-erp-push-button-PASSWORD.hpp"

#include "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.hpp"


#include <QtCore/QDebug>

#include <QtWidgets/QDesktopWidget>

#include <QtSql/QSqlError>

YerithAdminModifierWindow::YerithAdminModifierWindow()
:YerithPOSAdminWindowsCommons(QObject::tr("administration ~ modifier")),
 _logger(new YerithLogger("YerithAdminModifierWindow")),
 _curSearchSqlTableModel(0),
 _savePassword(false)
{
    setupUi(this);

    mySetupUi(this);

    QMESSAGE_BOX_STYLE_SHEET =
                    QString("QMessageBox {background-color: rgb(%1);}"
                            "QMessageBox QLabel {color: rgb(%2);}").arg
                    (COLOUR_RGB_STRING_YERITH_DARK_GREEN_47_67_67,
                     COLOUR_RGB_STRING_YERITH_WHITE_255_255_255);


    comboBox_label_modifier_localisation_adresse_ip
        ->addItem("127.0.0.1");

    comboBox_label_modifier_localisation_adresse_ip
        ->populateComboBoxRawString_APPEND(YerithDatabase::LOCALISATIONS,
                                           YerithDatabaseTableColumn::ADRESSE_IP);

    comboBox_label_modifier_localisation_adresse_ip
        ->setYerithEditable(true);


    comboBox_modifier_utilisateur_titre
		->setupPopulateNORawString(YerithDatabase::TITRES,
								   YerithDatabaseTableColumn::APPELATION_TITRE,
								   &YerithUtils::_titreToUserViewString);


    comboBox_modifier_utilisateur_role
		->setupPopulateNORawString(YerithDatabase::ROLES,
								   YerithDatabaseTableColumn::NOM_ROLE,
								   &YerithUtils::_roleToUserViewString);


    setupLineEdits();


    password_push_button_Line_Edit_initializations();


    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 false);

    pushButton_menu->enable(this, SLOT(Main_MENU()));

    pushButton_modifier_localisation_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_CHARGE_FINANCIERE_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_categorie_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_lignebudgetaire_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_compte_bancaire_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_utilisateur_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_departements_de_produits_annuler->enable(this, SLOT(annuler()));

    pushButton_modifier_alerte_annuler->enable(this, SLOT(annuler()));

    pushButton_supprimer_image->enable(this, SLOT(supprimer_limage_dun_utilisateur()));

    pushButton_modifier_utilisateur_valider
		->enable(this, SLOT(modifier_utilisateur()));

    pushButton_modifier_localisation_valider
		->enable(this, SLOT(modifier_localisation()));

    pushButton_modifier_CHARGE_FINANCIERE_valider
		->enable(this, SLOT(modifier_CHARGE_FINANCIERE()));

    pushButton_modifier_categorie_valider->enable(this, SLOT(modifier_categorie()));

    pushButton_modifier_LIGNE_BUDGETAIRE_valider->enable(this, SLOT(modifier_LIGNE_BUDGETAIRE()));

    pushButton_modifier_compte_bancaire_valider->enable(this, SLOT(modifier_compte_bancaire()));

    pushButton_modifier_departements_de_produits_valider
		->enable(this, SLOT(modifier_departements_de_produits()));

    pushButton_modifier_alerte_valider->enable(this, SLOT(modifier_alerte()));
    
    pushButton_selectionner_image->enable(this, SLOT(selectionner_image_Un___utilisateur()));

    pushButton_creer->enable(this, SLOT(creer()));
    pushButton_lister->enable(this, SLOT(lister()));
    pushButton_supprimer->enable(this, SLOT(supprimer()));

    connect(actionStocks, SIGNAL(triggered()), this, SLOT(lister()));
    connect(actionCreer, SIGNAL(triggered()), this, SLOT(creer()));
    connect(actionMenu, SIGNAL(triggered()), this, SLOT(Main_MENU()));
    connect(actionSupprimer, SIGNAL(triggered()), this, SLOT(supprimer()));
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
    connect(radioButton_modifier_alerte_quantite, SIGNAL(clicked(bool)),
            this, SLOT(radioButtons_quantite()));
    connect(radioButton_modifier_alerte_periode_temps, SIGNAL(clicked(bool)),
            this, SLOT(radioButtons_periode_temps()));
}


void YerithAdminModifierWindow::definirPasDeRole()
{
    _logger->log("definirPasDeRole");
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                                 false);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 false);
}


void YerithAdminModifierWindow::definirAdministrateur()
{
    _logger->log("definirAdministrateur");
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                                 true);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 false);
}


void YerithAdminModifierWindow::definirManager()
{
    _logger->log("definirManager");
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                                 true);
    YERITH_ERP_ADMIN_WRAPPER_QACTION_SET_ENABLED(actionRetournerMenuPrincipal,
                                                 true);
}


void YerithAdminModifierWindow::setupLineEdits()
{
	//FINANCIAL EXPENSE WIDGET SETUP
    dateEdit_date_de_reception->setYerithEnabled(false);
    dateEdit_date_de_commande->setYerithEnabled(false);

    lineEdit_departement->setYerithEnabled(false);
    lineEdit_reference_produit->setYerithEnabled(false);
    lineEdit_designation->setYerithEnabled(false);
    lineEdit_nom_entreprise_fournisseur->setYerithEnabled(false);
    lineEdit_LIGNE_BUDGETAIRE->setYerithEnabled(false);
    lineEdit_quantite->setYerithEnabled(false);
    lineEdit_prix_dachat->setYerithEnabled(false);
    lineEdit_prix_unitaire->setYerithEnabled(false);

    lineEdit_STATUT_DE_LACHAT->setYerithEnabled(false);
	lineEdit_MONTANT_TVA->setYerithEnabled(false);
	lineEdit_ref_RECU_DACHAT->setYerithEnabled(false);
	lineEdit_LOCALISATION->setYerithEnabled(false);
	lineEdit_ID_commandeur->setYerithEnabled(false);

    textEdit_une_CHARGE_FINANCIERE->setYerithEnabled(false);


    comboBox_label_modifier_localisation_adresse_ip->setYerithEnabled(false);


	lineEdit_modifier_categorie_nom_departement_produit->setYerithEnabled(false);

	lineEdit_modifier_montant_de_la_LIGNE_BUDGETAIRE->setYerithEnabled(false);
	lineEdit_modifier_montant_RESTANT_de_la_LIGNE_BUDGETAIRE->setYerithEnabled(false);

    lineEdit_modifier_utilisateur_id->setYerithEnabled(false);
    lineEdit_modifier_alerte_designation_alerte->setYerithEnabled(false);
    lineEdit_modifier_alerte_quantite->setYerithEnabled(false);
    lineEdit_modifier_localisation_nom->setYerithEnabled(false);
    lineEdit_modifier_utilisateur_mot_passe_1->setEchoMode(QLineEdit::Password);
    lineEdit_modifier_utilisateur_mot_passe_2->setEchoMode(QLineEdit::Password);
}


void YerithAdminModifierWindow::rendreInvisible()
{
    clear_utilisateur_all_fields();
    clear_departements_de_produits_all_fields();
    clear_CHARGE_FINANCIERE_all_fields();
    clear_categorie_all_fields();
    clear_LIGNE_BUDGETAIRE_all_fields();
    clear_localisation_all_fields();
    clear_alerte_all_fields();
    clear_remise_all_fields();


    _savePassword = false;


    YerithPOSAdminWindowsCommons::rendreInvisible();
}


void YerithAdminModifierWindow::supprimer_limage_dun_utilisateur()
{
    QSqlRecord record;

    _allWindows->_adminListerWindow->SQL_QUERY_YERITH_TABLE_VIEW_LAST_SELECTED_ROW(record);

    QString nom_complet = GET_SQL_RECORD_DATA(record,
                                              YerithDatabaseTableColumn::NOM_COMPLET);

    QVariant image_dun_utilisateur =
                record.value(YerithDatabaseTableColumn::IMAGE_DUN_UTILISATEUR);

    if (image_dun_utilisateur.toByteArray().isEmpty())
    {
        QString msg = QObject::tr("L'utilisateur '%1' n'a pas d'image enregistrée !")
                           .arg(nom_complet);

        YerithQMessageBox::information(this,
                                       QObject::tr("suppression de l'image d'1 utilisateur"),
                                       msg);

        label_admin_modifier_image_utilisateur->clear();
        label_admin_modifier_image_utilisateur->setAutoFillBackground(false);

        return;
    }


    QString msgSupprimer = QObject::tr("Poursuivre avec la suppression de l'image de l'utilisateur \"");

    msgSupprimer.append(nom_complet);
    msgSupprimer.append("\" ?");

    if (QMessageBox::Ok ==
            YerithQMessageBox::question(this,
                                        QObject::tr("suppression de l'image d'1 utilisateur"),
                                        msgSupprimer, QMessageBox::Cancel,
                                        QMessageBox::Ok))
    {
        record.setValue(YerithDatabaseTableColumn::IMAGE_DUN_UTILISATEUR,
                        QVariant(QVariant::ByteArray));

        bool success_removed_USER_IMAGE = _allWindows->
                                                _stocksWindow
                                                    ->SQL_UPDATE_YERITH_TABLE_VIEW_LAST_SELECTED_ROW(record);

        label_admin_modifier_image_utilisateur->clear();

        label_admin_modifier_image_utilisateur->setAutoFillBackground(false);

        if (success_removed_USER_IMAGE)
        {
            msgSupprimer.clear();

            msgSupprimer.append(QObject::tr
                                ("L'image du l'utilisateur '%1' a été supprimée !").
                                arg(nom_complet));

            YerithQMessageBox::information(this,
                                           QObject::tr
                                           ("suppression de l'image d'1 utilisateur avec succès"),
                                           msgSupprimer);
        }
        else
        {
            msgSupprimer.clear();

            msgSupprimer.append(QObject::tr("L'image de l'utilisateur '%1' ne pouvait pas être supprimée !")
                                    .arg(nom_complet));

            YerithQMessageBox::information(this,
                                           QObject::tr
                                           ("échec de la suppression de l'image d'1 utilisateur"),
                                           msgSupprimer);
        }
    }
    else
    {
    }
}


void YerithAdminModifierWindow::password_push_button_Line_Edit_initializations()
{
    _push_button_password =
        new YerithPushButtonPASSWORD(this,
                                     lineEdit_modifier_utilisateur_mot_passe_1,
                                     pushButton_Modifier_cacher_le_mot_de_passe,
                                     pushButton_Modifier_voir_le_mot_de_passe);


    _push_button_password_Verification =
        new YerithPushButtonPASSWORD(this,
                                     lineEdit_modifier_utilisateur_mot_passe_2,
                                     pushButton_Modifier_cacher_le_mot_de_passe_2_verification,
                                     pushButton_Modifier_voir_le_mot_de_passe_2_verification);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__UTILISATEUR()
{
    dateEdit_modifier_utilisateur_date_naissance->Set_widget_modified(false);

    lineEdit_modifier_utilisateur_prenom->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_nom->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_lieu_naissance->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_ville->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_province_etat->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_pays->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_boite_postale->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_email->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_numero_telephone_1->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_numero_telephone_2->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_id->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_mot_passe_1->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_mot_passe_2->Set_widget_modified(false);
    lineEdit_modifier_utilisateur_localisation->Set_widget_modified(false);

    comboBox_modifier_utilisateur_titre->Set_widget_modified(false);
    comboBox_modifier_utilisateur_role->Set_widget_modified(false);

    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__LOCALISATION()
{
    dateEdit_modifier_localisation_date_ouverture->Set_widget_modified(false);

    comboBox_modifier_localisation_base_donnees->Set_widget_modified(false);
    comboBox_label_modifier_localisation_adresse_ip->Set_widget_modified(false);

    lineEdit_modifier_localisation_nom->Set_widget_modified(false);
    lineEdit_modifier_localisation_numero_unique->Set_widget_modified(false);
    lineEdit_modifier_localisation_quartier->Set_widget_modified(false);
    lineEdit_modifier_localisation_ville->Set_widget_modified(false);
    lineEdit_modifier_localisation_province_etat->Set_widget_modified(false);
    lineEdit_modifier_localisation_pays->Set_widget_modified(false);
    lineEdit_modifier_localisation_boite_postale->Set_widget_modified(false);
    lineEdit_modifier_localisation_email->Set_widget_modified(false);
    lineEdit_modifier_localisation_numero_telephone_1->Set_widget_modified(false);
    lineEdit_modifier_localisation_numero_telephone_2->Set_widget_modified(false);


    textEdit_modifier_localisation_description_lieu->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__DEPARTEMENTS_DE_PRODUITS()
{
    checkBox_modifier_NOM_DEPARTEMENT_AUTRE_stocks_objets_PHYSIQUES->Set_widget_modified(false);

    lineEdit_modifier_departements_de_produits_nom->Set_widget_modified(false);

    textEdit_modifier_departements_de_produits_description->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__CATEGORIE()
{
    lineEdit_modifier_categorie_nom->Set_widget_modified(false);
    lineEdit_modifier_categorie_nom_departement_produit->Set_widget_modified(false);

    textEdit_modifier_categorie_description->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__CHARGE_FINANCIERE()
{
    doubleSpinBox_creer_charge_financiere_CMD_REPETITION->Set_widget_modified(false);

    textEdit_une_CHARGE_FINANCIERE->Set_widget_modified(false);

    lineEdit_departement->Set_widget_modified(false);
    lineEdit_reference_produit->Set_widget_modified(false);
    lineEdit_designation->Set_widget_modified(false);
    lineEdit_nom_entreprise_fournisseur->Set_widget_modified(false);
    lineEdit_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    lineEdit_quantite->Set_widget_modified(false);
    lineEdit_prix_dachat->Set_widget_modified(false);
    lineEdit_prix_unitaire->Set_widget_modified(false);
    lineEdit_MONTANT_TVA->Set_widget_modified(false);
    lineEdit_STATUT_DE_LACHAT->Set_widget_modified(false);
    lineEdit_ref_RECU_DACHAT->Set_widget_modified(false);
    lineEdit_LOCALISATION->Set_widget_modified(false);
    lineEdit_ID_commandeur->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__LIGNE_BUDGETAIRE()
{
    comboBox_modifier_INTITULE_DU_COMPTE_BANCAIRE->Set_widget_modified(false);

    lineEdit_MODIFIER_INTITULE_de_la_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    lineEdit_modifier_montant_de_la_LIGNE_BUDGETAIRE->Set_widget_modified(false);
    lineEdit_modifier_montant_RESTANT_de_la_LIGNE_BUDGETAIRE->Set_widget_modified(false);

    textEdit_modifier_une_LIGNE_budgetaire->Set_widget_modified(false);

    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__COMPTE_BANCAIRE()
{
    lineEdit_modifier_compte_bancaire_reference_du_compte_bancaire->Set_widget_modified(false);
    lineEdit_modifier_compte_bancaire_intitule_du_compte_bancaire->Set_widget_modified(false);
    lineEdit_modifier_compte_bancaire_institut_bancaire->Set_widget_modified(false);

    textEdit_modifier_compte_bancaire_description_du_compte->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__REMISE()
{
    dateEdit_modifier_remise_date_debut->Set_widget_modified(false);
    dateEdit_modifier_remise_date_fin->Set_widget_modified(false);

    lineEdit_modifier_remise_designation->Set_widget_modified(false);
    lineEdit_modifier_remise_nom->Set_widget_modified(false);
    lineEdit_modifier_remise_montant->Set_widget_modified(false);
    lineEdit_modifier_remise_quantite_en_stock->Set_widget_modified(false);
    lineEdit_modifier_remise_date_peremption->Set_widget_modified(false);

    spinBox_modifier_remise_pourcentage->Set_widget_modified(false);

    textEdit_modifier_remise_message->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit__m__ALERTE()
{
    comboBox_modifier_alerte_condition->Set_widget_modified(false);

    dateEdit_modifier_alerte_date_debut->Set_widget_modified(false);
    dateEdit_modifier_alerte_date_fin->Set_widget_modified(false);

    radioButton_modifier_alerte_quantite->Set_widget_modified(false);
    radioButton_modifier_alerte_periode_temps->Set_widget_modified(false);

    lineEdit_modifier_alerte_designation_article->Set_widget_modified(false);
    lineEdit_modifier_alerte_designation_alerte->Set_widget_modified(false);
    lineEdit_modifier_alerte_id_destinataire->Set_widget_modified(false);
    lineEdit_modifier_alerte_quantite->Set_widget_modified(false);
    lineEdit_modifier_alerte_nom_destinataire->Set_widget_modified(false);

    textEdit_modifier_alerte_message->Set_widget_modified(false);


    set_yerith_WindowModified(false);
    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithAdminModifierWindow::reset_window_widgets_modification_Bit()
{
    switch (tabWidget_modifier->currentIndex())
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:
        reset_window_widgets_modification_Bit__m__UTILISATEUR();
		break;

    case SUJET_ACTION_LOCALISATION:
        reset_window_widgets_modification_Bit__m__LOCALISATION();
        break;

    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:
        reset_window_widgets_modification_Bit__m__DEPARTEMENTS_DE_PRODUITS();
		break;


    case SUJET_ACTION_CATEGORIE:
        reset_window_widgets_modification_Bit__m__CATEGORIE();
        break;

    case SUJET_ACTION_ligne_budgetaire:
        reset_window_widgets_modification_Bit__m__CHARGE_FINANCIERE();
        break;

    case SUJET_ACTION_COMPTE_BANCAIRE:
        reset_window_widgets_modification_Bit__m__COMPTE_BANCAIRE();
        break;

    case SUJET_ACTION_REMISE:
        reset_window_widgets_modification_Bit__m__REMISE();
        break;

    case SUJET_ACTION_ALERTE:
        reset_window_widgets_modification_Bit__m__ALERTE();
        break;

    case SUJET_ACTION_CHARGE_FINANCIERE:
        reset_window_widgets_modification_Bit__m__CHARGE_FINANCIERE();
        break;

    default:
        break;
    }
}


void YerithAdminModifierWindow::enableOtherTabs(enum AdminSujetAction curAction, bool enabled)
{
    tabWidget_modifier->setTabEnabled(curAction, !enabled);
    for (int k = 0; k <= SUJET_ACTION_LOCALISATION; ++k)
    {
        if (k != curAction)
        {
            tabWidget_modifier->setTabEnabled(k, enabled);
        }
    }
}


void YerithAdminModifierWindow::rendreVisible(enum AdminSujetAction selectedSujetAction)
{
    retranslateUi(this);

    clear_utilisateur_all_fields();
    clear_departements_de_produits_all_fields();
    clear_categorie_all_fields();
    clear_CHARGE_FINANCIERE_all_fields();
    clear_LIGNE_BUDGETAIRE_all_fields();
    clear_compte_bancaire_all_fields();
    clear_localisation_all_fields();
    clear_alerte_all_fields();
    clear_remise_all_fields();

    switch (selectedSujetAction)
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_COMPTE_UTILISATEUR);
        enableOtherTabs(SUJET_ACTION_COMPTE_UTILISATEUR, false);
        setupEditCompteUtilisateur();
        break;

    case SUJET_ACTION_LOCALISATION:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_LOCALISATION);
        enableOtherTabs(SUJET_ACTION_LOCALISATION, false);
        setupEditLocalisation();
        break;

    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:
        tabWidget_modifier->setCurrentIndex
        (SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS);
        enableOtherTabs(SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS, false);
        setupEditDepartementsDeProduits();
        break;

    case SUJET_ACTION_CATEGORIE:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_CATEGORIE);
        enableOtherTabs(SUJET_ACTION_CATEGORIE, false);
        setupEditCategorie();
        break;

    case SUJET_ACTION_ligne_budgetaire:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_ligne_budgetaire);
        enableOtherTabs(SUJET_ACTION_ligne_budgetaire, false);
        setupEdit_LIGNE_BUDGETAIRE();
        break;

    case SUJET_ACTION_COMPTE_BANCAIRE:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_COMPTE_BANCAIRE);
        enableOtherTabs(SUJET_ACTION_COMPTE_BANCAIRE, false);
        setupEditCompteBancaire();
        break;

    case SUJET_ACTION_ALERTE:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_ALERTE);
        enableOtherTabs(SUJET_ACTION_ALERTE, false);
        setupEditAlerte();
        break;

    case SUJET_ACTION_REMISE:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_REMISE);
        enableOtherTabs(SUJET_ACTION_REMISE, false);
        setupEditRemise();
        break;

    case SUJET_ACTION_CHARGE_FINANCIERE:
        tabWidget_modifier->setCurrentIndex(SUJET_ACTION_CHARGE_FINANCIERE);
        enableOtherTabs(SUJET_ACTION_CHARGE_FINANCIERE, false);
        setupEdit_CHARGE_FINANCIERE();
        break;

    default:
        break;
    }


    RESET_Bits_Showing_Cancellation_Modification_REQUEST_Needed();

    setVisible(true);
}


void YerithAdminModifierWindow::retourListerCompteUtilisateur()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- Utilisateur (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- Utilisateur (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- Utilisateur (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_COMPTE_UTILISATEUR);


        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourListerLocalisation()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- Localisation (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- Localisation (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- Localisation (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_LOCALISATION);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourListerDepartementsDeProduits()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- \"Departements de Produits\" (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- \"Departements de Produits\" (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- \"Departements de Produits\" (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourListerCategorie()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- Catégorie (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- Catégorie (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- Catégorie (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_CATEGORIE);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourLister_CHARGE_FINANCIERE()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- 'CHARGE Financière' (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- 'CHARGE Financière' (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- 'CHARGE Financière' (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_CHARGE_FINANCIERE);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourLister_LIGNE_BUDGETAIRE()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- \"LIGNE Budgétaire\" (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- \"LIGNE Budgétaire\" (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- \"LIGNE Budgétaire\" (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_ligne_budgetaire);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourListerCompteBancaire()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- \"COMPTE Bancaire\" (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- \"COMPTE Bancaire\" (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- \"COMPTE Bancaire\" (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_COMPTE_BANCAIRE);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourListerAlerte()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- ALERTES (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- ALERTES (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- ALERTES (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_ALERTE);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::retourListerRemise()
{
    _Cancel_MODIFICATION_request_Object
    ->set_First__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("VOUS étiez entrain de faire 1 Modification -- REMISES (administration).\n"
                 "Souhaiter vous annuler\n"
                 "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
    (QObject::tr("Vous avez annulé(e) 1 modification -- REMISES (administration) !"));

    _Cancel_MODIFICATION_request_Object
    ->Set_Window__MODIFICATION_CANCELLATION_TITLE
    (QObject::tr("ANNULER 1 modification -- REMISES (administration)"));


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


        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_REMISE);

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::annuler()
{
    int current_index = tabWidget_modifier->currentIndex();

    switch (current_index)
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:
        retourListerCompteUtilisateur();
        break;

    case SUJET_ACTION_LOCALISATION:
        retourListerLocalisation();
        break;

    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:
        retourListerDepartementsDeProduits();
        break;

    case SUJET_ACTION_CATEGORIE:
        retourListerCategorie();
        break;

    case SUJET_ACTION_ligne_budgetaire:
    	retourLister_LIGNE_BUDGETAIRE();
        break;

    case SUJET_ACTION_COMPTE_BANCAIRE:
        retourListerCompteBancaire();
        break;

    case SUJET_ACTION_ALERTE:
        retourListerAlerte();
        break;

    case SUJET_ACTION_REMISE:
        retourListerRemise();
        break;

    case SUJET_ACTION_CHARGE_FINANCIERE:
    	retourLister_CHARGE_FINANCIERE();
        break;

    default:
        break;
    }

    _allWindows->_adminListerWindow->rendreVisible(current_index);
}


void YerithAdminModifierWindow::creer()
{
    _Cancel_MODIFICATION_request_Object
        ->set_First__MODIFICATION_CANCELLATION_MESSAGE
            (QObject::tr("VOUS étiez entrain de faire 1 Modification.\n"
                         "Souhaiter vous annuler\n"
                         "ceci en sortant de cette fenêtre du programme ?"));

    _Cancel_MODIFICATION_request_Object
        ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
            (QObject::tr("Vous avez annulé(e) 1 Modification !"));

    _Cancel_MODIFICATION_request_Object
        ->Set_Window__MODIFICATION_CANCELLATION_TITLE
            (QObject::tr("ANNULER 1 Modification"));


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


        _allWindows->_adminCreateWindow
            ->rendreVisible(_curStocksTableModel,
                            tabWidget_modifier->currentIndex());


        rendreInvisible();
    }
}


void YerithAdminModifierWindow::lister()
{
    QString item_type;

    switch (tabWidget_modifier->currentIndex())
    {
    case SUJET_ACTION_COMPTE_UTILISATEUR:
        item_type = QObject::tr("Utilisateur");
        break;

    case SUJET_ACTION_LOCALISATION:
        item_type = QObject::tr("Localisation");
        break;

    case SUJET_ACTION_DEPARTEMENTS_DE_PRODUITS:
        item_type = QObject::tr("Departements de Produits");
        break;

    case SUJET_ACTION_CATEGORIE:
        item_type = QObject::tr("Catégorie");
        break;

    case SUJET_ACTION_ligne_budgetaire:
    	item_type = QObject::tr("LIGNE Budgétaire");
        break;

    case SUJET_ACTION_COMPTE_BANCAIRE:
        item_type = QObject::tr("COMPTE Bancaire");
        break;

    case SUJET_ACTION_ALERTE:
        item_type = QObject::tr("ALERTES");
        break;

    case SUJET_ACTION_REMISE:
        item_type = QObject::tr("REMISES");
        break;

    case SUJET_ACTION_CHARGE_FINANCIERE:
    	item_type = QObject::tr("CHARGE Financière");
        break;

    default:
        break;
    }

    _Cancel_MODIFICATION_request_Object
        ->set_First__MODIFICATION_CANCELLATION_MESSAGE
            (QObject::tr("VOUS étiez entrain de faire 1 Modification -- %1 (administration).\n"
                         "Souhaiter vous annuler\n"
                         "ceci en sortant de cette fenêtre du programme ?")
                .arg(item_type));

    _Cancel_MODIFICATION_request_Object
        ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
            (QObject::tr("Vous avez annulé(e) 1 Modification -- %1 (administration) !")
                .arg(item_type));

    _Cancel_MODIFICATION_request_Object
        ->Set_Window__MODIFICATION_CANCELLATION_TITLE
            (QObject::tr("ANNULER 1 Modification -- %1 (administration) !")
                .arg(item_type));


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

        _allWindows->_adminListerWindow->rendreVisible(tabWidget_modifier->currentIndex());

        rendreInvisible();
    }
}


void YerithAdminModifierWindow::supprimer()
{
    _allWindows->_adminListerWindow->supprimer();
    _allWindows->_adminListerWindow->rendreVisible(tabWidget_modifier->currentIndex());
    rendreInvisible();
}


void YerithAdminModifierWindow::radioButtons_quantite()
{
    if (radioButton_modifier_alerte_periode_temps->isChecked())
    {
        radioButton_modifier_alerte_periode_temps->setChecked(false);
    }
}


void YerithAdminModifierWindow::radioButtons_periode_temps()
{
    if (radioButton_modifier_alerte_quantite->isChecked())
    {
        radioButton_modifier_alerte_quantite->setChecked(false);
    }
}



#include "modifier-utilisateur.cpp"

#include "modifier-localisation.cpp"

#include "modifier-departements_de_produits.cpp"

#include "modifier-CHARGE-FINANCIERE.cpp"

#include "modifier-categorie.cpp"

#include "modifier-LIGNE-BUDGETAIRE.cpp"

#include "modifier-compte-bancaire.cpp"

#include "modifier-alerte.cpp"

#include"modifier-remise.cpp"
