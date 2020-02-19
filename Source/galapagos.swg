%module galapagos
%{
#include "API/chromosome.h"
#include "API/creature.h"
#include "API/crossover.h"
#include "API/galapagos.h"
#include "API/galapagos_metadata.h"
#include "API/genetic_operator.h"
#include "API/mutation.h"
#include "API/population.h"
#include "API/selection_algorithm.h"
#include "API/stochastic.h"
#include "API/termination_condition.h"
%}

extern "C" population* gc_create_population(population_metadata* population_metadata);
extern "C" void gc_delete_population(population* population);

%include "API/galapagos_metadata.h"
%include "API/population.h"
%include "API/creature.h"
%include "API/chromosome.h"
