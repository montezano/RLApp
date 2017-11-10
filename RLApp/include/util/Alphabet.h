#ifndef __ALPHABET_H__
#define __ALPHABET_H__

#include <vector>
#include <QVector>
#include <QString>

typedef QString VT;		//Terminals
typedef unsigned NT;			//Not terminal
typedef QVector<NT> TR;	//Transitions

#define	StateType unsigned	//Regular, final, initial

#define REGULAR			1<<0
#define FINAL			1<<1
#define INITIAL			1<<2

#define FINAL_ST		REGULAR | FINAL


//namespace Alphabet
//{
//
//
//	//struct Alphabet
//	//{
//	std::vector<char> _valid_terminals = { 'a', 'b', 'c', 'd',
//		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
//		'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z', '0', '1', '2', '3', '4',
//		'5', '6', '7', '8', '9' };
//	//};
//}
#endif // !__ALPHABET_H__
