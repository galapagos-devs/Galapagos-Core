#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <string>

#include "../../Source/API/chromosome.h"

class creature {
public:
	virtual double get_fitness() = 0;

	// TODO: can we use templates to avoid manual casts?
	virtual chromosome* get_chromosome(std::string name) = 0;

	virtual creature* breed_with(creature* other) = 0;
};


#endif /* _CREATURE_H_ */
