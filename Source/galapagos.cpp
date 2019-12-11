#include "API/galapagos.h"

#include <utility>
#include "genetic_factory.h"
#include "population_internal.h"
#include "stochastic_internal.h"

/****************************
*****Galapagos Bootstrap*****
****************************/
GALAPAGOS_API void gc_initialize() {
    // find all dlls in current directory that export the symbol 'gc_bootstrap'
    // call gc_bootstrap on each of the discovered dlls (this should register plugins with the framework)
}

GALAPAGOS_API void gc_register_selection_algorithm(try_create_selection_algorithm_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_selection_algorithm(try_create);
}

GALAPAGOS_API void gc_register_termination_condition(try_create_termination_condition_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_termination_condition(try_create);
}

GALAPAGOS_API void gc_register_chromosome(try_create_chromosome_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_chromosome(try_create);
}

GALAPAGOS_API void gc_register_crossover(try_create_crossover_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_crossover(try_create);
}

GALAPAGOS_API void gc_register_mutation(try_create_mutation_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_mutation(try_create);
}

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata) {
	stochastic_internal* stochastic_instance = new stochastic_internal();
	return (population*)new population_internal(population_metadata, (stochastic*)stochastic_instance);
}

GALAPAGOS_API void delete_population(population* population) {
	delete population;
}

GALAPAGOS_API size_t population_get_size(population* population) {
    return population->get_size();
}

GALAPAGOS_API creature* population_get_creature(population* population, int i) {
    return population->get_creature(i);
}

GALAPAGOS_API creature* population_get_optimal_creature(population* population) {
    return population->get_optimal_creature();
}

GALAPAGOS_API void population_evolve(population* population) {
    population->evolve();
}

/***************************
*****Galapagos Creature*****
***************************/
GALAPAGOS_API double creature_get_fitness(creature* creature) {
    return creature->get_fitness();
}

GALAPAGOS_API chromosome* creature_get_chromosome(creature* creature, std::string name) {
    return creature->get_chromosome<chromosome>(name);
}
