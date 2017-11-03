#include "model/AF.h"

void FA::setFA()
{
}

MapModel FA::getFA()
{
	return map.data();
}

//void AF::setRe(QString re)
//{
//	_re = re;
//}

bool FA::verify()
{
	return false;
}

///////////////////////////////////////////////
// FAState
///////////////////////////////////////////////


FAState::FAState(FA * parent, NT state_name, QList<VT> transitions, StateType type):
	_parent(parent),
	_state_name(state_name),
	_transitions(transitions),
	_type(type)
{
	
}

FAState::~FAState()
{
}