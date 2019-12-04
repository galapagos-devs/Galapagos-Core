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

vector_chromosome::vector_chromosome(vector_chromosome* other) {
    _norm_rank = other->_norm_rank;
    _size = other->_size;

    _genes = new double[_size];
    for(size_t i = 0; i < _size; ++i)
        _genes[i] = other->get_gene(i);

}

vector_chromosome::~vector_chromosome() {
    delete[] _genes;
}

//endregion

//region Inherited Methods

double vector_chromosome::get_distance(vector_chromosome* other) {
    double norm = 0;
    for(size_t i = 0; i < _size; ++i)
        norm += pow(get_gene(i) - other->get_gene(i), _norm_rank);

    norm = pow(norm, 1.0/_norm_rank);
    return norm;
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
        gene_slice[gene_index] = get_gene(gene_index);
        gene_index++;
    }

    return gene_slice;
}

//endregion

//region Math Operations

vector_chromosome* vector_chromosome::add(vector_chromosome* other) {
    auto* new_chromosome = new vector_chromosome(this);
    for(size_t i = 0; i < _size; ++i)
        new_chromosome->_genes[i] = get_gene(i) + other->get_gene(i);

    return new_chromosome;
}

vector_chromosome* vector_chromosome::subtract(vector_chromosome *other) {
    auto* new_chromosome = new vector_chromosome(this);
    for(size_t i = 0; i < _size; ++i)
        new_chromosome->_genes[i] = get_gene(i) - other->get_gene(i);

    return new_chromosome;
}

vector_chromosome* vector_chromosome::multiply(double scalar) {
    auto* new_chromosome = new vector_chromosome(this);
    for(size_t i = 0; i < _size; ++i)
        new_chromosome->_genes[i] = scalar * get_gene(i);

    return new_chromosome;
}

double vector_chromosome::dot(vector_chromosome *other) {
    double dot_product = 0;
    for(size_t i = 0; i < _size; ++i)
        dot_product += get_gene(i) * other->get_gene(i);
    return dot_product;
}

vector_chromosome* vector_chromosome::cross(vector_chromosome** others, size_t num_chromosomes) {

}

//endregion


#endif /* _VECTOR_CHROMOSOME_ */

