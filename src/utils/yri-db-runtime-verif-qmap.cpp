/*
 * yri-db-runtime-verif-qmap.cpp
 *
 * THIS is ring-buffer implemented as a QMAP.
 * THE original version comes for YRI-DB-RUNTIME-VERIF
 * project.
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yri-db-runtime-verif-qmap.hpp"


#include "src/utils/yerith-erp-utils.hpp"



void YRIDBRUNTIMEVERIF_QMap::setMaxSize(uint MAX_SIZE)
{
	QMap<uint, QObject *>::clear();

	_current_IDX = 0;

	_max_elements_SIZE = MAX_SIZE;
}


void YRIDBRUNTIMEVERIF_QMap::yri_insert_item(uint       a_yri_key,
                                             QObject   *a_yri_value)
{
	if (_current_IDX >= _max_elements_SIZE)
	{
		_current_IDX = 0;

		QMap<uint, QObject *>::const_iterator map_begin = QMap<uint, QObject *>::constBegin();

        QMap<uint, QObject *>::insert(map_begin,
                                      a_yri_key,
                                      a_yri_value);

		++_current_IDX;
	}
	else
	{
		QMap<uint, QObject *>::insert(a_yri_key, a_yri_value);

		++_current_IDX;
	}

//	QDEBUG_STRING_OUTPUT_2_N("_max_elements_SIZE", _max_elements_SIZE);
//	QDEBUG_STRING_OUTPUT_2_N("size()", size());
//
//	assert (size() <= _max_elements_SIZE);
}


