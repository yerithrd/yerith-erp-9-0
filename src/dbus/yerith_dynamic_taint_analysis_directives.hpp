/*
 * yerith_dynamic_taint_analysis_directives.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _YERITH_DYNAMIC_TAINT_ANALYSIS_DIRECTIVES_HPP_
#define _YERITH_DYNAMIC_TAINT_ANALYSIS_DIRECTIVES_HPP_


#include <QtCore/QObject>


class YerithERPWindows;


class YerithDynamicTaintAnalysisDirectives : public QObject
{
	Q_OBJECT

public:

	inline YerithDynamicTaintAnalysisDirectives();

	virtual inline ~YerithDynamicTaintAnalysisDirectives()
	{
	}


	bool is_a_TAINTED_value(QString a_Potential_tainted_value_Variable_pointer);

	bool is_a_sanitizer_method(QString a_Potential_Sanitizing_method);


private:

    YerithERPWindows *_all_windows;
};



#endif /* _YERITH_DYNAMIC_TAINT_ANALYSIS_DIRECTIVES_HPP_ */
