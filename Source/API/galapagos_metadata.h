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

typedef std::function<void(log_entry_t)> log_func_t;
typedef std::function<double(creature*)> fitness_func_t;

typedef struct genetic_operator_metadata {
    const double weight;

    explicit genetic_operator_metadata(const double weight) : weight{weight} {};
    virtual  ~genetic_operator_metadata() = default;
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
	const std::string name;
	const double crossover_rate;
    const std::vector<const crossover_metadata_t*>& crossover_metadata;
    const double mutation_rate;
    const std::vector<const mutation_metadata_t*>& mutation_metadata;

    chromosome_metadata(
            std::string name,
            const double crossover_rate, const std::vector<const crossover_metadata_t*>& crossover_metadata,
            const double mutation_rate, const std::vector<const mutation_metadata_t*>& mutation_metadata) :
                name{std::move(name)},
                crossover_rate{crossover_rate}, crossover_metadata{crossover_metadata},
                mutation_rate{mutation_rate}, mutation_metadata{mutation_metadata} {}
    virtual  ~chromosome_metadata() = default;
} chromosome_metadata_t;

typedef struct creature_metadata {
    const fitness_func_t fitness_function;
	const std::vector<const chromosome_metadata_t*>& chromosome_metadata;

    creature_metadata(
            fitness_func_t fitness_function, const std::vector<const chromosome_metadata_t*>& chromosome_metadata) :
                fitness_function{std::move(fitness_function)}, chromosome_metadata{chromosome_metadata} {}
} creature_metadata_t;

typedef struct population_metadata {
    const log_func_t log_function;
	const size_t size;
	const double survival_rate;
	const double distance_threshold;
	const bool cooperative_coevolution;
    const std::vector<const selection_algorithm_metadata_t*>& selection_algorithm_metadata;
    const std::vector<const termination_condition_metadata_t*>& termination_condition_metadata;
    const creature_metadata_t creature_metadata;

    population_metadata(
            log_func_t log_function, const size_t size, const double survival_rate,
            const double distance_threshold, const bool cooperative_coevolution,
            const std::vector<const selection_algorithm_metadata_t*>& selection_algorithm_metadata,
            const std::vector<const termination_condition_metadata_t*>& termination_condition_metadata,
            const creature_metadata_t creature_metadata) :
                log_function{std::move(log_function)}, size{size}, survival_rate{survival_rate},
                distance_threshold{distance_threshold}, cooperative_coevolution{cooperative_coevolution},
                selection_algorithm_metadata{selection_algorithm_metadata},
                termination_condition_metadata{termination_condition_metadata},
                creature_metadata{creature_metadata} {}
} population_metadata_t;

#endif /* _GALAPAGOS_METADATA_H_ */
