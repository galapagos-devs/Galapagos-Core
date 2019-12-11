#include "API/galapagos.h"

#include "genetic_factory.h"
#include "population_internal.h"
#include "stochastic_internal.h"

/****************************
*****Galapagos Bootstrap*****
****************************/
#include <experimental/filesystem> // TODO: is this still experimental
#include <windows.h>
GALAPAGOS_API void gc_initialize() { // TODO: currently hard coded to work against windows
    // find all dlls in current directory that export the symbol 'gc_bootstrap'
    for (const auto& dir_entry : std::experimental::filesystem::recursive_directory_iterator(".")) {
        std::experimental::filesystem::path entry_path = dir_entry.path();
        if(entry_path.extension() == "\\.dll") {
            // found a dll, check if it exports gc_bootstrap
            HMODULE lib = LoadLibrary((LPCSTR)entry_path.c_str()); // TODO: this LPCSTR cast seems reckless
            if(lib) { // on load failures we will ignore the entry.
                auto gc_bootstrap = GetProcAddress(lib, "gc_bootstrap");
                if (gc_bootstrap) {
                    // found a galapagos extension, call gc_bootstrap to register plugins
                    gc_bootstrap();
                    // we now have a mem leak because we are not going to unload this lib. we should hold onto the lib
                    // pointers and delete them at the end of a galapagos session. perhaps an dedicated object is needed to
                    // mange this.
                } else {
                    FreeLibrary(lib); // library is not galapagos extension. unload the library.
                }
            }
        }
    }
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
