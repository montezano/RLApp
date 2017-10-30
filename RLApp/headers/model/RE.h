#ifndef __RE_H__
#define __RE_H__

#include <string>
#include <QString>

#include "util\Alphabet.h"

class RE
{
public:
	RE();
	RE(std::string re);
	RE(QString re);
	~RE();

private:
	QString _re;

};


#endif // !__RE_H__
