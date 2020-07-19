#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "chromosome.h"
#include "genetic_operator.h"

class crossover : public genetic_operator {
public:
    inline crossover(const crossover_metadata& metadata) :
        genetic_operator{metadata} {}

    virtual chromosome* invoke(const chromosome* const x, const chromosome* const y) const = 0;
    inline chromosome* operator()(const chromosome* const x, const chromosome* const y) const {
        return invoke(x, y);
    }
};

#endif /* _CROSSOVER_H_ */
