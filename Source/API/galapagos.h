#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos
 * bootstrapping procedure. 'galapagos' is the bootstrapping interface for the core galapagos library assembly while
 * 'galapagos_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos on startup.*/

#define BOOTSTRAP_FUNCTION galapagos_bootstrap
#define BOOTSTRAP_FUNCTION_STRING "galapagos_bootstrap"
#ifdef WIN32
#define GALAPAGOS_BOOTSTRAP extern "C" __declspec(dllexport) void BOOTSTRAP_FUNCTION
#else
#define GALAPAGOS_BOOTSTRAP extern "C" __attribute__((visibility("default"))) void BOOTSTRAP_FUNCTION
#endif

#include <functional>
#include <typeindex>
#include <string>
#include <utility>
#include <filesystem>
#include <memory>
#include <Windows.h> // TODO: currently only windows implementation exist. posix implementations will be needed as well.

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

// TODO: this is a windows method for loading assembly functions. need a posix implementation.
template <typename TSignature>
inline std::function<TSignature> load_assembly_func(HMODULE assembly, const std::string& func_name) {
    FARPROC address = GetProcAddress(assembly, func_name.c_str());
    if (!address)
        return nullptr;

    std::function<TSignature> func(reinterpret_cast<TSignature*>(address));
    return func;
}

class galapagos_assembly {
private:
    std::string _location;

protected:
    HMODULE _assembly;
    std::function<void(genetic_factory*&)> _bootstrap;

public:
    inline explicit galapagos_assembly(const std::string& assembly_location) {
        _location = assembly_location;
        _assembly = LoadLibrary(assembly_location.c_str());
        _bootstrap = load_assembly_func<void(genetic_factory*&)>(_assembly, BOOTSTRAP_FUNCTION_STRING);
    }

    inline void release() {
        FreeLibrary(_assembly);
    }
};

class galapagos_satellite : public galapagos_assembly {
public:
    inline galapagos_satellite(const std::string& assembly_location) :
        galapagos_assembly(assembly_location) { }

    inline void bootstrap(genetic_factory*& factory) {
        _bootstrap(factory);
    }
};

class galapagos : public galapagos_assembly {
private:
    std::vector<std::shared_ptr<galapagos_satellite>> _satellites;

public:
    inline galapagos(const std::string& assembly_location) :
        galapagos_assembly(assembly_location) { }

    inline ~galapagos() {
        release();
        for(auto satellite : _satellites)
            satellite->release();
    }

    inline genetic_factory* bootstrap() {
        genetic_factory* factory;
        _bootstrap(factory);
        bootstrap_satellites(factory);
        return factory;
    }

private:
    void bootstrap_satellites(genetic_factory* factory);
};

inline void galapagos::bootstrap_satellites(genetic_factory* factory) {
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

#endif /* _GALAPAGOS_H_ */
