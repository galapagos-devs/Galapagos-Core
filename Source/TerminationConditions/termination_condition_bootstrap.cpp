#include <functional>

#include "../API/galapagos.h"

#include "fitness_threshold.h"

//typedef std::function<void(try_create_termination_condition_t try_create)> register_termination_condition_t;

#include <iostream>
#include <string>
#include <functional>
#include <windows.h>

template <typename T>
std::function<T> loadDllFunc(HMODULE lib, const std::string& funcName) {
    // Locate function in DLL.
    FARPROC lpfnGetProcessID = GetProcAddress(lib, funcName.c_str());

    // Check if function was located.
    if (!lpfnGetProcessID) {
        return nullptr;
    }

    // Create function object from function pointer.
    std::function<T> func(reinterpret_cast<T*>(lpfnGetProcessID));

    return func;
}

//#include <windows.h>
GALAPAGOS_API void gc_bootstrap() { // TODO: currently hard coded to work against windows
    // get the handle of galapagos core. we should not need to load it should have called gc_bootstrap
    // and thus should be loaded into process memory.
    HMODULE lib = GetModuleHandle("Galapagos.dll");
    if(lib) { // on load failures do nothing
        // register plugin objects with the core lib.
        std::function<void(try_create_termination_condition_t try_create)> gc_register_termination_condition =
                loadDllFunc<void(try_create_termination_condition_t try_create)>(lib, "gc_register_termination_condition");

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
    }
}