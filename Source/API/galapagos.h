#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <functional>
#include <typeindex>
#include <memory>

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
#define GALAPAGOS_API extern "C" __declspec(dllexport)  // TODO: Rename to `GALAPAGOS_BOOTSTRAP`
#else
#define GALAPAGOS_API extern "C" __attribute__((visibility("default")))
#endif

/****************************
*****Galapagos Bootstrap*****
****************************/
typedef std::function<std::shared_ptr<selection_algorithm>(const selection_algorithm_metadata&)> create_selection_algorithm_t;
typedef std::function<std::shared_ptr<termination_condition>(const termination_condition_metadata&)> create_termination_condition_t;
typedef std::function<std::shared_ptr<chromosome>(const chromosome_metadata&)> create_chromosome_t;
typedef std::function<std::shared_ptr<crossover>(const crossover_metadata&)> create_crossover_t;
typedef std::function<std::shared_ptr<mutation>(const mutation_metadata&)> create_mutation_t;

GALAPAGOS_API void gc_initialize();
GALAPAGOS_API void gc_reset();

GALAPAGOS_API void gc_register_selection_algorithm(std::type_index index, const create_selection_algorithm_t& create_selection_algorithm);
GALAPAGOS_API void gc_register_termination_condition(std::type_index index, const create_termination_condition_t& create_termination_condition);
GALAPAGOS_API void gc_register_chromosome(std::type_index index, const create_chromosome_t& create_chromosome);
GALAPAGOS_API void gc_register_crossover(std::type_index index, const create_crossover_t& create_crossover);
GALAPAGOS_API void gc_register_mutation(std::type_index index, const create_mutation_t& create_mutation);

GALAPAGOS_API stochastic* gc_get_stochastic();

/**************************
*****Galapagos Session*****
***************************/
GALAPAGOS_API population* gc_create_population(const population_metadata& metadata);
GALAPAGOS_API void gc_delete_population(population* population);

#endif /* _GALAPAGOS_H_ */
