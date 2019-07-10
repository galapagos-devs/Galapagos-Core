#include "galapagos.h"
#include "genetic_factory.h"

GALAPAGOS_API population_metadata* create_population_metadata()
{
	return new population_metadata();
}

GALAPAGOS_API void set_population_metadata_size(population_metadata* population_metadata, uint32_t size)
{
	population_metadata->size = size;
}

GALAPAGOS_API uint32_t get_population_metadata_size(population_metadata* population_metadata)
{
	return population_metadata->size;
}

GALAPAGOS_API void set_population_metadata_survival_rate(population_metadata* population_metadata, uint32_t survival_rate)
{
	population_metadata->survival_rate = survival_rate;
}

GALAPAGOS_API uint32_t get_population_metadata_survival_rate(population_metadata* population_metadata)
{
	return population_metadata->survival_rate;
}

GALAPAGOS_API population* create_population(population_metadata* population_metadata)
{
	return genetic_factory::create_population(population_metadata);
}
