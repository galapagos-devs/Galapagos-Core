#include <vector>
#include <algorithm>

#include "population_internal.h"
#include "API/Factory/genetic_factory.h"

// Public members

population_internal::population_internal(population_metadata* population_metadata) {
	_population_metadata = population_metadata;

	_creatures.resize(get_size());
	for (size_t i = 0; i < get_size(); i++)
	    _creatures[i] = genetic_factory::create_creature(population_metadata->creature_metadata);

	_optimal_creature = nullptr;
}

population_internal::~population_internal() {
	for (size_t i = 0; i < get_size(); i++)
		delete _creatures[i];
}

// Returns the number of creaters in the population.
size_t population_internal::get_size() {
	return _population_metadata->size;
}

creature* population_internal::operator[] (int i) {
	return get_creature(i);
}

creature* population_internal::get_creature(int i) {
	return _creatures[i];
}

// Returns the most optimal creature in turms of fitness.
creature* population_internal::get_optimal_creature() {
	return _optimal_creature;
}

// Progresses the genetic algorithm until the termination conditions are met.
void population_internal::evolve() {
    // Initialize list of selection algorithms
    std::vector<selection_algorithm*> selection_algorithms;
    for(size_t i = 0; i < _population_metadata->num_selection_algorithms)
        selection_algorithms.push_back(
            genetic_factory::create_selection_algorithm(
                _population_metadata->selection_algorithm_metadata[i]));

    // Initialize list of termination conditions
    std::vector<termination_condition*> termination_conditions;
    for(size_t i = 0; i < _population_metadata->num_termination_conditions)
        termination_conditions.push_back(
            genetic_factory::create_termination_conditions(
                _population_metadata->termination_conditions_metadata[i]));

	std::vector<creature*> new_generation;
	new_generation.resize(get_size());

	while (!_has_terminated(termination_conditions)) {  // TODO -- Figure out how to handle multiple selection_algorithms.
		size_t surviving_creature_count = _elitism(new_generation);
		_breed_new_generation(new_generation, surviving_creature_count, selection_algorithms[0]);
	}

		// clean-up memory
	delete selection_algorithm;
	for (size_t i = 0; i < termination_conditions.size(); i++)
		delete termination_conditions[i];
}

// Private members
creature* population_internal::_find_optimal_creature() {
	creature* optimal_creature = nullptr;
	double optimal_fitness = 0;

	size_t size = get_size();
	for (size_t i = 0; i < size; i++) {
		creature* current_creature = _creatures[i];
		double current_fitness = current_creature->get_fitness();

		if (current_fitness > optimal_fitness) {
			optimal_fitness = current_fitness;
			optimal_creature = current_creature;
		}
	}

	return optimal_creature;
}

// Copies the n best creatures into the next generation based on the survival rate as definied in the metadata.
size_t population_internal::_elitism(std::vector<creature*>& new_generation) {
	size_t population_size = get_size();

	// Sorts the creatures by decending fitness
	std::sort(_creatures.begin(), _creatures.end(), [](creature* x, creature* y) {
		return x->get_fitness() > y->get_fitness();
		});  //TODO - check the complexity of this sort

	size_t surviving_creature_count = (size_t)(_population_metadata->survival_rate * population_size);
	for (size_t i = 0; i < surviving_creature_count; i++)
		new_generation[i] = _creatures[i];

	return surviving_creature_count;
}

// Breeds population_size - surviving_creature_count, new creates from the current population.
void population_internal::_breed_new_generation(std::vector<creature*>& new_generation, size_t surviving_creature_count, selection_algorithm* selection_algorithm) {
	size_t population_size = get_size();

	for (size_t i = surviving_creature_count; i < population_size; i++) {
		creature* parent1 = selection_algorithm->invoke(this);
		creature* parent2 = selection_algorithm->invoke(this);
		creature* child = parent1->breed_with(parent2);
		new_generation[i] = child;
	}

	for (size_t i = 0; i < population_size; i++) {
		delete _creatures[i];
		_creatures[i] = new_generation[i];
	}
}

// Checks if any of the termination conditions have been met.
bool population_internal::_has_terminated(std::vector<termination_condition*>& termination_conditions) {
	size_t num_termination_conditions = termination_conditions.size();

	for (size_t i = 0; i < num_termination_conditions; i++) {
		termination_condition* current_termination_condition = termination_conditions[i];
		if (current_termination_condition->invoke(this))
			return true;
	}
	return false;
}
