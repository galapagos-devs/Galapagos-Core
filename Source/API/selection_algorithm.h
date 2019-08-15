#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include "../../Source/API/creature.h"
#include "../../Source/API/population.h"

class selection_algorithm {
public:
	virtual creature* invoke(population* population) = 0;
};

#endif /* _SELECTION_ALGORITHM_H_ */
