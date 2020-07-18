#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include <vector> // TODO: probably don't need
#include <map>
#include <typeindex>

#include "API/galapagos.h"
#include "API/galapagos_metadata.h"
#include "API/chromosome.h"
#include "API/selection_algorithm.h"
#include "API/termination_condition.h"
#include "API/crossover.h"
#include "API/mutation.h"

class genetic_factory {
private:
    std::map<std::type_index, create_selection_algorithm_t> _registered_selection_algorithms;
    std::map<std::type_index, create_termination_condition_t> _registered_termination_conditions;
    std::vector<try_create_chromosome_t> _registered_chromosomes;
    std::map<std::type_index, create_crossover_t> _registered_crossovers;
    std::map<std::type_index, create_mutation_t> _registered_mutations;

public:
    static genetic_factory& get_instance(); // singleton access

    //region plugin registration

    void reset();

    void register_selection_algorithm(std::type_index index, const create_selection_algorithm_t& create_selection_algorithm);
    void register_termination_condition(std::type_index index, const create_termination_condition_t& create_termination_condition);

    void register_chromosome(const try_create_chromosome_t& try_create);
    void register_crossover(std::type_index index, const create_crossover_t& create_crossover);
    void register_mutation(std::type_index index, const create_mutation_t& create_mutation);

    //endregion

    //region plugin construction

    std::shared_ptr<selection_algorithm> create_selection_algorithm(const selection_algorithm_metadata* selection_algorithm_metadata);
    std::shared_ptr<termination_condition> create_termination_condition(const termination_condition_metadata* termination_condition_metadata);

    chromosome* create_chromosome(const chromosome_metadata* chromosome_metadata);
    std::shared_ptr<crossover> create_crossover(const crossover_metadata* crossover_metadata);
    std::shared_ptr<mutation> create_mutation(const mutation_metadata* mutation_metadata);

    //endregion

private:
    genetic_factory() = default;
};

#endif /* _GENETIC_FACTORY_H_ */
