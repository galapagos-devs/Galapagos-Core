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

    // region Construct Metadata
    // region Creature Metadata

    // region Mutation/Crossover Metadata
    std::vector<const crossover_metadata_t*> crossover_metadata = {
            new kpoint_crossover_metadata(1, 1)
    };

    std::vector<const mutation_metadata_t*> mutation_metadata = {
            new randomization_mutation_metadata(1),
            new gaussian_mutation_metadata(4, 0, 50)
    };
    // endregion

    // region Chromosome Metadata

    const std::string chromosome_name = "X";
    double gene_supremum = 500;
    double gene_infimum = -500;
    std::vector<const chromosome_metadata_t*> chromosome_metadata = {
            new vector_chromosome_metadata(
                    chromosome_name,
                    1, crossover_metadata,
                    0.5, mutation_metadata,
                    1, 3, gene_infimum, gene_supremum)
    };
    // endregion

    fitness_func_t fitness_function = [chromosome_name](creature* creature) {
        auto* X = creature->get_chromosome<vector_chromosome>(chromosome_name);
        return X->get_gene(0) - X->get_gene(1) + X->get_gene(2);
    };
    creature_metadata creature_metadata(fitness_function, chromosome_metadata);
    // endregion

    // region Population Metadata

    std::vector<const selection_algorithm_metadata_t*> selection_algorithm_metadata = {
            new tournament_selection_metadata(2)
    };

    std::vector<const termination_condition_metadata_t*> termination_condition_metadata = {
            new fitness_threshold_metadata(1500)
    };

    log_func_t log_function = [](log_entry entry) {
        std::cout << "generation: " << entry.generation << " optimal fitness: " << entry.optimal_fitness << std::endl;
    };
    auto* population_metadata1 = new population_metadata(log_function,
            25, 0.25, 0, false,
            selection_algorithm_metadata, termination_condition_metadata, creature_metadata);

    // endregion
    // endregion

    // region Invoke Algorithm Against Metadata

    gc_core lib("Galapagos.dll");
    lib.initialize();

    population* population1 = lib.create_population(population_metadata1);
    population1->evolve();

    creature* optimal = population1->get_optimal_creature();
    auto* X = optimal->get_chromosome<vector_chromosome>(chromosome_name);
    REQUIRE(X->get_gene(0) == gene_supremum);
    REQUIRE(X->get_gene(1) == gene_infimum);
    REQUIRE(X->get_gene(2) == gene_supremum);

    lib.delete_population(population1);
    lib.reset();
    // endregion
}

// TODO: we should figure out what problem we want to use for throughput testing.
// we will probably want a different problem for each chromosome type as well as
// a few problems that exercise throughput with kchromosome creatures.
// example test problems: sudoko, tsp, nqueens, cart pole, ect.
