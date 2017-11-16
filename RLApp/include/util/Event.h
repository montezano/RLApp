#ifndef __EVENT_H__
#define __EVENT_H__

enum Events
{
	RE_ADD,
	RE_TO_FA,
	RE_UNION,
	RE_INTERSECTION,
	RE_COMPLEMENT,
	RE_EQUIVALENCE,
	RE_EQUIVALENCE_RESULT,
	RG_TO_FA,
	RG_UNION,
	RG_INTERSECTION,
	RG_COMPLEMENT,
	RG_EQUIVALENCE,
	FA_UNION,
	FA_INTERSECTION,
	FA_COMPLEMENT,
	FA_EQUIVALENCE,
	FA_DETERMINIZATION,
	FA_MINIMIZATION,
	FA_ADD_TERMINAL,
	FA_UPDATE_OPERATION
};

#endif // !__EVENT_H__