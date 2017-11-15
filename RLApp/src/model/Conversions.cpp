#include "model/Conversions.h"

FA Conversions::reToFA(RE re)
{
	FA fa = FA();

	re.parse();
	QVector<Node*> di_simone_composition = re.buildDiSimoneComposition();
	QVector<VT> terminals = getTerminals(fa, di_simone_composition);

	terminals.append("&");
	fa.setTerminals(terminals);
	QVector<Node*> composition = re.initialDiSimonePath();


	NT last_state_add;
	QVector<TR> st_transitions;
	QVector<TR> nd_states;

	//first state (q0)
	for (VT terminal : terminals)
	{
		TR transition = createTransition(composition, terminal);
		st_transitions << transition;
		if (transition.size() > 1)
		{
			if (!nd_states.contains(transition))
			{
				nd_states << transition;
			}
		}
	}
	last_state_add = fa.addState(st_transitions, getStateType(composition));


	//basic states (q1, q2, q3...)
	for (int i = 0; i < di_simone_composition.size() - 1; i++)
	{
		st_transitions.clear();
		composition = re.followSimoneTreeFrom(di_simone_composition[i]);
		for (VT terminal : terminals)
		{
			TR transition = createTransition(composition, terminal);
			st_transitions << transition;
			if (transition.size() > 1)
			{
				if (!nd_states.contains(transition))
				{
					nd_states << transition;
				}
			}
		}

		last_state_add = fa.addState(st_transitions, getStateType(composition));
	}

	//composite non deterministic states (q1q2, q213, ...)
	for(TR state : nd_states)
	{
		QVector<TR> st_transitions;
		for (int i = 0; i < terminals.size(); i++)
		{
			if (terminals[i] == "&")
			{
				st_transitions << state;
			}
			else
			{
				st_transitions.append({});
			}
		}

		last_state_add = fa.addState(st_transitions, getStateType(composition));
	}

	return fa;
}

FA Conversions::grToFA(RG rg)
{
	QVector<VT> terminals;
	QString final_state = "$$$";
	QMap<PLeft, int> states_map;
	int st_count = 1;
	QList<PLeft> p_left = rg.getProductionLeft();
	PLeft init_prod = rg.getInitial();
	FA fa = FA();

	QMap<QString, QPair<VT, QString>> transitions_map;
	QVector<QString> added_state;

	for (PLeft prod : p_left)
	{
		if (!added_state.contains(prod))
		{
			if (prod == init_prod)
			{
				states_map.insert(prod, 0);
				added_state << prod;
			}
			else
			{
				states_map.insert(prod, st_count);
				st_count++;
				added_state << prod;
			}

			QList<PRight> p_rules = rg.getProduction(prod);

			for (PRight rule : p_rules)
			{
				if (rule[0].isLower())
				{
					if (!terminals.contains(QString(rule[0])))
					{
						terminals << QString(rule[0]);
					}
					if (rule.size() < 2)
					{
						transitions_map.insertMulti(prod, QPair<VT, QString>(QString(rule[0]), final_state));
					}
					else if (rule.size() >= 2)
					{
						transitions_map.insertMulti(prod, QPair<VT, QString>(QString(rule[0]), rule.right(1)));
					}
				}
			}
		}
	}
	states_map.insert(final_state, st_count);
	added_state.clear();
	fa.setTerminals(terminals);
	for (auto key : transitions_map.keys())
	{
		QVector<TR> new_trans;
		new_trans.resize(terminals.size());

		for (auto transition : transitions_map.values(key))
		{
			if (!new_trans[terminals.indexOf(transition.first)].contains(states_map.value(key)))
			{
				new_trans[terminals.indexOf(transition.first)] << states_map.value(transition.second);
			}
		}
		if (!added_state.contains(key))
		{
			fa.addState(new_trans, (key == "$$$" ? FINAL : REGULAR));
			added_state << key;
		}
	}
	QVector<TR> trans;
	trans.resize(terminals.size());
	//for (VT terminal : terminals)
	//{
	//	trans << TR();
	//}
	fa.addState( trans, FINAL);
	return FA();
}

QVector<VT> Conversions::getTerminals(FA& fa, QVector<Node*> di_simone_composition)
{
	QVector<VT> terminals;
	int i = 1;
	for (Node* node : di_simone_composition)
	{
		if (!terminals.contains(node->symbol) &&
			node->symbol != PILE_END)
		{
			terminals << node->symbol;
		}
		node->comp_index = i;
		i++;
	}


	for (int i = 0; i < di_simone_composition.size(); i++)
	{
		
	}
	return terminals;
}

QString Conversions::compositionToString(QVector<Node*> di_simone_composition)
{
	QString ret;
	for (Node* node : di_simone_composition)
	{
		ret += QString::number(node->comp_index) + node->symbol;
	}

	return ret;
}

TR Conversions::createTransition(QVector<Node*> di_simone_composition, VT terminal)
{
	TR transition;
	for (Node* node : di_simone_composition)
	{
		if (node->symbol == terminal)
		{
			transition << node->comp_index;
		}
	}
	return transition;
}

StateType Conversions::getStateType(QVector<Node*> di_simone_composition)
{
	for (Node* node : di_simone_composition)
	{
		if (node->symbol == PILE_END)
		{
			return FINAL | REGULAR;
		}
	}
	return REGULAR;
}
