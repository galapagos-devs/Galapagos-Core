#ifndef _VECTOR_CHROMOSOME_H_
#define _VECTOR_CHROMOSOME_H_

#include <vector>
#include <functional>
#include <memory>

#include "../../API/galapagos.h"
#include "../../API/galapagos_metadata.h"
#include "../../API/chromosome.h"
#include "../../API/stochastic.h"

struct vector_chromosome_metadata : chromosome_metadata, galapagos_metadata<vector_chromosome_metadata> {
    const uint32_t norm_rank; // k-value to be used with the k-norm defined in get_distance
    const size_t size;
    const double gene_infimum; // lowest possible value any gene will ever take
    const double gene_supremum; // greatest possible value any gene will ever take

    vector_chromosome_metadata(
            const std::string& name,
            const double crossover_rate, const std::vector<std::shared_ptr<const crossover_metadata_t>>& crossover_metadata,
            const double mutation_rate, const std::vector<std::shared_ptr<const mutation_metadata_t>>& mutation_metadata,
            const uint32_t norm_rank, const size_t size, const double gene_infimum, const double gene_supremum) :
                chromosome_metadata{name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata},
                norm_rank{norm_rank}, size{size}, gene_infimum{gene_infimum}, gene_supremum{gene_supremum} {}
};

class vector_chromosome : public chromosome {
private:
    std::shared_ptr<vector_chromosome> _this;

    const vector_chromosome_metadata& _metadata;
    stochastic& _stochastic_instance;
    std::vector<double> _genes;

public:
    //region Constructor & Destructor

    explicit vector_chromosome(const vector_chromosome_metadata& metadata, stochastic& stochastic_instance);
    explicit vector_chromosome(const std::shared_ptr<const vector_chromosome>& other);

    //endregion

    // region Inherited Methods

    double get_distance(const std::shared_ptr<const chromosome>& other) const override;

    // endregion

    //region Attributes

    virtual size_t num_genes() const;

    virtual double gene_inf() const;  // _gene_infimum getter
    virtual double gene_sup() const; // _gene_supremum getter

    //endregion

    //region Getters & Setters

    virtual void set_gene(size_t index, double gene);
    virtual void set_gene_slice(size_t start_index, size_t end_index, std::vector<double> genes);

    virtual double get_gene(size_t index) const;
    virtual std::vector<double> get_gene_slice(size_t start_index, size_t end_index) const;
    virtual std::vector<double> get_gene_slice(size_t start_index, size_t end_index, size_t step_size) const;

    //endregion

    //region Math Operations

    virtual double norm() const;

    virtual std::shared_ptr<vector_chromosome> add(const std::shared_ptr<const vector_chromosome>& other) const;
    virtual std::shared_ptr<vector_chromosome> subtract(const std::shared_ptr<const vector_chromosome>& other) const;
    virtual std::shared_ptr<vector_chromosome> multiply(double scalar) const;

    virtual double dot(const std::shared_ptr<const vector_chromosome>& other) const;
    virtual std::shared_ptr<vector_chromosome> cross(const std::vector<std::shared_ptr<vector_chromosome>>& others, size_t num_chromosomes) const;

    //endregion
};

std::shared_ptr<vector_chromosome> gc_get_vector_chromosome(std::shared_ptr<creature> creature, const std::string& name);

#endif /* _VECTOR_CHROMOSOME_H_ */
