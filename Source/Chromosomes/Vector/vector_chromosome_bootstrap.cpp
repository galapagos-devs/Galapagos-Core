#include "../../API/galapagos.h"
#include "../../galapagos_assemblies.h"

#include "vector_chromosome.h"
#include "kpoint_crossover.h"
#include "gaussian_mutation.h"
#include "randomization_mutation.h"

GALAPAGOS_API void gc_bootstrap(gc_core* core) {
    stochastic* stochastic_instance = core->get_stochastic();

    core->register_chromosome([stochastic_instance](const chromosome_metadata *metadata, chromosome*& chromosome) {
        auto *dynamic = dynamic_cast<const vector_chromosome_metadata*>(metadata);
        if (dynamic != nullptr) {
            chromosome = new vector_chromosome(dynamic, stochastic_instance);
            return true;
        }
        return false;
    });

    core->register_crossover([stochastic_instance](const crossover_metadata *metadata, crossover*& crossover) {
        auto *dynamic = dynamic_cast<const kpoint_crossover_metadata*>(metadata);
        if(dynamic != nullptr) {
            crossover = new kpoint_crossover(dynamic, stochastic_instance);
            return true;
        }
        return false;
    });

    core->register_mutation([stochastic_instance](const mutation_metadata* metadata, mutation*& mutation) {
       auto *dynamic = dynamic_cast<const gaussian_mutation_metadata*>(metadata);
       if(dynamic != nullptr) {
           mutation = new gaussian_mutation(dynamic, stochastic_instance);
           return true;
       }
        return false;
    });

    core->register_mutation([stochastic_instance](const mutation_metadata* metadata, mutation*& mutation) {
        auto *dynamic = dynamic_cast<const randomization_mutation_metadata*>(metadata);
        if(dynamic != nullptr) {
            mutation = new randomization_mutation(dynamic, stochastic_instance);
            return true;
        }
        return false;
    });
}