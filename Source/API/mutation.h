#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "chromosome.h"
#include "genetic_operator.h"

class mutation : genetic_operator {
public:
	virtual ~mutation() override;

	virtual chromosome* invoke(chromosome* chromosome) = 0;
};

//inline mutation::~mutation { }

#endif /* _MUTATION_H_ */
