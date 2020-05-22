#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <stdexcept>
#include <string>
#include <map>

#include "chromosome.h"

class creature {
protected:
    std::map<std::string, chromosome*> _chromosomes;

public:
	virtual ~creature() = default;

	virtual double get_fitness() = 0;

	template <class TChromosome> //TODO: Why does this have to be templated
	inline TChromosome* get_chromosome(const std::string& name) {
        chromosome* chromosome =  _chromosomes[name];
        return dynamic_cast<TChromosome*>(chromosome);
	}
};

#endif /* _CREATURE_H_ */
