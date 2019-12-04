#ifndef _GALAPAGOS_VECTOR_CHROMOSOME_H_
#define _GALAPAGOS_VECTOR_CHROMOSOME_H_

#include "../API/chromosome.h"
#include "../API/galapagos_metadata.h"

#include "chromosome_internal.h"

struct vector_chromosome_metadata : chromosome_metadata {
    uint norm_rank;
    size_t size;
    double gene_infimun;
    double gene_supremum;
};

class vector_chromosome : public chromosome_internal<vector_chromosome> {
private:
    uint _norm_rank; // k-value to be used with the k-norm defined in get_distance
    size_t _size;
    double _gene_infimun; // lowest possible value any gene will ever take
    double _gene_supremum; // greatest possible value any gene will ever take

    double* _genes;

protected:
    double get_distance(vector_chromosome* other) override;

public:
    //region Constructor & Destructor

    explicit vector_chromosome(vector_chromosome_metadata* metadata);
    explicit vector_chromosome(vector_chromosome* other);
    ~vector_chromosome() override;

    //endregion

    //region Indexing

    size_t num_genes();

    void set_gene(size_t index, double value);
    double get_gene(size_t index);
    double* get_gene_slice(size_t start_index, size_t end_index);
    double* get_gene_slice(size_t start_index, size_t end_index, size_t step_size);

    //endregion

    //region Math Operations

    double norm();

    vector_chromosome* add(vector_chromosome* other);
    vector_chromosome* subtract(vector_chromosome* other);
    vector_chromosome* multiply(double scalar);

    double dot(vector_chromosome* other);
    vector_chromosome* cross(vector_chromosome** others, size_t num_chromosomes);

    double gene_inf();  // _gene_infimum getter
    double gene_sup(); // _gene_supremum getter

    //endregion

};

#endif /* _GALAPAGOS_VECTOR_CHROMOSOME_H_ */
