#include "gaussian_mutation.h"

// TODO: argument chromosome was renamed cchromosome to fix the type shadowing of the trailing return type. fix this.
auto gaussian_mutation::invoke(const std::shared_ptr<const vector_chromosome>& cchromosome) const -> std::shared_ptr<chromosome> {
    auto child = std::make_shared<vector_chromosome>(cchromosome);
    size_t index = _stochastic_instance.rand_int(cchromosome->num_genes());

    double value = child->get_gene(index) + _stochastic_instance.rand_gaussian(_metadata->mean, _metadata->standard_deviation);
    child->set_gene(index, value);

    return child;
}