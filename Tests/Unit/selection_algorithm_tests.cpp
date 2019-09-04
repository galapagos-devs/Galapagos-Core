#include "../../Source/API/galapgos.h"
#include "../../Source/API/creature.h"
#include "../../Source/SelectionAlgorithms/tournament_selection.h"

int tournament_selection_test() {
  // TODO: how are we going to mock objects?
  stochastic* mocked_stochastic;
  population* mocked_population;

  galapagos_session& session = galapagos_session::get_instance();
  session.__stochastic__ = mocked_stochastic;

  size_t tournament_size = 2;
  tournament_selection selection_algorithm = tournament_selection(tournament_size);
  creature* selected_creature = selection_algorithm.invoke();

  size_t desired_creature_index = 0;
  creature* desired_creature = mocked_population[desired_creature_index];

  int error_code = 0; // TODO: should we define this in an enum? how does ctest expect error code.
  if(selected_creature != desired_creature)
    error_code = 1; //?

  delete mocked_stochastic;
  delete mocked_population;

  return error_code;
}
