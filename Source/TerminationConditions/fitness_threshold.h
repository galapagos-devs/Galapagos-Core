#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>

#include "../API/galapagos.h"
#include "../API/termination_condition.h"

struct fitness_threshold_metadata : selection_algorithm_metadata {
    size_t fitness_threshold;
};

class fitness_threshold : public termination_condition {
private:
    size_t _fitness_threshold;

public:
    explicit fitness_threshold(fitness_threshold_metadata* metadata);

    ~fitness_threshold() override;

    bool operator()(population* population) override;
    bool invoke(population* population) override;
};

#endif /* _FITNESS_THRESHOLD_H_ */
