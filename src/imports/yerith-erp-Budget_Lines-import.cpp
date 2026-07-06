/*
 * yerith-erp-Budget_Lines-import.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "src/imports/yerith-erp-Budget_Lines-import.hpp"



QString YerithERPbudgetLinesImport::_allMissingMandatoryColumnValue;


QMap<QString, bool> *YerithERPbudgetLinesImport::_dbTableColumnToIsNotNULL;



YerithERPbudgetLinesImport::YerithERPbudgetLinesImport(QStringList                                      &aCurCsvFileToImportContentWordList,
                                                       QMap<int, YerithERPDatabaseTableColumnInfo *>    &aCsvContentIdxToDatabaseTableColumnInfo)
:YerithERPAllCOMMONImport(aCurCsvFileToImportContentWordList,
                          aCsvContentIdxToDatabaseTableColumnInfo)
{
}


YerithERPbudgetLinesImport::YerithERPbudgetLinesImport(YerithPOSAdminWindowsCommons                   &aCallingWindow,
                                                       QStringList                                    &aCurCsvFileToImportContentWordList,
                                                       QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo)
:YerithERPAllCOMMONImport(aCallingWindow,
                          aCurCsvFileToImportContentWordList,
                          aCsvContentIdxToDatabaseTableColumnInfo)
{
}


int YerithERPbudgetLinesImport::import(QString  &_allMissingMandatoryColumnValue,
                                       bool     importerParlant /* = false */)
{
    QDEBUG_STRING_OUTPUT_1("YerithERPbudgetLinesImport::import");

    return
        YerithERPAllCOMMONImport::import(_allMissingMandatoryColumnValue,
                                         importerParlant);
}


enum import_csv_entry_row_return_status
    YerithERPbudgetLinesImport::import_csv_entry_row(bool           importerParlant,
                                                     QStringList    &aCsvFileEntryLine)
{
}
