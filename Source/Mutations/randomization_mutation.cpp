//
// Created by kosie on 12/3/2019.
//

#include "randomization_mutation.h"

randomization_mutation::randomization_mutation(randomization_mutation_metadata *metadata,
                                               stochastic *stochastic_instance) {
    _stochastic_instance = stochastic_instance;
}

randomization_mutation::~randomization_mutation() = default;

chromosome *randomization_mutation::invoke(vector_chromosome *chromosome) {
    double* seed = new double[chromosome->_size];
    for(size_t i = 0; i < chromosome->_size; i++)
        seed[i] = _stochastic_instance->rand_double(); // TODO: how do we determine the bounds on this?

    // TODO: this information flow needs to be reworked. are we holding onto metadata?
    vector_chromosome* child = new vector_chromosome(nullptr, seed);
    return child;
}
