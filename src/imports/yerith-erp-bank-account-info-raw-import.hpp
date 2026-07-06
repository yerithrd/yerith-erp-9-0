/*
 * yerith-erp-bank-account-info-raw-import.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_BANK_ACCOUNT_INFO_RAW_IMPORT_WINDOW_HPP_
#define YERITH_BANK_ACCOUNT_INFO_RAW_IMPORT_WINDOW_HPP_


#include "src/imports/yerith-erp-ALL-common-import.hpp"


class YerithERPbankaccountINFOrawImport : public YerithERPAllCOMMONImport

{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


    YerithERPbankaccountINFOrawImport(QStringList                                    &aCurCsvFileToImportContentWordList,
                                      QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo);


    YerithERPbankaccountINFOrawImport(YerithPOSAdminWindowsCommons                   &aCallingWindow,
                                      QStringList                                    &aCurCsvFileToImportContentWordList,
                                      QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo);


    virtual inline ~YerithERPbankaccountINFOrawImport()
    {
    }


    virtual inline int import_csv_file()
    {
        return YerithERPAllCOMMONImport::import(_allMissingMandatoryColumnValue);
    }

//    virtual int import(bool importerParlant = false);


    static QString _allMissingMandatoryColumnValue;

    static QMap<QString, bool> *_dbTableColumnToIsNotNULL;


signals:

    void SIGNAL_INCREMENT_PROGRESS_BAR(int countSuccess);


protected:

    virtual enum import_csv_entry_row_return_status
        import_csv_entry_row(bool           importerParlant,
                             QStringList    &aCsvFileEntryLine);
};


#endif /* YERITH_BANK_ACCOUNT_INFO_RAW_IMPORT_WINDOW_HPP_ */
