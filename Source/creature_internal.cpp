#include "API/stochastic.h"

#include "creature_internal.h"
#include "genetic_factory.h"

// Constructor/Destructor
creature_internal::creature_internal(const creature_metadata creature_metadata, stochastic* stochastic_instance) :
    _creature_metadata{creature_metadata}, _stochastic_instance{stochastic_instance} {


    genetic_factory& factory = genetic_factory::get_instance();
    for(auto chromosome_metadatum : _creature_metadata.chromosome_metadata)
        _chromosomes[chromosome_metadatum->name] = factory.create_chromosome(chromosome_metadatum);
}

creature_internal::~creature_internal() {
    // Delete all chromosomes
    for(auto it = _chromosomes.begin(); it != _chromosomes.end(); ++it) {
        delete it->second;
    }
}

// Public methods
double creature_internal::get_fitness() {
    return _creature_metadata.fitness_function(this);
}

creature_internal* creature_internal::breed_with(const creature_internal* const mate) const {
    auto* child = new creature_internal(_creature_metadata, _stochastic_instance);

    //for(size_t i = 0; i < _creature_metadata.num_chromosomes; i++)
    for(auto chromosome_metadatum : _creature_metadata.chromosome_metadata) {
        std::string chromosome_name = chromosome_metadatum->name;
        chromosome* child_chromosome;

        // Select crossover & mutation proportional to their weight
        crossover* crossover = _select_crossover(chromosome_metadatum->crossover_metadata);
        mutation* mutation = _select_mutation(chromosome_metadatum->mutation_metadata);

        auto* my_chromosome = get_chromosome<chromosome>(chromosome_name);  // chromosome of this creature
        auto* mate_chromosome = mate->get_chromosome<chromosome>(chromosome_name);

        // Conditionally apply cross-over
        if(_stochastic_instance->evaluate_probability(chromosome_metadatum->crossover_rate))
            child_chromosome = crossover->invoke(my_chromosome, mate_chromosome);
        else
            child_chromosome = my_chromosome;

        // Conditionally apply mutation
        if(_stochastic_instance->evaluate_probability(chromosome_metadatum->mutation_rate))
            child_chromosome = mutation->invoke(child_chromosome);

        child->_set_chromosome(chromosome_name, child_chromosome);

        // memory clean up
        // TODO: virtual destructor?
        delete crossover;
        delete mutation;
    }

    return child;
}

// Private methods
template <class TOperator, class TMetadata>
TOperator* creature_internal::_select_genetic_operator(const std::vector<const TMetadata*> operator_metadata,
                                                       create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator) const {
    auto num_operators = operator_metadata.size();
    std::vector<TOperator*> genetic_operators;
    auto* weights = new double[num_operators];

    for(size_t i = 0; i < num_operators; i++) {
        // populate genetic_operators vector
        TOperator* genetic_operator = create_genetic_operator(operator_metadata[i]);
        genetic_operators.push_back(genetic_operator);

        // populate weights list
        weights[i] = genetic_operator->get_weight();
    }

    size_t chosen_index = _stochastic_instance->weight_proportionate_selection(weights, num_operators);

    for(size_t i = 0; i < num_operators; i++) {  // memory clean up
        if(i != chosen_index)
            delete genetic_operators[i];
    }

    return genetic_operators[chosen_index];
}

crossover* creature_internal::_select_crossover(const std::vector<const crossover_metadata_t*>& crossover_metadata) const {
    genetic_factory& factory = genetic_factory::get_instance();
    create_genetic_operator_a<crossover, crossover_metadata_t>  create_crossover = [&factory](const crossover_metadata_t* metadatai) {
        return factory.create_crossover(metadatai);
    };
    return _select_genetic_operator<crossover, crossover_metadata_t>(crossover_metadata, create_crossover);
}

mutation* creature_internal::_select_mutation(const std::vector<const mutation_metadata_t*>& mutation_metadata) const {
    genetic_factory& factory = genetic_factory::get_instance();
    create_genetic_operator_a<mutation, mutation_metadata_t>  create_mutation = [&factory](const mutation_metadata_t* metadatai) {
        return factory.create_mutation(metadatai);
    };
    return _select_genetic_operator<mutation, mutation_metadata_t>(mutation_metadata, create_mutation);
}

void creature_internal::_set_chromosome(std::string name, chromosome* new_chromosome) {
    delete _chromosomes[name];
    _chromosomes[name] = new_chromosome;
}
