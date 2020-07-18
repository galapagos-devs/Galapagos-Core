#ifndef _CREATURE_INTERNAL_H_
#define _CREATURE_INTERNAL_H_

#include <string>
#include <functional>
#include <memory>

#include "API/creature.h"
#include "API/chromosome.h"
#include "API/crossover.h"
#include "API/mutation.h"
#include "API/galapagos_metadata.h"
#include "API/stochastic.h"

template <class TOperator, class TMetadata>
using create_genetic_operator_a = std::function<std::shared_ptr<TOperator>(const TMetadata*)>;

class creature_internal : public creature {
private:
    const creature_metadata _creature_metadata;
    stochastic* _stochastic_instance;

public:
    creature_internal(const creature_metadata creature_metadata, stochastic* stochastic_instance);
    ~creature_internal() override;

    double get_fitness() override;

    creature* breed_with(const creature* const mate) const override ;

private:
    // Templated function for _select_crossover and _select_mutation.
    template <class TOperator, class TMetadata>
    std::shared_ptr<TOperator> _select_genetic_operator(const std::vector<const TMetadata*> operator_metadata,
                                        create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator) const;
    std::shared_ptr<crossover> _select_crossover(const std::vector<const crossover_metadata*>& crossover_metadata) const;
    std::shared_ptr<mutation> _select_mutation(const std::vector<const mutation_metadata*>& mutation_metadata) const;
};

#endif /* _CREATURE_INTERNAL_H_ */
