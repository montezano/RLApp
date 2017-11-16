#include "controller/ModelController.h"

ModelController::ModelController() :
	_re()
{
}

ModelController::ModelController(Observer * observer, FADataModel* fa_data) :
	_re(),
	_fa(fa_data)
{
	_re.addObserver(observer);
}

ModelController::~ModelController()
{
}

bool ModelController::updateRE()
{

	return false;
}

void ModelController::onNotify(void * entity, Events event)
{
	switch (event)
	{
	case RE_TO_FA:
		break;
	case RE_UNION:
		break;
	case RE_INTERSECTION:
		break;
	case RE_COMPLEMENT:
		break;
	case RE_EQUIVALENCE:
		break;
	case RG_TO_FA:
		break;
	case RG_UNION:
		break;
	case RG_INTERSECTION:
		break;
	case RG_COMPLEMENT:
		break;
	case RG_EQUIVALENCE:
		break;
	case FA_UNION:
		break;
	case FA_INTERSECTION:
		break;
	case FA_COMPLEMENT:
		break;
	case FA_EQUIVALENCE:
		break;
	case FA_DETERMINIZATION:
		break;
	case FA_MINIMIZATION:
		break;	

	}
}



