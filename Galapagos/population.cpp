#ifndef _POPULATION_CPP_
#define _POPULATION_CPP_

#include "genetic_factory.h"
#include "population.h"
#include "population_metadata.h"
#include "creature.h"

class population_internal : population {
	/*
	The internal implementation of the population object from the public API.
	*/
private:
	population_metadata* _population_metadata;

	creature** _creatures;
	creature* _optimal_creature;
	
public:
	population_internal(population_metadata* population_metadata)
	{
		_population_metadata = population_metadata;

		_creatures = new creature*[_population_metadata->size];
		_optimal_creature = nullptr;
	}

	// Returns the number of creaters in the population.
	uint32_t get_size() override {
		return _population_metadata->size;
	}

	creature* operator[] (int i) override {
		return _creatures[i];
	}

	// Returns the most optimal creature in turms of fitness.
	creature* get_optimal_creature() override {
		return _optimal_creature;
	}

	// Progresses the genetic algorithum until the termination conditions are met.
	void evolve() override {
		uint32_t size = get_size();
		creature** new_generation = new creature*[size];

		selection_algorithm* selection_algorithm = genetic_factory::create_selection_algorithm(_population_metadata->selection_algorithm);
		termination_condition** termination_conditions = genetic_factory::create_termination_conditions(_population_metadata->termination_conditions);

		while (true) {
			// Breed new generation.
			for (uint32_t i = 0; i < size; i++) {
				creature* parent1 = selection_algorithm->invoke(this);
				creature* parent2 = selection_algorithm->invoke(this);
				creature* child = parent1->breed_with(parent2);
				new_generation[i] = child;
			}

			// Check termination conditions

		}
	}

private:
	creature* _find_optimal_creature() {
		creature* optimal_creature = nullptr;
		double optimal_fitness = 0;

		uint32_t size = get_size();
		for (uint32_t i = 0; i < size; i++) {
			creature* current_creature = _creatures[i];
			double current_fitness = current_creature->get_fitness();

			if (current_fitness > optimal_fitness) {
				optimal_fitness = current_fitness;
				optimal_creature = current_creature;
			}
		}

		return optimal_creature;
	}
};

#endif /* _POPULATION_CPP_ */