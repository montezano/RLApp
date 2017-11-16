#ifndef __MODELCONTROLLER_H__
#define __MODELCONTROLLER_H__

#include "model/RE.h"
#include "model/AF.h"
#include "model/RG.h"
#include "model/Conversions.h"
#include "model/FADataModel.h"
#include "util/Observer.h"

class ModelController : public Observer, public Subject
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
	FADataModel* _fa_temp;

};


#endif // !__MODELCONTROLLER_H__
