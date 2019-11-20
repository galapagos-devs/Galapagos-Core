//
// Created by Shane on 11/13/2019.
//

#ifndef _GALAPAGOS_VECTOR_CHROMOSOME_H_
#define _GALAPAGOS_VECTOR_CHROMOSOME_H_

#include "../API/chromosome.h"
#include "../API/galapagos_metadata.h"

struct vector_chromosome_metadata : chromosome_metadata {
    uint norm_rank;
    size_t size;
};

class vector_chromosome : chromosome_internal<vector_chromosome> {
private:
    uint _norm_rank; // k-value to be used with the k-norm defined in get_distance
    size_t _size;

protected:
    double get_distance(vector_chromosome* other) override;

public:
    explicit vector_chromosome(vector_chromosome_metadata* metadata);

    ~vector_chromosome() override;

    //region Indexing

    virtual double get_gene(size_t index) = 0;
    virtual double* get_slice(size_t end_index) = 0;
    virtual double* get_slice(size_t start_index, size_t end_index) = 0;
    virtual double* get_slice(size_t start_index, size_t end_index, size_t step_size) = 0;

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
