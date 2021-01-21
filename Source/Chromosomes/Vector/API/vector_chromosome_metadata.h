#ifndef _VECTOR_CHROMOSOME_METADATA_H_
#define _VECTOR_CHROMOSOME_METADATA_H_

#include "../../../API/galapagos_metadata.h"

struct kpoint_crossover_metadata : crossover_metadata {
    const size_t cut_points;

    kpoint_crossover_metadata(
            double weight, size_t cut_points) :
                crossover_metadata{weight},
                cut_points{cut_points} {}
};
MAKE_METADATA_POINTER_ALIAS(kpoint_crossover_metadata);

struct gaussian_mutation_metadata : mutation_metadata {
    const double mean;
    const double standard_deviation;

    gaussian_mutation_metadata(
            double weight, double mean, double standard_deviation) :
                mutation_metadata{weight},
                mean{mean}, standard_deviation{standard_deviation} {}
};
MAKE_METADATA_POINTER_ALIAS(gaussian_mutation_metadata);

struct randomization_mutation_metadata : mutation_metadata {
    explicit randomization_mutation_metadata(
            double weight) :
                mutation_metadata{weight} {}
};
MAKE_METADATA_POINTER_ALIAS(randomization_mutation_metadata);

struct vector_chromosome_metadata : chromosome_metadata {
    const uint32_t norm_rank; // k-value to be used with the k-norm defined in get_distance
    const size_t size;
    const double gene_infimum; // lowest possible value any gene will ever take
    const double gene_supremum; // greatest possible value any gene will ever take

    vector_chromosome_metadata(
            std::string name,
            double crossover_rate, std::vector<crossover_metadata_ptr> crossover_metadata,
            double mutation_rate, std::vector<mutation_metadata_ptr> mutation_metadata,
            uint32_t norm_rank, size_t size, double gene_infimum, double gene_supremum) :
                chromosome_metadata{name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata},
                norm_rank{norm_rank}, size{size}, gene_infimum{gene_infimum}, gene_supremum{gene_supremum} {}
};
MAKE_METADATA_POINTER_ALIAS(vector_chromosome_metadata);

#endif /* _VECTOR_CHROMOSOME_METADATA_H_ */
