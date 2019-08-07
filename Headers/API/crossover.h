#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "../../Headers/API/chromosome.h"
#include "operator.h"

class crossover : genetic_operator {
public:
	virtual chromosome* operator()(chromosome* x, chromosome* y) abstract;
};

#endif /* _CROSSOVER_H_ */ 