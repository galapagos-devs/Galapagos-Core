#ifndef _POPULATION_METADATA_H_
#define _POPULATION_METADATA_H_

#include "galapagos_types.h"
#include "creature.h"
#include "chromosome_metadata.h"
#include <cstdint>

class population_metadata {
public:
	uint32_t size;
	double survival_rate;
	double distance_threshold;
	bool cooperative_coevolution;
	selection_algo_t selection_algorithm;
	term_cond_t termination_condition;
	fitness_func_t fitness_function;

	//virtual chromosome_metadata* operator[] (int) = 0;
};

#endif /* _POPULATION_METADATA_H_ */
