#include <vector>
#include <memory>

#include "../../Source/Chromosomes/Vector/API/vector_chromosome.h"
#include "../../Source/Chromosomes/Vector/kpoint_crossover.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE("k-point (vector) crossover invoked", "[unit][vector-chromosome][crossover][k-point-crossover]") {
    size_t cut_points = 2;

    size_t num_genes = 3;
    double gene_infimum = 0;
    double gene_supremum = 10;

    std::vector<double> chromosomeX_genes{1, 2, 3};
    std::vector<double> chromosomeY_genes{4, 5, 6};
    std::vector<double> desired_genes{
            chromosomeX_genes[0],
            chromosomeY_genes[1],
            chromosomeX_genes[2]
    };

    Mock<stochastic> stochastic_mock;
    When(OverloadedMethod(stochastic_mock, rand_double, double(int, int))).AlwaysReturn(0);
    When(OverloadedMethod(stochastic_mock, rand_int, int(int, int))).Return(1, 1, 2);
    stochastic& mocked_stochastic = stochastic_mock.get();

    auto chromosomeX_metadata = vector_chromosome_metadata_ptr(
            new vector_chromosome_metadata{
                    "X",
                    0, {}, 0, {}, 1,
                    num_genes, gene_infimum, gene_supremum}
    );
    auto chromosomeX = std::make_shared<vector_chromosome>(chromosomeX_metadata, mocked_stochastic);
    chromosomeX->set_gene_slice(0, num_genes, chromosomeX_genes);

    auto chromosomeY_metadata = vector_chromosome_metadata_ptr(
            new vector_chromosome_metadata{
                    "Y",
                    0, {}, 0, {}, 1,
                    num_genes, gene_infimum, gene_supremum}
    );
    auto chromosomeY = std::make_shared<vector_chromosome>(chromosomeY_metadata, mocked_stochastic);
    chromosomeY->set_gene_slice(0, num_genes, chromosomeY_genes);

    double weight = 1;
    auto crossover_metadata = kpoint_crossover_metadata_ptr(
            new kpoint_crossover_metadata{weight, cut_points}
            );
    std::shared_ptr<crossover> crossover = std::make_shared<kpoint_crossover>(crossover_metadata, mocked_stochastic);

    std::shared_ptr<chromosome> x = chromosomeX;
    std::shared_ptr<chromosome> y = chromosomeY;
    auto child = std::dynamic_pointer_cast<vector_chromosome>(crossover->invoke(chromosomeX, chromosomeY));
    for (size_t i = 0; i < num_genes; i++)
        REQUIRE(child->get_gene(i) == desired_genes[i]);
}
