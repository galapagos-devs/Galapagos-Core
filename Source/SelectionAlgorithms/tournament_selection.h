#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

<<<<<<< HEAD
#include "../API/galapagos.h"
=======
#include <functional>

>>>>>>> origin/integration
#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

struct tournament_selection_metadata : selection_algorithm_metadata {
	size_t tournament_size;
};

class tournament_selection : selection_algorithm {
private:
  stochastic* _stochastic_instance;
  size_t _tournament_size;

public:
  tournament_selection(stochastic* stochastic_instance, size_t tournament_size);

  ~tournament_selection();

  creature* invoke(population* population) override;
};

GALAPAGOS_API tournament_selection_metadata* create_tournament_selection_metadata();
GALAPAGOS_API void delete_tournament_selection_metadata(tournament_selection_metadata* tournament_selection_metadata);

GALAPAGOS_API void set_tournament_selection_metadata_tournament_size(tournament_selection_metadata* tournament_selection_metadata, size_t tournament_size);
GALAPAGOS_API size_t get_tournament_selection_metadata_tournament_size(tournament_selection_metadata* tournament_selection_metadata);

#endif /* _TOURNAMENT_SELECTION_H_ */
