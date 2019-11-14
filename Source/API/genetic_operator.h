#ifndef __GENETIC_OPERATOR_H_
#define __GENETIC_OPERATOR_H_

class genetic_operator {

public:
	virtual ~genetic_operator() = 0;

	virtual double get_weight() = 0;
};

#endif /* __GENETIC_OPERATOR_H_ */
