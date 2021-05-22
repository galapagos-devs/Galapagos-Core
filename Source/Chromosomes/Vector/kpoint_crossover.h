#ifndef _KPOINT_CROSSOVER_H_
#define _KPOINT_CROSSOVER_H_

#include <memory>

#include "../../API/crossover.h"
#include "../../API/stochastic.h"

#include "API/vector_chromosome_metadata.h"
#include "API/vector_chromosome.h"

#include "../crossover_internal.h"

class kpoint_crossover : public crossover_internal<vector_chromosome> {
private:
    kpoint_crossover_metadata_ptr _metadata;
    stochastic& _stochastic_instance;

public:
    //region Constructor & Destructor

    inline explicit kpoint_crossover(kpoint_crossover_metadata_ptr metadata, stochastic& stochastic_instance) :
        _metadata{metadata}, _stochastic_instance{stochastic_instance}, crossover_internal{metadata} {}

    //endregion

private:
    [[nodiscard]] std::vector<int> _get_cut_points(size_t chromosome_len) const;

protected:
    [[nodiscard]] std::shared_ptr<chromosome> invoke(const std::shared_ptr<const vector_chromosome>& x, const std::shared_ptr<const vector_chromosome>& y) const override;
};



#endif /* _KPOINT_CROSSOVER_H_ */
