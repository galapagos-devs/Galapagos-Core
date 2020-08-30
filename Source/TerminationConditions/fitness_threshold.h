#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>
#include <memory>

#include "../API/galapagos.h"
#include "../API/termination_condition.h"

struct fitness_threshold_metadata : termination_condition_metadata, galapagos_metadata<fitness_threshold_metadata> {
    const size_t fitness_threshold;

    explicit fitness_threshold_metadata(const size_t fitness_threshold) : fitness_threshold{fitness_threshold} {}
};

class fitness_threshold : public termination_condition {
private:
    const fitness_threshold_metadata& _metadata;

public:
    explicit fitness_threshold(const fitness_threshold_metadata& metadata) :
        _metadata{metadata} {}

    [[nodiscard]] bool invoke(const std::shared_ptr<const population>& population) const override;
};

#endif /* _FITNESS_THRESHOLD_H_ */
