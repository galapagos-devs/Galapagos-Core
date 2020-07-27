#include "vector_chromosome.h"
#include "randomization_mutation.h"

randomization_mutation::randomization_mutation(const randomization_mutation_metadata& metadata, stochastic *stochastic_instance) :
    mutation_internal{metadata} {
    _stochastic_instance = stochastic_instance;
}

std::shared_ptr<chromosome> randomization_mutation::invoke(const std::shared_ptr<const vector_chromosome> chromosome) const {
    auto child = std::make_shared<vector_chromosome>(chromosome);
    double min = child->gene_inf();
    double max = child->gene_sup();

    for(size_t i = 0; i < chromosome->num_genes(); i++) {
        double value = _stochastic_instance->rand_double(min, max);
        child->set_gene(i, value);
    }

    return child;
}
