#include <typeindex>

#include "../../API/galapagos.h"
#include "../../galapagos_assemblies.h"
#include "../../stochastic_internal.h"

#include "vector_chromosome.h"
#include "kpoint_crossover.h"
#include "gaussian_mutation.h"
#include "randomization_mutation.h"

GALAPAGOS_BOOTSTRAP void gc_bootstrap(gc_core* core) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();

    core->register_chromosome(std::type_index(typeid(vector_chromosome_metadata)),
            [&stochastic_instance](const chromosome_metadata& metadata) {
                const auto& dynamic = dynamic_cast<const vector_chromosome_metadata&>(metadata);
                return new vector_chromosome(dynamic, stochastic_instance);
    }, [](chromosome* chromosome) { delete chromosome; });

    core->register_crossover(std::type_index(typeid(kpoint_crossover_metadata)),
            [&stochastic_instance](const crossover_metadata& metadata) {
                const auto& dynamic = dynamic_cast<const kpoint_crossover_metadata&>(metadata);
                return new kpoint_crossover(dynamic, stochastic_instance);
    }, [](crossover* crossover) { delete crossover; });

    core->register_mutation(std::type_index(typeid(gaussian_mutation_metadata)),
            [&stochastic_instance](const mutation_metadata& metadata) {
                const auto& dynamic = dynamic_cast<const gaussian_mutation_metadata&>(metadata);
                return new gaussian_mutation(dynamic, stochastic_instance);
    }, [](mutation* mutation) { delete mutation; });

    core->register_mutation(std::type_index(typeid(randomization_mutation_metadata)),
            [&stochastic_instance](const mutation_metadata& metadata) {
                const auto& dynamic = dynamic_cast<const randomization_mutation_metadata&>(metadata);
                return new randomization_mutation(dynamic, stochastic_instance);
    }, [](mutation* mutation) { delete mutation; });
}