#ifndef _CHROMOSOME_H_
#define _CHROMOSOME_H_

#include <memory>

/*! \brief The chromosome object is an encoded representation for 1 dimension of the \ref<creature> solution.
 *
 *  \details The chromosome object is an encoded representation for 1 dimension of the \ref<creature> solution.
 *           N chromosome objects are contained in a single \ref<creature> object to create the full N-d solution
 *           to the user defined problem statement.
 */
class chromosome {
public:
    //! A default implementation of the creature destructor.
    virtual ~chromosome() = default;

    /*! \brief This method will be used to measure distance between two creatures in terms of encoding. This will be used to
     *         determine if two creatures belong in the same niche. Creatures belonging to the same niche will
     *         share fitness therfore protecting inovation when small changes to a creature solution will result in 
     *         dirasticaly reduced fitness but is a necessary first step to creating a more optimal substructre.
     *  \param[other] The other chromosome to get the distance between.
     */
    virtual double get_distance(const std::shared_ptr<const chromosome>& other) const = 0;
};

#endif /* _CHROMOSOME_H_ */
