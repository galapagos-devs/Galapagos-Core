#ifndef _GALAPAGOS_VECTOR_CHROMOSOME_H_
#define _GALAPAGOS_VECTOR_CHROMOSOME_H_

#include "../API/chromosome.h"
#include "../API/galapagos_metadata.h"

#include "chromosome_internal.h"

struct vector_chromosome_metadata : chromosome_metadata {
    uint norm_rank;
    uint size;
};

class vector_chromosome : chromosome_internal<vector_chromosome> {
private:
    uint _norm_rank; // k-value to be used with the k-norm defined in get_distance
    uint _size;

    double* _genes;

protected:
    double get_distance(vector_chromosome* other) override;

public:
    //region Constructor & Destructor

    explicit vector_chromosome(vector_chromosome_metadata* metadata);
    ~vector_chromosome() override;

    //endregion

    //region Indexing

    virtual double get_gene(uint index) = 0;
    virtual double* get_gene_slice(uint start_index, uint end_index) = 0;
    virtual double* get_gene_slice(uint start_index, uint end_index, uint step_size) = 0;

    //endregion

    //region Math Operations

    virtual vector_chromosome* add (vector_chromosome* other) = 0;
    virtual vector_chromosome* subtract (vector_chromosome* other) = 0;
    virtual vector_chromosome* multiply(double scalar) = 0;

    virtual vector_chromosome* cross (vector_chromosome* other) = 0;
    virtual vector_chromosome* dot (vector_chromosome* other) = 0;

    //endregion

};

#endif /* _GALAPAGOS_VECTOR_CHROMOSOME_H_ */
