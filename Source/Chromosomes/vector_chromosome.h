//
// Created by Shane on 11/13/2019.
//

#ifndef _GALAPAGOS_VECTOR_CHROMOSOME_H_
#define _GALAPAGOS_VECTOR_CHROMOSOME_H_

#include "../API/galapagos_metadata.h"
#include "chromosome_internal.h"

struct vector_chromosome_metadata : chromosome_metadata {
    uint norm_rank;
    size_t size;
};

class vector_chromosome : public chromosome_internal<vector_chromosome> {
private:
    uint _norm_rank; // k-value to be used with the k-norm defined in get_distance

    double* _genes;

public:
    size_t _size; // This should be public so consumers know the max index

protected:
    double get_distance(vector_chromosome* other) override;

public:
    explicit vector_chromosome(vector_chromosome_metadata* metadata);
    vector_chromosome(vector_chromosome_metadata* metadata, double* seed);

    ~vector_chromosome() override;

    //region Indexing

    double get_gene(size_t index);
    double* get_slice(size_t end_index);
    double* get_slice(size_t start_index, size_t end_index);
    double* get_slice(size_t start_index, size_t end_index, size_t step_size);

    //endregion

    //region Math Operations

    vector_chromosome* add (vector_chromosome* other);
    vector_chromosome* subtract (vector_chromosome* other);
    vector_chromosome* multiply(double scalar);

    vector_chromosome* cross (vector_chromosome* other);
    vector_chromosome* dot (vector_chromosome* other);

    //endregion

};

#endif /* _GALAPAGOS_VECTOR_CHROMOSOME_H_ */
