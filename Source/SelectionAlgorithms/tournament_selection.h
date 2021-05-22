#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include <memory>

#include "../API/galapagos.h"
#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

#include "API/selection_algorithm_metadata.h"

class tournament_selection : public selection_algorithm {
private:
    tournament_selection_metadata_ptr _metadata;
    stochastic& _stochastic_instance;

public:
  inline tournament_selection(tournament_selection_metadata_ptr metadata, stochastic& stochastic_instance) :
          _metadata{metadata}, _stochastic_instance{stochastic_instance} {}

  [[nodiscard]] std::shared_ptr<creature> invoke(const std::shared_ptr<const population>& population) const override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
