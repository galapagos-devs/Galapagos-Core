#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "creature.h"
#include <cstdint>

class population {
public:
	virtual uint32_t get_size() = 0;

	virtual creature* operator[] (int) = 0;

	virtual creature* get_optimal_creature() = 0;

	virtual void evolve() = 0;
};

#endif /* _POPULATION_H_ */
