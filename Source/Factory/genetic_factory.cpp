#include <vector>

#include "../API/Factory/genetic_factory.h"
//#include "../population.h"

population* genetic_factory::create_population(population_metadata* population_metadata)
{
	return nullptr;
}

selection_algorithm* genetic_factory::create_selection_algorithm(population_metadata* population_metadata)
{
	return nullptr;
}

std::vector<termination_condition*> genetic_factory::create_termination_conditions(population_metadata* population_metadata)
{
	std::vector<termination_condition*> termination_conditions;
	return termination_conditions;
}
