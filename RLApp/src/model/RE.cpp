#include "model\RE.h"

//RE::RE()
//{
//}
//
//RE::RE(std::string re)
//{
//	_re = QString(re.c_str());
//}

//RE::RE(QString re)
//{
//	_re = re;
//}

//RE::~RE()
//{
//}

//void RE::setRe(std::string re)
//{
//	_re = QString(re.c_str());
//}

void RE::setRe(QString re)
{
	_re = re;
}

QString RE::getRe()
{
	return _re;
}

bool RE::verify(QString& re)
{
	for (auto terminal = re.begin; terminal != re.end; terminal++)
	{
		//if ()
	}
	//Alphabet::_terminals.
	return false;
}
