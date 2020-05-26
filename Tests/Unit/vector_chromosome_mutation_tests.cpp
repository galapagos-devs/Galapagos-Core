#include "../../Source/Chromosomes/Vector/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/gaussian_mutation.h"
#include "../../Source/Chromosomes/Vector/randomization_mutation.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

vector_chromosome_metadata* mutation_test_create_chromosome_metadata(size_t num_genes, double gene_infimum, double gene_supremum) {
    std::string name = "";
    double crossover_rate = 0;
    std::vector<const crossover_metadata_t*> crossover_metadata;
    double mutation_rate = 0;
    std::vector<const mutation_metadata_t*> mutation_metadata;
    uint32_t norm_rank = 1;
    return new vector_chromosome_metadata {
            name, crossover_rate, crossover_metadata, mutation_rate, mutation_metadata,
            norm_rank, num_genes, gene_infimum, gene_supremum
    };
}

TEST_CASE("gaussian mutation invoked", "[unit][vector-chromosome][mutation][gaussian-mutation]") {
    double gaussian_perturbation = 1;

    size_t num_genes = 3;
    double gene_infimum = 0;
    double gene_supremum = 10;

    double chromosome_genes[3] = { 1, 2, 3 };
    size_t desired_gene_index = 1;
    double desired_gene_value = 3;

    Mock<stochastic> stochastic_mock;
    When(OverloadedMethod(stochastic_mock, rand_double, double(int,int))).AlwaysReturn(0);
    When(OverloadedMethod(stochastic_mock, rand_int, int(int))).AlwaysReturn(desired_gene_index);
    When(Method(stochastic_mock, rand_gaussian)).AlwaysReturn(gaussian_perturbation);
    stochastic* mocked_stochastic = &stochastic_mock.get();

    auto* chromosome_metadata = mutation_test_create_chromosome_metadata(num_genes, gene_infimum, gene_supremum);
    auto* chromosome = new vector_chromosome(chromosome_metadata, mocked_stochastic);
    chromosome->set_gene_slice(0, num_genes, chromosome_genes);

    double weight = 1;
    double mean = 0;
    double standard_deviation = 0;
    auto* mutation_metadata = new gaussian_mutation_metadata{weight, mean, standard_deviation};
    mutation* mutation = new gaussian_mutation(mutation_metadata, mocked_stochastic);

    auto* mutated_chromosome = (vector_chromosome*)mutation->invoke(chromosome);
    double desired_gene = mutated_chromosome->get_gene(desired_gene_index);
    REQUIRE(desired_gene == desired_gene_value);
    delete mutated_chromosome;

    delete chromosome_metadata;
    delete chromosome;

    delete mutation;
    delete mutation_metadata;
}

TEST_CASE("randomization (vector) mutation invoked", "[unit][vector-chromosome][mutation][randomization-mutation]") {
    size_t num_genes = 3;
    double gene_infimum = 0;
    double gene_supremum = 10;

    double gene0 = 5;
    double gene1 = 4;
    double gene2 = 3;
    double desired_genes[3] = { gene0, gene1, gene2 };

    Mock<stochastic> stochastic_mock;
    When(OverloadedMethod(stochastic_mock, rand_double, double(int,int))).Return(1,1,1,gene0,gene1,gene2);
    stochastic* mocked_stochastic = &stochastic_mock.get();

    auto* chromosome_metadata = mutation_test_create_chromosome_metadata(num_genes, gene_infimum, gene_supremum);
    auto* chromosome = new vector_chromosome(chromosome_metadata, mocked_stochastic);

    double weight = 1;
    auto* mutation_metadata = new randomization_mutation_metadata{weight};
    mutation* mutation = new randomization_mutation(mutation_metadata, mocked_stochastic);

    auto* mutated_chromosome = (vector_chromosome*)mutation->invoke(chromosome);
    for(size_t i = 0; i < num_genes; i++)
        REQUIRE(mutated_chromosome->get_gene(i) == desired_genes[i]);
    delete mutated_chromosome;

    delete chromosome_metadata;
    delete chromosome;

    delete mutation;
    delete mutation_metadata;
}
