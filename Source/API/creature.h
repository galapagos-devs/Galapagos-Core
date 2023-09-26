#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <stdexcept>
#include <string>
#include <map>
#include <memory>

#include "chromosome.h"

/*! \brief The creature object represents a solution to the user defined problem statement.
 *  \details The creature object represents a solution to the user defined problem statement. It is 
 *           a member of a \ref<population> collection and is breed over successive generations to
 *           optimize a fitness metric.
 */
class creature {
protected:
    std::map<std::string, std::shared_ptr<chromosome>> _chromosomes;  // TODO: Rename to `genome` and maybe make public.

public:
     //! A default implementation of the creature destructor.
    virtual ~creature() = default;

    /*! \brief Gets the fitness of the creature as measured by the user defined fitness metric.
     *  \return The fitness of the creature.
     */
    virtual double get_fitness() = 0;

    /*! \brief Gets the \ref<chromosome> with the given name.
     *  \details Gets the \ref<chromsome> with the provided name. The templated type determines the derived type
     *           of the \ref<chromosome>.
     *  \param[name] The name of the \ref<chromosome>.
     *  \return The \ref<chromosome> with the provided name and type.
     */
    template <class TChromosome>
    inline std::shared_ptr<TChromosome> get_chromosome(const std::string& name) const {
        auto chromosome = _chromosomes.find(name)->second;
        return std::dynamic_pointer_cast<TChromosome>(chromosome);
    }

    /*! \brief Sets the \ref<chromosome> with the provided name. 
     *  \param[name] The name of the \ref<chromosome> to set.
     *  \param[new_chromosome] The new \ref<chromosome>.
     */
    inline void set_chromosome(const std::string& name, const std::shared_ptr<chromosome> new_chromosome) {
        _chromosomes[name] = new_chromosome;
    }

    /*! \brief Breeds this \ref<creature> with a selected mate \ref<creature> to create a child \ref<creature>
     *         for the next generation.
     *  \details Breeds this \ref<creature> with a selected mate \ref<creature>. The \ref<creature>s selected for
     *           breeding are selected with a \ref<selection_algorithm>. The breeding prosees consists of preforming a
     *           \ref<crossover> on the selected parent \ref<chromosome>s and then preforming a \ref<mutation> on the
     *           child \ref<chromosome>s.
     *  \param[mate] The mate \ref<creature>.
     *  \returns The child \ref<creature>.
     */
    virtual std::shared_ptr<creature> breed_with(const std::shared_ptr<const creature>& mate) const = 0;
};

#endif /* _CREATURE_H_ */
