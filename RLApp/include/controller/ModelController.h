#ifndef __MODELCONTROLLER_H__
#define __MODELCONTROLLER_H__

#include "model/RE.h"

class ModelController
{
public:
	ModelController();
	~ModelController();

	bool updateRE();

private:
	RE _re;
	//GR _gr;
	//FA _fa;

};


#endif // !__MODELCONTROLLER_H__
