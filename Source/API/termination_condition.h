#ifndef _TERMINATION_CONDITION_H_
#define _TERMINATION_CONDITION_H_

#include <memory>

#include "chromosome.h"
#include "population.h"

/*! \brief A condition that determines if the selection algorithm should terminate.
 */
class termination_condition {
public:
    //! A default implementation of the termination condition destructor.
    virtual ~termination_condition() = default;

    /*! \brief Invokes the termination condition. 
     *  \param[population] The \ref<population> to be evaluated for termination.
     */
    virtual bool invoke(const std::shared_ptr<const population>& population) const = 0;

    /*! \brief Invokes the termination condition. 
     *  \param[population] The \ref<population> to be evaluated for termination.
     */
    inline bool operator()(const std::shared_ptr<const population>& population) const {
        return invoke(population);
    }
};

#endif /* _TERMINATION_CONDITION_H_ */
