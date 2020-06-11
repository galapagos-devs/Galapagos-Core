#include <iostream>

#include "../../Source/API/galapagos.h"
#include "../../Source/API/galapagos_metadata.h"
#include "../../Source/galapagos_assemblies.h"
#include "../../Source/Chromosomes/Vector/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/gaussian_mutation.h"
#include "../../Source/Chromosomes/Vector/randomization_mutation.h"
#include "../../Source/Chromosomes/Vector/kpoint_crossover.h"
#include "../../Source/SelectionAlgorithms/tournament_selection.h"
#include "../../Source/TerminationConditions/fitness_threshold.h"

#include "../catch.hpp"

TEST_CASE("simple equation solved", "[integration][vector-chromosome]") {
    // population metadata
    auto* population_metadata1 = new population_metadata();
    population_metadata1->size = 25;
    population_metadata1->survival_rate = 0.25;
    population_metadata1->log_function = [](log_entry entry) {
        std::cout << "generation: " << entry.generation << " optimal fitness: " << entry.optimal_fitness << std::endl;
    };

    // selection algorithm metadata
    auto* tournament_selection_metadata1 = new tournament_selection_metadata();
    tournament_selection_metadata1->tournament_size = 2;

    population_metadata1->num_selection_algorithms = 1;
    population_metadata1->selection_algorithm_metadata = new selection_algorithm_metadata*[population_metadata1->num_selection_algorithms];
    population_metadata1->selection_algorithm_metadata[0] = tournament_selection_metadata1;

    // termination condition metadata
    auto* fitness_threshold_metadata1 = new fitness_threshold_metadata();
    fitness_threshold_metadata1->fitness_threshold = 1500;

    population_metadata1->num_termination_conditions = 1;
    population_metadata1->termination_condition_metadata = new termination_condition_metadata*[population_metadata1->num_termination_conditions];
    population_metadata1->termination_condition_metadata[0] = (termination_condition_metadata*)fitness_threshold_metadata1;

    // creature metadata
    auto* creature_metadata1 = new creature_metadata();
    creature_metadata1->fitness_function = [](creature* creature) {
        auto* X = creature->get_chromosome<vector_chromosome>("X");
        return X->get_gene(0) - X->get_gene(1) + X->get_gene(2);
    };

    population_metadata1->creature_metadata = creature_metadata1;

    // chromosome metadata
    auto* vector_chromosome_metadata1 = new vector_chromosome_metadata();
    vector_chromosome_metadata1->name = "X";
    vector_chromosome_metadata1->size = 3;
    vector_chromosome_metadata1->gene_infimum = -500;
    vector_chromosome_metadata1->gene_supremum = 500;
    vector_chromosome_metadata1->crossover_rate = 1;
    vector_chromosome_metadata1->mutation_rate = 0.5;

    creature_metadata1->num_chromosomes = 1;
    creature_metadata1->chromosome_metadata = new chromosome_metadata*[creature_metadata1->num_chromosomes];
    creature_metadata1->chromosome_metadata[0] = (chromosome_metadata*)vector_chromosome_metadata1;

    // crossover metadata
    auto* kpoint_crossover_metadata1 = new kpoint_crossover_metadata();
    kpoint_crossover_metadata1->cut_points = 1;

    vector_chromosome_metadata1->num_crossovers = 1;
    vector_chromosome_metadata1->crossover_metadata = new crossover_metadata*[vector_chromosome_metadata1->num_crossovers];
    vector_chromosome_metadata1->crossover_metadata[0] = (crossover_metadata*)kpoint_crossover_metadata1;

    // mutation metadata
    auto* randomization_mutation_metadata1 = new randomization_mutation_metadata();
    randomization_mutation_metadata1->weight = 1;

    auto* gaussian_mutation_metadata1 = new gaussian_mutation_metadata();
    gaussian_mutation_metadata1->weight = 4;
    gaussian_mutation_metadata1->mean = 0;
    gaussian_mutation_metadata1->standard_deviation = 50;

    vector_chromosome_metadata1->num_mutations = 2;
    vector_chromosome_metadata1->mutation_metadata = new mutation_metadata*[vector_chromosome_metadata1->num_mutations];
    vector_chromosome_metadata1->mutation_metadata[0] = (mutation_metadata*)randomization_mutation_metadata1;
    vector_chromosome_metadata1->mutation_metadata[1] = (mutation_metadata*)gaussian_mutation_metadata1;

    // invoke algorithm against metadata
    gc_core lib("Galapagos.dll");
    lib.initialize();

    population* population1 = lib.create_population(population_metadata1);
    population1->evolve();

    creature* optimal = population1->get_optimal_creature();
    auto* X = optimal->get_chromosome<vector_chromosome>("X");
    REQUIRE(X->get_gene(0) == vector_chromosome_metadata1->gene_supremum);
    REQUIRE(X->get_gene(1) == vector_chromosome_metadata1->gene_infimum);
    REQUIRE(X->get_gene(2) == vector_chromosome_metadata1->gene_supremum);

    lib.delete_population(population1);
    lib.reset();
}

// TODO: we should figure out what problem we want to use for throughput testing.
// we will probably want a different problem for each chromosome type as well as
// a few problems that excersise throughput with kchromosome creatures.
// example test problems: sudoko, tsp, nqueens, cart pole, ect.
