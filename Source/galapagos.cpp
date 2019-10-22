#include "API/galapagos.h"
#include "API/Factory/genetic_factory.h"
#include "API/stochastic.h"
#include "stochastic.h"

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata) {
	return genetic_factory::create_population(population_metadata);
}

GALAPAGOS_API void delete_population(population* population) {
	delete population;
}