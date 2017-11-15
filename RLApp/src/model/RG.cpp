#include "model/RG.h"

RG::RG()
{
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
