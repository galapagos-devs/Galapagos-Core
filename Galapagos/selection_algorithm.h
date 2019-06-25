#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include "chromosome.h"
#include "population.h"

class selection_algorithm {
public:
	virtual chromosome* operator()(population* population) = 0;
};

#endif /* _SELECTION_ALGORITHM_H_ */ 