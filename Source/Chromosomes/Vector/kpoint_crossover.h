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
    stochastic* _stochastic_instance;
    size_t _cut_points;
public:
    //region Constructor & Destructor

    explicit kpoint_crossover(const kpoint_crossover_metadata* metadata, stochastic* stochastic_instance);
    ~kpoint_crossover();

    //endregion

private:
    std::vector<int> _get_cut_points(size_t chromosome_len);

protected:
    chromosome* invoke(vector_chromosome* x, vector_chromosome* y) override;
};



#endif /* _KPOINT_CROSSOVER_H_ */
