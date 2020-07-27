#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include <memory>

#include "../API/galapagos.h"
#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

struct tournament_selection_metadata : selection_algorithm_metadata {
    const size_t tournament_size;

    explicit tournament_selection_metadata(const size_t tournament_size) : tournament_size{tournament_size} {}

    inline std::shared_ptr<const selection_algorithm_metadata> copy() const override {
        std::shared_ptr<const selection_algorithm_metadata> ptr(new tournament_selection_metadata(
                this->tournament_size
        ));
        return ptr;
    }
};

class tournament_selection : public selection_algorithm {
private:
    const tournament_selection_metadata& _metadata;
    stochastic* _stochastic_instance;

public:
  tournament_selection(const tournament_selection_metadata& metadata, stochastic* stochastic_instance) :
          _metadata{metadata}, _stochastic_instance{stochastic_instance} {}

  const std::shared_ptr<creature> invoke(const std::shared_ptr<const population> population) const override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
