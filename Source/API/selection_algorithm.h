#ifndef _SELECTION_ALGORITHM_H_
#define _SELECTION_ALGORITHM_H_

#include <memory>

#include "creature.h"
#include "population.h"

/*! \brief An algorithm for selecting a \ref<creature> for breeding. 
 *  \details An algorithm for selecting a \ref<creature> for breeding the next generation.
 */
class selection_algorithm {
public:
    //! A default implementation of the selection algorithms destructor.
    virtual ~selection_algorithm() = default;

    /*! \brief Invokes the selection algorithm. 
     *  \param[population] The \ref<population> to select the \ref<creature> from.
     *  \return The selected \ref<creature>.
     */
    virtual std::shared_ptr<creature> invoke(const std::shared_ptr<const population>& population) const = 0;

     /*! \brief Invokes the selection algorithm. 
     *  \param[population] The \ref<population> to select the \ref<creature> from.
     *  \return The selected \ref<creature>.
     */
    inline std::shared_ptr<creature> operator()(const std::shared_ptr<const population>& population) const {
        return invoke(population);
    }
};

#endif /* _SELECTION_ALGORITHM_H_ */
