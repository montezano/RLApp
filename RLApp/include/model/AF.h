#ifndef __FA_H__
#define __FA_H__

#include "util/Alphabet.h"
#include "model/MapModel.h"
#include "util/Subject.h"

struct FAState;


class FA : public Subject
{
public:
	FA();
	~FA();

	//ACCESS FUNCTIONS
	void setTerminals(QVector<VT> terminals);
	void addTerminal(VT terminal);
	QVector<VT> getTerminals();
	bool addState(QVector<TR> transitions, StateType type);

	//
	bool isEmpty();
	bool isInfinite();
	bool determinize();

	// Return true if it removed sucessufully
	bool removeETransition();
	bool verify();

	// UTILS
	unsigned getNextStateName();
	QVector<NT> getFinalStates();
	QVector<TR> getEStateClosure(NT state_name);

private:
	bool findCicle(FAState current_state, FAState last_state, QVector<NT> visited);
	QVector<TR> getEStateClosure(FAState state, QVector<NT> visited);
	FAState findStateByName(NT state_name);
	void organizeTransition(TR& transition);


	QVector<VT> _terminals;
	QVector<FAState> _states;
	NT _last_state_add;

	//MapModel map;

};


struct FAState
{
public:
	FAState();
	FAState(FA* parent, NT state_name, QVector<TR> transitions, StateType type);

	FA* _parent;
	NT _state_name;
	QVector<TR> _transitions;
	StateType _type;
};


#endif // !__FA_H__
