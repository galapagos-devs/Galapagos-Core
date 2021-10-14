#ifndef _PERMUTATION_CHROMOSOME_METADATA_H_
#define _PERMUTATION_CHROMOSOME_METADATA_H_

#include "../../../API/galapagos_metadata.h"

struct permutation_chromosome_metadata : chromosome_metadata {
    const size_t size;

    permutation_chromosome_metadata(
            std::string name,
            double crossover_rate, std::vector<crossover_metadata_ptr> crossover_metadata,
            double mutation_rate, std::vector<mutation_metadata_ptr> mutation_metadata,
            size_t size) :
            chromosome_metadata{name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata},
            size{size} {}
};
MAKE_METADATA_POINTER_ALIAS(permutation_chromosome_metadata);

#endif /* _GALAPAGOS_PERMUTATION_CHROMOSOME_METADATA_H_ */
