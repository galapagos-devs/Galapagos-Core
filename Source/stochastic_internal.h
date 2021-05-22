#ifndef _STOCHASTIC_INTERNAL_H_
#define _STOCHASTIC_INTERNAL_H_

#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <random>
#include <numeric>

#include "API/stochastic.h"

class stochastic_internal : public stochastic {
private:
    std::mt19937 _rng;

public:
    inline static stochastic_internal& get_instance() {
        static stochastic_internal instance;
        return instance;
    }

    inline stochastic_internal() {
        _rng.seed(std::time(0));
    }

    inline bool flip_coin() override {
        return (rand_int(2) > 0);
    }

    inline bool evaluate_probability(double probability) override {
        if (probability < 0 || probability > 1)
            throw std::runtime_error("evaluate_probability"); // TODO: how do we want to format exceptions. this should probably be a clean galapagos_bootstrap exception.

        double R = rand_double();
        return R < probability;
    }

    inline size_t weight_proportionate_selection(std::vector<double> weights) override {
        double sum = 0;
        sum = std::accumulate(weights.begin(), weights.end(), sum);

        double probability_capital = rand_double() * sum;

        auto num_weights = weights.size();
        for(size_t i = 0; i < num_weights; i++) {
            probability_capital -= weights[i];

            if(probability_capital <= 0)
                return i;
        }
        throw std::runtime_error("weight_proportionate_selection");
    }

    inline int rand_int(int max) override {
        return rand_int(0, max);
    }

    inline int rand_int(int min, int max) override {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(_rng);
    }

    inline double rand_double() override {
        return rand_double(0, 1);
    }

    inline double rand_double(int max) override {
        return rand_double(0, max);
    }

    inline double rand_double(int min, int max) override {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(_rng);
    }

    inline double rand_gaussian(double mean, double standard_deviation) override {
        std::normal_distribution<double> dist(mean, standard_deviation);
        return dist(_rng);
    }
};

#endif /* _STOCHASTIC_INTERNAL_H_ */
