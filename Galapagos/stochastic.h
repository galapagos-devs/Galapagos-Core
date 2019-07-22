#ifndef _STOCHASTIC_H_
#define _STOCHASTIC_H_

class stochastic {
public:
	virtual bool flip_coin() abstract;

	virtual bool evaulate_probability() abstract;

	virtual int next(int max) abstract;

	virtual int next(int min, int max) abstract;

	virtual double next_double() abstract;
};

#endif /* _STOCHASTIC_H_ */