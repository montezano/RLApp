#include "model/AF.h"

FA::FA() :
	_terminals(),
	_states(),
	_last_state_number_add(0)
{
	_null_state = new FAState(this, "NULL", 0x0);
	//_terminals << "Trans";
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
	if (!_terminals.contains(terminal))
	{
		_terminals << terminal;
	}
}

QVector<VT> FA::getTerminals()
{
	return _terminals;
}

QVector<FAState> FA::getStates()
{
	return _states;
}

FAState& FA::getState(VT state_name)
{
	for (FAState& state : _states)
	{
		if (state._state_name == state_name)
		{
			return state;
		}
	}
	
	return *_null_state;
}

QVector<DetFAState>& FA::getDetStates()
{
	return _states_determinized;
}

DetFAState FA::getDetStates(QString state_name)
{
	for (DetFAState state : _states_determinized)
	{
		if (state._state_name == state_name)
		{
			return state;
		}
	}
	return DetFAState(NULL, "NULL", 0x0);
}

NT FA::addState(QVector<TR> transitions, StateType type)
{
	if (transitions.size() != _terminals.size())
	{
		return QString::number(-1);
	}
	if (_states.size() == 0)
	{
		type = type | INITIAL;
		_last_state_number_add = 0;
	}
	_states << FAState(this, QString::number(getNextStateName()), transitions, type);
	return QString::number(_last_state_number_add);
}

NT FA::addState(QVector<QVector<int>> transitions, StateType type)
{
	QVector<TR> new_transitions;
	for (auto transition : transitions)
	{
		TR new_trans;
		for (auto state : transition)
		{
			new_trans << QString::number(state);
		}
		new_transitions << new_trans;
	}

	return addState(new_transitions, type);

}
NT FA::addState(NT state_name, QVector<TR> transitions, StateType type)
{
	if (transitions.size() != _terminals.size())
	{
		return QString::number(-1);
	}

	_states << FAState(this, state_name, transitions, type);
	return state_name;
}
NT FA::addState(FAState state)
{
	_states << state;
	return state._state_name;
}
FAState & FA::getInitialState()
{
	for (FAState& state : _states)
	{
		if (state._type & INITIAL)
		{
			return state;
		}
	}
	return _states[0];
	// TODO: insert return statement here
}

DetFAState & FA::getInitialDetState()
{
	for (DetFAState& state : _states_determinized)
	{
		if (state._type & INITIAL)
		{
			return state;
		}
	}
	return DetFAState();
	// TODO: insert return statement here
}

bool FA::setFinalState(VT state)
{
	getState(state)._type |= FINAL;
	return false;
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

	return !fertile_state.contains(_states[0]._state_name);
}

bool FA::isInfinite()
{
	QVector<NT> visited;

	return findCicle(getInitialState(), getInitialState(), visited);
}

bool FA::determinize()
{
	removeETransition();
	FAState old_ini_state = getInitialState();
	DetFAState ini_state = DetFAState(this,
							old_ini_state._state_name,
							old_ini_state._transitions,
							old_ini_state._type);
	_states_determinized << ini_state;

	QMap<QString, bool> new_states;		/// < QString: state name;
										/// < bool: visited or not (true for visited)
	new_states.insert(ini_state._state_name, true);

	//for (int i = 0; i < _terminals.size(); i++)
	//{
	
	reachableStateFrom({ getInitialState()._state_name}, new_states);

	//}

	if (!new_states.isEmpty())
	{
		bool unvisited = true;
		while (unvisited)
		{
			unvisited = false;
			for (auto next_state = new_states.begin(); next_state != new_states.end(); ++next_state)
			{
				if (!next_state.value())
				{
					QString str_state = next_state.key();
					TR state = strToTransition(str_state);

					int old_states_size = new_states.size();
					QVector<TR> trans = reachableStateFrom(state, new_states);
					
					if (new_states.size() != old_states_size)
					{
						unvisited = true;
					}

					StateType type = getDetStateType(state);

					_states_determinized << DetFAState(this, str_state, trans, type);
				}
				next_state.value() = true;
			}
		}
	}
	
	
	return true;
}

bool FA::removeETransition()
{
	if (_terminals.contains("&"))
	{
		for (FAState& state : _states)
		{
			QVector<TR> e_closure = getEStateClosure(state);
			for (int i = 0; i < _terminals.size(); i++)
			{
				state._transitions[i] += e_closure[i];
				organizeTransition(state._transitions[i]);

			}
			
		}

		for (FAState& state : _states)
		{
			state._transitions.remove(_terminals.size() - 1);	/// < remove the last transition
																///	it should be the & transition

		}

		_terminals.remove(_terminals.size() - 1);

		
	}
	
	return true;
}

bool FA::removeDeadStates()
{
	QVector<QString> f_states = getDetFinalStates();

	int f_states_size = f_states.size();
	int f_states_recount = 0;

	// makes a list of all states not dead
	while (f_states_size != f_states_recount)
	{
		f_states_size = f_states.size();
		for (DetFAState state : _states_determinized)
		{
			for (TR transition : state._transitions)
			{
				QVector<QString> f_states_temp = f_states;
				for (QString st_name : f_states_temp)
				{
					if (transition == strToTransition(st_name))
					{
						QString add_st = state._state_name;
						if (f_states.count(add_st) < 1)
						{
							f_states << add_st;
						}
					}
				}
				//f_states = f_states_temp;
			}
		}
		f_states_recount = f_states.size();
	}
	
	// remove dead states from the determinized FA

	QVector<QString> remove_list;
	//for (int i = 0; i < _states_determinized.size(); i++)
	for (DetFAState& det_state : _states_determinized)
	{
		bool remove = true;
		//for (DetFAState& det_state : _states_determinized)
		for (QString f_state : f_states)
		{
			if (det_state._state_name == f_state)
			{
				remove = false;
				break;
			}
		}
		if (remove)
		{
			remove_list << det_state._state_name;
		}
	}

	for (QString state : remove_list)
	{
		removeDetState(state);
	}

	for (DetFAState& state : _states_determinized)
	{
		for (QString remove : remove_list)
		{
			replaceTransition(state, strToTransition(remove), { QString::number(-1) });
		}
	}

	return true;
}

bool FA::removeEquivalenceClasses()
{
	QMap<QString, QVector<QString>> old_equiv_classes;
	QMap<QString, QVector<QString>> new_equiv_classes;
	old_equiv_classes.insert("0", QVector<QString>());
	old_equiv_classes.insert("1", QVector<QString>());
	
	for (int i = 0; i < _states_determinized.size(); i++)
	{
		if (_states_determinized[i]._type & FINAL)
		{
			old_equiv_classes.find("0").value().append(_states_determinized[i]._state_name);
		}
		else
		{
			old_equiv_classes.find("1").value().append(_states_determinized[i]._state_name);
		}
	}

	int old_size = old_equiv_classes.size();
	int new_size = 0;

	/// Until there is no change in the equivalence classes
	while (old_size != new_size)
	{
		old_size = old_equiv_classes.size();
		int class_number = 0;
		/// For all equivalence classes, do:
		for (auto equiv_class = old_equiv_classes.begin(); equiv_class != old_equiv_classes.end(); ++equiv_class)
		{
			QString e_class_name = equiv_class.key();
			/// For each value of this equivalence class, do:
			for (QString state : equiv_class.value())
			{
				QVector<TR> transitions = getDetStates(state)._transitions;


				for (TR transition : transitions)
				{
					QString str_trs = transitionToStr(transition);

					auto found_class = searchStateEquivalenceClass(str_trs, old_equiv_classes);
					//if (found_class == (old_equiv_classes.end()+1));
					//{
					//	return false;
					//}
					e_class_name += found_class.key();
				}
				auto add_class = new_equiv_classes.find(e_class_name);
				if (add_class != new_equiv_classes.end())
				{
					new_equiv_classes.find(e_class_name)->append(state);
				}
				else
				{
					new_equiv_classes.insert(e_class_name, { state });
				}				
			}
			class_number++;
		}
		new_size = new_equiv_classes.size();
		old_equiv_classes = new_equiv_classes;
		new_equiv_classes = QMap < QString, QVector<QString>>();
	}


	for (auto equiv_class : old_equiv_classes)
	{
		for (DetFAState& state : _states_determinized)
		{
			for (TR& transition : state._transitions)
			{
				for (int i = 1; i < equiv_class.size(); i++)
				{
					if (transition == strToTransition(equiv_class[i]))
					{
						transition = strToTransition(equiv_class[0]);
					}
				}
			}
		}
		for (int i = 1; i < equiv_class.size(); i++)
		{
			equiv_class.remove(i);
		}
	}

	for (auto equiv_class : old_equiv_classes)
	{
		for (int i = 1; i < equiv_class.size(); i++)
		{
			removeDetState(equiv_class[i]);
		}
	}
	

	return true;
}

bool FA::minimizeDeterministic()
{
	bool result = true;
	bool result_dead_state = removeDeadStates();
	bool result_equiv_class = removeEquivalenceClasses();
	return result & result_dead_state & result_equiv_class;
	// Good practices never die
	//  (o_O)
}

unsigned FA::getNextStateName()
{
	unsigned ret = _last_state_number_add;
	_last_state_number_add++;
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

QVector<QString> FA::getDetFinalStates()
{
	QVector<QString> fertile_state;

	for (DetFAState state : _states_determinized)
	{
		if (state._type & FINAL)
		{
			fertile_state << state._state_name;
		}
	}

	//for (int state = 0; state < _states_determinized.size(); state++)
	//{
	//	if (_states_determinized[state]._type & FINAL)
	//	{
	//		fertile_state << _states_determinized[state]._state_name;
	//	}
	//}

	return fertile_state;
}

QVector<TR> FA::getEStateClosure(NT state_name)
{

	return getEStateClosure(findStateByName(state_name), QVector<NT>());
}

QVector<TR> FA::getEStateClosure(FAState state)
{
	return getEStateClosure(state, QVector<NT>());
}

FA* FA::faUnion(FA& fa)
{
	determinize();
	minimizeDeterministic();

	fa.determinize();
	fa.minimizeDeterministic();

	for (DetFAState& state : _states_determinized)
	{
		state._state_name.prepend("A-");
		for (TR& transitions : state._transitions)
		{
			for (NT& transition : transitions)
			{
				transition.prepend("A-");
			}
		}
	}

	for (DetFAState& state : fa.getDetStates())
	{
		state._state_name.prepend("B-");
		for (TR& transitions : state._transitions)
		{
			for (NT& transition : transitions)
			{
				transition.prepend("B-");
			}
		}
	}



	FA* united_fa = new FA();

	QVector<VT> new_terminals;

	for (VT term : _terminals)
	{
		if (!new_terminals.contains(term))
		{
			new_terminals << term;
		}
	}

	for (VT term : fa.getTerminals())
	{
		if (!new_terminals.contains(term))
		{
			new_terminals << term;
		}
	}
	
	united_fa->setTerminals(new_terminals);
	FAState new_init_st;
	new_init_st._transitions.resize(new_terminals.size());
	////////////////////////////////////////
	DetFAState init_st_fa1 = getInitialDetState();

	new_init_st._parent= init_st_fa1._parent;
	new_init_st._state_name = getInitialDetState()._state_name + fa.getInitialDetState()._state_name;

	for (int i = 0; i < init_st_fa1._transitions.size(); i++)
	{
		new_init_st._transitions[new_terminals.indexOf(_terminals[i])] << init_st_fa1._transitions[i];
	}

	////////////////////////////////////
	DetFAState init_st_fa2 = fa.getInitialDetState();

	new_init_st._parent = init_st_fa2._parent;

	for (int i = 0; i < init_st_fa2._transitions.size(); i++)
	{
		new_init_st._transitions[new_terminals.indexOf(_terminals[i])] << init_st_fa2._transitions[i];
	}

	///////////////////////////////////////////////
	new_init_st._type = init_st_fa2._type | init_st_fa2._type;

	for (int i = 0; i < fa.getInitialDetState()._transitions.size(); i++)
	{
		new_init_st._transitions[i] << fa.getInitialDetState()._transitions[i];
	}
	//new_init_st._transitions << fa.getInitialDetState()._transitions;

	united_fa->addState(new_init_st);

	for (DetFAState& state : _states_determinized)
	{
		DetFAState new_state;
		new_state._transitions.resize(new_terminals.size());
		if (state._type & INITIAL)
		{
			state._type &= ~(INITIAL);
		}
		for (int i = 0; i < state._transitions.size(); i++)
		{
			new_state._transitions[new_terminals.indexOf(_terminals[i])] << state._transitions[i];
		}
		new_state._parent = state._parent;
		new_state._state_name = state._state_name;
		new_state._type = state._type;

		united_fa->addState(new_state);
	}

	for (DetFAState& state : fa.getDetStates())
	{
		DetFAState new_state;
		new_state._transitions.resize(new_terminals.size());
		if (state._type & INITIAL)
		{
			state._type &= ~(INITIAL);
		}
		for (int i = 0; i < state._transitions.size(); i++)
		{
			new_state._transitions[new_terminals.indexOf(fa.getTerminals()[i])] << state._transitions[i];
		}
		new_state._parent = state._parent;
		new_state._state_name = state._state_name;
		new_state._type = state._type;

		united_fa->addState(new_state);
	}

	return united_fa;
}

FA* FA::faComplement()
{
	FA* ret_fa = new FA();

	ret_fa->setTerminals(getTerminals());
	for (FAState state : _states)
	{
		if (state._type & FINAL)
		{
			FAState temp_state = FAState(this, state._state_name, (state._type & ~(FINAL)));
			temp_state._transitions.resize(state._transitions.size());
			for (int i = 0; i < state._transitions.size(); i++)
			{
				temp_state._transitions[i] = state._transitions[i];
			}
			ret_fa->addState(temp_state);
		}
		else if (state._type & REGULAR)
		{
			FAState temp_state = FAState(this, state._state_name, (state._type | FINAL_ST));
			temp_state._transitions.resize(state._transitions.size());
			for (int i = 0; i < state._transitions.size(); i++)
			{
				temp_state._transitions[i] = state._transitions[i];
			}
			ret_fa->addState(temp_state);
		}
	}

	return ret_fa;
}

FA* FA::faIntersection(FA fa)
{
	FA* fa1_comp = faComplement();
	fa1_comp->determinize();
	FA* fa2_comp = fa.faComplement();
	fa2_comp->determinize();

	return fa1_comp->faUnion(*fa2_comp);
}

bool FA::faEquivalent(FA fa)
{
	FA* fa1 = new FA(fa);
	fa1->determinize();
	fa1->minimizeDeterministic();

	FA* fa1_comp = fa1->faComplement();
	fa1_comp->determinize();
	fa1_comp->minimizeDeterministic();

	FA* fa2 = new FA(*this);
	fa2->determinize();
	fa2->minimizeDeterministic();

	FA* fa2_comp = fa2->faComplement();
	fa2_comp->determinize();
	fa2_comp->minimizeDeterministic();
	
	FA* fa1_int_cfa2 = fa1->faIntersection(*fa2_comp);
	fa1_int_cfa2->determinize();
	fa1_int_cfa2->minimizeDeterministic();

	FA* fa2_int_cfa1 = fa2->faIntersection(*fa1_comp);
	fa2_int_cfa1->determinize();
	fa2_int_cfa1->minimizeDeterministic();

	bool ret = fa1_int_cfa2->isEmpty();
	ret &= fa2_int_cfa1->isEmpty();



	return ret;
}

bool FA::findCicle(FAState current_state, FAState last_state, QVector<NT> visited)
{
	if (visited.contains(current_state._state_name))
	{
		return true;
	}

	visited.append(current_state._state_name);


	for (auto transition : current_state._transitions)
	{
		for (auto tr : transition)
		{
			if (tr != last_state._state_name)
			{
				FAState& tr_to_st = getState(tr);
				if (tr_to_st._state_name != "NULL" &&
					findCicle(tr_to_st, current_state, visited))
				{
					return true;
				}
			}
		}
	}
	visited.removeOne(current_state._state_name);

	return false;
}

QVector<TR> FA::getEStateClosure(FAState state, QVector<NT> visited)
{
	QVector<TR> closure = state._transitions;

	visited.push_back(state._state_name);
	int epsilon_index = _terminals.indexOf("&");
	if (epsilon_index != -1)
	{	
		for (NT transition : state._transitions[epsilon_index])
		{
			if (!visited.contains(transition))
			{
				QVector<TR> ret = getEStateClosure(findStateByName(transition), visited);
				for (int i = 0; i < ret.size(); i++)
				{
					closure[i] << ret[i];
					organizeTransition(closure[i]);
				}
			}
		}
	}

	return closure;
}

FAState FA::findStateByName(NT state_name)
{
	for (auto state : _states)
	{
		if (state._state_name == state_name)
		{
			return state;
		}
	}
	return FAState();
}

void FA::organizeTransition(TR& transition)
{
	for (NT tr : transition)
	{
		if (transition.count(tr) > 1)
		{
			for (int i = 0; i < transition.count(tr) -1; i++)
			{
				transition.removeOne(tr);
			}
		}
	}

	qSort(transition);
}

QString FA::transitionToStr(TR transition) const
{
	QString ret;
	for (auto tr : transition)
	{
		ret += tr+"-";

	}
	if (!ret.isEmpty())
	{
		ret.remove(ret.count() - 1, ret.count() - 1);
	}
	return ret;
}

TR FA::strToTransition(QString transition)
{
	//if (transition.contains('A') || transition.contains('B'))
	//{
	//	transition.remove(0, 2);
	//}
	QStringList tr_list = transition.split("-");
	TR ret;
	for (QString tr : tr_list)
	{
		
		//bool ok;
		//unsigned i = tr.toUInt(&ok);
		//if (ok)
		//{
			ret << tr;

		//}
	}
	return ret;
}

QVector<TR> FA::reachableStateFrom(TR transitions, QMap<QString, bool>& added)
{
	QVector<TR> ret;
	ret.resize(_terminals.size());

	for (int i = 0; i < _terminals.size(); i++)
	{

		for (auto tr : transitions)
		{
			if (getState(tr)._state_name != _null_state->_state_name)
			{
				for (NT nt : getState(tr)._transitions[i])
				{
					ret[i] << nt;
				}

			}
			
		}
		organizeTransition(ret[i]);
		QString st_name = transitionToStr(ret[i]);
		if (!st_name.isEmpty() && !added.contains(st_name))
		{
			added.insert(st_name, false);
		}		
	}

	return ret;
}

StateType FA::getDetStateType(TR state_name)
{
	StateType type = 1 << 0;

	for (auto t : state_name)
	{
		type = type | getState(t)._type;
	}

	return type & ~(INITIAL);
}

QMap<QString, QVector<QString>>::iterator FA::searchStateEquivalenceClass(QString state, QMap<QString, QVector<QString>>& equiv_classes)
{
	for (auto equiv_class = equiv_classes.begin(); equiv_class != equiv_classes.end(); ++equiv_class)
	{
		for (QString e_class_state : equiv_class.value())
		{
			if (e_class_state == state)
			{
				return equiv_class;
			}
		}
	}
	return equiv_classes.end();
}

bool FA::removeDetState(QString state_name)
{
	for (int i = 0; i < _states_determinized.size(); i++)
	{
		if (_states_determinized[i]._state_name == state_name)
		{
			_states_determinized.remove(i);
			return true;
		}
	}
	return false;
}

bool FA::replaceTransition(DetFAState & state, TR find, TR replace)
{
	for (TR& transition : state._transitions)
	{
		if (transition == find)
		{
			transition = replace;
		}
	}

	return true;
}

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

FAState::FAState(FA * parent, NT state_name, StateType type) :
	_parent(parent),
	_state_name(state_name),
	_type(type)
{

}

FAState::FAState(DetFAState & state) :
	_parent(state._parent),
	_state_name(state._state_name),
	_transitions(state._transitions),
	_type(state._type)
{
}


///////////////////////////////////////////////
// DetFAState
///////////////////////////////////////////////


DetFAState::DetFAState() :
	_parent(),
	_state_name(),
	_transitions(),
	_type()
{
}

DetFAState::DetFAState(FA * parent, NT state_name, QVector<TR> transitions, StateType type) :
	_parent(parent),
	_state_name(state_name),
	_transitions(transitions),
	_type(type)
{

}

DetFAState::DetFAState(FA * parent, NT state_name, StateType type) :
	_parent(parent),
	_state_name(state_name),
	_type(type)
{

}

DetFAState::DetFAState(FAState & state) :
	_parent(state._parent),
	_state_name(state._state_name),
	_transitions(state._transitions),
	_type(state._type)
{
}
