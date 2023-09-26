#ifndef _GENETIC_OPERATOR_H_
#define _GENETIC_OPERATOR_H_

#include "galapagos_metadata.h"

/*! \brief The genetic operator is an operation that can be preformed on a \ref<chromosome> object.
 *  \details The genetic operator is the abstract base class for \ref<crossover> and \ref<mutation>
 *           objects. These operations are used to evolve the encoded solutions through successive
 *           generations of the genetic algorithm.
 */
class genetic_operator {
private:
    genetic_operator_metadata_ptr _metadata;

public:
    /*! \brief The base class constructor of the genetic operator.
     *  \param[metadata] The metadata the parameterizes the genetic operator implementation.
     */
    explicit inline genetic_operator(genetic_operator_metadata_ptr metadata) :
        _metadata{metadata} {}

    //! A default implementation of the genetic operator destructor.
    virtual ~genetic_operator() = default;

    /*! \brief Gets the weight indicating the porportion of time this operator should be used.
     *  \return The weight indicating the porportion of time this operator should be used.
     */
    inline double get_weight() const {
        return _metadata->weight;
    }
};

#endif /* _GENETIC_OPERATOR_H_ */
