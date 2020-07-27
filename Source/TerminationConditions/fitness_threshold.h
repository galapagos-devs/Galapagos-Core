#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>
#include <memory>

#include "../API/galapagos.h"
#include "../API/termination_condition.h"

struct fitness_threshold_metadata : termination_condition_metadata {
    const size_t fitness_threshold;

    explicit fitness_threshold_metadata(const size_t fitness_threshold) : fitness_threshold{fitness_threshold} {}

    inline std::shared_ptr<const termination_condition_metadata> copy() const override {
        std::shared_ptr<const termination_condition_metadata> ptr(new fitness_threshold_metadata(
                this->fitness_threshold
        ));
        return ptr;
    }
};

class fitness_threshold : public termination_condition {
private:
    const fitness_threshold_metadata& _metadata;

public:
    explicit fitness_threshold(const fitness_threshold_metadata& metadata) :
        _metadata{metadata} {}

    bool invoke(const std::shared_ptr<const population> population) const override;
};

#endif /* _FITNESS_THRESHOLD_H_ */
