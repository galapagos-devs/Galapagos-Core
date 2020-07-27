#ifndef _GAUSSIAN_MUTATION_H_
#define _GAUSSIAN_MUTATION_H_

#include <memory>

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

    inline std::shared_ptr<const mutation_metadata> copy() const override {
        std::shared_ptr<const mutation_metadata> ptr(new gaussian_mutation_metadata(
            this->weight, this->mean, this->standard_deviation
        ));
        return ptr;
    }
};

class gaussian_mutation : public mutation_internal<vector_chromosome> {
private:
    const gaussian_mutation_metadata& _metadata;
    stochastic* _stochastic_instance;

public:
    explicit gaussian_mutation(const gaussian_mutation_metadata& metadata, stochastic* stochastic_instance);
    ~gaussian_mutation() /*override*/;

protected:
    std::shared_ptr<chromosome> invoke(std::shared_ptr<const vector_chromosome> chromosome) const override;
};

#endif /* _GAUSSIAN_MUTATION_H_ */
