#include "model\RE.h"

RE::RE()
{
}


RE::RE(QString re)
{
	_re_str = re;
	removeSpaces();
}

RE::~RE()
{
}

bool RE::setReString(QString re)
{
	_re_str = re;
	if (removeSpaces())
	{
		return true;
	}

	return false;
}

QString RE::getReString()
{
	return _re_str;
}

bool RE::removeSpaces()
{
	if (_re_str.remove(" ") != "")
	{
		return true;
	}
	return false;
}

bool RE::addDot()
{
	QString new_re;
	for (int i = 0; i < _re_str.size()-1; i++)
	{
		//if(_re_str[i])
	}
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
