#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "chromosome.h"
#include "operator.h"

class mutation : genetic_operator {
public:
	virtual ~mutation() = 0;

	virtual chromosome* invoke(chromosome* chromosome) = 0;
};

inline mutation::~mutation { }

#endif /* _MUTATION_H_ */
