#include "model\RE.h"

RE::RE()
{
}

RE::RE(std::string re)
{
	_re = QString(re.c_str());
}

RE::RE(QString re)
{
	_re = re;
}

RE::~RE()
{
}