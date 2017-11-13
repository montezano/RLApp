#ifndef __RE_H__
#define __RE_H__

#include <string>
#include <QString>

#include "util/Alphabet.h"
#include "util/Subject.h"

struct Node;

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
	/// \brief	Get di Simone parser tree root node.
	///	\return Node* di Simomne parser tree root node.
	///
	////////////////////////////////////////////////////////////
	Node* getDiSimoneTree();

	////////////////////////////////////////////////////////////
	/// \brief	Parse the desired symbol, spliting the RE in
	///			before and after and returnin a list of sub
	///			RE strings. This method is used to separete the
	///			RE string betwen disjunction and conjunction
	///			operators.
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	QList<QString> parseSymbol(QChar symbol);

	////////////////////////////////////////////////////////////
	/// \brief	Parse the entire RE through theh recursive
	///			method parse(QString).
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool parse();

	////////////////////////////////////////////////////////////
	/// \brief	Parse the string RE recursively, building the
	///			DiSimone tree.
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool parse(QString re, Node* tree);



private:
	bool removeSpaces();
	bool normalize();
	bool verify(QString &re);
	////////////////////////////////////////////////////////////
	/// \brief	Parse the desired symbol, spliting the RE in
	///			before and after and returnin a list of sub
	///			RE strings. This method is used to separete the
	///			RE string betwen disjunction and conjunction
	///			operators.
	///	\return	bool true if set successufully, false otherwise
	///
	////////////////////////////////////////////////////////////
	QList<QString> parseSymbol(QChar symbol, QString re);


	QString _original_re;
	QString _normalized_re;
	Node* _di_simone_tree;

	QVector<QChar> _valid_terminals = { 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9' };
	QVector<QChar> _operators = { CLOSURE, OPTION, OP_PARENT, CL_PARENT,
		CONJUNCT, DISJUNCT };
	QVector<QChar> _end_operators = { CLOSURE, CL_PARENT, OPTION };
	QVector<QChar> _open_operators = { OP_PARENT };

};

struct Node
{
public:
	Node() {}
	Node(Node* par) : parent(par) {}

	Node* parent;
	Node* left_children;
	Node* right_children;
	QChar symbol;
};


#endif // !__RE_H__
