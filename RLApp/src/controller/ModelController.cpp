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
	_fa->addTerminal("");
	_fa->addState(FAState());
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
	RE temp_re;
	FADataModel* ret_fa;
	bool* ret;
	FADataModel* conv_re;
	switch (event)
	{
	case RE_ADD:
		_re.setReString(*(QString*)entity);
		break;
	case RE_TO_FA:
		_fa_temp = new FADataModel(Conversions::reToFA(_re));
		_fa_temp->determinize();
		notify((void*)_fa_temp, FA_UPDATE_OPERATION);
		break;
	case RE_UNION:
		
		
		temp_re.setReString(*(QString*)entity);

		_fa_temp = new FADataModel(Conversions::reToFA(_re));
		//_fa_temp->determinize();
		//_fa_temp->minimizeDeterministic();

		conv_re = new FADataModel(Conversions::reToFA(temp_re));
		//conv_re->determinize();
		//conv_re->minimizeDeterministic();

		ret_fa = new FADataModel(_fa_temp->faUnion(*conv_re));

		ret_fa->determinize();
		ret_fa->minimizeDeterministic();
		notify((void*)ret_fa, FA_UPDATE_OPERATION);

		break;
	case RE_INTERSECTION:
		temp_re.setReString(*(QString*)entity);

		_fa_temp = new FADataModel(Conversions::reToFA(_re));


		ret_fa = new FADataModel(_fa_temp->faIntersection(*Conversions::reToFA(temp_re)));

		ret_fa->determinize();
		notify((void*)ret_fa, FA_UPDATE_OPERATION);
		break;
	case RE_COMPLEMENT:
		_fa_temp = new FADataModel(Conversions::reToFA(_re));

		ret_fa = new FADataModel(_fa_temp->faComplement());
		notify((void*)ret_fa, FA_UPDATE_OPERATION);
		break;
	case RE_EQUIVALENCE:
		temp_re.setReString(*(QString*)entity);

		_fa_temp = new FADataModel(Conversions::reToFA(_re));

		ret = new bool(_fa_temp->faEquivalent(*Conversions::reToFA(temp_re)));

		notify((void*)ret, RE_EQUIVALENCE_RESULT);
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
		//temp_re.setReString(*(QString*)entity);

		//_fa_temp = new FADataModel(*_fa);
		//FADataModel* ret_fa;

		//ret_fa = new FADataModel(_fa_temp->faUnion(*(FADataModel*)entity));
		//notify((void*)ret_fa, FA_UPDATE_OPERATION);
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



