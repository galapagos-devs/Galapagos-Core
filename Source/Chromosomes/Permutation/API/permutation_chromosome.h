#ifndef _PERMUTATION_CHROMOSOME_H_
#define _PERMUTATION_CHROMOSOME_H_

#include <vector>
#include <memory>

#include "../../../API/chromosome.h"
#include "../../../API/stochastic.h"

#include "permutation_chromosome_metadata.h"

class permutation_chromosome : public chromosome {
private:
    permutation_chromosome_metadata_ptr _metadata;
    stochastic& _stochastic_instance;
    std::vector<size_t> _genes;

public:
    // region Inherited Methods

    explicit permutation_chromosome(permutation_chromosome_metadata_ptr metadata, stochastic& stochastic_instance);

    double get_distance(const std::shared_ptr<const chromosome>& other) const override;

    // endregion

    //region Attributes

    virtual size_t num_genes() const;

    //endregion

    //region Getters & Setters

    virtual size_t get_gene(size_t index) const;

    //endregion
};

#endif /* _PERMUTATION_CHROMOSOME_H_ */
