#include "API/galapagos.h"

#include "genetic_factory.h"
#include "population_internal.h"
#include "stochastic_internal.h"

GALAPAGOS_BOOTSTRAP void gc_register_selection_algorithm(std::type_index index,
        const create_selection_algorithm_t& create_selection_algorithm,
        const delete_selection_algorithm_t& delete_selection_algorithm) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_selection_algorithm(index, create_selection_algorithm, delete_selection_algorithm);
}

GALAPAGOS_BOOTSTRAP void gc_register_termination_condition(std::type_index index,
        const create_termination_condition_t& create_termination_condition,
        const delete_termination_condition_t& delete_termination_condition) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_termination_condition(index, create_termination_condition, delete_termination_condition);
}

GALAPAGOS_BOOTSTRAP void gc_register_chromosome(std::type_index index,
        const create_chromosome_t& create_chromosome,
        const delete_chromosome_t& delete_chromosome) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_chromosome(index, create_chromosome, delete_chromosome);
}

GALAPAGOS_BOOTSTRAP void gc_register_crossover(std::type_index index,
        const create_crossover_t& create_crossover,
        const delete_crossover_t& delete_crossover) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_crossover(index, create_crossover, delete_crossover);
}

GALAPAGOS_BOOTSTRAP void gc_register_mutation(std::type_index index,
        const create_mutation_t& create_mutation,
        const delete_mutation_t& delete_mutation) {
    genetic_factory& factory = genetic_factory::get_instance();
    factory.register_mutation(index, create_mutation, delete_mutation);
}

GALAPAGOS_BOOTSTRAP population* gc_create_population(const population_metadata& metadata) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();
    return (population*)new population_internal(metadata, stochastic_instance);
}

GALAPAGOS_BOOTSTRAP void gc_delete_population(population* population) {
    delete population;
}
