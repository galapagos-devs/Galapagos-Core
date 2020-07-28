#ifndef _GALAPAGOS_ASSEMBLIES_H_
#define _GALAPAGOS_ASSEMBLIES_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos
 * bootstrapping procedure. 'gc_core' is the bootstrapping interface for the core galapagos library assembly while
 * 'gc_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos on startup.*/

#include <string>
#include <utility>
#include <filesystem>
#include <memory>
#include <Windows.h> // TODO: currently only windows implementation exist. posix implementations will be needed as well.

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

class gc_satellite;
class gc_core {
private:
    HMODULE _assembly;
    std::vector<std::shared_ptr<gc_satellite>> _satellites;

    std::function<void(std::type_index, const create_selection_algorithm_t&)> _register_selection_algorithm;
    std::function<void(std::type_index, const create_termination_condition_t&)> _register_termination_condition;
    std::function<void(std::type_index, const create_chromosome_t&)> _register_chromosome;
    std::function<void(std::type_index, const create_crossover_t&)> _register_crossover;
    std::function<void(std::type_index, const create_mutation_t&)> _register_mutation;

    std::function<stochastic*(void)> _get_stochastic;

    std::function<population*(const population_metadata&)> _create_population;
    std::function<void(population*)> _delete_population;

public:
    inline explicit gc_core(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());

        _register_selection_algorithm =
                load_assembly_func<void(std::type_index, const create_selection_algorithm_t&)>(
                        _assembly, "gc_register_selection_algorithm");
        _register_termination_condition =
                load_assembly_func<void(std::type_index, const create_termination_condition_t&)>(
                        _assembly, "gc_register_termination_condition");
        _register_chromosome =
                load_assembly_func<void(std::type_index, const create_chromosome_t&)>(
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
                load_assembly_func<population*(const population_metadata&)>(
                        _assembly, "gc_create_population");
        _delete_population =
                load_assembly_func<void(population*)>(
                        _assembly, "gc_delete_population");

        load_satellites();
    }

    inline ~gc_core() {
        FreeLibrary(_assembly);
    }

    inline void register_selection_algorithm(std::type_index index, const create_selection_algorithm_t& create_selection_algorithm) {
        _register_selection_algorithm(index, create_selection_algorithm);
    }

    inline void register_termination_condition(std::type_index index, const create_termination_condition_t& create_termination_condition) {
        _register_termination_condition(index, create_termination_condition);
    }

    inline void register_chromosome(std::type_index index, const create_chromosome_t& create_chromosome) {
        _register_chromosome(index, create_chromosome);
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

    inline std::shared_ptr<population> create_population(const population_metadata& metadata) {
        return std::shared_ptr<population>(_create_population(metadata), _delete_population);
    }

private:
    void load_satellites();
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

inline void gc_core::load_satellites() {
    // find all dlls in current directory that export the symbol 'gc_bootstrap'
    for (const auto &dir_entry : std::filesystem::recursive_directory_iterator(".")) {
        const std::filesystem::path& entry_path = dir_entry.path();
        if (entry_path.extension() == ".dll" &&  // FIXME: This will not work on linux
            entry_path.filename() != "Galapagos.dll") {
            const std::string filename = entry_path.filename().string();
            auto satellite = std::make_shared<gc_satellite>(filename);
            satellite->bootstrap(this);
            _satellites.push_back(satellite);
        }
    }
}

#endif /* _GALAPAGOS_ASSEMBLIES_H_ */
