/*
 * yerith-erp-bank-account-info-raw-import.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-bank-account-info-raw-import.hpp"


#include "src/utils/yerith-erp-historique-stock.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/utils/yerith-erp-database-table-column.hpp"

#include "src/widgets/yerith-erp-qmessage-box.hpp"


#include <QtCore/QDebug>


QString YerithERPbankaccountINFOrawImport::_allMissingMandatoryColumnValue;


QMap<QString, bool> *YerithERPbankaccountINFOrawImport::_dbTableColumnToIsNotNULL;



YerithERPbankaccountINFOrawImport::YerithERPbankaccountINFOrawImport(QStringList                                     &aCurCsvFileToImportContentWordList,
                                                                     QMap<int, YerithERPDatabaseTableColumnInfo *>   &aCsvContentIdxToDatabaseTableColumnInfo)
:YerithERPAllCOMMONImport(aCurCsvFileToImportContentWordList,
                          aCsvContentIdxToDatabaseTableColumnInfo)
{
    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE);

    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE);

    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::INSTITUT_BANCAIRE);

    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::DESCRIPTION_DU_COMPTE_BANCAIRE);
}


YerithERPbankaccountINFOrawImport::YerithERPbankaccountINFOrawImport(YerithPOSAdminWindowsCommons                   &aCallingWindow,
                                                                     QStringList                                    &aCurCsvFileToImportContentWordList,
                                                                     QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo)
:YerithERPAllCOMMONImport(aCallingWindow,
                          aCurCsvFileToImportContentWordList,
                          aCsvContentIdxToDatabaseTableColumnInfo)
{
    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE);

    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE);

    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::INSTITUT_BANCAIRE);

    _allMandatoryTableColumns.append(YerithDatabaseTableColumn::DESCRIPTION_DU_COMPTE_BANCAIRE);
}


//int YerithERPbankaccountINFOrawImport::import(bool importerParlant /* = false */)
//{
//    YerithERPbankaccountINFOrawImport::_allMissingMandatoryColumnValue.clear();
//
//    QString warnMesg;
//
//    if (_curCsvFileToImportContentWordList->size() <= 1)
//    {
//        if (0 != _callingWindow)
//        {
//            warnMesg = QObject::tr("Le fichier CSV n'a pas de données à importer !");
//
//            YerithQMessageBox::warning(_callingWindow,
//                                       QObject::tr("fichier CSV vide"),
//                                       warnMesg);
//        }
//
//        return 0;
//    }
//
//
//    QStringList csvHeader = _curCsvFileToImportContentWordList->at(0)
//                                .split(YerithUtils::CSV_FILE_SEPARATION_SEMI_COLON_STRING_CHAR);
//
//
//    QString curSqlTableImportHeaderStr;
//
//    YerithERPDatabaseTableColumnInfo *curDatabaseTableColumnInfo = 0;
//
//    int curCsvFileColumnSize = csvHeader.size();
//
//    /*
//     * check if '2 csv columns' are mapped to
//     * a same database table import-column.
//     */
//
//    for (int i = 0; i < curCsvFileColumnSize; ++i)
//    {
//        curDatabaseTableColumnInfo = _csvContentIdxToDatabaseTableColumnInfo->value(i);
//
////              qDebug() << "++ curDatabaseTableColumnInfo: " << curDatabaseTableColumnInfo;
//
//        if (0 != curDatabaseTableColumnInfo)
//        {
//            curSqlTableImportHeaderStr = curDatabaseTableColumnInfo->getColumnName();
//
////                      qDebug() << "++ curSqlTableImportHeaderStr: " << curSqlTableImportHeaderStr;
//
//            if (!_allSqlTableImportColumns.contains(curSqlTableImportHeaderStr, Qt::CaseInsensitive))
//            {
//                _allSqlTableImportColumns.append(curSqlTableImportHeaderStr);
//            }
//            else
//            {
//                if (0 != _callingWindow)
//                {
//                    warnMesg = QObject::tr("La colone '%1' apparaît "
//                                           "plusieurs fois parmis les "
//                                           "colones d'importation !").arg(curSqlTableImportHeaderStr);
//
//                    YerithQMessageBox::warning(_callingWindow,
//                                               QObject::tr("colones d'importation multiples"),
//                                               warnMesg);
//                }
//
//                return 0;
//            }
//        }
//    }
//
//    if (!check_mandatory_item_field())
//    {
//        return 0;
//    }
//
//
//    int curCsvFileLineCount = _curCsvFileToImportContentWordList->size() - 1;
//
//    int successImportCount = 0;
//
//    enum import_csv_entry_row_return_status insertionReturnStatusValue = IMPORT_DATA_CSV_UNDEFINED;
//
//
//    QStringList curCsvFileImportRow;
//
//
//    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;
//
//
//    /*
//     * We start at index 1 so to avoid the first line
//     * that represents the header content, and not data !
//     */
//    for (int k = 1; k < curCsvFileLineCount; ++k)
//    {
//        curCsvFileImportRow = _curCsvFileToImportContentWordList->at(k)
//                                    .split(YerithUtils::CSV_FILE_SEPARATION_SEMI_COLON_STRING_CHAR);
//
////              QDEBUG_STRINGS_OUTPUT_Q_CONTAINER("curCsvFileImportRow", curCsvFileImportRow);
//
//        insertionReturnStatusValue = import_csv_entry_row(importerParlant, curCsvFileImportRow);
//
//
//        if (IMPORT_DATA_CSV_INSERTION_SUCCEED == insertionReturnStatusValue)
//        {
//            ++successImportCount;
//        }
//
//        emit SIGNAL_INCREMENT_PROGRESS_BAR(k);
//    }
//
//
//    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;
//
//
//    if (successImportCount != curCsvFileLineCount)
//    {
//        if (IMPORT_DATA_CSV_MANDATORY_COLUMN_VALUE_MISSING == insertionReturnStatusValue)
//        {
//            YerithERPbankaccountINFOrawImport::_allMissingMandatoryColumnValue.replace(0, 3, YerithUtils::EMPTY_STRING);
//
//            if (0 != _callingWindow)
//            {
//                QString warnMesg =
//                    QObject::tr("Les colones obligatoires "
//                                "suivantes '%1' sont manquantes !")
//                            .arg(YerithERPbankaccountINFOrawImport::_allMissingMandatoryColumnValue);
//
//                YerithQMessageBox::warning(_callingWindow,
//                                           QObject::tr("colones obligatoires manquantes"),
//                                           warnMesg);
//            }
//        }
//    }
//
//    return successImportCount;
//}


enum import_csv_entry_row_return_status
        YerithERPbankaccountINFOrawImport::import_csv_entry_row(bool importerParlant,
                                                                QStringList &aCsvFileEntryLine)
{
    enum import_csv_entry_row_return_status insertionReturnStatus =
        IMPORT_DATA_CSV_INSERTION_FAILED;

    if (aCsvFileEntryLine.size() <= 0)
    {
        return IMPORT_DATA_CSV_INSERTION_FAILED;
    }

    if (1 == aCsvFileEntryLine.size() && aCsvFileEntryLine.at(0).isEmpty())
    {
        return IMPORT_DATA_CSV_INSERTION_FAILED;
    }

    YerithERPWindows *allWindows = YerithUtils::getAllWindows();

    if (0 == _callingWindow ||
        0 == allWindows)
    {
        return IMPORT_DATA_CSV_INSERTION_FAILED;
    }


    YerithERPDatabaseTableColumnInfo *curDatabaseTableColumnInfo = 0;

    YerithSqlTableModel &cur_comptes_bancaires_tableModel = allWindows->getSqlTableModel_comptes_bancaires();


    QSqlRecord record = cur_comptes_bancaires_tableModel.record();

    int Bank_ACCOUNT_ID_to_save = YerithERPWindows::getNextIdSqlTableModel_comptes_bancaires();

//    QDEBUG_STRING_OUTPUT_2_N("Bank_ACCOUNT_ID_to_save - init",
//                              Bank_ACCOUNT_ID_to_save);

    int querySize = -1;

    QStringList allImportedTableColumns;

    QString curTableColumnType;
    QString curTableColumnName;
    QString curColumnRowEntry;

    QString banking_account_SQL_ID;
    QString banking_account_Description;
    QString banking_account_reference;
    QString banking_account_title;
    QString bank_name_institution;

    for (int j = 0; j < aCsvFileEntryLine.size(); ++j)
    {
        curColumnRowEntry = aCsvFileEntryLine.at(j).trimmed();

        if (!curColumnRowEntry.isEmpty())
        {
            if (curColumnRowEntry.at(0) == '"')
            {
                curColumnRowEntry.replace(0, 1, "");
            }

            if (curColumnRowEntry.at(curColumnRowEntry.length() - 1) == '"')
            {
                curColumnRowEntry.replace(curColumnRowEntry.length() - 1, 1, "");
            }
        }

        curDatabaseTableColumnInfo =
            _csvContentIdxToDatabaseTableColumnInfo->value(j);

        if (0 != curDatabaseTableColumnInfo)
        {
            curTableColumnType = curDatabaseTableColumnInfo->getColumnType();

            curTableColumnName = curDatabaseTableColumnInfo->getColumnName();

//                      qDebug() << QString("++ curTableColumnName: %1, curTableColumnType: %2, curColumnRowEntry: %3")
//                                                      .arg(curTableColumnName,
//                                                               curTableColumnType,
//                                                               curColumnRowEntry);

            if (YerithUtils::isEqualCaseInsensitive
                    (YerithDatabaseTableColumn::ID, curTableColumnName))
            {
                banking_account_SQL_ID = curColumnRowEntry;

//                QDEBUG_STRING_OUTPUT_2("banking_account_SQL_ID",
//                                        banking_account_SQL_ID);
            }


            if (YerithUtils::isEqualCaseInsensitive
                    (YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE, curTableColumnName))
            {
                banking_account_reference = curColumnRowEntry;
            }


            if (_allMandatoryTableColumns.contains(curTableColumnName) &&
                    YerithUtils::isEqualCaseInsensitive(YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE,
                                                        curTableColumnName))
            {
                banking_account_title = curColumnRowEntry;
            }


            if (_allMandatoryTableColumns.contains(curTableColumnName) &&
                    YerithUtils::isEqualCaseInsensitive(YerithDatabaseTableColumn::INSTITUT_BANCAIRE,
                                                        curTableColumnName))
            {
                bank_name_institution = curColumnRowEntry;
            }


            if (_allMandatoryTableColumns.contains(curTableColumnName) &&
                    YerithUtils::isEqualCaseInsensitive(YerithDatabaseTableColumn::DESCRIPTION_DU_COMPTE_BANCAIRE,
                                                        curTableColumnName))
            {
                banking_account_Description = curColumnRowEntry;
            }


            if (YERITH_QSTRING_CONTAINS
                    (curTableColumnType,
                     YerithUtils::DATABASE_MYSQL_INT_TYPE_STRING))
            {
                int aCurIntValue = curColumnRowEntry.toInt();

                record.setValue(curTableColumnName, aCurIntValue);

                if (YerithUtils::isEqualCaseInsensitive(YerithDatabaseTableColumn::ID,
                                                        curTableColumnName))
                {
                    Bank_ACCOUNT_ID_to_save = aCurIntValue;
                }
            }
            else if (YERITH_QSTRING_CONTAINS
                         (curTableColumnType,
                          YerithUtils::DATABASE_MYSQL_VARCHAR_TYPE_STRING))
            {
                record.setValue(curTableColumnName,
                                GET_DATE_FROM_STRING(curColumnRowEntry));
            }
            else
            {
                record.setValue(curTableColumnName, curColumnRowEntry);
            }

            allImportedTableColumns.append(curTableColumnName);
        }
    }


    QString infoMesg;


    bool banking__account__SQL__ID___ALREADY_exist =
            YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*_callingWindow,
                                                        cur_comptes_bancaires_tableModel,
                                                        banking_account_SQL_ID,
                                                        QObject::tr("ID (Numéro d'identification unique)"),
                                                        YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE);

    bool banking__account__reference_ALREADY_exist =
            YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*_callingWindow,
                                                        cur_comptes_bancaires_tableModel,
                                                        banking_account_reference,
                                                        QObject::tr("compte bancaire"),
                                                        YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE);

    bool banking_account_title_ALREADY_exist =
            YerithUtils::checkIf_KEYWORD_ALREADY_EXISTS(*_callingWindow,
                                                        cur_comptes_bancaires_tableModel,
                                                        banking_account_title,
                                                        QObject::tr("intitulé de compte bancaire"),
                                                        YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE);


    if (banking__account__SQL__ID___ALREADY_exist)
    {
        infoMesg = QObject::tr("1 compte bancaire avec ID ('%1') est déjà utilisé !")
                        .arg(banking_account_SQL_ID);
    }
    else
    {
        Bank_ACCOUNT_ID_to_save = banking_account_SQL_ID.toUInt();
    }

    if (banking__account__reference_ALREADY_exist)
    {
        infoMesg = QObject::tr("1 compte bancaire avec référence ('%1') est déjà utilisé !")
                        .arg(banking_account_reference);
    }

    if (banking_account_title_ALREADY_exist)
    {
        infoMesg = QObject::tr("1 compte bancaire avec ''Intitulé de compte bancaire'' ('%1') est déjà utilisé !")
                        .arg(banking_account_reference);
    }


    if (banking__account__SQL__ID___ALREADY_exist ||
        banking__account__reference_ALREADY_exist ||
        banking_account_title_ALREADY_exist)
    {
        if (0 != _callingWindow)
        {
            if (importerParlant)
            {
                YerithQMessageBox::warning(_callingWindow,
                                           "enregistrer",
                                           infoMesg);
            }
        }
        else
        {
            qDebug() << infoMesg;
        }

        return IMPORT_DATA_CSV_INSERTION_ALREADY_EXISTANT;
    }



    record.setValue(YerithDatabaseTableColumn::ID,
                    Bank_ACCOUNT_ID_to_save);

    record.setValue(YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE,
                    banking_account_reference);

    record.setValue(YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE,
                    banking_account_title);

    record.setValue(YerithDatabaseTableColumn::INSTITUT_BANCAIRE,
                    bank_name_institution);

    record.setValue(YerithDatabaseTableColumn::DESCRIPTION_DU_COMPTE_BANCAIRE,
                    banking_account_Description);



    if (0 != YerithERPbankaccountINFOrawImport::_dbTableColumnToIsNotNULL)
    {
        QString aCurSqlTableImportColumn;

        QStringList allSqltableColumns = YerithERPbankaccountINFOrawImport::_dbTableColumnToIsNotNULL->keys();

        allSqltableColumns.removeAll(YerithDatabaseTableColumn::ID);
        allSqltableColumns.removeAll(YerithDatabaseTableColumn::REFERENCE_DU_COMPTE_BANCAIRE);
        allSqltableColumns.removeAll(YerithDatabaseTableColumn::INTITULE_DU_COMPTE_BANCAIRE);
        allSqltableColumns.removeAll(YerithDatabaseTableColumn::INSTITUT_BANCAIRE);
        allSqltableColumns.removeAll(YerithDatabaseTableColumn::DESCRIPTION_DU_COMPTE_BANCAIRE);


        for (int k = 0; k < allSqltableColumns.size(); ++k)
        {
            aCurSqlTableImportColumn = allSqltableColumns.at(k);

            if (allImportedTableColumns.contains(aCurSqlTableImportColumn))
            {
                continue;
            }

            if (false == YerithERPbankaccountINFOrawImport::_dbTableColumnToIsNotNULL->value(aCurSqlTableImportColumn))
            {
                insertionReturnStatus =
                    IMPORT_DATA_CSV_MANDATORY_COLUMN_VALUE_MISSING;

                /*
                 * This SQL stock table column MUST BE NOT NULL.
                 * So we attribute it a standard value.
                 *
                 * The previous statement is alone not valid for
                 * the 'id' column !
                 */
                if (!YerithUtils::isEqualCaseInsensitive
                        (YerithDatabaseTableColumn::ID, aCurSqlTableImportColumn))
                {
                    if (!YERITH_QSTRING_CONTAINS
                            (_allMissingMandatoryColumnValue,
                             aCurSqlTableImportColumn))
                    {
                        _allMissingMandatoryColumnValue.append(QString(" , %1")
                                                                .arg(aCurSqlTableImportColumn));
                    }
                }
            }
        }

        if (IMPORT_DATA_CSV_MANDATORY_COLUMN_VALUE_MISSING == insertionReturnStatus)
        {
            return IMPORT_DATA_CSV_MANDATORY_COLUMN_VALUE_MISSING;
        }
    }


//    QDEBUG_STRING_OUTPUT_2_N("Bank_ACCOUNT_ID_to_save - 2", Bank_ACCOUNT_ID_to_save);


    bool queryResut = cur_comptes_bancaires_tableModel.insertNewRecord(record);

    if (queryResut)
    {
        return IMPORT_DATA_CSV_INSERTION_SUCCEED;
    }

    return IMPORT_DATA_CSV_INSERTION_FAILED;
}
