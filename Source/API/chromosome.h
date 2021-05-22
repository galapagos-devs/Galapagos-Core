#ifndef _CHROMOSOME_H_
#define _CHROMOSOME_H_

#include <memory>

class chromosome {
public:
    virtual ~chromosome() = default;

    virtual double get_distance(const std::shared_ptr<const chromosome>& other) const = 0;
};

#endif /* _CHROMOSOME_H_ */
