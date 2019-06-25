#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include "chromosome.h"
#include "population.h"

class termination_condition {
public:
	virtual bool operator()(population* population) abstract;
};

#endif /* _TERMINATION_CONDITION_H_ */ 