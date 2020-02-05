#ifndef _GALAPAGOS_ASSEMBLIES_H_
#define _GALAPAGOS_ASSEMBLIES_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos
 * bootstrapping procedure. 'gc_core' is the bootstrapping interface for the core galapagos library assembly while
 * 'gc_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos on startup.*/

// TODO: currently only windows implementation exist. posix implementations will be needed as well.

#include <string>
#include <Windows.h>
#include <iostream> // TODO: delete this
#include <experimental/filesystem>
#include <utility>

#include "API/galapagos.h"

namespace fs = std::experimental::filesystem; // namespace alias

template <typename TSignature>
inline std::function<TSignature> load_assembly_func(HMODULE assembly, const std::string& func_name) {
    std::cout << func_name << std::endl;
    FARPROC address = GetProcAddress(assembly, func_name.c_str());
    if (!address) {
        std::cout << "?" << std::endl;
        return nullptr;
    }

    std::function<TSignature> func(reinterpret_cast<TSignature*>(address));
    return func;
}

class gc_satellite; // forward declaration
class gc_core {
private:
    HMODULE _assembly;
    std::vector<gc_satellite*> _satellites;
    bool _initialized = false;

    std::function<void(try_create_selection_algorithm_t)> _register_selection_algorithm;
    std::function<void(try_create_termination_condition_t)> _register_termination_condition;
    std::function<void(try_create_chromosome_t)> _register_chromosome;
    std::function<void(try_create_crossover_t)> _register_crossover;
    std::function<void(try_create_mutation_t)> _register_mutation;
    std::function<stochastic*(void)> _get_stochastic;

    std::function<population*(population_metadata*)> _create_population;
    std::function<void(population*)> _delete_population;

public:
    inline explicit gc_core(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());

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

    inline ~gc_core();

    inline void initialize();

    inline void register_selection_algorithm(try_create_selection_algorithm_t try_create) {
        _register_selection_algorithm(std::move(try_create));
    }

    inline void register_termination_condition(try_create_termination_condition_t try_create) {
        _register_termination_condition(std::move(try_create));
    }

    inline void register_chromosome(try_create_chromosome_t try_create) {
        _register_chromosome(std::move(try_create));
    }

    inline void register_crossover(try_create_crossover_t try_create) {
        _register_crossover(std::move(try_create));
    }

    inline void register_mutation(try_create_mutation_t try_create) {
        _register_mutation(std::move(try_create));
    }

    inline stochastic* get_stochastic() {
        return  _get_stochastic();
    }

    inline population* create_population(population_metadata* metadata) {
        // lazily initialize the bootstrapping procedure
        if(!_initialized)
            initialize();

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

gc_core::~gc_core() {
    FreeLibrary(_assembly);
    for (auto & satellite : _satellites)
        delete satellite;
}

void gc_core::initialize() {
    if(!_initialized) {
        // find all dlls in current directory that export the symbol 'gc_bootstrap'
        for (const auto &dir_entry : fs::recursive_directory_iterator(".")) {
            const fs::path& entry_path = dir_entry.path();
            if (entry_path.extension() == ".dll" &&
                entry_path.filename() != "Galapagos.dll") {
                const std::string filename = entry_path.filename().string();
                auto* satellite = new gc_satellite(filename);
                satellite->bootstrap(this);
                _satellites.push_back(satellite);
            }
        }

        _initialized = true;
    }
}

#endif /* _GALAPAGOS_ASSEMBLIES_H_ */
