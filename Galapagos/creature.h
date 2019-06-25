#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "chromosome.h"
#include <string>

class creature {
public:
	virtual double get_fitness() = 0;
	
	// TODO: can we use templates to avoid manual casts?
	virtual chromosome* get_chromosome(std::string name) = 0;
};


#endif /* _CREATURE_H_ */