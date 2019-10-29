#include <vector>

#include "../API/Factory/genetic_factory.h"
//#include "../population_internal.h"

// Core hierarchy
population* genetic_factory::create_population(population_metadata* population_metadata) {
	return nullptr;
}

creature* genetic_factory::create_creature(creature_metadata* creature_metadata) {
	return nullptr;
}

chromosome* genetic_factory::create_chromosome(chromosome_metadata* chromosome_metadata) {
	return nullptr;
}


// Plugin objects
selection_algorithm* genetic_factory::create_selection_algorithm(selection_algorithm_metadata* selection_algorithm_metadata) {
	return nullptr;
}

termination_condition* genetic_factory::create_termination_condition(termination_condition_metadata* termination_condition_metadata) {
	return nullptr;
}
