#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include "creature.h"
#include "population.h"

class selection_algorithm {
public:
    virtual ~selection_algorithm() = default;

    virtual creature* invoke(const population* const population) const = 0;
    inline creature* operator()(const population* const population) const {
        return invoke(population);
    }
};

#endif /* _SELECTION_ALGORITHM_H_ */
