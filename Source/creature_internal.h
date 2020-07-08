#ifndef _CREATURE_INTERNAL_H_
#define _CREATURE_INTERNAL_H_

#include <string>
#include <vector>
#include <functional>

#include "API/creature.h"
#include "API/chromosome.h"
#include "API/crossover.h"
#include "API/mutation.h"
#include "API/galapagos_metadata.h"
#include "API/stochastic.h"

template <class TOperator, class TMetadata>
using create_genetic_operator_a = std::function<TOperator*(const TMetadata* metadata)>;

class creature_internal : creature {

private:
    const creature_metadata _creature_metadata;
    stochastic* _stochastic_instance;

public:
    creature_internal(creature_metadata creature_metadata, stochastic* stochastic_instance);

    ~creature_internal() override;

    double get_fitness() override;

    creature_internal* breed_with(const creature_internal* mate) const;

private:
    // Templated function for _select_crossover and _select_mutation.
    template <class TOperator, class TMetadata>
    TOperator* _select_genetic_operator(const std::vector<const TMetadata*> operator_metadata,
                                        create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator) const;

    [[nodiscard]] crossover* _select_crossover(const std::vector<const crossover_metadata*>& crossover_metadata) const;
    [[nodiscard]] mutation* _select_mutation(const std::vector<const mutation_metadata*>& mutation_metadata) const;

    void _set_chromosome(std::string name, chromosome* new_chromosome);
};

#endif /* _CREATURE_INTERNAL_H_ */
