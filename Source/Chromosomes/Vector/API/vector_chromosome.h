#ifndef _VECTOR_CHROMOSOME_H_
#define _VECTOR_CHROMOSOME_H_

#include <vector>
#include <functional>
#include <memory>

#include "../../../API/galapagos.h"
#include "../../../API/chromosome.h"
#include "../../../API/stochastic.h"

#include "vector_chromosome_metadata.h"

class vector_chromosome : public chromosome {
private:
    std::shared_ptr<vector_chromosome> _this;

    vector_chromosome_metadata_ptr _metadata;
    stochastic& _stochastic_instance;
    std::vector<double> _genes;

public:
    //region Constructor & Destructor

    explicit vector_chromosome(vector_chromosome_metadata_ptr metadata, stochastic& stochastic_instance);
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

std::shared_ptr<vector_chromosome> gc_get_vector_chromosome(const std::shared_ptr<creature>& creature, const std::string& name);

#endif /* _VECTOR_CHROMOSOME_H_ */
