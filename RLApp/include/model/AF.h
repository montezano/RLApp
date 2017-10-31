#ifndef __AF_H__
#define __AF_H__

#include "model/MapModel.h"
#include "util/Subject.h"

class AF : public Subject
{
public:
	void setAF(/*QMap< map*/);

	bool verify();

private:
	MapModel map;

};


#endif // !__AF_H__
