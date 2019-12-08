#ifndef _GALAPAGOS_GAUSSIAN_MUTATION_H_
#define _GALAPAGOS_GAUSSIAN_MUTATION_H_

#include "../API/galapagos_metadata.h"
#include "../API/stochastic.h"
#include "mutation_internal.h"
#include "../Chromosomes/vector_chromosome.h"

struct gaussian_mutation_metadata : mutation_metadata {
    double mean;
    double standard_deviation;
};

class gaussian_mutation : public mutation_internal<vector_chromosome> {
private:
    double _mean;
    double _standard_deviation;

    stochastic* _stochastic_instance;

protected:
    chromosome* invoke(vector_chromosome* chromosome) override;

public:
    explicit  gaussian_mutation(gaussian_mutation_metadata* metadata, stochastic* stochastic_instance);

    ~gaussian_mutation() /*override*/;
};

#endif /* _GALAPAGOS_GAUSSIAN_MUTATION_H_ */
