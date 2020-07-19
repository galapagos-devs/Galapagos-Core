#include <vector>

#include "API/stochastic.h"

#include "creature_internal.h"
#include "genetic_factory.h"

// Constructor/Destructor
creature_internal::creature_internal(const creature_metadata& metadata, stochastic* stochastic_instance) :
        _metadata{metadata}, _stochastic_instance{stochastic_instance} {

    genetic_factory& factory = genetic_factory::get_instance();
    for(const auto& chromosome_metadatum : _metadata.chromosome_metadata)
        _chromosomes[chromosome_metadatum->name] = factory.create_chromosome(*chromosome_metadatum);
}

// Public methods
double creature_internal::get_fitness() {
    return _metadata.fitness_function(this);
}

creature* creature_internal::breed_with(const creature* const mate) const {
    auto* child = new creature_internal(_metadata, _stochastic_instance);

    //for(size_t i = 0; i < _metadata.num_chromosomes; i++)
    for(const auto& chromosome_metadatum : _metadata.chromosome_metadata) {
        std::string chromosome_name = chromosome_metadatum->name;
        chromosome* child_chromosome;

        // Select crossover & mutation proportional to their weight
        auto crossover = _select_crossover(chromosome_metadatum->crossover_metadata);
        auto mutation = _select_mutation(chromosome_metadatum->mutation_metadata);

        auto* x = get_chromosome<chromosome>(chromosome_name);  // chromosome of this creature
        auto* y = mate->get_chromosome<chromosome>(chromosome_name);

        // TODO: mem leak as crossovers and mutations create a new chromosome

        // Conditionally apply cross-over
        if(_stochastic_instance->evaluate_probability(chromosome_metadatum->crossover_rate))
            child_chromosome = (*crossover)(x, y);
        else
            child_chromosome = x;

        // Conditionally apply mutation
        if(_stochastic_instance->evaluate_probability(chromosome_metadatum->mutation_rate))
            child_chromosome = (*mutation)(child_chromosome);

        child->set_chromosome(chromosome_name, child_chromosome);
    }

    return child;
}

// Private methods
template <class TOperator, class TMetadata>
std::shared_ptr<TOperator> creature_internal::_select_genetic_operator(const std::vector<std::shared_ptr<const TMetadata>> operator_metadata,
                                                       create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator) const {
    auto num_operators = operator_metadata.size();
    std::vector<std::shared_ptr<TOperator>> genetic_operators;
    std::shared_ptr<double[]> weights(new double[num_operators]);

    for(size_t i = 0; i < num_operators; i++) {
        // populate genetic_operators vector
        genetic_operators.push_back(create_genetic_operator(*operator_metadata[i]));

        // populate weights list
        weights[i] = genetic_operators[i]->get_weight();
    }

    size_t chosen_index = _stochastic_instance->weight_proportionate_selection(weights.get(), num_operators);
    return genetic_operators[chosen_index];
}

std::shared_ptr<crossover> creature_internal::_select_crossover(const std::vector<std::shared_ptr<const crossover_metadata_t>>& crossover_metadata) const {
    genetic_factory& factory = genetic_factory::get_instance();
    create_genetic_operator_a<crossover, crossover_metadata_t> create_crossover =
            [&factory](const crossover_metadata_t& metadatai) { return factory.create_crossover(metadatai); };
    return _select_genetic_operator<crossover, crossover_metadata_t>(crossover_metadata, create_crossover);
}

std::shared_ptr<mutation> creature_internal::_select_mutation(const std::vector<std::shared_ptr<const mutation_metadata_t>>& mutation_metadata) const {
    genetic_factory& factory = genetic_factory::get_instance();
    create_genetic_operator_a<mutation, mutation_metadata_t> create_mutation =
            [&factory](const mutation_metadata_t& metadatai) { return factory.create_mutation(metadatai); };
    return _select_genetic_operator<mutation, mutation_metadata_t>(mutation_metadata, create_mutation);
}
