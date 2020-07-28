#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include <memory>

#include "chromosome.h"
#include "genetic_operator.h"

class crossover : public genetic_operator {
public:
    inline crossover(const crossover_metadata& metadata) :
        genetic_operator{metadata} {}

    virtual std::shared_ptr<chromosome> invoke(const std::shared_ptr<const chromosome>& x, const std::shared_ptr<const chromosome>& y) const = 0;
    inline std::shared_ptr<chromosome> operator()(const std::shared_ptr<const chromosome>& x, const std::shared_ptr<const chromosome>& y) const {
        return invoke(x, y);
    }
};

#endif /* _CROSSOVER_H_ */
