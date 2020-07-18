#include <typeindex>
#include <memory>

#include "../API/galapagos.h"
#include "../galapagos_assemblies.h"

#include "fitness_threshold.h"

GALAPAGOS_API void gc_bootstrap(gc_core* core) {
    core->register_termination_condition(std::type_index(typeid(fitness_threshold_metadata)),
            [](const termination_condition_metadata* metadata) {
                auto *dynamic = dynamic_cast<const fitness_threshold_metadata*>(metadata);
                std::shared_ptr<fitness_threshold> termination_condition(new fitness_threshold(dynamic));
                return termination_condition;
    });
}