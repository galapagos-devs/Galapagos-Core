#include "genetic_factory.h"
#include "population.h"
#include "population.cpp"

population* genetic_factory::create_population(population_metadata* population_metadata)
{
	population_internal population_obj(population_metadata);
	population *population_ptr = (population*)&population_obj;
	return population_ptr;
}
