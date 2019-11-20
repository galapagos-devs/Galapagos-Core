#ifndef _CREATURE_INTERNAL_H_
#define _CREATURE_INTERNAL_H_

#include <string>
#include <map>
#include <vector>
#include <functional>

#include "API/creature.h"
#include "API/chromosome.h"
#include "API/crossover.h"
#include "API/mutation.h"
#include "API/galapagos_metadata.h"
#include "API/stochastic.h"

template <class TOperator, class TMetadata>
using create_genetic_operator_a = std::function<TOperator*(TMetadata* metadata)>;

class creature_internal : creature {

private:
    creature_metadata* _creature_metadata;

    std::map<std::string, chromosome*> _chromosomes;

    stochastic* _stochastic_instance;

public:
    creature_internal(creature_metadata* creature_metadata, stochastic* stochastic_instance);

    ~creature_internal() override;

    double get_fitness() override;

    chromosome* get_chromosome(std::string name) override;

    creature_internal* breed_with(creature_internal* mate);

private:
    // Templated function for _get_crossover and _get_mutation.
    template <class TOperator, class TMetadata>
    TOperator* _get_genetic_operator(TMetadata** operator_metadata, size_t num_operators,
        create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator);

    crossover* _get_crossover(crossover_metadata** crossover_metadata, size_t num_crossovers);
    mutation* _get_mutation(mutation_metadata** mutation_metadata, size_t num_mutations);

    void _set_chromosome(std::string name, chromosome* new_chromosome);
};

#endif /* _CREATURE_INTERNAL_H_ */
