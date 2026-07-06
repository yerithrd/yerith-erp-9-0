/*
 * yerith-erp-dialog-changer-utilisateur.cpp
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "src/yerith-erp-windows.hpp"


#include "src/windows/yerith-erp-main-window.hpp"

#include "yerith-erp-changer-utilisateur-dialog.hpp"

#include "src/users/yerith-erp-users.hpp"

#include "src/users/yerith-erp-user-manager.hpp"

#include "src/users/yerith-erp-user-vendeur.hpp"

#include "src/users/yerith-erp-user-gestionaire-des-stocks.hpp"

#include "src/users/yerith-erp-user-magasinier.hpp"

#include "src/users/yerith-erp-user-caissier.hpp"

#include "src/users/yerith-erp-user-administrateur.hpp"


#include <QtWidgets/QDesktopWidget>

#include <QtWidgets/QMainWindow>

#include <QtSql/QSqlQuery>

#include <QtSql/QSqlRecord>

#include <QtSql/QSqlError>



const QString YerithPOSChangerUtilisateurDialog::DIALOG_WINDOW_TITLE(QString("%1 - %2")
                                                                        .arg(GET_YERITH_ERP_WINDOW_TITLE_MACRO,
                                                                             QObject::tr("changer d'utilisateur")));

YerithPOSChangerUtilisateurDialog::YerithPOSChangerUtilisateurDialog(YerithERPWindows *allWindows,
																	 QMainWindow *parent)
:YerithPOSDialogCommons(YerithPOSChangerUtilisateurDialog::DIALOG_WINDOW_TITLE),
 _currentPosition(new QPoint),
 _push_button_password(0),
 _user(0)
{
    setupUi(this);


    lineEdit_utilisateur_role->setYerithEnabled(false);


    _window_title_Base = windowTitle();


    QDesktopWidget &desktopWidget = _allWindows->desktopWidget();

    YerithUtils::getCenterPosition(desktopWidget.width(),
                                   desktopWidget.height(),
                                   *this,
                                   *_currentPosition);

    lineEdit_mot_passe->setEchoMode(QLineEdit::Password);


    _langues.append(YerithUtils::English_STRING);
    _langues.append(YerithUtils::FRANCAIS_STRING);

    comboBox_langue->addItems(_langues);


    setFixedSize(width(), height());


    connect(comboBox_langue,
            SIGNAL(currentTextChanged(const QString &)),
            this,
            SLOT(switch_language_ComboBoxes()));


    connect(lineEdit_nom_utilisateur,
            SIGNAL(editingFinished()),
            this,
            SLOT(SET_user_role()));


    connect(comboBox_company_site,
            SIGNAL(currentTextChanged(const QString &)),
            this,
            SLOT(change_Window_Title(const QString &)));


    connect(pushButton_annuler, SIGNAL(clicked()), this, SLOT(annuler()));
    connect(pushButton_valider, SIGNAL(clicked()), this, SLOT(valider()));


    _push_button_password = new YerithPushButtonPASSWORD(this,
                                                         lineEdit_mot_passe,
                                                         pushButton_cacher_le_mot_de_passe,
                                                         pushButton_voir_le_mot_de_passe);

    comboBox_company_site->setYerithEditable(true);
}


YerithPOSChangerUtilisateurDialog::~YerithPOSChangerUtilisateurDialog()
{
    delete _currentPosition;

    YERITH_DELETE_FREE_POINTER_NOW(_push_button_password);

    if (_user)
    {
        delete _user;

        _user = 0;
    }
}


void YerithPOSChangerUtilisateurDialog::change_Window_Title(const QString &a_database_remote_location)
{
    SET_user_role();

    setWindowTitle(QString("%1 --- ''%2''")
                   .arg(_window_title_Base,
                        a_database_remote_location));
}


void YerithPOSChangerUtilisateurDialog::___retranslateUi()
{
    retranslateUi(this);

    YerithUtils::RELOAD_VIEW_STRINGS();
}


void YerithPOSChangerUtilisateurDialog::setup_local_connected_Site()
{
    YerithERPConfig::_distantSiteConnected = false;
    YerithERPConfig::_connectedSiteIPAddress = "127.0.0.1";
    YerithERPConfig::_connectedSite = comboBox_company_site->currentText();

    change_Window_Title(YerithERPConfig::_connectedSite);
}


void YerithPOSChangerUtilisateurDialog::Change_flag_language_Next_TO_TRANSlate()
{
    if (0 != _allWindows)
    {
        ___retranslateUi();

        _allWindows->_mainWindow->CHANGER_DE_LANGUE__text__TRANSLATION(_allWindows->_mainWindow);
    }
}


void YerithPOSChangerUtilisateurDialog::annuler()
{
    lineEdit_utilisateur_role->clear();

    if (0 != _push_button_password)
    {
        _push_button_password->cacher_le_mot_de_passe();
    }

    close();
}


void YerithPOSChangerUtilisateurDialog::valider(bool only_set_A_user_role /* = false */)
{
     ___retranslateUi();


    if (! YerithUtils::isEqualCaseInsensitive("admin",
                                             lineEdit_nom_utilisateur->text())  &&
        comboBox_company_site->isEmpty())
    {
        if (! only_set_A_user_role)
        {
            YerithQMessageBox::information(_allWindows->_mainWindow,
                                           QObject::tr("Localisation non determinée"),
                                           QObject::tr("VEUILLEZ selectionner - inscrire 1 localisation \n"
                                                       "Dans le champs de texte 'société (site)' !"));

            return ;
        }
    }


    QString user_Entered_nom_localisation;

    if (! YerithERPConfig::THIS_SITE_LOCALISATION_NAME.isEmpty() &&
            ! YerithUtils::isEqualCaseInsensitive("THIS_SITE_LOCALISATION_HARD_CODED_BY_DEVELOPER_FOR_MAXIMUM_BENEFIT_FOR_CLIENT",
                                                   YerithERPConfig::THIS_SITE_LOCALISATION_NAME) )
    {

        YerithSqlTableModel & a_localisation_TableSqlTableModel =
                                _allWindows->getSqlTableModel_localisations();

        user_Entered_nom_localisation = comboBox_company_site->currentText();

        a_localisation_TableSqlTableModel
            .yerithSetFilter_WITH_where_clause
                (QString("%1 = '%2' AND %3 = '%4'")
                     .arg(YerithDatabaseTableColumn::NOM_LOCALISATION,
                          user_Entered_nom_localisation,
                          YerithDatabaseTableColumn::ADRESSE_IP,
                          "127.0.0.1"));


        int a_localisation_TableSqlTableModel__query_count =
                    a_localisation_TableSqlTableModel
                            .easySelect("src/dialogs/yerith-erp-changer-utilisateur-dialog.cpp",
                                        173);

        if (a_localisation_TableSqlTableModel__query_count > 0)
        {
            YerithDatabase &a_database_instance = _allWindows->getDatabase();

            if (YerithDatabase::Create___Database__Tables___Localisation(user_Entered_nom_localisation,
                                                                         true))
            {
                YerithERPConfig::THIS_SITE_LOCALISATION_NAME = user_Entered_nom_localisation;
            }
        }
    }
    else
    {
        if (! only_set_A_user_role)
        {
            YerithQMessageBox::information(_allWindows->_mainWindow,
                                           QObject::tr("II.] Localisation non determinée"),
                                           QObject::tr("VEUILLEZ selectionner - inscrire 1 localisation \n"
                                                       "Dans le champs de texte 'société (site)' !"));
        }

        return ;
    }


    QString mot_passe = lineEdit_mot_passe->text();

    QString nom_utilisateur = lineEdit_nom_utilisateur->text().toLower();



    QString searchUserFilter;


    YerithSqlTableModel &usersSqlTableModel = _allWindows->getSqlTableModel_users();

    searchUserFilter.append(GENERATE_SQL_IS_STMT
                            (YerithDatabaseTableColumn::NOM_UTILISATEUR,
                             nom_utilisateur));

    usersSqlTableModel.yerithSetFilter_WITH_where_clause(searchUserFilter);


    int usersSqlTableModelRowCount =
            usersSqlTableModel.easySelect("src/dialogs/yerith-erp-changer-utilisateur-window.cpp",
                                           225);


    int role = YerithUtils::ROLE_INDEFINI;


    QString a_user_role_String = QObject::tr("UTILISATEUR non existant !");


    QSqlRecord userRecord;


    if (usersSqlTableModelRowCount > 0)
    {
        userRecord = usersSqlTableModel.record(0);

        role = GET_SQL_RECORD_DATA(userRecord,
                                   YerithDatabaseTableColumn::ROLE).toInt();

        if (YerithUtils::ROLE_ADMINISTRATEUR        == role ||
            YerithUtils::ROLE_CAISSIER              == role ||
            YerithUtils::ROLE_MAGASINIER            == role ||
            YerithUtils::ROLE_MANAGER               == role ||
            YerithUtils::ROLE_VENDEUR               == role ||
            YerithUtils::ROLE_GESTIONNAIREDESTOCK   == role)
        {
            a_user_role_String = YerithUtils::_roleToUserViewString.value(role);
        }
    }


    lineEdit_utilisateur_role->setText(a_user_role_String.toUpper());


    if (only_set_A_user_role)
    {
        return ;
    }


    if (!mot_passe.isEmpty())
    {
        mot_passe.append(nom_utilisateur);

        QByteArray md5Hash_mot_passe(MD5_HASH(mot_passe));

        if (usersSqlTableModelRowCount > 0)
        {
            QByteArray md5Hash(userRecord.value("mot_passe").toByteArray());

            if (md5Hash != md5Hash_mot_passe)
            {
                YerithQMessageBox::information(_allWindows->_mainWindow,
                                               QObject::tr("enregistrement de l'utilisateur"),
                                               QObject::tr("Votre nom d'utilisateur "
                                                           "ou bien votre mot de passe "
                                                           "est incorrect !"));
                return;
            }


            YerithPOSUser *user = createUser(userRecord, role);

            if (!user)
            {
                YerithQMessageBox::information(_allWindows->_mainWindow,
                                               QObject::tr("enregistrement de l'utilisateur"),
                                               QObject::tr("Votre nom d'utilisateur "
                                                           "ou bien votre mot de passe "
                                                           "est incorrect !"));
                return;
            }

            if (_user)
            {
                delete _user;
            }

            _user = user;


            //Check if the user has new alerts.
            checkCourriersAlertes();

            _allWindows->CURRENTLY_CHANGING_USER = true;

            _allWindows->_mainWindow->cleanupAllOtherWindows();

            _allWindows->CURRENTLY_CHANGING_USER = false;

            _allWindows->setUser(user);


            if (YerithUtils::ROLE_ADMINISTRATEUR == role)
            {
                _allWindows->_mainWindow->rendreInvisible();
                _allWindows->_mainWindow->definirAdministrateur();

                setup_local_connected_Site();

                _allWindows->_adminWindow
                                ->rendreVisible(&_allWindows->getSqlTableModel_stocks());
            }
            else if (YerithUtils::ROLE_CAISSIER == role)
            {
                _allWindows->_mainWindow->rendreInvisible();
                _allWindows->_ventesWindow->resetFilter(&_allWindows->
                                                        getSqlTableModel_stocks_vendu
                                                        ());

                setup_local_connected_Site();

                _allWindows->_pdVenteWindow->rendreVisible(&_allWindows->
                                                           getSqlTableModel_stocks
                                                           ());
            }
            else if (YerithUtils::ROLE_MAGASINIER == role)
            {
                setup_local_connected_Site();

                _allWindows->_mainWindow->rendreVisible(&_allWindows->
                                                        getSqlTableModel_stocks
                                                        ());
            }
            else if (YerithUtils::ROLE_VENDEUR == role)
            {
                _allWindows->_ventesWindow->resetFilter(&_allWindows->
                                                        getSqlTableModel_stocks_vendu
                                                        ());

                setup_local_connected_Site();

                _allWindows->_mainWindow->rendreVisible(&_allWindows->
                                                        getSqlTableModel_stocks
                                                        ());
            }
            else if (YerithUtils::ROLE_GESTIONNAIREDESTOCK == role)
            {
                setup_local_connected_Site();

                _allWindows->_mainWindow->rendreVisible(&_allWindows->
                                                        getSqlTableModel_stocks
                                                        ());
            }
            else			//YerithUtils::ROLE_MANAGER
            {
                //qDebug() << "++ YerithUtils::ROLE_MANAGER";
                //qDebug() << "++ _allWindows->_caisseWindow: " << _allWindows->_caisseWindow;
                _allWindows->_ventesWindow->resetFilter(&_allWindows->
                                                        getSqlTableModel_stocks_vendu
                                                        ());

                if (!comboBox_company_site->isEmpty())
                {
                	YerithUtils::slot_connecter_localisation(*this,
                                                         	 _allWindows,
															 comboBox_company_site->currentText(),
															 false);
                }

                //qDebug() << "++ YerithUtils::ROLE_MANAGER, _allWindows->_caisseWindow->resetFilter()";

                setup_local_connected_Site();

                _allWindows->_mainWindow->rendreVisible(&_allWindows->
                                                        getSqlTableModel_stocks());
            }

            close();
        }
        else
        {
            YerithQMessageBox::information(_allWindows->_mainWindow,
                                           QObject::tr("enregistrement de l'utilisateur"),
                                           QObject::tr("Votre nom d'utilisateur "
                                                       "ou bien votre mot de passe "
                                                       "est incorrect !"));
            return;
        }
    }
    else
    {
        YerithQMessageBox::information(_allWindows->_mainWindow,
                                       QObject::tr("enregistrement de l'utilisateur"),
                                       QObject::tr("Votre nom d'utilisateur "
                                                   "ou bien votre mot de passe "
                                                   "est incorrect !"));
    }
}


YerithPOSUser *YerithPOSChangerUtilisateurDialog::createUser(QSqlRecord &userRecord,
                                                             int role)
{
    YerithPOSUser *user = 0;

    if (YerithUtils::ROLE_MANAGER == role)
    {
        user = new YerithPOSUserManager(_allWindows);
    }
    if (YerithUtils::ROLE_VENDEUR == role)
    {
        user = new YerithERPUserVendeur(_allWindows);
    }
    if (YerithUtils::ROLE_GESTIONNAIREDESTOCK == role)
    {
        user = new YerithPOSUserGestionaireDesStocks(_allWindows);
    }
    else if (YerithUtils::ROLE_MAGASINIER == role)
    {
        user = new YerithPOSUserMagasinier(_allWindows);
    }
    else if (YerithUtils::ROLE_CAISSIER == role)
    {
        user = new YerithPOSUserCaissier(_allWindows);
    }
    else if (YerithUtils::ROLE_ADMINISTRATEUR == role)
    {

#ifdef YERITH_CLIENT
        QString retMsg(QObject::tr
                       ("La version cliente de YERITH ne vous donne pas accès à l'administration !"));

        QMessageBox::information(this,
                                 QObject::tr
                                 ("pas d'accès à l'administration"), retMsg);
        return 0;
#endif

        user = new YerithPOSUserAdministrateur(_allWindows);
    }

    if (0 != user)
    {
        user->set_nom_utilisateur(GET_SQL_RECORD_DATA
                                  (userRecord,
                                   YerithDatabaseTableColumn::NOM_UTILISATEUR));
        user->set_prenom(GET_SQL_RECORD_DATA
                         (userRecord, YerithDatabaseTableColumn::PRENOM));
        user->set_nom(GET_SQL_RECORD_DATA
                      (userRecord, YerithDatabaseTableColumn::NOM));
        user->set_lieu_naissance(GET_SQL_RECORD_DATA
                                 (userRecord,
                                  YerithDatabaseTableColumn::LIEU_NAISSANCE));
        user->set_date_naissance(GET_SQL_RECORD_DATA
                                 (userRecord,
                                  YerithDatabaseTableColumn::DATE_NAISSANCE));
        user->set_localisation(GET_SQL_RECORD_DATA
                               (userRecord,
                                YerithDatabaseTableColumn::LOCALISATION));
        user->set_email(GET_SQL_RECORD_DATA
                        (userRecord, YerithDatabaseTableColumn::EMAIL));
        user->set_numero_telephone_1(GET_SQL_RECORD_DATA
                                     (userRecord,
                                      YerithDatabaseTableColumn::
                                      NUMERO_TELEPHONE_1));
        user->
        set_numero_telephone_2(GET_SQL_RECORD_DATA
                               (userRecord,
                                YerithDatabaseTableColumn::
                                NUMERO_TELEPHONE_2));

        user->set_titre(YerithUtils::_titreToUserViewString.
                        value(GET_SQL_RECORD_DATA
                              (userRecord,
                               YerithDatabaseTableColumn::TITRE).toInt()));

        user->set_nom_complet(QString("%1 %2").arg(user->prenom(),
                                                   user->nom()));
    }

    return user;
}


void YerithPOSChangerUtilisateurDialog::checkCourriersAlertes()
{
    YerithSqlTableModel &courriersAlertesTable =
                    _allWindows->getSqlTableModel_courriers_alertes();

    QString
    courriersAlertesFilter(GENERATE_SQL_IS_STMT
                           (YerithDatabaseTableColumn::DESTINATAIRE,
                            lineEdit_nom_utilisateur->text()));

    courriersAlertesFilter.append(" AND ").append(GENERATE_SQL_IS_STMT
                                                  (YerithDatabaseTableColumn::ALERTE_RESOLUE,
                                                   "0"));
    courriersAlertesTable.
    yerithSetFilter_WITH_where_clause(courriersAlertesFilter);

    int alertsNr = courriersAlertesTable.rowCount();

    if (courriersAlertesTable.select() && alertsNr > 0)
    {
        QApplication::beep();

        QString aMsg = QObject::tr("Vous avez '%1' alertes non résolues !")
                        .arg(QString::number(courriersAlertesTable.rowCount()));

        YerithQMessageBox::information(_allWindows->_listerAlertesWindow,
                                       QObject::tr("changer d'utilisateur - alertes"),
                                       aMsg);
    }
}


void YerithPOSChangerUtilisateurDialog::show()
{
    ___retranslateUi();

    comboBox_company_site
            ->populateComboBoxRawString(YerithDatabase::LOCALISATIONS,
                                        YerithDatabaseTableColumn::NOM_LOCALISATION);

    if (0 < comboBox_company_site->count())
    {
        comboBox_company_site->setCurrentIndex(1);

        lineEdit_nom_utilisateur->setFocus();
    }
    else
    {
        comboBox_company_site->setFocus();
    }


    move(*_currentPosition);


    change_Window_Title(comboBox_company_site->currentText());


    YerithPOSDialogCommons::show();
}


void YerithPOSChangerUtilisateurDialog::switch_language_ComboBoxes()
{
    if (YerithMainWindow::LANGUE_ANGLAISE)
    {
        setVisible(false);

        QString francais_langue = _langues.at(0);

        if (comboBox_langue->currentText() == francais_langue)
        {
            _allWindows->_mainWindow->Change_flag_language_Next_TO_TRANSlate();
        }
        else
        {
            QString engLISH_language = _langues.at(1);

            if (comboBox_langue->currentText() == engLISH_language)
            {
                _allWindows->_mainWindow->Change_flag_language_Next_TO_TRANSlate();
            }
        }

        valider(true);

        setVisible(true);
    }
    else
    {
         setVisible(false);

         QString engLISH_language = _langues.at(1);

         if (comboBox_langue->currentText() == engLISH_language)
         {
             _allWindows->_mainWindow->Change_flag_language_Next_TO_TRANSlate();
         }
         else
         {
             QString francais_langue = _langues.at(0);

             if (comboBox_langue->currentText() == francais_langue)
             {
                 _allWindows->_mainWindow->Change_flag_language_Next_TO_TRANSlate();
             }
         }

         valider(true);

         setVisible(true);
    }
}

void YerithPOSChangerUtilisateurDialog::CACHER_mot_de_passe()
{
    if (0 != _push_button_password)
    {
        _push_button_password->cacher_le_mot_de_passe();
    }
}


void YerithPOSChangerUtilisateurDialog::closeEvent(QCloseEvent *closeEvent)
{
    lineEdit_utilisateur_role->clear();
    lineEdit_nom_utilisateur->clear();
    lineEdit_mot_passe->clear();
    comboBox_company_site->setFocus();

    CACHER_mot_de_passe();

    YerithPOSDialogCommons::closeEvent(closeEvent);
}


