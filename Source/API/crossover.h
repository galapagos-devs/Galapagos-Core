#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include <memory>

#include "chromosome.h"
#include "genetic_operator.h"

/*! \brief An algorithm for combining two \ref<chromosome>s.
 */
class crossover : public genetic_operator {
public:
    /*! \brief The constructor of the crossover.
     *  \param[metadata] The metadata that parameterizes the crossover implementation.
     */
    inline crossover(crossover_metadata_ptr metadata) :
        genetic_operator{metadata} {}

    /*! \brief Invokes the crossover. 
     *  \param[x] The father \ref<chromosome>.
     *  \param[y] The mother \ref<chromosome>.
     *  \return The child \ref<chromosome>.
     */
    virtual std::shared_ptr<chromosome> invoke(const std::shared_ptr<const chromosome>& x, const std::shared_ptr<const chromosome>& y) const = 0;

    /*! \brief Invokes the crossover. 
     *  \param[x] The father \ref<chromosome>.
     *  \param[y] The mother \ref<chromosome>.
     *  \return The child \ref<chromosome>.
     */
    inline std::shared_ptr<chromosome> operator()(const std::shared_ptr<const chromosome>& x, const std::shared_ptr<const chromosome>& y) const {
        return invoke(x, y);
    }
};

#endif /* _CROSSOVER_H_ */
