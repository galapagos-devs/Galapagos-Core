#include "vector_chromosome.h"
#include "randomization_mutation.h"

randomization_mutation::randomization_mutation(const randomization_mutation_metadata* const metadata, stochastic *stochastic_instance) :
    mutation_internal{metadata} {
    _stochastic_instance = stochastic_instance;
}

randomization_mutation::~randomization_mutation() = default;

chromosome *randomization_mutation::invoke(const vector_chromosome* const chromosome) const {
    auto* const child = new vector_chromosome(chromosome);
    double min = child->gene_inf();
    double max = child->gene_sup();

    for(size_t i = 0; i < chromosome->num_genes(); i++) {
        double value = _stochastic_instance->rand_double(min, max);
        child->set_gene(i, value);
    }

    return child;
}
