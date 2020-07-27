#include <cmath>

#include "gaussian_mutation.h"

gaussian_mutation::gaussian_mutation(const gaussian_mutation_metadata& metadata, stochastic* stochastic_instance) :
    _metadata{metadata}, mutation_internal{metadata} {
    _stochastic_instance = stochastic_instance;
}

gaussian_mutation::~gaussian_mutation() = default;

std::shared_ptr<chromosome> gaussian_mutation::invoke(const std::shared_ptr<const vector_chromosome> chromosome) const {
    auto child = std::make_shared<vector_chromosome>(chromosome);
    size_t index = _stochastic_instance->rand_int(chromosome->num_genes());

    double value = child->get_gene(index) + _stochastic_instance->rand_gaussian(_metadata.mean, _metadata.standard_deviation);
    child->set_gene(index, value);

    return child;
}