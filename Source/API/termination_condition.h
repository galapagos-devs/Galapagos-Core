#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include "chromosome.h"
#include "population.h"

class termination_condition {
public:
	virtual ~termination_condition() = 0;

	virtual bool operator()(population* population) = 0;
	virtual bool invoke(population* population) = 0;
};

//inline termination_condition::~termination_condition { }

#endif /* _TERMINATION_CONDITION_H_ */