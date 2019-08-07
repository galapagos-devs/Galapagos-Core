#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include "../../Headers/API/chromosome.h"
#include "../../Headers/API/population.h"

class termination_condition {
public:
	virtual bool operator()(population* population) abstract;
	virtual bool invoke(population* population) abstract;
};

#endif /* _TERMINATION_CONDITION_H_ */ 