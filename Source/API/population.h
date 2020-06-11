#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <cstdint>

#include "creature.h"

class population {
public:
	virtual ~population() = default;

	virtual size_t get_size() = 0;

	virtual creature* operator[] (int) = 0;

	virtual creature* get_creature(int i) = 0;  // get the ith creature.

	virtual creature* get_optimal_creature() = 0;

	virtual void evolve() = 0;
};

#endif /* _POPULATION_H_ */
