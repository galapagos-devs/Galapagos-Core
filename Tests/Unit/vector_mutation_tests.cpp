#include "../../Source/Chromosomes/Vector/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/gaussian_mutation.h"
#include "../../Source/Chromosomes/Vector/randomization_mutation.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE("gaussian mutation invoked", "[unit][vector-chromosome][mutation][gaussian-mutation]") {
    size_t desired_gene_index = 0;
    double desired_gene_value = 3;

    double gaussian_mean = 0;
    double gaussian_standard_deviation = 1;

    Mock<stochastic> stochastic_mock;
    When(OverloadedMethod(stochastic_mock, rand_int, int(int))).AlwaysReturn(0);
    When(Method(stochastic_mock, rand_gaussian)).AlwaysReturn(0);
    stochastic* mocked_stochastic = &stochastic_mock.get();

    Mock<vector_chromosome> chromosome_mock;
    When(Method(chromosome_mock, gene_inf)).AlwaysReturn(0);
    vector_chromosome* mocked_chromosome = &chromosome_mock.get();

    gaussian_mutation_metadata* mutation_metadata = new gaussian_mutation_metadata();
    mutation_metadata->mean = gaussian_mean;
    mutation_metadata->standard_deviation = gaussian_standard_deviation;
    mutation* mutation = new gaussian_mutation(mutation_metadata, mocked_stochastic);

    vector_chromosome* mutated_chromosome = (vector_chromosome*)mutation->invoke(mocked_chromosome);
    double desired_gene = mutated_chromosome->get_gene(desired_gene_index);
    REQUIRE(desired_gene == desired_gene_value);
    delete mutated_chromosome;

    delete mutation;
    delete mutation_metadata;
}

TEST_CASE("randomization (vector) mutation invoked", "[unit][vector-chromosome][mutation][randomization-mutation]") {
    size_t desired_gene_index = 0;
    double desired_gene_value = 0;

    Mock<stochastic> stochastic_mock;
    stochastic* mocked_stochastic = &stochastic_mock.get();

    Mock<vector_chromosome> chromosome_mock;
    vector_chromosome* mocked_chromosome = &chromosome_mock.get();

    randomization_mutation_metadata* mutation_metadata = new randomization_mutation_metadata();
    mutation* mutation = new randomization_mutation(mutation_metadata, mocked_stochastic);

    vector_chromosome* mutated_chromosome = (vector_chromosome*)mutation->invoke(mocked_chromosome);
    double desired_gene = mutated_chromosome->get_gene(desired_gene_index);
    REQUIRE(desired_gene == desired_gene_value);
    delete mutated_chromosome;

    delete mutation;
    delete mutation_metadata;
}
