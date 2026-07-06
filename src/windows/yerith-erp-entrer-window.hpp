/*
 * yerith-erp-entrer-window.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ENTRER_WINDOW_HPP_
#define YERITH_ENTRER_WINDOW_HPP_


#include "../../ui_yerith-erp-entrer-window.h"


#include <QtWidgets/QMessageBox>


#include "src/windows/yerith-erp-window-commons.hpp"


class YerithERPWindows;
class YerithSqlTableModel;
class ServiceClientInfo;


class YerithEntrerWindow : public YerithWindowsCommons,
    					   private Ui_YerithEntrerWindow
{
Q_OBJECT

public:

    class ServiceClientInfo
    {
    public:
        int ID_client;
        double nouveau_compte_client;

        QString reference;
        QString designation;
        QString nom_departement_produit;
        QString nom_categorie;
        QString quartier_entreprise_client;
        QString ville_entreprise_client;
        QString region_etat_entreprise_client;
        QString nom_entreprise_client;
    };

    YERITH_CLASS_OPERATORS

    YerithEntrerWindow();

    inline ~YerithEntrerWindow()
    {
        delete _logger;
    }

    inline QToolBar *getQMainWindowToolBar()
    {
        return toolBar_entrerWindow;
    }

    virtual void definirCaissier();

    virtual void definirManager();

    virtual void definirVendeur();

    virtual void definirGestionaireDesStocks();

    virtual void definirMagasinier();

    virtual void definirPasDeRole();

    virtual void Set__label_prix_vente__TRANSFORME_PRIX_dachat__visible(bool visible);


    virtual void rendreInvisible();


    bool is_selection_rendering_VALID___STOCK();

    bool is_selection_rendering_VALID___ASSET();


    void rendreVisible(YerithSqlTableModel  *stocksTableModel,
                       bool 				aShowItem = false,
                       YerithSqlTableModel 	*marchandisesTableModel = 0,
                       enum 				entrer_VISIBLE_CHOICE choice_insert = set_choice_insert_ASSET);

    inline void rendreVisible(YerithSqlTableModel *stocksTableModel,
                              YerithSqlTableModel *marchandisesTableModel)
    {
        rendreVisible(stocksTableModel,
                      true,
                      marchandisesTableModel,
                      set_choice_insert_STANDARD_INVENTORY_STOCK);
    }


public slots:

    virtual inline void apropos()
    {
        YerithWindowsCommons::apropos(this);
    }

    virtual inline void help()
    {
        YerithQMessageBox::information(this,
                                       QObject::tr("aide"),
                                       QObject::tr("Remplissez le formulaire, et ensuite cliquer sur enregistrer !\n\n"
                                                   "POUR ENTRER 1 nouveau stock d'1 marchandise déjà existante,"
                                                   " il est préférable de ré-utiliser l'interface 'Marchandise / SERVICES (bouton rouge)' ! \n\n"
                                                   "1. Des champs aux couleurs rouges représentent des champs de texte"
                                                   " obligatoire et NON Éditable !\n\n"
                                                   "2. Des champs aux couleurs violets représentent des champs de texte"
                                                   " obligatoire et Éditable !\n\n"
                                                   "3. Creez au préalable 1 compte bancaire, ainsi que des lignes budgétaires"
                                                   " dans la section administration de ce progiciel de gestion intégré;"
                                                   " aux fins de permettre l'insertion de charges financières !"));
    }

    inline void rendreInvisibleAvecConservation()
    {
        setVisible(false);
    }

    virtual inline void modifier()
    {
        stocks();
    }

    void deconnecter_utilisateur();

    bool handle_stocks_vendu_table(int 					stockID,
                                   ServiceClientInfo 	&aServiceInfo,
                                   double 				montant_total_vente,
                                   double 				nouveau_compte_client,
                                   double				compteClient_PROGRAMME_DE_FIDELITE_CLIENTS);

    bool handle_clients_table(int stockID,
    						  double montant_total_vente);

    inline bool hasBuying()
    {
        return checkBox_achat->isChecked() &&
               !lineEdit_prix_dachat->text().isEmpty();
    }

    bool IS__SERVICE_STOCK_DESIGNATION_REFERENCE__AVAILABLE(enum service_stock_already_exist_type
                                                            	*SERVICE_REFERENCE_STOCK_DESIGNATION_EXIST_IN_OUT);

    bool executer_enregistrer_une_IMMOBILISATION();

    bool executer_enregistrer_une_charge_financiere();

    inline void enregistrer_une_charge_financiere()
    {
        YerithUtils::run_FUNCTION_ROUNDED_WITH_DB_TRANSACTION_WITH_ROLLBACK(this,
                                                                            &YerithEntrerWindow::
                                                                            executer_enregistrer_une_charge_financiere);
    }

    void enregistrer_produit();


    void HANDLE_Combobox_unite_de_Mesure();


    void handle_HISTORIQUE_CHECKBOX(int aState);

    void handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE(int aState);

    void handle_POURCENTAGE_PRIX_DACHAT_PRIX_DE_VENTE_EN_GROS(int aState);

    void handle_EXPIRATION_DATE_checkBox(int aState);

    void handle_achat_checkBox(int aState);


protected slots:

    inline void supprimer_image_stock()
    {
        YerithWindowsCommons::supprimer_image(*label_image_produit);
    }

    inline void selectionner_image_produit()
    {
        YerithWindowsCommons::selectionner_image(*label_image_produit);
    }


protected:

    virtual void reset_window_widgets_modification_Bit();

    virtual void setupShortcuts();


private slots:

    virtual void ON_action_START_YR_QVGE_dynamic_analysis_tool();

    void handle_comboBox_unite_de_mesure_changement(int currentUniteDeMesure_Index);

    inline void handle_categorie_produit_changement(const QString &currentProductCategory)
    {
        populateCOMBOBOX__REFERENCE_PRODUIT();
    }

    inline void handle_departement_de_produits_changement(const QString &currentProductDepartment)
    {
        populateCOMBOBOX__CATEGORIE();
    }


    bool CHECK_DESCRIPTION_TEXT_SIZE();


    void handle_Edit_ReferenceDesignation();

    void handle_Set_YerithEnabled_ComboBox_Reference_Produit(bool enabled);

    void handle_ReferenceDesignation_checkBox(int aState);


    void handle_enregistrer();

    bool product_search_with_designation();

    bool product_search_with_reference();

    virtual int get_unite_de_mesure_de_vente();

    double calculer_prix_dachat_au_GRAMME();

    void display_quantite_totale(const QString &quantite_par_lot);

    void display_quantite_totale_by_spinbox(double lots);

    void calculate_and_display_ALL_benefit_buying_price_percentage();

    void calculate_and_display_benefit_buying_price_percentage();

    void calculate_and_display_benefit_buying_price_percentage_EN_GROS();

    inline double Get__prix__vente__FOR__kilogrammes__thousands__From__unity(double prix_vente)
    {
        return prix_vente;
    }

    void edited_prix_vente(const QString &newPrixVente);

    void edited_prix_vente_en_gros(const QString &newPrixVente_En_Gros);

    void edited_pourcentage_prix_dachat_prix_de_vente(const QString &
                                                      new_pourcentage_prix_dachat_prix_de_vente);

    void edited_pourcentage_prix_dachat_prix_de_vente_EN_GROS(const QString &
                                                              new_pourcentage_prix_dachat_prix_de_vente_EN_GROS);

    void display_service_montant_total_vente();

    void display_prix_vente();

    void display_prix_vente_en_gros();

    void setStockSpecificWidgetVisible(bool visible);


    /**
     * Returns an empty string in case no 'banking account title' was
     * found for a given 'a_current_BUDGET_Line_INTITULE' ('banking account budget line title')
     */
    QString Get_intitule_du_compte_bancaire__FROM__BUDGET_LINE_table(QString a_current_BUDGET_Line_INTITULE);


    void Switch__label__SUPPLIER_fournisseur_banque_institution(bool client_text = false);


    inline bool Is__radioButton___PLACEMENT_dun_ordre_dun_client___Or___service_vente_de_service_au_client____CHECKED()
    {
        return
            ( radioButton_service_vente_de_service_au_client->isChecked() );
    }


    inline bool Is__radioButton__Dette__OR__Charge_financiere__CHECKED()
    {
        return
            ( radioButton_INSERER_UNE_CHARGE_FINANCIERE->isChecked() );
    }



    virtual inline void enable________ON_______Show_all_RadioButton()
    {
        action___Show_all_choices->setVisible(true);
    }

    virtual inline void disable________ON_______Show_all_RadioButton()
    {
        action___Show_all_choices->setVisible(false);
    }



    virtual inline void enable________ON_______HIDE_all_other_choices_RadioButton()
    {
        action___HIDE_all_other_choices_RadioButton->setVisible(true);
    }

    virtual inline void disable________ON_______HIDE_all_other_choices_RadioButton()
    {
        action___HIDE_all_other_choices_RadioButton->setVisible(false);
    }



    virtual bool ON_______Show_all_RadioButton();


    virtual bool ON_______HIDE_all_other_choices_RadioButton();



    void Handle___Departement_de_produits___Via___RADIOBUTTONS();


    void handle_checkBox_INSERT_ASSET(bool checked);


    void handle_checkBox_INSERT_STOCK(bool checked);


    void handle_checkBox_INSERER_UNE_CHARGE_FINANCIERE(bool checked);


    void handle_checkBox_service_vente(bool checked);


    void handleTVACheckBox(int state);


    bool check_fields_mandatory_buying();


private:

    void set_achat_checkBox_elements_visibility();

    double get_prix_vente_en_gros();

    void showItem(YerithSqlTableModel *stocks_OR_marchandises_TableModel = 0,
                  enum entrer_VISIBLE_CHOICE choice_insert =
                                  set_choice_insert_ASSET);

    bool check_fields_service_achat();

    bool check_fields_service_vente();

    bool check_fields(bool withClearAllServiceMandatoryFields = false);

    void clear_all_fields();

    void setupLineEdits();

    void setupLineEditsQCompleters__FOR_STOCK_INVENTORY();


    void POPULATE_banking_accounts__For__ONLY_budget_LINES_accounts();


    void populateComboBoxes__Labels_prix_ventes();

    void populateCOMBOBOX__REFERENCE_PRODUIT();

    void populateCOMBOBOX__UNITES_DE_Mesures();

    void populateCOMBOBOX__CATEGORIE();


    inline void setupLineEditsQCompleters()
    {
        setupLineEditsQCompleters__FOR_STOCK_INVENTORY();
    }

    inline void setupDateTimeEdits()
    {
        dateEdit_date_peremption->setStartDate(GET_CURRENT_DATE);
    }


    void set_red_palette(YerithLineEdit &a_yerith_qline_edit_WIDGET);


    bool is_PRIX_per_unit_of_measure_SET();


    void populateEntrerUnStock_OU_ServiceComboBoxes(enum entrer_VISIBLE_CHOICE choice_insert = set_choice_insert_STANDARD_INVENTORY_STOCK);


    void SET___label_stock_dalerte_value_STR();


    void set_PRIX_DE_VENTE_combobBOXLABEL();


    /**
     * !!! SETs whole sale price. IT is called
     * from method 'set_PRIX_DE_VENTE_combobBOXLABEL()'
     * only !!!
     */
    void set_PRIX_DE_VENTE_GROS_combobBOXLABEL();


    void set_PRIX_DE_VENTE_par_Unite_combobBOXLABEL();


    /**
     * !!! SETs whole sale price per unit of measure.
     * IT is called from method
     * 'set_PRIX_DE_VENTE_par_Unite_combobBOXLABEL()' only !!!
     */
    void set_PRIX_DE_VENTE_GROS_par_Unite_combobBOXLABEL();



    YerithLogger *_logger;

    ServiceClientInfo *_currentServiceInfo;


    static const uint PRIX_DE_VENTE_En_Gros_Par_Unite_Index;

    static const uint PRIX_DE_VENTE_En_Gros_Index;

    static const uint PRIX_DE_VENTE_Par_Unite_Index;

    static const uint PRIX_DE_VENTE_Index;


    static const unsigned CURRENT_MAX_DESCRIPTION_TEXT_SIZE_CHARACTER_NUMBER;

    unsigned _stocks_id;



    enum entrer_VISIBLE_CHOICE _Last_choice_insert;

    bool _a_show_ITEM;



    double _montantTva;

    double _montantTva_en_gros;

    bool _INSIDE___handleTVACheckBox;

    bool _INSIDE___handle_ReferenceDesignation_checkBox;

    bool _historique_stock_actif;

    bool _tvaCheckBoxPreviousState;

    QString _lastEditedPrixVente;

    QString _lastEditedPrixVente_en_gros;
};


#endif /* YERITH_ENTRER_WINDOW_HPP_ */
