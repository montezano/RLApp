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

	//if (_dot_re[_dot_re.size() - 1] == '.')
	//{
	//	_dot_re.remove(_dot_re.size() - 1, 1);
	//}
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
