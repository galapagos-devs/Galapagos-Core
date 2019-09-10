#include "../../Source/API/galapgos.h"
#include "../../Source/API/creature.h"
#include "../../Source/SelectionAlgorithms/tournament_selection.h"

#include "../fakeit.hpp"

int tournament_selection_test() {
  size_t tournament_size = 2;
  int desired_creature_index = 1;

  Mock<stochastic> stochastic_mock;
  When(Method(stochastic_mock, rand_int)).Return(0,0,1);
  stochastic* mocked_stochastic = (stochastic*)stochastic_mock.get();

  Mock<creature> creature_mock1;
  When(Method(creature_mock1, get_fitness)).AlwaysReturn(1);
  creature* mocked_creature1 (creature*)creature_mock1.get();

  Mock<creature> creature_mock2;
  When(Method(creature_mock2, get_fitness)).AlwaysReturn(2);
  creature* mocked_creature2 (creature*)creature_mock2.get();

  Mock<population> population_mock;
  When(Method(population_mock, get_size)).AlwaysReturn(2);
  When(Method(population_mock, get_creature)).AlwaysDo([](int i) {
    return i == 0 ? mocked_creature1 : mocked_creature2;
  });
  population* mocked_population = (population*)population_mock.get();

  galapagos_session& session = galapagos_session::get_instance();
  session.__stochastic__ = mocked_stochastic;

  tournament_selection selection_algorithm = tournament_selection(tournament_size);
  creature* selected_creature = selection_algorithm.invoke();
  creature* desired_creature = mocked_population.get_creature(desired_creature_index);

  int error_code = 0; // TODO: should we define this in an enum? how does ctest expect error code.
  if(selected_creature != desired_creature)
    error_code = 1; //?

  delete mocked_stochastic;
  delete mocked_creature1;
  delete mocked_creature2;
  delete mocked_population;

  return error_code;
}
