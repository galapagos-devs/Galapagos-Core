//
// Created by kosie on 11/19/2019.
//

#ifndef GALAPAGOS_CHROMOSOME_INTERNAL_H
#define GALAPAGOS_CHROMOSOME_INTERNAL_H

#include <stdexcept>

#include "../API/chromosome.h"

template<class TChromosome>
class chromosome_internal : chromosome {
public:
    inline double get_distance(chromosome* other) override {
        TChromosome* dynamic = dynamic_cast<TChromosome*>(other);
        if(dynamic == nullptr)
            throw std::runtime_error("get_distance mismatched types");
        return  get_distance(dynamic);
    }

protected:
    virtual double get_distance(TChromosome* other) = 0;
};

#endif //GALAPAGOS_CHROMOSOME_INTERNAL_H
