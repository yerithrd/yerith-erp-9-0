/*
 * yerith-erp-Budget_Lines-import.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_BUDGET_LINES_IMPORT_WINDOW_HPP_
#define YERITH_BUDGET_LINES_IMPORT_WINDOW_HPP_


#include "src/imports/yerith-erp-ALL-common-import.hpp"


class YerithERPbudgetLinesImport : public YerithERPAllCOMMONImport
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


    YerithERPbudgetLinesImport(QStringList                                    &aCurCsvFileToImportContentWordList,
                               QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo);


    YerithERPbudgetLinesImport(YerithPOSAdminWindowsCommons                   &aCallingWindow,
                               QStringList                                    &aCurCsvFileToImportContentWordList,
                               QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo);


    virtual inline ~YerithERPbudgetLinesImport()
    {
    }


    virtual inline int import_csv_file()
    {
        return import(_allMissingMandatoryColumnValue);
    }


    virtual int import(QString  &_allMissingMandatoryColumnValue,
                       bool     importerParlant = false);


    static QString _allMissingMandatoryColumnValue;

    static QMap<QString, bool> *_dbTableColumnToIsNotNULL;


signals:

    void SIGNAL_INCREMENT_PROGRESS_BAR(int countSuccess);


protected:

    virtual enum import_csv_entry_row_return_status
        import_csv_entry_row(bool           importerParlant,
                             QStringList    &aCsvFileEntryLine);
};


#endif /* YERITH_BUDGET_LINES_IMPORT_WINDOW_HPP_ */
