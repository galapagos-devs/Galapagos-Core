#include "../API/galapagos.h"
#include "../galapagos_assemblies.h"

#include "fitness_threshold.h"

GALAPAGOS_API void gc_bootstrap() {
    gc_core lib("Galapagos.dll");
    lib.register_termination_condition([](termination_condition_metadata* metadata, termination_condition* termination_condition) {
        fitness_threshold_metadata* dynamic = dynamic_cast<fitness_threshold_metadata*>(metadata);
        if(dynamic != nullptr) {
            termination_condition = new fitness_threshold(dynamic);
            return true;
        }
        return false;
    });

    // get the handle of galapagos core. we should not need to load it should have called gc_bootstrap
    // and thus should be loaded into process memory.
    /*HMODULE lib = GetModuleHandle("Galapagos.dll");
    if(lib) { // on load failures do nothing
        // register plugin objects with the core lib.
        std::function<void(try_create_termination_condition_t)> gc_register_termination_condition =
                loadDllFunc<void(try_create_termination_condition_t)>(lib, "gc_register_termination_condition");
        if(gc_register_termination_condition) {
            gc_register_termination_condition([](termination_condition_metadata* metadata, termination_condition* termination_condition) {
                fitness_threshold_metadata* dynamic = dynamic_cast<fitness_threshold_metadata*>(metadata);
                if(dynamic != nullptr) {
                    termination_condition = new fitness_threshold(dynamic);
                    return true;
                }
                return false;
            });
        }
    }*/
}