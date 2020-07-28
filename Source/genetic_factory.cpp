#include "genetic_factory.h"

genetic_factory& genetic_factory::get_instance() {
    static genetic_factory instance;
    return instance;
}

//region plugin registration

void genetic_factory::register_selection_algorithm(std::type_index index, const create_selection_algorithm_t& create_selection_algorithm) {
    _registered_selection_algorithms[index] = create_selection_algorithm;
}

void genetic_factory::register_termination_condition(std::type_index index, const create_termination_condition_t& create_termination_condition) {
    _registered_termination_conditions[index] = create_termination_condition;
}

void genetic_factory::register_chromosome(std::type_index index, const create_chromosome_t& create_chromosome) {
    _registered_chromosomes[index] = create_chromosome;
}

void genetic_factory::register_crossover(std::type_index index, const create_crossover_t& create_crossover) {
    _registered_crossovers[index] = create_crossover;
}

void genetic_factory::register_mutation(std::type_index index, const create_mutation_t& create_mutation) {
    _registered_mutations[index] = create_mutation;
}

//endregion

//region plugin construction

// TODO: error handling for map miss

std::shared_ptr<selection_algorithm> genetic_factory::create_selection_algorithm(const selection_algorithm_metadata& selection_algorithm_metadata) {
    return _registered_selection_algorithms[std::type_index(typeid(selection_algorithm_metadata))](selection_algorithm_metadata);
}

std::shared_ptr<termination_condition> genetic_factory::create_termination_condition(const termination_condition_metadata& termination_condition_metadata) {
    return _registered_termination_conditions[std::type_index(typeid(termination_condition_metadata))](termination_condition_metadata);
}

std::shared_ptr<chromosome> genetic_factory::create_chromosome(const chromosome_metadata& chromosome_metadata) {
    return _registered_chromosomes[std::type_index(typeid(chromosome_metadata))](chromosome_metadata);
}

std::shared_ptr<crossover> genetic_factory::create_crossover(const crossover_metadata& crossover_metadata) {
    return _registered_crossovers[std::type_index(typeid(crossover_metadata))](crossover_metadata);
}

std::shared_ptr<mutation> genetic_factory::create_mutation(const mutation_metadata& mutation_metadata) {
    return _registered_mutations[std::type_index(typeid(mutation_metadata))](mutation_metadata);
}

//endregion
