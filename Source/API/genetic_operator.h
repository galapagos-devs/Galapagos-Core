#ifndef _GENETIC_OPERATOR_H_
#define _GENETIC_OPERATOR_H_

#include "galapagos_metadata.h"

class genetic_operator {
private:
    const genetic_operator_metadata& _metadata;

public:
    inline genetic_operator(const genetic_operator_metadata& metadata) :
        _metadata{metadata} {}
    virtual ~genetic_operator() = default;

    inline double get_weight() const {
        return  _metadata.weight;
    }
};

#endif /* _GENETIC_OPERATOR_H_ */
