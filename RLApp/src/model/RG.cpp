#include "model/RG.h"

RG::RG()
{
	//addProduction("Z", "aA");
	//addProduction("Z", "bB");
	//addProduction("Z", "&");
	//addProduction("S", "aA");
	//addProduction("S", "bB");
	//addProduction("A", "aS");
	//addProduction("A", "bC");
	//addProduction("A", "a");
	//addProduction("B", "aC");
	//addProduction("B", "bS");
	//addProduction("B", "b");
	//addProduction("C", "aB");
	//addProduction("C", "bA");
}

RG::~RG()
{
}

bool RG::addProduction(PLeft pleft, PRight pright)
{
	if (!verifyProduction(pleft, pright))
	{
		return false;
	}
	return _rg.insertMulti(pleft, pright) != _rg.end();
}

QList<PRight> RG::getProduction(PLeft left)
{
	return _rg.values(left);
}

QList<PLeft> RG::getProductionLeft()
{
	return _rg.keys();
}

bool RG::setInitial(PLeft left)
{
	_initial_prod = left;
	return true;
}

PLeft RG::getInitial()
{
	return _initial_prod;
}

bool RG::parse(QString rg)
{
	
	setInitial(rg.at(0));
	QList<QString > str_productions = rg.split('\n');

	for (QString str_production : str_productions)
	{
		QList<QString> split_prod = str_production.split(QRegExp("->"));
		split_prod[0].remove(" ");
		for (QString right_prod : split_prod[1].split('|'))
		{
			right_prod.remove(" ");
			addProduction(split_prod[0], right_prod);
		}
	}
	return true;
}

bool RG::verifyProduction(PLeft pleft, PRight pright)
{
	for (QChar ch : pleft)
	{
		if (_valid_terminals.contains(ch))
		{
			return false;
		}
	}

	int count = 0;
	for (QChar ch : pright)
	{
		if (_valid_terminals.contains(ch))
		{
			count++;
		}
	}

	return count < 2;
}
