#ifndef _GALAPAGOS_MUTATION_INTERNAL_H_
#define _GALAPAGOS_MUTATION_INTERNAL_H_

#include <stdexcept>

#include "../API/mutation.h"

template <class TChromosome>
class mutation_internal : public mutation {
public:
    inline double get_weight() override {
        return  1; // TODO: how should this be reflected in the metadata?
    };

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
