#include "API/galapagos.h"
#include "population_internal.h"
#include "stochastic_internal.h"

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata) {
	stochastic_internal* stochastic_instance = new stochastic_internal();
	return (population*)new population_internal(population_metadata, (stochastic*)stochastic_instance);
}

GALAPAGOS_API void delete_population(population* population) {
	delete population;
}

GALAPAGOS_API size_t population_get_size(population* population) {
    return population->get_size();
}

GALAPAGOS_API creature* population_get_creature(population* population, int i) {
    return population->get_creature(i);
}

GALAPAGOS_API creature* population_get_optimal_creature(population* population) {
    return population->get_optimal_creature();
}

GALAPAGOS_API void population_evolve(population* population) {
    population->evolve();
}

/***************************
*****Galapagos Creature*****
***************************/
GALAPAGOS_API double creature_get_fitness(creature* creature) {
    return creature->get_fitness();
}

GALAPAGOS_API chromosome* creature_get_chromosome(creature* creature, std::string name) {
    return creature->get_chromosome<chromosome>(name);
}
