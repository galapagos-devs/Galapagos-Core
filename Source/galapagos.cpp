#include "API/galapagos.h"

#include "galapagos_assemblies.h"
#include "genetic_factory.h"
#include "population_internal.h"
#include "stochastic_internal.h"

/****************************
*****Galapagos Bootstrap*****
****************************/
#include <experimental/filesystem> // TODO: is this still experimental
namespace fs = std::experimental::filesystem; // namespace alias
GALAPAGOS_API void gc_initialize() { // TODO: currently hard coded to work against windows
    // find all dlls in current directory that export the symbol 'gc_bootstrap'
    for (const auto& dir_entry : fs::recursive_directory_iterator(".")) {
        fs::path entry_path = dir_entry.path();
        if(entry_path.extension() == "\\.dll") {
            gc_satellite lib((LPCSTR)entry_path.c_str()); // TODO: this LPCSTR cast seems reckless
            lib.bootstrap();
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

stochastic* gc_stochastic_instance = nullptr;
GALAPAGOS_API stochastic* gc_get_stochastic() {
    if(gc_stochastic_instance == nullptr)
        gc_stochastic_instance = new stochastic_internal();
    return gc_stochastic_instance;
}

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata) {
	stochastic* stochastic_instance = gc_get_stochastic();
	return (population*)new population_internal(population_metadata, (stochastic*)stochastic_instance);
}

GALAPAGOS_API void delete_population(population* population) {
	delete population;
}
