/*
 * yerith-erp-modifier-groupe-de-clients-window.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_MODIFIER_GROUPE_DE_CLIENTS_WINDOW_HPP_
#define YERITH_MODIFIER_GROUPE_DE_CLIENTS_WINDOW_HPP_


#include "../../../../ui_yerith-erp-modifier-groupe-de-clients-window.h"


#include "src/windows/yerith-erp-window-commons.hpp"


#include <QtWidgets/QMessageBox>


class YerithERPWindows;
class YerithSqlTableModel;

class YerithModifierGroupeDeClientsWindow : public YerithWindowsCommons,
    										private Ui_YerithModifierGroupeDeClientsWindow
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

	YerithModifierGroupeDeClientsWindow();

    inline ~YerithModifierGroupeDeClientsWindow()
    {
        delete _logger;
    }

    inline QToolBar *getQMainWindowToolBar()
    {
        return toolBar_modifierGroupeDeClientsWindow;
    }

    virtual void definirCaissier();

    virtual void definirManager();

    virtual void definirVendeur();

    virtual void definirGestionaireDesStocks();

    virtual void definirMagasinier();

    virtual void definirPasDeRole();

    virtual void rendreInvisible();

    virtual void rendreVisible(YerithSqlTableModel *stocksTableModel);

public slots:

    virtual inline void apropos()
    {
        YerithWindowsCommons::apropos(this);
    }

    virtual inline void help()
    {
        YerithQMessageBox::information(this,
                                       QObject::tr("aide"),
                                       QObject::tr("Remplisser le formulaire, et ensuite cliquer "
                                    		   	   "sur enregistrer !"));
    }

    void deconnecter_utilisateur();


protected:

    virtual void reset_window_widgets_modification_Bit();

    virtual void setupShortcuts();


private slots:

    inline void handle_select_table_widget_row(QTableWidgetItem *anItem)
    {
        _last_selected_table_widget_row = anItem->row();
    }

    bool IS_client_present_dans_un_groupe_de_clients(const QString & aClientGroupMemberName);

    void ajouter_un_membre_au_groupe_de_clients(const QString & aClientGroupMemberName);

    void annuler_la_creation_dun_groupe_de_clients();

    void supprimerUnMembreDunGroupeDeClients();

    bool modifierEnregistrerUnGroupeDeClients();

private:

    void update_client_group_member_data(const QString &new_client_group_designation,
                                         const QString &new_client_group_db_ID,
                                         const QString &client_db_ID);

    inline void setLastSelectedTableWidgetRow(int lastSelectedTableWidgetRow)
    {
        _last_selected_table_widget_row = lastSelectedTableWidgetRow;
    }


    inline bool clientGroupAlreadyExists()
    {
        // ** check if customer account with same name exist
        return
            YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*this,
                                                        _allWindows->getSqlTableModel_groupes_de_clients(),
                                                        *lineEdit_modifier_groupe_clients_recherche_client_initiaux,
                                                        QObject::tr
                                                        ("Un groupe de client"),
                                                        YerithDatabaseTableColumn::
                                                        NOM_ENTREPRISE);
    }


    inline bool YerithModifierGroupeDeClientsWindow::check_fields()
    {
        return lineEdit_modifier_groupe_clients_designation->checkField();
    }


    void clear_all_fields();

    void setupLineEdits();

    void setupLineEditsQCompleters();


    int _last_selected_table_widget_row;

    YerithLogger *_logger;
};


#endif /* YERITH_MODIFIER_GROUPE_DE_CLIENTS_WINDOW_HPP_ */
