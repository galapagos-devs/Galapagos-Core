#include <cstring>

#include "tournament_selection.h"

tournament_selection::tournament_selection(stochastic* stochastic_instance, tournament_selection_metadata* metadata) {
  _stochastic_instance = stochastic_instance;
  _tournament_size = metadata->tournament_size;
}

tournament_selection::~tournament_selection() {

}

// Consideres tournament_size creates from the population and returns the most fit creature.
creature* tournament_selection::invoke(population* population) {
	size_t population_size = population->get_size();

	bool* in_tournament = new bool[population_size];
	memset(in_tournament, false, sizeof(false) * population_size);  // initalize in_tournament to all false.

	// Run the tournament.
	size_t i = 0;
	creature* champion = nullptr;
	while (i < _tournament_size){
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
