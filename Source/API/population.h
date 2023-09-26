#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <cstdint>
#include <memory>

#include "creature.h"

/*! \brief The population object represents the top level container for a genetic algorithm experiment.
 *         It is used to kick off the algorithm execution as well as retrieve evolved answers in the
 *         form of \ref<creature> objects.
 *  \details The population object represents the top level container for a genetic algorithm experiment.
 *           It is constructed from the \ref<genetic_factory> against a paticular metadata description.
 *           The metadata description provided to the \ref<genetic_factory> is a declarative description
 *           of the genetic algorithm implementation to be used in the experiment. The concrete algorithm
 *           described by the metadata can be executed by invoking the \ref<evolve> method. Once the \ref<evolve>
 *           method has finished executing the experiment is complete and the evolved answers to the problem
 *           can be retrieved in the form of \ref<creature> objects.
 */
class population {
public:
    //! A default implementation of the population destructor.
    virtual ~population() = default;

    /*! \brief Gets the size of the population in terms of \ref<creature> objects.
     *  \return The size of the population in terms of \ref<creature> objects.
     */
    virtual size_t get_size() const = 0;

    /*! 
     *  \brief Indexes a \ref<creature> from the population.
     *  \return The \ref<creature> at the provided index.
     */
    virtual std::shared_ptr<creature> operator[] (int) const = 0;

    /*! \brief Gets a \ref<creature> from the population.
     *  \param[i] The index of the \ref<creature> to retrieve.
     *  \return The \ref<creature> at the provided index.
     */
    virtual std::shared_ptr<creature> get_creature(int i) const = 0;

    /*! \brief Gets the \ref<creature> that is considered to be the optimal solution to
     *         the problem statement in terms of the user provided \ref<fitness_function>.
     *  \details Gets the \ref<creature> that is considered to be the optimal soultion to
     *           the user defined problem statement. The quality of the \ref<creature> is measured
     *           by the \ref<fitness_function>, a user defined metric evaluating the abillity for the
     *           solution encoded by the \ref<creature> to answer the problem statement.
     *  \return The \ref<creature> considered to be the optimal soultion to the problem statement.
     */
    virtual std::shared_ptr<creature> get_optimal_creature() const = 0;

    /*! \brief Invokes the genetic algorithm parameterized with the provided metadata.
     *  \details Invokes the genetic algorithm parameterized with the provided metadata.
     *           The genetic algorithm will elvove successive generations of \ref<creature>
     *           objects which represent an encoded solution to the user defined problem statement.
     */
    virtual void evolve() = 0;
};

#endif /* _POPULATION_H_ */
