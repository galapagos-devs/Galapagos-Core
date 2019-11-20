#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <string>

#include "chromosome.h"

class creature {
public:
	virtual ~creature() = 0;

	virtual double get_fitness() = 0;

	// TODO: can we use templates to avoid manual casts?
	virtual chromosome* get_chromosome(std::string name) = 0;
};

inline creature::~creature() { }

#endif /* _CREATURE_H_ */
