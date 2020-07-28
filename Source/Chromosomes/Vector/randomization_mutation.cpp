#include "vector_chromosome.h"
#include "randomization_mutation.h"

std::shared_ptr<chromosome> randomization_mutation::invoke(const std::shared_ptr<const vector_chromosome> chromosome) const {
    auto child = std::make_shared<vector_chromosome>(chromosome);
    double min = child->gene_inf();
    double max = child->gene_sup();

    for(size_t i = 0; i < chromosome->num_genes(); i++) {
        double value = _stochastic_instance.rand_double(min, max);
        child->set_gene(i, value);
    }

    return child;
}
