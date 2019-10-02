#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>

#include "../API/termination_condition.h"

class fitness_threshold : termination_condition {
private:
  size_t _fitness_threshold;

public:
  fitness_threshold(size_t fitness_threshold);

  ~fitness_threshold();

  bool operator()(population* population) override;
  bool invoke(population* population) override;
};

#endif /* _FITNESS_THRESHOLD_H_ */
