#include "../../Source/Chromosomes/Vector/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/kpoint_crossover.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE("k-point (vector) crossover invoked", "[unit][vector-chromosome][crossover][k-point-crossover]") {
    double chromosomeX_genes[3] = { 1, 2, 3 };
    double chromosomeY_genes[3] = { 4, 5, 6 };
    double desired_genes[3] = {
            chromosomeX_genes[0],
            chromosomeY_genes[1],
            chromosomeX_genes[2]
    };

    size_t num_genes = 3;
    size_t cut_points = 2;

    Mock<stochastic> stochastic_mock;
    When(OverloadedMethod(stochastic_mock, rand_double, double(int,int))).AlwaysReturn(0);
    When(OverloadedMethod(stochastic_mock, rand_int, int(int,int))).Return(1, 1, 2);
    stochastic* mocked_stochastic = &stochastic_mock.get();

    auto* chromosomeX_metadata = new vector_chromosome_metadata();
    chromosomeX_metadata->size = num_genes;
    chromosomeX_metadata->gene_infimum = 0;
    chromosomeX_metadata->gene_supremum = 10;
    auto* chromosomeX = new vector_chromosome(mocked_stochastic, chromosomeX_metadata);
    chromosomeX->set_gene_slice(0, num_genes, chromosomeX_genes);

    auto* chromosomeY_metadata = new vector_chromosome_metadata();
    chromosomeY_metadata->size = num_genes;
    chromosomeY_metadata->gene_infimum = 0;
    chromosomeY_metadata->gene_supremum = 10;
    auto* chromosomeY = new vector_chromosome(mocked_stochastic, chromosomeY_metadata);
    chromosomeY->set_gene_slice(0, num_genes, chromosomeY_genes);

    auto* crossover_metadata = new kpoint_crossover_metadata();
    crossover_metadata->cut_points = cut_points;
    crossover* crossover = new kpoint_crossover(mocked_stochastic, crossover_metadata);

    auto* child = (vector_chromosome*)crossover->invoke(chromosomeX, chromosomeY);
    for(size_t i = 0; i < num_genes; i++)
        REQUIRE(child->get_gene(i) == desired_genes[i]);

    delete crossover;
    delete crossover_metadata;
}
