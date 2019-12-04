#include "stochastic_internal.h"

stochastic_internal::~stochastic_internal() = default;

uint32_t stochastic_internal::get_seed() {
    return time(0);
}

bool stochastic_internal::flip_coin() {
	return (rand_int(2) > 0);
}

bool stochastic_internal::evaluate_probability(double probability) {
	if (probability < 0 || probability > 1)
		throw std::runtime_error("evaluate_probability"); // TODO: how do we want to format exceptions. this should probably be a clean galapagos exception.

	double R = rand_double();
	return R < probability;
}

size_t stochastic_internal::weight_proportionate_selection(double* weights, size_t num_weights) {
    double sum = std::accumulate(weights, weights + num_weights, 0);
    double probability_capital = rand_double() * sum;

    for(size_t i = 0; i < num_weights; i++) {
        probability_capital -= weights[i];

        if(probability_capital <= 0)
            return i;
    }
    throw std::runtime_error("weight_proportionate_selection");
}

int stochastic_internal::rand_int(int max) {
	return rand_int(0, max);
}

int stochastic_internal::rand_int(int min, int max) {
    std::mt19937 rng(get_seed());
    std::uniform_real_distribution<double> dist(min, max);
	return dist(rng);
}

double stochastic_internal::rand_double() {
    return rand_double(0, 1);
}

double stochastic_internal::rand_double(int max) {
    return rand_double(0, max);
}

double stochastic_internal::rand_double(int min, int max) {
	std::mt19937 rng(get_seed());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(rng);
}

double stochastic_internal::rand_gaussian(double mean, double standard_deviation) {
    std::mt19937 rng(get_seed());
    std::normal_distribution<double> dist(mean, standard_deviation);
    return dist(rng);
}
