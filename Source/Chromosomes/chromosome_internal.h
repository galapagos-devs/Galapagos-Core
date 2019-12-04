//
// Created by kosie on 11/19/2019.
//

#ifndef _GALAPAGOS_CHROMOSOME_INTERNAL_H_
#define _GALAPAGOS_CHROMOSOME_INTERNAL_H_

#include <stdexcept>

#include "../API/chromosome.h"

template<class TChromosome>
class chromosome_internal : public chromosome {
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

#endif /* _GALAPAGOS_CHROMOSOME_INTERNAL_H_ */
