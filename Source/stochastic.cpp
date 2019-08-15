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
		// TODO: why can't we use std::exception?
		//if (probability < 0 || probability > 1)
		//	throw std::exception("evaulate_probability"); // TODO: how do we want to format exceptions. this should probably be a clean galapagos exception.

		double R = rand_percent();
		return R < probability;
	}

	int rand_int(int max) override {
		// TODO: why can't we call the rand() function?
		//return rand() % max;
		return 0; // temp!
	}

	int rand_int(int min, int max) override {
		// TODO: why can't we call the rand() function?
		//return rand() % (max - min + 1) + min;
		return 0; // temp!
	}

	double rand_percent() override {
		// TODO: why can't we use std::mt19937?
		// TODO: this will only work for compilers that support C++11. I think that is ok in 2019.
		//std::mt19937 rng;
		//std::uniform_real_distribution<double> dist(0, 1);
		//return dist(rng);
		return 0; // temp!
	}
};

#endif /* _STOCHASTIC_CPP_ */
