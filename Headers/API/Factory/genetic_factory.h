#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include <vector>

#include "../../../Headers/API/galapagos_metadata.h"
#include "../../../Headers/API/population.h"
#include "../../../Headers/API/selection_algorithm.h"
#include "../../../Headers/API/termination_condition.h"

class genetic_factory {
public:
	static population* create_population(population_metadata* population_metadata);
	static selection_algorithm* create_selection_algorithm(population_metadata* population_metadata);
	static std::vector<termination_condition*> create_termination_conditions(population_metadata* population_metadata);
};

#endif /* _GENETIC_FACTORY_H_ */
