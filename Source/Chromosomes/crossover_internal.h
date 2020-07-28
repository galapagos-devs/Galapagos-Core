#ifndef _GALAPAGOS_CROSSOVER_INTERNAL_H_
#define _GALAPAGOS_CROSSOVER_INTERNAL_H_

#include <stdexcept>
#include <memory>

#include "../API/crossover.h"

template<class TChromosome>
class crossover_internal : public crossover {
public:
    inline crossover_internal(const crossover_metadata& metadata) :
        crossover{metadata} {}

    inline std::shared_ptr<chromosome> invoke(const std::shared_ptr<const chromosome>& x, const std::shared_ptr<const chromosome>& y) const override {
        const auto dynamic_x = std::dynamic_pointer_cast<const TChromosome>(x);
        const auto dynamic_y = std::dynamic_pointer_cast<const TChromosome>(y);
        if(dynamic_x == nullptr || dynamic_y == nullptr)
            throw std::runtime_error("invoke mismatched types");
        return invoke(dynamic_x, dynamic_y);
    }

protected:
    virtual std::shared_ptr<chromosome> invoke(const std::shared_ptr<const TChromosome>& dynamic_x, const std::shared_ptr<const TChromosome>& dynamic_y) const = 0;
};

#endif /* _GALAPAGOS_CROSSOVER_INTERNAL_H_ */
