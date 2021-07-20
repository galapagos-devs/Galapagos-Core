#include "randomization_mutation.h"

// TODO: argument chromosome was renamed cchromosome to fix the type shadowing of the trailing return type. fix this.
auto randomization_mutation::invoke(const std::shared_ptr<const vector_chromosome>& cchromosome) const -> std::shared_ptr<chromosome> {
    auto child = std::make_shared<vector_chromosome>(cchromosome);
    double min = child->gene_inf();
    double max = child->gene_sup();

    for(size_t i = 0; i < cchromosome->num_genes(); i++) {
        double value = _stochastic_instance.rand_double(min, max);
        child->set_gene(i, value);
    }

    return child;
}
