#ifndef _GENETIC_OPERATOR_H_
#define _GENETIC_OPERATOR_H_

#include "galapagos_metadata.h"

class genetic_operator {
private:
    double _weight = 1;

public:
    inline genetic_operator(const genetic_operator_metadata* const metadata) :
        _weight{metadata->weight} {}
    virtual ~genetic_operator() = default;

    inline double get_weight() const {
        return  _weight;
    }
};

#endif /* _GENETIC_OPERATOR_H_ */
