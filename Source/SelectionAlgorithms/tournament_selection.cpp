#include <cstring>

#include "tournament_selection.h"

// Consideres tournament_size creates from the population and returns the most fit creature.
creature* tournament_selection::invoke(const population* const population) const {
    size_t population_size = population->get_size();

    bool* in_tournament = new bool[population_size];
    memset(in_tournament, false, sizeof(false) * population_size);  // initalize in_tournament to all false.

    // Run the tournament.
    size_t i = 0;
    creature* champion = nullptr;
    while (i < _metadata->tournament_size){
        size_t proposed_member_index = _stochastic_instance->rand_int(population_size);

        if (!in_tournament[proposed_member_index]) {
            in_tournament[proposed_member_index] = true;

            creature* challenger = population->get_creature(proposed_member_index);
            if ( (champion == nullptr) || (challenger->get_fitness() > champion->get_fitness()) )
                champion = challenger;

            i++;
        }
    }

    delete[] in_tournament;

  return champion;
}
