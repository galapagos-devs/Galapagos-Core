#ifndef _STOCHASTIC_INTERNAL_H_
#define _STOCHASTIC_INTERNAL_H_

#include "API/stochastic.h"

class stochastic_internal : public stochastic {
private:
    std::mt19937 _rng;

public:
    static stochastic_internal& get_instance(); // singleton access

    stochastic_internal();

    ~stochastic_internal() override;

    bool flip_coin() override;

    bool evaluate_probability(double probability) override;

    size_t weight_proportionate_selection(const double* const weights, size_t num_weights) override;

    int rand_int(int max) override;

    int rand_int(int min, int max) override;

    double rand_double() override;

    double rand_double(int max) override;

    double rand_double(int min, int max) override;

    double rand_gaussian(double mean, double standard_deviation) override;
};

#endif /* _STOCHASTIC_INTERNAL_H_ */
