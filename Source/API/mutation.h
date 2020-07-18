#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "chromosome.h"
#include "genetic_operator.h"

class mutation : public genetic_operator {
public:
    virtual chromosome* invoke(const chromosome* const chromosome) const = 0;
};

#endif /* _MUTATION_H_ */
