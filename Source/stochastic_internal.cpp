#include <stdlib.h>
#include <stdexcept>
#include <random>

#include "stochastic_internal.h"

stochastic_internal::~stochastic_internal() { }

bool stochastic_internal::flip_coin() {
	return (rand_int(2) > 0);
}

bool stochastic_internal::evaulate_probability(double probability) {
	if (probability < 0 || probability > 1)
		throw std::runtime_error("evaulate_probability"); // TODO: how do we want to format exceptions. this should probably be a clean galapagos exception.

	double R = rand_percent();
	return R < probability;
}

int stochastic_internal::rand_int(int max) {
	return rand() % max;
}

int stochastic_internal::rand_int(int min, int max) {
	return rand() % (max - min + 1) + min;
}

double stochastic_internal::rand_percent() {
	// TODO: this will only work for compilers that support C++11. I think that is ok in 2019.
	std::mt19937 rng;
	std::uniform_real_distribution<double> dist(0, 1);
	return dist(rng);
}
