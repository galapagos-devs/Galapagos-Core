#include <vector>

#include "genetic_factory.h"
#include "population.h"
#include "population.cpp"

population* genetic_factory::create_population(population_metadata* population_metadata)
{
	population_internal population_obj(population_metadata);
	population *population_ptr = (population*)&population_obj;
	return population_ptr;
}

selection_algorithm* genetic_factory::create_selection_algorithm(selection_algo_t selection_algo)
{
	return nullptr;
}

std::vector<termination_condition*> genetic_factory::create_termination_conditions(term_cond_t term_cond)
{
	std::vector<termination_condition*> termination_conditions;
	return termination_conditions;
}
