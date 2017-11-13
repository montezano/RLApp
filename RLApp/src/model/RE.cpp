#include "model\RE.h"

RE::RE()
{
}


RE::RE(QString re)
{
	_original_re = re;
	removeSpaces();
}

RE::~RE()
{
}

bool RE::setReString(QString re)
{
	_original_re = re;
	if (!removeSpaces())
	{
		return false;
	}
	if (!normalize())
	{
		return false;
	}
	return true;
}

QString RE::getOriginalReString()
{
	return _original_re;
}

QString RE::getDotReString()
{
	return _normalized_re;
}

Node * RE::getDiSimoneTree()
{
	return _di_simone_tree;
}

QList<QString> RE::parseSymbol(QChar symbol)
{
	return parseSymbol(symbol, _normalized_re);
}

bool RE::parse()
{
	_di_simone_tree = new Node(NULL);
	return parse(_normalized_re, _di_simone_tree);
}

bool RE::parse(QString re, Node* tree)
{
	bool ret = true;
	QList<QString> disj_parse;
	QList<QString> conj_parse;

	disj_parse = parseSymbol(DISJUNCT, re);
	if (disj_parse.size() > 1)
	{
		tree->symbol = DISJUNCT;
		tree->left_children = new Node(tree);
		tree->right_children = new Node(tree);

		ret &= parse(disj_parse[0], tree->left_children);
		ret &= parse(disj_parse[1], tree->right_children);
	}
	else
	{
		conj_parse = parseSymbol(CONJUNCT, re);
		if (conj_parse.size() > 1)
		{
			tree->symbol = CONJUNCT;
			tree->left_children = new Node(tree);
			tree->right_children = new Node(tree);

			ret &= parse(conj_parse[0], tree->left_children);
			ret &= parse(conj_parse[1], tree->right_children);
		}
		else
		{
			if (re[0] == OP_PARENT)
			{
				if (re[re.size() - 1] == OPTION || re[re.size() - 1] == CLOSURE)
				{
					tree->symbol = re[re.size() - 1];
					re.remove(re.size() - 1, 1);
					tree->left_children = new Node(tree);
					tree = tree->left_children;
				}
				

				re.remove(0, 1);
				re.remove(re.size() - 1, 1);
				
				parse(re, tree);
			}
			else
			{
				if ((re.size() > 1) && 
					(re[1] == OPTION || re[1] == CLOSURE))
				{
					tree->symbol = re[1];
					tree->left_children = new Node(tree);
					tree = tree->left_children;
				}
				tree->symbol = re[0];
				ret = true;
			}
		}
	}

	return ret;
}

bool RE::removeSpaces()
{
	if (_original_re.remove(" ") != "")
	{
		return true;
	}
	return false;
}

bool RE::normalize()
{
	for (int i = 0; i < _original_re.size() - 1; i++)
	{
		_normalized_re += _original_re[i];

		if (_valid_terminals.contains(_original_re[i]))
		{
			if ((_valid_terminals + _open_operators).contains(_original_re[i + 1]))
			{
				_normalized_re += '.';
			}
		}
		else
		{
			if (_end_operators.contains(_original_re[i]))
			{
				if ((_valid_terminals + _open_operators).contains(_original_re[i + 1]))
				{
					_normalized_re += '.';
				}
			}
		}
	}
	_normalized_re += _original_re[_original_re.size() - 1];

	return false;
}

bool RE::verify(QString& re)
{
	//for (auto terminal = re.begin; terminal != re.end; terminal++)
	//{
	//	//if ()
	//}
	//Alphabet::_terminals.
	return false;
}

QList<QString> RE::parseSymbol(QChar symbol, QString re)
{
	int parse_position;
	int last_position = 0;
	int parenthesis_count = 0;
	for (int i = 0; i < re.size(); i++)
	{
		if (re[i] == symbol && parenthesis_count == 0)
		{
			parse_position = i;
			break;
		}
		else
		{
			if (re[i] == OP_PARENT)
			{
				parenthesis_count++;
			}
			else
			{
				if (re[i] == CL_PARENT)
				{
					parenthesis_count--;
				}
			}
		}
	}
	//parse_position << (re.size() - last_position);

	QList<QString> sub_re_list;
	QString temp_dot_re = re;
	//for (int position : parse_position)
	//{
		sub_re_list << temp_dot_re.left(parse_position);
		temp_dot_re.remove(0, parse_position);
		sub_re_list << temp_dot_re;
	//}

	if(re == sub_re_list[0])
	{
		return QList<QString>();
	}
	for (QString& sub_re : sub_re_list)
	{
		if (sub_re[0] == symbol)
		{
			sub_re.remove(0, 1);
		}
		if (sub_re[sub_re.size() -1] == symbol)
		{
			sub_re.remove(sub_re.size() - 1, 1);
		}
	}

	return sub_re_list;
}
