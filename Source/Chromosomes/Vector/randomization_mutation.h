#ifndef _RANDOMIZATION_MUTATION_H_
#define _RANDOMIZATION_MUTATION_H_

#include <memory>

#include "../../API/stochastic.h"

#include "API/vector_chromosome_metadata.h"
#include "API/vector_chromosome.h"

#include "../mutation_internal.h"

class randomization_mutation : public mutation_internal<vector_chromosome> {
private:
    stochastic& _stochastic_instance;

public:
    inline explicit randomization_mutation(randomization_mutation_metadata_ptr metadata, stochastic& stochastic_instance) :
            mutation_internal{metadata}, _stochastic_instance{stochastic_instance} {}

protected:
    [[nodiscard]] std::shared_ptr<chromosome> invoke(const std::shared_ptr<const vector_chromosome>& chromosome) const override;

};

#endif /* _RANDOMIZATION_MUTATION_H_ */
