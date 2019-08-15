#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "../../Source/API/chromosome.h"
#include "operator.h"

class mutation : genetic_operator {
public:
	virtual chromosome* operator()(chromosome* chromosome) = 0;
};

#endif /* _MUTATION_H_ */
