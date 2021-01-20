#ifndef _GALAPAGOS_METADATA_H_
#define _GALAPAGOS_METADATA_H_

#include <utility>
#include <vector>
#include <string>
#include <cstdint>
#include <functional>
#include <utility>
#include <memory>

#include "creature.h"

typedef struct log_entry {  // TODO: This needs more entries in it. This is too limited
    size_t generation;
    double optimal_fitness;
} log_entry_t;

typedef std::function<void(log_entry_t)> log_func_t;
typedef std::function<double(creature*)> fitness_func_t;

// Object hierarchy


struct galapagos_metadata {virtual ~galapagos_metadata() = default;};

typedef struct genetic_operator_metadata : galapagos_metadata {
    const double weight;

    explicit genetic_operator_metadata(double weight) : weight{weight} {};
} genetic_operator_metadata_t;

// TODO: Remove `typedef` from `struct`s.
/* TODO: Rename `struct`s to CamelCased-metadatum naming convention e.g.:
 *       using CrossoverMetadatum_ptr = std::shared_ptr<const CrossoverMetadatum>
 *       using CrossoverMetadata = std::vector<CrossoverMetadatum_ptr>;
 */

typedef struct crossover_metadata : genetic_operator_metadata {
    explicit crossover_metadata(double weight) : genetic_operator_metadata{weight} {};
} crossover_metadata_t;
using crossover_metadata_ptr = std::shared_ptr<const crossover_metadata>;

typedef struct mutation_metadata : genetic_operator_metadata {
    explicit mutation_metadata(double weight) : genetic_operator_metadata{weight} {};
} mutation_metadata_t;
using mutation_metadata_ptr = std::shared_ptr<const mutation_metadata>;

typedef struct selection_algorithm_metadata : galapagos_metadata {} selection_algorithm_metadata_t;
using selection_algorithm_metadata_ptr = std::shared_ptr<const selection_algorithm_metadata>;

typedef struct termination_condition_metadata : galapagos_metadata {} termination_condition_metadata_t;
using termination_condition_metadata_ptr = std::shared_ptr<const termination_condition_metadata>;

typedef struct chromosome_metadata : galapagos_metadata {
    const std::string name;
    const double crossover_rate;
    const std::vector<crossover_metadata_ptr> crossover_metadata;
    const double mutation_rate;
    const std::vector<mutation_metadata_ptr> mutation_metadata;

    chromosome_metadata(
            std::string name,
            double crossover_rate, std::vector<crossover_metadata_ptr> crossover_metadata,
            double mutation_rate, std::vector<mutation_metadata_ptr> mutation_metadata) :
                name{std::move(name)},
                crossover_rate{crossover_rate}, crossover_metadata{std::move(crossover_metadata)},
                mutation_rate{mutation_rate}, mutation_metadata{std::move(mutation_metadata)} {}
} chromosome_metadata_t;
using chromosome_metadata_ptr = std::shared_ptr<const chromosome_metadata>;

typedef struct creature_metadata : galapagos_metadata{
    const fitness_func_t fitness_function;
    const std::vector<chromosome_metadata_ptr> chromosome_metadata;

    creature_metadata(
            fitness_func_t fitness_function, std::vector<chromosome_metadata_ptr> chromosome_metadata) :
                fitness_function{std::move(fitness_function)}, chromosome_metadata{std::move(chromosome_metadata)} {}
} creature_metadata_t;
using creature_metadata_ptr = std::shared_ptr<const creature_metadata>;

typedef struct population_metadata : galapagos_metadata {
    const log_func_t log_function;
    const size_t size;
    const double survival_rate;
    const double distance_threshold;
    const bool cooperative_coevolution;
    const std::vector<selection_algorithm_metadata_ptr> selection_algorithm_metadata;
    const std::vector<termination_condition_metadata_ptr> termination_condition_metadata;
    const creature_metadata_ptr creature_metadata;

    population_metadata(
            log_func_t log_function, size_t size, double survival_rate,
            double distance_threshold, bool cooperative_coevolution,
            std::vector<selection_algorithm_metadata_ptr>  selection_algorithm_metadata,
            std::vector<termination_condition_metadata_ptr>  termination_condition_metadata,
            creature_metadata_ptr creature_metadata) :
                log_function{std::move(log_function)}, size{size}, survival_rate{survival_rate},
                distance_threshold{distance_threshold}, cooperative_coevolution{cooperative_coevolution},
                selection_algorithm_metadata{std::move(selection_algorithm_metadata)},
                termination_condition_metadata{std::move(termination_condition_metadata)},
                creature_metadata{std::move(creature_metadata)} {}
} population_metadata_t;
using population_metadata_ptr = std::shared_ptr<population_metadata>;

// Constructor Macros

#define POPULATION_METADATA(metadata) population_metadata_ptr(new metadata)
#define SELECTION_ALGORITHM_METADATA(metadata) selection_algorithm_metadata_ptr(new metadata)
#define TERMINATION_CONDITION_METADATA(metadata) termination_condition_metadata_ptr(new metadata)
#define CREATURE_METADATA(metadata) creature_metadata_ptr(new metadata)
#define CHROMOSOME_METADATA(metadata) chromosome_metadata_ptr(new metadata)
#define CROSSOVER_METADATA(metadata) crossover_metadata_ptr(new metadata)
#define MUTATION_METADATA(metadata) mutation_metadata_ptr(new metadata)


#endif /* _GALAPAGOS_METADATA_H_ */
