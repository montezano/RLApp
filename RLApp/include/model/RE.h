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
	///			_re_str (Regular Expression string). The param
	///			string will have blank spaces removed and
	///			conjunction operators explicited.
	///	\param	QString re	QString to populate the _re_str
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool setReString(QString re);

	////////////////////////////////////////////////////////////
	/// \brief	Get the RE original string.
	///	\return QString RE original string
	///
	////////////////////////////////////////////////////////////
	QString getOriginalReString();

	////////////////////////////////////////////////////////////
	/// \brief	Get the RE with concatenation operations 
	///			explicit.
	///	\return QString RE original string
	///
	////////////////////////////////////////////////////////////
	QString getDotReString();

	////////////////////////////////////////////////////////////
	/// \brief	Parse the | operators, spliting the RE in
	///			before and after and returnin a list of sub
	///			RE strings.
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	QList<QString> parseFirstStep();




private:
	bool removeSpaces();
	bool addDot();
	bool verify(QString &re);


	QString _original_re;
	QString _dot_re;

	QVector<QChar> _valid_terminals = { 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9' };

	QVector<QChar> _end_operators = { CLOSURE, CL_PARENT, OPTION };
	QVector<QChar> _open_operators = { OP_PARENT };

};


#endif // !__RE_H__
