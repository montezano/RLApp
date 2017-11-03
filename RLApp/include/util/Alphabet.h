#ifndef __ALPHABET_H__
#define __ALPHABET_H__

#include <vector>

#define NT	QString			//Not terminal
#define VT	QString			//Terminals

#define	StateType unsigned	//Regular, final, initial

#define REGULAR			1<0
#define FINAL			1<1
#define INITIAL			1<2


namespace Alphabet
{


	//struct Alphabet
	//{
	std::vector<char> _terminals = { 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9' };
	//};
}
#endif // !__ALPHABET_H__
