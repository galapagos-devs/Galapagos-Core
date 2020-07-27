#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include <memory>

#include "chromosome.h"
#include "population.h"

class termination_condition {
public:
    virtual ~termination_condition() = default;

    virtual bool invoke(const std::shared_ptr<const population> population) const = 0;
    inline bool operator()(const std::shared_ptr<const population> population) const {
        return invoke(population);
    }
};

#endif /* _TERMINATION_CONDITION_H_ */
