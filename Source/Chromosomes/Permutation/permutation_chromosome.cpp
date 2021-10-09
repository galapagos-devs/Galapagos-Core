#include <algorithm>
#include <random> // smelly! what about stochastic?

#include "API/permutation_chromosome.h"

permutation_chromosome::permutation_chromosome(permutation_chromosome_metadata_ptr metadata, stochastic& stochastic_instance) :
        _metadata{metadata}, _stochastic_instance{stochastic_instance} {
    for(size_t i = 0; i < _metadata->size; ++i)
        _genes.push_back(i);

    // should this come from the stochastic class?
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(_genes.begin(), _genes.end(), urng);
}

//region Inherited Methods

// Kendall Tau distance
double merge_sort(std::vector<size_t>& map, std::vector<size_t>& buff, std::vector<size_t>& temp, size_t left, size_t right);
double merge(std::vector<size_t>& map, std::vector<size_t>& buff, std::vector<size_t>& temp, size_t left, size_t mid, size_t right);
double permutation_chromosome::get_distance(const std::shared_ptr<const chromosome>& other) const {
    const auto downcast = std::dynamic_pointer_cast<const permutation_chromosome>(other);
    if(downcast == nullptr)
        throw std::runtime_error("get_distance mismatched types");

    std::vector<size_t> map(_metadata->size);
    for(size_t i = 0; i < _metadata->size; i++)
        map[_genes[i]] = i;

    std::vector<size_t> buff(_metadata->size);
    std::vector<size_t> temp(_metadata->size);

    double distance = merge_sort(map, buff, temp, 0, _metadata->size - 1);
    return distance;
}

double merge_sort(std::vector<size_t>& map, std::vector<size_t>& buff, std::vector<size_t>& temp,
                  size_t left, size_t right) {
    if(right > left) {
        size_t mid = (right + left) / 2;
        double inv_count =
                merge_sort(map, buff, temp, left, mid) +
                merge_sort(map, buff, temp, mid + 1, right) +
                merge(map, buff, temp, left, mid + 1, right);

        return inv_count;
    }

    return 0;
}

double merge(std::vector<size_t>& map, std::vector<size_t>& buff, std::vector<size_t>& temp,
             size_t left, size_t mid, size_t right) {
    size_t inv_count = 0;

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    while((i <= mid - 1) && (j <= right)) {
        if(map[buff[i]] <= map[buff[j]]) {
            temp[k++] = buff[i++];
        }
        else {
            temp[k++] = buff[j++];
            inv_count += mid - i;
        }
    }

    while(i <= mid - 1)
        temp[k++] = buff[i++];

    while(j <= right)
        temp[k++] = buff[j++];

    for(i = left; i <= right; i++)
        buff[i] = temp[i];

    return inv_count;
}

//endregion

//region Attributes

size_t permutation_chromosome::num_genes() const {
    return _metadata->size;
}

//endregion

//region Getters & Setters

size_t permutation_chromosome::get_gene(size_t index) const {
    return _genes[index];
}

//endregion