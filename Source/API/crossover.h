#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "chromosome.h"
#include "genetic_operator.h"

class crossover : public genetic_operator {
public:
    virtual chromosome* invoke(const chromosome* const x, const chromosome* const y) const = 0;
};

#endif /* _CROSSOVER_H_ */
