#include <cmath>
#include <functional>

#include "gaussian_mutation.h"

gaussian_mutation::gaussian_mutation(gaussian_mutation_metadata *metadata, stochastic* stochastic_instance) {
    _mean = metadata->mean;
    _standard_deviation = metadata->standard_deviation;

    _stochastic_instance = stochastic_instance;
}

gaussian_mutation::~gaussian_mutation() = default;

chromosome *gaussian_mutation::invoke(vector_chromosome *chromosome) {
    auto* child = new vector_chromosome(chromosome);
    size_t index = _stochastic_instance->rand_int(chromosome->num_genes());

    double value = child->get_gene(index) + _stochastic_instance->rand_gaussian(_mean, _standard_deviation);
    child->set_gene(index, value);

    return child;
}