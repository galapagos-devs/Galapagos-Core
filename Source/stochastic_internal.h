#ifndef _STOCHASTIC_INTERNAL_H_
#define _STOCHASTIC_INTERNAL_H_

#include "API/stochastic.h"

class stochastic_internal : stochastic {
public:
	~stochastic_internal() override;

    uint32_t get_seed() override;

    bool flip_coin() override;

	bool evaluate_probability(double probability) override;

	size_t weight_proportionate_selection(double* weights, size_t num_weights) override;

	int rand_int(int max) override;

	int rand_int(int min, int max) override;

	double rand_double() override;

	double rand_double(int max) override;

	double rand_double(int min, int max) override;

	double rand_gaussian(double mean, double standard_deviation) override;
};

#endif /* _STOCHASTIC_INTERNAL_H_ */
