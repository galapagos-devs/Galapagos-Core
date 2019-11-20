#ifndef _CHROMOSOME_H_
#define _CHROMOSOME_H_

class chromosome {
public:
	virtual ~chromosome() = 0;

	virtual double get_distance(chromosome* other) = 0;
};

#endif /* _CHROMOSOME_H_ */
