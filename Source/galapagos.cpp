#include "API/galapagos.h"

#include "genetic_factory.h"
#include "population_internal.h"
#include "stochastic_internal.h"

/****************************
*****Galapagos Bootstrap*****
****************************/
GALAPAGOS_API void gc_register_selection_algorithm(try_create_selection_algorithm_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_selection_algorithm(std::move(try_create));
}

GALAPAGOS_API void gc_register_termination_condition(try_create_termination_condition_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_termination_condition(std::move(try_create));
}

GALAPAGOS_API void gc_register_chromosome(try_create_chromosome_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_chromosome(std::move(try_create));
}

GALAPAGOS_API void gc_register_crossover(try_create_crossover_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_crossover(std::move(try_create));
}

GALAPAGOS_API void gc_register_mutation(try_create_mutation_t try_create) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_mutation(std::move(try_create));
}

stochastic* gc_stochastic_instance = nullptr;
GALAPAGOS_API stochastic* gc_get_stochastic() {
    if(gc_stochastic_instance == nullptr)
        gc_stochastic_instance = new stochastic_internal();
    return gc_stochastic_instance;
}

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* gc_create_population(population_metadata* population_metadata) {
	stochastic* stochastic_instance = gc_get_stochastic();
	return (population*)new population_internal(population_metadata, (stochastic*)stochastic_instance);
}

GALAPAGOS_API void gc_delete_population(population* population) {
	delete population;
}
