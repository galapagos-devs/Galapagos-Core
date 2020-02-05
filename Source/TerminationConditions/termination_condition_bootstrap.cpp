#include "../API/galapagos.h"
#include "../galapagos_assemblies.h"

#include "fitness_threshold.h"

GALAPAGOS_API void gc_bootstrap(gc_core* core) {
    core->register_termination_condition([](termination_condition_metadata *metadata, termination_condition *termination_condition) {
        auto *dynamic = dynamic_cast<fitness_threshold_metadata *>(metadata);
        if (dynamic != nullptr) {
            termination_condition = new fitness_threshold(dynamic);
            return true;
        }
        return false;
    });
}