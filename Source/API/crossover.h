#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "chromosome.h"
#include "genetic_operator.h"

class crossover : public genetic_operator {
public:
	virtual chromosome* invoke(chromosome* x, chromosome* y) = 0;
};

//inline crossover::~crossover { }

#endif /* _CROSSOVER_H_ */
