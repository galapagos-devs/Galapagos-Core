#ifndef _GALAPAGOS_METADATA_H_
#define _GALAPAGOS_METADATA_H_

#include <string>
#include <cstdint>
#include <functional>
#include <utility>

#include "creature.h"

typedef struct log_entry {
    size_t generation;
    double optimal_fitness;
} log_entry_t;

typedef void (*log_func_t)(log_entry);
typedef double (*fitness_func_t)(creature*);

typedef struct genetic_operator_metadata {
    virtual  ~genetic_operator_metadata() = default;
    const double weight;

    explicit genetic_operator_metadata(const double weight) : weight{weight} {};
} genetic_operator_metadata_t;

typedef struct crossover_metadata : genetic_operator_metadata {
    explicit crossover_metadata(const double weight) : genetic_operator_metadata{weight} {};
} crossover_metadata_t;

typedef struct mutation_metadata : genetic_operator_metadata {
    explicit mutation_metadata(const double weight) : genetic_operator_metadata{weight} {};
} mutation_metadata_t;


typedef struct selection_algorithm_metadata {
    virtual ~selection_algorithm_metadata() = default;
} selection_algorithm_metadata_t;

typedef struct termination_condition_metadata {
    virtual ~termination_condition_metadata() = default;
} termination_condition_metadata_t;

typedef struct chromosome_metadata {
    virtual  ~chromosome_metadata() = default;
	std::string name;
	double crossover_rate;
	double mutation_rate;
	size_t num_crossovers;
	crossover_metadata_t** crossover_metadata;
	size_t num_mutations;
	mutation_metadata_t** mutation_metadata;
} chromosome_metadata_t;

typedef struct creature_metadata {
    fitness_func_t fitness_function;
	size_t num_chromosomes;
	chromosome_metadata_t** chromosome_metadata;
} creature_metadata_t;

typedef struct population_metadata {
    const log_func_t log_function;
	const size_t size;
	const double survival_rate;
	const double distance_threshold;
	const bool cooperative_coevolution;
	const size_t num_selection_algorithms;
	const selection_algorithm_metadata_t** selection_algorithm_metadata;
	const size_t num_termination_conditions;
	const termination_condition_metadata_t** termination_condition_metadata;
    const creature_metadata_t* creature_metadata;

    population_metadata(
            log_func_t  log_function, const size_t size, const double survival_rate,
            const double distance_threshold, const bool cooperative_coevolution,
            const size_t num_selection_algorithms, const selection_algorithm_metadata_t** selection_algorithm_metadata,
            const size_t num_termination_conditions, const termination_condition_metadata_t** termination_condition_metadata,
            const creature_metadata_t* creature_metadata) :
                    log_function{std::move(log_function)}, size{size}, survival_rate{survival_rate},
                    distance_threshold{distance_threshold}, cooperative_coevolution{cooperative_coevolution},
                    num_selection_algorithms{num_selection_algorithms}, selection_algorithm_metadata{selection_algorithm_metadata},
                    num_termination_conditions{num_termination_conditions}, termination_condition_metadata{termination_condition_metadata},
                    creature_metadata{creature_metadata} {}
} population_metadata_t;

#endif /* _GALAPAGOS_METADATA_H_ */
