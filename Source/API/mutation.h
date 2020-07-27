#ifndef _MUTATION_H_
#define _MUTATION_H_

#include <memory>

#include "chromosome.h"
#include "genetic_operator.h"

class mutation : public genetic_operator {
public:
    inline mutation(const mutation_metadata& metadata) :
        genetic_operator{metadata} {}

    virtual const std::shared_ptr<chromosome> invoke(const std::shared_ptr<const chromosome> chromosome) const = 0;
    inline const std::shared_ptr<chromosome> operator()(const std::shared_ptr<const chromosome> chromosome) const {
        return invoke(chromosome);
    }
};

#endif /* _MUTATION_H_ */
