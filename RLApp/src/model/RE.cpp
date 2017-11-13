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
	if (!addDot())
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
	return _dot_re;
}

QList<QString> RE::parseSymbol(QChar symbol)
{
	QVector<int> parse_position;
	int last_position = 0;
	int parenthesis_count = 0;
	for (int i = 0; i < _dot_re.size(); i++)
	{
		if (_dot_re[i] == symbol && parenthesis_count == 0)
		{
			parse_position << (i - last_position);
			last_position = i;

		}
		else
		{
			if (_dot_re[i] == OP_PARENT)
			{
				parenthesis_count++;
			}
			else
			{
				if (_dot_re[i] == CL_PARENT)
				{
					parenthesis_count--;
				}
			}
		}
	}
	parse_position << (_dot_re.size() - last_position);

	QList<QString> sub_re_list;
	QString temp_dot_re = _dot_re;
	for (int position : parse_position)
	{
		sub_re_list << temp_dot_re.left(position);
		temp_dot_re.remove(0, position);
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

QList<QString> RE::parseConjunctionStep()
{

	QVector<int> parse_position;
	int last_position = 0;
	int parenthesis_count = 0;
	for (int i = 0; i < _dot_re.size(); i++)
	{
		if (_dot_re[i] == CONJUNCT && parenthesis_count == 0)
		{
			parse_position << (i - last_position);
			last_position = i;

		}
		else
		{
			if (_dot_re[i] == OP_PARENT)
			{
				parenthesis_count++;
			}
			else
			{
				if (_dot_re[i] == CL_PARENT)
				{
					parenthesis_count--;
				}
			}
		}
	}
	parse_position << (_dot_re.size() - last_position);

	QList<QString> sub_re_list;
	QString temp_dot_re = _dot_re;
	for (int position : parse_position)
	{
		sub_re_list << temp_dot_re.left(position);
		temp_dot_re.remove(0, position);
	}

	for (QString& sub_re : sub_re_list)
	{
		if (sub_re[0] == CONJUNCT)
		{
			sub_re.remove(0, 1);
		}
		if (sub_re[sub_re.size() - 1] == CONJUNCT)
		{
			sub_re.remove(sub_re.size() - 1, 1);
		}
	}

	return sub_re_list;
}

bool RE::removeSpaces()
{
	if (_original_re.remove(" ") != "")
	{
		return true;
	}
	return false;
}

bool RE::addDot()
{
	for (int i = 0; i < _original_re.size() - 1; i++)
	{
		_dot_re += _original_re[i];

		if (_valid_terminals.contains(_original_re[i]))
		{
			if ((_valid_terminals + _open_operators).contains(_original_re[i + 1]))
			{
				_dot_re += '.';
			}
		}
		else
		{
			if (_end_operators.contains(_original_re[i]))
			{
				if ((_valid_terminals + _open_operators).contains(_original_re[i + 1]))
				{
					_dot_re += '.';
				}
			}
		}
	}
	_dot_re += _original_re[_original_re.size() - 1];

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
