/*
 * yerith-erp-credit-card-info.cpp
 *
 *   Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */



#include "yerith-erp-carte-credit-info.hpp"



void YerithPOSCreditCardInfo::clearAllFields()
{
    _issuingCompany.clear();

    _nameOnCard.clear();

    _postalCode.clear();

    _cardNumber.clear();

    _expiryDate_YY.clear();

    _expiryDate_MM.clear();

    _cvCode.clear();
}
