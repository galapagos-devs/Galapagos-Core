#ifndef _GALAPAGOS_MUTATION_INTERNAL_H_
#define _GALAPAGOS_MUTATION_INTERNAL_H_

#include <stdexcept>

#include "../API/mutation.h"

template <class TChromosome>
class mutation_internal : public mutation {
private:
    double _weight = 1;

public:
    inline mutation_internal(const mutation_metadata* mutation_metadata) {
        _weight = mutation_metadata->weight;
    }

    inline double get_weight() override {
        return  _weight;
    };

    inline chromosome* invoke(chromosome* chromosome) override {
        TChromosome* dynamic = dynamic_cast<TChromosome*>(chromosome);
        if(dynamic == nullptr)
            throw std::runtime_error("mutation::invoke mismatched types");
        return invoke(dynamic);
    }

protected:
    virtual chromosome* invoke(TChromosome* chromosome) = 0;
};

#endif /* _GALAPAGOS_MUTATION_INTERNAL_H_ */
