/*
 * yerith-erp-changer-utilisateur-dialog.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_CHANGER_UTILISATEUR_DIALOG_
#define YERITH_ERP_CHANGER_UTILISATEUR_DIALOG_

#include "../../ui_yerith-erp-changer-utilisateur-dialog.h"

#include "src/widgets/yerith-erp-push-button-PASSWORD.hpp"

#include "yerith-erp-dialog-commons.hpp"

class YerithERPWindows;
class YerithPOSUser;

class YerithPOSChangerUtilisateurDialog : public YerithPOSDialogCommons,
    									  private Ui_YerithPOSChangerUtilisateurDialog
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

    YerithPOSChangerUtilisateurDialog(YerithERPWindows  *allWindows,
                                      QMainWindow       *parent = 0);

    ~YerithPOSChangerUtilisateurDialog();

    virtual QPoint *getCurrentPosition()
    {
        return _currentPosition;
    }

//signals:

    //void disconnectUser();

public slots:

    virtual inline void SET_user_role()
    {
        valider(true);
    }


    virtual void change_Window_Title(const QString &a_database_remote_location);


    virtual void ___retranslateUi();


    virtual void setup_local_connected_Site();

    virtual void Change_flag_language_Next_TO_TRANSlate();

    void annuler();

    void valider(bool only_set_A_user_role = false);

    virtual void show();


protected slots:

    void switch_language_ComboBoxes();


protected:

    virtual void CACHER_mot_de_passe();

    virtual inline void hideEvent(QHideEvent *hideEvent)
    {
        CACHER_mot_de_passe();
    }

    virtual void closeEvent(QCloseEvent *closeEvent);

private:

    YerithPOSUser *createUser(QSqlRecord &userRecord, int role);

    void checkCourriersAlertes();

    static const QString DIALOG_WINDOW_TITLE;

    QString _window_title_Base;

    QPoint *_currentPosition;

    YerithPushButtonPASSWORD *_push_button_password;

    QList<QString> _langues;

    YerithPOSUser *_user;

};


#endif /* YERITH_ERP_CHANGER_UTILISATEUR_DIALOG_ */
