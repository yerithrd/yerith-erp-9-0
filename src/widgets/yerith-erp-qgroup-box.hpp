/*
 * yerith-erp-group-box.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_GROUP_BOX_HPP_
#define YERITH_ERP_GROUP_BOX_HPP_


#include <QtWidgets/QGroupBox>


#include "src/utils/yerith-erp-utils.hpp"



class YerithWindowsCommons;

class YerithUtils;



class YerithERPGROUPbox : public QGroupBox
{

public:

    YERITH_CLASS_OPERATORS

    inline YerithERPGROUPbox(QWidget *parent)
    :QGroupBox(parent)
    {
        _parent_window = (YerithWindowsCommons *) window();
    }

    inline ~YerithERPGROUPbox()
    {
    }


public:

    YerithWindowsCommons *_parent_window;

};





#endif /* YERITH_ERP_GROUP_BOX_HPP_ */
