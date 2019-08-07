#ifndef _STOCHASTIC_CPP_
#define _STOCHASTIC_CPP_

#include "API/stochastic.h"

#include <stdlib.h>
#include <exception>
#include <random>


class stochastic_internal : stochastic {
public:
	bool flip_coin() override {
		return (rand_int(2) > 0);
	}

	bool evaulate_probability(double probability) {
		if (probability < 0 || probability > 1)
			throw std::exception("evaulate_probability"); // TODO: how do we want to format exceptions. this should probably be a clean galapagos exception.

		double R = rand_percent();
		return R < probability;
	}

	int rand_int(int max) override {
		return rand() % max;
	}

	int rand_int(int min, int max) override {
		return rand() % (max - min + 1) + min;
	}

	double rand_percent() override {
		// TODO: this will only work for compilers that support C++11. I think that is ok in 2019.
		std::mt19937 rng;
		std::uniform_real_distribution<double> dist(0, 1);
		return dist(rng);
	}
};

#endif /* _STOCHASTIC_CPP_ */
