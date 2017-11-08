#include "model/AF.h"

FA::FA() :
	_terminals(),
	_states(),
	_last_state_add(0)
{
	_terminals << "Trans";
}

FA::~FA()
{
}

void FA::setTerminals(QVector<VT> terminals)
{
	_terminals = terminals;
}

void FA::addTerminal(VT terminal)
{
	_terminals << terminal;
}

QVector<VT> FA::getTerminals()
{
	return _terminals;
}

bool FA::addState(QVector<TR> transitions, StateType type)
{
	if (transitions.size() != _terminals.size() - 1)
	{
		return false;
	}
	if (_states.size() == 0)
	{
		type = type | INITIAL;
		_last_state_add = 0;
	}
	_states << FAState(this, getNextStateName(), transitions, type);
	return true;
}

bool FA::isEmpty()
{
	QVector<NT> fertile_state = getFinalStates();


	for (int i = 0; i < _states.size(); i++)
	{

		for (int state = 0; state < _states.size(); state++)
		{
			for (auto transition : _states[state]._transitions)
			{
				for (NT st : transition)
				{
					if (fertile_state.contains(st))
					{
						fertile_state << _states[state]._state_name;
					}
				}
			}
		}
	}

	return fertile_state.contains(_states[0]._state_name);
}

bool FA::isInfinite()
{
	QVector<NT> visited;

	

	return findCicle(_states[0], _states[0], visited);
}


//def findCicle(self) :
//	visited = []
//	return self.connected() and not self.findCicleOf(self.vertices.keys()[0], self.vertices.keys()[0], visited)





bool FA::verify()
{
	return false;
}

unsigned FA::getNextStateName()
{
	unsigned ret = _last_state_add;
	_last_state_add++;
	return ret;
}

QVector<NT> FA::getFinalStates()
{
	QVector<NT> fertile_state;

	for (int state = 0; state < _states.size(); state++)
	{
		if (_states[state]._type & FINAL)
		{
			fertile_state << _states[state]._state_name;
		}
	}

	return fertile_state;
}

bool FA::findCicle(FAState current_state, FAState last_state, QVector<NT> visited)
{
	if (visited.contains(current_state._state_name))
	{
		return true;
	}

	visited.append(current_state._state_name);

	for (auto transition : _states[current_state._state_name]._transitions)
	{
		for (auto tr : transition)
		{
			if (tr != last_state._state_name)
			{
				if (tr < _states.size() &&		//avoid checking out of bound
					findCicle(_states[tr], _states[current_state._state_name], visited))
				{
					return true;
				}
			}
		}
	}

	visited.remove(current_state._state_name);

	return false;
}

//def findCicleOf(self, currentVertex, lastVertex, visited) :
//	if currentVertex in visited :
//return True
//visited.append(currentVertex)
//for adjacent in self.vertices[currentVertex] :
//	if adjacent != lastVertex :
//		if self.findCicleOf(adjacent, currentVertex, visited) :
//			return True
//visited.remove(currentVertex)
//return False


///////////////////////////////////////////////
// FAState
///////////////////////////////////////////////


FAState::FAState() :
	_parent(),
	_state_name(),
	_transitions(),
	_type()
{
}

FAState::FAState(FA * parent, NT state_name, QVector<TR> transitions, StateType type):
	_parent(parent),
	_state_name(state_name),
	_transitions(transitions),
	_type(type)
{
	
}

