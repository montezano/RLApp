#include "controller/ModelController.h"

ModelController::ModelController() :
	_re()
{
}

ModelController::ModelController(Observer * observer) :
	_re()
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
