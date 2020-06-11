#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include "../API/galapagos.h"
#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

struct tournament_selection_metadata : selection_algorithm_metadata {
	size_t tournament_size;
};

class tournament_selection : public selection_algorithm {
private:
  stochastic* _stochastic_instance;
  size_t _tournament_size;

public:
  tournament_selection(stochastic* stochastic_instance, tournament_selection_metadata* metadata);

  ~tournament_selection() override;

  creature* invoke(population* population) override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
