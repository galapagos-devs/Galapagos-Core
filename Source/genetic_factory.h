#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include <vector>

#include "API/galapagos.h"
#include "API/galapagos_metadata.h"
#include "API/chromosome.h"
#include "API/selection_algorithm.h"
#include "API/termination_condition.h"
#include "API/crossover.h"
#include "API/mutation.h"

class genetic_factory {
private:
    std::vector<try_create_selection_algorithm_t> _registered_selection_algorithms;
    std::vector<try_create_termination_condition_t> _registered_termination_conditions;
    std::vector<try_create_chromosome_t> _registered_chromosomes;
    std::vector<try_create_crossover_t> _registered_crossovers;
    std::vector<try_create_mutation_t> _registered_mutations;

public:
    static genetic_factory& get_instance(); // singleton access

    //region plugin registration

    void reset();

    void register_selection_algorithm(const try_create_selection_algorithm_t& try_create);
    void register_termination_condition(const try_create_termination_condition_t& try_create);

    void register_chromosome(const try_create_chromosome_t& try_create);

    void register_crossover(const try_create_crossover_t& try_create);
    void register_mutation(const try_create_mutation_t& try_create);

    //endregion

    //region plugin construction

    selection_algorithm* create_selection_algorithm(const selection_algorithm_metadata* selection_algorithm_metadata);
    termination_condition* create_termination_condition(const termination_condition_metadata* termination_condition_metadata);

    chromosome* create_chromosome(const chromosome_metadata* chromosome_metadata);

    crossover* create_crossover(const crossover_metadata* crossover_metadata);
    mutation* create_mutation(const mutation_metadata* mutation_metadata);

    //endregion

private:
    genetic_factory() = default;
};

#endif /* _GENETIC_FACTORY_H_ */
