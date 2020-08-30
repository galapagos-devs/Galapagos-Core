#ifndef _GAUSSIAN_MUTATION_H_
#define _GAUSSIAN_MUTATION_H_

#include <memory>

#include "../../API/galapagos_metadata.h"
#include "../../API/stochastic.h"
#include "../mutation_internal.h"
#include "vector_chromosome.h"

struct gaussian_mutation_metadata : mutation_metadata, galapagos_metadata<mutation_metadata, gaussian_mutation_metadata> {
    const double mean;
    const double standard_deviation;

    gaussian_mutation_metadata(
            const double weight, const double mean, const double standard_deviation) :
                mutation_metadata{weight},
                mean{mean}, standard_deviation{standard_deviation} {}
};

class gaussian_mutation : public mutation_internal<vector_chromosome> {
private:
    const gaussian_mutation_metadata& _metadata;
    stochastic& _stochastic_instance;

public:
    inline explicit gaussian_mutation(const gaussian_mutation_metadata& metadata, stochastic& stochastic_instance) :
            _metadata{metadata}, _stochastic_instance{stochastic_instance}, mutation_internal{metadata} {}

protected:
    [[nodiscard]] std::shared_ptr<chromosome> invoke(const std::shared_ptr<const vector_chromosome>& chromosome) const override;
};

#endif /* _GAUSSIAN_MUTATION_H_ */
