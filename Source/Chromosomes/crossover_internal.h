#ifndef _GALAPAGOS_CROSSOVER_INTERNAL_H_
#define _GALAPAGOS_CROSSOVER_INTERNAL_H_

#include <stdexcept>

#include "../API/crossover.h"

template<class TChromosome>
class crossover_internal : public crossover {
private:
    double _weight = 1;

public:
    inline crossover_internal(const crossover_metadata* crossover_metadata) {
        _weight = crossover_metadata->weight;
    }

    inline double get_weight() const override {
        return  _weight;
    };

    inline chromosome* invoke(const chromosome* const x, const chromosome* const y) const override {
        const auto* const dynamic_x = dynamic_cast<const TChromosome* const>(x);
        const auto* const dynamic_y = dynamic_cast<const TChromosome* const>(y);
        if(dynamic_x == nullptr || dynamic_y == nullptr)
            throw std::runtime_error("invoke mismatched types");
        return invoke(dynamic_x, dynamic_y);
    }

protected:
    virtual chromosome* invoke(const TChromosome* const dynamic_x, const TChromosome* const dynamic_y) const = 0;
};

#endif /* _GALAPAGOS_CROSSOVER_INTERNAL_H_ */
