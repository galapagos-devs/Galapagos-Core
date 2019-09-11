#ifndef _GALAPAGOS_METADATA_H_
#define _GALAPAGOS_METADATA_H_

#include <string>
#include <cstdint>
#include <functional>

#include "creature.h"

typedef std::function<double(creature* creature)> fitness_func_t;

// crossovers
struct crossover_metadata { };

// mutations
struct mutation_metadata { };

// chromosomes
struct chromosome_metadata {
	std::string name;
	double crossover_rate;
	double mutation_rate;
	size_t num_crossovers;
	crossover_metadata* crossovers;
	size_t num_mutations;
	mutation_metadata mutations;
};

struct bin_chromosome_metadata : chromosome_metadata {
	size_t gene_count;  // TODO: does this go in base class. probably not... makes no sense for neural chromosome
};

// selection algorithms
struct selection_algorithm_metadata { };

struct tournament_selection_metadata : selection_algorithm_metadata {
	size_t tournament_size;
};

// termination conditions
struct termination_condition_metadata { };

// population
struct population_metadata {
	size_t size;
	double survival_rate;
	double distance_threshold;
	bool cooperative_coevolution;
	size_t num_selection_algorithm_metadata;
	selection_algorithm_metadata* selection_algorithm_metadata;
	size_t num_termination_condition_metadata;
	termination_condition_metadata* termination_condition_metadata;
	fitness_func_t fitness_function;
	size_t num_chromosome_metadata;
	chromosome_metadata* chromosome_metadata;
};

#endif /* _GALAPAGOS_METADATA_H_ */
