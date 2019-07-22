#ifndef _STOCHASTIC_H_
#define _STOCHASTIC_H_

class stochastic {
public:
	virtual bool flip_coin() abstract;

	virtual bool evaulate_probability(double probability) abstract;

	virtual int rand_int(int max) abstract;

	virtual int rand_int(int min, int max) abstract;

	virtual double rand_percent() abstract;
};

#endif /* _STOCHASTIC_H_ */