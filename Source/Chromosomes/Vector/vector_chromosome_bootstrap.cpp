#include "../../API/galapagos.h"
#include "../../galapagos_assemblies.h"

#include "vector_chromosome.h"
#include "kpoint_crossover.h"
#include "gaussian_mutation.h"
#include "randomization_mutation.h"

GALAPAGOS_API void gc_bootstrap() {
    gc_core lib("Galapagos.dll");
    stochastic *stochastic_instance = lib.get_stochastic();

    lib.register_chromosome([](chromosome_metadata *metadata, chromosome *chromosome) {
        auto *dynamic = dynamic_cast<vector_chromosome_metadata*>(metadata);
        if (dynamic != nullptr) {
            chromosome = new vector_chromosome(dynamic);
            return true;
        }
        return false;
    });

    lib.register_crossover([&stochastic_instance](crossover_metadata *metadata, crossover* crossover) {
        auto *dynamic = dynamic_cast<kpoint_crossover_metadata*>(metadata);
        if(dynamic != nullptr) {
            crossover = new kpoint_crossover(stochastic_instance, dynamic);
            return true;
        }
        return false;
    });

    lib.register_mutation([&stochastic_instance](mutation_metadata* metadata, mutation* mutation) {
       auto *dynamic = dynamic_cast<gaussian_mutation_metadata*>(metadata);
       if(dynamic != nullptr) {
           mutation = new gaussian_mutation(dynamic, stochastic_instance);
           return true;
       }
        return false;
    });

    lib.register_mutation([&stochastic_instance](mutation_metadata* metadata, mutation* mutation) {
        auto *dynamic = dynamic_cast<randomization_mutation_metadata*>(metadata);
        if(dynamic != nullptr) {
            mutation = new randomization_mutation(dynamic, stochastic_instance);
            return true;
        }
        return false;
    });
}