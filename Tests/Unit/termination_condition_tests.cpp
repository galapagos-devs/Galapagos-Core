#include "../../Source/API/creature.h"
#include "../../Source/API/population.h"
#include "../../Source/TerminationConditions/fitness_threshold.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE("fitness-threshold invoked", "[unit][termination-condition][fitness-threshold]") {
  size_t test_fitness_threshold = 2;

  Mock<creature> creature_mock;
  When(Method(creature_mock, get_fitness)).Return(1,2,3);
  std::shared_ptr<creature> mocked_creature(&creature_mock.get(), [](creature*){});

  Mock<population> population_mock;
  When(Method(population_mock, get_optimal_creature)).AlwaysReturn(mocked_creature);
  std::shared_ptr<population> mocked_population(&population_mock.get(), [](population*){});

  auto termination_condition_metadata = fitness_threshold_metadata_ptr(new fitness_threshold_metadata{test_fitness_threshold});
  fitness_threshold termination_condition(termination_condition_metadata);

  REQUIRE(!termination_condition.invoke(mocked_population));  // Checks fitness < threshold
  REQUIRE(termination_condition.invoke(mocked_population));  // Checks fitness == threshold
  REQUIRE(termination_condition.invoke(mocked_population));  // Checks fitness > threshold
}
