#include <cstring>
#include <vector>

#include "tournament_selection.h"

// Consideres tournament_size creates from the population and returns the most fit creature.
creature* tournament_selection::invoke(const population* const population) const {
    size_t population_size = population->get_size();
    std::vector<bool> in_tournament(population_size, false);

    // Run the tournament.
    size_t i = 0;
    creature *champion = nullptr;
    while (i < _metadata->tournament_size) {
        size_t proposed_member_index = _stochastic_instance->rand_int(population_size);

        if (!in_tournament[proposed_member_index]) {
            in_tournament[proposed_member_index] = true;

            creature *challenger = population->get_creature(proposed_member_index);
            if ((champion == nullptr) || (challenger->get_fitness() > champion->get_fitness()))
                champion = challenger;

            i++;
        }
    }

    return champion;
}
