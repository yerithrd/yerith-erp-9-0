/*
 * yerith-erp-stock-import.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_STOCK_IMPORT_WINDOW_HPP_
#define YERITH_STOCK_IMPORT_WINDOW_HPP_


#include "src/imports/yerith-erp-ALL-common-import.hpp"


class YerithERPStockImport : public YerithERPAllCOMMONImport
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


    YerithERPStockImport(QStringList                                    &aCurCsvFileToImportContentWordList,
                         QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo);


    YerithERPStockImport(YerithPOSAdminWindowsCommons                   &aCallingWindow,
                         QStringList                                    &aCurCsvFileToImportContentWordList,
                         QMap<int, YerithERPDatabaseTableColumnInfo *>  &aCsvContentIdxToDatabaseTableColumnInfo);


    virtual inline ~YerithERPStockImport()
    {
    }


    virtual inline int import_csv_file()
    {
        return YerithERPAllCOMMONImport::import(_allMissingMandatoryColumnValue,
                                                (0 != _callingWindow),
                                                _callingWindow);
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


#endif /* YERITH_STOCK_IMPORT_WINDOW_HPP_ */
