#ifndef _GALAPAGOS_KPOINT_CROSSOVER_H_
#define _GALAPAGOS_KPOINT_CROSSOVER_H_

#include "../API/crossover.h"
#include "../API/galapagos_metadata.h"
#include "../API/stochastic.h"

#include "../Chromosomes/vector_chromosome.h"

#include "crossover_internal.h"

struct kpoint_crossover_metadata : crossover_metadata {
    size_t cut_points;
};

class kpoint_crossover : public crossover_internal<vector_chromosome> {
private:
    stochastic* _stochastic_instance;
    size_t _cut_points;
public:
    //region Constructor & Destructor

    explicit kpoint_crossover(stochastic* stochastic_instance, kpoint_crossover_metadata* metadata);
    explicit kpoint_crossover(kpoint_crossover* other);
    ~kpoint_crossover() override ;

    //endregion

    vector_chromosome* invoke(vector_chromosome* x, vector_chromosome* y) override;
};



#endif /* _GALAPAGOS_KPOINT_CROSSOVER_H_ */
