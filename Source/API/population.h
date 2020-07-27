#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <cstdint>
#include <memory>

#include "creature.h"

class population {
public:
    virtual ~population() = default;

    virtual size_t get_size() const = 0;

    virtual const std::shared_ptr<creature> operator[] (int) const = 0;

    virtual const std::shared_ptr<creature> get_creature(int i) const = 0;  // get the ith creature.

    virtual const std::shared_ptr<creature> get_optimal_creature() const = 0;

    virtual void evolve() = 0;
};

#endif /* _POPULATION_H_ */
