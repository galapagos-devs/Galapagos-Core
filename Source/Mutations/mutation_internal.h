//
// Created by kosie on 12/3/2019.
//

#ifndef _GALAPAGOS_MUTATION_INTERNAL_H_
#define _GALAPAGOS_MUTATION_INTERNAL_H_

#include <stdexcept>

#include "../API/mutation.h"

template <class TChromosome>
class mutation_internal : mutation {
public:
    inline chromosome* invoke(chromosome* chromosome) override {
        TChromosome* dynamic = dynamic_cast<TChromosome*>(chromosome);
        if(dynamic == nullptr)
            throw std::runtime_error("mutation::invoke mismatched types");
        return invoke(chromosome);
    }

protected:
    virtual chromosome* invoke(TChromosome* chromosome) = 0;
};

#endif /* _GALAPAGOS_MUTATION_INTERNAL_H_ */
