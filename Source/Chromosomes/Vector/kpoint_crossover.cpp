#ifndef _VECTOR_CHROMOSOME_
#define _VECTOR_CHROMOSOME_

#include <vector>
#include <algorithm>

#include "kpoint_crossover.h"

auto kpoint_crossover::_get_cut_points(size_t chromosome_len) const -> std::vector<int> {
    std::vector<int> cuts(_metadata->cut_points);

    // Construct list of unique cuts
    size_t i = 0;
    while (i < _metadata->cut_points) {
        // we can't have a cut at the first or last index
        int proposed_cut = _stochastic_instance.rand_int(1, chromosome_len);

        // Check if proposed_cut is contained in cuts
        if (std::find(cuts.begin(), cuts.end(), proposed_cut) == cuts.end())
            cuts[i++] = proposed_cut;
    }
    std::sort(cuts.begin(), cuts.end());

    return cuts;
}

auto kpoint_crossover::invoke(const std::shared_ptr<const vector_chromosome>& x, const std::shared_ptr<const vector_chromosome>& y) const -> std::shared_ptr<chromosome> {
    size_t len = x->num_genes();
    std::vector<int> cuts(_metadata->cut_points);
    cuts = _get_cut_points(len);

    // Extract child DNA
    int cut_index = 0;
    std::shared_ptr<const vector_chromosome> active_parent = x;
    std::shared_ptr<const vector_chromosome> dormant_parent = y;
    std::shared_ptr<const vector_chromosome> buffer;

    auto child = std::make_shared<vector_chromosome>(active_parent);
    for (size_t i = 0; i < len; i++) {
        if (cut_index < _metadata->cut_points && i == cuts[cut_index]) {
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