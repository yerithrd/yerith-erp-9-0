/*
 * yerith-erp-stock-marchandise.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_MARCHANDISE_IMPORT_WINDOW_HPP_
#define YERITH_MARCHANDISE_IMPORT_WINDOW_HPP_


#include "src/imports/yerith-erp-stock-import.hpp"


class YerithERPMarchandiseImport : public YerithERPStockImport
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS


    YerithERPMarchandiseImport(QStringList                                      &aCurCsvFileToImportContentWordList,
                               QMap<int, YerithERPDatabaseTableColumnInfo *>    &aCsvContentIdxToDatabaseTableColumnInfo);


    YerithERPMarchandiseImport(YerithPOSAdminWindowsCommons                     &aCallingWindow,
                               QStringList                                      &aCurCsvFileToImportContentWordList,
                               QMap<int, YerithERPDatabaseTableColumnInfo *>    &aCsvContentIdxToDatabaseTableColumnInfo);


    virtual inline ~YerithERPMarchandiseImport()
    {
    }


    virtual inline int import_csv_file()
    {
        return YerithERPStockImport::import_csv_file();
    }


protected:

    virtual enum import_csv_entry_row_return_status
        import_csv_entry_row(bool           importerParlant,
                             QStringList    &aCsvFileEntryLine);
};


#endif /* YERITH_MARCHANDISE_IMPORT_WINDOW_HPP_ */
