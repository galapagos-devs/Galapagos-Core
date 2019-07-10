#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "operator.h"
#include "chromosome.h"

class mutation : genetic_operator {
public:
	virtual chromosome* operator()(chromosome* chromosome) abstract;
};

#endif /* _MUTATION_H_ */ 