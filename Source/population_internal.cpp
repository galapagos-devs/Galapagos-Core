#include <algorithm>
#include <memory>

#include "API/genetic_factory.h"

#include "population_internal.h"
#include "creature_internal.h"
#include "stochastic_internal.h"

//region Public Members

population_internal::population_internal(const population_metadata& metadata, stochastic& stochastic_instance) :
        _metadata{metadata}, _stochastic_instance{stochastic_instance} {
    _this = std::shared_ptr<population_internal>(this, [](population_internal*){});

    _creatures.resize(get_size());
    genetic_factory& factory = genetic_factory::get_instance();
    for (size_t i = 0; i < get_size(); i++)
        _creatures[i] = factory.create_creature(metadata.creature_metadata);
    _optimal_creature = _creatures[0];
}

// Returns the number of creaters in the population.
size_t population_internal::get_size() const {
    return _metadata.size;
}

std::shared_ptr<creature> population_internal::operator[] (int i) const {
    return get_creature(i);
}

std::shared_ptr<creature> population_internal::get_creature(int i) const {
    return _creatures[i];
}

// Returns the most optimal creature in turms of fitness.
std::shared_ptr<creature> population_internal::get_optimal_creature() const {
    return _optimal_creature;
}

// Progresses the genetic algorithm until the termination conditions are met.
void population_internal::evolve() {
    // Initialize selection algorithm and termination conditions from meta data.
    auto selection_algorithms = _create_selection_algorithms();
    auto termination_conditions = _create_termination_conditions();

    std::vector<std::shared_ptr<creature>> new_generation;
    new_generation.resize(get_size());

    // Run the genetic algorithm till termination conditions are met.
    int generation = 0;
    while (!_has_terminated(termination_conditions)) {  // TODO -- Figure out how to handle multiple selection_algorithms.
        size_t surviving_creature_count = _elitism(new_generation);
        _breed_new_generation(new_generation, surviving_creature_count, selection_algorithms[0]);
        _optimal_creature = _find_optimal_creature();
        _current_log_entry.generation = ++generation;

        if(_metadata.log_function != nullptr)  // TODO: log_functions should be processed on its own thread
            _metadata.log_function(_current_log_entry);
    }
}
//endregion

//region Private Members

// Copies the n best creatures into the next generation based on the survival rate as definied in the metadata.
size_t population_internal::_elitism(std::vector<std::shared_ptr<creature>>& new_generation) {
    size_t population_size = get_size();

    // Sorts the creatures by descending fitness
    std::sort(_creatures.begin(), _creatures.end(),
            [](const std::shared_ptr<creature>& x, const std::shared_ptr<creature>& y) {
                return x->get_fitness() > y->get_fitness();
    });

    auto surviving_creature_count = (size_t)(_metadata.survival_rate * population_size);
    for (size_t i = 0; i < surviving_creature_count; i++)
        new_generation[i] = _creatures[i];

    return surviving_creature_count;
}

// Breeds population_size - surviving_creature_count, new creates from the current population.
void population_internal::_breed_new_generation(std::vector<std::shared_ptr<creature>>& new_generation, size_t surviving_creature_count, std::shared_ptr<selection_algorithm> selection_algorithm) {
    size_t population_size = get_size();

    for (size_t i = surviving_creature_count; i < population_size; i++) {
        auto parent1 = (*selection_algorithm)(_this);
        auto parent2 = (*selection_algorithm)(_this);
        auto child = parent1->breed_with(parent2);
        new_generation[i] = child;
    }

    for (size_t i = surviving_creature_count; i < population_size; i++)
        _creatures[i] = new_generation[i];
}

// Checks if any of the termination conditions have been met.
bool population_internal::_has_terminated(std::vector<std::shared_ptr<termination_condition>>& termination_conditions) {
    size_t num_termination_conditions = termination_conditions.size();

    for (size_t i = 0; i < num_termination_conditions; i++) {
        auto current_termination_condition = termination_conditions[i];
        if ((*current_termination_condition)(_this))
            return true;
    }
    return false;
}

std::shared_ptr<creature> population_internal::_find_optimal_creature() {
    std::shared_ptr<creature> optimal_creature = nullptr;
    double optimal_fitness = 0;

    size_t size = get_size();
    for (size_t i = 0; i < size; i++) {
        std::shared_ptr<creature> current_creature = _creatures[i];
        double current_fitness = current_creature->get_fitness();

        if (current_fitness > optimal_fitness) {
            optimal_fitness = current_fitness;
            optimal_creature = current_creature;
            _current_log_entry.optimal_fitness = optimal_fitness;
        }
    }

    return optimal_creature;
}

std::vector<std::shared_ptr<selection_algorithm>> population_internal::_create_selection_algorithms() {
    auto num_selection_algorithms = _metadata.selection_algorithm_metadata.size();
    std::vector<std::shared_ptr<selection_algorithm>> selection_algorithms;

    for(size_t i = 0; i < num_selection_algorithms; i++) {
        genetic_factory& factory = genetic_factory::get_instance();
        selection_algorithms.push_back(factory.create_selection_algorithm(
                *_metadata.selection_algorithm_metadata[i]));
    }

    return selection_algorithms;
}

std::vector<std::shared_ptr<termination_condition>> population_internal::_create_termination_conditions() {
    auto num_termination_conditions = _metadata.termination_condition_metadata.size();
    std::vector<std::shared_ptr<termination_condition>> termination_conditions;

    for(size_t i = 0; i < num_termination_conditions; i++) {
        genetic_factory& factory = genetic_factory::get_instance();
        termination_conditions.push_back(factory.create_termination_condition(
                *_metadata.termination_condition_metadata[i]));
    }

    return termination_conditions;
}

//endregion
