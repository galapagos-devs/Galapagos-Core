#ifndef _VECTOR_CHROMOSOME_
#define _VECTOR_CHROMOSOME_

#include <vector>

#include "kpoint_crossover.h"

//region Constructor & Destructor

kpoint_crossover::kpoint_crossover(stochastic* stochastic_instance, kpoint_crossover_metadata* metadata) {
    _stochastic_instance = stochastic_instance;
    _cut_points = metadata->cut_points;
}

kpoint_crossover::kpoint_crossover(kpoint_crossover *other) {
    _stochastic_instance = other->_stochastic_instance;
    _cut_points = other->_cut_points;
}

kpoint_crossover::~kpoint_crossover() = default;

//endregion


std::vector<int> kpoint_crossover::_get_cut_points(size_t chromosome_len) {
    std::vector<int> cuts(_cut_points);

    // Construct list of unique cuts
    size_t i = 0;
    while (i < _cut_points) {
        // we can't have a cut at the first or last index
        int proposed_cut = _stochastic_instance->rand_int(1, chromosome_len-2);

        // Check if proposed_cut is contained in cuts
        if (std::find(cuts.begin(), cuts.end(), proposed_cut) == cuts.end()) {
            cuts[i] = proposed_cut;
            i++;
        }
    }
    std::sort(cuts.begin(), cuts.end());

    return cuts;
}

chromosome* kpoint_crossover::invoke(vector_chromosome* x, vector_chromosome* y) {
    size_t len = x->num_genes();
    std::vector<int> cuts(_cut_points);
    cuts = _get_cut_points(len);

    // Extract child DNA
    int cut_index = 0;
    vector_chromosome* active_parent = x;
    vector_chromosome* dormant_parent = y;
    vector_chromosome* buffer;

    auto* child = new vector_chromosome(active_parent);
    for (size_t i = 0; i < len; i++) {
        if (i == cuts[cut_index]) {
            cut_index++;
            buffer = active_parent;
            active_parent = dormant_parent;
            dormant_parent = buffer;
        }
        child->set_gene(i, active_parent->get_gene(i));
    }

    return child;
}

#endif /* _VECTOR_CHROMOSOME_ */