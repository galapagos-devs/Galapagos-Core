#ifndef _STOCHASTIC_H_
#define _STOCHASTIC_H_

#include <vector>

/*! Brief Description of the stochastic_internal class.
 *  This is the detailed description it is SuPoSeD tO Be LoNgEr.
 *
 */
class stochastic {
public:
    virtual ~stochastic() = default;

    virtual bool flip_coin() = 0; //!< Is either *true* or **false**.

    virtual bool evaluate_probability(double probability) = 0;

    virtual size_t weight_proportionate_selection(std::vector<double> weights) = 0;

    virtual int rand_int(int max) = 0;

    virtual int rand_int(int min, int max) = 0;

    // FIXME: `rand_double` methods should take `double`s as `min` and `max`
    virtual double rand_double() = 0;

    virtual double rand_double(int max) = 0;

    virtual double rand_double(int min, int max) = 0;

    virtual double rand_gaussian(double mean, double standard_deviation) = 0;
};

#endif /* _STOCHASTIC_H_ */
