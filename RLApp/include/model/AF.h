#ifndef __FA_H__
#define __FA_H__

#include "util/Alphabet.h"
#include "model/MapModel.h"
#include "util/Subject.h"

struct FAState;
struct DetFAState;



class FA : public Subject
{
public:
	FA();
	~FA();


	

	////////////////////////////////////////////////////////////
	/// ACCESS FUNCTIONS
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
	/// \brief	Set the vector with terminals. Make a copy to the
	///			existing QVector<VT>
	///	\param	QVector<VT> set the terminals of the FA
	///
	////////////////////////////////////////////////////////////
	void setTerminals(QVector<VT> terminals);

	////////////////////////////////////////////////////////////
	/// \brief	Add another terminal to the terminal QVector<VT>
	///	\param	VT terminal
	///
	////////////////////////////////////////////////////////////
	void addTerminal(VT terminal);

	////////////////////////////////////////////////////////////
	/// \brief	Get a copy of the QVector with terminals.
	///	\return	QVector<VT> A copy of the QVector<VT> with all
	///			terminals.
	///
	////////////////////////////////////////////////////////////
	QVector<VT> getTerminals();

	////////////////////////////////////////////////////////////
	/// \brief	Get the list of states of the FA
	///	\return	QVector<FAState> list of States
	///
	////////////////////////////////////////////////////////////
	QVector<FAState> getStates();

	////////////////////////////////////////////////////////////
	/// \brief	Get the desired state
	///	\return	desired state
	///
	////////////////////////////////////////////////////////////
	FAState& getState(VT state_name);


	////////////////////////////////////////////////////////////
	/// \brief	Get the list of states from the deterministic FA.
	///	\return	QVector<FAState> list of Deterministic States
	///
	////////////////////////////////////////////////////////////
	QVector<DetFAState>& getDetStates();

	////////////////////////////////////////////////////////////
	/// \brief	Get a state of the deterministic FA by it's name.
	///	\param	QString	state name
	///	\return	DetFAState determistic FA state
	///
	////////////////////////////////////////////////////////////
	DetFAState getDetStates(QString state_name);

	////////////////////////////////////////////////////////////
	/// \brief	Add a new state to the FA.
	///	\param	QVector<TR> with the transitions of the state.
	///			Transitions may be non deterministic (more than
	///			transition for the same terminal)
	///	\param	StateType	define if the state is FINAL, REGULAR,
	///			INITIAL or a combination of those.
	///	\return	bool if the operation were done successufully
	///
	////////////////////////////////////////////////////////////
	NT addState(QVector<TR> transitions, StateType type);

	////////////////////////////////////////////////////////////
	/// \brief	Add a new state to the FA.
	///	\param	QVector<TR> with the transitions of the state.
	///			Transitions may be non deterministic (more than
	///			transition for the same terminal)
	///	\param	StateType	define if the state is FINAL, REGULAR,
	///			INITIAL or a combination of those.
	///	\return	bool if the operation were done successufully
	///
	////////////////////////////////////////////////////////////
	NT addState(QVector<QVector<int>> transitions, StateType type);

	////////////////////////////////////////////////////////////
	/// \brief	Add a new state to the FA.
	///	\param	QVector<TR> with the transitions of the state.
	///			Transitions may be non deterministic (more than
	///			transition for the same terminal)
	///	\param	StateType	define if the state is FINAL, REGULAR,
	///			INITIAL or a combination of those.
	///	\return	bool if the operation were done successufully
	///
	////////////////////////////////////////////////////////////
	NT addState(NT state_name, QVector<TR> transitions, StateType type);

	////////////////////////////////////////////////////////////
	/// \brief	Add a new state to the FA.
	///	\param	QVector<TR> with the transitions of the state.
	///			Transitions may be non deterministic (more than
	///			transition for the same terminal)
	///	\param	StateType	define if the state is FINAL, REGULAR,
	///			INITIAL or a combination of those.
	///	\return	bool if the operation were done successufully
	///
	////////////////////////////////////////////////////////////
	NT addState(FAState state);

	FAState& getInitialState();

	DetFAState& getInitialDetState();

	bool setFinalState(VT state);

	////////////////////////////////////////////////////////////
	/// MAIN FUNCTIONS
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
	/// \brief	Verify if the actual FA is empty. An empty FA is
	///			one such that the initial state is dead.
	///	\return	true if the actual FA is empty, false otherwise.
	///
	////////////////////////////////////////////////////////////
	bool isEmpty();

	////////////////////////////////////////////////////////////
	/// \brief	Verify if the actual FA is infinite of finite.
	///			An infinite FA is one that generate sentences with
	///			infite length.
	///	\return	true if the actual FA is infinite, false otherwise.
	///
	////////////////////////////////////////////////////////////
	bool isInfinite();

	////////////////////////////////////////////////////////////
	/// \brief	Determinize the actual AF. The process consist
	///			on removing the & transitions, and processing the
	///			AF if it's an FDA, nothing will be done. If it's
	///			a FNDA, it will be determinized.
	///	\return	true if the process was completed successufully.
	///			false otherwise.
	///
	////////////////////////////////////////////////////////////
	bool determinize();

	////////////////////////////////////////////////////////////
	/// \brief	Remove the E transitions from the actual FA. This
	///			method is necessary for the determinization algorithm.
	///	\return	true if the process was completed successufully.
	///			false otherwise.
	///
	////////////////////////////////////////////////////////////
	bool removeETransition();

	////////////////////////////////////////////////////////////
	/// \brief	Remove FA states that don't produce or don't point
	///			to any state that's final. Only works on a
	///			determinized FA.
	///	\return	bool true if finished correctly, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool removeDeadStates();

	////////////////////////////////////////////////////////////
	/// \brief	Group the existing states in equivalence classes
	///			and remove the duplicates
	///	\return	bool true if finished correctly, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool removeEquivalenceClasses();

	////////////////////////////////////////////////////////////
	/// \brief	Minimize the FA previuosly determinized. It execute
	///			two operations:
	///			remove the dead states
	///			remove the equivalent states
	///	\return	bool true if finished correctly, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool minimizeDeterministic();

	FA* faUnion(FA& fa);

	FA* faComplement();

	FA* faIntersection(FA fa);

	bool faEquivalent(FA fa);


	////////////////////////////////////////////////////////////
	/// UTILS
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
	/// \brief	Get the state name to be added next. Use this method
	///			if you're adding a new state to the FA.
	///	\return	unsigned the name of the next state name.
	///
	////////////////////////////////////////////////////////////
	unsigned getNextStateName();

	////////////////////////////////////////////////////////////
	/// \brief	Get a list with all final states from the current FA.
	///	\return	QVector<NT> with all final states
	///
	////////////////////////////////////////////////////////////
	QVector<NT> getFinalStates();

	////////////////////////////////////////////////////////////
	/// \brief	Get a list with all final states from the current FA.
	///	\return	QVector<QString> with all final states
	///
	////////////////////////////////////////////////////////////
	QVector<QString> getDetFinalStates();

	////////////////////////////////////////////////////////////
	/// \brief	Get a list of all the states that makes the &
	///			transition closure for a gien state. & transition
	///			closure consist of all states reachable from the
	///			& transition from the given state.
	///	\param	NT		the name of the state to get the &
	///					state closure.
	///	\return	QVector<TR> the list of all states reachable from
	///			& transition.
	///
	////////////////////////////////////////////////////////////
	QVector<TR> getEStateClosure(NT state_name);

	////////////////////////////////////////////////////////////
	/// \brief	Get a list of all the states that makes the &
	///			transition closure for a gien state. & transition
	///			closure consist of all states reachable from the
	///			& transition from the given state.
	///	\param	FAState	the state to get the & transition.
	///	\return	QVector<TR> the list of all states reachable from
	///			& transition.
	///
	////////////////////////////////////////////////////////////
	QVector<TR> getEStateClosure(FAState state);



protected:
	bool findCicle(FAState current_state, FAState last_state, QVector<NT> visited);
	QVector<TR> getEStateClosure(FAState state, QVector<NT> visited);
	FAState findStateByName(NT state_name);
	void organizeTransition(TR& transition);
	QString transitionToStr(TR transition) const;
	TR strToTransition(QString transition);
	//void determinizeState(FAState state);
	QVector<TR> reachableStateFrom(TR transitions, QMap<QString, bool>& added);
	StateType getDetStateType(TR state_name);
	QMap<QString, QVector<QString>>::iterator searchStateEquivalenceClass(QString state, QMap<QString, QVector<QString>>& equiv_classes);
	bool removeDetState(QString state_name);
	bool replaceTransition(DetFAState& state, TR find, TR replace);



	QVector<VT> _terminals;
	QVector<FAState> _states;
	QVector<DetFAState> _states_determinized;
	QMap<QString, TR> _state_name_map;
	FAState* _null_state;
	int _last_state_number_add;

	//MapModel map;

};


struct FAState
{
public:
	FAState();
	FAState(FA* parent, NT state_name, QVector<TR> transitions, StateType type);
	FAState(FA* parent, NT state_name, StateType type);
	FAState(DetFAState& state);

	FA* _parent;
	NT _state_name;
	QVector<TR> _transitions;
	StateType _type;
};

struct DetFAState
{
public:
	DetFAState();
	DetFAState(FA* parent, NT state_name, QVector<TR> transitions, StateType type);
	DetFAState(FA* parent, NT state_name, StateType type);
	DetFAState(FAState& state);

	FA* _parent;
	QString _state_name;
	QVector<TR> _transitions;
	StateType _type;
};

#endif // !__FA_H__
