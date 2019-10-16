#ifndef _FITNESS_THRESHOLD_H_
#define _FITNESS_THRESHOLD_H_

#include <cstdint>

#include "../API/galapagos.h"
#include "../API/termination_condition.h"

struct fitness_threshold_metadata : selection_algorithm_metadata {
	size_t fitness_threshold;
};

class fitness_threshold : termination_condition {
private:
  size_t _fitness_threshold;

public:
  fitness_threshold(size_t fitness_threshold);

  ~fitness_threshold();

  bool operator()(population* population) override;
  bool invoke(population* population) override;
};

GALAPAGOS_API fitness_threshold_metadata* create_fitness_threshold_metadata();
GALAPAGOS_API void delete_fitness_threshold_metadata(fitness_threshold_metadata* fitness_threshold_metadata);

GALAPAGOS_API void set_fitness_threshold_metadata_fitness_threshold(fitness_threshold_metadata* fitness_threshold_metadata, size_t fitness_threshold);
GALAPAGOS_API size_t get_fitness_threshold_metadata_fitness_threshold(fitness_threshold_metadata* fitness_threshold_metadata);

#endif /* _FITNESS_THRESHOLD_H_ */
