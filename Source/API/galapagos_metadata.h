#ifndef _GALAPAGOS_METADATA_H_
#define _GALAPAGOS_METADATA_H_

#include <string>
#include <cstdint>
#include <functional>

#include "creature.h"

extern "C" struct log_entry {
    size_t generation;
    double optimal_fitness;
};

typedef void (*log_func_t)(log_entry);
typedef double (*fitness_func_t)(creature*);

extern "C" struct genetic_operator_metadata {
    virtual  ~genetic_operator_metadata() = default;
    double weight;
};

extern "C" struct crossover_metadata : genetic_operator_metadata { virtual ~crossover_metadata() = default; };
extern "C" struct mutation_metadata : genetic_operator_metadata { virtual ~mutation_metadata() = default; };
extern "C" struct selection_algorithm_metadata { virtual ~selection_algorithm_metadata() = default; };
extern "C" struct termination_condition_metadata { virtual ~termination_condition_metadata() = default; };

extern "C" struct chromosome_metadata {
    virtual  ~chromosome_metadata() = default;
	std::string name;
	double crossover_rate;
	double mutation_rate;
	size_t num_crossovers;
	crossover_metadata** crossover_metadata;
	size_t num_mutations;
	mutation_metadata** mutation_metadata;
};

extern "C" struct creature_metadata {
    fitness_func_t fitness_function;
	size_t num_chromosomes;
	chromosome_metadata** chromosome_metadata;
};

extern "C" struct population_metadata {
    log_func_t log_function;
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
