#ifndef _KPOINT_CROSSOVER_H_
#define _KPOINT_CROSSOVER_H_

#include <memory>

#include "../../API/crossover.h"
#include "../../API/galapagos_metadata.h"
#include "../../API/stochastic.h"

#include "../crossover_internal.h"

#include "vector_chromosome.h"

struct kpoint_crossover_metadata : crossover_metadata, galapagos_metadata<crossover_metadata, kpoint_crossover_metadata> {
    const size_t cut_points;

    kpoint_crossover_metadata(
            const double weight, const size_t cut_points) :
                crossover_metadata{weight},
                cut_points{cut_points} {}
};

class kpoint_crossover : public crossover_internal<vector_chromosome> {
private:
    const kpoint_crossover_metadata& _metadata;
    stochastic& _stochastic_instance;

public:
    //region Constructor & Destructor

    inline explicit kpoint_crossover(const kpoint_crossover_metadata& metadata, stochastic& stochastic_instance) :
        _metadata{metadata}, _stochastic_instance{stochastic_instance}, crossover_internal{metadata} {}

    //endregion

private:
    [[nodiscard]] std::vector<int> _get_cut_points(size_t chromosome_len) const;

protected:
    [[nodiscard]] std::shared_ptr<chromosome> invoke(const std::shared_ptr<const vector_chromosome>& x, const std::shared_ptr<const vector_chromosome>& y) const override;
};



#endif /* _KPOINT_CROSSOVER_H_ */
