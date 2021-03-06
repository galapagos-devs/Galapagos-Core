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
using create_genetic_operator_a = std::function< std::shared_ptr<TOperator>(std::shared_ptr<const TMetadata>) >;

class creature_internal : public creature {
private:
    creature_metadata_ptr _metadata;
    stochastic& _stochastic_instance;

public:
    creature_internal(creature_metadata_ptr metadata, stochastic& stochastic_instance);

    double get_fitness() override;

    [[nodiscard]] std::shared_ptr<creature> breed_with(const std::shared_ptr<const creature>& mate) const override;

private:
    // Templated function for _select_crossover and _select_mutation.
    template <class TOperator, class TMetadata>
    std::shared_ptr<TOperator> _select_genetic_operator(std::vector<std::shared_ptr<const TMetadata>> operator_metadata,
                                        create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator) const;
    [[nodiscard]] std::shared_ptr<crossover> _select_crossover(const std::vector<crossover_metadata_ptr>& crossover_metadata) const;
    [[nodiscard]] std::shared_ptr<mutation> _select_mutation(const std::vector<mutation_metadata_ptr>& mutation_metadata) const;
};

#endif /* _CREATURE_INTERNAL_H_ */
