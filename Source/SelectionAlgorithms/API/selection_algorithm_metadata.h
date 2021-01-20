#ifndef _SELECTION_ALGORITHM_METADATA_H_
#define _SELECTION_ALGORITHM_METADATA_H_

#include "../../API/galapagos_metadata.h"

struct tournament_selection_metadata : selection_algorithm_metadata {
    const size_t tournament_size;

    explicit tournament_selection_metadata(
            size_t tournament_size) :
                tournament_size{tournament_size} {}
};

#endif /* _SELECTION_ALGORITHM_METADATA_H_ */
