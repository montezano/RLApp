#ifndef __MODELCONTROLLER_H__
#define __MODELCONTROLLER_H__

#include "model/RE.h"
#include "model/AF.h"
#include "util/Observer.h"

class ModelController
{
public:
	ModelController();
	ModelController(Observer* observer);
	~ModelController();

	bool updateRE();

private:
	RE _re;
	//GR _gr;
	AF _fa;

};


#endif // !__MODELCONTROLLER_H__
