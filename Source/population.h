#ifndef _POPULATION_INTERNAL_H_
#define _POPULATION_INTERNAL_H_

#include "API/population.h"
#include "API/creature.h"
#include "API/selection_algorithm.h"
#include "API/termination_condition.h"
#include "API/galapagos_metadata.h"

class population_internal : population {
  /*
	The internal implementation of the population object from the public API.
	*/
private:
	population_metadata* _population_metadata;

	std::vector<creature*> _creatures;
	creature* _optimal_creature;

public:
	population_internal(population_metadata* population_metadata);

	~population_internal();

	// Returns the number of creaters in the population.
	size_t get_size() override;

	creature* operator[] (int i) override;

	// Returns the most optimal creature in turms of fitness.
	creature* get_optimal_creature();

	// Progresses the genetic algorithum until the termination conditions are met.
	void evolve() override;

private:
	creature* _find_optimal_creature();

	// Copies the n best creatures into the next generation based on the survival rate as definied in the metadata.
	size_t _elitism(std::vector<creature*>& new_generation);

	// Breeds population_size - surviving_creature_count, new creates from the current population.
	void _breed_new_generation(std::vector<creature*>& new_generation, size_t surviving_creature_count, selection_algorithm* selection_algorithm);

	// Checks if any of the termination conditions have been met.
	bool _has_terminated(std::vector<termination_condition*>& termination_conditions);
};

#endif /* _POPULATION_INTERNAL_H_ */
