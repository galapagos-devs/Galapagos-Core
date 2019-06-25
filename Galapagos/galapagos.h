#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include "population.h"
#include "population_metadata.h"
#include "creature.h"
#include <cstdint>
#include <functional>

#define GALAPAGOS_API extern "C" __declspec(dllexport)

namespace BINARY_CROSSOVER {
	enum BINARY_CROSSOVER : uint16_t {
		SINGLE_POINT = 1 << 0,
		TWO_POINT = 1 << 1,
		UNIFORM = 1 << 2,
		NOOP = 1 << 3,
		ALL = SINGLE_POINT | TWO_POINT | UNIFORM | NOOP
	};
}

namespace BINARY_MUTATION {
	enum BINARY_MUTATION : uint16_t {
		CYCLIC_SHIFT = 1 << 0,
		RANDOMIZATION = 1 << 1,
		REVERSE = 1 << 2,
		FLIP_BIT = 1 << 3,
		SINGLE_BIT = 1 << 4,
		SCRAMBLE = 1 << 5,
		ALL = CYCLIC_SHIFT | RANDOMIZATION | REVERSE |
			FLIP_BIT | SINGLE_BIT | SCRAMBLE
	};
}

namespace SELECTION_ALGORITHM {
	enum SELECTION_ALGORITHM {
		FITNESS_PROPORTIONATE,
		STOCHASTIC_UNIVERSAL_SAMPLING,
		TOURNAMENT,
		TRUNCATION
	};
}

namespace TERMINATION_CONDITION {
	enum TERMINATION_CONDITION {
		FITNESS_PLATEAU,
		FITNESS_THRESHOLD,
		GENERATION_THRESHOLD,
		TIMER
	};
}

typedef BINARY_CROSSOVER::BINARY_CROSSOVER bin_crossover_t;
typedef BINARY_MUTATION::BINARY_MUTATION bin_mutation_t;
typedef SELECTION_ALGORITHM::SELECTION_ALGORITHM selection_algo_t;
typedef TERMINATION_CONDITION::TERMINATION_CONDITION term_cond_t;
typedef std::function<double(creature* creature)> fitness_func_t;

GALAPAGOS_API population* create_population(population_metadata* metadata);

#endif /* _GALAPAGOS_H_ */
