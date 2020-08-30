#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>
#include <memory>

#include "../API/galapagos.h"
#include "../API/termination_condition.h"

#include "API/termination_condition_metadata.h"

class fitness_threshold : public termination_condition {
private:
    const fitness_threshold_metadata& _metadata;

public:
    explicit fitness_threshold(const fitness_threshold_metadata& metadata) :
        _metadata{metadata} {}

    [[nodiscard]] bool invoke(const std::shared_ptr<const population>& population) const override;
};

#endif /* _FITNESS_THRESHOLD_H_ */
