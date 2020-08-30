#ifndef _RANDOMIZATION_MUTATION_H_
#define _RANDOMIZATION_MUTATION_H_

#include <memory>

#include "../../API/galapagos_metadata.h"
#include "../../API/stochastic.h"

#include "../mutation_internal.h"

#include "vector_chromosome.h"

struct randomization_mutation_metadata : mutation_metadata, galapagos_metadata<randomization_mutation_metadata> {
    explicit randomization_mutation_metadata(
            const double weight) :
                mutation_metadata{weight} {}
};

class randomization_mutation : public mutation_internal<vector_chromosome> {
private:
    stochastic& _stochastic_instance;

public:
    inline explicit randomization_mutation(const randomization_mutation_metadata& metadata, stochastic& stochastic_instance) :
            mutation_internal{metadata}, _stochastic_instance{stochastic_instance} {}

protected:
    [[nodiscard]] std::shared_ptr<chromosome> invoke(const std::shared_ptr<const vector_chromosome>& chromosome) const override;

};

#endif /* _RANDOMIZATION_MUTATION_H_ */
