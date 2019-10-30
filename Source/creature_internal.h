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

// TODO: type alias only works with C++11 or later
template <class TOperator, class TMetadata>
using create_genetic_operator_a = std::function<TOperator*(TMetadata* metadata)>;

class creature_internal : creature {

private:
    creature_metadata* _creature_metadata;
    std::map<std::string, chromosome*> _chromosomes;


public:
    creature_internal(creature_metadata* creature_metadata, stochastic* stochastic_instance);

    ~creature_internal();

    double get_fitness() override;

    chromosome* get_chromosome(std::string name) override;

    creature* breed_with(creature* mate) override;

private:
    template <class TOperator, class TMetadata>
    TOperator* _get_genetic_operator(TMetadata** operator_metadata, size_t num_operators,
        create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator);

    crossover* _get_crossover(crossover_metadata** crossover_metadata, size_t num_crossovers);
    mutation* _get_mutation(mutation_metadata** mutation_metadata, size_t num_mutations);

    void _set_chromosome(std::string name, chromosome* new_chromosome);
};

#endif /* _CREATURE_INTERNAL_H_ */