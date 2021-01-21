#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos_bootstrap
 * bootstrapping procedure. 'galapagos_bootstrap' is the bootstrapping interface for the core galapagos_bootstrap library assembly while
 * 'galapagos_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos_bootstrap on startup.*/

#include <functional>
#include <typeindex>
#include <string>
#include <utility>
#include <filesystem>
#include <memory>

#include "stochastic.h"
#include "galapagos_metadata.h"
#include "selection_algorithm.h"
#include "termination_condition.h"
#include "population.h"
#include "creature.h"
#include "chromosome.h"
#include "genetic_operator.h"
#include "crossover.h"
#include "mutation.h"
#include "genetic_factory.h"

// region Macro Magic
#define HSTRING(function_name) #function_name
#define STRING(function_name) HSTRING(function_name)
#define BOOTSTRAP_FUNCTION galapagos_bootstrap
#ifdef WIN32
#define GALAPAGOS_BOOTSTRAP extern "C" __declspec(dllexport) void BOOTSTRAP_FUNCTION
#else
#define GALAPAGOS_BOOTSTRAP extern "C" __attribute__((visibility("default"))) void BOOTSTRAP_FUNCTION
#endif

// Facilitates macro overload by number of args
#define GET_MACRO(_1, _2, _3, _4, NAME,...) NAME

/* Use `GALAPAGOS_REGISTER_OBJ` to register new object derivatives.
 *
 * The ``GALAPAGOS_REGISTER_OBJ__<X>ARGS`` are macro overloads.
 * These overloads make the following assumptions:
 *
 *    #. The ``derived_type`` is built from an object with the same name as ``derived_type``,
 *       only suffixed with ``_metadata``, i.e. ``derived_type_metadata``.
 *
 *    #. The ``base_type`` has a `std::shared_ptr<base_type>` type-alias with the same name as ``base_type``,
 *       only suffixed with a ``_ptr``, i.e. ``base_type_ptr``
 *
 *    #. The ``factor`` pointer has a method to register an extension of ``base_type`` (i.e. ``derived_type``)
 *       and that method is named ``register_base_type)``
 *
 */
#define GALAPAGOS_REGISTER_OBJ__3ARGS(factory, base_type, derived_type) \
    factory->register_##base_type(std::type_index(typeid(derived_type##_metadata)), \
    [](base_type##_metadata_ptr metadata){ \
    auto derived_metadata = std::dynamic_pointer_cast<derived_type##_metadata>(std::move(metadata)); \
    return new derived_type(derived_metadata); \
    }, [](base_type *obj) { delete obj; })

#define GALAPAGOS_REGISTER_OBJ__4ARGS(factory, base_type, derived_type, stochastic_instance) \
    factory->register_##base_type(std::type_index(typeid(derived_type##_metadata)), \
    [&stochastic_instance](base_type##_metadata_ptr metadata){ \
    auto derived_metadata = std::dynamic_pointer_cast<derived_type##_metadata>(std::move(metadata)); \
    return new derived_type(derived_metadata, stochastic_instance); \
    }, [](base_type *obj) { delete obj; })


#define GALAPAGOS_REGISTER_OBJ(...) \
    GET_MACRO(__VA_ARGS__, GALAPAGOS_REGISTER_OBJ__4ARGS, GALAPAGOS_REGISTER_OBJ__3ARGS)(__VA_ARGS__)

// endregion

// TODO: this is a windows method for loading assembly functions. need a posix implementation.
#include <Windows.h>
template <typename TSignature>
inline std::function<TSignature> load_assembly_func(HMODULE assembly, const std::string& func_name) {
    FARPROC address = GetProcAddress(assembly, func_name.c_str());
    if (!address)
        return nullptr;

    std::function<TSignature> func(reinterpret_cast<TSignature*>(address));
    return func;
}

class galapagos_assembly {
protected:
    HMODULE _assembly;
    std::function<void(genetic_factory*&)> _bootstrap;

public:
    inline explicit galapagos_assembly(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());
        _bootstrap = load_assembly_func<void(genetic_factory*&)>(_assembly, STRING(BOOTSTRAP_FUNCTION));
    }

    inline virtual ~galapagos_assembly() {
        release();
    }

    inline void release() {
        FreeLibrary(_assembly);
    }
};

class galapagos_satellite : public galapagos_assembly {
public:
    inline explicit galapagos_satellite(const std::string& assembly_location) :
        galapagos_assembly(assembly_location) { }

    inline void bootstrap(genetic_factory*& factory) {
        _bootstrap(factory);
    }
};

class galapagos : public galapagos_assembly {
private:
    std::vector<std::shared_ptr<galapagos_satellite>> _satellites;

public:
    inline explicit galapagos(const std::string& assembly_location) :
        galapagos_assembly(assembly_location) { }

    inline ~galapagos() override {
        release();
    }

    inline genetic_factory* bootstrap() {
        genetic_factory* factory = nullptr;
        _bootstrap(factory);
        _bootstrap_satellites(factory);
        return factory;
    }

private:
    inline void _bootstrap_satellites(genetic_factory* factory) {
        // find all dlls in current directory that export the symbol 'gc_bootstrap'
        for (const auto &dir_entry : std::filesystem::recursive_directory_iterator(".")) {
            const std::filesystem::path& entry_path = dir_entry.path();
            if (entry_path.extension() == ".dll" &&  // FIXME: This will not work on linux
                entry_path.filename() != "Galapagos.dll") {
                const std::string filename = entry_path.filename().string();
                auto satellite = std::make_shared<galapagos_satellite>(filename);
                satellite->bootstrap(factory);
                _satellites.push_back(satellite);
            }
        }
    }
};

#endif /* _GALAPAGOS_H_ */
