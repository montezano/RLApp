#ifndef __RG_H__
#define __RG_H__

#include "util/Alphabet.h"

class RG
{
public:
	RG();
	~RG();

	bool addProduction(PLeft pleft, PRight pright);

	QList<PRight> getProduction(PLeft left);

	QList<PLeft> getProductionLeft();

	bool setInitial(PLeft left);

	PLeft getInitial();

private:
	bool verifyProduction(PLeft pleft, PRight pright);
	Productions _rg;
	PLeft _initial_prod;

	QVector<QChar> _valid_terminals = { 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9' };
};


#endif // !__RG_H__
