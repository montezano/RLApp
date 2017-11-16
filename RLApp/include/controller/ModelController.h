#ifndef __MODELCONTROLLER_H__
#define __MODELCONTROLLER_H__

#include "model/RE.h"
#include "model/AF.h"
#include "model/RG.h"
#include "model/FADataModel.h"
#include "util/Observer.h"

class ModelController : public Observer
{
public:
	ModelController();
	ModelController(Observer* observer, FADataModel* fa_data);
	~ModelController();

	bool updateRE();

	virtual void onNotify(void * entity, Events event);

private:
	RE _re;
	RG _rg;
	FADataModel* _fa;

};


#endif // !__MODELCONTROLLER_H__
