#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include "galapagos_metadata.h"
#include "population.h"
#include "creature.h"
#include "chromosome.h"

#ifdef WIN32
#define GALAPAGOS_API extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_API extern "C" __attribute__((visibility("default")))
#endif

/*****************************
*****Galapagos Population*****
*****************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata);
GALAPAGOS_API void delete_population(population* population);

GALAPAGOS_API size_t population_get_size(population* population);
GALAPAGOS_API creature* population_get_creature(population* population, int i);
GALAPAGOS_API creature* population_get_optimal_creature(population* population);
GALAPAGOS_API void population_evolve(population* population);

/***************************
*****Galapagos Creature*****
***************************/
GALAPAGOS_API double creature_get_fitness(creature* creature);
GALAPAGOS_API chromosome* creature_get_chromosome(creature* creature, std::string name);

#endif /* _GALAPAGOS_H_ */
