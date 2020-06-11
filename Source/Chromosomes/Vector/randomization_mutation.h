//
// Created by kosie on 12/3/2019.
//

#ifndef _RANDOMIZATION_MUTATION_H_
#define _RANDOMIZATION_MUTATION_H_

#include "../../API/galapagos_metadata.h"
#include "../../API/stochastic.h"

#include "../mutation_internal.h"

#include "vector_chromosome.h"

struct randomization_mutation_metadata : mutation_metadata {

};

class randomization_mutation : public mutation_internal<vector_chromosome> {
private:
    stochastic* _stochastic_instance;

protected:
    chromosome* invoke(vector_chromosome* chromosome) override;

public:
    explicit  randomization_mutation(randomization_mutation_metadata* metadata, stochastic* stochastic_instance);

    ~randomization_mutation() /*override*/;

};

#endif /* _RANDOMIZATION_MUTATION_H_ */
