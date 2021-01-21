#ifndef _VECTOR_CHROMOSOME_
#define _VECTOR_CHROMOSOME_

#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "API/vector_chromosome.h"

//region Constructor & Destructor

vector_chromosome::vector_chromosome(vector_chromosome_metadata_ptr metadata, stochastic& stochastic_instance) :
    _metadata{metadata}, _stochastic_instance{stochastic_instance} {
    _this = std::shared_ptr<vector_chromosome>(this, [](vector_chromosome*){});
    for(size_t i = 0; i < _metadata->size; ++i)
        _genes.push_back(_stochastic_instance.rand_double(_metadata->gene_infimum, _metadata->gene_supremum));
}

vector_chromosome::vector_chromosome(const std::shared_ptr<const vector_chromosome>& other) :
    _metadata{other->_metadata}, _stochastic_instance{other->_stochastic_instance} {
    _this = std::shared_ptr<vector_chromosome>(this, [](vector_chromosome*){});
    for(size_t i = 0; i < _metadata->size; ++i)
        _genes.push_back(other->get_gene(i));

}

//endregion

//region Inherited Methods

double vector_chromosome::get_distance(const std::shared_ptr<const chromosome>& other) const {
    const auto downcast = std::dynamic_pointer_cast<const vector_chromosome>(other);
    if(downcast == nullptr)
        throw std::runtime_error("get_distance mismatched types");

    double norm = 0;
    for(size_t i = 0; i < _metadata->size; ++i)
        norm += pow(get_gene(i) - downcast->get_gene(i), _metadata->norm_rank);

    norm = pow(norm, 1.0 / _metadata->norm_rank);
    return norm;
}

//endregion

//region Attributes

size_t vector_chromosome::num_genes() const {
    return _metadata->size;
}

double vector_chromosome::gene_inf() const {
    return _metadata->gene_infimum;
}

double vector_chromosome::gene_sup() const {
    return _metadata->gene_supremum;
}

//endregion

//region Getters & Setters

void vector_chromosome::set_gene(size_t index, double gene) {
    double clamped_gene = std::clamp(gene, _metadata->gene_infimum, _metadata->gene_supremum);
    _genes[index] = clamped_gene;
}

void vector_chromosome::set_gene_slice(size_t start_index, size_t end_index, std::vector<double> genes) {
    size_t i = 0;
    for(size_t slice_index = start_index; slice_index < end_index; slice_index++)
        set_gene(slice_index, genes[i++]);
}

double vector_chromosome::get_gene(size_t index) const {
    return _genes[index];
}

std::vector<double> vector_chromosome::get_gene_slice(size_t start_index, size_t end_index) const {
    return get_gene_slice(start_index, end_index, 1);
}

std::vector<double> vector_chromosome::get_gene_slice(size_t start_index, size_t end_index, size_t step_size) const {
    size_t slice_size = end_index - start_index;

    std::vector<double> gene_slice;
    gene_slice.resize(slice_size);
    size_t gene_index = 0;

    for(size_t slice_index = start_index; slice_index < end_index; slice_index += step_size) {
        gene_slice[gene_index] = get_gene(gene_index);
        gene_index++;
    }

    return gene_slice;
}

//endregion

//region Math Operations

double vector_chromosome::norm() const {
    double radical = 0;
    for (size_t i = 0; i < _metadata->size; i++)
        radical += std::abs(std::pow(_genes[i], _metadata->norm_rank));  // |x^y| absolute value of x raised to the y

    return std::pow(radical, 1 / _metadata->norm_rank);
}

std::shared_ptr<vector_chromosome> vector_chromosome::add(const std::shared_ptr<const vector_chromosome>& other) const {
    auto new_chromosome = std::make_shared<vector_chromosome>(_this);
    for(size_t i = 0; i < _metadata->size; ++i)
        new_chromosome->_genes[i] = get_gene(i) + other->get_gene(i);
    return new_chromosome;
}

std::shared_ptr<vector_chromosome> vector_chromosome::subtract(const std::shared_ptr<const vector_chromosome>& other) const {
    auto new_chromosome = std::make_shared<vector_chromosome>(_this);
    for(size_t i = 0; i < _metadata->size; ++i)
        new_chromosome->_genes[i] = get_gene(i) - other->get_gene(i);
    return new_chromosome;
}

std::shared_ptr<vector_chromosome> vector_chromosome::multiply(double scalar) const {
    auto new_chromosome = std::make_shared<vector_chromosome>(_this);
    for(size_t i = 0; i < _metadata->size; ++i)
        new_chromosome->_genes[i] = scalar * get_gene(i);
    return new_chromosome;
}

double vector_chromosome::dot(const std::shared_ptr<const vector_chromosome>& other) const {
    double dot_product = 0;
    for(size_t i = 0; i < _metadata->size; ++i)
        dot_product += get_gene(i) * other->get_gene(i);
    return dot_product;
}

std::shared_ptr<vector_chromosome> vector_chromosome::cross(const std::vector<std::shared_ptr<vector_chromosome>>& others, size_t num_chromosomes) const {
    throw std::runtime_error("vector_chromosome.cross not implemented");
}

//endregion

// TODO: better way to expose this with swig
std::shared_ptr<vector_chromosome> gc_get_vector_chromosome(std::shared_ptr<creature> creature, const std::string& name) {
    return creature->get_chromosome<vector_chromosome>(name);
}

#endif /* _VECTOR_CHROMOSOME_ */

