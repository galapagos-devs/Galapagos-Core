#include <memory>

#include "../../Source/API/galapagos.h"
#include "../../Source/API/creature.h"
#include "../../Source/SelectionAlgorithms/tournament_selection.h"

#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace fakeit;

TEST_CASE( "tournament-selection invoked", "[unit][selection-algorithm][tournament-selection]" ) {
  size_t test_tournament_size = 2;
  int desired_creature_index = 1;

  Mock<stochastic> stochastic_mock;
  When(OverloadedMethod(stochastic_mock, rand_int, int(int))).Return(0,0,1);
  stochastic* mocked_stochastic = &stochastic_mock.get();

  Mock<creature> creature_mock0;
  When(Method(creature_mock0, get_fitness)).AlwaysReturn(1);
  std::shared_ptr<creature> mocked_creature0(&creature_mock0.get(), [](creature*){});

  Mock<creature> creature_mock1;
  When(Method(creature_mock1, get_fitness)).AlwaysReturn(2);
  std::shared_ptr<creature> mocked_creature1(&creature_mock1.get(), [](creature*){});

  Mock<population> population_mock;
  When(Method(population_mock, get_size)).AlwaysReturn(2);
  When(Method(population_mock, get_creature)).AlwaysDo([mocked_creature0, mocked_creature1](int i) {
    return i == 0 ? mocked_creature0 : mocked_creature1;
  });
  std::shared_ptr<population> mocked_population(&population_mock.get(), [](population*){});

  tournament_selection_metadata selection_algorithm_metadata{test_tournament_size};
  tournament_selection selection_algorithm(selection_algorithm_metadata, mocked_stochastic);
  auto selected_creature = selection_algorithm.invoke(mocked_population);
  auto desired_creature = mocked_population->get_creature(desired_creature_index);

  REQUIRE(selected_creature == desired_creature);
}
