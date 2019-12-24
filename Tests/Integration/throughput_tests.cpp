#include "../../Source/API/galapagos.h"
#include "../../Source/API/galapagos_metadata.h"
#include "../../Source/Chromosomes/Vector/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/gaussian_mutation.h"
#include "../../Source/Chromosomes/Vector/randomization_mutation.h"
#include "../../Source/Chromosomes/Vector/kpoint_crossover.h"
#include "../../Source/SelectionAlgorithms/tournament_selection.h"
#include "../../Source/TerminationConditions/fitness_threshold.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE("simple equation solved", "[integration][vector-chromosome]") {
    // population metadata
    population_metadata* population_metadata = new population_metadata();
    population_metadata->size = 500;
    population_metadata->survival_rate = 0.25;
    population_metadata->distance_threshold = 0; //?
    population_metadata->cooperative_coevolution = false;

    // selection algorithm metadata
    selection_algorithm_metadata* selection_algorithm_metadata = new tournament_selection_metadata();
    selection_algorithm_metadata->tournament_size = 2;
    population_metadata->num_selection_algorithms = 1;
    population_metadata->selection_algorithm_metadata = new selection_algorithm_metadata*[0];
    population_metadata->selection_algorithm_metadata[0] = selection_algorithm_metadata;

    // termination condition metadata
    termination_condition_metadata* termination_condition_metadata = new fitness_threshold_metadata();
    termination_condition_metadata->fitness_threshold = 10; //?
    population_metadata->num_termination_conditions = 1;
    population_metadata->termination_condition_metadata = new termination_condition_metadata*[0];
    population_metadata->termination_condition_metadata[0] = termination_condition_metadata;

    // creature metadata
    creature_metadata* creature_metadata = new creature_metadata();
    population_metadata->creature_metadata = creature_metadata;
    population_metadata->creature_metadata->fitness_function = nullptr;

    // chromosome metadata
    chromosome_metadata = new vector_chromosome_metadata();
    creature_metadata->num_chromosomes = 1;
    creature_metadata->chromosome_metadata = new creature_metadata*[0];
    creature_metadata->chromosome_metadata[0] = chromosome_metadata;
    chromosome_metadata->name = "vars";

    // crossover metadata
    crossover_metadata* crossover_metadata = new kpoint_crossover_metadata();
    chromosome_metadata->crossover_rate = 1;
    chromosome_metadata->crossover_metadata = crossover_metadata;

    // invoke algorithm against metadata
    population* population = create_population(population_metadata);
    population->evolve();
}

// TODO: we should figure out what problem we want to use for throughput testing.
// we will probably want a different problem for each chromosome type as well as
// a few problems that excersise throughput with kchromosome creatures.
// example test problems: sudoko, tsp, nqueens, cart pole, ect.
