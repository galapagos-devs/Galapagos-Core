#include <typeindex>

#include "../API/galapagos.h"
#include "../API/genetic_factory.h"

#include "fitness_threshold.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    factory->register_termination_condition(std::type_index(typeid(fitness_threshold_metadata)),
            [](termination_condition_metadata_ptr metadata) {
                const auto& dynamic = dynamic_cast<const fitness_threshold_metadata&>(metadata);
                return new fitness_threshold(dynamic);
    }, [](termination_condition* termination_condition) { delete termination_condition; });
}