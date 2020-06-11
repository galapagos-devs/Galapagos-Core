#ifndef _GALAPAGOS_CROSSOVER_INTERNAL_H_
#define _GALAPAGOS_CROSSOVER_INTERNAL_H_

#include <stdexcept>

#include "../API/crossover.h"

template<class TChromosome>
class crossover_internal : public crossover {
private:
    double _weight = 1;

public:
    inline crossover_internal(crossover_metadata* crossover_metadata) {
        _weight = crossover_metadata->weight;
    }

    inline double get_weight() override {
        return  _weight;
    };

    inline chromosome* invoke(chromosome* x, chromosome* y) override {
        auto* dynamic_x = dynamic_cast<TChromosome*>(x);
        auto* dynamic_y = dynamic_cast<TChromosome*>(y);
        if(dynamic_x == nullptr || dynamic_y == nullptr)
            throw std::runtime_error("invoke mismatched types");
        return invoke(dynamic_x, dynamic_y);
    }

protected:
    virtual chromosome* invoke(TChromosome* dynamic_x, TChromosome* dynamic_y) = 0;
};

#endif /* _GALAPAGOS_CROSSOVER_INTERNAL_H_ */
