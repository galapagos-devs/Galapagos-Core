#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <stdexcept>
#include <string>
#include <map>
#include <memory>

#include "chromosome.h"

class creature {
protected:
    std::map<std::string, std::shared_ptr<chromosome>> _chromosomes;  // TODO: Rename to `genome` and maybe make public.

public:
    virtual ~creature() = default;

    virtual double get_fitness() = 0;

    // TODO: Improve the ease of getting chromosomes
    template <class TChromosome> //TODO: Why does this have to be templated
    inline TChromosome* get_chromosome(const std::string& name) const {
        auto chromosome = _chromosomes.find(name)->second;
        return dynamic_cast<TChromosome*>(chromosome.get());
    }

    inline void set_chromosome(std::string name, chromosome* new_chromosome) {
        _chromosomes[name].reset(new_chromosome);
    }

    virtual creature* breed_with(const creature* const mate) const = 0;
};

#endif /* _CREATURE_H_ */
