#ifndef _STOCHASTIC_H_
#define _STOCHASTIC_H_

class stochastic {
public:
	virtual ~stochastic() = 0;

	virtual bool flip_coin() = 0;

	virtual bool evaulate_probability(double probability) = 0;

	virtual int rand_int(int max) = 0;

	virtual int rand_int(int min, int max) = 0;

	virtual double rand_percent() = 0;
};

inline stochastic::~stochastic() { }

#endif /* _STOCHASTIC_H_ */
