#ifndef _GALAPAGOS_ASSEMBLIES_H_
#define _GALAPAGOS_ASSEMBLIES_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos
 * bootstrapping procedure. 'gc_core' is the bootstrapping interface for the core galapagos library assembly while
 * 'gc_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos on startup.*/

#include <string>
#include <Windows.h> // TODO: currently only windows implementation exist. posix implementations will be needed as well.
#include <utility>

#include "API/galapagos.h"

// TODO: this is a windows method for loading assembly functions. need a posix implementation.
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

    std::function<void(void)> _initialize;
    std::function<void(void)> _reset;

    std::function<void(std::type_index, create_selection_algorithm_t)> _register_selection_algorithm;
    std::function<void(std::type_index, create_termination_condition_t)> _register_termination_condition;
    std::function<void(try_create_chromosome_t)> _register_chromosome;
    std::function<void(std::type_index, create_crossover_t)> _register_crossover;
    std::function<void(std::type_index, create_mutation_t)> _register_mutation;

    std::function<stochastic*(void)> _get_stochastic;

    std::function<population*(population_metadata*)> _create_population;
    std::function<void(population*)> _delete_population;

public:
    inline explicit gc_core() {
        _assembly = nullptr;

        _initialize = gc_initialize;
        _reset = gc_reset;

        _register_selection_algorithm = gc_register_selection_algorithm;
        _register_termination_condition = gc_register_termination_condition;
        _register_chromosome = gc_register_chromosome;
        _register_crossover = gc_register_crossover;
        _register_mutation = gc_register_mutation;

        _get_stochastic = gc_get_stochastic;

        _create_population = gc_create_population;
        _delete_population = gc_delete_population;
    }

    inline explicit gc_core(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());

        _initialize =
                load_assembly_func<void(void)>(
                        _assembly, "gc_initialize");
        _reset =
                load_assembly_func<void(void)>(
                        _assembly, "gc_reset");

        _register_selection_algorithm =
                load_assembly_func<void(std::type_index, create_selection_algorithm_t)>(
                        _assembly, "gc_register_selection_algorithm");
        _register_termination_condition =
                load_assembly_func<void(std::type_index, create_termination_condition_t)>(
                        _assembly, "gc_register_termination_condition");
        _register_chromosome =
                load_assembly_func<void(try_create_chromosome_t)>(
                        _assembly, "gc_register_chromosome");
        _register_crossover =
                load_assembly_func<void(std::type_index, const create_crossover_t&)>(
                        _assembly, "gc_register_crossover");
        _register_mutation =
                load_assembly_func<void(std::type_index, const create_mutation_t&)>(
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
        if(_assembly != nullptr)
            FreeLibrary(_assembly);
    }

    inline void initialize() {
        _initialize();
    }

    inline void reset() {
        _reset();
    }

    inline void register_selection_algorithm(std::type_index index, const create_selection_algorithm_t& create_selection_algorithm) {
        _register_selection_algorithm(index, create_selection_algorithm);
    }

    inline void register_termination_condition(std::type_index index, const create_termination_condition_t& create_termination_condition) {
        _register_termination_condition(index, create_termination_condition);
    }

    inline void register_chromosome(try_create_chromosome_t try_create) {
        _register_chromosome(std::move(try_create));
    }

    inline void register_crossover(std::type_index index, const create_crossover_t& create_crossover) {
        _register_crossover(index, create_crossover);
    }

    inline void register_mutation(std::type_index index, const create_mutation_t& create_mutation) {
        _register_mutation(index, create_mutation);
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

    std::function<void(gc_core*)> _bootstrap;

public:
    inline explicit gc_satellite(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());

        _bootstrap =
                load_assembly_func<void(gc_core*)>(
                        _assembly, "gc_bootstrap");
    }

    inline ~gc_satellite() {
        FreeLibrary(_assembly);
    }

    inline void bootstrap(gc_core* core) {
        _bootstrap(core);
    }
};

#endif /* _GALAPAGOS_ASSEMBLIES_H_ */
