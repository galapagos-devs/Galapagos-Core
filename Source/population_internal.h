#ifndef _POPULATION_INTERNAL_H_
#define _POPULATION_INTERNAL_H_

#include "API/population.h"
#include "API/creature.h"
#include "API/selection_algorithm.h"
#include "API/termination_condition.h"
#include "API/galapagos_metadata.h"

#include "creature_internal.h

class population_internal : population {
  /*
	The internal implementation of the population object from the public API.
	*/
private:
	population_metadata* _population_metadata;

	std::vector<creature_internal*> _creatures;
	creature_internal* _optimal_creature;

	stochastic* _stochastic_instance;

public:
	population_internal(population_metadata* population_metadata, stochastic* stochastic_instance);

	~population_internal() override;

	// Returns the number of creates in the population.
	size_t get_size() override;

	creature* operator[] (int i) override;

	creature* get_creature(int i) override;

	// Returns the most optimal creature in terms of fitness.
	creature* get_optimal_creature() override;

	// Progresses the genetic algorithm until the termination conditions are met.
	void evolve() override;

private:
	creature* _find_optimal_creature();

	// Creates all the selection algorithms from the population metadata.
    std::vector<selection_algorithm*> _create_selection_algorithms();

    // Creates all the termination conditions from the population metadata.
    std::vector<termination_condition*> _create_termination_conditions();

    // Copies the n best creatures into the next generation based on the survival rate as defined in the metadata.
	size_t _elitism(std::vector<creature*>& new_generation);

	// Breeds population_size - surviving_creature_count, new creates from the current population.
	void _breed_new_generation(std::vector<creature*>& new_generation, size_t surviving_creature_count, selection_algorithm* selection_algorithm);

	// Checks if any of the termination conditions have been met.
	bool _has_terminated(std::vector<termination_condition*>& termination_conditions);
};

#endif /* _POPULATION_INTERNAL_H_ */
