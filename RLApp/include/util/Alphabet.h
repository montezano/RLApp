#ifndef __ALPHABET_H__
#define __ALPHABET_H__

#include <vector>
#include <QVector>
#include <QString>

typedef QString VT;		//Terminals
typedef int NT;			//Not terminal
typedef QVector<NT> TR;	//Transitions

#define	StateType unsigned	//Regular, final, initial

#define REGULAR			1<<0
#define FINAL			1<<1
#define INITIAL			1<<2

#define FINAL_ST		REGULAR | FINAL

#define CLOSURE		'*'
#define OP_PARENT	'('
#define CL_PARENT	')'
#define OPTION		'?'
#define DISJUNCT	'|'
#define	CONJUNCT	'.'

#endif // !__ALPHABET_H__
