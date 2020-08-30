#ifndef _TERMINATION_CONDITION_METADATA_H_
#define _TERMINATION_CONDITION_METADATA_H_

#include "../../API/galapagos_metadata.h"

struct fitness_threshold_metadata : termination_condition_metadata, galapagos_metadata<fitness_threshold_metadata> {
    const size_t fitness_threshold;

    explicit fitness_threshold_metadata(
            size_t fitness_threshold) :
                fitness_threshold{fitness_threshold} {}
};

#endif /* _TERMINATION_CONDITION_METADATA_H_ */
