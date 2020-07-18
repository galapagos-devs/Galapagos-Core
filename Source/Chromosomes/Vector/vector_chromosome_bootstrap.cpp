#include <typeindex>
#include <memory>

#include "../../API/galapagos.h"
#include "../../galapagos_assemblies.h"

#include "vector_chromosome.h"
#include "kpoint_crossover.h"
#include "gaussian_mutation.h"
#include "randomization_mutation.h"

GALAPAGOS_API void gc_bootstrap(gc_core* core) {
    stochastic* stochastic_instance = core->get_stochastic();

    core->register_chromosome(std::type_index(typeid(vector_chromosome_metadata)),
            [stochastic_instance](const chromosome_metadata* metadata) {
                auto *dynamic = dynamic_cast<const vector_chromosome_metadata*>(metadata);
                std::shared_ptr<vector_chromosome> chromosome(new vector_chromosome(dynamic, stochastic_instance));
                return chromosome;
    });

    core->register_crossover(std::type_index(typeid(kpoint_crossover_metadata)),
            [stochastic_instance](const crossover_metadata* metadata) {
                auto* dynamic = dynamic_cast<const kpoint_crossover_metadata*>(metadata);
                std::shared_ptr<kpoint_crossover> crossover(new kpoint_crossover(dynamic, stochastic_instance));
                return crossover;
    });

    core->register_mutation(std::type_index(typeid(gaussian_mutation_metadata)),
            [stochastic_instance](const mutation_metadata* metadata) {
                auto* dynamic = dynamic_cast<const gaussian_mutation_metadata*>(metadata);
                std::shared_ptr<gaussian_mutation> mutation(new gaussian_mutation(dynamic, stochastic_instance));
                return mutation;
    });

    core->register_mutation(std::type_index(typeid(randomization_mutation_metadata)),
            [stochastic_instance](const mutation_metadata* metadata) {
                auto* dynamic = dynamic_cast<const randomization_mutation_metadata*>(metadata);
                std::shared_ptr<randomization_mutation> mutation(new randomization_mutation(dynamic, stochastic_instance));
                return mutation;
    });
}