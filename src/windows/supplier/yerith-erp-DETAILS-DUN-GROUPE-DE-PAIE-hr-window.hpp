/*
 * yerith-erp-DETAILS-DUN-GROUPE-DE-PAIE-hr-window.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_WINDOWS_YERITH_SUPPLIER_DETAILS_DUN_GROUPE_DE_PAIE_hr_WINDOW_HPP_
#define SRC_WINDOWS_YERITH_SUPPLIER_DETAILS_DUN_GROUPE_DE_PAIE_hr_WINDOW_HPP_

#include "../../../ui_yerith-erp-DETAILS-DUN-GROUPE-DE-PAIE-hr-window.h"

#include "src/utils/yerith-erp-logger.hpp"

#include "src/windows/yerith-erp-window-commons.hpp"

#include <QtWidgets/QMessageBox>


class QContextMenuEvent;

class YerithERPWindows;
class YerithSqlTableModel;
class YerithLogger;

class YerithDetailsDunGroupeDePaieWindow : public YerithWindowsCommons,
    									   private Ui_YerithDetailsDunGroupeDePaieWindow
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

	YerithDetailsDunGroupeDePaieWindow();

    ~YerithDetailsDunGroupeDePaieWindow();

    inline QToolBar *getQMainWindowToolBar()
    {
        return toolBar_YerithDetailsDunGroupeDePaieWindow;
    }

    virtual inline void definirCaissier()
    {
        definirPasDeRole();
    }

    virtual void definirManager();

    virtual inline void definirVendeur()
    {
        definirManager();
    }

    virtual inline void definirGestionaireDesStocks()
    {
        definirPasDeRole();
    }

    virtual inline void definirMagasinier()
    {
        definirPasDeRole();
    }

    virtual void definirPasDeRole();

    virtual void rendreInvisible();

    virtual void rendreVisible(YerithSqlTableModel *curClient_LOYALTY_PROGRAM_TableModel,
                               YerithSqlTableModel *stocksTableModel);

    virtual inline QString NOM_DU_Groupe_de_PAYE_actuel()
    {
        return _Nom_du_groupe_de_PAYE;
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
                                       QObject::tr("Vous pouvez modifier les détails de ce programme de fidélité clients "
                                    		   	   "en cliquant sur 'Modifier' !"));
    }

protected:

    virtual void reset_window_widgets_modification_Bit();

    virtual void setupShortcuts();


private slots:

    bool Modify_Date_JOUR_de_Paye(bool AskConfirmation = true);

    void Cancel__enregistrer___DATE_DE_PAYE();

    void Enregistrer__DATE_DE_PAYE();


private:

    void clear_all_fields();

    void setup_Date_JOUR_de_Paye___GROUPBOX();

    void setupLineEdits();

    void showPayGroup_PROGRAM_DETAIL();



    QString                  _Nom_du_groupe_de_PAYE;


    YerithLogger        *_logger;

    YerithSqlTableModel *_curPAY_GROUP_TableModel;
};


#endif /* SRC_WINDOWS_YERITH_SUPPLIER_DETAILS_DUN_GROUPE_DE_PAIE_hr_WINDOW_HPP_ */
