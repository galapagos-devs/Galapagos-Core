#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include "population.h"
#include "population_metadata.h"

class genetic_factory {
public:
	static population* create_population(population_metadata* population_metadata);
};

#endif /* _GENETIC_FACTORY_H_ */
