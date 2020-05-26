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
    //region  creature metadata
    fitness_func_t fitness_function = [](creature* creature) {
        auto* X = creature->get_chromosome<vector_chromosome>("X");
        return X->get_gene(0) - X->get_gene(1) + X->get_gene(2);
    };
    std::vector<const chromosome_metadata_t*> chromosome_metadata;
    creature_metadata creature_metadata{fitness_function, chromosome_metadata};
    // endregion

    //region  chromosome metadata
    std::string name = "X";
    double crossover_rate = 1;
    std::vector<const crossover_metadata_t*> crossover_metadata;
    double mutation_rate = 0.5;
    std::vector<const mutation_metadata_t*> mutation_metadata;
    uint32_t norm_rank = 1;
    size_t chromosome_size = 3;
    double gene_infimum = -500;
    double gene_supremum = 500;
    chromosome_metadata.push_back(new vector_chromosome_metadata {
            name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata,
            norm_rank, chromosome_size, gene_infimum, gene_supremum
    });
    // endregion

    //region  crossover metadata
    double kpoint_crossover_weight = 1;
    size_t cut_points = 1;
    crossover_metadata.push_back(new kpoint_crossover_metadata {
        kpoint_crossover_weight, cut_points
    });
    // endregion

    //region mutation metadata
    double randomization_mutation_weight = 1;
    mutation_metadata.push_back(new randomization_mutation_metadata {
      randomization_mutation_weight
    });

    double gaussian_mutation_weight = 4;
    double mean = 0;
    double standard_deviation = 50;
    mutation_metadata.push_back(new gaussian_mutation_metadata {
       gaussian_mutation_weight, mean, standard_deviation
    });
    // endregion

    // region population metadata
    log_func_t log_function = [](log_entry entry) {
        std::cout << "generation: " << entry.generation << " optimal fitness: " << entry.optimal_fitness << std::endl;
    };
    size_t population_size = 25;
    double survival_rate = 0.25;
    double distance_threshold = 0;
    bool cooperative_coevolution = false;
    std::vector<const selection_algorithm_metadata_t*> selection_algorithm_metadata;
    std::vector<const termination_condition_metadata_t*> termination_condition_metadata;
    auto* population_metadata1 = new population_metadata{
            log_function, population_size, survival_rate, distance_threshold, cooperative_coevolution,
            selection_algorithm_metadata, termination_condition_metadata, creature_metadata
    };
    // endregion

    //region  selection algorithm metadata
    size_t tournament_size = 2;
    selection_algorithm_metadata.push_back(new tournament_selection_metadata {
       tournament_size
    });
    // endregion

    //region  termination condition metadata
    size_t fitness_threshold = 1500;
    termination_condition_metadata.push_back(new fitness_threshold_metadata {
       fitness_threshold
    });
    // endregion

    // invoke algorithm against metadata
    gc_core lib("Galapagos.dll");
    lib.initialize();

    population* population1 = lib.create_population(population_metadata1);
    population1->evolve();

    creature* optimal = population1->get_optimal_creature();
    auto* X = optimal->get_chromosome<vector_chromosome>("X");
    REQUIRE(X->get_gene(0) == gene_supremum);
    REQUIRE(X->get_gene(1) == gene_infimum);
    REQUIRE(X->get_gene(2) == gene_supremum);

    lib.delete_population(population1);
    lib.reset();
}

// TODO: we should figure out what problem we want to use for throughput testing.
// we will probably want a different problem for each chromosome type as well as
// a few problems that excersise throughput with kchromosome creatures.
// example test problems: sudoko, tsp, nqueens, cart pole, ect.
