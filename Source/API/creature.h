#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <stdexcept>
#include <string>
#include <map>

#include "chromosome.h"

class creature {
protected:
    std::map<std::string, chromosome*> _chromosomes;  // TODO: Rename to `genome` and maybe make public.

public:
    virtual ~creature() = default;

    virtual double get_fitness() = 0;

    // TODO: Improve the ease of getting chromosomes
    template <class TChromosome> //TODO: Why does this have to be templated
    inline TChromosome* get_chromosome(const std::string& name) const {
        chromosome* chromosome = _chromosomes.find(name)->second;
        return dynamic_cast<TChromosome*>(chromosome);
    }

    inline void set_chromosome(std::string name, chromosome* new_chromosome) {
        delete _chromosomes[name];
        _chromosomes[name] = new_chromosome;
    }

    virtual creature* breed_with(const creature* const mate) const = 0;
};

#endif /* _CREATURE_H_ */
