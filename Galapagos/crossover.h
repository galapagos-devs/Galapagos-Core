#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "operator.h"
#include "chromosome.h"

class crossover : genetic_operator {
public:
	virtual chromosome* operator()(chromosome* x, chromosome* y) abstract;
};

#endif /* _CROSSOVER_H_ */ 