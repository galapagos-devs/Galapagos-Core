#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <cstdint>

#include "galapagos_metadata.h"
#include "population.h"
#include "stochastic.h"

class galapagos_session {
public:
	stochastic* __stochastic__;

public:
	galapagos_session();
	~galapagos_session();

	static galapagos_session& get_instance();

	population* create_population(population_metadata* population_metadata);
};

#ifdef WIN32
#define GALAPAGOS_API extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_API extern "C" __attribute__((visibility("default")))
#endif

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata);
GALAPAGOS_API void delete_population(population* population);

/****************************
*****Chromosome Metadata*****
****************************/
GALAPAGOS_API chromosome_metadata* create_chromosome_metadata();
GALAPAGOS_API void delete_chromosome_metadata(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_name(chromosome_metadata* chromosome_metadata, const char* name);
GALAPAGOS_API const char* get_chromosome_metadata_name(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_crossover_rate(chromosome_metadata* chromosome_metadata, double crossover_rate);
GALAPAGOS_API double get_chromosome_metadata_crossover_rate(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_mutation_rate(chromosome_metadata* chromosome_metadata, double mutation_rate);
GALAPAGOS_API double get_chromosome_metadata_mutation_rate(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_num_crossovers(chromosome_metadata* chromosome_metadata, size_t num_crossovers);
GALAPAGOS_API size_t get_chromosome_metadata_num_crossovers(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_crossovers(chromosome_metadata* chromosome_metadata, crossover_metadata** crossovers);
GALAPAGOS_API crossover_metadata** get_chromosome_metadata_crossovers(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_num_mutations(chromosome_metadata* chromosome_metadata, size_t num_mutations);
GALAPAGOS_API size_t get_chromosome_metadata_num_mutations(chromosome_metadata* chromosome_metadata);

GALAPAGOS_API void set_chromosome_metadata_mutations(chromosome_metadata* chromosome_metadata, mutation_metadata** mutations);
GALAPAGOS_API mutation_metadata** get_chromosome_metadata_mutations(chromosome_metadata* chromosome_metadata);

/****************************
*****Population Metadata*****
****************************/
GALAPAGOS_API population_metadata* create_population_metadata();
GALAPAGOS_API void delete_population_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_size(population_metadata* population_metadata, size_t size);
GALAPAGOS_API size_t get_population_metadata_size(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_survival_rate(population_metadata* population_metadata, double survival_rate);
GALAPAGOS_API double get_population_metadata_survival_rate(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_distance_threshold(population_metadata* population_metadata, double distance_threshold);
GALAPAGOS_API double get_population_metadata_distance_threshold(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_cooperative_coevolution(population_metadata* population_metadata, bool cooperative_coevolution);
GALAPAGOS_API bool get_population_metadata_cooperative_coevolution(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_num_selection_algorithm_metadata(population_metadata* population_metadata, size_t num_selection_algorithm_metadata);
GALAPAGOS_API size_t get_population_metadata_num_selection_algorithm_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_selection_algorithm_metadata(population_metadata* population_metadata, selection_algorithm_metadata** selection_algorithm_metadata);
GALAPAGOS_API selection_algorithm_metadata** get_population_metadata_selection_algorithm_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_num_termination_condition_metadata(population_metadata* population_metadata, size_t num_termination_condition_metadata);
GALAPAGOS_API size_t get_population_metadata_num_termination_condition_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_termination_condition_metadata(population_metadata* population_metadata, termination_condition_metadata** termination_condition_metadata);
GALAPAGOS_API termination_condition_metadata** get_population_metadata_termination_condition_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_fitness_function(population_metadata* population_metadata, fitness_func_t fitness_function);
GALAPAGOS_API fitness_func_t get_population_metadata_fitness_function(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_num_chromosome_metadata(population_metadata* population_metadata, size_t num_chromosome_metadata);
GALAPAGOS_API size_t get_population_metadata_num_chromosome_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_chromosome_metadata(population_metadata* population_metadata, chromosome_metadata** chromosome_metadata);
GALAPAGOS_API chromosome_metadata** get_population_metadata_chromosome_metadata(population_metadata* population_metadata);

#endif /* _GALAPAGOS_H_ */
