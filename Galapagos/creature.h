#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "chromosome.h"
#include <string>

class creature {
public:
	virtual double get_fitness() abstract;
	
	// TODO: can we use templates to avoid manual casts?
	virtual chromosome* get_chromosome(std::string name) abstract;
};


#endif /* _CREATURE_H_ */