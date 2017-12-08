#include "controller/ModelController.h"

ModelController::ModelController() :
	_re(),
	_rg()
{
}

ModelController::ModelController(Observer * observer, FADataModel* fa_data, FADataModel* fa_data2) :
	_re(),
	_fa(fa_data),
	_fa2(fa_data2)
{
	_re.addObserver(observer);
	//_fa->addTerminal("");
	//_fa->addState(FAState());
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
		//_fa_temp->determinize();
		//_fa_temp->minimizeDeterministic();
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
		_rg.parse(*(QString*)entity);

		ret_fa = new FADataModel(Conversions::grToFA(_rg));

		notify((void*)ret_fa, FA_UPDATE_OPERATION);
		break;
	case RG_UNION:
		break;
	case RG_INTERSECTION:
		break;
	case RG_COMPLEMENT:
		break;
	case RG_EQUIVALENCE:
		break;
	case FA_ADD:
		_fa = (FADataModel*)entity;
		break;
	case FA_UNION:
		ret_fa = new FADataModel(_fa->faUnion(*_fa2));
		notify((void*)ret_fa, FA_UPDATE_OPERATION);

		break;
	case FA_INTERSECTION:
		conv_re = (FADataModel*)entity;
		ret_fa = new FADataModel(_fa->faIntersection(*_fa2));
		notify((void*)ret_fa, FA_UPDATE_OPERATION);
		break;
	case FA_COMPLEMENT:
		ret_fa = new FADataModel(_fa->faComplement());
		notify((void*)ret_fa, FA_UPDATE_OPERATION);
		break;
	case FA_EQUIVALENCE:
		conv_re = (FADataModel*)entity;
		ret = new bool(_fa->faEquivalent(*_fa2));
		notify((void*)ret, FA_UPDATE_OPERATION);
		break;
	case FA_DETERMINIZATION:
		_fa->determinize();
		//notify((void*)ret, FA_UPDATE_OPERATION);
		notify((void*)_fa, FA_UPDATE_ORIGINAL);

		break;
	case FA_MINIMIZATION:
		_fa->determinize();
		_fa->minimizeDeterministic();
		notify((void*)_fa, FA_UPDATE_ORIGINAL);

		break;	

	}
}



