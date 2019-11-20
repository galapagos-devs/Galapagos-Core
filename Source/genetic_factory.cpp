#include "genetic_factory.h"

chromosome* genetic_factory::create_chromosome(chromosome_metadata* chromosome_metadata) {
	return nullptr;
}

selection_algorithm* genetic_factory::create_selection_algorithm(selection_algorithm_metadata* selection_algorithm_metadata) {
	return nullptr;
}

termination_condition* genetic_factory::create_termination_condition(termination_condition_metadata* termination_condition_metadata) {
	return nullptr;
}

crossover* genetic_factory::create_crossover(crossover_metadata* crossover_metadata) {
	return nullptr;
}

mutation* genetic_factory::create_mutation(mutation_metadata* mutation_metadata) {
	return nullptr;
}
