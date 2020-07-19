#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "chromosome.h"
#include "genetic_operator.h"

class mutation : public genetic_operator {
public:
    inline mutation(const mutation_metadata& metadata) :
        genetic_operator{metadata} {}

    virtual chromosome* invoke(const chromosome* const chromosome) const = 0;
    inline chromosome* operator()(const chromosome* const chromosome) const {
        return invoke(chromosome);
    }
};

#endif /* _MUTATION_H_ */
