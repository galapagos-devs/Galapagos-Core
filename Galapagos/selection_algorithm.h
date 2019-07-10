#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include "creature.h"
#include "population.h"

class selection_algorithm {
public:
	virtual creature* operator()(population* population) abstract;
	virtual creature* invoke(population* population) abstract;
};

#endif /* _SELECTION_ALGORITHM_H_ */  