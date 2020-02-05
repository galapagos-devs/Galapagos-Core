#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <functional>

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
#define GALAPAGOS_API extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_API extern "C" __attribute__((visibility("default")))
#endif

/****************************
*****Galapagos Bootstrap*****
****************************/
typedef std::function<bool(selection_algorithm_metadata* metadata, selection_algorithm*& selection_algorithm)> try_create_selection_algorithm_t;
typedef std::function<bool(termination_condition_metadata* metadata, termination_condition*& termination_condition)> try_create_termination_condition_t;
typedef std::function<bool(chromosome_metadata* metadata, chromosome*& chromosome)> try_create_chromosome_t;
typedef std::function<bool(crossover_metadata* metadata, crossover*& crossover)> try_create_crossover_t;
typedef std::function<bool(mutation_metadata* metadata, mutation*& mutation)> try_create_mutation_t;

GALAPAGOS_API void gc_register_selection_algorithm(try_create_selection_algorithm_t try_create);
GALAPAGOS_API void gc_register_termination_condition(try_create_termination_condition_t try_create);
GALAPAGOS_API void gc_register_chromosome(try_create_chromosome_t try_create);
GALAPAGOS_API void gc_register_crossover(try_create_crossover_t try_create);
GALAPAGOS_API void gc_register_mutation(try_create_mutation_t try_create);

GALAPAGOS_API stochastic* gc_get_stochastic();

/**************************
*****Galapagos Session*****
***************************/
GALAPAGOS_API population* gc_create_population(population_metadata* population_metadata);
GALAPAGOS_API void gc_delete_population(population* population);

#endif /* _GALAPAGOS_H_ */
