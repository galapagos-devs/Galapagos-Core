#include "genetic_factory.h"

genetic_factory& genetic_factory::get_instance() {
    static genetic_factory instance;
    return instance;
}

//region plugin registration

void genetic_factory::reset() {
    _registered_selection_algorithms.clear();
    _registered_termination_conditions.clear();
    _registered_chromosomes.clear();
    _registered_crossovers.clear();
    _registered_mutations.clear();
}

void genetic_factory::register_selection_algorithm(const try_create_selection_algorithm_t& try_create) {
    _registered_selection_algorithms.push_back(try_create);
}

void genetic_factory::register_termination_condition(const try_create_termination_condition_t& try_create) {
    _registered_termination_conditions.push_back(try_create);
}

void genetic_factory::register_chromosome(const try_create_chromosome_t& try_create) {
    _registered_chromosomes.push_back(try_create);
}

void genetic_factory::register_crossover(const try_create_crossover_t& try_create) {
    _registered_crossovers.push_back(try_create);
}

void genetic_factory::register_mutation(const try_create_mutation_t& try_create) {
    _registered_mutations.push_back(try_create);
}

//endregion

//region plugin construction

selection_algorithm* genetic_factory::create_selection_algorithm(const selection_algorithm_metadata* selection_algorithm_metadata) {
	for(const try_create_selection_algorithm_t& try_create : _registered_selection_algorithms) {
	    selection_algorithm* selection_algorithm = nullptr;
	    if(try_create(selection_algorithm_metadata, selection_algorithm))
            return  selection_algorithm;
	}
	throw std::runtime_error("genetic_factory::create_selection_algorithm invalid metadata");
}

termination_condition* genetic_factory::create_termination_condition(const termination_condition_metadata* termination_condition_metadata) {
    for(const try_create_termination_condition_t& try_create : _registered_termination_conditions) {
        termination_condition* termination_condition = nullptr;
        if(try_create(termination_condition_metadata, termination_condition))
            return termination_condition;
    }
    throw std::runtime_error("genetic_factory::create_termination_condition invalid metadata");
}

chromosome* genetic_factory::create_chromosome(const chromosome_metadata* chromosome_metadata) {
    for(const try_create_chromosome_t& try_create : _registered_chromosomes) {
        chromosome* chromosome = nullptr;
        if(try_create(chromosome_metadata, chromosome))
            return chromosome;
    }
    throw std::runtime_error("genetic_factory::create_chromosome invalid metadata");
}

crossover* genetic_factory::create_crossover(const crossover_metadata* crossover_metadata) {
    for(const try_create_crossover_t& try_create : _registered_crossovers) {
        crossover* crossover = nullptr;
        if(try_create(crossover_metadata, crossover))
            return crossover;
    }
    throw std::runtime_error("genetic_factory::create_crossover invalid metadata");
}

mutation* genetic_factory::create_mutation(const mutation_metadata* mutation_metadata) {
    for(const try_create_mutation_t& try_create : _registered_mutations) {
        mutation* mutation = nullptr;
        if(try_create(mutation_metadata, mutation))
            return mutation;
    }
    throw std::runtime_error("genetic_factory::create_mutation invalid metadata");
}

//endregion
