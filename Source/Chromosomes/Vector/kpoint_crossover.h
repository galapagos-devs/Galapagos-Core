#ifndef _KPOINT_CROSSOVER_H_
#define _KPOINT_CROSSOVER_H_

#include "../../API/crossover.h"
#include "../../API/galapagos_metadata.h"
#include "../../API/stochastic.h"

#include "../crossover_internal.h"

#include "vector_chromosome.h"

struct kpoint_crossover_metadata : crossover_metadata {
    const size_t cut_points;

    kpoint_crossover_metadata(
            const double weight, const size_t cut_points) :
                crossover_metadata{weight},
                cut_points{cut_points} {}
};

class kpoint_crossover : public crossover_internal<vector_chromosome> {
private:
    const kpoint_crossover_metadata* const _metadata;

    stochastic* _stochastic_instance;

public:
    //region Constructor & Destructor

    explicit kpoint_crossover(const kpoint_crossover_metadata* metadata, stochastic* stochastic_instance);
    ~kpoint_crossover();

    //endregion

private:
    std::vector<int> _get_cut_points(size_t chromosome_len) const;

protected:
    chromosome* invoke(const vector_chromosome* const x, const vector_chromosome* const y) const override;
};



#endif /* _KPOINT_CROSSOVER_H_ */
