/*
 * yerith-erp-ALL-common-import.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-ALL-common-import.hpp"


#include "src/utils/yerith-erp-historique-stock.hpp"

#include "src/yerith-erp-windows.hpp"

#include "src/utils/yerith-erp-database-table-column.hpp"

#include "src/widgets/yerith-erp-qmessage-box.hpp"


#include <QtCore/QDebug>




int YerithERPAllCOMMONImport::import(QString                        &_allMissingMandatoryColumnValue,
                                     bool                            importerParlant /* = true */,
                                     YerithPOSAdminWindowsCommons   *A_Calling_Window  /* = 0 */)
{
    _allMissingMandatoryColumnValue.clear();


    if (0 != A_Calling_Window)
    {
        _callingWindow = A_Calling_Window;
    }

    QString warnMesg;

    if (_curCsvFileToImportContentWordList->size() <= 1)
    {
        if (0 != _callingWindow)
        {
            warnMesg = QObject::tr("Le fichier CSV n'a pas de données à importer !");

            YerithQMessageBox::warning(_callingWindow,
                                       QObject::tr("fichier CSV vide"),
                                       warnMesg);
        }

        return 0;
    }


    QStringList csvHeader = _curCsvFileToImportContentWordList->at(0)
                                .split(YerithUtils::CSV_FILE_SEPARATION_SEMI_COLON_STRING_CHAR);


    QString curSqlTableImportHeaderStr;

    YerithERPDatabaseTableColumnInfo *curDatabaseTableColumnInfo = 0;

    int curCsvFileColumnSize = csvHeader.size();

    /*
     * check if '2 csv columns' are mapped to
     * a same database table import-column.
     */
    for (int i = 0; i < curCsvFileColumnSize; ++i)
    {
        curDatabaseTableColumnInfo = _csvContentIdxToDatabaseTableColumnInfo->value(i);

        if (0 != curDatabaseTableColumnInfo)
        {
            curSqlTableImportHeaderStr = curDatabaseTableColumnInfo->getColumnName();

            curSqlTableImportHeaderStr = curSqlTableImportHeaderStr
                                            .remove("\"")
                                            .remove("\'")
                                            .trimmed();

            if (!_allSqlTableImportColumns.contains(curSqlTableImportHeaderStr, Qt::CaseInsensitive))
            {
                _allSqlTableImportColumns.append(curSqlTableImportHeaderStr);
            }
            else
            {
                if (0 != _callingWindow)
                {
                    warnMesg = QObject::tr("La colone '%1' apparaît "
                                           "plusieurs fois parmis les "
                                           "colones d'importation !").arg(curSqlTableImportHeaderStr);

                    YerithQMessageBox::warning(_callingWindow,
                                               QObject::tr("colones d'importation multiples"),
                                               warnMesg);
                }

                return 0;
            }
        }
    }

    if (!check_mandatory_item_field())
    {
        return 0;
    }


    int curCsvFileLineCount = _curCsvFileToImportContentWordList->size() - 1;

    int successImportCount = 0;

    enum import_csv_entry_row_return_status insertionReturnStatusValue = IMPORT_DATA_CSV_UNDEFINED;


    QStringList curCsvFileImportRow;


    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;


    /*
     * We start at index 1 so to avoid the first line
     * that represents the header content, and not data !
     */
    for (int k = 1; k < curCsvFileLineCount; ++k)
    {
        curCsvFileImportRow = _curCsvFileToImportContentWordList->at(k)
                                    .split(YerithUtils::CSV_FILE_SEPARATION_SEMI_COLON_STRING_CHAR);

        insertionReturnStatusValue = import_csv_entry_row(importerParlant, curCsvFileImportRow);

        if (IMPORT_DATA_CSV_INSERTION_SUCCEED == insertionReturnStatusValue)
        {
            ++successImportCount;
        }

        emit SIGNAL_INCREMENT_PROGRESS_BAR(k);
    }


    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;


    if (successImportCount != curCsvFileLineCount)
    {
        if (IMPORT_DATA_CSV_MANDATORY_COLUMN_VALUE_MISSING == insertionReturnStatusValue)
        {
            _allMissingMandatoryColumnValue.replace(0, 3, YerithUtils::EMPTY_STRING);

            if (0 != _callingWindow)
            {
                QString warnMesg =
                    QObject::tr("Les colones obligatoires "
                                "suivantes '%1' sont manquantes !")
                            .arg(_allMissingMandatoryColumnValue);

                YerithQMessageBox::warning(_callingWindow,
                                           QObject::tr("colones obligatoires manquantes"),
                                           warnMesg);
            }
        }
    }

    return successImportCount;
}


void YerithERPAllCOMMONImport::missing_mandatory_item_field_msg(const QString &aMandatoryColumn)
{
    QString warnMesg =
        QObject::tr("La colone OBLIGATOIRE '%1' est manquante !")
                 .arg(aMandatoryColumn);

    if (0 != _callingWindow)
    {
        YerithQMessageBox::warning(_callingWindow,
                                   QObject::tr("colone OBLIGATOIRE manquante"),
                                   warnMesg);
    }
    else
    {
        qDebug() << warnMesg;
    }
}


bool YerithERPAllCOMMONImport::check_mandatory_item_field()
{
    QString curMandatoryTableColumn;

    for (int j = 0; j < _allMandatoryTableColumns.size(); ++j)
    {
        curMandatoryTableColumn = _allMandatoryTableColumns.at(j);

        if (!_allSqlTableImportColumns.contains(curMandatoryTableColumn))
        {
            missing_mandatory_item_field_msg(curMandatoryTableColumn);

            return false;
        }
    }

    return true;
}


