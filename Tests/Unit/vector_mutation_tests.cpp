//
// Created by kosie on 12/3/2019.
//

#include "../../Source/Chromosomes/vector_chromosome.h"
#include "../../Source/Mutations/gaussian_mutation.h"
#include "../../Source/Mutations/randomization_mutation.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE("gaussian mutation invoked", "[unit][vector-chromosome][mutation][gaussian-mutation]") {
    Mock<stochastic> stochastic_mock;
    stochastic* mocked_stochastic = &stochastic_mock.get();

    Mock<vector_chromosome> chromosome_mock;
    vector_chromosome* mocked_chromosome = &chromosome_mock.get();

    // TODO: what is the information flow for metadata?
    gaussian_mutation_metadata* mutation_metadata = new gaussian_mutation_metadata();
    mutation_metadata->height = 1;
    mutation_metadata->mean = 0;
    mutation_metadata->variance = 1;
    mutation* mutation = new gaussian_mutation(mutation_metadata, mocked_stochastic);

    vector_chromosome* mutated_chromosome = (vector_chromosome*)mutation->invoke(mocked_chromosome);
    delete mutated_chromosome;

    delete mutation;
    delete mutation_metadata;
}

TEST_CASE("randomization (vector) mutation invoked", "[unit][vector-chromosome][mutation][randomization-mutation]") {
    Mock<stochastic> stochastic_mock;
    stochastic* mocked_stochastic = &stochastic_mock.get();

    Mock<vector_chromosome> chromosome_mock;
    vector_chromosome* mocked_chromosome = &chromosome_mock.get();

    // TODO: what is the information flow for metadata?
    randomization_mutation_metadata* mutation_metadata = new randomization_mutation_metadata();
    mutation* mutation = new randomization_mutation(mutation_metadata, mocked_stochastic);

    vector_chromosome* mutated_chromosome = (vector_chromosome*)mutation->invoke(mocked_chromosome);
    delete mutated_chromosome;

    delete mutation;
    delete mutation_metadata;
}
