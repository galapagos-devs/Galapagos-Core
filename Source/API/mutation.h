#ifndef _MUTATION_H_
#define _MUTATION_H_

#include <memory>

#include "chromosome.h"
#include "genetic_operator.h"

/*! \brief An algorithm for mutating a \ref<chromosome>.
 */
class mutation : public genetic_operator {
public:
    /*! \brief The constructor of the mutation.
     *  \param[metadata] The metadata that parameterizes the mutation implementation.
     */
    inline mutation(mutation_metadata_ptr metadata) :
        genetic_operator{metadata} {}

    /*! \brief Invokes the mutation. 
     *  \param[chromosme] The unmutated \ref<chromosome>.
     *  \return The mutated \ref<chromosome>.
     */
    virtual std::shared_ptr<chromosome> invoke(const std::shared_ptr<const chromosome>& chromosome) const = 0;

    /*! \brief Invokes the mutation. 
     *  \param[chromosme] The unmutated \ref<chromosome>.
     *  \return The mutated \ref<chromosome>.
     */
    inline std::shared_ptr<chromosome> operator()(const std::shared_ptr<const chromosome>& chromosome) const {
        return invoke(chromosome);
    }
};

#endif /* _MUTATION_H_ */
