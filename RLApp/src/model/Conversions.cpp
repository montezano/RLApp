#include "model/Conversions.h"

FA* Conversions::reToFA(RE re)
{
	FA* fa = new FA();

	re.parse();
	QVector<Node*> di_simone_composition = re.buildDiSimoneComposition();
	QVector<VT> terminals = getTerminals(*fa, di_simone_composition);

	terminals.append("&");
	fa->setTerminals(terminals);
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
	last_state_add = fa->addState(st_transitions, getStateType(composition));


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

		last_state_add = fa->addState(st_transitions, getStateType(composition));
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

		last_state_add = fa->addState(st_transitions, getStateType(composition));
	}

	return fa;
}

FA* Conversions::grToFA(RG rg)
{
	QVector<VT> terminals;
	QString final_state = "$$$";
	//QMap<PLeft, int> states_map;
	QVector<PLeft> states_map;
	QVector<PLeft> added_states;

	int st_count = 1;
	QList<PLeft> p_left = rg.getProductionLeft();
	FA* fa = new FA();

	QMap<QString, QPair<VT, QString>> transitions_map;

	states_map << rg.getInitial();

	for (PLeft prod : p_left)
	{
		if (!added_states.contains(prod))
		{
			if (prod != states_map[0])
			{
				states_map << prod;
			}
			added_states << prod;
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
	states_map << final_state;
	fa->setTerminals(terminals);

	for (auto key : states_map)
	{
		QVector<TR> new_trans;
		new_trans.resize(terminals.size());

		for (auto transition : transitions_map.values(key))
		{
			if (!new_trans[terminals.indexOf(transition.first)].contains(QString::number(states_map.indexOf(key))))
			{
				new_trans[terminals.indexOf(transition.first)] << QString::number(states_map.indexOf(transition.second));
			}
		}
		fa->addState(new_trans, (key == "$$$" ? FINAL_ST : REGULAR));
	}
	/*QVector<TR> trans;
	trans.resize(terminals.size());*/

	//fa.addState( trans, FINAL);
	return fa;
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
			transition << QString::number(node->comp_index);
		}
	}
	return transition;
}

StateType Conversions::getStateType(QVector<Node*> di_simone_composition)
{
	if (di_simone_composition.size() == 0)
	{
		return FINAL_ST;
	}
	for (Node* node : di_simone_composition)
	{
		if (node->symbol == PILE_END)
		{
			return FINAL_ST;
		}
	}
	return REGULAR;
}
