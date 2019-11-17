#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include "API/galapagos_metadata.h"
#include "API/chromosome.h"
#include "API/selection_algorithm.h"
#include "API/termination_condition.h"
#include "API/crossover.h"
#include "API/mutation.h"

class genetic_factory {
public:
	static chromosome* create_chromosome(chromosome_metadata* chromosome_metadata);

	static selection_algorithm* create_selection_algorithm(selection_algorithm_metadata* selection_algorithm_metadata);
	static termination_condition* create_termination_condition(termination_condition_metadata* termination_condition_metadata);

	static crossover* create_crossover(crossover_metadata* crossover_metadata);
	static mutation* create_mutation(mutation_metadata* mutation_metadata);
};

#endif /* _GENETIC_FACTORY_H_ */
