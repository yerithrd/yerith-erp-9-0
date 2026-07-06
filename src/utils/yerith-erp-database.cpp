/*
 * yerith-erp-database.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-database.hpp"

#include "src/utils/yerith-erp-utils.hpp"



const QString YerithDatabase::PERIODES_DAPPARTENANCE_GROUPES_DE_PAIE_HR("periodes_dappartenance_groupes_de_paie_hr");

const QString YerithDatabase::IMPRIMANTERESEAU_RECUS_PETITS("imprimantereseau_recus_petits");

const QString YerithDatabase::COMPTES_BANCAIRES("comptes_bancaires");

const QString YerithDatabase::OPERATIONS_COMPTABLES("operations_comptables");

const QString YerithDatabase::ENTREPRISE_INFO("entreprise_info");

const QString YerithDatabase::PAIEMENTS("paiements");

const QString YerithDatabase::USERS("users");

const QString YerithDatabase::UNITES_DE_MESURES("unites_DE_MESURES");

const QString YerithDatabase::TITRES("titres");

const QString YerithDatabase::LOCALISATIONS("localisations");

const QString YerithDatabase::DEPARTEMENTS_PRODUITS("departements_produits");

const QString YerithDatabase::CATEGORIES("categories");

const QString YerithDatabase::LIGNES_BUDGETAIRES("LIGNES_BUDGETAIRES");

const QString YerithDatabase::PROGRAMMES_DE_FIDELITE_CLIENTS("programmes_de_fidelite_clients");

const QString YerithDatabase::GROUPES_DEMPLOYES_hr("groupes_demployes_hr");

const QString YerithDatabase::GROUPES_DE_PAIE_hr("groupes_de_paie_hr");

const QString YerithDatabase::CLIENTS("clients");

const QString YerithDatabase::GROUPES_DE_CLIENTS("groupes_de_clients");

const QString YerithDatabase::FOURNISSEURS("fournisseurs");

const QString YerithDatabase::ALERTES("alertes");

const QString YerithDatabase::REMISES("remises");

const QString YerithDatabase::CREDIT_CARD_ISSUING_COMPANY("credit_card_issuing_company");

const QString YerithDatabase::CONDITIONS_ALERTES("conditions_alertes");

const QString YerithDatabase::COURRIERS_ALERTES("courriers_alertes");

const QString YerithDatabase::CHARGES_FINANCIERES("charges_financieres");

const QString YerithDatabase::ACHATS("achats");

const QString YerithDatabase::STOCKS("stocks");

const QString YerithDatabase::SERVICES_COMPLETES("services_completes");

const QString YerithDatabase::STOCKS_VENDU("stocks_vendu");

const QString YerithDatabase::STOCKS_SORTIES("stocks_sorties");

const QString YerithDatabase::MARCHANDISES("marchandises");

const QString YerithDatabase::CONFIGURATIONS("configurations");

const QString YerithDatabase::INIT_CONFIGURATIONS("init_configurations");

const QString YerithDatabase::YRI_DB_RUNTIME_VERIF("yri_db_runtime_verif");

const QString YerithDatabase::TYPE_DOPERATIONS_FINANCIERES("type_doperations_financieres");

const QString YerithDatabase::TYPE_DE_VENTE("type_de_vente");

const QString YerithDatabase::TYPE_DE_PAIEMENT("type_de_paiement");

const QString YerithDatabase::ROLES("roles");

const QString YerithDatabase::DBMS("dbms");


const QString YerithDatabase::MYSQL("MySQL");

const QString YerithDatabase::QSQLITE("QSQLITE");

QString YerithDatabase::_db_type("");

QString YerithDatabase::_db_name("");

QString YerithDatabase::_db_ip_address("");

QString YerithDatabase::_db_user_name("");

QString YerithDatabase::_db_user_pwd("");

QString YerithDatabase::_db_connection_options("");


YerithDatabase::YerithDatabase()
{
    set_db_name(YerithERPConfig::_db_name);
    set_db_ip_address(YerithERPConfig::_db_ip_address);
    set_db_user_name(YerithERPConfig::_db_user_name);
    set_db_user_pwd(YerithERPConfig::_db_user_pwd);
    set_db_type(YerithERPConfig::_db_type);
    set_db_connection_options(YerithERPConfig::_db_connection_options);

    if (YerithUtils::isEqualCaseInsensitive(YerithDatabase::MYSQL,
                                            YerithERPConfig::_db_type))
    {
        //logger << "++ main(): QMYSQL" << "\n";
        _database = QSqlDatabase::addDatabase("QMYSQL");
    }
    else if (YerithUtils::isEqualCaseInsensitive(YerithDatabase::QSQLITE,
                                                 YerithERPConfig::_db_type))
    {
        //logger << "++ main(): QSQLITE" << "\n";
        _database = QSqlDatabase::addDatabase("QSQLITE");
    }

    _database.setDatabaseName(_db_name);
    _database.setHostName(_db_ip_address);
    _database.setUserName(_db_user_name);
    _database.setPassword(_db_user_pwd);
    _database.setConnectOptions(_db_connection_options);
}


bool YerithDatabase::switch___CLOSE____Database__Localisation(QString A_user_Entered_Previous_NOM_LOCALISATION,
                                                              QString A_user_Entered_Current_NOM_LOCALISATION)
{
    bool a_new_current_db_name_OPENED = false;

    YerithDatabase *a_database_instance = YerithUtils::getDatabase();

    if (0 != a_database_instance &&
        YerithUtils::isEqualCaseInsensitive(A_user_Entered_Previous_NOM_LOCALISATION,
                                            a_database_instance->db_name()))
    {
        a_database_instance->close();

        a_database_instance->set_db_name(A_user_Entered_Current_NOM_LOCALISATION);

        a_new_current_db_name_OPENED =
            YerithDatabase::switch___OPEN____Database__Localisation
                                (A_user_Entered_Current_NOM_LOCALISATION);
    }

//    QDEBUG_STRING_OUTPUT_2_BOOL(QString("'%1 database' was opened : %1")
//                                  .arg(A_user_Entered_Current_NOM_LOCALISATION),
//                                 a_new_current_db_name_OPENED);

    return a_new_current_db_name_OPENED;
}


bool YerithDatabase::switch___OPEN____Database__Localisation(QString A_user_Entered_nom_localisation)
{
    bool a_new_current_db_name_OPENED = false;

    YerithDatabase *a_database_instance = YerithUtils::getDatabase();

    if (0 != a_database_instance)
    {
        a_database_instance->close();

        a_database_instance->set_db_name(A_user_Entered_nom_localisation);

        a_new_current_db_name_OPENED = a_database_instance->open();
    }

//    QDEBUG_STRING_OUTPUT_2_BOOL(QString("'%1 database' was opened : %1")
//                                  .arg(A_user_Entered_nom_localisation),
//                                 a_new_current_db_name_OPENED);

    return a_new_current_db_name_OPENED;
}


bool YerithDatabase::
        Create___Database__Tables___Localisation(QString an_Entered_nom_localisation,
                                                 bool    initialization_LIST___repeat___Once /* = false */,
                                                 bool    an_Entered_nom_localisation___Keep_OPEN /* = true */)
{
    if (switch___OPEN____Database__Localisation(an_Entered_nom_localisation))
    {
        QStringList sql_table_list;

#ifdef YERITH_FEATURES_COMPTABILITE_yes
        sql_table_list
                << FILE_YERITH_ERP_3_0_SQL_TABLE_OPERATIONS_COMPTABLES;
#endif
        sql_table_list
                << FILE_YERITH_ERP_3_0_SQL_TABLE_periodes_dappartenance_groupes_de_paie_hr
                << FILE_YERITH_ERP_3_0_SQL_TABLE_groupes_demployes_hr
                << FILE_YERITH_ERP_3_0_SQL_TABLE_groupes_de_paie_hr
                << FILE_YERITH_ERP_3_0_SQL_TABLE_TYPE_DOPERATIONS_FINANCIERES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_COMPTES_BANCAIRES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_ENTREPRISE_INFO
                << FILE_YERITH_ERP_3_0_SQL_TABLE_TYPE_DE_VENTE
                << FILE_YERITH_ERP_3_0_SQL_TABLE_TYPE_DE_PAIEMENT
                << FILE_YERITH_ERP_3_0_SQL_TABLE_PAIEMENTS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_CREDIT_CARD_ISSUING_COMPANY
                << FILE_YERITH_ERP_3_0_SQL_TABLE_INIT_CONFIGURATION
                << FILE_YERITH_ERP_3_0_SQL_TABLE_YRI_DB_RUNTIME_VERIF
                << FILE_YERITH_ERP_3_0_SQL_TABLE_CONFIGURATIONS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_ROLES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_USERS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_UNITES_DE_MESURES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_TITRES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_LOCALISATIONS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_CHARGES_FINANCIERES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_YRI_DB_RUNTIME_VERIF
                << FILE_YERITH_ERP_3_0_SQL_TABLE_ACHATS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_STOCKS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_SERVICES_COMPLETES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_MARCHANDISES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_STOCKS_VENDU
                << FILE_YERITH_ERP_3_0_SQL_TABLE_STOCKS_SORTIES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_ALERTES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_REMISES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_CONDITIONS_ALERTES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_COURRIERS_ALERTES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_PROGRAMMES_DE_FIDELITES_CLIENTS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_GROUPES_DE_CLIENTS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_CLIENTS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_SALAIRES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_FOURNISSEURS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_IMPRIMANTERESEAU_RECUS_PETITS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_DBMS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_DEPARTEMENTS_PRODUITS
                << FILE_YERITH_ERP_3_0_SQL_TABLE_CATEGORIES
                << FILE_YERITH_ERP_3_0_SQL_TABLE_LIGNES_BUDGETAIRES;


    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;

        if (initialization_LIST___repeat___Once)
        {
//            QDEBUG_STRING_OUTPUT_1
//                ("YerithDatabase::Create___Database__Tables___Localisation | initialization_LIST___repeat___Once.");

            for (int k = 0; k < sql_table_list.size(); ++k)
            {
                YerithUtils::executer_fichier_sql(sql_table_list.at(k));
            }
        }
        else
        {
            QString add_localization_site_query_Str =
                        QString("Insert into %1 (%2, %3, %4) values (%5, '%6', '%7')")
                          .arg(YerithDatabase::LOCALISATIONS,
                                YerithDatabaseTableColumn::ID,
                                YerithDatabaseTableColumn::NOM_LOCALISATION,
                                YerithDatabaseTableColumn::ADRESSE_IP,
                                "0",
                                 an_Entered_nom_localisation,
                                "127.0.0.1");

            for (uint i = 0; i < 4; ++i)
            {
                for (int k = 0; k < sql_table_list.size(); ++k)
                {
                    YerithUtils::executer_fichier_sql(sql_table_list.at(k));
                }
            }

            for (uint i = 0; i < 2; ++i)
            {
                YerithUtils::execQuery(add_localization_site_query_Str);
            }

        }

    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;

//        QDEBUG_STRING_OUTPUT_2("YerithERPConfig::THIS_SITE_LOCALISATION_NAME; an_Entered_nom_localisation; an_Entered_nom_localisation___Keep_OPEN",
//                                QString("%1; %2; %3")
//                                  .arg(YerithERPConfig::THIS_SITE_LOCALISATION_NAME,
//                                       an_Entered_nom_localisation,
//                                       BOOL_TO_STRING(an_Entered_nom_localisation___Keep_OPEN)));


        bool creating_a_new_site_db =
                ! YerithUtils::isEqualCaseInsensitive(YerithERPConfig::THIS_SITE_LOCALISATION_NAME,
                                                      an_Entered_nom_localisation)                  &&
                ! an_Entered_nom_localisation___Keep_OPEN;


//        QDEBUG_STRING_OUTPUT_2_BOOL("creating_a_new_site_db",
//                                     creating_a_new_site_db);


        if (creating_a_new_site_db)
        {
            YerithDatabase::switch___CLOSE____Database__Localisation
                                (an_Entered_nom_localisation,
                                 YerithERPConfig::THIS_SITE_LOCALISATION_NAME);
        }


//        QDEBUG_STRING_OUTPUT_1
//            (QString("YerithDatabase::Create___Database__Tables___Localisation(%1) : True.")
//                .arg(an_Entered_nom_localisation));

        return true;
    }


//    QDEBUG_STRING_OUTPUT_1
//        (QString("YerithDatabase::Create___Database__Tables___Localisation(%1) : FALSE.")
//            .arg(an_Entered_nom_localisation));


    return false;
}


void YerithDatabase::set_db_name(const QString &db_name)
{
    _db_name = db_name;
    _database.setDatabaseName(_db_name);
}


void YerithDatabase::set_db_ip_address(const QString &db_ip_address)
{
    _db_ip_address = db_ip_address;
    _database.setHostName(_db_ip_address);
}


void YerithDatabase::set_db_user_name(const QString &db_user_name)
{
    _db_user_name = db_user_name;
    _database.setUserName(_db_user_name);
}


void YerithDatabase::set_db_user_pwd(const QString &db_user_pwd)
{
    _db_user_pwd = db_user_pwd;
    _database.setPassword(_db_user_pwd);
}


void YerithDatabase::set_db_connection_options(const QString &
                                               db_connection_options)
{
    _db_connection_options = db_connection_options;
    _database.setConnectOptions(_db_connection_options);

}


QString YerithDatabase::toString() const
{
    QString ret;

    if (_database.isValid())
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            _database.
                                                            databaseName(),
                                                            _database.
                                                            hostName(),
                                                            _database.
                                                            connectOptions
                                                            ()));
    }
    else
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            YerithDatabase::
                                                            _db_name,
                                                            YerithDatabase::
                                                            _db_ip_address,
                                                            YerithDatabase::
                                                            _db_connection_options));
    }

    return ret;
}

