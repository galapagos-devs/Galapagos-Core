#include <typeindex>

#include "../../API/galapagos.h"
#include "../../API/genetic_factory.h"

#include "API/vector_chromosome.h"

#include "../../stochastic_internal.h"
#include "kpoint_crossover.h"
#include "gaussian_mutation.h"
#include "randomization_mutation.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();

    factory->register_chromosome(std::type_index(typeid(vector_chromosome_metadata)),
            [&stochastic_instance](chromosome_metadata_ptr metadata) {
                const auto& dynamic = dynamic_cast<const vector_chromosome_metadata&>(metadata);
                return new vector_chromosome(dynamic, stochastic_instance);
    }, [](chromosome* chromosome) { delete chromosome; });

    factory->register_crossover(std::type_index(typeid(kpoint_crossover_metadata)),
            [&stochastic_instance](crossover_metadata_ptr metadata) {
                const auto& dynamic = dynamic_cast<const kpoint_crossover_metadata&>(metadata);
                return new kpoint_crossover(dynamic, stochastic_instance);
    }, [](crossover* crossover) { delete crossover; });

    factory->register_mutation(std::type_index(typeid(gaussian_mutation_metadata)),
            [&stochastic_instance](mutation_metadata_ptr metadata) {
                const auto& dynamic = dynamic_cast<const gaussian_mutation_metadata&>(metadata);
                return new gaussian_mutation(dynamic, stochastic_instance);
    }, [](mutation* mutation) { delete mutation; });

    factory->register_mutation(std::type_index(typeid(randomization_mutation_metadata)),
            [&stochastic_instance](mutation_metadata_ptr metadata) {
                const auto& dynamic = dynamic_cast<const randomization_mutation_metadata&>(metadata);
                return new randomization_mutation(dynamic, stochastic_instance);
    }, [](mutation* mutation) { delete mutation; });
}