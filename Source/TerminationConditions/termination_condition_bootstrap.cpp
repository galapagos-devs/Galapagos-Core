#include <typeindex>

#include "../API/galapagos.h"
#include "../API/genetic_factory.h"
#include "../galapagos_assemblies.h"

#include "fitness_threshold.h"

GALAPAGOS_BOOTSTRAP void gc_bootstrap(genetic_factory* factory) {
    factory->register_termination_condition(std::type_index(typeid(fitness_threshold_metadata)),
            [](const termination_condition_metadata& metadata) {
                const auto& dynamic = dynamic_cast<const fitness_threshold_metadata&>(metadata);
                return new fitness_threshold(dynamic);
    }, [](termination_condition* termination_condition) { delete termination_condition; });
}