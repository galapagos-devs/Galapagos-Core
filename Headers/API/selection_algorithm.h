#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include "../../Headers/API/creature.h"
#include "../../Headers/API/population.h"

class selection_algorithm {
public:
	virtual creature* invoke(population* population) abstract;
};

#endif /* _SELECTION_ALGORITHM_H_ */  