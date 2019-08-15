#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "../../Source/API/chromosome.h"
#include "operator.h"

class crossover : genetic_operator {
public:
	virtual chromosome* operator()(chromosome* x, chromosome* y)  = 0;
};

#endif /* _CROSSOVER_H_ */
