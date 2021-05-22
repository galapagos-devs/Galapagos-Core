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
    inline std::shared_ptr<TChromosome> get_chromosome(const std::string& name) const {
        auto chromosome = _chromosomes.find(name)->second;
        return std::dynamic_pointer_cast<TChromosome>(chromosome);
    }

    inline void set_chromosome(const std::string& name, const std::shared_ptr<chromosome> new_chromosome) {
        _chromosomes[name] = new_chromosome;
    }

    virtual std::shared_ptr<creature> breed_with(const std::shared_ptr<const creature>& mate) const = 0;
};

#endif /* _CREATURE_H_ */
