#ifndef _GENETIC_OPERATOR_H_
#define _GENETIC_OPERATOR_H_

#include "galapagos_metadata.h"

class genetic_operator {
private:
    genetic_operator_metadata_ptr _metadata;

public:
    explicit inline genetic_operator(genetic_operator_metadata_ptr metadata) :
        _metadata{metadata} {}
    virtual ~genetic_operator() = default;

    inline double get_weight() const {
        return _metadata->weight;
    }
};

#endif /* _GENETIC_OPERATOR_H_ */
