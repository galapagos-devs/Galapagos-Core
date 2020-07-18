#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include "../API/galapagos.h"
#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

struct tournament_selection_metadata : selection_algorithm_metadata {
    const size_t tournament_size;

    explicit tournament_selection_metadata(const size_t tournament_size) : tournament_size{tournament_size} {}
};

class tournament_selection : public selection_algorithm {
private:
  stochastic* _stochastic_instance;
  const tournament_selection_metadata* const _metadata;

public:
  tournament_selection(const tournament_selection_metadata* const metadata, stochastic* stochastic_instance) :
      _stochastic_instance{stochastic_instance}, _metadata{metadata} {}

  creature* invoke(const population* const population) const override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
