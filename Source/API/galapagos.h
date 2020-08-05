#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <functional>
#include <typeindex>

#include "stochastic.h"
#include "galapagos_metadata.h"
#include "selection_algorithm.h"
#include "termination_condition.h"
#include "population.h"
#include "creature.h"
#include "chromosome.h"
#include "crossover.h"
#include "mutation.h"

#ifdef WIN32
#define GALAPAGOS_BOOTSTRAP extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_BOOTSTRAP extern "C" __attribute__((visibility("default")))
#endif

typedef std::function<selection_algorithm*(const selection_algorithm_metadata&)> create_selection_algorithm_t;
typedef std::function<void(selection_algorithm*)> delete_selection_algorithm_t;

typedef std::function<termination_condition*(const termination_condition_metadata&)> create_termination_condition_t;
typedef std::function<void(termination_condition*)> delete_termination_condition_t;

typedef std::function<chromosome*(const chromosome_metadata&)> create_chromosome_t;
typedef std::function<void(chromosome*)> delete_chromosome_t;

typedef std::function<crossover*(const crossover_metadata&)> create_crossover_t;
typedef std::function<void(crossover*)> delete_crossover_t;

typedef std::function<mutation*(const mutation_metadata&)> create_mutation_t;
typedef std::function<void(mutation*)> delete_mutation_t;

GALAPAGOS_BOOTSTRAP void gc_register_selection_algorithm(std::type_index index,
        const create_selection_algorithm_t& create_selection_algorithm,
        const delete_selection_algorithm_t& delete_selection_algorithm);

GALAPAGOS_BOOTSTRAP void gc_register_termination_condition(std::type_index index,
        const create_termination_condition_t& create_termination_condition,
        const delete_termination_condition_t& delete_termination_condition);

GALAPAGOS_BOOTSTRAP void gc_register_chromosome(std::type_index index,
        const create_chromosome_t& create_chromosome,
        const delete_chromosome_t& delete_chromosome);

GALAPAGOS_BOOTSTRAP void gc_register_crossover(std::type_index index,
        const create_crossover_t& create_crossover,
        const delete_crossover_t& delete_crossover);

GALAPAGOS_BOOTSTRAP void gc_register_mutation(std::type_index index,
        const create_mutation_t& create_mutation,
        const delete_mutation_t& delete_mutation);

GALAPAGOS_BOOTSTRAP population* gc_create_population(const population_metadata& population_metadata);
GALAPAGOS_BOOTSTRAP void gc_delete_population(population* population);

#endif /* _GALAPAGOS_H_ */
