#ifndef __RE_H__
#define __RE_H__

#include <string>
#include <QString>

#include "util/Alphabet.h"
#include "util/Subject.h"

class RE: public Subject
{
public:
	////////////////////////////////////////////////////////////
	/// \brief	Default constructor
	///
	////////////////////////////////////////////////////////////
	RE();

	////////////////////////////////////////////////////////////
	/// \brief	Constructor passing a QString to populate the 
	///			_re_str (Regular Expression string)
	///	\param QString re	QString to populate the _re_str
	///
	////////////////////////////////////////////////////////////
	RE(QString re);

	////////////////////////////////////////////////////////////
	/// \brief	Default destructor
	///
	////////////////////////////////////////////////////////////
	~RE();

	////////////////////////////////////////////////////////////
	/// \brief	set the RE passing a QString to populate the 
	///			_re_str (Regular Expression string)
	///	\param	QString re	QString to populate the _re_str
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool setReString(QString re);

	////////////////////////////////////////////////////////////
	/// \brief	Get the RE as a string.
	///	\return QString RE as a string
	///
	////////////////////////////////////////////////////////////
	QString getReString();




private:
	bool removeSpaces();
	bool addDot();
	bool verify(QString &re);


	QString _re_str;

	std::vector<char> _valid_terminals = { 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9' };
};


#endif // !__RE_H__
