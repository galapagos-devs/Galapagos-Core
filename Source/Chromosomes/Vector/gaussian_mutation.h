#ifndef _GAUSSIAN_MUTATION_H_
#define _GAUSSIAN_MUTATION_H_

#include "../../API/galapagos_metadata.h"
#include "../../API/stochastic.h"
#include "../mutation_internal.h"
#include "vector_chromosome.h"

struct gaussian_mutation_metadata : mutation_metadata {
    const double mean;
    const double standard_deviation;

    gaussian_mutation_metadata(
            const double weight, const double mean, const double standard_deviation) :
                mutation_metadata{weight},
                mean{mean}, standard_deviation{standard_deviation} {}
};

class gaussian_mutation : public mutation_internal<vector_chromosome> {
private:
    double _mean;
    double _standard_deviation;

    stochastic* _stochastic_instance;

protected:
    chromosome* invoke(vector_chromosome* chromosome) override;

public:
    explicit gaussian_mutation(const gaussian_mutation_metadata* metadata, stochastic* stochastic_instance);

    ~gaussian_mutation() /*override*/;
};

#endif /* _GAUSSIAN_MUTATION_H_ */
