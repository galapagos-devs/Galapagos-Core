#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include "../API/selection_algorithm.h"

class tournament_selection : selection_algorithm {
private:
  size_t _tournament_size;

public:
  tournament_selection(size_t tournament_size);

  ~tournament_selection();

  creature* invoke(population* population) override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
