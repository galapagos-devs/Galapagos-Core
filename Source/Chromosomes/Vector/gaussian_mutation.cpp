#include "gaussian_mutation.h"

std::shared_ptr<chromosome> gaussian_mutation::invoke(const std::shared_ptr<const vector_chromosome>& chromosome) const {
    auto child = std::make_shared<vector_chromosome>(chromosome);
    size_t index = _stochastic_instance.rand_int(chromosome->num_genes());

    double value = child->get_gene(index) + _stochastic_instance.rand_gaussian(_metadata.mean, _metadata.standard_deviation);
    child->set_gene(index, value);

    return child;
}