#ifndef __RE_H__
#define __RE_H__

#include <string>
#include <QString>

#include "util/Alphabet.h"
#include "util/Subject.h"

class RE: public Subject
{
public:
	//RE();
	//RE(std::string re);
	//RE(QString re);
	//~RE();

	//void setRe(std::string re);
	void setRe(QString re);
	QString getRe();



private:
	bool verify(QString &re);


	QString _re;

};


#endif // !__RE_H__
