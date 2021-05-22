#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include <memory>

#include "creature.h"
#include "population.h"

class selection_algorithm {
public:
    virtual ~selection_algorithm() = default;

    virtual std::shared_ptr<creature> invoke(const std::shared_ptr<const population>& population) const = 0;
    inline std::shared_ptr<creature> operator()(const std::shared_ptr<const population>& population) const {
        return invoke(population);
    }
};

#endif /* _SELECTION_ALGORITHM_H_ */
