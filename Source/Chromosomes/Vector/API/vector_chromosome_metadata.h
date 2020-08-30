#ifndef _VECTOR_CHROMOSOME_METADATA_H_
#define _VECTOR_CHROMOSOME_METADATA_H_

#include "../../../API/galapagos_metadata.h"

struct kpoint_crossover_metadata : crossover_metadata, galapagos_metadata<kpoint_crossover_metadata> {
    const size_t cut_points;

    kpoint_crossover_metadata(
            double weight, size_t cut_points) :
            crossover_metadata{weight},
            cut_points{cut_points} {}
};

struct gaussian_mutation_metadata : mutation_metadata, galapagos_metadata<gaussian_mutation_metadata> {
    const double mean;
    const double standard_deviation;

    gaussian_mutation_metadata(
            double weight, double mean, double standard_deviation) :
            mutation_metadata{weight},
            mean{mean}, standard_deviation{standard_deviation} {}
};

struct randomization_mutation_metadata : mutation_metadata, galapagos_metadata<randomization_mutation_metadata> {
    explicit randomization_mutation_metadata(
            double weight) :
            mutation_metadata{weight} {}
};

struct vector_chromosome_metadata : chromosome_metadata, galapagos_metadata<vector_chromosome_metadata> {
    const uint32_t norm_rank; // k-value to be used with the k-norm defined in get_distance
    const size_t size;
    const double gene_infimum; // lowest possible value any gene will ever take
    const double gene_supremum; // greatest possible value any gene will ever take

    vector_chromosome_metadata(
            std::string name,
            double crossover_rate, std::vector<std::shared_ptr<const crossover_metadata_t>> crossover_metadata,
            double mutation_rate, std::vector<std::shared_ptr<const mutation_metadata_t>> mutation_metadata,
            uint32_t norm_rank, size_t size, double gene_infimum, double gene_supremum) :
            chromosome_metadata{name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata},
            norm_rank{norm_rank}, size{size}, gene_infimum{gene_infimum}, gene_supremum{gene_supremum} {}
};

#endif /* _VECTOR_CHROMOSOME_METADATA_H_ */
