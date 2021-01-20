#ifndef _GENETIC_FACTORY_H_
#define _GENETIC_FACTORY_H_

#include <map>
#include <tuple>
#include <typeindex>

#include "galapagos_metadata.h"
#include "population.h"
#include "creature.h"
#include "chromosome.h"
#include "selection_algorithm.h"
#include "termination_condition.h"
#include "crossover.h"
#include "mutation.h"

using create_population_t = std::function<population*(population_metadata_ptr)>;
using delete_population_t = std::function<void(population*)>;

using create_creature_t = std::function<creature*(creature_metadata_ptr)>;
using delete_creature_t = std::function<void(creature*)>;

using create_selection_algorithm_t = std::function<selection_algorithm*(selection_algorithm_metadata_ptr)>;
using delete_selection_algorithm_t = std::function<void(selection_algorithm*)>;

using create_termination_condition_t = std::function<termination_condition*(termination_condition_metadata_ptr)>;
using delete_termination_condition_t = std::function<void(termination_condition*)>;

using create_chromosome_t = std::function<chromosome*(chromosome_metadata_ptr)>;
using delete_chromosome_t = std::function<void(chromosome*)>;

using create_crossover_t = std::function<crossover*(crossover_metadata_ptr)>;
using delete_crossover_t = std::function<void(crossover*)>;

using create_mutation_t = std::function<mutation*(mutation_metadata_ptr)>;
using delete_mutation_t = std::function<void(mutation*)>;

class genetic_factory {
private:
    std::map<std::type_index, std::tuple<create_population_t, delete_population_t>> _registered_populations;
    std::map<std::type_index, std::tuple<create_creature_t, delete_creature_t>> _registered_creatures;
    std::map<std::type_index, std::tuple<create_selection_algorithm_t, delete_selection_algorithm_t>> _registered_selection_algorithms;
    std::map<std::type_index, std::tuple<create_termination_condition_t, delete_termination_condition_t>> _registered_termination_conditions;
    std::map<std::type_index, std::tuple<create_chromosome_t, delete_chromosome_t>> _registered_chromosomes;
    std::map<std::type_index, std::tuple<create_crossover_t, delete_crossover_t>> _registered_crossovers;
    std::map<std::type_index, std::tuple<create_mutation_t, delete_mutation_t>> _registered_mutations;

public:
    inline static genetic_factory& get_instance() { // singleton access
        static genetic_factory instance;
        return instance;
    }

    //region plugin registration

    inline void register_population(std::type_index index,
            const create_population_t& create_population, const delete_population_t& delete_population) {
        _register_obj(_registered_populations, index, create_population, delete_population);
    }

    inline void register_creature(std::type_index index,
            const create_creature_t& create_creature, const delete_creature_t& delete_creature) {
        _register_obj(_registered_creatures, index, create_creature, delete_creature);
    }

    inline void register_selection_algorithm(std::type_index index,
            const create_selection_algorithm_t& create_selection_algorithm, const delete_selection_algorithm_t& delete_selection_algorithm) {
        _register_obj(_registered_selection_algorithms, index, create_selection_algorithm, delete_selection_algorithm);
    }

    inline void register_termination_condition(std::type_index index,
            const create_termination_condition_t& create_termination_condition, const delete_termination_condition_t& delete_termination_condition) {
        _register_obj(_registered_termination_conditions, index, create_termination_condition, delete_termination_condition);
    }

    inline void register_chromosome(std::type_index index,
            const create_chromosome_t& create_chromosome, const delete_chromosome_t& delete_chromosome) {
        _register_obj(_registered_chromosomes, index, create_chromosome, delete_chromosome);
    }

    inline void register_crossover(std::type_index index,
            const create_crossover_t& create_crossover, const delete_crossover_t& delete_crossover) {
        _register_obj(_registered_crossovers, index, create_crossover, delete_crossover);
    }

    inline void register_mutation(std::type_index index,
            const create_mutation_t& create_mutation, const delete_mutation_t& delete_mutation) {
        _register_obj(_registered_mutations, index, create_mutation, delete_mutation);
    }

    //endregion

    //region plugin construction

    inline std::shared_ptr<population> create_population(population_metadata_ptr population_metadata) {
        return _create_obj<population>(_registered_populations, population_metadata);
    }

    inline std::shared_ptr<creature> create_creature(creature_metadata_ptr creature_metadata) {
        return _create_obj<creature>(_registered_creatures, creature_metadata);
    }

    inline std::shared_ptr<selection_algorithm> create_selection_algorithm(selection_algorithm_metadata_ptr selection_algorithm_metadata) {
        return _create_obj<selection_algorithm>(_registered_selection_algorithms, selection_algorithm_metadata);
    }

    inline std::shared_ptr<termination_condition> create_termination_condition(termination_condition_metadata_ptr termination_condition_metadata) {
        return _create_obj<termination_condition>(_registered_termination_conditions, termination_condition_metadata);
    }

    inline std::shared_ptr<chromosome> create_chromosome(chromosome_metadata_ptr chromosome_metadata) {
        return _create_obj<chromosome>(_registered_chromosomes, chromosome_metadata);
    }

    inline std::shared_ptr<crossover> create_crossover(crossover_metadata_ptr crossover_metadata) {
        return _create_obj<crossover>(_registered_crossovers, crossover_metadata);
    }

    inline std::shared_ptr<mutation> create_mutation(mutation_metadata_ptr mutation_metadata) {
        return _create_obj<mutation>(_registered_mutations, mutation_metadata);
    }

    //endregion

private:
    inline genetic_factory() = default;

    template<class TCreate, class TDelete>
    inline void _register_obj(std::map<std::type_index, std::tuple<TCreate, TDelete>>& registry,
                                std::type_index index, const TCreate& create_obj, const TDelete& delete_obj) {
        registry[index] = std::make_tuple(create_obj, delete_obj);
    }

    template<class TObj, class TMetadata, class TCreate, class TDelete>
    inline std::shared_ptr<TObj> _create_obj(std::map<std::type_index, std::tuple<TCreate, TDelete>>& registry,
                                            const TMetadata& metadata) {
        auto registration = registry[std::type_index(typeid(metadata))];
        auto create_obj = std::get<0>(registration);
        auto delete_obj = std::get<1>(registration);
        return std::shared_ptr<TObj>(create_obj(metadata), delete_obj);
    }
};

#endif /* _GENETIC_FACTORY_H_ */
