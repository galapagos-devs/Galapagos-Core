#ifndef _STOCHASTIC_INTERNAL_H_
#define _STOCHASTIC_INTERNAL_H_

#include "API/stochastic.h"

class stochastic_internal : stochastic {
public:
	~stochastic_internal();

  bool flip_coin();

	bool evaulate_probability(double probability);

	int rand_int(int max) override;

	int rand_int(int min, int max) override;

	double rand_percent() override;
};

#endif /* _STOCHASTIC_INTERNAL_H_ */
