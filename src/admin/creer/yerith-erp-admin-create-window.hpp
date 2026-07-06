/*
 * yerith-erp-admin-create-window.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ADMIN_CREATE_WINDOW_HPP_
#define YERITH_ADMIN_CREATE_WINDOW_HPP_

#include "../../../ui_yerith-erp-admin-create-window.h"


#include "src/admin/yerith-erp-admin-windows-commons.hpp"


#include <QtWidgets/QMessageBox>


class YerithPushButtonPASSWORD;
class YerithERPWindows;
class YerithLogger;

class YerithAdminCreateWindow : public YerithPOSAdminWindowsCommons,
								private Ui_YerithAdminCreateWindow
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


	YerithAdminCreateWindow();

    virtual inline ~YerithAdminCreateWindow()
    {
    }

    virtual inline QToolBar *getQMainWindowToolBar()
    {
        return toolBar_adminCreateWindow;
    }

    virtual void definirPasDeRole();

    virtual void definirAdministrateur();

    virtual void definirManager();

    virtual void rendreVisible(YerithSqlTableModel *stocksTableModel,
                               unsigned selectedSujetAction,
    						   bool 	a_show_item_CHARGE_FINANCIERE = false,
    						   bool     from_charge_financiere_window = false);


    virtual QString get_currently_Selected_Object_For_WORK();


    virtual void rendreInvisible();


public slots:

    virtual inline void ___retranslateUi()
    {
        retranslateUi(this);
    }


    void showDestinataireNomComplet(const QString &destinataireId);


    inline void HANDLE_lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE(const QString &text_changed)
    {
    	lineEdit_creer_montant_RESTANT_de_la_LIGNE_BUDGETAIRE
			->setText(GET_DOUBLE_STRING(text_changed.toDouble()));
    }


    void HANDLE_comboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE(const QString &text_changed);


    void showProduitInfo(const QString &nomProduit);

    void showDatePeremption(const QString &nomProduit);


    void lister();

    void annuler();


    void handleCurrentChanged();


    virtual inline void creer_utilisateur___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_utilisateur);
    }

    virtual inline void creer_localisation___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_localisation);
    }

    virtual inline void creer_departements_de_produits___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_departements_de_produits);
    }

    virtual inline void creer_categorie___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_categorie);
    }

    virtual inline void creer_charge_financiere___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_charge_financiere);
    }

    virtual inline void creer_ligne_budgetaire___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_ligne_budgetaire);
    }

    virtual inline void creer_compte_bancaire___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_compte_bancaire);
    }

    virtual inline void creer_remise___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_remise);
    }

    virtual inline void creer_alerte___With___PROGRESS_BAR()
    {
        YerithProgressBar (this)
                          (this, &YerithAdminCreateWindow::creer_alerte);
    }



    bool creer_utilisateur();

    bool creer_localisation();

    bool creer_departements_de_produits();

    bool creer_categorie();

    bool creer_charge_financiere();

    bool creer_ligne_budgetaire();

    bool creer_compte_bancaire();

    bool creer_remise();

    bool creer_alerte();


    void radioButtons_quantite();

    void radioButtons_periode_temps();


    virtual inline void help()
    {
        YerithQMessageBox::information(this,
                                       QObject::tr
                                       ("Yerith-pgi-9.0 ~ admin-créer"),
                                       QObject::tr
                                       ("Remplissez les informations nécessaire, et "
                                        "ensuite cliquer sur 'Valider'.\n"
                                        "Cliquez sur 'Annuler' si vous souhaiter annuler "
                                        "l'opération !"), QMessageBox::Ok);
    }


protected slots:

    inline void selectionner_image_Un___utilisateur()
    {
        YerithWindowsCommons::selectionner_image(*label_admin_creer_2_image_utlisateur);
    }

    inline void supprimer_image_Un___utilisateur()
    {
        YerithWindowsCommons::supprimer_image(*label_admin_creer_2_image_utlisateur);
    }

	void calculate_tva_value(const QString &VALEUR_TVA);

	void display_montant_prix_dachat_total(const QString &prix_dachat_alunite);

	void display_montant_prix_dachat_totalby_spinbox(double quantite);


protected:

    virtual void password_push_button_Line_Edit_initializations();


    virtual void reset_window_widgets_modification_Bit____UTILISATEUR();

    virtual void reset_window_widgets_modification_Bit____LOCALISATION();

    virtual void reset_window_widgets_modification_Bit____DEPARTEMENTS_DE_PRODUITS();

    virtual void reset_window_widgets_modification_Bit____CATEGORIE();

    virtual void reset_window_widgets_modification_Bit____CHARGE_FINANCIERE();

    virtual void reset_window_widgets_modification_Bit____LIGNE_BUDGETAIRE();

    virtual void reset_window_widgets_modification_Bit____COMPTE_BANCAIRE();

    virtual void reset_window_widgets_modification_Bit____REMISE();

    virtual void reset_window_widgets_modification_Bit____ALERTE();



    virtual void reset_window_widgets_modification_Bit();

    virtual void hideEvent(QHideEvent *hideEvent);


private slots:

    void swap_values___LABEL_entrees_sorties_DargEnts(QLabel *new_visible_Entrees_Sorties_Dargents_QLABEL);

    void handle_reactiver_departement_CMD_REPETITION(int state);


private:

    void setupValidators();

    void show_item_CHARGE_FINANCIERE(bool from_charge_financiere_window = false);

    void setupLineEdits();

    void setupDateTimeEdits();


    void populateUtilisateurComboBoxes();

    void populateAlerteComboBoxes();

    void populateLocalisationComboBoxes();

    void populate_CHARGE_FINANCIERE_ComboBoxes();

    void populate_LIGNE_BUDGETAIRE_ComboBoxes();

    void populateRemiseComboBoxes();


    void clear_utilisateur_all_fields();

    void clear_departements_de_produits_all_fields();

    void clear_categorie_all_fields();

    void clear_CHARGE_FINANCIERE_all_fields();

    void clear_LIGNE_BUDGETAIRE_all_fields();

    void clear_localisation_all_fields();

    void clear_alerte_all_fields();

    void clear_compte_bancaire_all_fields();

    void clear_remise_all_fields();


    bool creer_utilisateur_check_fields();

    bool creer_departements_de_produits_check_fields();

    bool creer_categorie_check_fields();

    bool creer_charge_financiere_CHECK_fields();

    bool creer_ligne_budgetaire_CHECK_fields();

    virtual inline bool creer_localisation_check_fields()
    {
        return lineEdit_creer_localisation_nom->checkField();
    }

    bool creer_alerte_check_fields();

    bool creer_compte_bancaire_check_fields();

    bool creer_remise_check_fields();


    void creer_utilisateur_check_fields_entry();

    void creer_charge_financiere_check_fields_entry();

    void creer_alerte_check_fields_entry();

    void creer_remise_check_fields_entry();



    static QMap<QString, QLabel *> _ComboBox_label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_Idx___To___labels_PLUS_Minus_signs;

    static QString _Label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_entrees_dargents;

    static QString _Label_creer_MONTANT_DE_LA_LIGNE_BUDGETAIRE_sorties_dargents;


    double _VALEUR_TVA;

    double _MONTANT_TVA_CHARGE_FINANCIERE;

    double _montant_PRIX_DACHAT_TOTAL;

    YerithLogger *_logger;
};

#endif /* YERITH_ADMIN_CREATE_WINDOW_HPP_ */
