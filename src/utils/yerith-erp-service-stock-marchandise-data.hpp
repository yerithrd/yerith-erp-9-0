/*
 * yerith-erp-service-stock-marchandise-data.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef SRC_YERITH_SERVICE_STOCK_MARCHANDISES_DATA_HPP_
#define SRC_YERITH_SERVICE_STOCK_MARCHANDISES_DATA_HPP_

#include "src/include/yerith-erp-9-0-definition-oo-class-operators.hpp"

#include "src/utils/yerith-erp-utils.hpp"


#include <QtCore/QByteArray>
#include <QtCore/QString>


class YerithERPServiceData
{

public:

    YERITH_CLASS_OPERATORS


    inline YerithERPServiceData():_isService(true)
    {
    }

    inline ~YerithERPServiceData()
    {
    }

    int _unite_de_mesure_de_vente;

    bool _isService;

    QString _nom_entreprise_client;

    QString _nom_departement_produit;

    QString _categorie;

    QString _designation;

    QString _reference;

    QString _description;
};


class YerithERPStockMarchandiseData : public YerithERPServiceData
{

public:

    YERITH_CLASS_OPERATORS

    inline YerithERPStockMarchandiseData()
    :_prix_dachat_precedent("0.0"),
     _prix_vente_precedent("0.0"),
     _prix_vente_en_gros_precedent("0.0")
    {
        _isService = false;
    }

    inline ~YerithERPStockMarchandiseData()
    {
    }


    QString _prix_dachat_precedent;

    QString _prix_vente_precedent;

    QString _prix_vente_en_gros_precedent;
};



#endif /* SRC_YERITH_SERVICE_STOCK_MARCHANDISES_DATA_HPP_ */
