#ifndef _VECTOR_CHROMOSOME_
#define _VECTOR_CHROMOSOME_

#include <cmath>

#include "vector_chromosome.h"


//region Constructor & Destructor

vector_chromosome::vector_chromosome(vector_chromosome_metadata *metadata) {
    _norm_rank = metadata->norm_rank;
    _size = metadata->size;

    _genes = new double[_size];
}

vector_chromosome::~vector_chromosome() {
    delete[] _genes;
}

//endregion

//region Inherited Methods

double vector_chromosome::get_distance(chromosome* other) {
//    double norm = 0;
//    for(size_t i = 0; i < _size; ++i) {
//
//    }
}

//endregion

//region Indexing

double vector_chromosome::get_gene(uint index) {
    return _genes[index];
}

double* vector_chromosome::get_gene_slice(uint start_index, uint end_index) {
    return get_gene_slice(start_index, end_index, 1);
}

double* vector_chromosome::get_gene_slice(uint start_index, uint end_index, uint step_size) {
    size_t slice_size = end_index - start_index;

    double* gene_slice;
    gene_slice = new double[slice_size];
    size_t gene_index = 0;

    for(size_t slice_index = start_index; slice_index < end_index; slice_index += step_size) {
        gene_slice[gene_index] = _genes[slice_index];
        gene_index++;
    }

    return gene_slice;
}

//endregion

//region Math Operations

vector_chromosome* vector_chromosome::add(vector_chromosome *other) {

}

vector_chromosome* vector_chromosome::subtract(vector_chromosome *other) {

}

vector_chromosome* vector_chromosome::multiply(double scalar) {

}

vector_chromosome* vector_chromosome::dot(vector_chromosome *other) {

}

vector_chromosome* vector_chromosome::cross(vector_chromosome *other) {

}

//endregion


#endif /* _VECTOR_CHROMOSOME_ */

