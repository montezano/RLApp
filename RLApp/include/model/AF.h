#ifndef __FA_H__
#define __FA_H__

#include "util/Alphabet.h"
#include "model/MapModel.h"
#include "util/Subject.h"

//class FAState;


class FA : public Subject
{
public:
	void setFA(/*QMap< map*/);
	void getFA();

	bool verify();

private:
	QList<QString> _terminals;
	QList<FAState> _states;


	MapModel map;

};


class FAState
{
public:
	FAState(FA* parent, NT state_name, QList<VT> transitions, StateType type);
	~FAState();

private:
	FA* _parent;
	NT _state_name;
	QList<VT> _transitions;
	StateType _type;


};


#endif // !__FA_H__
