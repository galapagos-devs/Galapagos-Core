#ifndef _POPULATION_CPP_
#define _POPULATION_CPP_

#include "population.h"
#include "population_metadata.h"
#include "creature.h"

class population_internal : population {
private:
	population_metadata* _population_metadata;

public:
	population_internal(population_metadata* population_metadata) {
		_population_metadata = population_metadata;
	}

	uint32_t get_size() override {
		return _population_metadata->size;
	}

	creature* operator[] (int) override {
		return nullptr;
	}

	creature* get_optimal_creature() override {
		return nullptr;
	}

	void evolve() override {

	}
};

#endif /* _POPULATION_CPP_ */