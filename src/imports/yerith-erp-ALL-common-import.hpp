/*
 * yerith-erp-ALL-common-import.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ALL_COMMON_IMPORT_WINDOW_HPP_
#define YERITH_ALL_COMMON_IMPORT_WINDOW_HPP_


#include "src/imports/yerith-erp-database-table-import-info.hpp"

#include "src/utils/yerith-erp-utils.hpp"



enum import_csv_entry_row_return_status
{
    IMPORT_DATA_CSV_INSERTION_SUCCEED = 0,
    IMPORT_DATA_CSV_INSERTION_ALREADY_EXISTANT,
    IMPORT_DATA_CSV_INSERTION_FAILED,
    IMPORT_DATA_CSV_INCORRECT_COLUMN_VALUE,
    IMPORT_DATA_CSV_MANDATORY_COLUMN_VALUE_MISSING,
    IMPORT_DATA_CSV_UNDEFINED
};


class YerithERPAllCOMMONImport : public QObject
{
    Q_OBJECT

public:

    inline YerithERPAllCOMMONImport(QStringList                                     &aCurCsvFileToImportContentWordList,
                                    QMap<int, YerithERPDatabaseTableColumnInfo *>   &aCsvContentIdxToDatabaseTableColumnInfo)
        :_curCsvFileToImportContentWordList(&aCurCsvFileToImportContentWordList),
         _csvContentIdxToDatabaseTableColumnInfo(&aCsvContentIdxToDatabaseTableColumnInfo),
         _callingWindow(0)
    {
    }


    inline YerithERPAllCOMMONImport(YerithPOSAdminWindowsCommons                   &aCallingWindow,
                                    QStringList                                    &aCurCsvFileToImportContentWordList,
                                    QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo)
        :_curCsvFileToImportContentWordList(&aCurCsvFileToImportContentWordList),
         _csvContentIdxToDatabaseTableColumnInfo(&aCsvContentIdxToDatabaseTableColumnInfo),
         _callingWindow(&aCallingWindow)
    {
    }


    virtual inline ~YerithERPAllCOMMONImport()
    {
    }


    virtual inline void set_A_Calling_WINDOW(YerithPOSAdminWindowsCommons *A_CALLING_Window)
    {
        _callingWindow = A_CALLING_Window;
    }


    virtual inline int import_csv_file() = 0;


    virtual int import(QString                      &_allMissingMandatoryColumnValue,
                       bool                         importerParlant                    = true,
                       YerithPOSAdminWindowsCommons *A_Calling_Window                  = 0);


signals:

    void SIGNAL_INCREMENT_PROGRESS_BAR(int countSuccess);


protected:

    void missing_mandatory_item_field_msg(const QString &aMandatoryColumn);


    bool check_mandatory_item_field();


    virtual enum import_csv_entry_row_return_status
        import_csv_entry_row(bool           importerParlant,
                             QStringList    &aCsvFileEntryLine) = 0;


    QStringList _allSqlTableImportColumns;

    QStringList _allMandatoryTableColumns;

    QStringList *_curCsvFileToImportContentWordList;

    QMap<int, YerithERPDatabaseTableColumnInfo *> *_csvContentIdxToDatabaseTableColumnInfo;

    YerithPOSAdminWindowsCommons *_callingWindow;

};


#endif /* YERITH_ALL_COMMON_IMPORT_WINDOW_HPP_ */
