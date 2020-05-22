#ifndef _GALAPAGOS_VECTOR_CHROMOSOME_H_
#define _GALAPAGOS_VECTOR_CHROMOSOME_H_

#include "../../API/galapagos.h"
#include "../../API/galapagos_metadata.h"
#include "../../API/chromosome.h"
#include "../../API/stochastic.h"

struct vector_chromosome_metadata : chromosome_metadata {
    const uint32_t norm_rank;
    const size_t size;
    const double gene_infimum;
    const double gene_supremum;

    vector_chromosome_metadata(
            std::string name,
            const double crossover_rate, const std::vector<const crossover_metadata_t*> crossover_metadata,
            const double mutation_rate, const std::vector<const mutation_metadata_t*> mutation_metadata,
            const uint32_t norm_rank, const size_t size, const double gene_infimum, const double gene_supremum) :
                chromosome_metadata{name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata},
                norm_rank{norm_rank}, size{size}, gene_infimum{gene_infimum}, gene_supremum{gene_supremum} {}
};

class vector_chromosome : public chromosome {
private:
    stochastic* _stochastic_instance;

    uint32_t _norm_rank; // k-value to be used with the k-norm defined in get_distance
    size_t _size;
    double _gene_infimum; // lowest possible value any gene will ever take
    double _gene_supremum; // greatest possible value any gene will ever take

    double* _genes;

// base class method
protected:


public:
    //region Constructor & Destructor

    explicit vector_chromosome(const vector_chromosome_metadata* metadata, stochastic* stochastic_instance);
    explicit vector_chromosome(vector_chromosome* other);
    ~vector_chromosome() override;

    //endregion

    // region Inherited Methods

    double get_distance(chromosome* other) override;

    // endregion

    //region Attributes

    virtual size_t num_genes();

    virtual double gene_inf();  // _gene_infimum getter
    virtual double gene_sup(); // _gene_supremum getter

    //endregion

    //region Getters & Setters

    virtual void set_gene(size_t index, double gene);
    virtual void set_gene_slice(size_t start_index, size_t end_index, double* genes);

    virtual double get_gene(size_t index);
    virtual double* get_gene_slice(size_t start_index, size_t end_index);
    virtual double* get_gene_slice(size_t start_index, size_t end_index, size_t step_size);

    //endregion

    //region Math Operations

    virtual double norm();

    virtual vector_chromosome* add(vector_chromosome* other);
    virtual vector_chromosome* subtract(vector_chromosome* other);
    virtual vector_chromosome* multiply(double scalar);

    virtual double dot(vector_chromosome* other);
    virtual vector_chromosome* cross(vector_chromosome** others, size_t num_chromosomes);

    //endregion

};

vector_chromosome* gc_get_vector_chromosome(creature* creature, const std::string& name);

#endif /* _GALAPAGOS_VECTOR_CHROMOSOME_H_ */
