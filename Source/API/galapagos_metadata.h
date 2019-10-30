#ifndef _GALAPAGOS_METADATA_H_
#define _GALAPAGOS_METADATA_H_

#include <string>
#include <cstdint>
#include <functional>

#include "creature.h"

typedef std::function<double(creature* creature)> fitness_func_t;

struct crossover_metadata { };
struct mutation_metadata { };
struct selection_algorithm_metadata { };
struct termination_condition_metadata { };

struct chromosome_metadata {
	std::string name;
	double crossover_rate;
	double mutation_rate;
	size_t num_crossovers;
	crossover_metadata** crossover_metadata;
	size_t num_mutations;
	mutation_metadata** mutation_metadata;
};

struct creature_metadata {
    fitness_func_t fitness_function;
	size_t num_chromosomes;
	chromosome_metadata** chromosome_metadata;
};

struct population_metadata {
	size_t size;
	double survival_rate;
	double distance_threshold;
	bool cooperative_coevolution;
	size_t num_selection_algorithms;
	selection_algorithm_metadata** selection_algorithm_metadata;
	size_t num_termination_conditions;
	termination_condition_metadata** termination_condition_metadata;
    creature_metadata* creature_metadata;
};

#endif /* _GALAPAGOS_METADATA_H_ */
