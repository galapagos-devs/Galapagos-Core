%module galapagos
%{
#include "chromosome.h"
#include "creature.h"
#include "crossover.h"
#include "galapagos.h"
#include "galapagos_metadata.h"
#include "genetic_operator.h"
#include "mutation.h"
#include "population.h"
#include "selection_algorithm.h"
#include "stochastic.h"
#include "termination_condition.h"
%}

extern "C" population* gc_create_population(population_metadata* population_metadata);
extern "C" void gc_delete_population(population* population);
extern "C" struct population_metadata {
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
