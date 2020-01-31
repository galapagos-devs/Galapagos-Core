#ifndef _GALAPAGOS_ASSEMBLIES_H_
#define _GALAPAGOS_ASSEMBLIES_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos
 * bootstrapping procedure. 'gc_core' is the bootstrapping interface for the core galapagos library assembly while
 * 'gc_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos on startup.*/

// TODO: currently only windows implementation exist. posix implementations will be needed as well.

#include <string>
#include <windows.h>

#include "API/galapagos.h"

template <typename TSignature>
inline std::function<TSignature> load_assembly_func(HMODULE assembly, const std::string& func_name) {
    FARPROC address = GetProcAddress(assembly, func_name.c_str());
    if (!address)
        return nullptr;

    std::function<TSignature> func(reinterpret_cast<TSignature*>(address));
    return func;
}

class gc_core {
private:
    HMODULE _assembly;
    std::function<void(try_create_selection_algorithm_t)> _register_selection_algorithm;
    std::function<void(try_create_termination_condition_t)> _register_termination_condition;
    std::function<void(try_create_chromosome_t)> _register_chromosome;
    std::function<void(try_create_crossover_t)> _register_crossover;
    std::function<void(try_create_mutation_t)> _register_mutation;
    std::function<stochastic*(void)> _get_stochastic;

    std::function<population*(population_metadata*)> _create_population;
    std::function<void(population*)> _delete_population;

public:
    inline gc_core(LPCSTR assembly_location) {
        _assembly = LoadLibrary(assembly_location);

        _register_selection_algorithm =
                load_assembly_func<void(try_create_selection_algorithm_t)>(
                        _assembly, "gc_register_selection_algorithm");

        _register_termination_condition =
                load_assembly_func<void(try_create_termination_condition_t)>(
                        _assembly, "gc_register_termination_condition");

        _register_chromosome =
                load_assembly_func<void(try_create_chromosome_t)>(
                        _assembly, "gc_register_chromosome");

        _register_crossover =
                load_assembly_func<void(try_create_crossover_t)>(
                        _assembly, "gc_register_crossover");

        _register_mutation =
                load_assembly_func<void(try_create_mutation_t)>(
                        _assembly, "gc_register_mutation");

        _get_stochastic =
                load_assembly_func<stochastic*(void)>(
                        _assembly, "gc_get_stochastic");

        _create_population =
                load_assembly_func<population*(population_metadata*)>(
                        _assembly, "gc_create_population");

        _delete_population =
                load_assembly_func<void(population*)>(
                        _assembly, "gc_delete_population");
    }

    inline ~gc_core() {
        FreeLibrary(_assembly);
    }

    inline void register_selection_algorithm(try_create_selection_algorithm_t try_create) {
        _register_selection_algorithm(try_create);
    }

    inline void register_termination_condition(try_create_termination_condition_t try_create) {
        _register_termination_condition(try_create);
    }

    inline void register_chromosome(try_create_chromosome_t try_create) {
        _register_chromosome(try_create);
    }

    inline void register_crossover(try_create_crossover_t try_create) {
        _register_crossover(try_create);
    }

    inline void register_mutation(try_create_mutation_t try_create) {
        _register_mutation(try_create);
    }

    inline stochastic* get_stochastic() {
        return  _get_stochastic();
    }

    inline population* create_population(population_metadata* metadata) {
        return _create_population(metadata);
    }

    inline void delete_population(population* population) {
        _delete_population(population);
    }
};

class gc_satellite {
private:
    HMODULE _assembly;
    std::function<void(void)> _bootstrap;

public:
    inline gc_satellite(LPCSTR assembly_location) {
        _assembly = LoadLibrary(assembly_location);

        _bootstrap =
                load_assembly_func<void(void)>(
                        _assembly, "gc_bootstrap");
    }

    inline ~gc_satellite() {
        FreeLibrary(_assembly);
    }

    inline void bootstrap() {
        _bootstrap();
    }
};

#endif /* _GALAPAGOS_ASSEMBLIES_H_ */
