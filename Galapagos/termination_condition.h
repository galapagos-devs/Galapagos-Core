#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include "chromosome.h"
#include "population.h"

class termination_condition {
public:
	virtual bool operator()(population* population) = 0;
};

#endif /* _TERMINATION_CONDITION_H_ */ 