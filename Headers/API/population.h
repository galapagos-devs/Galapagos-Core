#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <cstdint>

#include "../../Headers/API/creature.h"

class population {
public:
	virtual size_t get_size() abstract;

	virtual creature* operator[] (int) abstract;

	virtual creature* get_optimal_creature() abstract;

	virtual void evolve() abstract;
};

#endif /* _POPULATION_H_ */
