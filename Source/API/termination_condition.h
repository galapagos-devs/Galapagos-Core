#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include "../../Source/API/chromosome.h"
#include "../../Source/API/population.h"

class termination_condition {
public:
	virtual bool operator()(population* population) abstract;
	virtual bool invoke(population* population) abstract;
};

#endif /* _TERMINATION_CONDITION_H_ */ 