#ifndef _TOURNAMENT_SELECTION_CPP_
#define _TOURNAMENT_SELECTION_CPP_

#include "selection_algorithm.h"
#include "creature.h"
#include "galapagos.h"
#include "stochastic.h"

class tournament_selection : selection_algorithm {
private:
	size_t _tournament_size;
public:
	tournament_selection(size_t tournament_size) {
		_tournament_size = tournament_size;
	}

	// Consideres tournament_size creates from the population and returns the most fit creature.
	creature* invoke(population* population) override {
		galapagos_session& session = galapagos_session::get_instance();
		stochastic* stochastic = session.stochastic;

		size_t population_size = population->get_size();

		bool* in_tournament = new bool[population_size];
		memset(in_tournament, false, sizeof(false) * population_size);  // initalize in_tournament to all false.

		// Run the tournament.
		size_t i = 0;
		creature* champion = nullptr;
		while (i < _tournament_size){
			size_t proposed_member_index = stochastic->rand_int(population_size);

			if (!in_tournament[proposed_member_index]) {
				in_tournament[proposed_member_index] = true;

				creature* challenger = population->get_creature(proposed_member_index);
				if ( (champion == nullptr) || (challenger->get_fitness() > champion->get_fitness()) )
					champion = challenger;

				i++;
			}
		}

		delete[] in_tournament;
	}
};

#endif /* _TOURNAMENT_SELECTION_CPP_ */