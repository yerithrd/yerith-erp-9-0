/*
 * yerith-erp-entrer-window.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-entrer-window.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/utils/yerith-erp-payment-processing-information.hpp"

#include "src/utils/yerith-erp-service-stock-marchandise-data.hpp"

#include "src/utils/yerith-erp-database-table-column.hpp"

#include "src/users/yerith-erp-users.hpp"

#include "src/utils/yerith-erp-config.hpp"

#include "src/utils/yerith-erp-database-table-column.hpp"

#include "src/utils/yerith-erp-historique-stock.hpp"

#include "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.hpp"


#include <QtCore/QtMath>

#include <QtSql/QSqlQuery>



const uint YerithEntrerWindow::PRIX_DE_VENTE_En_Gros_Par_Unite_Index = 1;

const uint YerithEntrerWindow::PRIX_DE_VENTE_En_Gros_Index = 0;

const uint YerithEntrerWindow::PRIX_DE_VENTE_Par_Unite_Index = 1;

const uint YerithEntrerWindow::PRIX_DE_VENTE_Index = 0;


const unsigned YerithEntrerWindow::CURRENT_MAX_DESCRIPTION_TEXT_SIZE_CHARACTER_NUMBER = 256;



YerithEntrerWindow::YerithEntrerWindow():YerithWindowsCommons(),
    _logger(new YerithLogger("YerithEntrerWindow")),
    _currentServiceInfo(0),
    _stocks_id(0),
    _Last_choice_insert(set_choice_insert_UNDEFINED),
    _a_show_ITEM(false),
    _montantTva(0.0),
    _montantTva_en_gros(0.0),
    _INSIDE___handleTVACheckBox(false),
    _INSIDE___handle_ReferenceDesignation_checkBox(false),
    _historique_stock_actif(true),
	_tvaCheckBoxPreviousState(false)
{
    _windowName = QString("%1 - %2")
                			.arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                				 QObject::tr("entrer 1 IMMOBILISATION, OU 1 stock, ou 1 service, Ou 1 Charge financière"));

    _windowName_WITH_NO_MAINTENANCE = _windowName;

    setupUi(this);

    mySetupUi(this);

    QMESSAGE_BOX_STYLE_SHEET =
                    QString("QMessageBox {background-color: rgb(%1);}"
                            "QMessageBox QLabel {color: rgb(%2);}").arg
                    (COLOUR_RGB_STRING_YERITH_GRAY_78_78_78,
                     COLOUR_RGB_STRING_YERITH_GOLD_245_194_17);


    checkBox_achat->setChecked(true);


    label_montant_total_vente_service->setVisible(false);

    lineEdit_service_montant_total_vente->setVisible(false);

    setupLineEdits();

    setupLineEditsQCompleters();

    setupDateTimeEdits();



    checkBox_HISTORIQUE->setChecked(_historique_stock_actif);



    checkBox_date_peremption->setChecked(true);


    comboBox_reference_produit->setYerithEditable(true);

    comboBox_nom_departement_produit->setYerithEditable(true);

    comboBox_nom_entreprise_fournisseur->setYerithEditable(true);

    comboBox_categorie_produit->setYerithEditable(true);


    populateEntrerUnStock_OU_ServiceComboBoxes();


    populateComboBoxes__Labels_prix_ventes();


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(action_START_YR_QVGE_dynamic_analysis_tool, false);


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_Principal, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionStocks, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSortir, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAlertes, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregisterStock, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSupprimerImage, false);

    pushButton_supprimer_limage_du_stock->disable(this);
    pushButton_afficher_stocks->disable(this);
    pushButton_menu_principal->disable(this);
    pushButton_sortir->disable(this);
    pushButton_annuler->disable(this);




    connect(action___HIDE_all_other_choices_RadioButton,
            SIGNAL(triggered()),
            this,
            SLOT(ON_______HIDE_all_other_choices_RadioButton()));


    connect(action___Show_all_choices,
            SIGNAL(triggered()),
            this,
            SLOT(ON_______Show_all_RadioButton()));




    connect(action_START_YR_QVGE_dynamic_analysis_tool,
            SIGNAL(triggered()),
            this,
            SLOT(ON_action_START_YR_QVGE_dynamic_analysis_tool()));


    /** Menu actions */
    connect(actionChanger_utilisateur, SIGNAL(triggered()), this,
            SLOT(changer_utilisateur()));
    connect(actionAppeler_aide, SIGNAL(triggered()), this, SLOT(help()));
    connect(actionDeconnecter_utilisateur, SIGNAL(triggered()), this,
            SLOT(deconnecter_utilisateur()));
    connect(actionMenu_Principal, SIGNAL(triggered()), this, SLOT(Main_MENU()));
    connect(actionStocks, SIGNAL(triggered()), this, SLOT(stocks()));
    connect(actionSortir, SIGNAL(triggered()), this, SLOT(sortir()));
    connect(actionAnnuler, SIGNAL(triggered()), this, SLOT(Main_MENU()));
    connect(actionSupprimerImage, SIGNAL(triggered()), this,
            SLOT(supprimer_image_stock()));
    connect(actionEnregisterStock, SIGNAL(triggered()), this,
            SLOT(enregistrer_produit()));
    connect(actionFermeture, SIGNAL(triggered()), this, SLOT(fermeture()));
    connect(actionA_propos, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(actionAlertes, SIGNAL(triggered()), this, SLOT(alertes()));
    connect(actionInformationEntreprise, SIGNAL(triggered()), this,
            SLOT(infosEntreprise()));
    connect(actionQui_suis_je, SIGNAL(triggered()), this,
            SLOT(qui_suis_je()));
    connect(actionAdministration, SIGNAL(triggered()), this,
            SLOT(administration()));

#ifdef YERITH_CLIENT
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
#endif

    connect(lineEdit_quantite_par_lot,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(display_quantite_totale(const QString &)));


    connect(comboBox_UNITE_DE_Mesure,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(handle_comboBox_unite_de_mesure_changement(int)));


    connect(comboBox_categorie_produit,
            SIGNAL(currentTextChanged(const QString &)),
            this,
            SLOT(handle_categorie_produit_changement(const QString &)));


    connect(comboBox_nom_departement_produit,
            SIGNAL(currentTextChanged(const QString &)),
            this,
            SLOT(handle_departement_de_produits_changement(const QString &)));


    connect(doubleSpinBox_lots_entrant,
            SIGNAL(valueChanged(double)),
            this,
            SLOT(display_quantite_totale_by_spinbox(double)));


    connect(radioButton_inserer_une_IMMOBILISATION,
            SIGNAL(toggled(bool)),
            this,
            SLOT(handle_checkBox_INSERT_ASSET(bool)));

    connect(radioButton_inserer_un_stock,
            SIGNAL(toggled(bool)),
            this,
            SLOT(handle_checkBox_INSERT_STOCK(bool)));

    connect(radioButton_INSERER_UNE_CHARGE_FINANCIERE,
            SIGNAL(toggled(bool)),
            this,
            SLOT(handle_checkBox_INSERER_UNE_CHARGE_FINANCIERE(bool)));


    connect(radioButton_service_vente_de_service_au_client,
            SIGNAL(toggled(bool)),
            this,
            SLOT(handle_checkBox_service_vente(bool)));


    connect(checkBox_HISTORIQUE,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_HISTORIQUE_CHECKBOX(int)));


    connect(checkBox_pourcentage_prix_dachat_prix_de_vente,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE(int)));


    connect(checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE_EN_GROS(int)));


    connect(checkBox_date_peremption,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_EXPIRATION_DATE_checkBox(int)));


    connect(lineEdit_designation,
            SIGNAL(editingFinished()),
            this,
            SLOT(handle_Edit_ReferenceDesignation()));



    connect(comboBox_reference_produit,
            SIGNAL(SIGNAL_set_yerith_enabled_called(bool)),
            this,
            SLOT(handle_Set_YerithEnabled_ComboBox_Reference_Produit(bool)));


    connect(checkBox_EXACT_Reference_value_AS_DESIGNATION,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_ReferenceDesignation_checkBox(int)));



    connect(checkBox_achat,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_achat_checkBox(int)));

    connect(checkBox_tva,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handleTVACheckBox(int)));

    connect(lineEdit_prix_dachat,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(calculate_and_display_ALL_benefit_buying_price_percentage()));

    connect(lineEdit_prix_vente,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(calculate_and_display_ALL_benefit_buying_price_percentage()));

    /*
     * Fonctionne seulement avec 1 seul configuration.
     */
    connect(lineEdit_prix_vente,
            SIGNAL(textEdited(const QString &)),
            this,
            SLOT(display_service_montant_total_vente()));

//    connect(lineEdit_prix_vente,
//            SIGNAL(editingFinished()),
//            this,
//            SLOT(display_prix_vente()));

    connect(lineEdit_prix_vente_en_gros,
            SIGNAL(textEdited(const QString &)),
            this,
            SLOT(edited_prix_vente_en_gros(const QString &)));

    connect(lineEdit_prix_vente_en_gros,
            SIGNAL(editingFinished()),
            this,
            SLOT(display_prix_vente_en_gros()));


    connect(lineEdit_pourcentage_prix_dachat_prix_de_vente,
            SIGNAL(textEdited(const QString &)),
            this,
            SLOT(edited_pourcentage_prix_dachat_prix_de_vente(const QString &)));


    connect(lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros,
            SIGNAL(textEdited(const QString &)),
            this,
            SLOT(edited_pourcentage_prix_dachat_prix_de_vente_EN_GROS(const QString &)));


    connect(lineEdit_designation,
            SIGNAL(editingFinished()),
            this,
            SLOT(product_search_with_designation()));

    connect(comboBox_reference_produit,
            SIGNAL(currentTextChanged(const QString &)),
            this,
            SLOT(product_search_with_reference()));


    populateCOMBOBOX__UNITES_DE_Mesures();


    radioButton_inserer_un_stock->setChecked(true);


    checkBox_EXACT_Reference_value_AS_DESIGNATION->setChecked(true);


    setupShortcuts();
}

void YerithEntrerWindow::deconnecter_utilisateur()
{
    clear_all_fields();
    _allWindows->definirPasDeRole();
    _allWindows->_mainWindow->show();
    rendreInvisible();
}

void YerithEntrerWindow::setupLineEdits()
{
    label_POURCENTAGE_1->setVisible(false);
    label_POURCENTAGE_2->setVisible(false);

    lineEdit_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
    lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);

    lineEdit_pourcentage_prix_dachat_prix_de_vente->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

    lineEdit_service_montant_total_vente->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    lineEdit_quantite_totale->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    lineEdit_tva->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

    lineEdit_tva->setText(YerithUtils::getTvaStringWithPercent());

    lineEdit_quantite_totale->setValidator(&YerithUtils::POSITIVE_DoubleValidator_GREATER_THAN_ZERO);
    lineEdit_quantite_par_lot->setValidator(&YerithUtils::POSITIVE_DoubleValidator_GREATER_THAN_ZERO);
    lineEdit_stock_dalerte->setValidator(&YerithUtils::POSITIVE_DoubleValidator);
    lineEdit_prix_dachat->setValidator(&YerithUtils::POSITIVE_DoubleValidator);
    lineEdit_prix_vente->setValidator(&YerithUtils::POSITIVE_DoubleValidator);
    lineEdit_prix_vente_en_gros->setValidator(&YerithUtils::POSITIVE_DoubleValidator);

    calculate_and_display_benefit_buying_price_percentage();
}


void YerithEntrerWindow::setupLineEditsQCompleters__FOR_STOCK_INVENTORY()
{
    if (Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        checkBox_tva->setVisible(true);

        lineEdit_tva->setVisible(true);
    }

    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED() ||
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {

        Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(false);

        comboBox_label_prix_vente->setVisible(false);

        lineEdit_prix_vente->setYerithEnabled(true);

        lineEdit_designation->clearQCompleter();
    }
    else
    {
        QString aConditionStr =
                    YerithUtils::generateSqlIs(YerithDatabaseTableColumn::IS_SERVICE,
                                               YerithUtils::MYSQL_FALSE_LITERAL);

        lineEdit_designation->
            setupMyStaticQCompleter(YerithDatabase::MARCHANDISES,
                                    YerithDatabaseTableColumn::DESIGNATION,
                                    false,
                                    aConditionStr);


        comboBox_localisation_produit
            ->setYerithEditable(true);

        comboBox_localisation_produit
            ->populateComboBoxRawString_APPEND(YerithDatabase::STOCKS,
                                               YerithDatabaseTableColumn::LOCALISATION_STOCK);

        comboBox_localisation_produit
            ->addItem_AFTER_POPULATE(YerithUtils::EMPTY_STRING);
    }


   if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        Switch__label__SUPPLIER_fournisseur_banque_institution(true);

        comboBox_label_prix_vente->setVisible(true);

        lineEdit_prix_vente->setVisible(true);

        comboBox_nom_entreprise_fournisseur
            ->populateComboBoxRawString(YerithDatabase::CLIENTS,
                                        YerithDatabaseTableColumn::NOM_ENTREPRISE);
    }
    else
    {
        Switch__label__SUPPLIER_fournisseur_banque_institution();

        comboBox_nom_entreprise_fournisseur
            ->populateComboBoxRawString(YerithDatabase::FOURNISSEURS,
                                        YerithDatabaseTableColumn::NOM_ENTREPRISE);
    }

    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
        Switch__label__SUPPLIER_fournisseur_banque_institution();

        Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(true);

        label_montant_total_vente_service->setText(QObject::tr("montant total achat"));
    }
    else
    {
        Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(false);

        label_montant_total_vente_service->setText(QObject::tr("montant total vente"));
    }
}


void YerithEntrerWindow::POPULATE_banking_accounts__For__ONLY_budget_LINES_accounts()
{
    QStringList bank_institution_names;


    QSqlRecord a_current_bank_account_Sql_RECORD;


    QString a_current_BUDGET_Line_INTITULE;

    QString a_current_bank_account_TItle;

    QString a_current_bank_account_INSTITUTION;


    bank_institution_names.append("");


    comboBox_nom_entreprise_fournisseur
        ->populateComboBoxRawString(YerithDatabase::LIGNES_BUDGETAIRES,
                                    YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);


    //Searching for all banking accounts that have already
    //created budget lines.
    for (uint j = 0; j < comboBox_nom_entreprise_fournisseur->count(); ++j)
    {
        a_current_BUDGET_Line_INTITULE =
            comboBox_nom_entreprise_fournisseur->itemText(j);

        if (a_current_BUDGET_Line_INTITULE.isEmpty())
        {
            continue ;
        }

        a_current_bank_account_TItle =
            Get_intitule_du_compte_bancaire__FROM__BUDGET_LINE_table
            (a_current_BUDGET_Line_INTITULE);

//                QDEBUG_STRING_OUTPUT_2(QString("a_current_bank_account_TItle [from '%1']")
//                                            .arg(a_current_BUDGET_Line_INTITULE),
//                                        a_current_bank_account_TItle);

        if (a_current_bank_account_TItle.isEmpty())
        {
            continue ;
        }

        if (YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS_msg_silent
                                    (*this,
                                     _allWindows->getSqlTableModel_comptes_bancaires(),
                                     a_current_bank_account_TItle,
                                     QObject::tr("intitule de compte bancaire a re-verifier"),
                                     YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE))
        {
            YerithSqlTableModel &aBankSqlTableModel =
                _allWindows->getSqlTableModel_comptes_bancaires();

            aBankSqlTableModel.yerithSetFilter_WITH_where_clause
                (YerithUtils::generateSqlIs(YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE,
                                            a_current_bank_account_TItle));

            int rowCount_result = aBankSqlTableModel.easySelect();

            if (rowCount_result > 0)
            {
                a_current_bank_account_Sql_RECORD = aBankSqlTableModel.record(0);

                a_current_bank_account_INSTITUTION =
                    GET_SQL_RECORD_DATA(a_current_bank_account_Sql_RECORD,
                                        YerithDatabaseTableColumn::INSTITUT_BANCAIRE);

                if (!a_current_bank_account_INSTITUTION.isEmpty())
                {
                    bank_institution_names.append(a_current_bank_account_INSTITUTION);
                }
            }
        }
    }

    comboBox_nom_entreprise_fournisseur->clearField();

    comboBox_nom_entreprise_fournisseur->addItems(bank_institution_names);
}


void YerithEntrerWindow::populateComboBoxes__Labels_prix_ventes()
{
    QStringList aQStringList;

    if (YerithMainWindow::LANGUE_ANGLAISE)
    {
        aQStringList.append(QObject::tr("price of sale (ATC)"));

        aQStringList.append(QObject::tr("price of sale per unit (ATC)"));
    }
    else
    {
        aQStringList.append(QObject::tr("prix de vente (TTC)"));

        aQStringList.append(QObject::tr("prix de vente par unité (TTC)"));
    }

    comboBox_label_prix_vente->clear();

    comboBox_label_prix_vente->addItems_raw_as___Defined__in_QComboBox(aQStringList);

    comboBox_label_prix_vente->setCurrentIndex(YerithEntrerWindow::PRIX_DE_VENTE_Index);


    aQStringList.clear();


    if (YerithMainWindow::LANGUE_ANGLAISE)
    {
        aQStringList.append(QObject::tr("whole sale price (ATC)"));

        aQStringList.append(QObject::tr("whole sale price per unit (ATC)"));
    }
    else
    {
        aQStringList.append(QObject::tr("prix de vente en gros (TTC)"));

        aQStringList.append(QObject::tr("prix de vente en gros par unité (TTC)"));
    }


    comboBox_label_prix_vente_en_gros->clear();

    comboBox_label_prix_vente_en_gros->addItems_raw_as___Defined__in_QComboBox(aQStringList);

    comboBox_label_prix_vente_en_gros->setCurrentIndex(YerithEntrerWindow::PRIX_DE_VENTE_En_Gros_Index);



    Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(true);

    comboBox_label_prix_vente->setVisible(false);

    comboBox_label_prix_vente_en_gros->setVisible(false);
}


void YerithEntrerWindow::populateCOMBOBOX__REFERENCE_PRODUIT()
{
    if (radioButton_inserer_un_stock->isChecked())
    {
        QString
        aConditionStr(YerithUtils::generateSqlIs
                      (YerithDatabaseTableColumn::IS_SERVICE,
                       YerithUtils::MYSQL_FALSE_LITERAL));
        comboBox_reference_produit->populateComboBoxRawString(YerithDatabase::
                                                              MARCHANDISES,
                                                              YerithDatabaseTableColumn::
                                                              REFERENCE,
                                                              aConditionStr);
    }
    else if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        QString
        aConditionStr(YerithUtils::generateSqlIs
                      (YerithDatabaseTableColumn::IS_SERVICE,
                       YerithUtils::MYSQL_TRUE_LITERAL));

        comboBox_reference_produit->populateComboBoxRawString(YerithDatabase::
                                                              MARCHANDISES,
                                                              YerithDatabaseTableColumn::
                                                              REFERENCE,
                                                              aConditionStr);

        comboBox_reference_produit->populateComboBoxRawString_APPEND
        (YerithDatabase::SERVICES_COMPLETES,
         YerithDatabaseTableColumn::REFERENCE, aConditionStr);
    }
    else if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
        comboBox_reference_produit->populateComboBoxRawString(YerithDatabase::
                                                              CHARGES_FINANCIERES,
                                                              YerithDatabaseTableColumn::
                                                              REFERENCE);
    }
}


void YerithEntrerWindow::populateCOMBOBOX__UNITES_DE_Mesures()
{
    comboBox_UNITE_DE_Mesure
        ->setupPopulateNORawString(YerithDatabase::UNITES_DE_MESURES,
                                   YerithDatabaseTableColumn::UNITE_DE_MESURE,
                                   &YerithUtils::_mesureuniteToUserViewString);

    comboBox_UNITE_DE_Mesure
        ->populateComboBoxWithout(YerithUtils::UNITE_DE_MESURE_INDEFINIE);
}


void YerithEntrerWindow::populateCOMBOBOX__CATEGORIE()
{
    QString departement_de_produits_choisi =
                    comboBox_nom_departement_produit->currentText();

    QString
    aConditionStr(YerithUtils::generateSqlIs
                  (YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                   departement_de_produits_choisi));

    if (radioButton_inserer_une_IMMOBILISATION->isChecked() 	||
    	radioButton_inserer_un_stock->isChecked()				||
		radioButton_service_vente_de_service_au_client->isChecked())
    {
    	comboBox_categorie_produit->clearField();

    	comboBox_categorie_produit
			->populateComboBoxRawString(YerithDatabase::CATEGORIES,
										YerithDatabaseTableColumn::NOM_CATEGORIE,
										aConditionStr);
    }

    comboBox_categorie_produit->checkField();
}


void YerithEntrerWindow::set_red_palette(YerithLineEdit &a_yerith_qline_edit_WIDGET)
{
    a_yerith_qline_edit_WIDGET.setPalette(YerithUtils::YERITH_RED_PALETTE);

//    a_yerith_qline_edit_WIDGET.setPalette
//        (_allWindows->_marchandisesWindow->getQMainWindowToolBar()->palette());

    a_yerith_qline_edit_WIDGET.setForegroundRole(QPalette::Window);
}


bool YerithEntrerWindow::is_PRIX_per_unit_of_measure_SET()
{
    bool result =
        (PRIX_DE_VENTE_Par_Unite_Index == comboBox_label_prix_vente->currentIndex() &&
         PRIX_DE_VENTE_En_Gros_Par_Unite_Index == comboBox_label_prix_vente_en_gros->currentIndex()) ? true : false;


    return result;
}


void YerithEntrerWindow::
        populateEntrerUnStock_OU_ServiceComboBoxes(enum entrer_VISIBLE_CHOICE choice_insert /* = set_choice_insert_STANDARD_INVENTORY_STOCK */)
{
    if (set_choice_sell_TO_CLIENT             == choice_insert)
    {
        comboBox_nom_entreprise_fournisseur
            ->populateComboBoxRawString(YerithDatabase::CLIENTS,
                                        YerithDatabaseTableColumn::NOM_ENTREPRISE);
    }
    else if (set_choice_insert_FINANCIAL_EXPENSE_loan_Debt == choice_insert)
    {
    	comboBox_categorie_produit
			->populateComboBoxRawString(YerithDatabase::LIGNES_BUDGETAIRES,
										YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);
    }
    else if (set_choice_insert_FINANCIAL_EXPENSE == choice_insert)
    {
    	comboBox_categorie_produit
			->populateComboBoxRawString(YerithDatabase::LIGNES_BUDGETAIRES,
										YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);
    }
    else
    {
        comboBox_nom_entreprise_fournisseur
            ->populateComboBoxRawString(YerithDatabase::FOURNISSEURS,
                                        YerithDatabaseTableColumn::NOM_ENTREPRISE);
    }


    Handle___Departement_de_produits___Via___RADIOBUTTONS();


    comboBox_nom_departement_produit->setFocus();
}


void YerithEntrerWindow::SET___label_stock_dalerte_value_STR()
{
    QString yri_unite_de_mesure_cr = comboBox_UNITE_DE_Mesure->currentText();

    if (yri_unite_de_mesure_cr.isEmpty())
    {
        label_stock_dalerte
            ->setText(QObject::tr("stock d'alerte"));
    }
    else
    {
        label_stock_dalerte
            ->setText(QObject::tr("stock d'alerte (%1)")
                      .arg(yri_unite_de_mesure_cr));
    }
}


void YerithEntrerWindow::set_PRIX_DE_VENTE_combobBOXLABEL()
{
    SET___label_stock_dalerte_value_STR();


    comboBox_label_prix_vente
        ->setCurrentIndex(YerithEntrerWindow::PRIX_DE_VENTE_Index);

    comboBox_label_prix_vente->setEnabled(false);


    comboBox_UNITE_DE_Mesure->resetYerithComboBox();


    set_PRIX_DE_VENTE_GROS_combobBOXLABEL();
}


void YerithEntrerWindow::set_PRIX_DE_VENTE_GROS_combobBOXLABEL()
{
    comboBox_label_prix_vente_en_gros
        ->setCurrentIndex(YerithEntrerWindow::PRIX_DE_VENTE_En_Gros_Index);

    comboBox_label_prix_vente_en_gros->setEnabled(false);

    comboBox_UNITE_DE_Mesure->resetYerithComboBox();
}


void YerithEntrerWindow::set_PRIX_DE_VENTE_par_Unite_combobBOXLABEL()
{
    SET___label_stock_dalerte_value_STR();


    comboBox_label_prix_vente
        ->setCurrentIndex(YerithEntrerWindow::PRIX_DE_VENTE_Par_Unite_Index);


    comboBox_label_prix_vente->setEnabled(false);


    set_PRIX_DE_VENTE_GROS_par_Unite_combobBOXLABEL();
}


void YerithEntrerWindow::set_PRIX_DE_VENTE_GROS_par_Unite_combobBOXLABEL()
{
    comboBox_label_prix_vente_en_gros
        ->setCurrentIndex(YerithEntrerWindow::PRIX_DE_VENTE_En_Gros_Par_Unite_Index);

    comboBox_label_prix_vente_en_gros->setEnabled(false);


    if (PRIX_DE_VENTE_Index == comboBox_label_prix_vente->currentIndex())
    {
        set_PRIX_DE_VENTE_GROS_combobBOXLABEL();
    }
}


void YerithEntrerWindow::reset_window_widgets_modification_Bit()
{
    lineEdit_designation->Set_widget_modified(false);
    lineEdit_pourcentage_prix_dachat_prix_de_vente->Set_widget_modified(false);
    lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->Set_widget_modified(false);
    lineEdit_quantite_par_lot->Set_widget_modified(false);
    lineEdit_quantite_totale->Set_widget_modified(false);
    lineEdit_stock_dalerte->Set_widget_modified(false);
    lineEdit_reference_recu_dachat->Set_widget_modified(false);
    lineEdit_prix_dachat->Set_widget_modified(false);
    lineEdit_prix_vente->Set_widget_modified(false);
    lineEdit_prix_vente_en_gros->Set_widget_modified(false);
    comboBox_localisation_produit->Set_widget_modified(false);

    comboBox_nom_departement_produit->Set_widget_modified(false);
    comboBox_categorie_produit->Set_widget_modified(false);
    comboBox_nom_entreprise_fournisseur->Set_widget_modified(false);
    comboBox_UNITE_DE_Mesure->Set_widget_modified(false);
    comboBox_reference_produit->Set_widget_modified(false);

    doubleSpinBox_lots_entrant->Set_widget_modified(false);

    textEdit_description->Set_widget_modified(false);


    checkBox_EXACT_Reference_value_AS_DESIGNATION
        ->Set_widget_modified(false);

    checkBox_pourcentage_prix_dachat_prix_de_vente
        ->Set_widget_modified(false);

    checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros
        ->Set_widget_modified(false);

    checkBox_achat->Set_widget_modified(false);
    checkBox_HISTORIQUE->Set_widget_modified(false);
    checkBox_date_peremption->Set_widget_modified(false);
    checkBox_tva->Set_widget_modified(false);


    set_yerith_WindowModified(false);

    Set_Succeeded_INSERTION_to_DB_Tables_Bit(false);
}


void YerithEntrerWindow::setupShortcuts()
{
    setupShortcutActionMessageDaide(*actionAppeler_aide);
    setupShortcutActionQuiSuisJe(*actionQui_suis_je);
}


void YerithEntrerWindow::definirPasDeRole()
{
    _logger->log("definirPasDeRole");

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(action_START_YR_QVGE_dynamic_analysis_tool, false);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                           false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionStocks, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSortir, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAlertes, false);;
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregisterStock, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSupprimerImage, false);

    pushButton_afficher_stocks->disable(this);
    pushButton_sortir->disable(this);
    pushButton_annuler->disable(this);
    pushButton_supprimer_limage_du_stock->disable(this);
    pushButton_selectionner_image->disable(this);
    pushButton_INSERER->disable(this);
}


void YerithEntrerWindow::definirCaissier()
{
    _logger->log("definirCaissier - definirPasDeRole()");

    definirPasDeRole();
}


void YerithEntrerWindow::definirManager()
{
    _logger->log("definirManager");

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(action_START_YR_QVGE_dynamic_analysis_tool, true);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                           true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_Principal, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionStocks, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSortir, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAlertes, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, true);

#ifdef YERITH_CLIENT
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
#endif

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregisterStock, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSupprimerImage, true);

    pushButton_supprimer_limage_du_stock->enable(this,
                                                 SLOT(supprimer_image_stock
                                                      ()));
    pushButton_afficher_stocks->enable(this, SLOT(stocks()));
    pushButton_menu_principal->enable(this, SLOT(Main_MENU()));
    pushButton_sortir->enable(this, SLOT(sortir()));
    pushButton_annuler->enable(this, SLOT(Main_MENU()));
    pushButton_selectionner_image->enable(this,
                                          SLOT(selectionner_image_produit
                                               ()));
    pushButton_INSERER->enable(this, SLOT(handle_enregistrer()));
}


void YerithEntrerWindow::definirVendeur()
{
    _logger->log("definirVendeur");


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(action_START_YR_QVGE_dynamic_analysis_tool, false);


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur,
                                           true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_Principal, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionStocks, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSortir, false);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAlertes, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregisterStock, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSupprimerImage, false);

    pushButton_supprimer_limage_du_stock->disable(this);
    pushButton_afficher_stocks->enable(this, SLOT(stocks()));
    pushButton_menu_principal->enable(this, SLOT(Main_MENU()));
    pushButton_sortir->disable(this);
    pushButton_annuler->enable(this, SLOT(Main_MENU()));
    pushButton_selectionner_image->disable(this);
    pushButton_INSERER->enable(this, SLOT(handle_enregistrer()));
}


void YerithEntrerWindow::definirGestionaireDesStocks()
{
    _logger->log("definirGestionaireDesStocks");


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(action_START_YR_QVGE_dynamic_analysis_tool, false);


    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionDeconnecter_utilisateur, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionMenu_Principal, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionStocks, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSortir, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAlertes, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);

#ifdef YERITH_CLIENT
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAdministration, false);
#endif

    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionQui_suis_je, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionAnnuler, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionEnregisterStock, true);
    YERITH_ERP_WRAPPER_QACTION_SET_ENABLED(actionSupprimerImage, true);

    pushButton_supprimer_limage_du_stock->enable(this,
                                                 SLOT(supprimer_image_stock
                                                      ()));
    pushButton_afficher_stocks->enable(this, SLOT(stocks()));
    pushButton_menu_principal->enable(this, SLOT(Main_MENU()));
    pushButton_sortir->enable(this, SLOT(sortir()));
    pushButton_annuler->enable(this, SLOT(Main_MENU()));
    pushButton_selectionner_image->enable(this,
                                          SLOT(selectionner_image_produit
                                               ()));
    pushButton_INSERER->enable(this, SLOT(handle_enregistrer()));
}


void YerithEntrerWindow::definirMagasinier()
{
    _logger->log("definirMagasinier - definirPasDeRole()");

    definirPasDeRole();
}


void YerithEntrerWindow::ON_action_START_YR_QVGE_dynamic_analysis_tool()
{
    _allWindows->_adminWindow->START_YRI_DB_RUNTIME_VERIF_GUI();
}


void YerithEntrerWindow::
        handle_comboBox_unite_de_mesure_changement(int currentUniteDeMesure_Index)
{
    if (currentUniteDeMesure_Index > 0)
    {
        //SET the unit price per unit of measure
        set_PRIX_DE_VENTE_par_Unite_combobBOXLABEL();
    }
    else
    {
        //SET the unit price for all quantities
        set_PRIX_DE_VENTE_combobBOXLABEL();
    }

    calculate_and_display_ALL_benefit_buying_price_percentage();
}


bool YerithEntrerWindow::CHECK_DESCRIPTION_TEXT_SIZE()
{
    int textEdit_description_Size = textEdit_description->toPlainText().size();

    if (textEdit_description_Size >=
            YerithEntrerWindow::CURRENT_MAX_DESCRIPTION_TEXT_SIZE_CHARACTER_NUMBER)
    {
        YerithQMessageBox::warning(this,
                                   QObject::tr("NOMBRE DE CARACTÈRES DE LA DESCRIPTION"),
                                   QObject::tr("Le nombre de caractères (%1) de la description est\n"
                                               "supérieur au maximum de caractères autorisé (%2) !")
                                        .arg(QString::number(textEdit_description_Size),
                                             QString::number(YerithEntrerWindow::CURRENT_MAX_DESCRIPTION_TEXT_SIZE_CHARACTER_NUMBER)));

        return false;
    }

    return true;
}


void YerithEntrerWindow::handle_Edit_ReferenceDesignation()
{
    if (checkBox_EXACT_Reference_value_AS_DESIGNATION->isChecked())
    {
        if (!lineEdit_designation->isEmpty())
        {
            comboBox_reference_produit
                ->find_AND_SET_CURRENT_INDEX(lineEdit_designation->text());
        }
    }
}


void YerithEntrerWindow::handle_Set_YerithEnabled_ComboBox_Reference_Produit(bool enabled)
{
    if (!_INSIDE___handle_ReferenceDesignation_checkBox)
    {
        // Checkbox MUST be opposite of QComboBox SET_YERITH_ENABLED boolean value set.
        checkBox_EXACT_Reference_value_AS_DESIGNATION->setChecked(!enabled);
    }
}


/**
 * Qt framework shall already call this SLOT method automically using
 * a semaphore or something similar; SO WE DON'T NEED IT !
 */
void YerithEntrerWindow::handle_ReferenceDesignation_checkBox(int aState)
{
    _INSIDE___handle_ReferenceDesignation_checkBox = true;

    if (!checkBox_EXACT_Reference_value_AS_DESIGNATION->isChecked())
    {
        comboBox_reference_produit->setYerithEnabled(true);
        //comboBox_reference_produit->resetYerithComboBox();
    }
    else
    {
        if (!lineEdit_designation->isEmpty())
        {
            comboBox_reference_produit
                ->set_text_AT_current_index(lineEdit_designation->text());
        }
        comboBox_reference_produit->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    }

    _INSIDE___handle_ReferenceDesignation_checkBox = false;
}


void YerithEntrerWindow::handle_enregistrer()
{
    if (radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
        executer_enregistrer_une_IMMOBILISATION();
    }
    else if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
    	enregistrer_une_charge_financiere();
    }
    else
    {
        enregistrer_produit();
    }
}


bool YerithEntrerWindow::product_search_with_designation()
{
    YerithSqlTableModel &productListSqlTableModel =
                    _allWindows->getSqlTableModel_marchandises();

    QString productName(lineEdit_designation->text());

    int productNameRowCount =
                    productListSqlTableModel.
                    Is_SearchQSqlTable(YerithDatabaseTableColumn::DESIGNATION, productName);

    if (!productName.isEmpty() && 1 == productNameRowCount)
    {
        QString
        strQuery(QString("select * from %1 where %2='%3' AND %4='%5'").arg
                 (productListSqlTableModel.sqlTableName(),
                  YerithDatabaseTableColumn::IS_SERVICE,
                  YerithUtils::MYSQL_FALSE_LITERAL,
                  YerithDatabaseTableColumn::DESIGNATION, productName));

        QSqlQuery query;

        query.prepare(strQuery);

        bool success = query.exec();

        if (success && query.last())
        {
            int reference_Found_IDX =
                comboBox_reference_produit
                    ->findText(query.value(YerithDatabaseTableColumn::REFERENCE).toString());

            comboBox_reference_produit->setCurrentIndex(reference_Found_IDX);

            comboBox_nom_departement_produit->setCurrentIndex
            (comboBox_nom_departement_produit->findText
             (query.value
              (YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT).
              toString()));

            comboBox_categorie_produit->setCurrentIndex
            (comboBox_categorie_produit->findText
             (query.value(YerithDatabaseTableColumn::CATEGORIE).
              toString()));

            textEdit_description->setText(query.value
                                          (YerithDatabaseTableColumn::
                                           DESCRIPTION_PRODUIT).toString());

            return true;
        }
    }

    return false;
}


bool YerithEntrerWindow::product_search_with_reference()
{
    /*
    * This is a case where MANUAL ENTRY is PERFORMED, and
    * no automatic User manipulation should occur !
    */
    if (!lineEdit_designation->isEmpty())
    {
//        QDEBUG_STRING_OUTPUT_1("*** Manual entry 1.");
        return true;
    }


    YerithSqlTableModel &productListSqlTableModel =
                            _allWindows->getSqlTableModel_marchandises();


    QString aCodebar = comboBox_reference_produit->currentText();


    int codebarRowCount = productListSqlTableModel
                            .Is_SearchQSqlTable(YerithDatabaseTableColumn::REFERENCE,
                                                aCodebar);


    if (!aCodebar.isEmpty() && 1 == codebarRowCount)
    {
        QString strQuery = QString("select * from %1 where %2='%3' AND %4='%5'")
                            .arg(productListSqlTableModel.sqlTableName(),
                                 YerithDatabaseTableColumn::IS_SERVICE,
                                 YerithUtils::MYSQL_FALSE_LITERAL,
                                 YerithDatabaseTableColumn::REFERENCE, aCodebar);

        QSqlQuery query;

        query.prepare(strQuery);


        bool success = query.exec();

        if (success && query.last())
        {
            lineEdit_designation->setText(query.
                                          value(YerithDatabaseTableColumn::
                                                DESIGNATION).toString());


            comboBox_nom_departement_produit->setCurrentIndex
            (comboBox_nom_departement_produit->findText
             (query.value
              (YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT).
              toString()));


            comboBox_categorie_produit->setCurrentIndex
            (comboBox_categorie_produit->findText
             (query.value(YerithDatabaseTableColumn::CATEGORIE).
              toString()));


            textEdit_description->setText(query.value
                                          (YerithDatabaseTableColumn::
                                           DESCRIPTION_PRODUIT).toString());

            return true;
        }
    }

    return false;
}


int YerithEntrerWindow::get_unite_de_mesure_de_vente()
{
    enum YerithUtils::UNITES_DE_MESURES ret_unit_of_measure_value =
            YerithUtils::UNITE_DE_MESURE_INDEFINIE;


    if (YerithUtils::isEqualCaseInsensitive(comboBox_UNITE_DE_Mesure->currentText(),
                                            QObject::tr("Kg")))
    {
        ret_unit_of_measure_value = YerithUtils::UNITE_DE_MESURE_kiloGRAMME;
    }
    else if (YerithUtils::isEqualCaseInsensitive(comboBox_UNITE_DE_Mesure->currentText(),
                                                 QObject::tr("g")))
    {
        ret_unit_of_measure_value = YerithUtils::UNITE_DE_MESURE_GRAMME;
    }
    else if (YerithUtils::isEqualCaseInsensitive(comboBox_UNITE_DE_Mesure->currentText(),
                                                 QObject::tr("l")))
    {
        ret_unit_of_measure_value = YerithUtils::UNITE_DE_MESURE_LITRE;
    }
    else if (YerithUtils::isEqualCaseInsensitive(comboBox_UNITE_DE_Mesure->currentText(),
                                                 QObject::tr("m")))
    {
        ret_unit_of_measure_value = YerithUtils::UNITE_DE_MESURE_METRE;
    }

    return ret_unit_of_measure_value;
}


double YerithEntrerWindow::calculer_prix_dachat_au_GRAMME()
{
    double yri_new_PRIX_Vente = lineEdit_prix_vente->text().toDouble();

    double yri_new_PRIX_DACHAT = yri_new_PRIX_Vente;

    if (is_PRIX_per_unit_of_measure_SET())
    {
        if (comboBox_UNITE_DE_Mesure
                ->current_text_EQUALS_case_insensitive
                (YerithUtils::_mesureuniteToUserViewString
                 .value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
        {
            double a_quantite_toTALE = lineEdit_quantite_totale->text().toDouble();

            double yri_new_PRIX_DACHAT_KG = lineEdit_prix_dachat->text().toDouble();

            double yri_new_PRIX_DACHAT_au_Kg = yri_new_PRIX_DACHAT_KG / 1000.0;

            if (a_quantite_toTALE > 0)
            {
                yri_new_PRIX_DACHAT = yri_new_PRIX_DACHAT_au_Kg / a_quantite_toTALE;
            }

//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculer_prix_dachat_au_GRAMME",
//                                   QString("lineEdit_prix_dachat:(%1); a_quantite_toTALE:(%2)")
//                                   .arg(lineEdit_prix_dachat->text(),
//                                        QString::number(a_quantite_toTALE)));
//
//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculer_prix_dachat_au_GRAMME",
//                                   QString("yri_new_PRIX_Vente:(%1); yri_new_PRIX_DACHAT_KG:(%2); yri_new_PRIX_DACHAT:(%3); _montantTva:(%4)")
//                                   .arg(QString::number(yri_new_PRIX_Vente),
//                                        QString::number(yri_new_PRIX_DACHAT_KG),
//                                        QString::number(yri_new_PRIX_DACHAT),
//                                        QString::number(_montantTva)));
        }
        else if (comboBox_UNITE_DE_Mesure
                     ->current_text_EQUALS_case_insensitive
                     (YerithUtils::_mesureuniteToUserViewString
                      .value(YerithUtils::UNITE_DE_MESURE_GRAMME)))
        {
            double a_quantite_toTALE = lineEdit_quantite_totale->text().toDouble();

            yri_new_PRIX_DACHAT = lineEdit_prix_dachat->text().toDouble();

            double yri_new_PRIX_DACHAT_au_g = yri_new_PRIX_DACHAT / 1000.0;

            if (a_quantite_toTALE > 0)
            {
                yri_new_PRIX_DACHAT = yri_new_PRIX_DACHAT_au_g / a_quantite_toTALE;
            }

//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculer_prix_dachat_au_GRAMME",
//                                   QString("lineEdit_prix_dachat:(%1); a_quantite_toTALE:(%2)")
//                                   .arg(lineEdit_prix_dachat->text(),
//                                        QString::number(a_quantite_toTALE)));
//
//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculer_prix_dachat_au_GRAMME",
//                                   QString("yri_new_PRIX_Vente:(%1); yri_new_PRIX_DACHAT_au_g:(%2); yri_new_PRIX_DACHAT:(%3); _montantTva:(%4)")
//                                   .arg(QString::number(yri_new_PRIX_Vente),
//                                        QString::number(yri_new_PRIX_DACHAT_au_g),
//                                        QString::number(yri_new_PRIX_DACHAT),
//                                        QString::number(_montantTva)));
        }
    }


    return yri_new_PRIX_DACHAT;
}


void YerithEntrerWindow::display_quantite_totale(const QString &quantite_par_lot)
{
    double qte_lot = quantite_par_lot.toDouble();
    double qte_totale = doubleSpinBox_lots_entrant->valueMultiplyBy(qte_lot);

    lineEdit_quantite_totale->setText(QString::number(qte_totale, 'f', 2));


    handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE
        (checkBox_pourcentage_prix_dachat_prix_de_vente->isChecked());


    handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE_EN_GROS
        (checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->isChecked());


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED() ||
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        double montant_total_vente_ou_achat =
                        qte_totale * lineEdit_prix_vente->text().toDouble();

        lineEdit_service_montant_total_vente->setText(GET_CURRENCY_STRING_NUM
                                                      (montant_total_vente_ou_achat));
    }
}


void YerithEntrerWindow::display_quantite_totale_by_spinbox(double lots)
{
    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED()                                             ||
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        display_service_montant_total_vente();
    }
    else
    {
        if (lots > -1)
        {
            double a_qte_TOTALE = (lots * lineEdit_quantite_par_lot->text().toInt());

            lineEdit_quantite_totale->setText(QString::number(a_qte_TOTALE));
        }
    }
}


void YerithEntrerWindow::display_prix_vente()
{
    if (_lastEditedPrixVente != lineEdit_prix_vente->text())
    {
        return;
    }

    if (checkBox_tva->isChecked())
    {
        double prix_vente = lineEdit_prix_vente->text().toDouble();
        _montantTva = prix_vente * YerithERPConfig::tva_value;
        prix_vente = prix_vente + _montantTva;
        lineEdit_prix_vente->setText(QString::number(prix_vente, 'f', 2));

       //calculate_and_display_ALL_benefit_buying_price_percentage();
    }
}


void YerithEntrerWindow::display_prix_vente_en_gros()
{
    if (_lastEditedPrixVente_en_gros != lineEdit_prix_vente_en_gros->text())
    {
        return;
    }

    if (checkBox_tva->isChecked())
    {
        double prix_vente_en_gros =
                    lineEdit_prix_vente_en_gros->text().toDouble();

        _montantTva_en_gros = prix_vente_en_gros * YerithERPConfig::tva_value;

        prix_vente_en_gros = prix_vente_en_gros + _montantTva_en_gros;

        lineEdit_prix_vente_en_gros
            ->setText(QString::number(prix_vente_en_gros, 'f', 2));
    }
}


void YerithEntrerWindow::calculate_and_display_ALL_benefit_buying_price_percentage()
{
    calculate_and_display_benefit_buying_price_percentage();
    calculate_and_display_benefit_buying_price_percentage_EN_GROS();
}


void YerithEntrerWindow::calculate_and_display_benefit_buying_price_percentage()
{
    double qte_totale = lineEdit_quantite_totale->text().toDouble();

    if (0 == qte_totale)
    {
        return ;
    }

    if (!radioButton_service_vente_de_service_au_client->isChecked()  &&
         checkBox_achat->isChecked())
    {
        double prix_dachat = lineEdit_prix_dachat->text().toDouble();

        double prix_vente = lineEdit_prix_vente->text().toDouble();

        QString STRING_pourcentage_benefice_prix_dachat = "0.00";

        if (!checkBox_pourcentage_prix_dachat_prix_de_vente->isChecked())
        {
            double UNITE_prix_dachat = prix_dachat;

            if (is_PRIX_per_unit_of_measure_SET())
            {
                if (comboBox_UNITE_DE_Mesure
                        ->current_text_EQUALS_case_insensitive
                            (YerithUtils::_mesureuniteToUserViewString.value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
                {
                    UNITE_prix_dachat =  prix_dachat / 1000.0;
                }
            }

            prix_vente = prix_vente + _montantTva;

            prix_dachat = UNITE_prix_dachat;


//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculate_and_display_benefit_buying_price_percentage",
//                                   QString("prix_vente:(%1); UNITE_prix_dachat:(%2)")
//                                   .arg(QString::number(prix_vente),
//                                        QString::number(UNITE_prix_dachat)));


            double marginBeneficial = YerithUtils::getMargeBeneficiaire(prix_vente,
                                                                        prix_dachat,
                                                                        _montantTva);

//            QDEBUG_STRING_OUTPUT_2_N("calculate_and_display_benefit_buying_price_percentage -- marginBeneficial",
//                                     marginBeneficial);


            if (YerithUtils::isProfitable(prix_vente,
                                          prix_dachat,
                                          _montantTva))
            {
                lineEdit_pourcentage_prix_dachat_prix_de_vente
                    ->setPalette(YerithUtils::YERITH_DARK_GREEN_PALETTE);

                double pourcentage_benefice_prix_dachat =
                            POURCENTAGE_YERITH_GET_VALUE(YerithUtils::getMargeBeneficiaire(prix_vente,
                                                                                           prix_dachat,
                                                                                           _montantTva),
                                                          prix_dachat);

                STRING_pourcentage_benefice_prix_dachat =
                                QString("%1")
                                    .arg(QString::number(pourcentage_benefice_prix_dachat, 'f', 2));
            }
            else
            {
                set_red_palette(*lineEdit_pourcentage_prix_dachat_prix_de_vente);

                STRING_pourcentage_benefice_prix_dachat = "0.00";
            }

           // lineEdit_prix_vente->setText(QString::number(prix_vente, 'f', 2));

            lineEdit_pourcentage_prix_dachat_prix_de_vente
                ->setText(STRING_pourcentage_benefice_prix_dachat);
        }
        else
        {
            STRING_pourcentage_benefice_prix_dachat =
                            lineEdit_pourcentage_prix_dachat_prix_de_vente->text();

            prix_vente = prix_dachat +
                            (prix_dachat *
                             STRING_pourcentage_benefice_prix_dachat.toDouble() / 100.0);

            prix_vente = prix_vente + _montantTva;

            if (is_PRIX_per_unit_of_measure_SET())
            {
                prix_vente = prix_vente; //qFabs(prix_vente / qte_totale);

                if (comboBox_UNITE_DE_Mesure
                        ->current_text_EQUALS_case_insensitive
                            (YerithUtils::_mesureuniteToUserViewString.value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
                {
                     prix_vente = prix_vente / 1000.0;
                }
            }

            lineEdit_prix_vente->setText(QString::number(prix_vente, 'f', 2));
        }

        lineEdit_pourcentage_prix_dachat_prix_de_vente
            ->setText(STRING_pourcentage_benefice_prix_dachat);
    }
}


void YerithEntrerWindow::calculate_and_display_benefit_buying_price_percentage_EN_GROS()
{
    double qte_totale = lineEdit_quantite_totale->text().toDouble();

    if (0 == qte_totale)
    {
        return ;
    }

    if (radioButton_service_vente_de_service_au_client->isChecked() &&
        checkBox_achat->isChecked())
    {
        double prix_dachat = lineEdit_prix_dachat->text().toDouble();

        double prix_vente_en_gros = get_prix_vente_en_gros();

        QString STRING_pourcentage_benefice_prix_dachat_gros = "0.00";

        if (!checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->isChecked())
        {
            double UNITE_prix_dachat = prix_dachat; //qFabs(prix_dachat / qte_totale);

            if (is_PRIX_per_unit_of_measure_SET())
            {
                if (comboBox_UNITE_DE_Mesure
                        ->current_text_EQUALS_case_insensitive
                            (YerithUtils::_mesureuniteToUserViewString.value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
                {
                      UNITE_prix_dachat =  UNITE_prix_dachat / 1000.0;
                }
            }

            prix_vente_en_gros = prix_vente_en_gros + _montantTva_en_gros;

            prix_dachat = UNITE_prix_dachat;

//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculate_and_display_benefit_buying_price_percentage_EN_GROS",
//                                   QString("prix_vente_en_gros:(%1); UNITE_prix_dachat:(%2)")
//                                   .arg(QString::number(prix_vente_en_gros),
//                                        QString::number(UNITE_prix_dachat)));


            double marginBeneficial_en_gros =
                        YerithUtils::getMargeBeneficiaire(prix_vente_en_gros,
                                                          prix_dachat,
                                                          _montantTva_en_gros);


//            QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::calculate_and_display_benefit_buying_price_percentage_EN_GROS",
//                                   QString("_montantTva_en_gros:(%1); marginBeneficial_en_gros:(%2)")
//                                   .arg(QString::number(_montantTva_en_gros),
//                                        QString::number(marginBeneficial_en_gros)));


            if (YerithUtils::isProfitable(prix_vente_en_gros,
                                          prix_dachat,
                                          _montantTva_en_gros))
            {
                lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros
                    ->setPalette(YerithUtils::YERITH_DARK_GREEN_PALETTE);

                double pourcentage_benefice_prix_dachat_gros =
                         POURCENTAGE_YERITH_GET_VALUE
                                (YerithUtils::getMargeBeneficiaire(prix_vente_en_gros,
                                                                   prix_dachat,
                                                                   _montantTva_en_gros),
                                  prix_dachat);

                STRING_pourcentage_benefice_prix_dachat_gros =
                                QString("%1")
                                    .arg(QString::number(pourcentage_benefice_prix_dachat_gros, 'f', 2));
            }
            else
            {
                set_red_palette(*lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros);

                STRING_pourcentage_benefice_prix_dachat_gros = "0.00";
            }

            lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros
                ->setText(STRING_pourcentage_benefice_prix_dachat_gros);
        }
        else
        {
            STRING_pourcentage_benefice_prix_dachat_gros =
                            lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->text();

            prix_vente_en_gros =
                            prix_dachat +
                            (prix_dachat *
                             STRING_pourcentage_benefice_prix_dachat_gros.toDouble() /
                             100.0);

            prix_vente_en_gros = prix_vente_en_gros + _montantTva_en_gros;

            if (is_PRIX_per_unit_of_measure_SET())
            {
                prix_vente_en_gros = qFabs(prix_vente_en_gros / qte_totale);

                if (comboBox_UNITE_DE_Mesure
                        ->current_text_EQUALS_case_insensitive
                            (YerithUtils::_mesureuniteToUserViewString.value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
                {
                     prix_vente_en_gros = prix_vente_en_gros / 1000.0;
                }

//                QDEBUG_STRING_OUTPUT_2_N("prix_vente_en_gros per UNIT --- calculate_and_display_benefit_buying_price_percentage",
//                                         prix_vente_en_gros);
            }

            lineEdit_prix_vente_en_gros
                ->setText(QString::number(prix_vente_en_gros, 'f', 2));
        }

        lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros
            ->setText(STRING_pourcentage_benefice_prix_dachat_gros);
    }
}


void YerithEntrerWindow::edited_prix_vente(const QString &newPrixVente)
{
    _lastEditedPrixVente = newPrixVente;

    calculate_and_display_benefit_buying_price_percentage();
}


void YerithEntrerWindow::edited_prix_vente_en_gros(const QString &newPrixVente_En_Gros)
{
    _lastEditedPrixVente_en_gros = newPrixVente_En_Gros;

    calculate_and_display_benefit_buying_price_percentage_EN_GROS();
}


void YerithEntrerWindow::edited_pourcentage_prix_dachat_prix_de_vente
                                (const QString &new_pourcentage_prix_dachat_prix_de_vente)
{
    double qte_totale = lineEdit_quantite_totale->text().toDouble();

    if (0 == qte_totale)
    {
        return ;
    }

    if (!radioButton_service_vente_de_service_au_client->isChecked() &&
         checkBox_achat->isChecked())
    {
        double prix_dachat = lineEdit_prix_dachat->text().toDouble();

        double DOUBLE_new_pourcentage_prix_dachat_prix_de_vente =
                        new_pourcentage_prix_dachat_prix_de_vente.toDouble();

        double prix_vente =
                        prix_dachat * (1 +
                                       (DOUBLE_new_pourcentage_prix_dachat_prix_de_vente / 100.0));

        if (checkBox_tva->isChecked())
        {
            _montantTva = prix_vente * YerithERPConfig::tva_value;
        }
        else
        {
            _montantTva = 0;
        }


        prix_vente = prix_vente + _montantTva;


        //QDEBUG_STRING_OUTPUT_2_N("_montantTva", _montantTva);
        //QDEBUG_STRING_OUTPUT_2_N("DOUBLE_new_pourcentage_prix_dachat_prix_de_vente", DOUBLE_new_pourcentage_prix_dachat_prix_de_vente);
        //QDEBUG_STRING_OUTPUT_2_N("prix_dachat", prix_dachat);
        //QDEBUG_STRING_OUTPUT_2_N("prix_vente", prix_vente);

        if (YerithUtils::isProfitable(prix_vente,
                                      prix_dachat,
                                      _montantTva))
        {
            lineEdit_pourcentage_prix_dachat_prix_de_vente
                ->setPalette(YerithUtils::YERITH_DARK_GREEN_PALETTE);

            if (is_PRIX_per_unit_of_measure_SET())
            {
                prix_vente = qFabs(prix_vente / qte_totale);

                if (comboBox_UNITE_DE_Mesure
                        ->current_text_EQUALS_case_insensitive
                            (YerithUtils::_mesureuniteToUserViewString.value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
                {
                     prix_vente = (prix_vente / 1000.0);
                }

//                QDEBUG_STRING_OUTPUT_2_N("prix_vente (TTC) per UNIT",
//                                          prix_vente);
            }

            lineEdit_prix_vente
                ->setText(QString("%1")
                            .arg(QString::number(prix_vente, 'f', 2)));
        }
        else
        {
            set_red_palette(*lineEdit_pourcentage_prix_dachat_prix_de_vente);

            lineEdit_prix_vente->setText("0");
        }
    }
}


void YerithEntrerWindow::edited_pourcentage_prix_dachat_prix_de_vente_EN_GROS
                                (const QString &new_pourcentage_prix_dachat_prix_de_vente_EN_GROS)
{
    double qte_totale = lineEdit_quantite_totale->text().toDouble();

    if (0 == qte_totale)
    {
        return ;
    }

    if (!radioButton_service_vente_de_service_au_client->isChecked() &&
         checkBox_achat->isChecked())
    {
        double prix_dachat = lineEdit_prix_dachat->text().toDouble();

        double DOUBLE_new_pourcentage_prix_dachat_prix_de_vente_EN_GROS =
                    new_pourcentage_prix_dachat_prix_de_vente_EN_GROS.toDouble();

        double prix_vente_en_gros =
                    prix_dachat * (1 + (DOUBLE_new_pourcentage_prix_dachat_prix_de_vente_EN_GROS / 100.0));


        if (checkBox_tva->isChecked())
        {
            _montantTva_en_gros = prix_vente_en_gros * YerithERPConfig::tva_value;
        }
        else
        {
            _montantTva_en_gros = 0;
        }


        prix_vente_en_gros = prix_vente_en_gros + _montantTva_en_gros;


        if (YerithUtils::isProfitable(prix_vente_en_gros,
                                      prix_dachat,
                                      _montantTva_en_gros))
        {
            lineEdit_pourcentage_prix_dachat_prix_de_vente
                ->setPalette(YerithUtils::YERITH_DARK_GREEN_PALETTE);

            if (is_PRIX_per_unit_of_measure_SET())
            {
                prix_vente_en_gros = qFabs(prix_vente_en_gros / qte_totale);

                if (comboBox_UNITE_DE_Mesure
                        ->current_text_EQUALS_case_insensitive
                            (YerithUtils::_mesureuniteToUserViewString.value(YerithUtils::UNITE_DE_MESURE_kiloGRAMME)))
                {
                    prix_vente_en_gros = (prix_vente_en_gros / 1000.0);
                }

//                QDEBUG_STRING_OUTPUT_2_N("prix_vente_en_gros per UNIT",
//                                         prix_vente_en_gros);
            }

            lineEdit_prix_vente_en_gros
                ->setText(QString("%1")
                            .arg(QString::number(prix_vente_en_gros, 'f', 2)));
        }
        else
        {
            set_red_palette(*lineEdit_pourcentage_prix_dachat_prix_de_vente);

            lineEdit_prix_vente_en_gros->setText("0");
        }
    }
}


void YerithEntrerWindow::display_service_montant_total_vente()
{
    double prix_vente = lineEdit_prix_vente->text().toDouble();

    double qte_totale = lineEdit_quantite_totale->text().toDouble();


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED() ||
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        double doubleSpinBox_lots_entrant_QTE = doubleSpinBox_lots_entrant->value();

        double total = doubleSpinBox_lots_entrant_QTE * prix_vente;

        lineEdit_service_montant_total_vente
            ->setText(GET_CURRENCY_STRING_NUM(total));
    }
    else
    {
        if (! _INSIDE___handleTVACheckBox)
        {
            calculate_and_display_benefit_buying_price_percentage();
        }
    }
}


void YerithEntrerWindow::setStockSpecificWidgetVisible(bool visible)
{
    if (visible)
    {
        checkBox_HISTORIQUE->setVisible(true);

        doubleSpinBox_lots_entrant->setMinimum(1.0);

        doubleSpinBox_lots_entrant->setFixedWidth(52);

        doubleSpinBox_lots_entrant->setDecimals(0);

        lineEdit_quantite_par_lot->clear();

        lineEdit_prix_vente->setFixedWidth(88);

        lineEdit_quantite_totale->setFixedWidth(104);
    }
    else
    {
        checkBox_HISTORIQUE->setVisible(false);

        doubleSpinBox_lots_entrant->setMinimum(0.0);

        doubleSpinBox_lots_entrant->setFixedWidth(205);

        doubleSpinBox_lots_entrant->setDecimals(2);

        lineEdit_quantite_par_lot->setText("1");

        lineEdit_prix_vente->setFixedWidth(205);

        lineEdit_quantite_totale->setFixedWidth(205);

        if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED()                                            ||
            Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
        {
            doubleSpinBox_lots_entrant->setValue(0.0);
        }
        else
        {
            doubleSpinBox_lots_entrant->setValue(1.0);
        }
    }


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
        checkBox_tva->setVisible(false);
        lineEdit_tva->setVisible(false);
    }
    else
    {
        checkBox_tva->setVisible(true);
        lineEdit_tva->setVisible(true);
    }


    comboBox_UNITE_DE_Mesure->setVisible(visible);

    label_description->setVisible(visible);

    textEdit_description->setVisible(visible);

    label_quantite->setVisible(visible);

    label_quantite_totale->setVisible(visible);

    lineEdit_quantite_totale->setVisible(visible);

    lineEdit_quantite_par_lot->setVisible(visible);

    pushButton_selectionner_image->setVisible(visible);

    pushButton_supprimer_limage_du_stock->setVisible(visible);

    groupBox_image_du_stock_service->setVisible(visible);

    label_reference_recu_dachat->setVisible(visible);
    lineEdit_reference_recu_dachat->setVisible(visible);

    label_stock_dalerte->setVisible(visible);
    lineEdit_stock_dalerte->setVisible(visible);

    label_localisation_du_stock->setVisible(visible);
    comboBox_localisation_produit->setVisible(visible);

    checkBox_date_peremption->setChecked(visible);

    dateEdit_date_peremption->setVisible(visible);
    checkBox_date_peremption->setVisible(visible);


    /*
     * '*_montant_total_vente_service' et
     * '*_prix_dachat' sont justaposes dans
     * l'interface utilisateur.
     *
     * Donc ils ne peuvent jamais etre visible
     * au meme moment.
     */
    label_montant_total_vente_service->setVisible(!visible);
    lineEdit_service_montant_total_vente->setVisible(!visible);

    comboBox_label_prix_vente_en_gros->setVisible(visible);
    lineEdit_prix_vente_en_gros->setVisible(visible);

    label_prix_dachat->setVisible(visible);
    lineEdit_prix_dachat->setVisible(visible);

    label_POURCENTAGE_1->setVisible(visible);
    label_POURCENTAGE_2->setVisible(visible);

    lineEdit_pourcentage_prix_dachat_prix_de_vente->setVisible(visible);
    lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(visible);


    checkBox_achat->setVisible(visible);
}


QString YerithEntrerWindow::
            Get_intitule_du_compte_bancaire__FROM__BUDGET_LINE_table(QString a_current_BUDGET_Line_INTITULE)
{
    QString a_current_bank_account_TITLE;

    QSqlRecord aBUDGETLINE_QSql_RECORD;

    YerithSqlTableModel &aBUDGETLINE_SqlTableModel = _allWindows->getSqlTableModel_lignes_budgetaires();

    aBUDGETLINE_SqlTableModel.yerithSetFilter_WITH_where_clause
        (YerithUtils::generateSqlIs(YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire,
                                    a_current_BUDGET_Line_INTITULE));

    int rowCount_result = aBUDGETLINE_SqlTableModel.easySelect();

    if (rowCount_result > 0)
    {
        aBUDGETLINE_QSql_RECORD = aBUDGETLINE_SqlTableModel.record(0);

        a_current_bank_account_TITLE =
            GET_SQL_RECORD_DATA(aBUDGETLINE_QSql_RECORD,
                                YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE);
    }

    return a_current_bank_account_TITLE;
}


void YerithEntrerWindow::Switch__label__SUPPLIER_fournisseur_banque_institution(bool client_text /* = false */)
{
    if (!client_text)
    {
        if (false)
        {
//            QDEBUG_STRING_OUTPUT_1("Switch__label__SUPPLIER_fournisseur_banque_institution - banque_INSTITUTION");

            POPULATE_banking_accounts__For__ONLY_budget_LINES_accounts();

            if (YerithMainWindow::LANGUE_ANGLAISE)
            {
                label_fournisseur->setText("BANK - Institution");
            }
            else
            {
                label_fournisseur->setText("Banque - Institution");
            }

            label_fournisseur->setPalette(YerithUtils::YERITH_RED_PALETTE);

            label_fournisseur->setForegroundRole(QPalette::Window);
        }
        else
        {
//            QDEBUG_STRING_OUTPUT_1("Switch__label__SUPPLIER_fournisseur_banque_institution - Fournisseur");

            comboBox_nom_entreprise_fournisseur
                ->populateComboBoxRawString(YerithDatabase::FOURNISSEURS,
                                            YerithDatabaseTableColumn::NOM_ENTREPRISE);

            if (YerithMainWindow::LANGUE_ANGLAISE)
            {
                label_fournisseur->setText("Supplier");
            }
            else
            {
                label_fournisseur->setText("Fournisseur");
            }

            label_fournisseur->setPalette(label_designation->palette());

            label_fournisseur->setForegroundRole(QPalette::WindowText);
        }
    }
    else
    {
        comboBox_nom_entreprise_fournisseur
            ->populateComboBoxRawString(YerithDatabase::CLIENTS,
                                        YerithDatabaseTableColumn::NOM_ENTREPRISE);

        label_fournisseur->setText(QObject::tr("client"));

        label_fournisseur->setPalette(label_designation->palette());

        label_fournisseur->setForegroundRole(QPalette::WindowText);
    }
}


bool YerithEntrerWindow::ON_______Show_all_RadioButton()
{
    if (! _a_show_ITEM)
    {
        radioButton_inserer_une_IMMOBILISATION->setVisible(true);
        radioButton_inserer_un_stock->setVisible(true);
        radioButton_INSERER_UNE_CHARGE_FINANCIERE->setVisible(true);
        radioButton_service_vente_de_service_au_client->setVisible(true);
    }

    HANDLE_Combobox_unite_de_Mesure();

    return true;
}


bool YerithEntrerWindow::ON_______HIDE_all_other_choices_RadioButton()
{
    if (! _a_show_ITEM)
    {
        if (radioButton_inserer_une_IMMOBILISATION->isChecked())
        {
            radioButton_inserer_un_stock->setVisible(false);
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->setVisible(false);
            radioButton_service_vente_de_service_au_client->setVisible(false);
        }
        else if (radioButton_inserer_un_stock->isChecked())
        {
            radioButton_inserer_une_IMMOBILISATION->setVisible(false);
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->setVisible(false);
            radioButton_service_vente_de_service_au_client->setVisible(false);
        }
        else if (radioButton_INSERER_UNE_CHARGE_FINANCIERE->isChecked())
        {
            radioButton_inserer_une_IMMOBILISATION->setVisible(false);
            radioButton_inserer_un_stock->setVisible(false);
            radioButton_service_vente_de_service_au_client->setVisible(false);
        }
        else if (radioButton_service_vente_de_service_au_client->isChecked())
        {
            radioButton_inserer_une_IMMOBILISATION->setVisible(false);
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->setVisible(false);
            radioButton_inserer_un_stock->setVisible(false);
        }
    }

    HANDLE_Combobox_unite_de_Mesure();

    return true;
}


void YerithEntrerWindow::Handle___Departement_de_produits___Via___RADIOBUTTONS()
{
    if (radioButton_inserer_une_IMMOBILISATION->isChecked()     ||
        radioButton_inserer_un_stock->isChecked())
    {
        yri___POPULATE_COMBOX_BOX_RAW_STRING_Physical_STOCK_ASSET_DEPARTMENT(*comboBox_nom_departement_produit);

        label_nom_departement_produit->setText(QObject::tr("département produit"));
    }
    else
    {
        yri___POPULATE_COMBOX_BOX_RAW_STRING_NON_PHYSICAL_STOCK_ASSET_DEPARTMENT(*comboBox_nom_departement_produit);

        label_nom_departement_produit->setText(QObject::tr("département"));

        if (radioButton_service_vente_de_service_au_client->isChecked() ||
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->isChecked())
        {
            comboBox_nom_departement_produit->checkField();
        }
    }
}


void YerithEntrerWindow::handle_checkBox_INSERT_ASSET(bool checked)
{
    radioButton_inserer_une_IMMOBILISATION->setChecked(checked);

    if (radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
    	comboBox_categorie_produit->clear();

        radioButton_inserer_une_IMMOBILISATION->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);
        radioButton_inserer_une_IMMOBILISATION->
                setStyleSheet(QString
                              ("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_inserer_un_stock->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);
        radioButton_inserer_un_stock->
                setStyleSheet(QString
                              ("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_INSERER_UNE_CHARGE_FINANCIERE->setPalette(YerithUtils::YERITH_BLUE_PALETTE);
        radioButton_INSERER_UNE_CHARGE_FINANCIERE->
                setStyleSheet(QString
                              ("color: rgb(0, 0, 255);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_service_vente_de_service_au_client->setPalette(YerithUtils::YERITH_YERITH_GOLD_PALETTE);
        radioButton_service_vente_de_service_au_client->setStyleSheet(QString
                                                                      ("color: rgb(245, 194, 17);  border: 0px solid rgb(60, 60, 60);"));
    }
    else
    {
        radioButton_inserer_une_IMMOBILISATION->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);
        radioButton_inserer_une_IMMOBILISATION->
            setStyleSheet(QString("color: rgb(243, 162, 0); border: 0px solid rgb(60, 60, 60);"));
    }

    radioButton_inserer_une_IMMOBILISATION->update();
    radioButton_inserer_un_stock->update();
    radioButton_INSERER_UNE_CHARGE_FINANCIERE->update();
    radioButton_service_vente_de_service_au_client->update();


    if (radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
        label_localisation_du_stock->setText(QObject::tr
                                             ("localisation immobilisation"));

        Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(false);

        comboBox_label_prix_vente->setVisible(false);
        comboBox_label_prix_vente_en_gros->setVisible(false);

        lineEdit_prix_vente->setVisible(false);
        lineEdit_prix_vente_en_gros->setVisible(false);

        checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
        checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);
        checkBox_tva->setVisible(false);
        lineEdit_tva->setVisible(false);
    }
    else
    {
        label_localisation_du_stock->setText(QObject::tr("localisation STOCK"));

        checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(true);
        checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(true);
        checkBox_tva->setVisible(true);
        lineEdit_tva->setVisible(true);
    }


    Handle___Departement_de_produits___Via___RADIOBUTTONS();


    set_achat_checkBox_elements_visibility();


    ON_______HIDE_all_other_choices_RadioButton();

//TODO.
//    Q_ASSERT_X(is_selection_rendering_VALID___ASSET(),
//               "YerithEntrerWindow::handle_checkBox_INSERT_ASSET(bool)",
//               "ERROR when selecting asset insertion radiobutton");
}


void YerithEntrerWindow::handle_checkBox_INSERT_STOCK(bool checked)
{
    radioButton_inserer_un_stock->setChecked(checked);

    if (radioButton_inserer_un_stock->isChecked())
    {
    	comboBox_categorie_produit->clear();

        radioButton_inserer_un_stock->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);
        radioButton_inserer_un_stock->
        setStyleSheet(QString
                      ("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_inserer_une_IMMOBILISATION->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);
        radioButton_inserer_une_IMMOBILISATION->
                setStyleSheet(QString
                              ("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_INSERER_UNE_CHARGE_FINANCIERE->setPalette(YerithUtils::YERITH_BLUE_PALETTE);
        radioButton_INSERER_UNE_CHARGE_FINANCIERE->
                setStyleSheet(QString
                              ("color: rgb(0, 0, 255);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_service_vente_de_service_au_client->setPalette(YerithUtils::YERITH_YERITH_GOLD_PALETTE);
        radioButton_service_vente_de_service_au_client->setStyleSheet(QString
                                                                      ("color: rgb(245, 194, 17);  border: 0px solid rgb(60, 60, 60);"));
    }
    else
    {
        radioButton_inserer_un_stock->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);
        radioButton_inserer_un_stock->
                setStyleSheet(QString
                              ("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));
    }

    radioButton_inserer_une_IMMOBILISATION->update();
    radioButton_inserer_un_stock->update();
    radioButton_INSERER_UNE_CHARGE_FINANCIERE->update();
    radioButton_service_vente_de_service_au_client->update();


    if (radioButton_inserer_un_stock->isChecked())
    {
        label_localisation_du_stock->setText(QObject::tr("localisation STOCK"));

        Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(false);

        comboBox_label_prix_vente->setVisible(true);
        comboBox_label_prix_vente_en_gros->setVisible(true);

        lineEdit_prix_vente->setVisible(true);
        lineEdit_prix_vente_en_gros->setVisible(true);

        checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(true);
        checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(true);
        checkBox_tva->setVisible(true);
        lineEdit_tva->setVisible(true);
    }
    else
    {
        label_localisation_du_stock->setText(QObject::tr("localisation immobilisation"));

        checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
        checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);
        checkBox_tva->setVisible(false);
        lineEdit_tva->setVisible(false);
    }


    Handle___Departement_de_produits___Via___RADIOBUTTONS();


    set_achat_checkBox_elements_visibility();


    ON_______HIDE_all_other_choices_RadioButton();

//TODO.
//    Q_ASSERT_X(is_selection_rendering_VALID___STOCK(),
//               "YerithEntrerWindow::handle_checkBox_INSERT_STOCK(bool)",
//               "ERROR when selecting Stock insertion radiobutton");
}


void YerithEntrerWindow::handle_checkBox_INSERER_UNE_CHARGE_FINANCIERE(bool checked)
{
    radioButton_INSERER_UNE_CHARGE_FINANCIERE->setChecked(checked);

    radioButton_INSERER_UNE_CHARGE_FINANCIERE->setPalette(YerithUtils::YERITH_BLUE_PALETTE);

    radioButton_INSERER_UNE_CHARGE_FINANCIERE
    ->setStyleSheet(QString("color: rgb(0, 0, 255);  border: 0px solid rgb(60, 60, 60);"));


    Switch__label__SUPPLIER_fournisseur_banque_institution();


    comboBox_categorie_produit->setYerithEditable(true);


    if (!radioButton_INSERER_UNE_CHARGE_FINANCIERE->isChecked())
    {
    	comboBox_categorie_produit->setYerithEditable(true);

        radioButton_INSERER_UNE_CHARGE_FINANCIERE
            ->setPalette(YerithUtils::YERITH_BLUE_PALETTE);

        radioButton_INSERER_UNE_CHARGE_FINANCIERE
            ->setStyleSheet(QString("color: rgb(0, 0, 255);  border: 0px solid rgb(60, 60, 60);"));
    }


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
    	comboBox_categorie_produit
			->populateComboBoxRawString(YerithDatabase::LIGNES_BUDGETAIRES,
                                                    YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire);

    	comboBox_categorie_produit->setYerithEditable(false);

        radioButton_inserer_une_IMMOBILISATION
            ->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);

        radioButton_inserer_une_IMMOBILISATION
            ->setStyleSheet(QString("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_inserer_un_stock
            ->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);

        radioButton_inserer_un_stock
            ->setStyleSheet(QString("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_service_vente_de_service_au_client
            ->setPalette(YerithUtils::YERITH_YERITH_GOLD_PALETTE);

        radioButton_service_vente_de_service_au_client
            ->setStyleSheet(QString("color: rgb(245, 194, 17);  border: 0px solid rgb(60, 60, 60);"));
    }


    radioButton_inserer_une_IMMOBILISATION->update();
    radioButton_inserer_un_stock->update();
    radioButton_INSERER_UNE_CHARGE_FINANCIERE->update();
    radioButton_service_vente_de_service_au_client->update();


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
        setStockSpecificWidgetVisible(false);

        check_fields_service_vente();
    }
    else
    {
        setStockSpecificWidgetVisible(true);

        check_fields(true);
    }


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
    	label_categorie->setText(QObject::tr("LIGNE BUDGÉTAIRE"));
    }
    else
    {
    	label_categorie->setText(QObject::tr("catégorie"));
    }


    setupLineEditsQCompleters__FOR_STOCK_INVENTORY();


    Handle___Departement_de_produits___Via___RADIOBUTTONS();


    ON_______HIDE_all_other_choices_RadioButton();
}


void YerithEntrerWindow::handle_checkBox_service_vente(bool checked)
{
    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
    	comboBox_categorie_produit->clear();

        radioButton_service_vente_de_service_au_client->setPalette(YerithUtils::YERITH_YERITH_GOLD_PALETTE);

        radioButton_service_vente_de_service_au_client
            ->setStyleSheet(QString("color: rgb(245, 194, 17);  border: 0px solid rgb(60, 60, 60);"));


        radioButton_inserer_une_IMMOBILISATION->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);

        radioButton_inserer_une_IMMOBILISATION
            ->setStyleSheet(QString("color: rgb(243, 162, 0);  border: 0px solid rgb(60, 60, 60);"));

        radioButton_inserer_un_stock->setPalette(YerithUtils::YERITH_ORANGE_PALETTE);

        radioButton_inserer_un_stock
            ->setStyleSheet(QString("color: rgb(243, 162, 0); border: 0px solid rgb(60, 60, 60);"));


        radioButton_INSERER_UNE_CHARGE_FINANCIERE->setPalette(YerithUtils::YERITH_BLUE_PALETTE);

        radioButton_INSERER_UNE_CHARGE_FINANCIERE
            ->setStyleSheet(QString("color: rgb(0, 0, 255);  border: 0px solid rgb(60, 60, 60);"));
    }
    else
    {
        radioButton_service_vente_de_service_au_client->setPalette(YerithUtils::YERITH_YERITH_GOLD_PALETTE);

        radioButton_service_vente_de_service_au_client
            ->setStyleSheet(QString("color: rgb(245, 194, 17);  border: 0px solid rgb(60, 60, 60);"));
    }

    radioButton_inserer_une_IMMOBILISATION->update();
    radioButton_inserer_un_stock->update();
    radioButton_INSERER_UNE_CHARGE_FINANCIERE->update();
    radioButton_service_vente_de_service_au_client->update();


    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        setStockSpecificWidgetVisible(false);

        check_fields_service_vente();
    }
    else
    {
        setStockSpecificWidgetVisible(true);

        check_fields(true);
    }


    setupLineEditsQCompleters__FOR_STOCK_INVENTORY();

    set_PRIX_DE_VENTE_combobBOXLABEL();


    Handle___Departement_de_produits___Via___RADIOBUTTONS();


    ON_______HIDE_all_other_choices_RadioButton();
}


void YerithEntrerWindow::handleTVACheckBox(int state)
{
    _INSIDE___handleTVACheckBox = true;

    double prix_vente = lineEdit_prix_vente->text().toDouble();

    double prix_vente_en_gros = get_prix_vente_en_gros();

    if (checkBox_tva->isChecked())
    {
        _montantTva = prix_vente * YerithERPConfig::tva_value;

        _montantTva_en_gros = prix_vente_en_gros * YerithERPConfig::tva_value;

        prix_vente = prix_vente + _montantTva;

        prix_vente_en_gros = prix_vente_en_gros + _montantTva_en_gros;

//        QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::handleTVACheckBox; checked",
//                               QString("prix_vente:(%1); prix_vente_en_gros:(%2);"
//                                       "_montantTva:(%3); _montantTva_en_gros(%4)")
//                               .arg(QString::number(prix_vente),
//                                    QString::number(prix_vente_en_gros),
//                                    QString::number(_montantTva),
//                                    QString::number(_montantTva_en_gros)));
    }
    else
    {
        _montantTva = 0;

        _montantTva_en_gros = 0;

        prix_vente = prix_vente / (1 + YerithERPConfig::tva_value);

        prix_vente_en_gros =
                        prix_vente_en_gros / (1 + YerithERPConfig::tva_value);

//        QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::handleTVACheckBox; UNCHECKED",
//                               QString("prix_vente:(%1); prix_vente_en_gros:(%2);"
//                                       "_montantTva:(%3); _montantTva_en_gros(%4)")
//                               .arg(QString::number(prix_vente),
//                                    QString::number(prix_vente_en_gros),
//                                    QString::number(_montantTva),
//                                    QString::number(_montantTva_en_gros)));
    }

    lineEdit_prix_vente->setText(QString::number(prix_vente, 'f', 2));

    lineEdit_prix_vente_en_gros
        ->setText(QString::number(prix_vente_en_gros, 'f', 2));

    _INSIDE___handleTVACheckBox = false;
}


bool YerithEntrerWindow::check_fields_mandatory_buying()
{
    bool prix_dachat = true;

    set_achat_checkBox_elements_visibility();

    if (checkBox_achat->isChecked())
    {
        prix_dachat = lineEdit_prix_dachat->checkField();
    }

    return prix_dachat;
}


void YerithEntrerWindow::set_achat_checkBox_elements_visibility()
{
    if (checkBox_achat->isChecked())
    {
        label_prix_dachat->setVisible(true);

        lineEdit_prix_vente->setFixedWidth(88);
        lineEdit_prix_vente_en_gros->setFixedWidth(88);

        lineEdit_prix_dachat->setVisible(true);

        if (radioButton_inserer_un_stock->isChecked())
        {
            checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(true);
            checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(true);

            label_POURCENTAGE_1->setVisible(true);
            label_POURCENTAGE_2->setVisible(true);

            lineEdit_pourcentage_prix_dachat_prix_de_vente->setVisible(true);
            lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(true);
        }
        else
        {
            checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
            checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);

            lineEdit_prix_vente->setVisible(false);
            lineEdit_prix_vente_en_gros->setVisible(false);

            label_POURCENTAGE_1->setVisible(false);
            label_POURCENTAGE_2->setVisible(false);

            lineEdit_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
            lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);
        }
    }
    else
    {
        label_prix_dachat->setVisible(false);

        lineEdit_prix_vente->setFixedWidth(205);
        lineEdit_prix_vente_en_gros->setFixedWidth(205);

        lineEdit_prix_dachat->setText(YerithUtils::EMPTY_STRING);

        lineEdit_prix_dachat->setVisible(false);

        checkBox_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
        checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);

        label_POURCENTAGE_1->setVisible(false);
        label_POURCENTAGE_2->setVisible(false);

        lineEdit_pourcentage_prix_dachat_prix_de_vente->setVisible(false);
        lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setVisible(false);
    }
}


double YerithEntrerWindow::get_prix_vente_en_gros()
{
    double yri_new_PRIX_Vente_En_Gros = lineEdit_prix_vente->text().toDouble();

//    QDEBUG_STRING_OUTPUT_2("lineEdit_prix_vente_en_gros->isEmpty()",
//                            BOOL_TO_STRING(lineEdit_prix_vente_en_gros->isEmpty()));

    if (!lineEdit_prix_vente_en_gros->isEmpty())
    {

//        QDEBUG_STRING_OUTPUT_2("is_PRIX_per_unit_of_measure_SET()",
//                                BOOL_TO_STRING(is_PRIX_per_unit_of_measure_SET()));

        yri_new_PRIX_Vente_En_Gros = lineEdit_prix_vente_en_gros->text().toDouble();
    }

    return yri_new_PRIX_Vente_En_Gros;
}


void YerithEntrerWindow::showItem(YerithSqlTableModel           *stocks_OR_marchandises_TableModel /* = 0 */,
                                  enum entrer_VISIBLE_CHOICE     choice_insert /* = set_choice_insert_ASSET */)
{
    populateEntrerUnStock_OU_ServiceComboBoxes();

    QString yerithSqlTableModelFilter =
        QString("%1 = '%2'")
            .arg(YerithDatabaseTableColumn::ID,
                 YerithERPWindows::get_last_lister_selected_row_db_ID());


    if (0 == stocks_OR_marchandises_TableModel)
    {
        stocks_OR_marchandises_TableModel = _curStocksTableModel;
    }


    QSqlRecord record;

    stocks_OR_marchandises_TableModel
        ->yerithSetFilter_WITH_where_clause(yerithSqlTableModelFilter);

    record = stocks_OR_marchandises_TableModel->record(0);


    lineEdit_designation->setText(GET_SQL_RECORD_DATA
                                  (record,
                                   YerithDatabaseTableColumn::DESIGNATION));

    textEdit_description->setText(GET_SQL_RECORD_DATA
                                  (record,
                                   YerithDatabaseTableColumn::DESCRIPTION_PRODUIT));


    double prix_vente =
                GET_SQL_RECORD_DATA(record,
                                    YerithDatabaseTableColumn::PRIX_VENTE).toDouble();

    double montant_tva =
                GET_SQL_RECORD_DATA(record,
                                    YerithDatabaseTableColumn::MONTANT_TVA).toDouble();

    double prix_vente_en_gros =
                GET_SQL_RECORD_DATA(record,
                                    YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS).toDouble();

    double montant_tva_en_gros =
                GET_SQL_RECORD_DATA(record,
                                    YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS).toDouble();


    bool is_record_an_asset = YerithUtils::IS_QSQL_RECORD_AN_ASSET(record);

    if (!is_record_an_asset)
    {
        //lineEdit_designation->setReadOnly(true);
    }
    else
    {
        //lineEdit_designation->setReadOnly(false);

        if (&_allWindows->getSqlTableModel_marchandises() == stocks_OR_marchandises_TableModel)
        {
            //lineEdit_designation->setReadOnly(true);
        }
    }


    if (prix_vente <= 0)
    {
        if (set_choice_insert_STANDARD_INVENTORY_STOCK == choice_insert)
        {
            radioButton_inserer_un_stock->setYerithEnabled(true);
            radioButton_inserer_un_stock->setChecked(true);

            radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

            handle_checkBox_INSERT_STOCK(true);
        }
        else if (set_choice_insert_ASSET == choice_insert)
        {
            radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(true);
            radioButton_inserer_une_IMMOBILISATION->setChecked(true);

            radioButton_inserer_un_stock->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

            handle_checkBox_INSERT_ASSET(true);
        }
    }
    else
    {
        radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

        radioButton_inserer_un_stock->setYerithEnabled(true);
        radioButton_inserer_un_stock->setChecked(true);

        handle_checkBox_INSERT_STOCK(false);
    }


    _historique_stock_actif =
                    GET_SQL_RECORD_DATA(record,
                                        YerithDatabaseTableColumn::HISTORIQUE_STOCK_ACTIF).toInt();


    checkBox_HISTORIQUE->setChecked(_historique_stock_actif);


    double prix_dachat = GET_SQL_RECORD_DATA(record,
                                             YerithDatabaseTableColumn::PRIX_DACHAT).toDouble();

    if (prix_dachat > 0)
    {
        lineEdit_prix_dachat->setText(QString::number(prix_dachat));
    }
    else
    {
        lineEdit_prix_dachat->setText(YerithUtils::EMPTY_STRING);
    }


    if (0 < montant_tva || 0 < montant_tva_en_gros)
    {
        checkBox_tva->setChecked(true);
        handleTVACheckBox(true);
    }
    else
    {
        checkBox_tva->setChecked(false);
        handleTVACheckBox(false);
    }

    if (prix_vente > 0)
    {
        lineEdit_prix_vente->setText(QString::number(prix_vente, 'f', 2));
    }
    else
    {
        lineEdit_prix_vente->setText(YerithUtils::EMPTY_STRING);
    }

    if (prix_vente_en_gros > 0)
    {
        lineEdit_prix_vente_en_gros->
        setText(QString::number(prix_vente_en_gros, 'f', 2));
    }
    else
    {
        lineEdit_prix_vente_en_gros->setText(YerithUtils::EMPTY_STRING);
    }


    comboBox_nom_departement_produit
        ->find_AND_SET_CURRENT_INDEX_NOT_EDITABLE
            (GET_SQL_RECORD_DATA(record,
                                 YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT));


    comboBox_categorie_produit
        ->find_AND_SET_CURRENT_INDEX_NOT_EDITABLE
            (GET_SQL_RECORD_DATA(record,
                                 YerithDatabaseTableColumn::CATEGORIE));


    QString reference_produit = GET_SQL_RECORD_DATA(record,
                                                    YerithDatabaseTableColumn::REFERENCE);


    if (!YerithUtils::isEqualCaseInsensitive(YerithUtils::EMPTY_STRING,
                                             reference_produit))
    {
        comboBox_reference_produit->find_AND_SET_CURRENT_INDEX_NOT_EDITABLE(reference_produit);
    }
    else
    {
        comboBox_reference_produit->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    }

    comboBox_localisation_produit->find_AND_SET_CURRENT_INDEX(GET_SQL_RECORD_DATA
                                           (record,
                                            YerithDatabaseTableColumn::LOCALISATION_STOCK));

    QVariant img(record.value(YerithDatabaseTableColumn::IMAGE_PRODUIT));

    if (!img.isNull())
    {
        YerithUtils::loadPixmapFromDB(*label_image_produit, img, "JPG");
    }
    else
    {
        label_image_produit->setAutoFillBackground(false);
    }

    if (YerithUtils::isEqualCaseInsensitive(YerithDatabase::STOCKS,
                                            stocks_OR_marchandises_TableModel->
                                            sqlTableName()))
    {
        QString recordID = YerithERPWindows::get_last_lister_selected_row_db_ID();

        int achatQuerySize =
                        YerithUtils::STOCK_PURCHASE_RECORDS_QUANTITY(recordID);

        if (achatQuerySize > 0)
        {
            checkBox_achat->setChecked(true);
        }
        else
        {
            checkBox_achat->setChecked(false);
        }
    }

    stocks_OR_marchandises_TableModel->resetFilter("src/windows/yerith-erp-entrer-window.cpp");

    lineEdit_quantite_par_lot->setFocus();
}


bool YerithEntrerWindow::check_fields_service_achat()
{
    bool fournisseur = comboBox_nom_entreprise_fournisseur->checkField();

    bool nom_departement_produit =
                    comboBox_nom_departement_produit->checkField();

    bool categorie_produit = comboBox_categorie_produit->checkField();

    bool reference = comboBox_reference_produit->checkField();

    bool quantite = lineEdit_quantite_par_lot->checkField();

    bool prix_vente = lineEdit_prix_vente->checkField();

    bool result = fournisseur               &&
                  nom_departement_produit   &&
                  categorie_produit         &&
                  reference                 &&
                  prix_vente                &&
                  quantite;

    return result;
}


bool YerithEntrerWindow::check_fields_service_vente()
{
    bool designation = lineEdit_designation->checkField();

    bool client_fournisseur =
                    comboBox_nom_entreprise_fournisseur->checkField();

    bool nom_departement_produit =
                    comboBox_nom_departement_produit->checkField();

    bool categorie_produit = comboBox_categorie_produit->checkField();

    bool reference = comboBox_reference_produit->checkField();

    bool quantite = lineEdit_quantite_par_lot->checkField();

    bool prix_vente = lineEdit_prix_vente->checkField();

    bool result = designation               &&
                  client_fournisseur        &&
                  nom_departement_produit   &&
                  categorie_produit         &&
                  reference                 &&
                  prix_vente                &&
                  quantite;

    return result;
}


bool YerithEntrerWindow::check_fields(bool withClearAllServiceMandatoryFields /*  = false */)
{
    if (withClearAllServiceMandatoryFields)
    {
        comboBox_nom_entreprise_fournisseur->resetYerithComboBox();

        comboBox_reference_produit->resetYerithComboBox();
    }

    bool prix_dachat = check_fields_mandatory_buying();

    bool designation = lineEdit_designation->checkField_With_SETTING_COLOR_at_label(label_designation);

    bool quantite_par_lot = lineEdit_quantite_par_lot->checkField();

    if (quantite_par_lot)
    {
        if (lineEdit_quantite_par_lot->text().toDouble() <= 0)
        {
            YerithQMessageBox::information(this,
                                           QObject::tr("enregistrer article"),
                                           QObject::tr("La quantité par lot doit être supérieure à zéro !"));

            lineEdit_quantite_par_lot->clear();

            lineEdit_quantite_par_lot->checkField();

            return false;
        }
    }

    bool nom_departement_produit =
                    comboBox_nom_departement_produit->checkField();

    bool categorie_produit = comboBox_categorie_produit->checkField();


    bool result = false;


    if (radioButton_inserer_un_stock->isChecked())
    {
        bool prix_vente = lineEdit_prix_vente->checkField();

        result = prix_dachat                &&
                 designation                &&
                 nom_departement_produit    &&
                 categorie_produit          &&
                 prix_vente                 &&
                 quantite_par_lot;
    }
    else
    {
        result = prix_dachat                &&
                 designation                &&
                 nom_departement_produit    &&
                 categorie_produit          &&
                 quantite_par_lot;
    }


    return result;
}


void YerithEntrerWindow::clear_all_fields()
{
    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED() ||
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        doubleSpinBox_lots_entrant->setValue(0.0);
    }
    else
    {
        doubleSpinBox_lots_entrant->setValue(1.0);
    }

    lineEdit_designation->clearField();

    comboBox_nom_departement_produit->clearField();
    comboBox_categorie_produit->clearField();
    comboBox_nom_entreprise_fournisseur->clearField();

    lineEdit_pourcentage_prix_dachat_prix_de_vente->clear();
    lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->clear();

    lineEdit_quantite_par_lot->clearField();
    lineEdit_quantite_totale->clear();
    lineEdit_stock_dalerte->clearField();
    lineEdit_reference_recu_dachat->clearField();
    lineEdit_prix_dachat->clearField();
    lineEdit_prix_vente->clearField();
    lineEdit_prix_vente_en_gros->clearField();
    comboBox_localisation_produit->clearField();

    textEdit_description->clear();


    comboBox_UNITE_DE_Mesure->resetYerithComboBox();

    comboBox_reference_produit->clearField();


    label_image_produit->clear();
    label_image_produit->setAutoFillBackground(false);

    checkBox_tva->setChecked(false);

    _lastEditedPrixVente.clear();
    _lastEditedPrixVente_en_gros.clear();

    _montantTva = 0.0;
    _montantTva_en_gros = 0.0;

    _tvaCheckBoxPreviousState = false;


    reset_window_widgets_modification_Bit();
}


void YerithEntrerWindow::Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(bool visible)
{
    lineEdit_prix_vente->setVisible(visible);

    label_prix_vente__TRANSFORME_PRIX_dachat->setVisible(visible);

    if (Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        lineEdit_prix_vente->setVisible(true);
    }
}


void YerithEntrerWindow::rendreInvisible()
{
    if (GET___Succeeded___INSERTION_to_DB_Tables_Bit())
    {
        clear_all_fields();

        dateEdit_date_peremption->reset();


        _a_show_ITEM = false;

        _Last_choice_insert = set_choice_insert_UNDEFINED;

        setVisible(false);
    }
    else
    {
        _Cancel_MODIFICATION_request_Object
            ->set_First__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("VOUS étiez entrain de faire 1 insertion.\n"
                             "Souhaiter vous annuler\n"
                             "ceci en sortant de cette fenêtre du programme ?"));

        _Cancel_MODIFICATION_request_Object
            ->Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE
                (QObject::tr("Vous avez annulé(e) 1 insertion !"));

        _Cancel_MODIFICATION_request_Object
            ->Set_Window__MODIFICATION_CANCELLATION_TITLE
            (QObject::tr("ANNULER 1 insertion"));


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

            dateEdit_date_peremption->reset();


            _a_show_ITEM = false;

            _Last_choice_insert = set_choice_insert_UNDEFINED;

            setVisible(false);
        }
    }
}


bool YerithEntrerWindow::is_selection_rendering_VALID___STOCK()
{
    bool is_selection_rendering_VALID___STOCK = true;

    if (radioButton_inserer_un_stock->isChecked())
    {
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_nom_departement_produit);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_categorie_produit);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_reference_produit);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_designation);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_nom_entreprise_fournisseur);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, doubleSpinBox_lots_entrant);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_quantite);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_quantite_par_lot);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_UNITE_DE_Mesure);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_quantite_totale);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, checkBox_achat);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_prix_dachat);


        /* STOCK vs Asset specific qt-gui elements*/
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_label_prix_vente);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_prix_vente);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, checkBox_pourcentage_prix_dachat_prix_de_vente);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_pourcentage_prix_dachat_prix_de_vente);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_POURCENTAGE_1);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_label_prix_vente_en_gros);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_prix_vente_en_gros);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_POURCENTAGE_2);


        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, checkBox_HISTORIQUE);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, checkBox_date_peremption);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, dateEdit_date_peremption);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_localisation_du_stock);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, comboBox_localisation_produit);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_stock_dalerte);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_stock_dalerte);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_reference_recu_dachat);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, lineEdit_reference_recu_dachat);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, groupBox_image_du_stock_service);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_image_produit);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, label_description);
        YRI___VALIDATION___SELECTION(is_selection_rendering_VALID___STOCK, textEdit_description);
    }

    QDEBUG_STRING_OUTPUT_2_BOOL("YerithEntrerWindow::is_selection_rendering_VALID___STOCK",
                                 is_selection_rendering_VALID___STOCK);

    return is_selection_rendering_VALID___STOCK;
}


bool YerithEntrerWindow::is_selection_rendering_VALID___ASSET()
{
    bool yri___valid_selection___ASSET = true;

    if (radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, comboBox_nom_departement_produit);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, comboBox_categorie_produit);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, comboBox_reference_produit);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, lineEdit_designation);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, comboBox_nom_entreprise_fournisseur);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, doubleSpinBox_lots_entrant);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, label_quantite);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, lineEdit_quantite_par_lot);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, comboBox_UNITE_DE_Mesure);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, lineEdit_quantite_totale);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, checkBox_achat);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, lineEdit_prix_dachat);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, checkBox_HISTORIQUE);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, checkBox_date_peremption);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, dateEdit_date_peremption);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, label_localisation_du_stock);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, comboBox_localisation_produit);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, label_stock_dalerte);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, lineEdit_stock_dalerte);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, label_reference_recu_dachat);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, lineEdit_reference_recu_dachat);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, groupBox_image_du_stock_service);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, label_image_produit);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, label_description);
        YRI___VALIDATION___SELECTION(yri___valid_selection___ASSET, textEdit_description);
    }

    QDEBUG_STRING_OUTPUT_2_BOOL("YerithEntrerWindow::is_selection_rendering_VALID___ASSET",
                                 yri___valid_selection___ASSET);

    return yri___valid_selection___ASSET;
}


void YerithEntrerWindow::rendreVisible(YerithSqlTableModel 	*stocksTableModel,
                                       bool 				aShowItem /* = false */,
                                       YerithSqlTableModel 	*marchandisesTableModel /* = 0 */,
                                       enum 				entrer_VISIBLE_CHOICE choice_insert /* = set_choice_insert_ASSET */)
{
    //QDEBUG_STRING_OUTPUT_2_N("choice_insert", choice_insert);

    HANDLE_rendering_IF_ALLOWED_PREVIOUSLY_With___Direct_modification_entry();


    retranslateUi(this);


    populateComboBoxes__Labels_prix_ventes();


    groupBox_choix->setVisible(false);


    _a_show_ITEM = aShowItem;

    _Last_choice_insert = choice_insert;


    radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    radioButton_inserer_un_stock->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    radioButton_service_vente_de_service_au_client->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
    radioButton_INSERER_UNE_CHARGE_FINANCIERE->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

    radioButton_inserer_une_IMMOBILISATION->setChecked(true);

    YerithPOSUser *aCurrentUser = _allWindows->getUser();

    if (0 != aCurrentUser)
    {
        if (aCurrentUser->isManager())
        {
            groupBox_choix->setVisible(true);

            radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(true);
            radioButton_inserer_un_stock->setYerithEnabled(true);
            radioButton_service_vente_de_service_au_client->setYerithEnabled(true);
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->setYerithEnabled(true);

            if (set_choice_sell_TO_CLIENT == choice_insert)
            {
                radioButton_service_vente_de_service_au_client->setChecked(true);
            }
            else if (set_choice_insert_FINANCIAL_EXPENSE == choice_insert)
            {
                radioButton_INSERER_UNE_CHARGE_FINANCIERE->setChecked(true);
            }
            else if (set_choice_insert_STANDARD_INVENTORY_STOCK == choice_insert)
            {
                radioButton_inserer_un_stock->setChecked(true);
            }

        }
        else if (aCurrentUser->isVendeur())
        {
            groupBox_choix->setVisible(true);

            radioButton_service_vente_de_service_au_client->setYerithEnabled(true);

            radioButton_service_vente_de_service_au_client->setChecked(true);
        }
        else if (aCurrentUser->isGestionaireDesStocks())
        {
            groupBox_choix->setVisible(true);

            radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(true);

            radioButton_inserer_un_stock->setYerithEnabled(true);

            if (set_choice_insert_ASSET == choice_insert)
            {
                radioButton_inserer_une_IMMOBILISATION->setChecked(true);
            }
            else			// set_choice_insert_STANDARD_INVENTORY_STOCK
            {
                radioButton_inserer_un_stock->setChecked(true);
            }
        }
    }

    _curStocksTableModel = stocksTableModel;


    bool stockCheckInVisible = true;


    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED() ||
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        stockCheckInVisible = false;
    }

    if (aShowItem)
    {
        stockCheckInVisible = true;

        radioButton_INSERER_UNE_CHARGE_FINANCIERE->setChecked(false);
        radioButton_service_vente_de_service_au_client->setChecked(false);

        radioButton_service_vente_de_service_au_client->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);

        if (set_choice_sell_TO_CLIENT == choice_insert)
        {
        	radioButton_service_vente_de_service_au_client->setChecked(true);
        	radioButton_service_vente_de_service_au_client->setYerithEnabled(true);

        	radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        	radioButton_INSERER_UNE_CHARGE_FINANCIERE->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        	radioButton_inserer_un_stock->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        }
        if (set_choice_insert_FINANCIAL_EXPENSE == choice_insert)
        {
        	radioButton_INSERER_UNE_CHARGE_FINANCIERE->setChecked(true);
        	radioButton_INSERER_UNE_CHARGE_FINANCIERE->setYerithEnabled(true);

        	radioButton_service_vente_de_service_au_client->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        	radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        	radioButton_inserer_un_stock->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        }
        if (set_choice_insert_STANDARD_INVENTORY_STOCK == choice_insert)
        {
            radioButton_inserer_un_stock->setChecked(true);
            radioButton_inserer_un_stock->setYerithEnabled(true);

            radioButton_service_vente_de_service_au_client->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
            radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        }
        else if (set_choice_insert_ASSET == choice_insert)
        {
            radioButton_inserer_une_IMMOBILISATION->setChecked(true);
            radioButton_inserer_une_IMMOBILISATION->setYerithEnabled(true);

            radioButton_service_vente_de_service_au_client->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
            radioButton_INSERER_UNE_CHARGE_FINANCIERE->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
            radioButton_inserer_un_stock->setYerithEnabled(false, &YerithUtils::YERITH_DARK_GREEN_PALETTE);
        }
    }


    if (stockCheckInVisible &&
            set_choice_insert_STANDARD_INVENTORY_STOCK == choice_insert)
    {
        setStockSpecificWidgetVisible(stockCheckInVisible);
    }


    setupLineEditsQCompleters();

    populateEntrerUnStock_OU_ServiceComboBoxes(choice_insert);

    lineEdit_tva->setText(YerithUtils::getTvaStringWithPercent());

    if (Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
        checkBox_achat->setChecked(false);
        lineEdit_prix_vente->setFixedWidth(205);
        lineEdit_quantite_totale->setFixedWidth(205);

        check_fields_service_achat();
    }
    else if (Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        checkBox_achat->setChecked(false);
        lineEdit_prix_vente->setFixedWidth(205);
        lineEdit_quantite_totale->setFixedWidth(205);

        check_fields_service_vente();
    }
    else
    {
        if (aShowItem)
        {
            clear_all_fields();

            check_fields(true);

            showItem(marchandisesTableModel, choice_insert);
        }
    }

    if (!aShowItem ||
         radioButton_service_vente_de_service_au_client->isChecked())
    {
        comboBox_reference_produit->setYerithEnabled(true);

        comboBox_nom_departement_produit->setYerithEnabled(true);

        comboBox_categorie_produit->setYerithEnabled(true);

        //lineEdit_designation->setReadOnly(false);

        check_fields(true);
    }


    /**
     * No case requiring disabling it.
     */
    checkBox_EXACT_Reference_value_AS_DESIGNATION->setEnabled(true);


    if (_a_show_ITEM)
    {
        disable________ON_______HIDE_all_other_choices_RadioButton();
        disable________ON_______Show_all_RadioButton();
    }
    else
    {
        enable________ON_______HIDE_all_other_choices_RadioButton();
        enable________ON_______Show_all_RadioButton();
    }



    RESET_Bits_Showing_Cancellation_Modification_REQUEST_Needed();


    HANDLE_Combobox_unite_de_Mesure();


    setVisible(true);
}


void YerithEntrerWindow::HANDLE_Combobox_unite_de_Mesure()
{
    if (YerithERPConfig::___function___REMOVE_DETAILED_INPUT_entrer_stock)
    {
        comboBox_UNITE_DE_Mesure->setVisible(false);
    }
    else
    {
        comboBox_UNITE_DE_Mesure->setVisible(true);
    }
}


void YerithEntrerWindow::handle_HISTORIQUE_CHECKBOX(int aState)
{
    if (!YerithMainWindow::LANGUE_ANGLAISE)
    {
        if (checkBox_HISTORIQUE->isChecked())
        {
            checkBox_HISTORIQUE
                ->setFont(QFont(STRING_APPLICATION_WIDE_FONT_TYPE_YERITH_ERP_3_0,
                          INT_APPLICATION_WIDE_FONT_SIZE_YERITH_ERP_3_0));
        }
        else
        {
            checkBox_HISTORIQUE
                ->setFont(QFont(STRING_APPLICATION_WIDE_FONT_TYPE_YERITH_ERP_3_0, 9));
        }
    }


    if (checkBox_HISTORIQUE->isChecked())
    {
        checkBox_HISTORIQUE->setText(QObject::tr("historique actif"));

        _historique_stock_actif = true;
    }
    else
    {
        checkBox_HISTORIQUE->setText(QObject::tr("historique désac"));

        _historique_stock_actif = false;
    }
}


void YerithEntrerWindow::handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE(int aState)
{
    if (checkBox_pourcentage_prix_dachat_prix_de_vente->isChecked())
    {
        lineEdit_prix_vente->setReadOnly(true);
        lineEdit_pourcentage_prix_dachat_prix_de_vente->setReadOnly(false);
    }
    else
    {
        lineEdit_prix_vente->setReadOnly(false);
        lineEdit_pourcentage_prix_dachat_prix_de_vente->setReadOnly(true);
    }

    calculate_and_display_benefit_buying_price_percentage();
}


void YerithEntrerWindow::handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE_EN_GROS(int aState)
{
    if (checkBox_pourcentage_prix_dachat_prix_de_vente_en_gros->isChecked())
    {
        lineEdit_prix_vente_en_gros->setReadOnly(true);
        lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setReadOnly(false);
    }
    else
    {
        lineEdit_prix_vente_en_gros->setReadOnly(false);
        lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setReadOnly(true);
    }

    calculate_and_display_benefit_buying_price_percentage_EN_GROS();
}


void YerithEntrerWindow::handle_EXPIRATION_DATE_checkBox(int aState)
{
    if (checkBox_date_peremption->isChecked())
    {
        dateEdit_date_peremption->setVisible(true);
    }
    else
    {
        dateEdit_date_peremption->setVisible(false);
    }
}


void YerithEntrerWindow::handle_achat_checkBox(int aState)
{
    set_achat_checkBox_elements_visibility();

    lineEdit_pourcentage_prix_dachat_prix_de_vente->setText("0.00");
    lineEdit_pourcentage_prix_dachat_prix_de_vente_en_gros->setText("0.00");

    check_fields_mandatory_buying();
}


bool YerithEntrerWindow::handle_stocks_vendu_table(int stockID,
                                                   ServiceClientInfo &aServiceInfo,
                                                   double montant_total_vente,
                                                   double nouveau_compte_client,
                                                   double compteClient_PROGRAMME_DE_FIDELITE_CLIENTS)
{
    QString clientName = comboBox_nom_entreprise_fournisseur->currentText();

    int stocksVenduID =
                    YerithERPWindows::getNextIdSqlTableModel_stocks_vendu();

    QString
    referenceRecuVenduCompteClient(YerithUtils::GET_REFERENCE_RECU_VENDU
                                   (QString::number(stocksVenduID)));

    YerithSqlTableModel &stocksTableModel =
                    _allWindows->getSqlTableModel_stocks();

    QString stocksTableFilter =
                    QString("%1 = '%2'").arg(YerithDatabaseTableColumn::ID,
                                             QString::number(stockID));

    stocksTableModel.yerithSetFilter_WITH_where_clause(stocksTableFilter);


    int rows = stocksTableModel.easySelect("src/windows/yerith-erp-entrer-windows.cpp", 2278);

    if (rows > 0)
    {
        QSqlRecord stockRecord = stocksTableModel.record(0);

        QString
        quantiteQueryStr(QString("SELECT %1 FROM %2 WHERE id = '%3'").arg
                         (YerithDatabaseTableColumn::QUANTITE_TOTALE,
                          YerithDatabase::STOCKS,
                          QString::number(stockID)));
        QSqlQuery quantiteQuery;

        double quantite_actuelle = 0.0;

        int querySize =
                        YerithUtils::execQuery(quantiteQuery, quantiteQueryStr, _logger);

        if (querySize > 0 && quantiteQuery.next())
        {
            quantite_actuelle = quantiteQuery.value(0).toDouble();
        }


        QString historiqueStock = GET_SQL_RECORD_DATA(stockRecord,
                                                      YerithDatabaseTableColumn::HISTORIQUE_STOCK);

        YerithSqlTableModel &stocksVenduTableModel =
                        _allWindows->getSqlTableModel_stocks_vendu();

        QSqlRecord record = stocksVenduTableModel.record();

        int typeDeVente = YerithUtils::VENTE_COMPTE_CLIENT;

        record.setValue(YerithDatabaseTableColumn::TYPE_DE_VENTE, typeDeVente);

        record.setValue(YerithDatabaseTableColumn::IS_VENTE_EN_GROS, false);

        record.setValue(YerithDatabaseTableColumn::ID, stocksVenduID);

        record.setValue(YerithDatabaseTableColumn::REFERENCE,
                        aServiceInfo.reference);

        record.setValue(YerithDatabaseTableColumn::DESIGNATION,
                        aServiceInfo.designation);

        record.setValue(YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                        aServiceInfo.nom_departement_produit);

        record.setValue(YerithDatabaseTableColumn::CATEGORIE,
                        aServiceInfo.nom_categorie);

        record.setValue(YerithDatabaseTableColumn::IS_SERVICE,
                        YerithUtils::MYSQL_TRUE_LITERAL);

        record.setValue(YerithDatabaseTableColumn::REMISE_PRIX, 0.0);

        record.setValue(YerithDatabaseTableColumn::REMISE_POURCENTAGE, 0.0);

        record.setValue(YerithDatabaseTableColumn::DATE_PEREMPTION,
                        GET_CURRENT_DATE);

        record.setValue(YerithDatabaseTableColumn::REFERENCE_RECU_VENDU,
                        referenceRecuVenduCompteClient);

        double quantite_total_vendue = GET_SQL_RECORD_DATA(stockRecord,
                                                           YerithDatabaseTableColumn::QUANTITE_TOTALE).
                                       toDouble();

        record.setValue(YerithDatabaseTableColumn::QUANTITE_VENDUE,
                        quantite_total_vendue);

        record.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE,
                        GET_SQL_RECORD_DATA(stockRecord,
                                            YerithDatabaseTableColumn::
                                            PRIX_UNITAIRE).toDouble());

        record.setValue(YerithDatabaseTableColumn::MONTANT_TOTAL_VENTE,
                        montant_total_vente);

        record.setValue(YerithDatabaseTableColumn::MONTANT_TVA,
                        GET_SQL_RECORD_DATA(stockRecord,
                                            YerithDatabaseTableColumn::
                                            MONTANT_TVA).toDouble());

        record.setValue(YerithDatabaseTableColumn::LOCALISATION_STOCK,
                        GET_SQL_RECORD_DATA(stockRecord,
                                            YerithDatabaseTableColumn::
                                            LOCALISATION_STOCK));

        record.setValue(YerithDatabaseTableColumn::LOCALISATION,
                        GET_SQL_RECORD_DATA(stockRecord,
                                            YerithDatabaseTableColumn::
                                            LOCALISATION));

        record.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_CLIENT,
                        GET_SQL_RECORD_DATA(stockRecord,
                                            YerithDatabaseTableColumn::
                                            NOM_ENTREPRISE_CLIENT));

        YerithPOSUser *user = _allWindows->getUser();

        record.setValue(YerithDatabaseTableColumn::NOM_CAISSIER,
                        user->nom_complet());
        record.setValue(YerithDatabaseTableColumn::NOM_UTILISATEUR_CAISSIER,
                        user->nom_utilisateur());
        record.setValue(YerithDatabaseTableColumn::DATE_VENTE,
                        GET_CURRENT_DATE);
        record.setValue(YerithDatabaseTableColumn::HEURE_VENTE, CURRENT_TIME);

        record.setValue(YerithDatabaseTableColumn::STOCKS_ID, stockID);

        record.setValue(YerithDatabaseTableColumn::MONTANT_RECU,
                        montant_total_vente);

        double montant_a_rembourser = montant_total_vente;

        if (nouveau_compte_client >= 0.0)
        {
            montant_a_rembourser = 0.0;
        }
        else if (qFabs(nouveau_compte_client) >= montant_total_vente)
        {
            montant_a_rembourser = montant_total_vente;
        }
        else
        {
            montant_a_rembourser = qFabs(nouveau_compte_client);
        }

        record.setValue(YerithDatabaseTableColumn::MONTANT_A_REMBOURSER,
                        montant_a_rembourser);

        double nouvelle_quantite = quantite_actuelle - quantite_total_vendue;

        QString historiqueStockVendu;

        if (_historique_stock_actif)
        {
            historiqueStockVendu =
            		YerithHistoriqueStock::creer_mouvement_stock(MOUVEMENT_DE_STOCK_VENTE,
                                    							 stocksVenduID,
																 GET_CURRENT_DATE,
																 quantite_actuelle,
																 quantite_total_vendue,
																 nouvelle_quantite);
        }

        historiqueStock.append(QString("%1%2")
        						.arg(YerithHistoriqueStock::SEPARATION_EXTERNE,
        							 historiqueStockVendu));

        record.setValue(YerithDatabaseTableColumn::COMPTE_CLIENT_PROGRAMME_DE_FIDELITE_CLIENTS,
        				compteClient_PROGRAMME_DE_FIDELITE_CLIENTS);

        record.setValue(YerithDatabaseTableColumn::COMPTE_CLIENT,
                        aServiceInfo.nouveau_compte_client);

        record.setValue(YerithDatabaseTableColumn::CLIENTS_ID,
                        aServiceInfo.ID_client);

        record.setValue(YerithDatabaseTableColumn::QUARTIER_ENTREPRISE_CLIENT,
                        aServiceInfo.quartier_entreprise_client);

        record.setValue(YerithDatabaseTableColumn::VILLE_ENTREPRISE_CLIENT,
                        aServiceInfo.ville_entreprise_client);

        record.setValue(YerithDatabaseTableColumn::REGION_ETAT_ENTREPRISE_CLIENT,
                 	 	aServiceInfo.region_etat_entreprise_client);

        record.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_CLIENT,
                        aServiceInfo.nom_entreprise_client);

        record.setValue(YerithDatabaseTableColumn::SERVICE_SUPPLEMENT_AJOUT_COMMERCIAL,
                        0.0);

        bool success1 = stocksVenduTableModel.insertNewRecord(record,
        													  this,
															  "src/windows/yerith-erp-entrer-window.cpp",
															  3530,
															  aServiceInfo.designation);

        if (success1)
        {
            QString
            removeRowQuery(QString("DELETE FROM %1 WHERE %2 = '%3'").arg
                           (YerithDatabase::STOCKS,
                            YerithDatabaseTableColumn::ID,
                            QString::number(stockID)));

            YerithUtils::execQuery(removeRowQuery);

            if (0 == montant_a_rembourser)
            {
                //copy row from 'stocksVendu' to 'services_completes'
                QString copyRowQuery(QString("DROP TABLE IF EXISTS TempData;"
                                             "CREATE TEMPORARY TABLE TempData LIKE %1;"
                                             "INSERT INTO TempData SELECT * FROM %2 WHERE id = '%3';"
                                             "ALTER TABLE TempData CHANGE COLUMN `id` `id` INT(11) NULL, DROP PRIMARY KEY;"
                                             "UPDATE TempData SET id = %4;"
                                             "INSERT INTO %5 SELECT * FROM TempData;"
                                             "DROP TABLE IF EXISTS TempData;").
                                     arg(YerithDatabase::STOCKS_VENDU,
                                         YerithDatabase::STOCKS_VENDU,
                                         QString::number(stocksVenduID),
                                         QString::number(YerithERPWindows::
                                                         getNextIdSqlTableModel_services_completes()),
                                         YerithDatabase::SERVICES_COMPLETES));

                if (YerithUtils::execQuery(copyRowQuery))
                {
                    //handle stocksVendu table
                    QString
                    removeStocksVenduRowQuery(QString
                                              ("DELETE FROM %1 WHERE %2 = '%3'").
                                              arg(YerithDatabase::
                                                  STOCKS_VENDU,
                                                  YerithDatabaseTableColumn::
                                                  REFERENCE,
                                                  aServiceInfo.reference));

                    if (YerithUtils::execQuery(removeStocksVenduRowQuery))
                    {
                        //handle marchandise table
                        QString
                        removeMarchandisesRowQuery(QString
                                                   ("DELETE FROM %1 WHERE %2 = '%3'").
                                                   arg(YerithDatabase::
                                                       MARCHANDISES,
                                                       YerithDatabaseTableColumn::
                                                       REFERENCE,
                                                       aServiceInfo.
                                                       reference));

                        YerithUtils::execQuery(removeMarchandisesRowQuery);
                    }
                }
            }

            return true;
        }
    }

    return false;
}


bool YerithEntrerWindow::handle_clients_table(int stockID,
                                              double montant_total_vente)
{
    ServiceClientInfo aServiceClientInfo;

    QString clientName = comboBox_nom_entreprise_fournisseur->currentText();

    YerithSqlTableModel &clientsTableModel =
                    _allWindows->getSqlTableModel_clients();

    QString clientsTableFilter =
                    QString("%1 = '%2'").arg(YerithDatabaseTableColumn::NOM_ENTREPRISE,
                                             clientName);

    clientsTableModel.yerithSetFilter_WITH_where_clause(clientsTableFilter);

    int rows = clientsTableModel.easySelect("src/windows/yerith-erp-entrer-windows.cpp", 3617);

    if (rows > 0)
    {
        QSqlRecord clientsRecord = clientsTableModel.record(0);

        double compteClient_PROGRAMME_DE_FIDELITE_CLIENTS =
                        GET_SQL_RECORD_DATA(clientsRecord,
                                            YerithDatabaseTableColumn::COMPTE_CLIENT_PROGRAMME_DE_FIDELITE_CLIENTS).toDouble();

        double compteClient = GET_SQL_RECORD_DATA(clientsRecord,
                                                  YerithDatabaseTableColumn::COMPTE_CLIENT).toDouble();

        double nouveau_compte_client = compteClient - montant_total_vente;

        double detteMaximale = GET_SQL_RECORD_DATA(clientsRecord,
                                                   YerithDatabaseTableColumn::DETTE_MAXIMALE_COMPTE_CLIENT).toDouble();

        if (nouveau_compte_client >= 0.0)
        {
            detteMaximale = 0.0;
        }
        else if (qFabs(nouveau_compte_client) >= montant_total_vente)
        {
            detteMaximale = detteMaximale + montant_total_vente;
        }
        else
        {
            detteMaximale = qFabs(nouveau_compte_client);
        }

        clientsRecord.setValue(YerithDatabaseTableColumn::COMPTE_CLIENT,
                               nouveau_compte_client);

        clientsRecord.setValue(YerithDatabaseTableColumn::DETTE_MAXIMALE_COMPTE_CLIENT,
                               detteMaximale);

        bool success_clients =
                        clientsTableModel.updateRecord(0,
                        							   clientsRecord,
													   "src/windows/yerith-erp-entrer-window.cpp",
													   3654);

        aServiceClientInfo.ID_client =
                        GET_SQL_RECORD_DATA(clientsRecord,
                                            YerithDatabaseTableColumn::ID).toInt();

        aServiceClientInfo.reference =
                        comboBox_reference_produit->currentText();
        aServiceClientInfo.designation = lineEdit_designation->text();
        aServiceClientInfo.nom_departement_produit =
                        comboBox_nom_departement_produit->currentText();
        aServiceClientInfo.nom_categorie =
                        comboBox_categorie_produit->currentText();

        aServiceClientInfo.quartier_entreprise_client =
                        GET_SQL_RECORD_DATA(clientsRecord,
                                            YerithDatabaseTableColumn::QUARTIER);

        aServiceClientInfo.ville_entreprise_client =
                        GET_SQL_RECORD_DATA(clientsRecord, YerithDatabaseTableColumn::VILLE);

        aServiceClientInfo.region_etat_entreprise_client =
                        GET_SQL_RECORD_DATA(clientsRecord,
                                            YerithDatabaseTableColumn::PROVINCE_ETAT);

        aServiceClientInfo.nom_entreprise_client = clientName;

        aServiceClientInfo.nouveau_compte_client = nouveau_compte_client;

        clientsTableModel.resetFilter("src/windows/yerith-erp-entrer-window.cpp");

        //handle 'stocks_vendu' table
        bool success_stocksVendu = false;

        if (success_clients)
        {
            success_stocksVendu = handle_stocks_vendu_table(stockID,
                                                            aServiceClientInfo,
                                                            montant_total_vente,
                                                            nouveau_compte_client,
                                                            compteClient_PROGRAMME_DE_FIDELITE_CLIENTS);
        }

        return success_stocksVendu && true;
    }

    return false;
}


bool YerithEntrerWindow::IS__SERVICE_STOCK_DESIGNATION_REFERENCE__AVAILABLE(enum
                                                                            service_stock_already_exist_type
                                                                            *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT)
{
    *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT = SERVICE_STOCK_UNDEFINED;

    if (!comboBox_reference_produit->isEmpty())
    {
        QString curExistingReferenceDesignation_PRODUCT_in_out;

        *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT =
                        YerithUtils::IS_STOCK_DESIGNATION_OR_REFERENCE_UNIQUE
                        (comboBox_reference_produit->currentText(),
                         comboBox_categorie_produit->currentText(),
                         lineEdit_designation->text(),
                         curExistingReferenceDesignation_PRODUCT_in_out);

//      QDEBUG_STRING_OUTPUT_2_N("SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT",
//                                                   *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT);

        if (SERVICE_REFERENCE_EXISTS ==
                *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT)
        {
            if (!curExistingReferenceDesignation_PRODUCT_in_out.isEmpty() &&
                    !YerithUtils::isEqualCaseInsensitive(lineEdit_designation->
                                                         text(),
                                                         curExistingReferenceDesignation_PRODUCT_in_out))
            {
                QString infoMesg =
                                QObject::tr("Cette référence ('%1') "
                                                "est déjà utilisée par la marchandise (SERVICE) '%2' "
                                                "dans la catégorie ('%3') !").arg
                                (comboBox_reference_produit->currentText(),
                                 curExistingReferenceDesignation_PRODUCT_in_out,
                                 comboBox_categorie_produit->currentText());

                YerithQMessageBox::warning(this, "enregistrer", infoMesg);

                return false;
            }
        }
        else if (SERVICE_STOCK_DESIGNATION_EXIST ==
                 *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT)
        {
            if (!curExistingReferenceDesignation_PRODUCT_in_out.isEmpty() &&
                    !YerithUtils::isEqualCaseInsensitive(lineEdit_designation->
                                                         text(),
                                                         curExistingReferenceDesignation_PRODUCT_in_out))
            {
                QString infoMesg =
                                QObject::tr("La marchandise (SERVICE) '%1' utilise déjà la désignation ('%2') "
                                             "dans la catégorie ('%3') !").arg
                                            (comboBox_reference_produit->currentText(),
                                             curExistingReferenceDesignation_PRODUCT_in_out,
                                             comboBox_categorie_produit->currentText());

                YerithQMessageBox::warning(this, "enregistrer", infoMesg);

                return false;
            }
        }
        else if (SERVICE_STOCK_CATEGORY_EXIST ==
                 *SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT)
        {
            if (!curExistingReferenceDesignation_PRODUCT_in_out.isEmpty() &&
                    !YerithUtils::isEqualCaseInsensitive(comboBox_categorie_produit->currentText(),
                                                         curExistingReferenceDesignation_PRODUCT_in_out))
            {
                QString infoMesg = QObject::tr("La marchandise (SERVICE) '%1' est déjà dans la catégorie ('%2') !")
                                        .arg(comboBox_reference_produit->currentText(),
                                             curExistingReferenceDesignation_PRODUCT_in_out);

                YerithQMessageBox::warning(this, "enregistrer", infoMesg);

                return false;
            }
        }
    }

    return true;
}


bool YerithEntrerWindow::executer_enregistrer_une_IMMOBILISATION()
{
    if (!radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
        return false;
    }

    bool result_check_field = check_fields();

    if (!result_check_field)
    {
        if (QMessageBox::Ok ==
                YerithQMessageBox::warning(this,
                                           QObject::tr("IMMOBILISATION"),
                                           QObject::tr("Remplisser tous les champs obligatoires !")))
        {
        }
        else
        {
        }

        return false;
    }


    YerithSqlTableModel &cur_stocks_table_model = _allWindows->getSqlTableModel_stocks();

    bool designation_EXIST = YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*this,
                                                                         cur_stocks_table_model,
                                                                         *lineEdit_designation,
                                                                         QObject::tr("Une immobilisation"),
                                                                         YerithDatabaseTableColumn::DESIGNATION);

    if (designation_EXIST)
    {
        return false;
    }

    if (checkBox_date_peremption->isChecked())
    {
        if (dateEdit_date_peremption->date() <= GET_CURRENT_DATE)
        {
            QString warnMsg(QObject::tr("La date de péremption n'est pas postdatée !\n\n"
                                        "Continuer avec l'enregistrement des données de l'immobilisation ?"));

            if (QMessageBox::Ok ==
                    YerithQMessageBox::question(this,
                                                QObject::tr("enregistrer 1 immobilisation"),
                                                warnMsg,
                                                QMessageBox::Cancel,
                                                QMessageBox::Ok))
            {
            }
            else
            {
                return false;
            }
        }
    }


    if (!CHECK_DESCRIPTION_TEXT_SIZE())
    {
        return false;
    }


    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;



    QString proposed_nom_departement_produit =
                    comboBox_nom_departement_produit->currentText();

    if (!proposed_nom_departement_produit.isEmpty())
    {
        if (!YerithUtils::creerNouveauDepartementDeProduits
                (proposed_nom_departement_produit, this))
        {
            return false;
        }
    }


    QString proposed_nom_categorie = comboBox_categorie_produit->currentText();

    if (!proposed_nom_categorie.isEmpty())
    {
        if (!YerithUtils::creerNouvelleCategorie(proposed_nom_categorie,
                                                 proposed_nom_departement_produit,
                                                 this))
        {
            return false;
        }
    }


    QString proposed_Fournisseur_Client_Name =
                    comboBox_nom_entreprise_fournisseur->currentText();


    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        if (!proposed_Fournisseur_Client_Name.isEmpty())
        {
            if (!YerithUtils::creerNouveauClient(proposed_Fournisseur_Client_Name, this))
            {
                return false;
            }
        }
    }
    else
    {
        if (!proposed_Fournisseur_Client_Name.isEmpty())
        {
            if (!YerithUtils::creerNouveauFournisseur(proposed_Fournisseur_Client_Name, this))
            {
                return false;
            }
        }
    }

    YerithSqlTableModel &achatSqlTableModel = _allWindows->getSqlTableModel_achats();

    QSqlRecord achatRecord;

    QSqlRecord record = _curStocksTableModel->record();

    int stock_id_to_save = YerithERPWindows::getNextIdSqlTableModel_stocks();

    if (radioButton_inserer_une_IMMOBILISATION->isChecked() && hasBuying())
    {
        achatRecord = achatSqlTableModel.record();

        int achat_id_to_save = YerithERPWindows::getNextIdSqlTableModel_achats();

        achatRecord.setValue(YerithDatabaseTableColumn::ID, achat_id_to_save);

        achatRecord.setValue(YerithDatabaseTableColumn::STOCKS_ID,
                             stock_id_to_save);

        achatRecord.setValue(YerithDatabaseTableColumn::REFERENCE,
                             comboBox_reference_produit->currentText());

        achatRecord.setValue(YerithDatabaseTableColumn::DESIGNATION,
                             lineEdit_designation->text());

        achatRecord.setValue(YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                             comboBox_nom_departement_produit->currentText());

        achatRecord.setValue(YerithDatabaseTableColumn::CATEGORIE,
                             comboBox_categorie_produit->currentText());
    }

    record.setValue(YerithDatabaseTableColumn::IS_SERVICE, 0);
    record.setValue(YerithDatabaseTableColumn::ID, stock_id_to_save);
    record.setValue(YerithDatabaseTableColumn::REFERENCE,
                    comboBox_reference_produit->currentText());
    record.setValue(YerithDatabaseTableColumn::DESIGNATION,
                    lineEdit_designation->text());
    record.setValue(YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                    comboBox_nom_departement_produit->currentText());
    record.setValue(YerithDatabaseTableColumn::CATEGORIE,
                    comboBox_categorie_produit->currentText());
    record.setValue(YerithDatabaseTableColumn::DESCRIPTION_PRODUIT,
                    textEdit_description->toPlainText());
    record.setValue(YerithDatabaseTableColumn::LOTS_ENTRANT,
                    doubleSpinBox_lots_entrant->value());
    record.setValue(YerithDatabaseTableColumn::QUANTITE_PAR_LOT,
                    lineEdit_quantite_par_lot->text().toDouble());

    double quantite_totale = lineEdit_quantite_totale->text().toDouble();

    double stock_dalerte = lineEdit_stock_dalerte->text().toDouble();

    QString reference_recu_dachat = lineEdit_reference_recu_dachat->text();

    double prix_vente = lineEdit_prix_vente->text().toDouble();

    double prix_dachat = lineEdit_prix_dachat->text().toDouble();

    if (prix_dachat < 0)
    {
        prix_dachat = 0;
    }

    double montant_total_service_vente = quantite_totale * prix_vente;

    QString utilisateurCourrantNomComplet;

    YerithPOSUser *aUser = _allWindows->getUser();

    if (0 != aUser)
    {
        utilisateurCourrantNomComplet.append(aUser->nom_complet());
    }

    if (hasBuying())
    {
        achatRecord.setValue(YerithDatabaseTableColumn::ENREGISTREUR_STOCK,
                             utilisateurCourrantNomComplet);
        achatRecord.setValue(YerithDatabaseTableColumn::QUANTITE_TOTALE,
                             quantite_totale);
        achatRecord.setValue(YerithDatabaseTableColumn::REFERENCE_RECU_DACHAT,
                             reference_recu_dachat);
        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_DACHAT,
                             prix_dachat);

        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS,
                             0.0);
        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_VENTE, 0.0);

        //qDebug() << "++_tva: " << QString::number(_tva, 'f', 2);
        achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA, 0.0);
        achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS, 0.0);
    }


    record.setValue(YerithDatabaseTableColumn::REFERENCE_RECU_DACHAT,
                    reference_recu_dachat);

    record.setValue(YerithDatabaseTableColumn::STOCK_DALERTE, stock_dalerte);

    record.setValue(YerithDatabaseTableColumn::PRIX_DACHAT, prix_dachat);

    record.setValue(YerithDatabaseTableColumn::ENREGISTREUR_STOCK,
                    utilisateurCourrantNomComplet);

    record.setValue(YerithDatabaseTableColumn::QUANTITE_TOTALE,
                    quantite_totale);


    double prix_unitaire_ht = 0.0;

    double prix_unitaire_en_gros_ht = 0.0;

    double marge_beneficiaire = 0.0;

    double marge_beneficiaire_en_gros = 0.0;

    record.setValue(YerithDatabaseTableColumn::PRIX_VENTE, 0.0);

    record.setValue(YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS, 0.0);

    record.setValue(YerithDatabaseTableColumn::MONTANT_TVA, 0.0);

    record.setValue(YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS, 0.0);


    if (hasBuying())
    {
        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE,
                             prix_unitaire_ht);

        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE_EN_GROS,
                             prix_unitaire_en_gros_ht);

        achatRecord.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_FOURNISSEUR,
                 	 	 	 proposed_Fournisseur_Client_Name);

        achatRecord.setValue(YerithDatabaseTableColumn::LOCALISATION,
                             YerithERPConfig::THIS_SITE_LOCALISATION_NAME);

        achatRecord.setValue(YerithDatabaseTableColumn::LOCALISATION_STOCK,
                             comboBox_localisation_produit->currentText());

        achatRecord.setValue(YerithDatabaseTableColumn::DATE_ENTREE,
                             GET_CURRENT_DATE);

        if (checkBox_date_peremption->isChecked())
        {
            achatRecord.setValue(YerithDatabaseTableColumn::DATE_PEREMPTION,
                                 dateEdit_date_peremption->date());
        }
    }

    record.setValue(YerithDatabaseTableColumn::LOCALISATION_STOCK,
                    comboBox_localisation_produit->currentText());

    if (checkBox_date_peremption->isChecked())
    {
        record.setValue(YerithDatabaseTableColumn::DATE_PEREMPTION,
                        dateEdit_date_peremption->date());
    }

    record.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_FOURNISSEUR,
                    proposed_Fournisseur_Client_Name);

    record.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE,
                    prix_unitaire_ht);

    record.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE_EN_GROS,
                    prix_unitaire_en_gros_ht);

    record.setValue(YerithDatabaseTableColumn::LOCALISATION,
                    YerithERPConfig::THIS_SITE_LOCALISATION_NAME);

    record.setValue(YerithDatabaseTableColumn::DATE_ENTREE,
    				GET_CURRENT_DATE);


    QString historiqueStockInitial;

    if (_historique_stock_actif)
    {
        historiqueStockInitial =
                        YerithHistoriqueStock::creer_mouvement_stock
                        (MOUVEMENT_DE_STOCK_ENTREE, stock_id_to_save, GET_CURRENT_DATE, 0.0,
                         quantite_totale, quantite_totale);
    }

    //qDebug() << QString("++ test: %1")
    //                              .arg(historiqueStockInitial);

    record.setValue(YerithDatabaseTableColumn::HISTORIQUE_STOCK_ACTIF,
                    _historique_stock_actif);

    record.setValue(YerithDatabaseTableColumn::HISTORIQUE_STOCK,
                    historiqueStockInitial);

    if (label_image_produit->pixmap())
    {
        QByteArray bytes;
        YerithUtils::savePixmapToByteArray(bytes,
                                           *label_image_produit->pixmap(),
                                           "JPG");
        record.setValue(YerithDatabaseTableColumn::IMAGE_PRODUIT,
                        QVariant::fromValue(bytes));
    }

    bool achatSuccess = false;

    if (hasBuying())
    {
        achatSuccess = achatSqlTableModel
        					.insertNewRecord(achatRecord,
        									 this,
											 "src/windows/yerith-erp-entrer-window.cpp",
											 4125,
											 lineEdit_designation->text());
    }

    bool successInsertStock =
    		_curStocksTableModel
				->insertNewRecord(record,
								  this,
								  "src/windows/yerith-erp-entrer-window.cpp",
								  4133,
								  lineEdit_designation->text());


    STOP_Performing_MODIFICATIONS_handler();


    QString achatRetMsg;

    achatRetMsg.append(QObject::tr("L'achat de l'immobilisation '%1'")
    					.arg(lineEdit_designation->text()));


    if (hasBuying())
    {
        if (achatSuccess)
        {
            achatRetMsg.append(QObject::tr(" a été enregistré dans la base de données !"));

            YerithQMessageBox::information(this,
                                           QObject::tr("enregistrement - succès"),
                                           achatRetMsg);
        }
        else
        {
            achatRetMsg.append(QObject::tr(" n'a pas pu être enregistré dans la base de données !"));

            YerithQMessageBox::warning(this,
                                       QObject::tr("enregistrement - échec"),
                                       achatRetMsg);
        }
    }

    QString retMsg;

    retMsg.append(QObject::tr("L'immobilisation '%1'")
                  	  .arg(lineEdit_designation->text()));


    if (successInsertStock)
    {
        Set_Succeeded_INSERTION_to_DB_Tables_Bit(true);

        YERITH_RUNTIME_VERIFIER_instrumentation_INSERT("stocks.entrer_window_frame",
                                                       "src/windows/yerith-erp-entrer-window.cpp",
                                                       4181,
                                                       _allWindows);

        retMsg.append(QObject::tr(" a été enregistré dans la base de données !"));

        YerithQMessageBox::information(this,
                                       QObject::tr("enregistrement - succès"), retMsg);
    }
    else
    {
        retMsg.append(QObject::tr(" n'a pas pu être enregistré dans la base de données !"));

        YerithQMessageBox::warning(this,
                                   QObject::tr("enregistrement - échec"),
                                   retMsg);
    }


    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;

    rendreInvisible();

    _allWindows->_stocksWindow->rendreVisible(_curStocksTableModel, true);

    return true;
}



bool YerithEntrerWindow::executer_enregistrer_une_charge_financiere()
{
    if (!Is__radioButton__Dette__OR__Charge_financiere__CHECKED())
    {
        return false;
    }

    bool result_check_field = check_fields_service_achat();

    if (!result_check_field)
    {
        if (QMessageBox::Ok ==
                YerithQMessageBox::warning(this,
                                           QObject::tr("achat"),
                                           QObject::tr("Remplisser tous les champs obligatoires !")))
        {
        }
        else
        {
        }

        return false;
    }


    enum service_stock_already_exist_type SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST;

    if (!IS__SERVICE_STOCK_DESIGNATION_REFERENCE__AVAILABLE(&SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST))
    {
        return false;
    }



    QString proposed_nom_departement_produit =
    			comboBox_nom_departement_produit->currentText();

    if (!proposed_nom_departement_produit.isEmpty())
    {
        if (!YerithUtils::creerNouveauDepartement_non_objets_physiques(proposed_nom_departement_produit,
                                                                       this))
        {
            return false;
        }
    }


    YerithERPServiceData a_service_achat_au_fournisseur_data;

    a_service_achat_au_fournisseur_data._nom_departement_produit =
                    comboBox_nom_departement_produit->currentText();
    a_service_achat_au_fournisseur_data._categorie =
                    comboBox_categorie_produit->currentText();
    a_service_achat_au_fournisseur_data._description =
                    textEdit_description->toPlainText();
    a_service_achat_au_fournisseur_data._designation =
                    lineEdit_designation->text();
    a_service_achat_au_fournisseur_data._reference =
                    comboBox_reference_produit->currentText();

    QString proposed_Categorie_Name =
                    comboBox_categorie_produit->currentText();

    if (!proposed_Categorie_Name.isEmpty())
    {
        if (!YerithUtils::creerNouvelleCategorie
                (a_service_achat_au_fournisseur_data._categorie,
                 a_service_achat_au_fournisseur_data._nom_departement_produit))
        {
            return false;
        }
    }

    QString proposed_Fournisseur_Client_Name =
                    comboBox_nom_entreprise_fournisseur->currentText();

    if (!proposed_Fournisseur_Client_Name.isEmpty())
    {
        if (!YerithUtils::creerNouveauFournisseur
                (proposed_Fournisseur_Client_Name, this))
        {
            return false;
        }
    }


    double quantite_totale = doubleSpinBox_lots_entrant->value();

    double prix_unitaire = -1 * lineEdit_prix_vente->text().toDouble();

    double prix_dachat_du_service = quantite_totale * prix_unitaire;

    double prix_dachat_du_service_POSITIF = -1.0 * prix_dachat_du_service;

    QString utilisateurCourantNomComplet;

    YerithPOSUser *aUser = _allWindows->getUser();

    if (0 != aUser)
    {
        utilisateurCourantNomComplet.append(aUser->nom_complet());
    }

    bool successAchatDeServiceInsert = false;


	YerithSqlTableModel &LIGNES_BUDGETAIRES_SqlTableModel =
			_allWindows->getSqlTableModel_lignes_budgetaires();

	QSqlRecord LIGNES_BUDGETAIRES_query_RECORD;

	double montant_de_la_ligne_budgetaire_RESTANTE = 0.0;

    {
    	/*
    	 * VÉRIFIONS SI CETTE LIGNE BUGÉTAIRE DISPOSE D'ASSEZ
    	 * D'ARGENT pour cet achat !
    	 */

        QString yerith_LIGNES_BUDGETAIRES_SqlTableModelFilter =
        		QString("%1 = '%2'")
					.arg(YerithDatabaseTableColumn::INTITULE_DE_LA_ligne_budgetaire,
						 proposed_Categorie_Name);

    	LIGNES_BUDGETAIRES_SqlTableModel
			.yerithSetFilter_WITH_where_clause
				(yerith_LIGNES_BUDGETAIRES_SqlTableModelFilter);

    	QString retMsg_ECHEC_inserer_charge_financiere;

    	int rows =
    			LIGNES_BUDGETAIRES_SqlTableModel
					.easySelect("src/windows/yerith-erp-entrer-windows.cpp", 4341);

    	if (rows <= 0)
    	{
    		retMsg_ECHEC_inserer_charge_financiere =
    				QObject::tr("LA LIGNE BUDGÉTAIRE '%1' est inexistante !")
						.arg(proposed_Categorie_Name);

            YerithQMessageBox::warning(this,
                                       QObject::tr("enregistrement ACHAT SUR LIGNE BUDGÉTAIRE (1) - échec"),
									   retMsg_ECHEC_inserer_charge_financiere);

            LIGNES_BUDGETAIRES_SqlTableModel.resetFilter("src/windows/yerith-erp-entrer-window.cpp");

            return false;
    	}


    	LIGNES_BUDGETAIRES_query_RECORD = LIGNES_BUDGETAIRES_SqlTableModel.record(0);

    	montant_de_la_ligne_budgetaire_RESTANTE =
    			GET_SQL_RECORD_DATA(LIGNES_BUDGETAIRES_query_RECORD,
    								YerithDatabaseTableColumn::montant_RESTANT_de_la_ligne_budgetaire).toDouble();

    	if (montant_de_la_ligne_budgetaire_RESTANTE < prix_dachat_du_service_POSITIF)
    	{
    		retMsg_ECHEC_inserer_charge_financiere =
    				QObject::tr("LA LIGNE BUDGÉTAIRE '%1' DÉTIENT UN \n"
    								"MONTANT INSUFFISANT: ('%2') (requis pour \n"
    								"la charge financière !)!")
						.arg(proposed_Categorie_Name,
							 QString::number(montant_de_la_ligne_budgetaire_RESTANTE));

            YerithQMessageBox::warning(this,
                                       QObject::tr("enregistrement ACHAT SUR LIGNE BUDGÉTAIRE (2) - échec"),
									   retMsg_ECHEC_inserer_charge_financiere);

            LIGNES_BUDGETAIRES_SqlTableModel.resetFilter("src/windows/yerith-erp-entrer-window.cpp");

            return false;
    	}
    }

    {
        YerithSqlTableModel &charges_financieresSqlTableModel =
                        _allWindows->getSqlTableModel_charges_financieres();

        QSqlRecord achatRecord = charges_financieresSqlTableModel.record();

        int achat_de_service_id_to_save =
                        YerithERPWindows::getNextIdSqlTableModel_charges_financieres();

        achatRecord.setValue(YerithDatabaseTableColumn::ID,
                             achat_de_service_id_to_save);
        achatRecord.setValue(YerithDatabaseTableColumn::REFERENCE,
                             comboBox_reference_produit->currentText());
        achatRecord.setValue(YerithDatabaseTableColumn::DESIGNATION,
                             lineEdit_designation->text());
        achatRecord.setValue(YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                             a_service_achat_au_fournisseur_data.
                             _nom_departement_produit);
        achatRecord.setValue(YerithDatabaseTableColumn::CATEGORIE,
                             a_service_achat_au_fournisseur_data._categorie);

        achatRecord.setValue(YerithDatabaseTableColumn::ENREGISTREUR_STOCK,
                             utilisateurCourantNomComplet);
        achatRecord.setValue(YerithDatabaseTableColumn::QUANTITE_TOTALE,
                             quantite_totale);
        achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA,
                             _montantTva);
        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE,
                             prix_unitaire);
        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_DACHAT,
                             prix_dachat_du_service);

        achatRecord.
        setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_FOURNISSEUR,
                 proposed_Fournisseur_Client_Name);
        achatRecord.setValue(YerithDatabaseTableColumn::LOCALISATION,
                             YerithERPConfig::THIS_SITE_LOCALISATION_NAME);
        achatRecord.setValue(YerithDatabaseTableColumn::LOCALISATION_STOCK,
                             comboBox_localisation_produit->currentText());
        achatRecord.setValue(YerithDatabaseTableColumn::DATE_DE_COMMANDE,
                             GET_CURRENT_DATE);

        if (!YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*this,
        												 charges_financieresSqlTableModel,
														 *lineEdit_designation,
														 QObject::tr("Désignation"),
														 YerithDatabaseTableColumn::DESIGNATION)  &&
        	!YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*this,
        		            						     charges_financieresSqlTableModel,
        												 comboBox_reference_produit->lineEdit()->text(),
        												 QObject::tr("Référence"),
        												 YerithDatabaseTableColumn::REFERENCE)	)
        {
            successAchatDeServiceInsert =
            		charges_financieresSqlTableModel
    					.insertNewRecord(achatRecord,
    									 this,
    									 "src/windows/yerith-erp-entrer-window.cpp",
    									 4439,
    									 lineEdit_designation->text());
        }
    }

    bool successPaiementsInsert = false;

    {
        YerithERPPaymentProcessingInformation payment_processing_info;

        payment_processing_info._nom_entreprise =
                        proposed_Fournisseur_Client_Name;

        payment_processing_info._type_de_paiement =
                        YerithUtils::DECAISSEMENT_COMPTANT;

        payment_processing_info._montant_paye = prix_dachat_du_service;

        payment_processing_info._designation =
        		a_service_achat_au_fournisseur_data._designation;

        payment_processing_info._paiement_intitule_compte_bancaire =
        		GET_SQL_RECORD_DATA(LIGNES_BUDGETAIRES_query_RECORD,
        							YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE);

        payment_processing_info._reference =
        		a_service_achat_au_fournisseur_data._reference;

        bool is_supplier_payment = true;

        successPaiementsInsert =
                        payment_processing_info.save_payment_info_record(is_supplier_payment);
    }


    if (!successAchatDeServiceInsert || !successPaiementsInsert)
    {
    	LIGNES_BUDGETAIRES_SqlTableModel.resetFilter("src/windows/yerith-erp-entrer-window.cpp");

        return false;
    }


    /*
     * UPDATING TABLE lignes_budgetaires WITH A NEW REMAINING
     * AMOUNT for the current modified budget line !
     */
    double NOUVEAU_MONTANT_montant_de_la_ligne_budgetaire_RESTANTE =
    		montant_de_la_ligne_budgetaire_RESTANTE - prix_dachat_du_service_POSITIF;

    LIGNES_BUDGETAIRES_query_RECORD
		.setValue(YerithDatabaseTableColumn::montant_RESTANT_de_la_ligne_budgetaire,
				  NOUVEAU_MONTANT_montant_de_la_ligne_budgetaire_RESTANTE);

    LIGNES_BUDGETAIRES_SqlTableModel.updateRecord(0,
    											  LIGNES_BUDGETAIRES_query_RECORD,
												  "src/windows/yerith-erp-entrer-window.cpp",
												  4498);


    QString achatRetMsg(QObject::tr("La charge financière '%1' au fournisseur '%2'")
                            .arg(lineEdit_designation->text(),
                        proposed_Fournisseur_Client_Name));

    if (successAchatDeServiceInsert)
    {
        Set_Succeeded_INSERTION_to_DB_Tables_Bit(true);

        YERITH_RUNTIME_VERIFIER_instrumentation_INSERT("charges_financieres.entrer_window_frame",
                                                       "src/windows/yerith-erp-entrer-window.cpp",
                                                       4512,
                                                       _allWindows);

        achatRetMsg.append(QObject::tr(" a été enregistrée dans la base de données !"));

        YerithQMessageBox::information(this,
                                       QObject::tr("ajout d'une charge financière - succès"),
                                       achatRetMsg);
    }
    else
    {
        achatRetMsg.append(QObject::tr(" n'a pas pu être enregistrée dans la base de données !"));

        YerithQMessageBox::warning(this,
                                   QObject::tr("ajout d'1 charge financière - échec"),
                                   achatRetMsg);
    }


    QString paiementsRetMsg(QObject::tr("La charge financière '%1' au fournisseur '%2'")
                                .arg(lineEdit_designation->text(),
                                    proposed_Fournisseur_Client_Name));

    if (successPaiementsInsert)
    {
        paiementsRetMsg.append(QObject::tr(" a été répertoriée dans le tableau des paiements !"));

        YerithQMessageBox::information(this,
                                       QObject::tr("ajout d'une charge financière - répertorié - succès"),
                                       paiementsRetMsg);
    }
    else
    {
        paiementsRetMsg.append(QObject::tr(" n'a pas pu être répertoriée dans le tableau des paiements !"));

        YerithQMessageBox::warning(this,
                                   QObject::tr("ajout d'une charge financière - répertorié - échec"),
                                   paiementsRetMsg);
    }

    LIGNES_BUDGETAIRES_SqlTableModel.resetFilter("src/windows/yerith-erp-entrer-window.cpp");

    rendreInvisible();

    _allWindows->_charges_financieresWindow->rendreVisible(_curStocksTableModel);

    return true;
}


void YerithEntrerWindow::enregistrer_produit()
{
    bool result_check_field = false;

    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        result_check_field = check_fields_service_vente();
    }
    else
    {
        result_check_field = check_fields();
    }

    if (!result_check_field)
    {
        if (QMessageBox::Ok ==
                YerithQMessageBox::warning(this,
                                           QObject::tr("stock (service)"),
                                           QObject::tr("Remplisser tous les champs obligatoires !")))
        {
        }
        else
        {
        }

        return;
    }


    enum service_stock_already_exist_type SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST;

    if (!IS__SERVICE_STOCK_DESIGNATION_REFERENCE__AVAILABLE
            (&SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST))
    {
        return;
    }


    //double prix_vente_en_gros = 0.0;

    double yri_new_PRIX_Vente = lineEdit_prix_vente->text().toDouble();

    double yri_new_PRIX_Vente_En_Gros = get_prix_vente_en_gros();

    double yri_new_PRIX_DACHAT = lineEdit_prix_dachat->text().toDouble();


    if (radioButton_inserer_un_stock->isChecked())
    {
//        QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::enregistrer_produit",
//                               QString("prix_vente:(%1); prix_vente_en_gros:(%2); prix_dachat:(%3)")
//                                   .arg(QString::number(lineEdit_prix_vente->text().toDouble()),
//                                        QString::number(lineEdit_prix_vente_en_gros->text().toDouble()),
//                                        QString::number(lineEdit_prix_dachat->text().toDouble())));

        if (is_PRIX_per_unit_of_measure_SET())
        {
            yri_new_PRIX_DACHAT = calculer_prix_dachat_au_GRAMME();
        }


//        QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::enregistrer_produit",
//                               QString("yri_new_PRIX_Vente:(%1); yri_new_PRIX_DACHAT:(%2); _montantTva:(%3)")
//                                   .arg(QString::number(yri_new_PRIX_Vente),
//                                        QString::number(yri_new_PRIX_DACHAT),
//                                        QString::number(_montantTva)));


        if (!YerithUtils::isProfitable
                (yri_new_PRIX_Vente,
                 yri_new_PRIX_DACHAT,
                 _montantTva))
        {
            lineEdit_pourcentage_prix_dachat_prix_de_vente
                ->setPalette(YerithUtils::YERITH_RED_PALETTE);

            QString warnMsg(QObject::tr("Le prix de vente doit être supérieur ou égal au prix d'achat !"));

            YerithQMessageBox::warning(this,
                                       QObject::tr("pas profitable"),
                                       warnMsg);

            return;
        }


//        QDEBUG_STRING_OUTPUT_2("YerithEntrerWindow::enregistrer_produit",
//                               QString("prix_vente_en_gros:(%1); lineEdit_prix_dachat:(%2); _montantTva_en_gros:(%3)")
//                                   .arg(QString::number(yri_new_PRIX_Vente_En_Gros),
//                                        QString::number(yri_new_PRIX_DACHAT),
//                                        QString::number(_montantTva_en_gros)));


        if (!YerithUtils::isProfitable(yri_new_PRIX_Vente_En_Gros,
                                       yri_new_PRIX_DACHAT,
                                       _montantTva_en_gros))
        {
            lineEdit_pourcentage_prix_dachat_prix_de_vente
                ->setPalette(YerithUtils::YERITH_RED_PALETTE);

            QString warnMsg(QObject::tr("Le prix de vente (en gros) doit être supérieur ou égal au prix d'achat !"));

            YerithQMessageBox::warning(this,
                                       QObject::tr("pas profitable"),
                                       warnMsg);

            return;
        }
    }

    lineEdit_pourcentage_prix_dachat_prix_de_vente
        ->setPalette(YerithUtils::YERITH_DARK_GREEN_PALETTE);

    bool CURRENTLY_checking_expiration_date =
                    (radioButton_inserer_une_IMMOBILISATION->isChecked() ||
                     radioButton_inserer_un_stock->isChecked());

    if (checkBox_date_peremption->isChecked())
    {
        if (CURRENTLY_checking_expiration_date &&
                dateEdit_date_peremption->date() <= GET_CURRENT_DATE)
        {
            QString warnMsg(QObject::tr("La date de péremption n'est pas postdatée !\n\n"
                                        "Continuer avec l'enregistrement des données du stock (service) ?"));

            if (QMessageBox::Ok ==
                    YerithQMessageBox::question(this,
                                                QObject::tr("enregistrer un stock"),
                                                warnMsg,
                                                QMessageBox::Cancel,
                                                QMessageBox::Ok))
            {
            }
            else
            {
                return;
            }
        }
    }


    if (!CHECK_DESCRIPTION_TEXT_SIZE())
    {
        return;
    }


    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;

    YerithERPStockMarchandiseData a_stock_data;

    a_stock_data._isService =
                    Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED() ||
                    Is__radioButton__Dette__OR__Charge_financiere__CHECKED();

    if (Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        a_stock_data._nom_entreprise_client = comboBox_nom_entreprise_fournisseur->currentText();
    }

    a_stock_data._nom_departement_produit = comboBox_nom_departement_produit->currentText();
    a_stock_data._categorie = comboBox_categorie_produit->currentText();
    a_stock_data._description = textEdit_description->toPlainText();
    a_stock_data._designation = lineEdit_designation->text();
    a_stock_data._unite_de_mesure_de_vente = get_unite_de_mesure_de_vente();

    if (checkBox_achat->isChecked())
    {
        a_stock_data._prix_dachat_precedent = lineEdit_prix_dachat->text();
    }

    a_stock_data._prix_vente_precedent = lineEdit_prix_vente->text();


    yri_new_PRIX_Vente_En_Gros = get_prix_vente_en_gros();

//    QDEBUG_STRING_OUTPUT_2_N("II.) yri_new_PRIX_Vente_En_Gros",
//                              yri_new_PRIX_Vente_En_Gros);


    if (!lineEdit_prix_vente_en_gros->isEmpty())
    {
        a_stock_data._prix_vente_en_gros_precedent = QString::number(yri_new_PRIX_Vente_En_Gros);
    }
    else
    {
        a_stock_data._prix_vente_en_gros_precedent = QString::number(yri_new_PRIX_Vente);
    }

    a_stock_data._reference = comboBox_reference_produit->currentText();


    QString proposed_nom_departement_produit =
                    comboBox_nom_departement_produit->currentText();

    if (!proposed_nom_departement_produit.isEmpty())
    {
        if (!YerithUtils::creerNouveauDepartementDeProduits(proposed_nom_departement_produit, this))
        {
            return;
        }
    }


    if (!a_stock_data._categorie.isEmpty())
    {
        if (!YerithUtils::creerNouvelleCategorie(a_stock_data._categorie,
                                                 proposed_nom_departement_produit,
                                                 this))
        {
            return;
        }
    }


    if (SERVICE_STOCK_UNDEFINED == SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST)
    {
        if (!radioButton_inserer_une_IMMOBILISATION->isChecked())
        {
            if (!YerithUtils::insertStockItemInProductList(a_stock_data))
            {
                return;
            }
        }
    }

    QString proposed_Fournisseur_Client_Name =
                    comboBox_nom_entreprise_fournisseur->currentText();

    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        if (!proposed_Fournisseur_Client_Name.isEmpty())
        {
            if (!YerithUtils::creerNouveauClient
                    (proposed_Fournisseur_Client_Name, this))
            {
                return;
            }
        }
    }
    else
    {
        if (!proposed_Fournisseur_Client_Name.isEmpty())
        {
            if (!YerithUtils::creerNouveauFournisseur
                    (proposed_Fournisseur_Client_Name, this))
            {
                return;
            }
        }
    }

    YerithSqlTableModel &achatSqlTableModel =
                    _allWindows->getSqlTableModel_achats();

    QSqlRecord achatRecord;

    QSqlRecord record = _curStocksTableModel->record();

    int stock_id_to_save = YerithERPWindows::getNextIdSqlTableModel_stocks();

    if (!radioButton_service_vente_de_service_au_client->isChecked() &&
         hasBuying())
    {
        achatRecord = achatSqlTableModel.record();

        int achat_id_to_save =
                        YerithERPWindows::getNextIdSqlTableModel_achats();

        achatRecord.setValue(YerithDatabaseTableColumn::ID, achat_id_to_save);

        achatRecord.setValue(YerithDatabaseTableColumn::STOCKS_ID,
                             stock_id_to_save);

        achatRecord.setValue(YerithDatabaseTableColumn::REFERENCE,
                             comboBox_reference_produit->currentText());

        achatRecord.setValue(YerithDatabaseTableColumn::DESIGNATION,
                             lineEdit_designation->text());

        achatRecord.setValue(YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                             a_stock_data._nom_departement_produit);

        achatRecord.setValue(YerithDatabaseTableColumn::UNITE_DE_MESURE_DE_VENTE,
                             a_stock_data._unite_de_mesure_de_vente);

        achatRecord.setValue(YerithDatabaseTableColumn::CATEGORIE,
                             a_stock_data._categorie);
    }

    record.setValue(YerithDatabaseTableColumn::IS_SERVICE,
                    a_stock_data._isService);

    record.setValue(YerithDatabaseTableColumn::ID, stock_id_to_save);

    record.setValue(YerithDatabaseTableColumn::REFERENCE,
                    comboBox_reference_produit->currentText());

    record.setValue(YerithDatabaseTableColumn::DESIGNATION,
                    lineEdit_designation->text());

    record.setValue(YerithDatabaseTableColumn::NOM_DEPARTEMENT_PRODUIT,
                    a_stock_data._nom_departement_produit);

    record.setValue(YerithDatabaseTableColumn::UNITE_DE_MESURE_DE_VENTE,
                    a_stock_data._unite_de_mesure_de_vente);

    record.setValue(YerithDatabaseTableColumn::CATEGORIE,
                    a_stock_data._categorie);

    record.setValue(YerithDatabaseTableColumn::DESCRIPTION_PRODUIT,
                    textEdit_description->toPlainText());

    record.setValue(YerithDatabaseTableColumn::LOTS_ENTRANT,
                    doubleSpinBox_lots_entrant->value());

    record.setValue(YerithDatabaseTableColumn::QUANTITE_PAR_LOT,
                    lineEdit_quantite_par_lot->text().toDouble());

    double quantite_totale = lineEdit_quantite_totale->text().toDouble();

    double stock_dalerte = lineEdit_stock_dalerte->text().toDouble();

    QString reference_recu_dachat = lineEdit_reference_recu_dachat->text();

    double prix_vente = lineEdit_prix_vente->text().toDouble();

    double prix_dachat = lineEdit_prix_dachat->text().toDouble();

    if (prix_dachat < 0)
    {
        prix_dachat = 0;
    }

    double montant_total_service_vente = quantite_totale * prix_vente;

    QString utilisateurCourrantNomComplet;

    YerithPOSUser *aUser = _allWindows->getUser();

    if (0 != aUser)
    {
        utilisateurCourrantNomComplet.append(aUser->nom_complet());
    }

    if (!radioButton_service_vente_de_service_au_client->isChecked()    &&
        hasBuying())
    {
        achatRecord.setValue(YerithDatabaseTableColumn::ENREGISTREUR_STOCK,
                             utilisateurCourrantNomComplet);

        achatRecord.setValue(YerithDatabaseTableColumn::QUANTITE_TOTALE,
                             quantite_totale);

        achatRecord.setValue(YerithDatabaseTableColumn::REFERENCE_RECU_DACHAT,
                             reference_recu_dachat);

        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_DACHAT,
                             prix_dachat);

        if (!radioButton_inserer_une_IMMOBILISATION->isChecked())
        {
            achatRecord.setValue(YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS,
                                 yri_new_PRIX_Vente_En_Gros);

            achatRecord.setValue(YerithDatabaseTableColumn::PRIX_VENTE,
                                 yri_new_PRIX_Vente);

            //qDebug() << "++_tva: " << QString::number(_tva, 'f', 2);
            achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA,
                                 _montantTva);

            achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS,
                                 _montantTva_en_gros);
        }
        else
        {
            achatRecord.setValue(YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS,
                                 0.0);
            achatRecord.setValue(YerithDatabaseTableColumn::PRIX_VENTE, 0.0);

            //qDebug() << "++_tva: " << QString::number(_tva, 'f', 2);
            achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA, 0.0);

            achatRecord.setValue(YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS, 0.0);
        }
    }

    if (!radioButton_service_vente_de_service_au_client->isChecked())
    {
        record.setValue(YerithDatabaseTableColumn::REFERENCE_RECU_DACHAT,
                        reference_recu_dachat);

        record.setValue(YerithDatabaseTableColumn::STOCK_DALERTE,
                        stock_dalerte);

        YerithUtils::UPDATE_PREVIOUS_BUYING_PRICE_IN_ProductList(a_stock_data,
                                                                 this);

        record.setValue(YerithDatabaseTableColumn::PRIX_DACHAT, prix_dachat);
    }

    record.setValue(YerithDatabaseTableColumn::ENREGISTREUR_STOCK,
                    utilisateurCourrantNomComplet);

    record.setValue(YerithDatabaseTableColumn::QUANTITE_TOTALE,
                    quantite_totale);


    double prix_unitaire_ht = 0.0;

    double prix_unitaire_en_gros_ht = 0.0;

    double marge_beneficiaire = 0.0;

    double marge_beneficiaire_en_gros = 0.0;

    if (radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
        record.setValue(YerithDatabaseTableColumn::PRIX_VENTE, 0.0);

        record.setValue(YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS, 0.0);

        record.setValue(YerithDatabaseTableColumn::MONTANT_TVA, 0.0);

        record.setValue(YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS, 0.0);
    }
    else
    {
        YerithUtils::UPDATE_PREVIOUS_SELLING_PRICE_IN_ProductList(a_stock_data,
                                                                  this);

        record.setValue(YerithDatabaseTableColumn::PRIX_VENTE,
                        yri_new_PRIX_Vente);

        record.setValue(YerithDatabaseTableColumn::PRIX_VENTE_EN_GROS,
                        yri_new_PRIX_Vente_En_Gros);

//        QDEBUG_STRING_OUTPUT_2_N("enregistrer_produit; yri_new_PRIX_Vente_En_Gros",
//                                  yri_new_PRIX_Vente_En_Gros);

        //qDebug() << "++_tva: " << QString::number(_tva, 'f', 2);

        record.setValue(YerithDatabaseTableColumn::MONTANT_TVA,
                        _montantTva);

        record.setValue(YerithDatabaseTableColumn::MONTANT_TVA_EN_GROS,
                        _montantTva_en_gros);

        prix_unitaire_ht = yri_new_PRIX_Vente - _montantTva;

        prix_unitaire_en_gros_ht = yri_new_PRIX_Vente_En_Gros - _montantTva_en_gros;

        marge_beneficiaire =
                        YerithUtils::getMargeBeneficiaire(prix_vente, prix_dachat,
                                                          _montantTva);

        marge_beneficiaire_en_gros =
                        YerithUtils::getMargeBeneficiaire(yri_new_PRIX_Vente_En_Gros,
                                                          yri_new_PRIX_DACHAT,
                                                          _montantTva_en_gros);
    }


    if (!radioButton_service_vente_de_service_au_client->isChecked() &&
        hasBuying())
    {
        if (!radioButton_inserer_une_IMMOBILISATION->isChecked())
        {
            achatRecord.setValue(YerithDatabaseTableColumn::MARGE_BENEFICIAIRE,
                                 marge_beneficiaire);

            achatRecord.setValue(YerithDatabaseTableColumn::MARGE_BENEFICIAIRE_EN_GROS,
                                 marge_beneficiaire_en_gros);
        }

        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE,
                             prix_unitaire_ht);

        achatRecord.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE_EN_GROS,
                             prix_unitaire_en_gros_ht);

        achatRecord.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_FOURNISSEUR,
                             proposed_Fournisseur_Client_Name);

        achatRecord.setValue(YerithDatabaseTableColumn::LOCALISATION,
                             YerithERPConfig::THIS_SITE_LOCALISATION_NAME);

        achatRecord.setValue(YerithDatabaseTableColumn::LOCALISATION_STOCK,
                             comboBox_localisation_produit->currentText());

        achatRecord.setValue(YerithDatabaseTableColumn::DATE_ENTREE,
                             GET_CURRENT_DATE);

        if (checkBox_date_peremption->isChecked())
        {
            achatRecord.setValue(YerithDatabaseTableColumn::DATE_PEREMPTION,
                                 dateEdit_date_peremption->date());
        }
    }

    if (radioButton_inserer_un_stock->isChecked())
    {
        record.setValue(YerithDatabaseTableColumn::LOCALISATION_STOCK,
                        comboBox_localisation_produit->currentText());

        if (checkBox_date_peremption->isChecked())
        {
            record.setValue(YerithDatabaseTableColumn::DATE_PEREMPTION,
                            dateEdit_date_peremption->date());
        }

        record.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_FOURNISSEUR,
                        proposed_Fournisseur_Client_Name);
    }
    else
    {
        record.setValue(YerithDatabaseTableColumn::NOM_ENTREPRISE_CLIENT,
                        proposed_Fournisseur_Client_Name);
    }

    record.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE,
                    prix_unitaire_ht);

    record.setValue(YerithDatabaseTableColumn::PRIX_UNITAIRE_EN_GROS,
                    prix_unitaire_en_gros_ht);

    record.setValue(YerithDatabaseTableColumn::LOCALISATION,
                    YerithERPConfig::THIS_SITE_LOCALISATION_NAME);

    record.setValue(YerithDatabaseTableColumn::DATE_ENTREE, GET_CURRENT_DATE);


    QString historiqueStockInitial;

    if (_historique_stock_actif)
    {
        historiqueStockInitial =
                YerithHistoriqueStock::creer_mouvement_stock(MOUVEMENT_DE_STOCK_ENTREE,
                                                             stock_id_to_save,
                                                             GET_CURRENT_DATE,
                                                             0.0,
                                                             quantite_totale,
                                                             quantite_totale);
    }

    //qDebug() << QString("++ test: %1")
    //                              .arg(historiqueStockInitial);

    record.setValue(YerithDatabaseTableColumn::HISTORIQUE_STOCK_ACTIF,
                    _historique_stock_actif);

    record.setValue(YerithDatabaseTableColumn::HISTORIQUE_STOCK,
                    historiqueStockInitial);

    if (label_image_produit->pixmap())
    {
        QByteArray bytes;

        YerithUtils::savePixmapToByteArray(bytes,
                                           *label_image_produit->pixmap(),
                                           "JPG");

        record.setValue(YerithDatabaseTableColumn::IMAGE_PRODUIT,
                        QVariant::fromValue(bytes));
    }

    bool achatSuccess = false;

    if (hasBuying())
    {
        if (radioButton_inserer_une_IMMOBILISATION->isChecked() ||
            radioButton_inserer_un_stock->isChecked())
        {
            achatSuccess = achatSqlTableModel
            				.insertNewRecord(achatRecord,
            								 this,
											 "src/windows/yerith-erp-entrer-window.cpp",
											 5200,
											 lineEdit_designation->text());
        }
    }


    bool successInsertStock =
    		_curStocksTableModel->insertNewRecord(record,
    											  this,
												  "src/windows/yerith-erp-entrer-window.cpp",
												  5210,
												  lineEdit_designation->text());


    QString achatRetMsg;

    if (!radioButton_inserer_une_IMMOBILISATION->isChecked())
    {
        achatRetMsg.append(QObject::tr("L'achat du stock '%1'")
                            .arg(lineEdit_designation->text()));
    }
    else
    {
        achatRetMsg.append(QObject::tr("L'achat de l'immobilisation '%1'")
                            .arg(lineEdit_designation->text()));
    }


    if (!radioButton_service_vente_de_service_au_client->isChecked()    &&
        hasBuying())
    {
        if (achatSuccess)
        {
            achatRetMsg.append(QObject::tr(" a été enregistré dans la base de données !"));

            YerithQMessageBox::information(this,
                                           QObject::tr("enregistrement - succès"),
                                           achatRetMsg);
        }
        else
        {
            achatRetMsg.append(QObject::tr(" n'a pas pu être enregistré dans la base de données !"));

            YerithQMessageBox::warning(this,
                                       QObject::tr("enregistrement - échec"),
                                       achatRetMsg);
        }
    }

    QString retMsg;

    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        retMsg.append(QObject::tr("Le service '%1'")
                        .arg(comboBox_reference_produit->currentText()));
    }
    else
    {
        retMsg.append(QObject::tr("Le stock '%1'")
                        .arg(lineEdit_designation->text()));
    }

    if (successInsertStock                                                                                  &&
        Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED())
    {
        //handle 'clients' table
        handle_clients_table(stock_id_to_save, montant_total_service_vente);
    }

    if (successInsertStock)
    {
        Set_Succeeded_INSERTION_to_DB_Tables_Bit(true);

        YERITH_RUNTIME_VERIFIER_instrumentation_INSERT("stocks.entrer_window_frame",
                                                       "src/windows/yerith-erp-entrer-window.cpp",
                                                       5188,
                                                       _allWindows);

        retMsg.append(QObject::tr(" a été enregistré dans la base de données !"));

        YerithQMessageBox::information(this,
                                       QObject::tr("enregistrement - succès"), retMsg);
    }
    else
    {
        retMsg.append(QObject::tr(" n'a pas pu être enregistré dans la base de données !"));

        YerithQMessageBox::warning(this,
                                   QObject::tr("enregistrement - échec"),
                                   retMsg);
    }


    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;

    rendreInvisible();

    if (radioButton_service_vente_de_service_au_client->isChecked())
    {
        _allWindows->_ventesWindow->rendreVisible(_curStocksTableModel);
    }
    else
    {
        if (radioButton_inserer_une_IMMOBILISATION->isChecked())
        {
            _allWindows->_stocksWindow->rendreVisible(_curStocksTableModel,
                                                      true);
        }
        else
        {
            _allWindows->_stocksWindow->rendreVisible(_curStocksTableModel);
        }
    }
}
