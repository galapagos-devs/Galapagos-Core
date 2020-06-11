#include <filesystem>

#include "API/galapagos.h"

#include "galapagos_assemblies.h"
#include "genetic_factory.h"
#include "population_internal.h"
#include "stochastic_internal.h"

namespace fs = std::filesystem; // namespace alias

/****************************
*****Galapagos Bootstrap*****
****************************/
bool gc_initialized = false;
std::vector<gc_satellite*> gc_satellites;
GALAPAGOS_API void gc_initialize() {
    if(!gc_initialized) {
        auto* core = new gc_core();

        // find all dlls in current directory that export the symbol 'gc_bootstrap'
        for (const auto &dir_entry : fs::recursive_directory_iterator(".")) {
            const fs::path& entry_path = dir_entry.path();
            if (entry_path.extension() == ".dll" &&  // FIXME: This will not work on linux
                entry_path.filename() != "Galapagos.dll") {
                const std::string filename = entry_path.filename().string();
                auto* satellite = new gc_satellite(filename);
                satellite->bootstrap(core);
                gc_satellites.push_back(satellite);
            }
        }

        // its safe to delete gc_core here because we are using it in a way that does not
        // dynamically load the core assembly. we are in the core assembly already! there
        // it will not try to free the core assembly in its destructor
        delete core;  // FIXME: This is sketchy
        gc_initialized = true;
    }
}

GALAPAGOS_API void gc_reset() {
    if(gc_initialized) {
        genetic_factory &factory = genetic_factory::get_instance();
        factory.reset();

        for (auto & satellite : gc_satellites)
            delete satellite;
        gc_satellites.clear();

        gc_initialized = false;
    }
}

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

GALAPAGOS_API stochastic* gc_get_stochastic() {
    stochastic_internal& stochastic = stochastic_internal::get_instance();
    return &stochastic;
}

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* gc_create_population(const population_metadata* population_metadata) {
	stochastic* stochastic_instance = gc_get_stochastic();
	return (population*)new population_internal(population_metadata, (stochastic*)stochastic_instance);
}

GALAPAGOS_API void gc_delete_population(population* population) {
	delete population;
}
