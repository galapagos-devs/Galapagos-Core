#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>

#include "../API/galapagos.h"
#include "../API/termination_condition.h"

struct fitness_threshold_metadata : termination_condition_metadata {
    const size_t fitness_threshold;

    explicit fitness_threshold_metadata(const size_t fitness_threshold) : fitness_threshold{fitness_threshold} {}
};

class fitness_threshold : public termination_condition {
private:
    const fitness_threshold_metadata* const _metadata;

public:
    explicit fitness_threshold(const fitness_threshold_metadata* const metadata) : _metadata{metadata} {}
    ~fitness_threshold() override = default;

    bool invoke(const population* const population) const override;
};

#endif /* _FITNESS_THRESHOLD_H_ */
