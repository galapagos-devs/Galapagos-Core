#ifndef _GALAPAGOS_MUTATION_INTERNAL_H_
#define _GALAPAGOS_MUTATION_INTERNAL_H_

#include <stdexcept>
#include <memory>

#include "../API/mutation.h"

template <class TChromosome>
class mutation_internal : public mutation {
public:
    inline mutation_internal(const mutation_metadata& metadata) :
        mutation{metadata} {}

    inline const std::shared_ptr<chromosome> invoke(const std::shared_ptr<const chromosome> chromosome) const override {
        const std::shared_ptr<const TChromosome> dynamic = std::dynamic_pointer_cast<const TChromosome>(chromosome);
        if(dynamic == nullptr)
            throw std::runtime_error("mutation::invoke mismatched types");
        return invoke(dynamic);
    }

protected:
    virtual std::shared_ptr<chromosome> invoke(const std::shared_ptr<const TChromosome> chromosome) const = 0;
};

#endif /* _GALAPAGOS_MUTATION_INTERNAL_H_ */
