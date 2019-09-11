#include "API/galapagos.h"
#include "API/Factory/genetic_factory.h"
#include "API/stochastic.h"
#include "stochastic.h"

// Implementation of root galapgos "session" object
galapagos_session::galapagos_session()
{
	stochastic_internal* default_rng = new stochastic_internal();
	__stochastic__ = (stochastic*)default_rng;
}

galapagos_session::~galapagos_session()
{
	delete __stochastic__;
}

galapagos_session& galapagos_session::get_instance()
{
	static galapagos_session instance;
	return instance;
}

population_metadata* galapagos_session::create_population_metadata()
{
	return new population_metadata();
}

population* galapagos_session::create_population(population_metadata* population_metadata)
{
	return genetic_factory::create_population(population_metadata);
}

// Exported (.so/.dll) "C-style" interface to the galapagos library
GALAPAGOS_API population_metadata* create_population_metadata()
{
	galapagos_session& session = galapagos_session::get_instance();
	return session.create_population_metadata();
}

GALAPAGOS_API void set_population_metadata_size(population_metadata* population_metadata, size_t size)
{
	population_metadata->size = size;
}

GALAPAGOS_API size_t get_population_metadata_size(population_metadata* population_metadata)
{
	return population_metadata->size;
}

GALAPAGOS_API void set_population_metadata_survival_rate(population_metadata* population_metadata, double survival_rate)
{
	population_metadata->survival_rate = survival_rate;
}

GALAPAGOS_API double get_population_metadata_survival_rate(population_metadata* population_metadata)
{
	return population_metadata->survival_rate;
}

GALAPAGOS_API void set_population_metadata_distance_threshold(population_metadata* population_metadata, double distance_threshold) {
	population_metadata->distance_threshold = distance_threshold;
}

GALAPAGOS_API double get_population_metadata_distance_threshold(population_metadata* population_metadata) {
	return population_metadata->distance_threshold;
}

GALAPAGOS_API void set_population_metadata_cooperative_coevolution(population_metadata* population_metadata, bool cooperative_coevolution) {
	population_metadata->cooperative_coevolution = cooperative_coevolution;
}

GALAPAGOS_API bool get_population_metadata_cooperative_coevolution(population_metadata* population_metadata) {
	return population_metadata->cooperative_coevolution;
}

GALAPAGOS_API void set_population_metadata_num_selection_algorithm_metadata(population_metadata* population_metadata, size_t num_selection_algorithm_metadata) {
	population_metadata->num_selection_algorithm_metadata = num_selection_algorithm_metadata;
}

GALAPAGOS_API size_t get_population_metadata_num_selection_algorithm_metadata(population_metadata* population_metadata) {
	return population_metadata->num_selection_algorithm_metadata;
}

GALAPAGOS_API void set_population_metadata_selection_algorithm_metadata(population_metadata* population_metadata, selection_algorithm_metadata* selection_algorithm_metadata) {
	population_metadata->selection_algorithm_metadata = selection_algorithm_metadata;
}

GALAPAGOS_API selection_algorithm_metadata* get_population_metadata_selection_algorithm_metadata(population_metadata* population_metadata) {
	return population_metadata->selection_algorithm_metadata;
}

GALAPAGOS_API void set_population_metadata_num_termination_condition_metadata(population_metadata* population_metadata, size_t num_termination_condition_metadata) {
	population_metadata->num_termination_condition_metadata = num_termination_condition_metadata;
}

GALAPAGOS_API size_t get_population_metadata_num_termination_condition_metadata(population_metadata* population_metadata) {
	return population_metadata->num_termination_condition_metadata;
}

GALAPAGOS_API void set_population_metadata_termination_condition_metadata(population_metadata* population_metadata, termination_condition_metadata* termination_condition_metadata) {
	population_metadata->termination_condition_metadata = termination_condition_metadata;
}

GALAPAGOS_API termination_condition_metadata* get_population_metadata_termination_condition_metadata(population_metadata* population_metadata) {
	return population_metadata->termination_condition_metadata;
}

GALAPAGOS_API void set_population_metadata_fitness_function(population_metadata* population_metadata, fitness_func_t fitness_function) {
	population_metadata->fitness_function = fitness_function;
}

GALAPAGOS_API fitness_func_t get_population_metadata_fitness_function(population_metadata* population_metadata) {
	return population_metadata->fitness_function;
}

GALAPAGOS_API void set_population_metadata_num_chromosome_metadata(population_metadata* population_metadata, size_t num_chromosome_metadata) {
	population_metadata->num_chromosome_metadata = num_chromosome_metadata;
}

GALAPAGOS_API size_t get_population_metadata_num_chromosome_metadata(population_metadata* population_metadata) {
	return population_metadata->num_chromosome_metadata;
}

GALAPAGOS_API void set_population_metadata_chromosome_metadata(population_metadata* population_metadata, chromosome_metadata* chromosome_metadata) {
	population_metadata->chromosome_metadata = chromosome_metadata;
}

GALAPAGOS_API chromosome_metadata* get_population_metadata_chromosome_metadata(population_metadata* population_metadata) {
	return population_metadata->chromosome_metadata;
}

GALAPAGOS_API population* create_population(population_metadata* population_metadata)
{
	galapagos_session& session = galapagos_session::get_instance();
	return session.create_population(population_metadata);
}
