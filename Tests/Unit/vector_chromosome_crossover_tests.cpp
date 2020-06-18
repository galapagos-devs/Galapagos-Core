#include "../../Source/Chromosomes/Vector/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/kpoint_crossover.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

vector_chromosome_metadata* crossover_test_create_chromosome_metadata(size_t num_genes, double gene_infimum, double gene_supremum) {
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

TEST_CASE("k-point (vector) crossover invoked", "[unit][vector-chromosome][crossover][k-point-crossover]") {
    size_t cut_points = 2;

    size_t num_genes = 3;
    double gene_infimum = 0;
    double gene_supremum = 10;

    double chromosomeX_genes[3] = { 1, 2, 3 };
    double chromosomeY_genes[3] = { 4, 5, 6 };
    double desired_genes[3] = {
            chromosomeX_genes[0],
            chromosomeY_genes[1],
            chromosomeX_genes[2]
    };

    Mock<stochastic> stochastic_mock;
    When(OverloadedMethod(stochastic_mock, rand_double, double(int,int))).AlwaysReturn(0);
    When(OverloadedMethod(stochastic_mock, rand_int, int(int,int))).Return(1, 1, 2);
    stochastic* mocked_stochastic = &stochastic_mock.get();

    auto* chromosomeX_metadata = crossover_test_create_chromosome_metadata(num_genes, gene_infimum, gene_supremum);
    auto* chromosomeX = new vector_chromosome(chromosomeX_metadata, mocked_stochastic);
    chromosomeX->set_gene_slice(0, num_genes, chromosomeX_genes);

    auto* chromosomeY_metadata = crossover_test_create_chromosome_metadata(num_genes, gene_infimum, gene_supremum);
    auto* chromosomeY = new vector_chromosome(chromosomeY_metadata, mocked_stochastic);
    chromosomeY->set_gene_slice(0, num_genes, chromosomeY_genes);

    double weight = 1;
    auto* crossover_metadata = new kpoint_crossover_metadata{weight, cut_points};
    crossover* crossover = new kpoint_crossover(crossover_metadata, mocked_stochastic);

    auto* child = (vector_chromosome*)crossover->invoke(chromosomeX, chromosomeY);
    for(size_t i = 0; i < num_genes; i++)
        REQUIRE(child->get_gene(i) == desired_genes[i]);
    delete child;

    delete chromosomeX_metadata;
    delete chromosomeX;

    delete chromosomeY_metadata;
    delete chromosomeY;

    delete crossover;
    delete crossover_metadata;
}
