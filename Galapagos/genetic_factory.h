#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include "galapagos_types.h"
#include "population.h"
#include "population_metadata.h"
#include "selection_algorithm.h"
#include "termination_condition.h"

class genetic_factory {
public:
	static population* create_population(population_metadata* population_metadata);
	static selection_algorithm* create_selection_algorithm(selection_algo_t selection_algorithm);
	static termination_condition** create_termination_conditions(term_cond_t termination_conditions);
};

#endif /* _GENETIC_FACTORY_H_ */
