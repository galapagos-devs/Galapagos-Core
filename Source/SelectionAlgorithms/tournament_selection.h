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
  const tournament_selection_metadata* _metadata;

public:
  tournament_selection(const tournament_selection_metadata* metadata, stochastic* stochastic_instance) :
      _stochastic_instance{stochastic_instance}, _metadata{metadata} {}

  ~tournament_selection() override = default;

  creature* invoke(population* population) override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
