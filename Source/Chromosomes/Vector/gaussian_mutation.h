#ifndef _GAUSSIAN_MUTATION_H_
#define _GAUSSIAN_MUTATION_H_

#include <memory>

#include "../../API/stochastic.h"

#include "API/vector_chromosome_metadata.h"
#include "API/vector_chromosome.h"

#include "../mutation_internal.h"

class gaussian_mutation : public mutation_internal<vector_chromosome> {
private:
    gaussian_mutation_metadata_ptr _metadata;
    stochastic& _stochastic_instance;

public:
    inline explicit gaussian_mutation(gaussian_mutation_metadata_ptr metadata, stochastic& stochastic_instance) :
            _metadata{metadata}, _stochastic_instance{stochastic_instance}, mutation_internal{metadata} {}

protected:
    [[nodiscard]] std::shared_ptr<chromosome> invoke(const std::shared_ptr<const vector_chromosome>& chromosome) const override;
};

#endif /* _GAUSSIAN_MUTATION_H_ */
