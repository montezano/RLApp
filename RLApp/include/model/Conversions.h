#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include "model/AF.h"
#include "model/RE.h"

class Conversions
{
public:
	//Conversions();
	//~Conversions();
	
	static FA reToFA(RE re);
private:
	static QVector<VT> getTerminals(FA& fa, QVector<Node*> di_simone_composition);
	static QString compositionToString(QVector<Node*> di_simone_composition);
	static TR createTransition(QVector<Node*> di_simone_composition, VT terminal);
	static StateType getStateType(QVector<Node*> di_simone_composition);
};

//Conversions::Conversions()
//{
//}
//
//Conversions::~Conversions()
//{
//}
#endif // !__CONVERSIONS_H__
