#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include <functional>

#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

class tournament_selection : selection_algorithm {
private:
  stochastic* _stochastic_instance;
  size_t _tournament_size;

public:
  tournament_selection(stochastic* stochastic_instance, size_t tournament_size);

  ~tournament_selection();

  creature* invoke(population* population) override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
