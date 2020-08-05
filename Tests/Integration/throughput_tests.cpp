#include <iostream>

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
    const std::string chromosome_name = "X";

    fitness_func_t fitness_function = [chromosome_name](creature* creature) {
        auto X = creature->get_chromosome<vector_chromosome>(chromosome_name);
        return X->get_gene(0) - X->get_gene(1) + X->get_gene(2);
    };

    log_func_t log_function = [](log_entry entry) {
        std::cout << "generation: " << entry.generation << " optimal fitness: " << entry.optimal_fitness << std::endl;
    };

    population_metadata metadata {
            log_function, 25, 0.25, 0, false,
            {tournament_selection_metadata{2}},
            {fitness_threshold_metadata{1500}},
            creature_metadata{fitness_function, {
                    vector_chromosome_metadata{
                            chromosome_name,
                            1, {kpoint_crossover_metadata{1, 1}},
                            0.5, {
                                    randomization_mutation_metadata{1},
                                    gaussian_mutation_metadata{4, 0, 50}
                            },
                            1, 3, -500, 500
                    }
            }}
    };

    // region Invoke Algorithm Against Metadata

    gc_core lib("Galapagos.dll");
    auto factory = lib.bootstrap();
    auto population = factory->create_population(metadata);
    population->evolve();

    auto optimal = population->get_optimal_creature();
    auto X = optimal->get_chromosome<vector_chromosome>(chromosome_name);
    REQUIRE(X->get_gene(0) == X->gene_sup());
    REQUIRE(X->get_gene(1) == X->gene_inf());
    REQUIRE(X->get_gene(2) == X->gene_sup());

    // endregion
}

// TODO: we should figure out what problem we want to use for throughput testing.
// we will probably want a different problem for each chromosome type as well as
// a few problems that exercise throughput with kchromosome creatures.
// example test problems: sudoko, tsp, nqueens, cart pole, ect.
