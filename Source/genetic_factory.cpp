#include "genetic_factory.h"

genetic_factory& genetic_factory::get_instance() {
    static genetic_factory instance;
    return instance;
}

//region plugin registration

void genetic_factory::register_selection_algorithm(std::type_index index,
        const create_selection_algorithm_t& create_selection_algorithm,
        const delete_selection_algorithm_t& delete_selection_algorithm) {
    _registered_selection_algorithms[index] = std::make_tuple(create_selection_algorithm, delete_selection_algorithm);
}

void genetic_factory::register_termination_condition(std::type_index index,
        const create_termination_condition_t& create_termination_condition,
        const delete_termination_condition_t& delete_termination_condition) {
    _registered_termination_conditions[index] = std::make_tuple(create_termination_condition, delete_termination_condition);
}

void genetic_factory::register_chromosome(std::type_index index,
        const create_chromosome_t& create_chromosome,
        const delete_chromosome_t& delete_chromosome) {
    _registered_chromosomes[index] = std::make_tuple(create_chromosome, delete_chromosome);
}

void genetic_factory::register_crossover(std::type_index index,
        const create_crossover_t& create_crossover,
        const delete_crossover_t& delete_crossover) {
    _registered_crossovers[index] = std::make_tuple(create_crossover, delete_crossover);
}

void genetic_factory::register_mutation(std::type_index index,
        const create_mutation_t& create_mutation,
        const delete_mutation_t& delete_mutation) {
    _registered_mutations[index] = std::make_tuple(create_mutation, delete_mutation);
}

//endregion

//region plugin construction

// TODO: error handling for map miss
#define CREATE_INDEX 0
#define DELETE_INDEX 1

std::shared_ptr<selection_algorithm> genetic_factory::create_selection_algorithm(const selection_algorithm_metadata& selection_algorithm_metadata) {
    auto registration = _registered_selection_algorithms[std::type_index(typeid(selection_algorithm_metadata))];
    auto create_selection_algorithm = std::get<CREATE_INDEX>(registration);
    auto delete_selection_algorithm = std::get<DELETE_INDEX>(registration);
    return std::shared_ptr<selection_algorithm>(create_selection_algorithm(selection_algorithm_metadata), delete_selection_algorithm);
}

std::shared_ptr<termination_condition> genetic_factory::create_termination_condition(const termination_condition_metadata& termination_condition_metadata) {
    auto registration = _registered_termination_conditions[std::type_index(typeid(termination_condition_metadata))];
    auto create_termination_condition = std::get<CREATE_INDEX>(registration);
    auto delete_termination_condition = std::get<DELETE_INDEX>(registration);
    return std::shared_ptr<termination_condition>(create_termination_condition(termination_condition_metadata), delete_termination_condition);
}

std::shared_ptr<chromosome> genetic_factory::create_chromosome(const chromosome_metadata& chromosome_metadata) {
    auto registration = _registered_chromosomes[std::type_index(typeid(chromosome_metadata))];
    auto create_chromosome = std::get<CREATE_INDEX>(registration);
    auto delete_chromosome = std::get<DELETE_INDEX>(registration);
    return std::shared_ptr<chromosome>(create_chromosome(chromosome_metadata), delete_chromosome);
}

std::shared_ptr<crossover> genetic_factory::create_crossover(const crossover_metadata& crossover_metadata) {
    auto registration = _registered_crossovers[std::type_index(typeid(crossover_metadata))];
    auto create_crossover = std::get<CREATE_INDEX>(registration);
    auto delete_crossover = std::get<DELETE_INDEX>(registration);
    return std::shared_ptr<crossover>(create_crossover(crossover_metadata), delete_crossover);
}

std::shared_ptr<mutation> genetic_factory::create_mutation(const mutation_metadata& mutation_metadata) {
    auto registration = _registered_mutations[std::type_index(typeid(mutation_metadata))];
    auto create_mutation = std::get<CREATE_INDEX>(registration);
    auto delete_mutation = std::get<DELETE_INDEX>(registration);
    return std::shared_ptr<mutation>(create_mutation(mutation_metadata), delete_mutation);
}

//endregion
