#ifndef _GALAPAGOS_ASSEMBLIES_H_
#define _GALAPAGOS_ASSEMBLIES_H_

/* This header file contains the definitions of the assemblies (.dll or .so) that are used in the core galapagos
 * bootstrapping procedure. 'gc_core' is the bootstrapping interface for the core galapagos library assembly while
 * 'gc_satellite' is the interface to any assembly that wishes to inject custom API objects into galapagos on startup.*/

#ifdef WIN32
#define GALAPAGOS_BOOTSTRAP extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_BOOTSTRAP extern "C" __attribute__((visibility("default")))
#endif

#include <string>
#include <utility>
#include <filesystem>
#include <memory>
#include <Windows.h> // TODO: currently only windows implementation exist. posix implementations will be needed as well.

#include "API/galapagos.h"
#include "API/genetic_factory.h"

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
    std::function<genetic_factory*()> _bootstrap;

public:
    inline explicit gc_core(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());
        _bootstrap = load_assembly_func<genetic_factory*()>(_assembly, "gc_bootstrap");
    }

    inline ~gc_core() {
        FreeLibrary(_assembly);
    }

    inline genetic_factory* bootstrap() {
        genetic_factory* factory =_bootstrap();
        bootstrap_satellites(factory);
        return factory;
    }

private:
    void bootstrap_satellites(genetic_factory* factory);
};

class gc_satellite {
private:
    HMODULE _assembly;
    std::function<void(genetic_factory*)> _bootstrap;

public:
    inline explicit gc_satellite(const std::string& assembly_location) {
        _assembly = LoadLibrary(assembly_location.c_str());
        _bootstrap = load_assembly_func<void(genetic_factory*)>(_assembly, "gc_bootstrap");
    }

    inline ~gc_satellite() {
        FreeLibrary(_assembly);
    }

    inline void bootstrap(genetic_factory* factory) {
        _bootstrap(factory);
    }
};

inline void gc_core::bootstrap_satellites(genetic_factory* factory) {
    // find all dlls in current directory that export the symbol 'gc_bootstrap'
    for (const auto &dir_entry : std::filesystem::recursive_directory_iterator(".")) {
        const std::filesystem::path& entry_path = dir_entry.path();
        if (entry_path.extension() == ".dll" &&  // FIXME: This will not work on linux
            entry_path.filename() != "Galapagos.dll") {
            const std::string filename = entry_path.filename().string();
            auto satellite = std::make_shared<gc_satellite>(filename);
            satellite->bootstrap(factory);
            _satellites.push_back(satellite);
        }
    }
}

#endif /* _GALAPAGOS_ASSEMBLIES_H_ */
