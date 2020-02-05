#include <vector>
#include <algorithm>

#include "genetic_factory.h"

#include "population_internal.h"
#include "creature_internal.h"
#include "stochastic_internal.h"

//region Public Members

population_internal::population_internal(population_metadata* population_metadata, stochastic* stochastic_instance) {
	_population_metadata = population_metadata;
	_stochastic_instance = stochastic_instance;

	_creatures.resize(get_size());
	for (size_t i = 0; i < get_size(); i++)
	    _creatures[i] = new creature_internal(population_metadata->creature_metadata, stochastic_instance);

	_optimal_creature = nullptr;
}

population_internal::~population_internal() {
	// deleting the population should delete all other objects in the object
	// tree from the bottom up.
	for (size_t i = 0; i < get_size(); i++)
		delete _creatures[i];
    delete _stochastic_instance; // we should only need to delete this here.
}

// Returns the number of creaters in the population.
size_t population_internal::get_size() {
	return _population_metadata->size;
}

creature* population_internal::operator[] (int i) {
	return get_creature(i);
}

creature* population_internal::get_creature(int i) {
	return (creature*)_creatures[i];
}

// Returns the most optimal creature in turms of fitness.
creature* population_internal::get_optimal_creature() {
	return (creature*)_optimal_creature;
}

// Progresses the genetic algorithm until the termination conditions are met.
void population_internal::evolve() {
    // Initialize selection algorithm and termination conditions from meta data.
    std::vector<selection_algorithm*> selection_algorithms = _create_selection_algorithms();
    std::vector<termination_condition*> termination_conditions = _create_termination_conditions();

	std::vector<creature_internal*> new_generation;
	new_generation.resize(get_size());

	// Run the genetic algorithm till termination conditions are met.
	while (!_has_terminated(termination_conditions)) {  // TODO -- Figure out how to handle multiple selection_algorithms.
        _optimal_creature = _find_optimal_creature();
		size_t surviving_creature_count = _elitism(new_generation);
		_breed_new_generation(new_generation, surviving_creature_count, selection_algorithms[0]);
	}

	// clean-up memory
    for (auto & selection_algorithm : selection_algorithms)
        delete selection_algorithm;

	for (auto & termination_condition : termination_conditions)
		delete termination_condition;
}
//endregion

//region Private Members

creature_internal* population_internal::_find_optimal_creature() {
	creature_internal* optimal_creature = nullptr;
	double optimal_fitness = 0;

	size_t size = get_size();
	for (size_t i = 0; i < size; i++) {
		creature_internal* current_creature = _creatures[i];
		double current_fitness = current_creature->get_fitness();

		if (current_fitness > optimal_fitness) {
			optimal_fitness = current_fitness;
			optimal_creature = current_creature;
		}
	}

	return optimal_creature;
}

std::vector<selection_algorithm*> population_internal::_create_selection_algorithms() {
    std::vector<selection_algorithm*> selection_algorithms;

    for(size_t i = 0; i < _population_metadata->num_selection_algorithms; i++) {
        genetic_factory& factory = genetic_factory::get_instance();
        selection_algorithm* selection_algorithm = factory.create_selection_algorithm(
                _population_metadata->selection_algorithm_metadata[i]);
        selection_algorithms.push_back(selection_algorithm);
    }
    return selection_algorithms;
}

std::vector<termination_condition*> population_internal::_create_termination_conditions() {
    std::vector<termination_condition*> termination_conditions;

    for(size_t i = 0; i < _population_metadata->num_termination_conditions; i++) {
        genetic_factory& factory = genetic_factory::get_instance();
        termination_condition* termination_condition = factory.create_termination_condition(
                _population_metadata->termination_condition_metadata[i]);
        termination_conditions.push_back(termination_condition);
    }
    return termination_conditions;
}

// Copies the n best creatures into the next generation based on the survival rate as definied in the metadata.
size_t population_internal::_elitism(std::vector<creature_internal*>& new_generation) {
	size_t population_size = get_size();

	// Sorts the creatures by decending fitness
	std::sort(_creatures.begin(), _creatures.end(), [](creature_internal* x, creature_internal* y) {
		return x->get_fitness() > y->get_fitness();
		});  //TODO - check the complexity of this sort

	auto surviving_creature_count = (size_t)(_population_metadata->survival_rate * population_size);
	for (size_t i = 0; i < surviving_creature_count; i++)
		new_generation[i] = _creatures[i];

	return surviving_creature_count;
}

// Breeds population_size - surviving_creature_count, new creates from the current population.
void population_internal::_breed_new_generation(std::vector<creature_internal*>& new_generation, size_t surviving_creature_count, selection_algorithm* selection_algorithm) {
	size_t population_size = get_size();

	for (size_t i = surviving_creature_count; i < population_size; i++) {
		auto* parent1 = (creature_internal*)selection_algorithm->invoke(this);
		auto* parent2 = (creature_internal*)selection_algorithm->invoke(this);
		creature_internal* child = parent1->breed_with(parent2);
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
//endregion
